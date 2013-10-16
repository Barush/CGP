/***********  TODO ***********************

	- po 13.00

	- PLAN MODULES

	- eureqa == soft na sym. regresi pro win s GUI
	- make the syntactic tree - array --> TEST!!!
	- get the inputs from file
	- fitness - score
	- choose parent
	- mutation (5% of gens)
	- function enum... - dynamic array of structures?
	- l_back > 0


*****************************************/


#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <stack>

#define INCOUNT 3
#define OUTCOUNT 1
#define COMPINCOUNT 2
#define FUNCTIONCOUNT 3
#define ROW 8
#define COL 5
#define L_BACK 10
#define GENER 1

using namespace std;

/******************************************************************************/
/********************** TYPEDEFS OF STRUCTURES ********************************/
/******************************************************************************/

//Possible operations in CGP matrix, will be modificated from program input
typedef enum function{
	MUL = 0,
	PLUS,
	MINUS
}TFunction;

//one cell of a CGP matrix
typedef struct cell {
	int input1;
	int input2;
	int function;
}TCell;

typedef struct cgpProperties {
	int inCount;		//count of main inputs
	int outCount;		//count of main outputs
	int compInCount;	//count of component inputs
	int functionCount;	//count of functions
	int rows;			//count of rows in the matrix
	int cols;			//count of columns in the matrix
	int l_back; 		//l-back param of the matrix
	int individCount;	//count of individuals in the generation
}TCgpProperties;

//whole CGP struct
typedef struct individual{
	TCell** CgpProgram;
	TCell* output;
	vector<bool>* activeNodes;
	int value;
	int fitness;
}TIndividual;

/******************************************************************************/
/******************* FUNCTIONS FOR GENERATION CREATION ************************/
/******************************************************************************/

TCgpProperties* getParams(){
	TCgpProperties* params = (TCgpProperties*)malloc(sizeof(struct cgpProperties));

	params->inCount = INCOUNT;
	params->outCount = OUTCOUNT;
	params->compInCount = COMPINCOUNT;
	params->functionCount = FUNCTIONCOUNT;
	params->rows = ROW;
	params->cols = COL;
	params->l_back = L_BACK;
	params-> individCount = GENER;

	return params;
}

//alocation of a single subject of CGP
TCell** alocateProgram(int row, int col){
	TCell** subject = (TCell**)malloc(row * sizeof(TCell*));

	for(int i = 0; i < row; i++){
		subject[i] = (TCell*)malloc(col * sizeof(TCell));
	}

	return subject;
}

//fill in the CGP matrix
TIndividual* createIndividual(TCgpProperties* geneticP, TIndividual *subject){
	subject->CgpProgram = alocateProgram(geneticP->rows, geneticP->cols);
	subject->output = (TCell*)malloc(sizeof(struct cell)); 
	subject->fitness = 0;

	for(int i = 0; i < geneticP->rows; i++){
		for(int j = 0; j < geneticP->cols; j++){
			int index = j * geneticP->rows + i;		//in which cell we are
			if((index / geneticP->rows - geneticP->l_back) < 0){
				subject->CgpProgram[i][j].input1 = rand() % ((index / geneticP->rows) * 
					geneticP->rows + geneticP->inCount);
				subject->CgpProgram[i][j].input2 = rand() % ((index / geneticP->rows) * 
					geneticP->rows + geneticP->inCount);
			}
			else {
				subject->CgpProgram[i][j].input1 = 
					(rand() % (geneticP->rows * geneticP->l_back)) + (index / geneticP->rows - geneticP->l_back) * geneticP->rows + geneticP->inCount;
				subject->CgpProgram[i][j].input2 = 
					(rand() % (geneticP->rows * geneticP->l_back)) + (index / geneticP->rows - geneticP->l_back) * geneticP->rows + geneticP->inCount;
			}
			subject->CgpProgram[i][j].function = rand() % geneticP->functionCount;
		} //end of one row
	} // end of whole matrix
	if((geneticP->cols - geneticP->l_back) <= 0){
		subject->output->input1 = rand() % (geneticP->cols * geneticP->rows) + geneticP->inCount;
	}
	else{
		subject->output->input1 = (rand() % (geneticP->rows * geneticP->l_back)) + (geneticP->cols - geneticP->l_back) * geneticP->rows + geneticP->inCount;
	}

	return subject;
}

//create an array of individuals as a generation
TIndividual* createGeneration(TCgpProperties* geneticP){
	TIndividual* generation = (TIndividual*)malloc(geneticP->individCount * sizeof(struct individual));

	for(int i = 0; i < geneticP->individCount ; i++){
		generation[i] = *(createIndividual(geneticP, &(generation[i])));
	}

	return generation;
}

/******************************************************************************/
/******************* FUNCTIONS FOR WORK WITH EVOLUTION ************************/
/******************************************************************************/

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


/******************************************************************************/
/************************ HANDLING OUTPUTS FUNCTIONS **************************/
/******************************************************************************/

void printResult(TIndividual* result, TCgpProperties* geneticP){
	cout << "====================================================================" << endl;
	for(int i = 0; i < geneticP->rows; i++){
		for(int j = 0; j < geneticP->cols; j++){
			cout << (*result).CgpProgram[i][j].input1 << " " << (*result).CgpProgram[i][j].input2 << " [" << (*result).CgpProgram[i][j].function << "]   ";
			fflush(stdout);
		}
		cout << endl;
	}
	cout << (*result).output->input1 << " [Y]" << endl;
	cout << "Active nodes: ";
	for(int i = 0; i < (geneticP->rows * geneticP->cols); i++){
		if(result->activeNodes->at(i))
			cout << i  << ", ";
	}
	cout << endl;
	cout << "Value: " << result->value << endl;
	cout << "====================================================================" << endl;

	return;
}

void destroyGeneration(TIndividual** geneticArray, TCgpProperties* geneticP){
	for(int i = 0; i < geneticP->individCount; i++){
		for(int j = 0; j < geneticP->rows; j++){
			free((*geneticArray)[i].CgpProgram[j]);
		}
		free((*geneticArray)[i].CgpProgram);
		free((*geneticArray)[i].output);
		delete((*geneticArray)[i].activeNodes);
	}
	free(*geneticArray);
	return;
}

int main(int argc, char** argv){
	TIndividual* geneticArray;
	TCgpProperties* geneticParams;

	srand(time(NULL)); // initiate random generator
	geneticParams = getParams();
	geneticArray = createGeneration(geneticParams);

	getActiveNodes(geneticArray, geneticParams);
	getValue(geneticArray, geneticParams, 10, 20, 30, 50);
	for(int i = 0; i < geneticParams->individCount; i++){
		cout << "Individual no. " << i+1 << ":" << endl;
		printResult(&geneticArray[i], geneticParams);
	}

	destroyGeneration(&geneticArray, geneticParams);
	free(geneticParams);

	return EXIT_SUCCESS;
} 