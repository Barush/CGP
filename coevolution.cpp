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
#define BESTCNT 8
#define CHLDCNT 8

vector<TCoevIndividual>* generatePopulation(TCgpProperties* CGPparams, TData* input){
		cout << "generate population I" << endl;
	vector<TCoevIndividual>* population = new vector<TCoevIndividual>(CGPparams->coevICnt);

	for(int i = 0; i < CGPparams->coevICnt; i++){
		population->at(i).fitness = 0;
		cout << "generate population II" << endl;
		vector<int>* a = new vector<int>(CGPparams->testSize);
		population->at(i).value = a;
		for(int j = 0; j < CGPparams->testSize; j++){
			population->at(i).value->at(j) = rand() % input->dataCount;
		}

		// TODO: check for duplicities
	}

	return population;
}

void C_writeOutPopulation(vector<TCoevIndividual>* population){
	for(int i = 0; i < population->size(); i++){
		for(int j = 0; j < population->at(i).value->size(); j++){
			cout << population->at(i).value->at(j) << " " ;
			if((population->at(i).value->at(j) < 100)){
				cout << " ";
				if(population->at(i).value->at(j) < 10)
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
		for(int j = 0; j < population->at(i).value->size(); j++){
			for(int k = 0; k < params->individCount; k++){
				//reset fitness
				resetFitness_ActiveNodes(&archive[k], params);
				//get value
				getValue(&archive[k], params, input->data[population->at(i).value->at(j)]);
				//get fitness
				getFitness(&archive[k], params, input->data[population->at(i).value->at(j)]);
				//sume fitness
				population->at(i).fitness += archive[k].fitness;
			}//for all elements of archive
		}//for all vectors of test
		population->at(i).fitness = population->at(i).fitness / population->at(i).value->size();
	}//for all tests
}

bool comp(TCoevIndividual i, TCoevIndividual j){
	return (i.fitness < j.fitness);
}

vector<TCoevIndividual>* C_getBest(vector<TCoevIndividual>* oldGen, TCgpProperties* CGPparams){
	sort(oldGen->begin(), oldGen->end(), comp);
	cout << "get best" << endl;
	vector<TCoevIndividual>* newGen = new vector<TCoevIndividual>(CGPparams->coevICnt);
	cout << "after new" << endl;
	for(int i = 0; i < BESTCNT; i++){
		newGen->at(i) = oldGen->at(i);
	}
	cout << "after getbest" << endl;
	return newGen;
}

TCoevIndividual* C_getParent(vector<TCoevIndividual>* population, TCgpProperties* CGPparams){
	int ind1, ind2;

	ind1 = rand() % CGPparams->coevICnt;
	ind2 = rand() % CGPparams->coevICnt;

	return (population->at(ind1).fitness < population->at(ind2).fitness)?&population->at(ind1):&population->at(ind2);
}

void C_getChildren(vector<TCoevIndividual>* oldGen, vector<TCoevIndividual>* newGen, TCgpProperties* CGPparams){
	TCoevIndividual* parent1, *parent2;
	cout << "get children" << endl;
	vector<int> crossPts;
	for(int i = BESTCNT; i < (BESTCNT + CHLDCNT); i += 2){
		parent1 = C_getParent(oldGen, CGPparams);
		parent2 = C_getParent(oldGen, CGPparams);
		for(int j = 0; j < CGPparams->hybridPoints; j++){
			crossPts.push_back(rand() % CGPparams->testSize);
		}
		cout << "sort" << endl;
		sort(crossPts.begin(), crossPts.end());
		cout << "after" << endl;
		newGen->at(i) = oldGen->at(i);
		newGen->at(i+1) = oldGen->at(i+1);
		cout << "before for" << endl;
		for(int j = 0; j < CGPparams->testSize; j++){
			if(CGPparams->hybridPoints == 1){
				cout << "hybridPoints == 1" << endl;
				if(j > crossPts[0]){
					newGen->at(i).value[j] = parent2->value[j];
					newGen->at(i+1).value[j] = parent1->value[j];	
				}
			}
			else {
				if(j > crossPts[0] && j < crossPts[1]){
					newGen->at(i).value[j] = parent2->value[j];
					newGen->at(i+1).value[j] = parent1->value[j];	
				}
				if(CGPparams->hybridPoints == 3){
					if(j > crossPts[2]){
						newGen->at(i).value[j] = parent2->value[j];
						newGen->at(i+1).value[j] = parent1->value[j];							
					}
				}
			}
		}//for all components of tests
		cout << "after for" << endl;
	}//for all tests
}

void C_getMutants(vector<TCoevIndividual>* newGen, TCgpProperties* CGPparams, TData* input){
	for(int i = (BESTCNT + CHLDCNT); i < CGPparams->coevICnt; i++){
		newGen->at(i).fitness = 0;
		cout << "get mutants" << endl;
		vector<int> *a = new vector<int>(CGPparams->testSize);
		newGen->at(i).value = a;
		for(int j = 0; j < CGPparams->testSize; j++){
			newGen->at(i).value->at(j) = rand() % input->dataCount;
		}
	}
}

vector<TCoevIndividual>* C_getNewGeneration(vector<TCoevIndividual>* oldGen, TCgpProperties* CGPparams, TData* input){
	vector<TCoevIndividual>* newGen = C_getBest(oldGen, CGPparams);
	C_getChildren(oldGen, newGen, CGPparams);
	C_getMutants(newGen, CGPparams, input);

	delete(oldGen);
	return newGen;
}


void* coevolution(void* par){
	srand(time(NULL));

	TCoevParams* params = (TCoevParams*) par;
	vector<TCoevIndividual> *population = generatePopulation(params->CGPparams, params->input);

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
		population = C_getNewGeneration(population, params->CGPparams, params->input);
		i++;
	}

	C_writeOutPopulation(population);
}
