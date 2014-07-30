/******************************************************************************/
/************************ COEVOLUTION IN CGP **********************************/
/************************* BACHELORS THESIS ***********************************/
/*********************** BARBORA SKRIVANKOVA **********************************/
/********************* xskri01@stud.fit.vutbr.cz ******************************/
/******************************************************************************/

/********************** HEADER FILE FOR COEVOLUTION ***************************/
/** file name: 			coevolution.h
	creation date:		03/2014
**/

#include <unistd.h>
#include <algorithm>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

#include "datatypes.h"
#include "creategen.h"
#include "iowork.h"
#include "evalexpre.h"
#include "evolution.h"


TShared* memoryInit();
TArchive* archiveInit(TCgpProperties* geneticP, vector<TIndividual>* genArray, TFuncAvailable* funcAv);
TTest* testInit(TData* input, TCgpProperties* params);
void changeArchive(int index, TArchive* archive, TIndividual* genotype, TCgpProperties* params);
TCoevParams* paramsInit(TCgpProperties* geneticP, vector<TIndividual>* geneticArray, TFuncAvailable* funcAv, TData* input);
void* coevolution(void* par);
int C_testGlobalSolution(TIndividual* solution, TData* input, TCgpProperties* geneticP);