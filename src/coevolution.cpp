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

/******************************************************************************
	Function memoryInit - creates the shared memory objects for a variant with
		coevolution
	Takes parameters:
		--
******************************************************************************/
TShared* memoryInit(){
	TShared* mem = NULL;
	int descriptor;

	descriptor = shm_open("ending01", O_RDWR|O_CREAT, 0600);
	ftruncate(descriptor, sizeof(TShared));
	mem = (TShared*)mmap(NULL, sizeof(TShared), PROT_READ|PROT_WRITE, MAP_SHARED,descriptor, 0);

	pthread_mutex_init(&mem->end_sem, NULL);
	pthread_mutex_lock(&mem->end_sem);
		mem->end = false;
	pthread_mutex_unlock(&mem->end_sem);

	pthread_mutex_init(&mem->cont_sem, NULL);
	pthread_mutex_lock(&mem->cont_sem);
		mem->cont = false;
	pthread_mutex_unlock(&mem->cont_sem);
	
	return mem;
}


/***********************************************************************
	Function ArchiveInit - cerates shared memory object and fills it 
		with data from generated archive
	Takes parameters:
		@geneticP - pointer to a structure of params of CGP
		@genArray - vector of candidate solutions
		@funcAv - pointer to an array of available functions
***********************************************************************/
TArchive* archiveInit(TCgpProperties* geneticP, vector<TIndividual>* genArray, TFuncAvailable* funcAv){
	TArchive* archive = NULL;
	int descriptor;
	vector<TIndividual>* nextArray;

	descriptor = shm_open("archive01", O_RDWR|O_CREAT, 0600);
	ftruncate(descriptor, sizeof(TArchive));
	archive = (TArchive*)mmap(NULL, sizeof(TArchive), PROT_READ|PROT_WRITE, MAP_SHARED, descriptor, 0);

	pthread_mutex_init(&archive->arch_sem, NULL);

	pthread_mutex_lock(&archive->arch_sem);
		archive->arch = (TIndividual*)malloc(geneticP->archiveSize * geneticP->individCount * sizeof(struct individual));
		for(int i = 0; i < (geneticP->archiveSize*geneticP->individCount); i++){
			alocateIndividual(geneticP->rows, geneticP->cols, &archive->arch[i], geneticP);
			if(i < geneticP->individCount){
				copyGenotype(&genArray->at(i), &archive->arch[i], geneticP);
			}
			else if(!(i % geneticP->individCount)){
				if(i == geneticP->individCount){
					nextArray = createGeneration(geneticP, funcAv);
					copyGenotype(&nextArray->at(i%geneticP->individCount), &archive->arch[i], geneticP);
				}
				else{
					destroyGeneration(nextArray, geneticP);
					nextArray = createGeneration(geneticP, funcAv);
					copyGenotype(&nextArray->at(i%geneticP->individCount), &archive->arch[i], geneticP);
				}
			}
			else if (i > geneticP->individCount){
				copyGenotype(&nextArray->at(i%geneticP->individCount), &archive->arch[i], geneticP);
			}
		}
	pthread_mutex_unlock(&archive->arch_sem);

	if(geneticP->archiveSize > 1)
		destroyGeneration(nextArray, geneticP);
	return archive;
}

/***********************************************************************
	Function testInit - creates individuals for the coevolution population
	Takes parameters:
		@input - pointer to an array of input data
		@params - pointer to a structure of params of CGP
***********************************************************************/
TTest* testInit(TData* input, TCgpProperties* params){
	TTest* test = NULL;
	int descriptor;

	descriptor = shm_open("test01", O_RDWR|O_CREAT, 0600);
	ftruncate(descriptor, sizeof(TTest));
	test = (TTest*)mmap(NULL, sizeof(TTest), PROT_READ|PROT_WRITE, MAP_SHARED, descriptor, 0);

	pthread_mutex_init(&test->test_sem, NULL);

	vector<int>* a = new vector<int>(params->testSize);
	for(int i = 0; i < params->testSize; i++)
		a->at(i) = rand() % input->dataCount;

	pthread_mutex_lock(&test->test_sem);
		test->test.fitness = 0;
		test->test.value = a;
	pthread_mutex_unlock(&test->test_sem);

	return test;
}


/***********************************************************************
	Function changeArchive - function which changes one individual in
		archive of candidate solutions
	Takes parameters:
		@index - index of individual to change in the archive
		@archive - pointer to a shared memory object of archive
		@genotype - new individual to the position
		@params - pointer to a structure of params of CGP
***********************************************************************/
void changeArchive(int index, TArchive* archive, TIndividual* genotype, TCgpProperties* params){
	pthread_mutex_lock(&archive->arch_sem);
	copyGenotype(genotype, &archive->arch[index], params);
	pthread_mutex_unlock(&archive->arch_sem);

	return;
}


/***********************************************************************
	Function paramsInit - function which initiates all object necessary
		for coevolutive variant of this programm
	Takes parameters:
		@geneticP - pointer to a structure of params of CGP
		@geneticArray - vector of population of CGP
		@funcAv - pointer to an array of available functions
		@input - pointer to an array of training vectors
***********************************************************************/
TCoevParams* paramsInit(TCgpProperties* geneticP, vector<TIndividual>* geneticArray, TFuncAvailable* funcAv, TData* input){
	TCoevParams* params = (TCoevParams*)malloc(sizeof(struct coevParams));
	params->memory = memoryInit();
	params->CGPparams = geneticP;
	params->funcAv = funcAv;
	params->archive = archiveInit(geneticP, geneticArray, funcAv);
	params->test = testInit(input, geneticP);
	params->input = input;

	return params;
}

/***********************************************************************
	Function C_testGlobalSolution - function which count fitness of an
		individual from all training vectors
	Takes parameters:
		@solution - pointer to the solution to find fitness of
		@input - pointer to array of all training vectors
		@geneticP - pointer to a structure of params of CGP
***********************************************************************/
int C_testGlobalSolution(TIndividual* solution, TData* input, TCgpProperties* geneticP){
	resetFitness(solution);
	for(int i = 0; i < input->dataCount; i++){
		getValue(solution, geneticP, input->data[i]);
		getFitness(solution, geneticP, input->data[i]);
	}

	return solution->fitness;
}

/***********************************************************************
	Function C_controlDuplicities - function, which controls and removes
		duplicities in the individual of coevolution population
	Takes parameters:
		@test - vector of the individual
		@input - pointer to an array of all training vectors
***********************************************************************/
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


/***********************************************************************
	Function C_generatePopulation - function which creates a population
		for coevolution thread and calls the function for controlling
		duplicities in each individual
	Takes parameters:
		@CGPparams - pointer to a structure of params of CGP
		@input - pointer to an array of all training vectors
***********************************************************************/
vector<TCoevIndividual>* C_generatePopulation(TCgpProperties* CGPparams, TData* input){
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


/***********************************************************************
	Function C_writeOutPopulation - function which writes whole population
		to the standard output. Used only for debugging.
	Takes parameters:
		@population - vector of individuals
***********************************************************************/
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


/***********************************************************************
	Function C_evaluatePopulation - function, which gets fitness of whole
		coevolution population by interaction with candidate solutions in
		archive
	Takes parameters:
		@population - vector of all individuals
		@input - pointer to an array of all training vectors
		@archive - pointer to an archive of candidate solutions
		@params - pointer to a structure of params of CGP
***********************************************************************/
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

/***********************************************************************
	Function comp - used as callback function for sort function
***********************************************************************/
bool comp(TCoevIndividual i, TCoevIndividual j){
	return (i.fitness < j.fitness);
}

/***********************************************************************
	Function C_getBest - returns as much best individuals, as is set in
		CGPparams.coevICnt
	Takes parameters:
		@oldGen - vector of all individuals
		@CGPparams - pointer to a structure of params of CGP
***********************************************************************/
vector<TCoevIndividual>* C_getBest(vector<TCoevIndividual>* oldGen, TCgpProperties* CGPparams){
	sort(oldGen->begin(), oldGen->end(), comp);
	vector<TCoevIndividual>* newGen = new vector<TCoevIndividual>(CGPparams->coevICnt);

	for(int i = 0; i < CGPparams->coevICnt; i++){
		newGen->at(i) = oldGen->at(i);
	}

	return newGen;
}

/***********************************************************************
	Function C_getParent - realizes one competition of randomly selected
		individuals to find parents
	Takes parameters:
		@population - vector of individuals
		@CGPparams - pointer to a structure of params of CGP
***********************************************************************/
int C_getParent(vector<TCoevIndividual>* population, TCgpProperties* CGPparams){
	int ind1, ind2;

	ind1 = rand() % CGPparams->coevICnt;
	ind2 = rand() % CGPparams->coevICnt;

	return (population->at(ind1).fitness < population->at(ind2).fitness)?ind1:ind2;
}

/***********************************************************************
	Function C_getChildren - function, which gets fitness of whole
		coevolution population by interaction with candidate solutions in
		archive
	Takes parameters:
		@population - vector of individuals
		@input - pointer to an array of all training vectors
		@archive - pointer to an archive of candidate solutions
		@params - pointer to a structure of params of CGP
***********************************************************************/
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
					//switching the higher half of genotype
					newGen->at(i).value->at(j) = oldGen->at(parent2).value->at(j);
					newGen->at(i+1).value->at(j) = oldGen->at(parent1).value->at(j);	
				}
			}
			else {
				if(j > crossPts[0] && j < crossPts[1]){
					//switching  the middle part of genotype
					newGen->at(i).value->at(j) = oldGen->at(parent2).value->at(j);
					newGen->at(i+1).value->at(j) = oldGen->at(parent1).value->at(j);	
				}
				if(CGPparams->hybridPoints == 3){
					if(j > crossPts[2]){
						//switching the fourth part of genotype
						newGen->at(i).value->at(j) = oldGen->at(parent2).value->at(j);
						newGen->at(i+1).value->at(j) = oldGen->at(parent1).value->at(j);							
					}
				}
			}
			C_controlDuplicities(newGen->at(i).value, input);
			C_controlDuplicities(newGen->at(i + 1).value, input);
		}//for all components of tests
	}//for all children tests
}

/***********************************************************************
	Function C_getMutants - creates the new, randomly generated individuals
		into the coevolution population
	Takes parameters:
		@newGen - vector of individuals from new generation
		@CGPparams - pointer to a structure of params of CGP
		@input - pointer to an array of all training vectors
***********************************************************************/
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


/***********************************************************************
	Function C_getNewGeneration - creates new generation by the set
		parameters
	Takes parameters:
		@oldGen - vector of individuals from old generation
		@CGPparams - pointer to a structure of params of CGP
		@input - pointer to an array of all training vectors
***********************************************************************/
vector<TCoevIndividual>* C_getNewGeneration(vector<TCoevIndividual>* oldGen, TCgpProperties* CGPparams, TData* input){
	vector<TCoevIndividual>* newGen = C_getBest(oldGen, CGPparams);
	C_getChildren(oldGen, newGen, CGPparams, input);
	C_getMutants(newGen, CGPparams, input);

	delete(oldGen);
	return newGen;
}

/***********************************************************************
	Function C_changeTest - loads a new test into shared memory object
		used for evolution of candidate solutions
	Takes parameters:
		@test - the shared memory object where test is saved
		@newTest - the test chosen from the last generation of coev
		@CGPparams - pointer to a structure of params of CGP
***********************************************************************/
void C_changeTest(TTest* test, TCoevIndividual* newTest, TCgpProperties* CGPparams){
	vector<int>* a = new vector<int>(*newTest->value);


	pthread_mutex_lock(&test->test_sem);
	delete(test->test.value);
	test->test.value = a;
	pthread_mutex_unlock(&test->test_sem);

	return;
}

/***********************************************************************
	Function coevolution - the main function for the coevolution thread
	Takes parameters:
		@par - pointer to a shared memory object with all parameters
***********************************************************************/
void* coevolution(void* par){
	srand(time(NULL));

	TCoevParams* params = (TCoevParams*) par;
	vector<TCoevIndividual> *population = C_generatePopulation(params->CGPparams, params->input);

	int i = 0;

	while(1){	
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
		while(1){
			if(params->memory->cont)
				break;
		}
	}
}
