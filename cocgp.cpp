/******************************************************************************/
/************************ COEVOLUTION IN CGP **********************************/
/************************* BACHELORS THESIS ***********************************/
/*********************** BARBORA SKRIVANKOVA **********************************/
/********************* xskri01@stud.fit.vutbr.cz ******************************/
/******************************************************************************/

/**************************** MAIN MODUL **************************************/
/** file name: 			cocgp.cpp
	creation date:		10/2013
**/

#include "datatypes.h"
#include "evalexpre.h"
#include "iowork.h"
#include "creategen.h"


int main(int argc, char** argv){
	TIndividual* geneticArray;
	TCgpProperties* geneticParams;

	srand(time(NULL)); // initiate random generator
	geneticParams = getParams();
	geneticArray = createGeneration(geneticParams);

	getActiveNodes(geneticArray, geneticParams);
	getValue(geneticArray, geneticParams, 10, 20, 30, 50, 5);
	for(int i = 0; i < geneticParams->individCount; i++){
		cout << "Individual no. " << i+1 << ":" << endl;
		printResult(&geneticArray[i], geneticParams);
	}

	destroyGeneration(&geneticArray, geneticParams);
	free(geneticParams);

	return EXIT_SUCCESS;
} 