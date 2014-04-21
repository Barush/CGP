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
void getActiveNodes(vector<TIndividual>* geneticArray, TCgpProperties* geneticP){
	for(int ind = 0; ind < geneticP->individCount; ind++){
		//reset activenodes count
		geneticArray->at(ind).activeNodesCount = 0;		
		//reset activenodes vector
		for(int i = 0; i < (geneticP->cols * geneticP->rows); i++){
			geneticArray->at(ind).activeNodes->at(i) = false;
		}

		//mark output's input as active
		if(geneticArray->at(ind).output.input1 > geneticP->inCount){
			geneticArray->at(ind).activeNodes->
				at(geneticArray->at(ind).output.input1 - geneticP->inCount) = true;
			geneticArray->at(ind).activeNodesCount++;
		}

		for(int i = (geneticP->cols - 1); i >= 0; i--){
			for(int j = 0; j < geneticP->rows; j++){
				if(geneticArray->at(ind).activeNodes->at(i*geneticP->rows + j)){	
				//if node[i][j] is active	
					if(geneticArray->at(ind).CgpProgram->at(j)[i].function != CONST){			
					//if node is const --> continue
						if(geneticArray->at(ind).CgpProgram->at(j)[i].input1 >= geneticP->inCount){
						//if input1 is not primary
							geneticArray->at(ind).activeNodes->
								at(geneticArray->at(ind).CgpProgram->at(j)[i].input1 - geneticP->inCount) = true;	
							geneticArray->at(ind).activeNodesCount++;						
						}
						if((geneticArray->at(ind).CgpProgram->at(j)[i].function != SIN) &&
							(geneticArray->at(ind).CgpProgram->at(j)[i].function != COS) &&
							(geneticArray->at(ind).CgpProgram->at(j)[i].function != LOG) &&
							(geneticArray->at(ind).CgpProgram->at(j)[i].function != ABS) &&
							(geneticArray->at(ind).CgpProgram->at(j)[i].function != EXP)){
						//if node is SIN/COS/LOG/ABS/EXP, it has one input
							if(geneticArray->at(ind).CgpProgram->at(j)[i].input2 >= geneticP->inCount){
							//if input2 is not primary
								geneticArray->at(ind).activeNodes->
									at(geneticArray->at(ind).CgpProgram->at(j)[i].input2 - geneticP->inCount) = true;
								geneticArray->at(ind).activeNodesCount++;							
							}
						}

					}//if node is not a constant
				}//if node is active
			}//for all rows
		}//for all columns
	}//for all individuals
}

double countVal(int func, double op1, double op2){
	double value;

	//count value
	switch(func){
		case MUL:	value = op1 * op2;
					break;
		case DIV:	if(op2 != 0)
						value = op1 / op2;
					else
						value = 1;
					break;
		case PLUS:	value = op1 + op2;
					break;
		case MINUS: value = op1 - op2;
					break;
		case POW:	value = pow(op1, op2);
					break;
		case SIN:	value = sin(op1);
					break;
		case COS:	value = cos(op1);
					break;
		case LOG:	value = log(op1);
					break;
		case ABS:	value = (op1 < 0)?(-op1):(op1);
					break;
		case CONST: value = op1;
					break;
		case EXP: 	value = exp(op1);
					break;
	}

	return value;
}

/***********************************************************************
	Function getValue - uses one line of data input to make output value
	of one genotype
	Takes parameters:
		@geneticArray - pointer to an array of whole generation
		@geneticP - pointer to a structure of params of CGP
		@dataArray - pointer to an array of one line of input file
***********************************************************************/
void getValue(TIndividual* genotype, TCgpProperties* geneticP, double* dataArray){
	vector<double> *values = new vector<double>(geneticP->rows * geneticP->cols);
	double op1 = 0.0, op2 = 0.0;
	int func;

	for(int i = 0; i < geneticP->cols; i++){
		for(int j = 0; j < geneticP->rows; j++){
			if(genotype->activeNodes->at(i*geneticP->rows + j)){
			//if node is active

				//get function
				func = genotype->CgpProgram->at(j)[i].function;

				//get inputs
				if(func == CONST){
				//const has special input
					op1 = geneticP->constants[genotype->CgpProgram->at(j)[i].input1];
				}
				else {
					if(genotype->CgpProgram->at(j)[i].input1 >= geneticP->inCount){
					//other node output
						op1 = values->at(genotype->CgpProgram->at(j)[i].input1 - geneticP->inCount);
					}
					else{
					//primary input
						op1 = dataArray[genotype->CgpProgram->at(j)[i].input1];
					}	
					if((func != SIN) && (func != COS) && (func != LOG) && (func != ABS) && (func != EXP)){
					//sin, cos, log, abs, exp have one input
						if(genotype->CgpProgram->at(j)[i].input2 >= geneticP->inCount){						
							op2 = values->at(genotype->CgpProgram->at(j)[i].input2 - geneticP->inCount);
						}//other node output
						else{						
							op2 = dataArray[genotype->CgpProgram->at(j)[i].input2];
						}//primary input		
					}//not sin, cos, log, abs, exp
				}//not const

				values->at(i*geneticP->rows + j) = countVal(func, op1, op2);
			}//if node is active
		}//for all rows
	}//for all columns	
	genotype->value = values->at(genotype->output.input1 - geneticP->inCount);
	geneticP->countedNodes++;

	delete(values);
}

/***********************************************************************
	Function resetFitness - sets fitness and active nodes count to zero
	in all genotypes in a generation
	Takes parameters:
		@geneticArray - pointer to an array of whole generation
		@geneticP - pointer to a structure of params of CGP
***********************************************************************/
void resetFitness(TIndividual* genotype){
		genotype->fitness = 0;
}

/***********************************************************************
	Function getFitness - compares values of all genotypes to reference value
	in dataArray - uses hit method
	Takes parameters:
		@geneticArray - pointer to an array of whole generation
		@geneticP - pointer to a structure of params of CGP
		@dataArray - one line of data input
***********************************************************************/
void getFitness(TIndividual* genotype, TCgpProperties* geneticP, double* dataArray){
		if(abs(genotype->value - dataArray[geneticP->inCount]) <= geneticP->fitToleration)
			genotype->fitness++;
}
