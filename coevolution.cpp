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
#include <algorithm>
#include "datatypes.h"
#include "creategen.h"
#include "iowork.h"
#include "evalexpre.h"

//these will be params
#define TRAINEESIZE 200
#define INDCNT 20
#define INDSIZE 10
#define BESTCNT 8
#define CHLDCNT 8

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

void C_writeOutPopulation(vector<TCoevIndividual>* population){
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

void C_evaluatePopulation(vector<TCoevIndividual>* population, TData* input, TIndividual* archive, TCgpProperties* params){
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

bool comp(TCoevIndividual i, TCoevIndividual j){
	return (i.fitness < j.fitness);
}

vector<TCoevIndividual>* C_getBest(vector<TCoevIndividual>* oldGen){
	sort(oldGen->begin(), oldGen->end(), comp);
	vector<TCoevIndividual>* newGen = new vector<TCoevIndividual>(INDCNT);
	for(int i = 0; i < BESTCNT; i++){
		newGen->at(i) = oldGen->at(i);
	}
	return newGen;
}

TCoevIndividual* C_getParent(vector<TCoevIndividual>* population){
	int ind1, ind2;

	ind1 = rand() % INDCNT;
	ind2 = rand() % INDCNT;

	return (population->at(ind1).fitness < population->at(ind2).fitness)?&population->at(ind1):&population->at(ind2);
}

void C_getChildren(vector<TCoevIndividual>* oldGen, vector<TCoevIndividual>* newGen){
	TCoevIndividual* parent1, *parent2;
	int crossPnt1;
	for(int i = BESTCNT; i < (BESTCNT + CHLDCNT); i += 2){
		parent1 = C_getParent(oldGen);
		parent2 = C_getParent(oldGen);
		crossPnt1 = rand() % INDSIZE;
		newGen->at(i) = oldGen->at(i);
		newGen->at(i+1) = oldGen->at(i+1);
		for(int j = 0; j < INDSIZE; j++){
			if(j > crossPnt1){
				newGen->at(i).value[j] = parent2->value[j];
				newGen->at(i+1).value[j] = parent1->value[j];
			}
		}//for all components of tests
	}//for all tests
}

void C_getMutants(vector<TCoevIndividual>* newGen){
	for(int i = (BESTCNT + CHLDCNT); i < INDCNT; i++){
		newGen->at(i).fitness = 0;
		vector<int> a(INDSIZE);
		newGen->at(i).value = a;
		for(int j = 0; j < INDSIZE; j++){
			newGen->at(i).value[j] = rand() % TRAINEESIZE;
		}
	}
}

vector<TCoevIndividual>* C_getNewGeneration(vector<TCoevIndividual>* oldGen){
	vector<TCoevIndividual>* newGen = C_getBest(oldGen);
	C_getChildren(oldGen, newGen);
	C_getMutants(newGen);

	delete(oldGen);
	return newGen;
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
		C_evaluatePopulation(population, input, archive, params);
		population = C_getNewGeneration(population);
		i++;
	}

	C_writeOutPopulation(population);
	destroyGeneration(&archive, params);
	destroyFunctions(funcAv);
	destroyData(input);
	delete(population);
	free(params);

	return 0;
}
