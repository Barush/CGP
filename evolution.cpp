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

void destroyList(TIndivList* first){
	TIndivList* tmp;
	for(TIndivList* j = first; j != NULL; ){
		tmp = j->next;
		free(j);
		j = tmp;
	}	
}

TIndividual* getLowNodesParent(TIndivList* first, TCgpProperties* geneticP){
	if(first == NULL)
		cout << "evolution@26: first is null" << endl;
	TIndividual* parent = first->node;
	int min = geneticP->rows * geneticP->cols;

	for(TIndivList* i = first; i != NULL; i = i->next){
		if(i->node->activeNodesCount < min){
			parent = i->node;
			min = i->node->activeNodesCount;
		}
	}

	return parent;
}

TIndividual* getParents(TCgpProperties* geneticP, TIndividual* geneticArray){
	int max = 0;
	TIndivList* act = NULL;
	TIndivList* first = NULL;
	TIndividual* parent;

	//get list of best valued programs
	for(int i = 0; i < geneticP->individCount; i++){
		cout << "Current fitness is: " << geneticArray[i].fitness << endl;
		if(geneticArray[i].fitness > max){
			max = geneticArray[i].fitness;
			//destroy the linked list
			destroyList(first);	
			//list is always empty
			TIndivList* node;
			if((node = (TIndivList*)malloc(sizeof(TIndivList))) == NULL){
				cerr << "Chyba pri alokaci pameti" << endl;
				exit(2);
			}
			node->node = &(geneticArray[i]);	
			node->next = NULL;
			first = node;
			act = node;
		}
		else if((geneticArray[i].fitness == max) && (!geneticArray[i].wasParent)){	
			TIndivList* node = (TIndivList*)malloc(sizeof(TIndivList));
			node->node = &(geneticArray[i]);	
			node->next = NULL;
			if(act != NULL){
				act->next = node;
			}
			if(first == NULL)
				first = node;
			act = node;
		}
	}

	//get the individual with maximal fitness and lowest count of active nodes
	parent = getLowNodesParent(first, geneticP);
	if(parent == NULL)
		cout << "evolution@72: didnt get any lowNodesParent" << endl;
	//destroy the linked list
	destroyList(first);	

	return parent;
} 

void copyFenotype(TIndividual* parent, TIndividual* individ, TCgpProperties* geneticP){
	for(int i = 0; i < geneticP->rows; i++){
		for(int j = 0; j < geneticP->cols; j++){

//HERE COMES RANDOM NULL POINTERS.....WTF??

			if(individ == NULL)
				cout << "evolution:81: individ is null" << endl;
			else if(parent == NULL)
				cout << "evolution:86: Parent is null" << endl;
			individ->CgpProgram[i][j].input1 = parent->CgpProgram[i][j].input1;
			individ->CgpProgram[i][j].input2 = parent->CgpProgram[i][j].input2;
			individ->CgpProgram[i][j].function = parent->CgpProgram[i][j].function;
		}
	}
	individ->output->input1 = parent->output->input1;

	return;
}

void changeGenes(TIndividual* parent, TIndividual* individ, TCgpProperties* geneticP){
	//lepsi je mutovat po jedne slozce
	int index = 0, change = 0, row, col;

	copyFenotype(parent, individ, geneticP);

	for(int i = 0; i < (int)(0.05 * geneticP->rows * geneticP->cols * (geneticP->compInCount + 1)); i++){
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

	for(int i = 0; i < geneticP->individCount; i++){
		if( parents == &(geneticArray[i]) ){
			geneticArray[i].wasParent = true;
			cout << " " << geneticArray[i].fitness << endl;\
		}
		else{
			changeGenes(parents, &(geneticArray[i]), geneticP);
			geneticArray[i].wasParent = false;
		} 
	}

	return geneticArray;
}

TIndividual* mutation(TCgpProperties* geneticP, TIndividual* geneticArray){	
	TIndividual* parents = getParents(geneticP, geneticArray);
	if(parents == NULL)
		cout << "evolution@178: didnt get any parents..." << endl;
	geneticArray = mutateGeneration(geneticArray, parents, geneticP);

	return geneticArray;
}

TIndividual* evolutionStep(char* filename, TCgpProperties* geneticP, TIndividual* geneticArray, bool mutate){
	int dataCount = 0;
	FILE* data;
	double* dataArray;

	// open the data source file
	if((data = fopen(filename, "r")) == NULL){
		cerr << "Error in opening file: " << filename << endl;
		exit(1);
	}

	// create array of data = one line of source file
	dataArray = (double*)malloc((geneticP->inCount + 1) * sizeof(double));

	if(mutate){
		mutation(geneticP, geneticArray);
	}


	resetFitness(geneticArray, geneticP);
	getActiveNodes(geneticArray, geneticP);  
	dataCount = getDataCount(data);
	for(int i = 0; i < dataCount; i++){
		getNextData(data, dataArray, geneticP->inCount + geneticP->outCount);
		// each runs on whole geneticArray
		getValue(geneticArray, geneticP, dataArray);
		getFitness(geneticArray, geneticP, dataArray);
	}//test of all data inputs


	free(dataArray);
	fclose(data);

	return geneticArray;
}