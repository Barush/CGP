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
void getActiveNodes(vector<TIndividual>* geneticArray, TCgpProperties* geneticP);
void getValue(TIndividual* genotype, TCgpProperties* geneticP, double* dataArray);
void resetFitness(TIndividual* genotype);
void getFitness(TIndividual* genotype, TCgpProperties* geneticP, double* dataArray);
