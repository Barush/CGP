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

TParents* getParents(TCgpProperties* geneticP, TIndividual* geneticArray);
void copyFenotype(TIndividual* parent, TIndividual* individ, TCgpProperties* geneticP);
void changeGenes(TIndividual* parent, TIndividual* individ, TCgpProperties* geneticP);
TIndividual* mutateGeneration(TIndividual* geneticArray, TParents* parents, TCgpProperties* geneticP);
TIndividual* mutation(TCgpProperties* geneticP, TIndividual* geneticArray);
TIndividual* evolutionStep(char* filename, TCgpProperties* geneticP, TIndividual* geneticArray, bool mutate);
