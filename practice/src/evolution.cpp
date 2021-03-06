/******************************************************************************/
/************************ COEVOLUTION IN CGP **********************************/
/************************* BACHELORS THESIS ***********************************/
/*********************** BARBORA SKRIVANKOVA **********************************/
/********************* xskri01@stud.fit.vutbr.cz ******************************/
/******************************************************************************/

/************* MODUL USED TO FIND PARENTS AND NEW GENERATION ******************/
/** file name: 			evolution.cpp
	creation date:		10/2013
**/

#include "evolution.h"

/******************************************************************************
	Function copyGenotype - copies content of one individual into another
		individual
	Takes parameters:
		@from - pointer to individual which is copied
		@to - pointer to individual into which is copied
		@geneticP - pointer to a struct of all CGP params
******************************************************************************/
void copyGenotype(TIndividual* from, TIndividual* to, TCgpProperties* geneticP){
	//copy program nodes
	for(int i = 0; i < geneticP->rows; i++){
		for(int j = 0; j < geneticP->cols; j++){
			to->CgpProgram->at(i)[j].input1  = from->CgpProgram->at(i)[j].input1;
			to->CgpProgram->at(i)[j].input2  = from->CgpProgram->at(i)[j].input2;
			to->CgpProgram->at(i)[j].function  = from->CgpProgram->at(i)[j].function;
		}
	}

	//copy output
	to->output.input1 = from->output.input1;
	//copy fitness
	to->fitness = from->fitness;
}

/******************************************************************************
	Function getParents - selects the best individual in the generation compared
		by fitness. Secondary parameters - the one which was not parent is better
		and the one with shorter equation is better.
	Takes parameters:
		@geneticArray - pointer to a vector of whole population
		@geneticP - pointer to a struct of all CGP params
******************************************************************************/
void getParents(vector<TIndividual>* geneticArray, TCgpProperties* geneticP){
	int max = -1;
	TIndividual* parent;

	for(int i = 0; i < geneticP->individCount; i++){
		if(geneticArray->at(i).fitness > max){
			max = geneticArray->at(i).fitness;
			parent = &(geneticArray->at(i));
		}
		else if(geneticArray->at(i).fitness == max){
			if(geneticArray->at(i).activeNodesCount < parent->activeNodesCount){
				parent = &(geneticArray->at(i));
			}
			else if((i > 0) && (parent == &(geneticArray->at(i)))){
				parent = &(geneticArray->at(i));
			}
		}
	}

	copyGenotype(parent, &geneticArray->at(0), geneticP);
}

/******************************************************************************
	Function changeGenes - selects 1-8% of genes in the genotype and randomly 
		changes it
	Takes parameters:
		@genotype - pointer to an individual to be changed
		@geneticP - pointer to a struct of all CGP params
		@functions - pointer to an array of available functions
******************************************************************************/
void changeGenes(TIndividual* genotype, TCgpProperties* geneticP, TFuncAvailable* functions){
	//generate percent - 1-8
	double percent = ((rand() % 8) + 1) / 100;	//uniform(1,8) 
	int nodesCount = geneticP->rows * geneticP->cols;
	int index, row, col, part;

	//zero to n --> round up
	for(int i = 0; i < (percent * (nodesCount * (geneticP->compInCount + 1))); i++){
		//which gene is to change
		index = rand() % (nodesCount + 1);

		//change the gene
		if(index == nodesCount){
			//changing the output fnc
			genotype->output.input1 = rand() % nodesCount;
			while(genotype->output.input1 < geneticP->inCount){
				genotype->output.input1 = rand() % nodesCount;
			}
		}
		else{
			//changing some of nodes

			row = index % geneticP->rows;
			col = index / geneticP->rows;
			part = rand() % (geneticP->compInCount + 1); // 0=input1, 1=input2, 2=function

			if(part == 2){
				int prevFnc = genotype->CgpProgram->at(row)[col].function;
				//changing the function
				genotype->CgpProgram->at(row)[col].function = functions->funArr->at(rand() % functions->funCnt);
				if((genotype->CgpProgram->at(row)[col].function == CONST) && (prevFnc != CONST)){
					//correction needed for constants
					genotype->CgpProgram->at(row)[col].input1 = rand() % CONSTCOUNT;
				}
				else if((genotype->CgpProgram->at(row)[col].function != CONST) && (prevFnc= CONST)){
					//input1 corrections
					if(geneticP->l_back < col){
						genotype->CgpProgram->at(row)[col].input1 = (rand() % (geneticP->rows * geneticP->l_back)) + 
							((col - geneticP->l_back) * geneticP->rows) + geneticP->inCount;
					}
					else{
						genotype->CgpProgram->at(row)[col].input1 = rand() % (col * geneticP->rows + geneticP->inCount);
					}
				}
			}

			else if(part < 2){
				//changing input1 or input2
				if((genotype->CgpProgram->at(row)[col].function == CONST) && (part == 0)){
					//node function is const
					genotype->CgpProgram->at(row)[col].input1 = rand() % CONSTCOUNT;
				}
				else if(geneticP->l_back < col){
					//lback is in use
					if(part == 0){
						//changing input1
						genotype->CgpProgram->at(row)[col].input1 = (rand() % (geneticP->rows * geneticP->l_back)) + 
							((col - geneticP->l_back) * geneticP->rows) + geneticP->inCount;
					}
					else{
						//changing input2
						genotype->CgpProgram->at(row)[col].input2 = (rand() % (geneticP->rows * geneticP->l_back)) + 
							((col - geneticP->l_back) * geneticP->rows) + geneticP->inCount;
					}
				}
				else{
					//lback not used
					if(part == 0){
						genotype->CgpProgram->at(row)[col].input1 = rand() % (col * geneticP->rows + geneticP->inCount);
					}
					else{
						genotype->CgpProgram->at(row)[col].input2 = rand() % (col * geneticP->rows + geneticP->inCount);
					}
				}
			}
		}
	}
}


/******************************************************************************
	Function createChildren - controls the process of creating children
	Takes parameters:
		@geneticArray - pointer to a vector of whole population
		@geneticP - pointer to a struct of all CGP params
		@functions - pointer to an array of available functions
******************************************************************************/
void createChildren(vector<TIndividual>* geneticArray, TCgpProperties* geneticP, TFuncAvailable* functions){
	for(int i = 1; i < geneticP->individCount; i++){
		//copy parent
		copyGenotype(&geneticArray->at(0), &geneticArray->at(i), geneticP);
		//change 3-10% of genes
		changeGenes(&geneticArray->at(i), geneticP, functions);
	}
}

/******************************************************************************
	Function evolutionStep - controls one evolution step, is called for each
		generation, manages the deffirences between CGP and coevolution
	Takes parameters:
		@input - pointer to an array of all training vectors
		@geneticP - pointer to a struct of all CGP params
		@geneticArray - pointer to a vector of whole population
		@functions - pointer to an array of available functions
		@test - pointer to the test - in variant without coevolution is NULL
******************************************************************************/
void evolutionStep(TData* input, TCgpProperties* geneticP, vector<TIndividual>* geneticArray, TFuncAvailable* functions, TTest* test){

#ifdef COEVOLUTION
	//copy test vector from shared memory
	TCoevIndividual* testVect = NULL;
	testVect = (TCoevIndividual*)malloc(sizeof(struct test));
	pthread_mutex_lock(&test->test_sem);
	testVect->value = new vector<int>(*test->test.value);
	pthread_mutex_unlock(&test->test_sem);
#endif

	getActiveNodes(geneticArray, geneticP);
 
 	for(int ind = 0; ind < geneticP->individCount; ind++){
 		resetFitness(&geneticArray->at(ind));
#ifdef COEVOLUTION
 		for(int i = 0; i < geneticP->testSize; i++){
 			getValue(&geneticArray->at(ind), geneticP, input->data[testVect->value->at(i)]);
			getFitness(&geneticArray->at(ind), geneticP, input->data[testVect->value->at(i)]);			
 		}//for all tests
#else
		for(int i = 0; i < input->dataCount; i++){
			getValue(&geneticArray->at(ind), geneticP, input->data[i]);
			getFitness(&geneticArray->at(ind), geneticP, input->data[i]);
		}//for all inputs	
#endif
 	}//for all individuals

 #ifdef COEVOLUTION
 	//tidy up the test vector
 	delete(testVect->value);
 	free(testVect);
 #endif

	getParents(geneticArray, geneticP);
	createChildren(geneticArray, geneticP, functions);
}
