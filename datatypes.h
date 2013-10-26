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
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <vector>
#include <stack>
#include <string>
#include <cmath>

using namespace std;


//Possible operations in CGP matrix, will be modified from program input
typedef enum function {
	MUL = 0,
	DIV,
	AND,
	OR,
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
	double countedNodes;
}TCgpProperties;

//whole CGP struct
typedef struct individual{
	TCell** CgpProgram;
	TCell* output;
	vector<bool>* activeNodes;
	int value;
	int fitness;
	bool wasParent;
}TIndividual;