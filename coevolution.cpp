/******************************************************************************/
/************************ COEVOLUTION IN CGP **********************************/
/************************* BACHELORS THESIS ***********************************/
/*********************** BARBORA SKRIVANKOVA **********************************/
/********************* xskri01@stud.fit.vutbr.cz ******************************/
/******************************************************************************/

/********************* COEVOLUTION MODUL **************************************/
/** file name: 			coevolution.cpp
	creation date:		03/2014
**/

//#include "coevolution.h"
#include <unistd.h>
#include "datatypes.h"
#include "creategen.h"
#include "iowork.h"
#include "evalexpre.h"

#define TRAINEESIZE 200
#define INDCNT 20
#define INDSIZE 10

vector<TCoevIndividual>* generatePopulation(){
	vector<TCoevIndividual>* population = new vector<TCoevIndividual>(INDCNT);

	for(int i = 0; i < INDCNT; i++){
		population->at(i).fitness = 0;
		vector<int> a(INDSIZE);
		population->at(i).value = a;
		for(int j = 0; j < INDSIZE; j++){
			population->at(i).value[j] = rand() % TRAINEESIZE;
		}

		// TODO: check for duplicities
	}

	return population;
}

void writeOutPopulation(vector<TCoevIndividual>* population){
	for(int i = 0; i < population->size(); i++){
		for(int j = 0; j < population->at(i).value.size(); j++){
			cout << population->at(i).value[j] << " " ;
			if((population->at(i).value[j] < 100)){
				cout << " ";
				if(population->at(i).value[j] < 10)
					cout << " ";
			} 
		}
		cout << " -> " << population->at(i).fitness << endl;
	}
}

void evaluate_population(vector<TCoevIndividual>* population, TData* input, TIndividual* archive, TCgpProperties* params){
	//reset fitness
	for(int i = 0; i < population->size(); i++){
		population->at(i).fitness = 0;
		for(int j = 0; j < population->at(i).value.size(); j++){
			//reset fitness
			resetFitness_ActiveNodes(archive, params);
			//get value
			getValue(&archive, params, input->data[population->at(i).value[j]]);
			//get fitness
			getFitness(archive, params, input->data[population->at(i).value[j]]);
			//sume fitness
			for(int k = 0; k < params->individCount; k++){
				population->at(i).fitness += archive[k].fitness;
			}//for all elements of archive
		}//for all vectors of test
	}//for all tests
}

int main(int argc, char * argv[]){
	srand(time(NULL));
	vector<TCoevIndividual> *population = generatePopulation();

	//these will be params
	TCgpProperties* params = getParams(argv, argc);
	TFuncAvailable* funcAv = getFunctions(argv[2]);
	TIndividual* archive = createGeneration(params, funcAv);
	TData* input = getData(argv[1], params);

	int i = 0;

	while(i < 1){
		evaluate_population(population, input, archive, params);
		i++;
	}

	writeOutPopulation(population);
	destroyGeneration(&archive, params);
	destroyFunctions(funcAv);
	destroyData(input);
	free(params);

	return 0;
}
