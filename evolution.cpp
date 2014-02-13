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
	cerr << "KROK 2: VYBER RODICU" << endl;
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

void copyGenotype(TIndividual* from, TIndividual* to, TCgpProperties* geneticP){
	//copy the cgp program
	for(int i = 0; i < geneticP->rows; i++){
		for(int j = 0; j < geneticP->cols; j++){
			if(to == NULL)
				cout << "evolution:81: to is null" << endl;
			else if(from == NULL)
				cout << "evolution:86: from is null" << endl;
			to->CgpProgram[i][j].input1 = from->CgpProgram[i][j].input1;
			to->CgpProgram[i][j].input2 = from->CgpProgram[i][j].input2;
			to->CgpProgram[i][j].function = from->CgpProgram[i][j].function;
		}
	}
	//copy output
	to->output->input1 = from->output->input1;
	//copy integer values
	to->fitness = from->fitness;
	to->value = from->value;
	to->activeNodesCount = from->activeNodesCount;

	return;
}

void changeGenes(TIndividual* child, TCgpProperties* geneticP){
	// TODO: use randR when using lpthreads

	int index = 0, change = 0, row, col;

	for(int i = 0; i < (int)(0.05 * geneticP->rows * geneticP->cols * (geneticP->compInCount + 1) + 0.5); i++){
		//which node is to change
		index = rand() % (geneticP->rows * geneticP->cols + 1);
		//which part of node is to change
		change = rand() % (geneticP->compInCount + 1);

		if(index == (geneticP->rows * geneticP->cols)){			
		//changes the output function
			if((geneticP->cols - geneticP->l_back) <= 0){
				child->output->input1 = rand() % (geneticP->cols * geneticP->rows) + geneticP->inCount;
			}
			else{
				child->output->input1 = (rand() % (geneticP->rows * geneticP->l_back)) + (geneticP->cols - geneticP->l_back) * geneticP->rows + geneticP->inCount;
			}
		}

		else{
		//changes some of the nodes
			row = index % geneticP->rows;
			col = index / geneticP->rows;
			if(((col - geneticP->l_back) < 0) && (change < 2)){
			//changes some of the inputs and l-back is not used
				if(change == 0){
				//first input
					if(child->CgpProgram[row][col].function == CONST)
						child->CgpProgram[row][col].input1 = rand() % CONSTCOUNT;
					else
						child->CgpProgram[row][col].input1 = rand() % ((index / geneticP->rows) * 
							geneticP->rows + geneticP->inCount);
				}
				else if(change == 1){
				//second input
					child->CgpProgram[row][col].input2 = rand() % ((index / geneticP->rows) * 
						geneticP->rows + geneticP->inCount);
				}
			}
			else if (change < 2){
			//changes some of the inputs and l-back is used
				if(change == 0){
				//first input
					if(child->CgpProgram[row][col].function == CONST)
						child->CgpProgram[row][col].input1 = rand() % CONSTCOUNT;
					else
						child->CgpProgram[row][col].input1 = 
							(rand() % (geneticP->rows * geneticP->l_back)) + (index / geneticP->rows - geneticP->l_back) * geneticP->rows + geneticP->inCount;
				}
				else if(change == 1){
				//second input
					child->CgpProgram[row][col].input2 = 
						(rand() % (geneticP->rows * geneticP->l_back)) + (index / geneticP->rows - geneticP->l_back) * geneticP->rows + geneticP->inCount;
				}
			}
			else{
			//changes the node function
				child->CgpProgram[row][col].function = rand() % geneticP->functionCount;
				if(child->CgpProgram[row][col].function == CONST)
					child->CgpProgram[row][col].input1 = rand() % CONSTCOUNT;
			}
		}
	}// for 5% of genes

	return;
}

void mutation(TCgpProperties* geneticP, TIndividual* geneticArray){
	//find parent
	TIndividual* parent = getParents(geneticP, geneticArray);

	//put parent on the first place
	copyGenotype(parent, &(geneticArray[0]), geneticP);

	//mutate parent into children
	for(int i = 0; i < geneticP->individCount; i++){
		copyGenotype(&(geneticArray[0]), &(geneticArray[i]), geneticP);

		//vvv tam nastane chyba... vvv
		//changeGenes(&(geneticArray[i]), geneticP);
	}
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
	getParents(geneticP, geneticArray);

	cerr << " " << geneticArray[0].fitness << endl;
	printResult(&(geneticArray[0]), geneticP);
	printReadableResult(&(geneticArray[0]), geneticP);

	cerr << "KROK 4: RESET FITNESS" << endl;
	resetFitness(geneticArray, geneticP);
	getActiveNodes(geneticArray, geneticP);  

	//get first line of input file - count of lines
	dataCount = getDataCount(data);

	cerr << "KROK 5: ZISKANI NOVE FITNESS" << endl;
	for(int i = 0; i < dataCount; i++){
		getNextData(data, dataArray, geneticP->inCount + geneticP->outCount);
		// each runs on whole geneticArray
		getValue(geneticArray, geneticP, dataArray);
		// counts the fitness value for one line (0 or 1 at each fenotype)
		getFitness(geneticArray, geneticP, dataArray); 
	}//test all data inputs

	cerr << " " << geneticArray[0].fitness << endl;
	for(int i = 0; i < geneticP->individCount; i++){
		cerr << "individ " << i << ": " << endl;
		printResult(&(geneticArray[0]), geneticP);
		printReadableResult(&(geneticArray[0]), geneticP);
	}

	free(dataArray);
	fclose(data);

	return geneticArray;
}