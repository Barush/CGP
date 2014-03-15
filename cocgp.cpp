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

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

TShared* memoryInit(){
	TShared* mem = NULL;
	int descriptor;
/*
	descriptor = shm_open("ending", O_RDWR|O_CREAT, 0600);
	ftruncate(descriptor, sizeof(TShared));
	mem = mmap(NULL, sizeof(TShared), PROT_READ|PROT_WRITE, MAP_SHARED,descriptor, 0);
	//pthread_mutex_init(mem->end_sem, NULL);
	*/
	return mem;
}

int main(int argc, char** argv){

	if(!strcmp(argv[1], "-h")){
		//parameter help
		printUsage();
		return EXIT_SUCCESS;
	}

	TIndividual* geneticArray;		//array for one generation
	TCgpProperties* geneticParams;	//parameters of CGP
	TData* input;					//matrix of input-output data
	TFuncAvailable* funcAv;
	int fitness = 0, gener = 0;

	// TODO: make argv controls

	srand(time(NULL)); // initiate random generator
	geneticParams = getParams(argv, argc);
	funcAv = getFunctions(argv[2]);
	geneticArray = createGeneration(geneticParams, funcAv);

	input = getData(argv[1], geneticParams);

#ifdef COEVOLUTION
	TShared* memory;
	memory = memoryInit();
	pthread_t coevolution_var;
	pthread_create(&coevolution_var, NULL, coevolution, NULL);
#endif

	for(int i = 0;; i++){
		evolutionStep(input, geneticParams, &geneticArray, funcAv);
		//cout << "got out of evolution step" << endl;
		if(geneticArray[0].fitness != fitness){
			fitness = geneticArray[0].fitness;
			gener = i;
		}
		if((i - gener) > 1000000)
			break;

		if(!(i%100))
			cout << i << " " << geneticArray[0].fitness << endl;
		if(geneticArray[0].fitness == input->dataCount){
			cout << i + 1 << " " << input->dataCount << endl;
			break;
		}
	}
	/*	cout << i << ". generation: " << endl;
	    for(int i = 0; i < geneticParams->individCount; i++){
	            cout << "Individual no. " << i+1 << ":" << endl;
	            printResult(&geneticArray[i], geneticParams);
	    }		
	}*/
	TIndividual* solution = &(geneticArray[0]);
	printResult(solution, geneticParams);
	printReadableResult(solution, geneticParams);
	cerr << "Counted nodes: " << geneticParams->countedNodes << endl;

    destroyGeneration(&geneticArray, geneticParams);
    destroyData(input);
    destroyFunctions(funcAv);
    free(geneticParams);
	return EXIT_SUCCESS;
} 
