/******************************************************************************/
/************************ COEVOLUTION IN CGP **********************************/
/************************* BACHELORS THESIS ***********************************/
/*********************** BARBORA SKRIVANKOVA **********************************/
/********************* xskri01@stud.fit.vutbr.cz ******************************/
/******************************************************************************/

/*********************** MODUL FOR I/O OPERATIONS *****************************/
/** file name: 			iowork.cpp
	creation date:		10/2013
**/

#include "iowork.h"


/***************** TEMPORARILY DEFINES ********************/
#define INCOUNT 5
#define OUTCOUNT 1
#define COMPINCOUNT 2
#define FUNCTIONCOUNT 3
#define ROW 5
#define COL 6
#define L_BACK 10
#define GENER 1

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