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
#define INCOUNT 2
#define OUTCOUNT 1
#define COMPINCOUNT 2
#define FUNCTIONCOUNT 6
#define ROW 3
#define COL 3
#define L_BACK 25
#define GENER 10

void printUsage(){
	cout << "COEVOLUTION IN CGP" << endl;
	cout << "BACHELORS THESIS" << endl;
	cout << "BARBORA SKRIVANKOVA " << endl;
	cout << "xskri01@stud.fit.vutbr.cz" << endl;

	cout << "Usage: " << endl;
	cout << "./cocgp testfile [-r rows -c cols -l L-back -g generation]" << endl << endl;
	cout << "\t testfile looks like: " << endl;
	cout << "\t\t number_of_test_points" << endl;
	cout << "\t\t in1 in2 in3 .. inN out" << endl;
	cout << "\t rows - sets number of rows in cgp program" << endl;
	cout << "\t cols - sets number of cols in cgp program" << endl;
	cout << "\t L-back - sets L-backindividuals in each generation" << endl;
	return;
}

TCgpProperties* getParams(char** argv, int argc){
	TCgpProperties* params = (TCgpProperties*)malloc(sizeof(struct cgpProperties));

	// set defaults
	params->inCount = INCOUNT;
	params->outCount = OUTCOUNT;
	params->compInCount = COMPINCOUNT;
	params->functionCount = FUNCTIONCOUNT;
	params->rows = ROW;
	params->cols = COL;
	params->l_back = L_BACK;
	params-> individCount = GENER;
	params->countedNodes = 0;

	// set custom changes
	for(int i = 2; i < argc; i++){
		if(!strcmp(argv[i], "-r")){
			i++;
			params->rows = atoi(argv[i]);
		}
		else if(!strcmp(argv[i], "-c")){
			i++;
			params->cols = atoi(argv[i]);
		}
		else if(!strcmp(argv[i], "-l")){
			i++;
			int lb = atoi(argv[i]);
			if(lb < 1){
				params->l_back = 1;
			}
			else
				params->l_back = lb;
		}
		else if(!strcmp(argv[i], "-g")){
			i++;
			params->individCount = atoi(argv[i]);
		}
	}

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

int getDataCount(FILE* data){
	int count, i = 0;
	char line[20], c;

	
  	while((c = fgetc(data)) != '\n'){
		line[i] = c;
		i++;
	}
	count = atoi(line);

	return count;
}

void getNextData(FILE* data, double* dataArray, int ioCount){
	int i = 0, j = 0;
	char num[20], c;

	while((c = fgetc(data)) != '\n'){
		if(c == ' '){
			if(j < ioCount){
				dataArray[j] = strtod(num, NULL);
				memset(num, 0, 20);
				j++;
				i = 0;	
			}
			else{
				cerr << "Wrong input file!!" << endl;
				exit(1);
			}
		}
		else{
			num[i] = c;
			i++;
		}
	}

	// store the last number of a line - 'while' ended with endl
	if(j < ioCount){
		dataArray[j] = strtod(num, NULL);
	}
	else{
		cerr << "Wrong input file!!" << endl;
		exit(1);
	}

	return;
}