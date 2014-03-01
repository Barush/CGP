/******************************************************************************/
/************************ COEVOLUTION IN CGP **********************************/
/************************* BACHELORS THESIS ***********************************/
/*********************** BARBORA SKRIVANKOVA **********************************/
/********************* xskri01@stud.fit.vutbr.cz ******************************/
/******************************************************************************/

/************* MODUL USED TO EVALUATE CARTESIAN PROGRAM ***********************/
/** file name: 			evalexpre.cpp
	creation date:		10/2013
**/

#include "evalexpre.h"

/***********************************************************************
	Function getActiveNodes - makes marking of active nodes on whole generation
	and fills the activeNodes vector of each genotype and counts active 
	nodes into activeNodesCount
	Takes parameters:
		@geneticArray - pointer to an array of whole generation
		@geneticP - pointer to a structure of params of CGP
***********************************************************************/
void getActiveNodes(TIndividual** geneticArray, TCgpProperties* geneticP){
	for(int ind = 0; ind < geneticP->individCount; ind++){		
		//reset activenodes vector
		for(int i = 0; i < (geneticP->cols * geneticP->rows); i++){
			(*geneticArray)[ind].activeNodes->at(i) = false;
		}

		//mark output's input as active
		if((*geneticArray)[ind].output->input1 > geneticP->inCount){
			(*geneticArray)[ind].activeNodes->
				at((*geneticArray)[ind].output->input1 - geneticP->inCount) = true;
		}

		for(int i = (geneticP->cols - 1); i >= 0; i--){
			for(int j = 0; j < geneticP->rows; j++){
				if((*geneticArray)[ind].activeNodes->at(i*geneticP->rows + j)){	
				//if node[i][j] is active	
					if((*geneticArray)[ind].CgpProgram[j][i].function != CONST){			
					//if node is const --> continue
						if((*geneticArray)[ind].CgpProgram[j][i].input1 >= geneticP->inCount){
						//if input1 is not primary
							(*geneticArray)[ind].activeNodes->
								at((*geneticArray)[ind].CgpProgram[j][i].input1 - geneticP->inCount) = true;							
						}
						if(((*geneticArray)[ind].CgpProgram[j][i].function != SIN) &&
							((*geneticArray)[ind].CgpProgram[j][i].function != COS)){
						//if node is SIN/COS, it has one input
							if((*geneticArray)[ind].CgpProgram[j][i].input2 >= geneticP->inCount){
							//if input2 is not primary
								(*geneticArray)[ind].activeNodes->
									at((*geneticArray)[ind].CgpProgram[j][i].input2 - geneticP->inCount) = true;							
							}
						}

					}//if node is not a constant
				}//if node is active
			}//for all rows
		}//for all columns
	}//for all individuals
}

/***********************************************************************
	Function getValue - uses one line of data input to make output value
	of each genotype in the generation
	Takes parameters:
		@geneticArray - pointer to an array of whole generation
		@geneticP - pointer to a structure of params of CGP
		@dataArray - pointer to an array of one line of input file
***********************************************************************/
void getValue(TIndividual** geneticArray, TCgpProperties* geneticP, double* dataArray){
	vector<double> *values = new vector<double>(geneticP->rows * geneticP->cols);
	double op1, op2;
	int func;

	for(int ind = 0; ind < geneticP->individCount; ind++){
		for(int i = 0; i < geneticP->cols; i++){
			for(int j = 0; j < geneticP->rows; j++){
				if((*geneticArray)[ind].activeNodes->at(i*geneticP->rows + j)){
				//if node is active
					func = (*geneticArray)[ind].CgpProgram[j][i].function;

					//get inputs
					if(func == CONST){
						op1 = geneticP->constants[(*geneticArray)[ind].CgpProgram[j][i].input1];
					}
					else {
						if((*geneticArray)[ind].CgpProgram[j][i].input1 >= geneticP->inCount){
							op1 = values->at((*geneticArray)[ind].CgpProgram[j][i].input1 - geneticP->inCount);
						}
						else{
							op1 = dataArray[(*geneticArray)[ind].CgpProgram[j][i].input1];
						}	
						if((func != SIN) && (func != COS)){
						//sin and cos have one input
							if((*geneticArray)[ind].CgpProgram[j][i].input2 >= geneticP->inCount){
								op2 = values->at((*geneticArray)[ind].CgpProgram[j][i].input2 - geneticP->inCount);
							}
							else{
								op2 = dataArray[(*geneticArray)[ind].CgpProgram[j][i].input2];
							}		
						}
					}

					//count value
					switch(func){
						case MUL:	values->at(i*geneticP->rows + j) = op1 * op2;
									break;
						case DIV:	if(op2 != 0)
										values->at(i*geneticP->rows + j) = op1 / op2;
									else
										values->at(i*geneticP->rows + j) = 1;
									break;
						case PLUS:	values->at(i*geneticP->rows + j) = op1 + op2;
									break;
						case MINUS: values->at(i*geneticP->rows + j) = op1 - op2;
									break;
						case POW:	values->at(i*geneticP->rows + j) = pow(op1, op2);
									break;
						case SIN:	values->at(i*geneticP->rows + j) = sin(op1);
									break;
						case COS:	values->at(i*geneticP->rows + j) = cos(op1);
									break;
						case CONST: values->at(i*geneticP->rows + j) = op1;
									break;
					}

				}//if node is active
			}//for all rows
		}//for all columns		
		(*geneticArray)[ind].value = values->at((*geneticArray)[ind].output->input1 - geneticP->inCount);
	}//for all genotypes
}

/***********************************************************************
	Function resetFitness - sets fitness and active nodes count to zero
	in all genotypes in a generation
	Takes parameters:
		@geneticArray - pointer to an array of whole generation
		@geneticP - pointer to a structure of params of CGP
***********************************************************************/
void resetFitness_ActiveNodes(TIndividual* geneticArray, TCgpProperties* geneticP){
	for(int ind = 0; ind < geneticP->individCount; ind++){
		geneticArray[ind].fitness = 0;
		geneticArray[ind].activeNodesCount = 0;
	}
}

/***********************************************************************
	Function getFitness - compares values of all genotypes to reference value
	in dataArray - uses hit method
	Takes parameters:
		@geneticArray - pointer to an array of whole generation
		@geneticP - pointer to a structure of params of CGP
		@dataArray - one line of data input
***********************************************************************/
void getFitness(TIndividual* geneticArray, TCgpProperties* geneticP, double* dataArray){
	for(int ind = 0; ind < geneticP->individCount; ind++){
		if(abs(geneticArray[ind].value - dataArray[geneticP->inCount]) <= 1.0)
			geneticArray[ind].fitness++;
	}
}