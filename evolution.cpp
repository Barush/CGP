/******************************************************************************/
/************************ COEVOLUTION IN CGP **********************************/
/************************* BACHELORS THESIS ***********************************/
/*********************** BARBORA SKRIVANKOVA **********************************/
/********************* xskri01@stud.fit.vutbr.cz ******************************/
/******************************************************************************/

/************* MODUL USED TO FIND PARENTS AND MUTATE IT ***********************/
/** file name: 			evolution.cpp
	creation date:		10/2013
**/

#include "evolution.h"

void copyGenotype(TIndividual* from, TIndividual* to, TCgpProperties* geneticP){
	//copy program nodes
	for(int i = 0; i < geneticP->rows; i++){
		for(int j = 0; j < geneticP->cols; j++){
			//copy input1
			to->CgpProgram[i][j].input1  = from->CgpProgram[i][j].input1;
			//copy input2
			to->CgpProgram[i][j].input2  = from->CgpProgram[i][j].input2;
			//copy function
			to->CgpProgram[i][j].function  = from->CgpProgram[i][j].function;
		}
	}

	//copy output
	to->output->input1 = from->output->input1;

	//copy fitness
	to->fitness = from->fitness;
}

void getParents(TIndividual* geneticArray, TCgpProperties* geneticP){
	int max = -1;
	TIndividual* parent;

	for(int i = 0; i < geneticP->individCount; i++){
		//cerr << (*geneticArray)[i].fitness << " ";
		if(geneticArray[i].fitness > max){
			max = geneticArray[i].fitness;
			parent = &(geneticArray[i]);
		}
		else if(geneticArray[i].fitness == max){
			if(geneticArray[i].activeNodesCount < parent->activeNodesCount){
				parent = &(geneticArray[i]);
			}
			else if(i > 0){
				parent = &(geneticArray[i]);
			}
		}
	}

	//cerr << "->" << parent->fitness << endl;
	/*for(int i = 0; i < geneticP->individCount; i++){
		printResult(&(*geneticArray)[i], geneticP);
		printReadableResult(&(*geneticArray)[i], geneticP);
	}*/

	copyGenotype(parent, &geneticArray[0], geneticP);
}

void changeGenes(TIndividual* genotype, TCgpProperties* geneticP, TFuncAvailable* functions){
	//generate percent - 3-10
	double percent = ((rand() % 7) + 3.5) / 100;	//uniform(3,10) + 0.5 for the round corection
	int nodesCount = geneticP->rows * geneticP->cols;
	int index, row, col, part;

	for(int i = 0; i < (percent * (nodesCount * (geneticP->compInCount + 1))); i++){
		//which gene is to change
		index = rand() % nodesCount;
		row = index % geneticP->rows;
		col = index / geneticP->rows;
		part = (int)(rand() % geneticP->compInCount + 0.5); // 0=input1, 1=input2, 2=function

		//change the gene
		if(index == nodesCount){
			//changing the output fnc
			genotype->output->input1 = rand() % nodesCount;
		}
		else{

			//changing some of nodes
			if(part == 2){
				int prevFnc = genotype->CgpProgram[row][col].function;
				//changing the function
				genotype->CgpProgram[row][col].function = functions->funArr[rand() % functions->funCnt];
				if(genotype->CgpProgram[row][col].function == CONST){
					//correction needed for constants
					genotype->CgpProgram[row][col].input1 = rand() % CONSTCOUNT;
				}
				else if(prevFnc == CONST){
					//input1 corrections
					if(geneticP->l_back < col){
						genotype->CgpProgram[row][col].input1 = (rand() % (geneticP->rows * geneticP->l_back)) + 
							((col - geneticP->l_back) * geneticP->rows) + geneticP->inCount;
					}
					else{
						genotype->CgpProgram[row][col].input1 = rand() % (col * geneticP->rows + geneticP->inCount);
					}
				}
			}

			else if(part < 2){
				//changing input1 or input2
				if((genotype->CgpProgram[row][col].function == CONST) && (part == 0)){
					//node function is const
					genotype->CgpProgram[row][col].input1 = rand() % CONSTCOUNT;
				}
				else if(geneticP->l_back < col){
					//lback is in use
					if(part == 0){
						//changing input1
						genotype->CgpProgram[row][col].input1 = (rand() % (geneticP->rows * geneticP->l_back)) + 
							((col - geneticP->l_back) * geneticP->rows) + geneticP->inCount;
					}
					else{
						//changing input2
						genotype->CgpProgram[row][col].input2 = (rand() % (geneticP->rows * geneticP->l_back)) + 
							((col - geneticP->l_back) * geneticP->rows) + geneticP->inCount;
					}
				}
				else{
					//lback not used
					if(part == 0){
						genotype->CgpProgram[row][col].input1 = rand() % (col * geneticP->rows + geneticP->inCount);
					}
					else{
						genotype->CgpProgram[row][col].input2 = rand() % (col * geneticP->rows + geneticP->inCount);
					}
				}
			}
		}
	}
}

void createChildren(TIndividual* geneticArray, TCgpProperties* geneticP, TFuncAvailable* functions){
	for(int i = 1; i < geneticP->individCount; i++){
		//copy parent
		copyGenotype(&geneticArray[0], &geneticArray[i], geneticP);
		//change 3-10% of genes
		changeGenes(&geneticArray[i], geneticP, functions);
	}
}

void evolutionStep(TData* input, TCgpProperties* geneticP, TIndividual* geneticArray, TFuncAvailable* functions, TTest* test){

#ifdef COEVOLUTION
	TCoevIndividual* testVect = NULL;
	testVect = (TCoevIndividual*)malloc(sizeof(struct test));
	pthread_mutex_lock(&test->test_sem);
	testVect->value = new vector<int>(test->test->value);
	pthread_mutex_unlock(&test->test_sem);
#endif

	getActiveNodes(geneticArray, geneticP);
 
 	for(int ind = 0; ind < geneticP->individCount; ind++){
 		resetFitness_ActiveNodes(&geneticArray[ind], geneticP);
#ifdef COEVOLUTION
 		for(int i = 0; i < geneticP->testSize; i++){
 			getValue(&geneticArray[ind], geneticP, input->data[testVect->value->at(i)]);
			getFitness(&geneticArray[ind], geneticP, input->data[testVect->value->at(i)]);			
 		}
 		free(testVect);
#else
		for(int i = 0; i < input->dataCount; i++){
			getValue(&geneticArray[ind], geneticP, input->data[i]);
			getFitness(&geneticArray[ind], geneticP, input->data[i]);
		}	
#endif
 	}


	//get parents
	getParents(geneticArray, geneticP);

	//create new generation
	createChildren(geneticArray, geneticP, functions);
}
