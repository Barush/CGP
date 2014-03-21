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
#define ROW 1
#define COL 20
#define L_BACK 20
#define GENER 5

void printUsage(){
	cout << "COEVOLUTION IN CGP" << endl;
	cout << "BACHELORS THESIS" << endl;
	cout << "BARBORA SKRIVANKOVA " << endl;
	cout << "xskriv01@stud.fit.vutbr.cz" << endl;

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
	params->fitToleration = 0.1;

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
		else if(!strcmp(argv[i], "-t")){
			i++;
			stringstream ss(argv[i]);
			ss >> params->fitToleration;
		}
		else if(!strcmp(argv[i], "-i")){
			i++;
			params->inCount = atoi(argv[i]);
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
		case LOG:	func->printable =  strdup("log");
					break;
		case ABS:	func->printable =  strdup("abs");
					break;
		case CONST:	func->printable =  strdup("const");
					break;
		case EXP:	func->printable = strdup("exp");
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
		free(lBracket->printable);
		free(lBracket);
		free(rBracket->printable);
		free(rBracket);
		free(op2->printable);
		free(op2);
		free(func->printable);
		free(func);	
		if((*tmp) == (*stack))
			(*stack) = op1;
		free((*tmp)->printable);
		free((*tmp));
		(*tmp) = op1;
	}
	else if((!strcmp(func->printable,"sin")) || (!strcmp(func->printable, "cos"))
	 || (!strcmp(func->printable, "log")) || (!strcmp(func->printable, "exp"))){
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
		free(op2->printable);
		free(op2);			
		if((*tmp) == (*stack))
			(*stack) = func;
		free((*tmp)->printable);
		free((*tmp));
		(*tmp) = rBracket;
	}
	else if(!strcmp(func->printable, "abs")){
		if((*tmp)->prev != NULL){
			(*tmp)->prev->next = lBracket;
		}
		free(lBracket->printable);
		lBracket->printable = strdup("|");
		free(rBracket->printable);
		rBracket->printable = strdup("|");
		lBracket->prev = (*tmp)->prev;
		lBracket->next = op1;
		op1->prev = lBracket;
		op1->next = rBracket;
		rBracket->prev = op1;
		rBracket->next = (*tmp)->next;
		if(rBracket->next != NULL){
			rBracket->next->prev = rBracket;
		}
		free(op2->printable);
		free(op2);			
		if((*tmp) == (*stack))
			(*stack) = func;
		free((*tmp)->printable);
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
		free((*tmp)->printable);
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
			//cerr << "" << endl;
		}
	}while(change);

	for(TStackItem* tmp = stack; tmp != NULL; tmp = tmp->next){
		cerr << tmp->printable;
	}
	cerr << endl;

	TStackItem *pom, *tmp;
	for(tmp = stack; tmp->next != NULL;){
		pom = tmp;
		tmp = tmp->next;
		free(pom);
	}
	free(tmp);
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

	memset(line, 0, 20);

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
	char num[20] = { 0 };
	char c;


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

TData* getData(char* filename, TCgpProperties* geneticP){	
	FILE* data;						//input file
	TData* input = (TData*)malloc(sizeof(struct data));

	// open the data source file
	if((data = fopen(filename, "r")) == NULL){
		cerr << "Error in opening file: " << filename << endl;
		exit(1);
	}

	input->dataCount = getDataCount(data);
	input->data = (double**)malloc(input->dataCount * sizeof(double*));

	for(int i = 0; i < input->dataCount; i++){
		input->data[i] = (double*)malloc((geneticP->inCount + geneticP->outCount) * sizeof(double));
	}

	for(int i = 0; i < input->dataCount; i++){
		getNextData(data, input->data[i], geneticP->inCount + geneticP->outCount);
	}

	fclose(data);
	return input;
}

void destroyData(TData* input){
	for(int i = 0; i < input->dataCount; i++){
		free(input->data[i]);
	}
	free(input->data);
	free(input);
}

int getFunc(FILE* input){
	int i = 0;
	char line[6], c;

	memset(line, 0, 6);

  	while((c = fgetc(input)) != '\n'){
		line[i] = c;
		i++;
	}

	if(!strcmp(line, "PLUS")){
		return PLUS;
	}
	else if(!strcmp(line, "MINUS")){
		return MINUS;
	}
	else if(!strcmp(line, "MUL")){
		return MUL;
	}
	else if(!strcmp(line, "DIV")){
		return DIV;
	}
	else if(!strcmp(line, "POW")){
		return POW;
	}
	else if(!strcmp(line, "SIN")){
		return SIN;
	}
	else if(!strcmp(line, "COS")){
		return COS;
	}
	else if(!strcmp(line, "CONST")){
		return CONST;
	}
	else if(!strcmp(line, "LOG")){
		return LOG;
	}
	else if(!strcmp(line, "ABS")){
		return ABS;
	}
	else if(!strcmp(line, "EXP")){
		return EXP;
	}
	else{
		cerr << "Error in the functions file." << endl;
		exit(1);
	}

}

TFuncAvailable* getFunctions(char* filename){
	FILE* input;
	TFuncAvailable* functions = (TFuncAvailable*)malloc(sizeof(struct funcAvailable));

	if((input = fopen(filename, "r")) == NULL){
		cerr << "Error in opening file: " << filename << endl;
		exit(1);
	}

	functions->funCnt = getDataCount(input);
	functions->funArr = (int*)malloc(functions->funCnt * sizeof(int));

	for(int i = 0; i < functions->funCnt; i++){
		functions->funArr[i] = getFunc(input);
	}

	fclose(input);
	return functions;
}

void destroyFunctions(TFuncAvailable* fnc){
	free(fnc->funArr);
	free(fnc);
}
