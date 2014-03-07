/******************************************************************************/
/************************ COEVOLUTION IN CGP **********************************/
/************************* BACHELORS THESIS ***********************************/
/*********************** BARBORA SKRIVANKOVA **********************************/
/********************* xskri01@stud.fit.vutbr.cz ******************************/
/******************************************************************************/

/******************** HEADER FILE FOR EVOLUTION *******************************/
/** file name: 			evolution.h
	creation date:		10/2013
**/

#include "datatypes.h"
#include "iowork.h"
#include "evalexpre.h"

void evolutionStep(TData* input, TCgpProperties* geneticP, TIndividual** geneticArray, TFuncAvailable* functions);
void getParents(TIndividual** geneticArray, TCgpProperties* geneticP);
void copyGenotype(TIndividual* parent, TIndividual** geneticArray, TCgpProperties* geneticP);
