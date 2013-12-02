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
#define FUNCTIONCOUNT 10
#define ROW 16
#define COL 10
#define L_BACK 20
#define GENER 5

void printUsage(){
	cout << "COEVOLUTION IN CGP" << endl;
	cout << "BACHELORS THESIS" << endl;
	cout << "BARBORA SKRIVANKOVA " << endl;
	cout << "xskri01@stud.fit.vutbr.cz" << endl;

	cout << "Usage: " << endl;
	cout << "./cocgp testfile [-r rows -c cols -l L-back -g generation]" << endl << endl;
	cout << "\t testfile looks like: " << endl;
	cout << "\t\t number_of_test_vectors" << endl;
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

	params->constants[PI] = 3.141592;
	params->constants[EULER] = 2.718281;
	params->constants[ONE] = 1;
	params->constants[ZERO] = 0;

	return params;
}

char* intToStr(int val){
	//conversion int to string
	stringstream intStr;
	intStr << val;
	string tmp = intStr.str();
	tmp = "x" + tmp;
	char* result = (char*)malloc(sizeof(tmp.length()));
	strcpy(result, tmp.c_str());

	return result;
}

char* getPrintable(int ind){
	char* str = (char*)malloc(sizeof(char) * 10);

	switch(ind){
		case 0: str = strdup("3.141592");
				break;
		case 1: str = strdup("2.718281");
				break;
		case 2: str = strdup("1");
				break;
		case 3: str = strdup("0");
				break;
	}

	return str;
}

void expandNode(TStackItem** tmp, TIndividual* result, TStackItem** stack, TCgpProperties* geneticP){
	int row, col;

	//get value
	row = ((*tmp)->value - geneticP->inCount) % geneticP->rows;
	col = ((*tmp)->value - geneticP->inCount) / geneticP->rows;

	//insert (
	TStackItem* lBracket = (TStackItem*)malloc(sizeof(struct stackItem));
	lBracket->isTerm = TERM;
	lBracket->printable = strdup("(");

	//get first operand - NONTERM?
	TStackItem* op1 = (TStackItem*)malloc(sizeof(struct stackItem));
	if(result->CgpProgram[row][col].input1 < geneticP->inCount){
		op1->isTerm = TERM;
		op1->printable = strdup(intToStr(result->CgpProgram[row][col].input1)); 
	}
	else {
		op1->isTerm = NONTERM;
		op1->printable = strdup("nonterm");
	}
	op1->value = result->CgpProgram[row][col].input1;

	//get operation - TERM
	TStackItem* func = (TStackItem*)malloc(sizeof(struct stackItem));
	func->isTerm = TERM;
	switch (result->CgpProgram[row][col].function) {
		case MUL:	func->printable =  strdup("*");
					break;
		case DIV:	func->printable =  strdup("/");
					break;
		case AND:	func->printable =  strdup("&");
					break;
		case OR:	func->printable =  strdup("|");
					break;
		case PLUS:	func->printable =  strdup("+");
					break;
		case MINUS: func->printable =  strdup("-");
					break;
		case POW:	func->printable =  strdup("^");
					break;
		case SIN:	func->printable =  strdup("sin");
					break;
		case COS:	func->printable =  strdup("cos");
					break;
		case CONST:	func->printable =  strdup("const");
					break;
		default: cout << "blbost" << endl;
	}

	//get second operand - NONTERM?
	TStackItem* op2 = (TStackItem*)malloc(sizeof(struct stackItem));
	if(result->CgpProgram[row][col].input2 < geneticP->inCount){
		op2->isTerm = TERM;
		op2->printable = strdup(intToStr(result->CgpProgram[row][col].input2)); 
	}
	else{
		op2->isTerm = NONTERM;
		op2->printable = strdup("nonterm");
	}
	op2->value = result->CgpProgram[row][col].input2;

	//insert (
	TStackItem* rBracket = (TStackItem*)malloc(sizeof(struct stackItem));
	rBracket->isTerm = TERM;
	rBracket->printable = strdup(")");

	//connect stack into list
	if(!strcmp(func->printable, "const")){
		op1->isTerm = TERM;
		op1->printable = getPrintable(result->CgpProgram[row][col].input1);
 		if((*tmp)->prev != NULL){
			(*tmp)->prev->next = op1;
		}		
		op1->prev = (*tmp)->prev;
		op1->next = (*tmp)->next;
		if(op1->next != NULL){
			op1->next->prev = op1;
		}
		free(lBracket);
		free(rBracket);
		free(op2);
		free(func);	
		if((*tmp) == (*stack))
			(*stack) = op1;
		free((*tmp));
		(*tmp) = op1;
	}
	else if((!strcmp(func->printable,"sin")) || (!strcmp(func->printable, "cos"))){
		if((*tmp)->prev != NULL){
			(*tmp)->prev->next = func;
		}
		func->prev = (*tmp)->prev;
		func->next = lBracket;
		lBracket->prev = func;
		lBracket->next = op1;
		op1->prev = lBracket;
		op1->next = rBracket;
		rBracket->prev = op1;
		rBracket->next = (*tmp)->next;	
		if(rBracket->next != NULL){
			rBracket->next->prev = rBracket;
		}
		free(op2);			
		if((*tmp) == (*stack))
			(*stack) = func;
		free((*tmp));
		(*tmp) = rBracket;
	}
	else {
		if((*tmp)->prev != NULL){
			(*tmp)->prev->next = lBracket;
		}
		lBracket->prev = (*tmp)->prev;
		lBracket->next = op1;
		op1->prev = lBracket;
		op1->next = func;
		func->prev = op1;
		func->next = op2;
		op2->prev = func;
		op2->next = rBracket;
		rBracket->prev = op2;
		rBracket->next = (*tmp)->next;	
		if(rBracket->next != NULL){
			rBracket->next->prev = rBracket;
		}	
		if((*tmp) == (*stack))
			(*stack) = lBracket;
		free((*tmp));
		(*tmp) = rBracket;
	}
}

void printReadableResult(TIndividual* result, TCgpProperties* geneticP){
	TStackItem* stack;
	TStackItem* node = (TStackItem*)malloc(sizeof(struct stackItem));
	bool change;

	node->isTerm = NONTERM;
	node->value = result->output->input1;
	node->printable = strdup("nonterm");
	node->next = NULL;
	node->prev = NULL;
	stack = node;
	
	do{
		change = false;
		for(TStackItem* tmp = stack; tmp != NULL; tmp = tmp->next){
			if(tmp->isTerm == NONTERM){
				change = true;
				expandNode(&tmp, result, &stack, geneticP);
			}
		}
	}while(change);

	for(TStackItem* tmp = stack; tmp != NULL; tmp = tmp->next){
		cerr << tmp->printable;
	}
	cerr << endl;

	return;
}


void printResult(TIndividual* result, TCgpProperties* geneticP){
	cerr << "====================================================================" << endl;
	for(int i = 0; i < geneticP->rows; i++){
		for(int j = 0; j < geneticP->cols; j++){
			cerr << (*result).CgpProgram[i][j].input1 << " " << (*result).CgpProgram[i][j].input2 << " [" << (*result).CgpProgram[i][j].function << "]   ";
			fflush(stdout);
		}
		cerr << endl;
	}
	cerr << (*result).output->input1 << " [Y]" << endl;
	cerr << "Active nodes: ";
	for(int i = 0; i < (geneticP->rows * geneticP->cols); i++){
		if(result->activeNodes->at(i))
			cerr << i  << ", ";
	}
	cerr << endl;
	cerr << "Fitness: " << result->fitness << endl;
	cerr << "====================================================================" << endl;

	return;
}

int getDataCount(FILE* data){
	int count, i = 0;
	char line[20], c;

	//cout << "iowork@291: got into while" << endl;
  	while((c = fgetc(data)) != '\n'){
		line[i] = c;
		i++;
	}
	//cout << "iowork@296: got out of while" << endl;
	count = atoi(line);

	return count;
}

void getNextData(FILE* data, double* dataArray, int ioCount){
	int i = 0;
	int j = 0;
	char num[20];
	char c;

//	cout << "iowork@308: got into while" << endl;
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
//	cout << "iowork@327: got out of while" << endl;

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