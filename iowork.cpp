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
#define INCOUNT 1
#define OUTCOUNT 1
#define COMPINCOUNT 2
#define FUNCTIONCOUNT 3
#define ROW 10
#define COL 6
#define L_BACK 10
#define GENER 3

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
	cout << "Fitness: " << result->fitness << endl;
	cout << "====================================================================" << endl;

	return;
}

int getDataCount(ifstream &data){
	int count;
	string line;

	getline(data, line);
	count = atoi(line.c_str());

	return count;
}

void getNextData(ifstream &data, double* dataArray, int ioCount){
	//double num;
	string line;

	getline(data, line);
	char *cline=new char[line.size()+1];
	cline[line.size()]=0;
	memcpy(cline,line.c_str(),line.size());

	//for(int i = 0; i < ioCount; i++){
	int i = 0;
		sscanf(line.c_str(), "%lf %lf ", &dataArray[i], &dataArray[i+1]);
		//more work here, now just for one input
	//}

	return;
}