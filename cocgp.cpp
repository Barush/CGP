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

	int *data = (int*)malloc((geneticParams->inCount + 1) * sizeof(int));
	ifstream testData.open(argv[0], ios::in);
	string line, number;

	while(getline(testData, line)){
		for(int i = 0; i < (geneticParams->inCount + 1); i++){
			for(int j = 0; line.c_str()[j] != " "; j++){
				number.c_str()[j] = line.c_str()[j];
			}
			number >> data[i];
		}
		
	}
	getValue(geneticArray, geneticParams, data);


	for(int i = 0; i < geneticParams->individCount; i++){
		cout << "Individual no. " << i+1 << ":" << endl;
		printResult(&geneticArray[i], geneticParams);
	}

	destroyGeneration(&geneticArray, geneticParams);
	free(geneticParams);

	return EXIT_SUCCESS;
} 