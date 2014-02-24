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

void getParents(TIndividual** geneticArray, TCgpProperties* geneticP){
	int max = -1;
	TIndividual* parent;

	for(int i = 0; i < geneticP->individCount; i++){
		if((*geneticArray)[i].fitness > max){
			max = (*geneticArray)[i].fitness;
			parent = &((*geneticArray)[i]);
		}
		else if((*geneticArray)[i].fitness == max){
			if((*geneticArray)[i].activeNodesCount < parent->activeNodesCount){
				parent = &((*geneticArray)[i]);
			}
		}
	}

	copyGenotype(parent, &(*geneticArray)[0], geneticP);
}

void evolutionStep(TData* input, TCgpProperties* geneticP, TIndividual** geneticArray){

	resetFitness_ActiveNodes(*geneticArray, geneticP);
	getActiveNodes(*geneticArray, geneticP);

	for(int i = 0; i < input->dataCount; i++){
		getValue(*geneticArray, geneticP, input->data[i]);
		getFitness(*geneticArray, geneticP, input->data[i]);
	}

	//get parents
	getParents(geneticArray, geneticP);

	//create new generation
}