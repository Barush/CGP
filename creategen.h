/******************************************************************************/
/************************ COEVOLUTION IN CGP **********************************/
/************************* BACHELORS THESIS ***********************************/
/*********************** BARBORA SKRIVANKOVA **********************************/
/********************* xskri01@stud.fit.vutbr.cz ******************************/
/******************************************************************************/

/********************** HEADER FILE FOR CREATEGEN ********************************/
/** file name: 			creategen.h
	creation date:		10/2013
**/

#include "datatypes.h"

/******************* FUNCTION PROTOTYPES ***************************************/
TCell** alocateProgram(int row, int col);
TIndividual* createIndividual(TCgpProperties* geneticP, TIndividual *subject, TFuncAvailable* functions);
TIndividual* createGeneration(TCgpProperties* geneticP, TFuncAvailable* functions);
void destroyGeneration(TIndividual** geneticArray, TCgpProperties* geneticP);
