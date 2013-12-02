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

void printVal(stack<int> s){
	int x = 0;
	cout << "Stav zasobniku: " << endl;
	for(unsigned i = 0; i < s.size(); i++){
		x = s.top();
		cout << i << " : " << x << endl;
		s.pop();
	}
	return;
}

void getActiveNodes(TIndividual* geneticArray, TCgpProperties* geneticP){
	stack<int> myStack;
	TCell tmpCell;
	int actualCell, row, col;
	bool solved[geneticP->cols*geneticP->rows];

	for(int i = 0; i < (geneticP->rows * geneticP->cols); i++){
		solved[i] = 0;
	}

	for(int i = 0; i < geneticP->individCount; i++){
		for(int j = 0; j < (geneticP->rows * geneticP->cols); j++){
			geneticArray[i].activeNodes->at(j) = false;
		}
		myStack.push(geneticArray[i].output->input1);
		solved[geneticArray[i].output->input1] = 1;
		//cout << "evalexpre@27: got into while" << endl;
		while(!myStack.empty()){
			//printVal(myStack);
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
			geneticArray[i].activeNodesCount++;
			//set temp variables	
			col = (actualCell) / geneticP->rows;
			row = (actualCell) % geneticP->rows;
			tmpCell = geneticArray[i].CgpProgram[row][col];
			//push inputs of actual component
			if(tmpCell.function != CONST){
				if(!solved[tmpCell.input1]){
					myStack.push(tmpCell.input1);
					solved[tmpCell.input1] = 1;
				}
				if((tmpCell.function != SIN) && (tmpCell.function != COS)){
					if(!solved[tmpCell.input2]){
						myStack.push(tmpCell.input2);
						solved[tmpCell.input2] = 1;
					}
				}
			}
		}
		//cout << "evalexpre@51: got out of while" << endl;
	}

	return;
}

void getValue(TIndividual* geneticArray, TCgpProperties* geneticP, double* dataArray){
	int row, col;
	double compIn1 = 0, compIn2 = 0;

	for(int i = 0; i < geneticP->individCount; i++){

		vector<double> *values = new vector<double>(geneticP->rows * geneticP->cols);
		for(int j = 0; j < (geneticP->rows * geneticP->cols); j++){
			row = j % geneticP->rows;
			col = j / geneticP->rows;
			if(geneticArray[i].activeNodes->at(j)){
				geneticP->countedNodes++;
				if(geneticArray[i].CgpProgram[row][col].function == CONST){
					compIn1 = geneticArray[i].CgpProgram[row][col].input1;
				}
				else {
					if(geneticArray[i].CgpProgram[row][col].input1 < geneticP->inCount){
						for(int k = 0; k < geneticP->inCount; k++){
							if(geneticArray[i].CgpProgram[row][col].input1 == k)
								compIn1 = dataArray[k];
						}					}
					else{
						compIn1 = values->at(geneticArray[i].CgpProgram[row][col].input1 - geneticP->inCount);
					}

					if(geneticArray[i].CgpProgram[row][col].input2 < geneticP->inCount){
						for(int k = 0; k < geneticP->inCount; k++){
							if(geneticArray[i].CgpProgram[row][col].input2 == k)
								compIn2 = dataArray[k];
						}
					}
					else {
						compIn2 = values->at(geneticArray[i].CgpProgram[row][col].input2 - geneticP->inCount);
					}
				}

				switch (geneticArray[i].CgpProgram[row][col].function) {
					case MUL:	values->at(j) = compIn1 * compIn2;
								//cout << compIn1 << "*" << compIn2 << "=" << values->at(j) << endl;
								break;
					case DIV:	if(compIn2 == 0){
									values->at(j) = 1;
								}
								else{
									values->at(j) = compIn1 / compIn2;
								}
								break;
					case AND:	values->at(j) = (int)compIn1 & (int)compIn2;
								//cout << compIn1 << "&" << compIn2 << "=" << values->at(j) << endl;
								break;
					case OR:	values->at(j) = (int)compIn1 | (int)compIn2;
								//cout << compIn1 << "|" << compIn2 << "=" << values->at(j) << endl;
								break;
					case PLUS:	values->at(j) = compIn1 + compIn2;
								//cout << compIn1 << "+" << compIn2 << "=" << values->at(j) << endl;
								break;
					case MINUS: values->at(j) = compIn1 - compIn2;
								//cout << compIn1 << "-" << compIn2 << "=" << values->at(j) << endl;
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
		} //for all nodes
		delete(values);
	} //for all fenotypes

	return;
}

void resetFitness(TIndividual* geneticArray, TCgpProperties* geneticP){
	for(int i = 0; i < geneticP->individCount; i++){
		geneticArray[i].fitness = 0;
		geneticArray[i].activeNodesCount = 0;
	}

	return;
}


void getFitness(TIndividual* geneticArray, TCgpProperties* geneticP, double* dataArray){

	for(int i = 0; i < geneticP->individCount; i++){
		if(abs(geneticArray[i].value - dataArray[geneticP->inCount]) < 0.1){
			geneticArray[i].fitness++; //HIT
		//	cout << "Fitness of fenotype " << i << " increased." << endl;
		}
	}//for all fenotypes

	return;
}