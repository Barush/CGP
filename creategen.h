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
TIndividual* alocateIndividual(int row, int col, TIndividual* subject, TCgpProperties* geneticP);
TIndividual* createIndividual(TCgpProperties* geneticP, TIndividual *subject, TFuncAvailable* functions);
vector<TIndividual>* createGeneration(TCgpProperties* geneticP, TFuncAvailable* functions);
void destroyGeneration(vector<TIndividual>* geneticArray, TCgpProperties* geneticP);
