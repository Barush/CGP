/******************************************************************************/
/************************ COEVOLUTION IN CGP **********************************/
/************************* BACHELORS THESIS ***********************************/
/*********************** BARBORA SKRIVANKOVA **********************************/
/********************* xskri01@stud.fit.vutbr.cz ******************************/
/******************************************************************************/

/******************** HEADER FILE FOR EVALEXPRE *******************************/
/** file name: 			evalexpre.h
	creation date:		10/2013
**/

#include "datatypes.h"

/******************* FUNCTION PROTOTYPES ***************************************/
void getActiveNodes(TIndividual* geneticArray, TCgpProperties* geneticP);
void getValue(TIndividual* geneticArray, TCgpProperties* geneticP, double* dataArray);
void resetFitness(TIndividual* geneticArray, TCgpProperties* geneticP);
void getFitness(TIndividual* geneticArray, TCgpProperties* geneticP, double* dataArray);