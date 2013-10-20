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
	ifstream data;
	int dataCount = 0;
	double* dataArray;

	//make argv controls
	data.open(argv[1], ifstream::in);

	srand(time(NULL)); // initiate random generator
	geneticParams = getParams();
	geneticArray = createGeneration(geneticParams);

	dataArray = (double*)malloc((geneticParams->inCount + 1) * sizeof(double));
	getActiveNodes(geneticArray, geneticParams);   
	dataCount = getDataCount(data);
	for(int i = 0; i < dataCount; i++){
		getNextData(data, dataArray, geneticParams->inCount + 1);
		getValue(geneticArray, geneticParams, dataArray);
		for(int j = 0; j < geneticParams->individCount; j++){
			//cout << "Value " << j << ": " << geneticArray[j].value << ", original is: " << dataArray[geneticParams->inCount] << endl;
		}	
		getFitness(geneticArray, geneticParams, dataArray);
	}//test of all data inputs
	

    for(int i = 0; i < geneticParams->individCount; i++){
            cout << "Individual no. " << i+1 << ":" << endl;
            printResult(&geneticArray[i], geneticParams);
    }

    destroyGeneration(&geneticArray, geneticParams);
    free(geneticParams);
	return EXIT_SUCCESS;
} 