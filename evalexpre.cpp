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
	Function getActiveNodes - makes recursive descent on whole generation
	and fills the activeNodes vector of each genotype and counts active 
	nodes into activeNodesCount
	Takes parameters:
		@geneticArray - pointer to an array of whole generation
		@geneticP - pointer to a structure of params of CGP
***********************************************************************/
void getActiveNodes(TIndividual* geneticArray, TCgpProperties* geneticP){
	stack<int> myStack;		//recursive descent stack
	TCell tmpCell;
	int actualCell, row, col;
	vector<bool> *solved  = new vector<bool>(geneticP->cols*geneticP->rows);

	//initialize the solved vector
	for(int i = 0; i < (geneticP->rows * geneticP->cols); i++){
		solved->at(i) = false;
	}

	for(int i = 0; i < geneticP->individCount; i++){
		//for all genotypes
		for(int j = 0; j < (geneticP->rows * geneticP->cols); j++){
			//set all nodes to inactive
			geneticArray[i].activeNodes->at(j) = false;
		}

		//initialize a stack
		myStack.push(geneticArray[i].output->input1);
		solved->at(geneticArray[i].output->input1 - geneticP->inCount) = true;
		while(!myStack.empty()){
			//get the index of actual node
			actualCell = myStack.top();
			myStack.pop();
			//control for primary inputs
			if(actualCell < geneticP->inCount)
				continue;
			//index correction
			actualCell -= geneticP->inCount;
			//set actual node as active
			geneticArray[i].activeNodes->at(actualCell) = true;	
			geneticArray[i].activeNodesCount++;
			//set temp variables	
			col = (actualCell) / geneticP->rows;
			row = (actualCell) % geneticP->rows;
			tmpCell = geneticArray[i].CgpProgram[row][col];
			//push inputs of actual node
			if(tmpCell.function != CONST){	
				//const doesnt have inputs
				if(!(solved->at(tmpCell.input1))){
					myStack.push(tmpCell.input1);
					solved->at(tmpCell.input1) = 1;
				}
				if((tmpCell.function != SIN) && (tmpCell.function != COS)){	
					//sin and cos functions have just one input
					if(!(solved->at(tmpCell.input2))){
						myStack.push(tmpCell.input2);
						solved->at(tmpCell.input2) = 1;
					}
				}
			}//if not const
		}//while stack is not empty
	}//for all genotypes

	return;
}

/***********************************************************************
	Function getValue - uses one line of data input to make output value
	of each genotype in the generation
	Takes parameters:
		@geneticArray - pointer to an array of whole generation
		@geneticP - pointer to a structure of params of CGP
		@dataArray - pointer to an array of one line of input file
***********************************************************************/
void getValue(TIndividual* geneticArray, TCgpProperties* geneticP, double* dataArray){
	int row, col;
	double compIn1 = 0, compIn2 = 0;

	for(int i = 0; i < geneticP->individCount; i++){
		vector<double> *values = new vector<double>(geneticP->rows * geneticP->cols);
		//for all nodes
		for(int j = 0; j < (geneticP->rows * geneticP->cols); j++){
			row = j % geneticP->rows;
			col = j / geneticP->rows;
			//if node j is active
			if(geneticArray[i].activeNodes->at(j)){
				geneticP->countedNodes++;
				if(geneticArray[i].CgpProgram[row][col].function == CONST){
					compIn1 = geneticArray[i].CgpProgram[row][col].input1;
				}
				else {
					//first input
					if(geneticArray[i].CgpProgram[row][col].input1 < geneticP->inCount){
						//from primary input
						compIn1 = dataArray[geneticArray[i].CgpProgram[row][col].input1];					
					}
					else{
						//from previous node
						compIn1 = values->at(geneticArray[i].CgpProgram[row][col].input1 - geneticP->inCount);
					}

					//second input
					if(geneticArray[i].CgpProgram[row][col].input2 < geneticP->inCount){
						//from primary input
						compIn2 = dataArray[geneticArray[i].CgpProgram[row][col].input2];
					}
					else {
						//from previous node
						compIn2 = values->at(geneticArray[i].CgpProgram[row][col].input2 - geneticP->inCount);
					}
				}

				switch (geneticArray[i].CgpProgram[row][col].function) {
					case MUL:	values->at(j) = compIn1 * compIn2;
								break;
					case DIV:	if(compIn2 == 0){
									values->at(j) = 1;
								}
								else{
									values->at(j) = compIn1 / compIn2;
								}
								break;
					case PLUS:	values->at(j) = compIn1 + compIn2;
								break;
					case MINUS: values->at(j) = compIn1 - compIn2;
								break;
					case POW:	values->at(j) = pow(compIn1, compIn2);
								break;
					case SIN: 	values->at(j) = sin(compIn1);
								break;
					case COS:	values->at(j) = cos(compIn1);
								break;
					case CONST:	values->at(j) = geneticP->constants[(int)(compIn1)];
								break;
				} //switch

			} // if node j is active
			geneticArray[i].value = values->at(geneticArray[i].output->input1 - geneticP->inCount);
			//cerr << geneticArray[i].value << endl;
		} //for all nodes
		delete(values);
	} //for all genotypes

	return;
}

/***********************************************************************
	Function resetFitness - sets fitness and active nodes count to zero
	in all genotypes in a generation
	Takes parameters:
		@geneticArray - pointer to an array of whole generation
		@geneticP - pointer to a structure of params of CGP
***********************************************************************/
void resetFitness_ActiveNodes(TIndividual* geneticArray, TCgpProperties* geneticP){
	for(int i = 0; i < geneticP->individCount; i++){
		geneticArray[i].fitness = 0;
		geneticArray[i].activeNodesCount = 0;
	}

	return;
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
	for(int i = 0; i < geneticP->individCount; i++){
		if(abs(geneticArray[i].value - dataArray[geneticP->inCount]) < 0.5){
			//cerr << i << "(" << geneticArray[i].fitness << "): " << geneticArray[i].value << " = " << dataArray[geneticP->inCount] << endl;
			geneticArray[i].fitness++; //HIT
		}
	}//for all fenotypes

	return;
}