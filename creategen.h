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
TIndividual* createIndividual(TCgpProperties* geneticP, TIndividual *subject);
TIndividual* createGeneration(TCgpProperties* geneticP);
void destroyGeneration(TIndividual** geneticArray, TCgpProperties* geneticP);