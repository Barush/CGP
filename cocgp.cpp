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
#include "evolution.h"


int main(int argc, char** argv){
	TIndividual* geneticArray;
	TCgpProperties* geneticParams;

	//make argv controls

	srand(time(NULL)); // initiate random generator
	geneticParams = getParams();
	geneticArray = createGeneration(geneticParams);


	geneticArray = evolutionStep(argv[1], geneticParams, geneticArray, false);

	for(int i = 0; i < 10; i++){
		geneticArray = evolutionStep(argv[1], geneticParams, geneticArray, true);

		cout << i << ". generation: " << endl;
	    for(int i = 0; i < geneticParams->individCount; i++){
	            cout << "Individual no. " << i+1 << ":" << endl;
	            printResult(&geneticArray[i], geneticParams);
	    }		
	}

    destroyGeneration(&geneticArray, geneticParams);
    free(geneticParams);
	return EXIT_SUCCESS;
} 