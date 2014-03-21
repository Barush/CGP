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

#include "coevolution.h"

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
	//copy archive --> minimalizace kriticke sekce
	for(int i = 0; i < population->size(); i++){
		population->at(i).fitness = 0;
		for(int j = 0; j < population->at(i).value.size(); j++){
			for(int k = 0; k < params->individCount; k++){
				//reset fitness
				resetFitness_ActiveNodes(&archive[k], params);
				//get value
				getValue(&archive[k], params, input->data[population->at(i).value[j]]);
				//get fitness
				getFitness(&archive[k], params, input->data[population->at(i).value[j]]);
				//sume fitness
				population->at(i).fitness += archive[k].fitness;
			}//for all elements of archive
		}//for all vectors of test
		population->at(i).fitness = population->at(i).fitness / population->at(i).value.size();
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


void* coevolution(void* par){
	srand(time(NULL));

	TCoevParams* params = (TCoevParams*) par;
	vector<TCoevIndividual> *population = generatePopulation();

	int i = 0;

	while(1){	
		//presun na konec --> aby byl test
		while(1){
			//zrusit aktivni cekani
			if(params->memory->cont)
				break;
		}
		pthread_mutex_lock(&params->memory->cont_sem);
		params->memory->cont = false;
		pthread_mutex_unlock(&params->memory->cont_sem);

		pthread_mutex_lock(&params->memory->end_sem);
		if(params->memory->end){
			break;
		}
		pthread_mutex_unlock(&params->memory->end_sem);
		C_evaluatePopulation(population, params->input, params->archive->arch, params->CGPparams);
		population = C_getNewGeneration(population);
		i++;
	}

	C_writeOutPopulation(population);
}
