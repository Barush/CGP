/******************************************************************************/
/************************ COEVOLUTION IN CGP **********************************/
/************************* BACHELORS THESIS ***********************************/
/*********************** BARBORA SKRIVANKOVA **********************************/
/********************* xskri01@stud.fit.vutbr.cz ******************************/
/******************************************************************************/

/********************** HEADER FILE FOR COEVOLUTION ********************************/
/** file name: 			coevolution.h
	creation date:		03/2014
**/

#include <unistd.h>
#include <algorithm>
#include "datatypes.h"
#include "creategen.h"
#include "iowork.h"
#include "evalexpre.h"

void* coevolution(void* par);
bool C_testGlobalSolution(TIndividual* solution, TData* input, TCgpProperties* geneticP);