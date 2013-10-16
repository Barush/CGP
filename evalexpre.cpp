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


void getActiveNodes(TIndividual* geneticArray, TCgpProperties* geneticP){
	stack<int> myStack;
	TCell tmpCell;
	int actualCell, row, col;

	for(int i = 0; i < geneticP->individCount; i++){
		vector<bool> *vect = new vector<bool>(geneticP->rows * geneticP->cols);	
		geneticArray[i].activeNodes = vect;
		myStack.push(geneticArray[i].output->input1);
		while(!myStack.empty()){
			//get the index of actual component
			actualCell = myStack.top();
			myStack.pop();
			//control for primary inputs
			if(actualCell < geneticP->inCount)
				continue;
			//index correction for an array and coordinates
			actualCell -= geneticP->inCount;
			//set actual components bit for true
			geneticArray[i].activeNodes->at(actualCell) = true;	
			//set temp variables	
			col = (actualCell) / geneticP->rows;
			row = (actualCell) % geneticP->rows;
			tmpCell = geneticArray[i].CgpProgram[row][col];
			//push inputs of actual component
			//if(!geneticArray[i].activeNodes[tmpCell.input1 - geneticP->inCount])
				myStack.push(tmpCell.input1);
			//if(!geneticArray[i].activeNodes[tmpCell.input2 - geneticP->inCount])
				myStack.push(tmpCell.input2);

		}
	}

	return;
}

void getValue(TIndividual* geneticArray, TCgpProperties* geneticP, int in1, int in2, int in3, int in4){
	int row, col, compIn1, compIn2;

	for(int i = 0; i < geneticP->individCount; i++){

		vector<int> *values = new vector<int>(geneticP->rows * geneticP->cols);
		for(int j = 0; j < (geneticP->rows * geneticP->cols); j++){

			row = j % geneticP->rows;
			col = j / geneticP->cols;
			if(geneticArray[i].activeNodes->at(j)){

				if(geneticArray[i].CgpProgram[row][col].input1 < geneticP->inCount){
					// REWRITE --> FOR
					if(geneticArray[i].CgpProgram[row][col].input1 == 0)
						compIn1 = in1;
					else if(geneticArray[i].CgpProgram[row][col].input1 == 1)
						compIn1 = in2;
					else if(geneticArray[i].CgpProgram[row][col].input1 == 2)
						compIn1 = in3;
					else if(geneticArray[i].CgpProgram[row][col].input1 == 3)
						compIn1 = in4;
				}
				else
					compIn1 = values->at(geneticArray[i].CgpProgram[row][col].input1 - geneticP->inCount);

				if(geneticArray[i].CgpProgram[row][col].input2 < geneticP->inCount){
					if(geneticArray[i].CgpProgram[row][col].input2 == 0)
						compIn2 = in1;
					else if(geneticArray[i].CgpProgram[row][col].input2 == 1)
						compIn2 = in2;
					else if(geneticArray[i].CgpProgram[row][col].input2 == 2)
						compIn2 = in3;
					else if(geneticArray[i].CgpProgram[row][col].input2 == 3)
						compIn2 = in4;
				}
				else
					compIn2 = values->at(geneticArray[i].CgpProgram[row][col].input2 - geneticP->inCount);

				switch (geneticArray[i].CgpProgram[row][col].function) {
					case MUL:	values->at(j) = compIn1 * compIn2;
								cout << compIn1 << " * " << compIn2 << " = " << values->at(j) << endl;
								break;
					case PLUS:	values->at(j) = compIn1 + compIn2;
								cout << compIn1 << " + " << compIn2 << " = " << values->at(j) << endl;
								break;
					case MINUS: values->at(j) = compIn1 - compIn2;
								cout << compIn1 << " - " << compIn2 << " = " << values->at(j) << endl;
								break;
					default: 	cout << "Error function in counting value..." << endl;
				} //switch

			} // if node j is active
			geneticArray[i].value = values->at(geneticArray[i].output->input1 - geneticP->inCount);
		} //for all nodes
		delete(values);
	} //for all fenotypes

	return;
}