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

TParents* getParents(TCgpProperties* geneticP, TIndividual* geneticArray);
void changeGenes(TIndividual* parent, TIndividual* individ, TCgpProperties* geneticP);
TIndividual* mutateGeneration(TIndividual* geneticArray, TParents* parents, TCgpProperties* geneticP);
