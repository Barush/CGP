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

#define CHLDCNT 8

int C_testGlobalSolution(TIndividual* solution, TData* input, TCgpProperties* geneticP){
	resetFitness(solution);
	for(int i = 0; i < input->dataCount; i++){
		getValue(solution, geneticP, input->data[i]);
		getFitness(solution, geneticP, input->data[i]);
	}

	return solution->fitness;
}

TCoevIndividual C_controlDuplicities(vector<int>* test, TData* input){
	sort(test->begin(), test->end());
	int last = test->at(0);
	for(int i = 1; i < test->size(); i++){
		if(last == test->at(i)){
			test->at(i) = rand() % input->dataCount;
		}
		else{
			last = test->at(i);
		}
	}
}

vector<TCoevIndividual>* generatePopulation(TCgpProperties* CGPparams, TData* input){
	vector<TCoevIndividual>* population = new vector<TCoevIndividual>(CGPparams->coevICnt);

	for(int i = 0; i < CGPparams->coevICnt; i++){
		population->at(i).fitness = 0;
		vector<int>* a = new vector<int>(CGPparams->testSize);
		population->at(i).value = a;
		for(int j = 0; j < CGPparams->testSize; j++){
			population->at(i).value->at(j) = rand() % input->dataCount;
		}
		C_controlDuplicities(population->at(i).value, input);
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
	// TODO: copy archive --> minimalizace kriticke sekce
	
	for(int i = 0; i < population->size(); i++){
		population->at(i).fitness = 0;
		for(int j = 0; j < population->at(i).value->size(); j++){
			for(int k = 0; k < params->individCount; k++){
				//reset fitness
				resetFitness(&archive[k]);
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
	vector<TCoevIndividual>* newGen = new vector<TCoevIndividual>(CGPparams->coevICnt);
	for(int i = 0; i < CGPparams->coevICnt; i++){
		newGen->at(i) = oldGen->at(i);
	}
	return newGen;
}

int C_getParent(vector<TCoevIndividual>* population, TCgpProperties* CGPparams){
	int ind1, ind2;

	ind1 = rand() % CGPparams->coevICnt;
	ind2 = rand() % CGPparams->coevICnt;

	return (population->at(ind1).fitness < population->at(ind2).fitness)?ind1:ind2;
}

void C_getChildren(vector<TCoevIndividual>* oldGen, vector<TCoevIndividual>* newGen, TCgpProperties* CGPparams, TData* input){
	int parent1, parent2;
	vector<int> crossPts;
	for(int i = CGPparams->bestCnt; i < (CGPparams->bestCnt + CGPparams->chldCnt); i += 2){
		parent1 = C_getParent(oldGen, CGPparams);
		parent2 = C_getParent(oldGen, CGPparams);
		for(int j = 0; j < CGPparams->hybridPoints; j++){
			crossPts.push_back(rand() % CGPparams->testSize);
		}
		sort(crossPts.begin(), crossPts.end());
		newGen->at(i) = oldGen->at(i);
		newGen->at(i+1) = oldGen->at(i+1);
		for(int j = 0; j < CGPparams->testSize; j++){
			if(CGPparams->hybridPoints == 1){
				if(j > crossPts[0]){
					newGen->at(i).value->at(j) = oldGen->at(parent2).value->at(j);
					newGen->at(i+1).value->at(j) = oldGen->at(parent1).value->at(j);	
				}
			}
			else {
				if(j > crossPts[0] && j < crossPts[1]){
					newGen->at(i).value->at(j) = oldGen->at(parent2).value->at(j);
					newGen->at(i+1).value->at(j) = oldGen->at(parent1).value->at(j);	
				}
				if(CGPparams->hybridPoints == 3){
					if(j > crossPts[2]){
						newGen->at(i).value->at(j) = oldGen->at(parent2).value->at(j);
						newGen->at(i+1).value->at(j) = oldGen->at(parent1).value->at(j);							
					}
				}
			}
			C_controlDuplicities(newGen->at(i).value, input);
			C_controlDuplicities(newGen->at(i + 1).value, input);
		}//for all components of tests
	}//for all tests
}

void C_getMutants(vector<TCoevIndividual>* newGen, TCgpProperties* CGPparams, TData* input){
	for(int i = (CGPparams->bestCnt + CGPparams->chldCnt); i < CGPparams->coevICnt; i++){
		newGen->at(i).fitness = 0;
		vector<int> *a = new vector<int>(CGPparams->testSize);
		newGen->at(i).value = a;
		for(int j = 0; j < CGPparams->testSize; j++){
			newGen->at(i).value->at(j) = rand() % input->dataCount;
		}
	}
}

vector<TCoevIndividual>* C_getNewGeneration(vector<TCoevIndividual>* oldGen, TCgpProperties* CGPparams, TData* input){
	vector<TCoevIndividual>* newGen = C_getBest(oldGen, CGPparams);
	C_getChildren(oldGen, newGen, CGPparams, input);
	C_getMutants(newGen, CGPparams, input);

	delete(oldGen);
	return newGen;
}

void C_changeTest(TTest* test, TCoevIndividual* newTest, TCgpProperties* CGPparams){
	vector<int>* a = new vector<int>(*newTest->value);


	pthread_mutex_lock(&test->test_sem);
	delete(test->test.value);
	test->test.value = a;
	pthread_mutex_unlock(&test->test_sem);

	return;
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
			//nahradit umelym zpozdenim...
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
		C_changeTest(params->test, &population->at(0), params->CGPparams);
		i++;
	}

	//C_writeOutPopulation(population);
}
