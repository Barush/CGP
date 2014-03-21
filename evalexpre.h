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
void getValue(TIndividual* genotype, TCgpProperties* geneticP, double* dataArray);
void resetFitness_ActiveNodes(TIndividual* genotype, TCgpProperties* geneticP);
void getFitness(TIndividual* genotype, TCgpProperties* geneticP, double* dataArray);
