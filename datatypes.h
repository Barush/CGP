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

using namespace std;

#define CONSTCOUNT 4
#define MAXFIT 400

//Possible operations in CGP matrix, will be modified from program input
typedef enum function {
	MUL = 0,
	DIV,	//1
	PLUS,	//2
	MINUS,	//3
	POW,	//4
	SIN,	//5
	COS,	//6
	CONST 	//7
}TFunction;

typedef enum constants {
	PI = 0,
	EULER,
	ONE,
	ZERO
}TConstants;

typedef enum stackFlag {
	TERM = 0,
	NONTERM
}TStackFlag;

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
	double constants[CONSTCOUNT];
	double countedNodes;
}TCgpProperties;

//whole CGP struct
typedef struct individual{
	TCell** CgpProgram;
	TCell* output;
	vector<bool>* activeNodes;
	int activeNodesCount;
	double value;
	int fitness;
}TIndividual;

typedef struct data{
	double** data;
	int dataCount;
}TData;

//struct for recursive descent
typedef struct stackItem {
	int isTerm;
	int value;
	char* printable;
	struct stackItem* next;
	struct stackItem* prev;
}TStackItem;

typedef struct indivList {
	TIndividual* node;
	struct indivList* next;
}TIndivList;