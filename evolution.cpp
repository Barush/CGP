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

TIndividual* getParents(TCgpProperties* geneticP, TIndividual* geneticArray){
	int max = geneticArray[0].fitness;
	TIndividual* parent = &(geneticArray[0]);

	cerr << max;

	//for all fenotypes except parent (first)
	for(int i = 1; i < geneticP->individCount; i++){
		cerr << " " << geneticArray[i].fitness;

		if(geneticArray[i].fitness == max){
			// max is the parent of last generation
			if(parent == &(geneticArray[0])){
				parent = &(geneticArray[i]);
			}
			else{
				//new parent has less active nodes and same fitness
				if(geneticArray[i].activeNodesCount < parent->activeNodesCount){
					parent = &(geneticArray[i]);
				}
			} 
		}

		else if(geneticArray[i].fitness > max){
			parent = &(geneticArray[i]);
			max = geneticArray[i].fitness;
		}
	}

	cerr << "->" << parent->fitness << endl;
	return parent;
} 

void copyFenotype(TIndividual* parent, TIndividual* individ, TCgpProperties* geneticP){
	//copy the cgp program
	for(int i = 0; i < geneticP->rows; i++){
		for(int j = 0; j < geneticP->cols; j++){
			if(individ == NULL)
				cout << "evolution:81: individ is null" << endl;
			else if(parent == NULL)
				cout << "evolution:86: Parent is null" << endl;
			individ->CgpProgram[i][j].input1 = parent->CgpProgram[i][j].input1;
			individ->CgpProgram[i][j].input2 = parent->CgpProgram[i][j].input2;
			individ->CgpProgram[i][j].function = parent->CgpProgram[i][j].function;
		}
	}
	//copy output
	individ->output->input1 = parent->output->input1;
	//copy integer values
	individ->fitness = parent->fitness;
	individ->value = parent->value;
	individ->activeNodesCount = parent->activeNodesCount;

	return;
}

void changeGenes(TIndividual* parent, TIndividual* individ, TCgpProperties* geneticP){
	//lepsi je mutovat po jedne slozce
	int index = 0, change = 0, row, col;

	copyFenotype(parent, individ, geneticP);

	for(int i = 0; i < (int)(0.05 * geneticP->rows * geneticP->cols * (geneticP->compInCount + 1) + 0.5); i++){
		index = rand() % (geneticP->rows * geneticP->cols + 1);
		change = rand() % (geneticP->compInCount + 1);

		if(index == (geneticP->rows * geneticP->cols)){			
		//changes the output function
			if((geneticP->cols - geneticP->l_back) <= 0){
				individ->output->input1 = rand() % (geneticP->cols * geneticP->rows) + geneticP->inCount;
			}
			else{
				individ->output->input1 = (rand() % (geneticP->rows * geneticP->l_back)) + (geneticP->cols - geneticP->l_back) * geneticP->rows + geneticP->inCount;
			}
		}

		else{
		//changes some of the gens
			row = index % geneticP->rows;
			col = index / geneticP->rows;
			if(((col - geneticP->l_back) < 0) && (change < 2)){
				if(change == 0){
					if(individ->CgpProgram[row][col].function == CONST)
						individ->CgpProgram[row][col].input1 = rand() % CONSTCOUNT;
					else
						individ->CgpProgram[row][col].input1 = rand() % ((index / geneticP->rows) * 
							geneticP->rows + geneticP->inCount);
				}
				else if(change == 1){
					individ->CgpProgram[row][col].input2 = rand() % ((index / geneticP->rows) * 
						geneticP->rows + geneticP->inCount);
				}
			}
			else if (change < 2){
				if(change == 0){
					if(individ->CgpProgram[row][col].function == CONST)
						individ->CgpProgram[row][col].input1 = rand() % CONSTCOUNT;
					else
						individ->CgpProgram[row][col].input1 = 
							(rand() % (geneticP->rows * geneticP->l_back)) + (index / geneticP->rows - geneticP->l_back) * geneticP->rows + geneticP->inCount;
				}
				else if(change == 1){
					individ->CgpProgram[row][col].input2 = 
						(rand() % (geneticP->rows * geneticP->l_back)) + (index / geneticP->rows - geneticP->l_back) * geneticP->rows + geneticP->inCount;
				}
			}
			else{
				individ->CgpProgram[row][col].function = rand() % geneticP->functionCount;
				if(individ->CgpProgram[row][col].function == CONST)
					individ->CgpProgram[row][col].input1 = rand() % CONSTCOUNT;
			}
		}
	}// for 5% of genes

	return;
}

TIndividual* mutateGeneration(TIndividual* geneticArray, TIndividual* parents, TCgpProperties* geneticP){
	//parent is always first in the array
	cerr << parents->fitness;
	copyFenotype(parents, &(geneticArray[0]), geneticP);
	cerr << " " << geneticArray[0].fitness;

	//others in the array are mutants
	for(int i = 1; i < geneticP->individCount; i++){
		changeGenes(&(geneticArray[0]), &(geneticArray[i]), geneticP);
	}

	return geneticArray;
}

TIndividual* mutation(TCgpProperties* geneticP, TIndividual* geneticArray){	
	TIndividual* parents = getParents(geneticP, geneticArray);
	if(parents == NULL)
		cout << "evolution@178: didnt get any parents..." << endl;
	geneticArray = mutateGeneration(geneticArray, parents, geneticP);
	cerr << " " << geneticArray[0].fitness;

	return geneticArray;
}

TIndividual* evolutionStep(char* filename, TCgpProperties* geneticP, TIndividual* geneticArray, bool mutate){
	int dataCount = 0;	//input + output count
	FILE* data;			//input file
	double* dataArray;	//one line of file

	// open the data source file
	if((data = fopen(filename, "r")) == NULL){
		cerr << "Error in opening file: " << filename << endl;
		exit(1);
	}

	// create array of data = one line of input file
	dataArray = (double*)malloc((geneticP->inCount + geneticP->outCount) * sizeof(double));

	if(mutate){
		mutation(geneticP, geneticArray);
	}

	cerr << " " << geneticArray[0].fitness << endl;
	printResult(&(geneticArray[0]), geneticP);
	printReadableResult(&(geneticArray[0]), geneticP);

	resetFitness(geneticArray, geneticP);
	getActiveNodes(geneticArray, geneticP);  

	//get first line of input file - count of lines
	dataCount = getDataCount(data);

	for(int i = 0; i < dataCount; i++){
		getNextData(data, dataArray, geneticP->inCount + geneticP->outCount);
		// each runs on whole geneticArray
		getValue(geneticArray, geneticP, dataArray);
		// counts the fitness value for one line (0 or 1 at each fenotype)
		getFitness(geneticArray, geneticP, dataArray); 
	}//test all data inputs

	cerr << " " << geneticArray[0].fitness << endl;
	printResult(&(geneticArray[0]), geneticP);
	printReadableResult(&(geneticArray[0]), geneticP);

	free(dataArray);
	fclose(data);

	return geneticArray;
}