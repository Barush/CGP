/******************************************************************************/
/************************ COEVOLUTION IN CGP **********************************/
/************************* BACHELORS THESIS ***********************************/
/*********************** BARBORA SKRIVANKOVA **********************************/
/********************* xskri01@stud.fit.vutbr.cz ******************************/
/******************************************************************************/

/********************** HEADER FILE FOR IOWORK ********************************/
/** file name: 			iowork.h
	creation date:		10/2013
**/

#include "datatypes.h"

/******************* FUNCTION PROTOTYPES ***************************************/
void printUsage();
TCgpProperties* getParams(char** argv, int argc);
void printResult(TIndividual* result, TCgpProperties* geneticP);
void printReadableResult(TIndividual* result, TCgpProperties* geneticP);
int getDataCount(FILE* data);
void getNextData(FILE* data, double* dataArray, int ioCount);
TData* getData(char* filename, TCgpProperties* geneticP);
void destroyData(TData* input);
