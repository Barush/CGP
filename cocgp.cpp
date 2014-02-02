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

int lastFit = 0;

int main(int argc, char** argv){

	if(!strcmp(argv[1], "-h")){
		//parameter help
		printUsage();
		return EXIT_SUCCESS;
	}

	TIndividual* geneticArray;		//array for one generation
	TIndividual* actual;			//ptr to geneticArray - best fitness in the generation
	TCgpProperties* geneticParams;	//parameters of CGP

	// TODO: make argv controls

	srand(time(NULL)); // initiate random generator
	geneticParams = getParams(argv, argc);
	geneticArray = createGeneration(geneticParams);

	geneticArray = evolutionStep(argv[1], geneticParams, geneticArray, false);
	for(int i = 0; i < 100000; i++){
		cout << i;
		geneticArray = evolutionStep(argv[1], geneticParams, geneticArray, true);
		//cout << "got out of evolution step" << endl;
		actual = getParents(geneticParams, geneticArray);
		if(actual->fitness == 400){
			cout << i + 1 << " 400" << endl;
			break;
		}
	}
	/*	cout << i << ". generation: " << endl;
	    for(int i = 0; i < geneticParams->individCount; i++){
	            cout << "Individual no. " << i+1 << ":" << endl;
	            printResult(&geneticArray[i], geneticParams);
	    }		
	}*/
	TIndividual* solution = getParents(geneticParams, geneticArray);
	printResult(solution, geneticParams);
	printReadableResult(solution, geneticParams);
	cerr << "Counted nodes: " << geneticParams->countedNodes << endl;

    destroyGeneration(&geneticArray, geneticParams);
    free(geneticParams);
	return EXIT_SUCCESS;
} 