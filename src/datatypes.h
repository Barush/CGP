/******************************************************************************/
/************************ COEVOLUTION IN CGP **********************************/
/************************* BACHELORS THESIS ***********************************/
/*********************** BARBORA SKRIVANKOVA **********************************/
/********************* xskri01@stud.fit.vutbr.cz ******************************/
/******************************************************************************/

/**************** HEADER FILE WITH DEFINED DATA TYPES *************************/
/** file name: 			datatypes.h
	creation date:		10/2013
**/

#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <vector>
#include <stack>
#include <string>
#include <cmath>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/types.h>

#define _XOPEN_SOURCE
#define _POSIX_SOURCE
#define _GNU_SOURCE

using namespace std;

#define CONSTCOUNT 4

/***************************************************************************
									ENUMS
***************************************************************************/

//possible operations in CGP matrix
typedef enum function {
	MUL = 0,
	DIV,	//1
	PLUS,	//2
	MINUS,	//3
	POW,	//4
	SIN,	//5
	COS,	//6
	CONST, 	//7
	LOG,	//8
	ABS,	//9
	EXP		//10
}TFunction;

//constants usable in CONST operation
typedef enum constants {
	PI = 0,
	EULER,
	ONE,
	ZERO
}TConstants;

//possibilities for the syntactic tree nodes
typedef enum stackFlag {
	TERM = 0,
	NONTERM
}TStackFlag;

//codes of runtime errors
typedef enum errCodes{
	EOK = 0,
	ECMD,
	EFILE,
	EALLOC,
	EUNKNOWN
}TErrCode;

/***************************************************************************
									CGP STRUCTS
***************************************************************************/

//one cell of a CGP matrix
typedef struct cell {
	int input1;
	int input2;
	int function;
}TCell;

//all CGP properties structure
typedef struct cgpProperties {
	int inCount;			//count of main inputs
	int outCount;			//count of main outputs
	int compInCount;		//count of component inputs
	int rows;				//count of rows in the matrix
	int cols;				//count of columns in the matrix
	int l_back;		 		//l-back param of the matrix
	int individCount;		//count of individuals in the generation
	double fitToleration;	//toleration of hits
	double constants[CONSTCOUNT];//constants array
	double countedNodes;	//countednodes during whole run
	int hybridPoints;		//COEV: number of points use for crossing
	int testSize;			//COEV: size of one test
	int coevICnt;			//COEV: number of tests in one generation
	int archiveSize;		//COEV: size of archive comparing to CGP generation
	int bestCnt;			//COEV: number of best genotypes continuing to the next generation
	int chldCnt;			//COEV: number of children created for the next generation
	TErrCode ecode;			//actual state of encounting
}TCgpProperties;

//whole CGP struct
typedef struct individual{
	vector< vector<TCell> >* CgpProgram;
	TCell output;
	vector<bool>* activeNodes;
	int activeNodesCount;
	double value;
	int fitness;
}TIndividual;

//input file data matrix
typedef struct data{
	double** data;
	int dataCount;
}TData;

//functions file data struct
typedef struct funcAvailable{
	vector<int>* funArr;
	int funCnt;
}TFuncAvailable;

//struct for recursive descent
typedef struct stackItem {
	int isTerm;
	int value;
	char* printable;
	struct stackItem* next;
	struct stackItem* prev;
}TStackItem;

/***************************************************************************
								COEVOLUTION STRUCTS
***************************************************************************/
//individual for coevolution population								
typedef struct coevIndividual{
	double fitness;
	vector<int>* value;
}TCoevIndividual;

//struct for shared memory between threads						
typedef struct shared{
	pthread_mutex_t cont_sem;
	bool cont;
	pthread_mutex_t end_sem;
	bool end;
}TShared;

//shared memory archive of best solutions
typedef struct archive{
	pthread_mutex_t arch_sem;
	TIndividual* arch;
}TArchive;

//one individual of coevolution population
typedef struct test{
	pthread_mutex_t test_sem;
	TCoevIndividual test;
}TTest;

//coevolution properties
typedef struct coevParams{
	TShared* memory;
	TCgpProperties* CGPparams;
	TFuncAvailable* funcAv;
	TArchive* archive;
	TTest* test;
	TData* input;
}TCoevParams;