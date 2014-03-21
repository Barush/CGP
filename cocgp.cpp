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
#include "coevolution.h"

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

TShared* memoryInit(){
	TShared* mem = NULL;
	int descriptor;

	descriptor = shm_open("ending", O_RDWR|O_CREAT, 0600);
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

TArchive* archiveInit(TCgpProperties* geneticP, TIndividual* genArray, TFuncAvailable* funcAv){
	TArchive* archive = NULL;
	int descriptor;
	TIndividual* secArray;

	descriptor = shm_open("archive", O_RDWR|O_CREAT, 0600);
	ftruncate(descriptor, sizeof(TArchive));
	archive = (TArchive*)mmap(NULL, sizeof(TArchive), PROT_READ|PROT_WRITE, MAP_SHARED, descriptor, 0);

	pthread_mutex_init(&archive->arch_sem, NULL);

	secArray = createGeneration(geneticP, funcAv);

	pthread_mutex_lock(&archive->arch_sem);
		archive->arch = (TIndividual*)malloc(2 * geneticP->individCount * sizeof(struct individual));
		for(int i = 0; i < (2*geneticP->individCount); i++){
			alocateIndividual(geneticP->rows, geneticP->cols, &archive->arch[i], geneticP);
			if(i < geneticP->individCount){
				copyGenotype(&genArray[i], &archive->arch[i], geneticP);
			}
			else{
				copyGenotype(&secArray[i - geneticP->individCount], &archive->arch[i], geneticP);
			}
		}
	pthread_mutex_unlock(&archive->arch_sem);

	destroyGeneration(&secArray, geneticP);
	return archive;
}

TTest* testInit(TData* input){
	TTest* test = NULL;
	int descriptor;

	descriptor = shm_open("test", O_RDWR|O_CREAT, 0600);
	ftruncate(descriptor, sizeof(TTest));
	test = (TTest*)mmap(NULL, sizeof(TTest), PROT_READ|PROT_WRITE, MAP_SHARED, descriptor, 0);

	pthread_mutex_init(&test->test_sem, NULL);

	vector<int>* a = new vector<int>(10);
	pthread_mutex_lock(&test->test_sem);
		test->test.fitness = 0;
		test->test.value = a;
		for(int i = 0; i < 10; i++)
			test->test.value->at(i) = rand() % input->dataCount;
	pthread_mutex_unlock(&test->test_sem);

	return test;
}

void changeArchive(int index, TArchive* archive, TIndividual* genotype, TCgpProperties* params){
	pthread_mutex_lock(&archive->arch_sem);
	copyGenotype(genotype, &archive->arch[index], params);
	pthread_mutex_unlock(&archive->arch_sem);

	return;
}

TCoevParams* paramsInit(TCgpProperties* geneticP, TIndividual* geneticArray, TFuncAvailable* funcAv, TData* input){
	TCoevParams* params = (TCoevParams*)malloc(sizeof(struct coevParams));
	params->memory = memoryInit();
	params->CGPparams = geneticP;
	params->funcAv = funcAv;
	params->archive = archiveInit(geneticP, geneticArray, funcAv);
	params->test = testInit(input);
	params->input = input;

	return params;
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

#ifdef COEVOLUTION
	//variables for archive indexes
	int fitCh_ind = 0, nGen_ind = 0;
#endif

	// TODO: make argv controls

	srand(time(NULL)); // initiate random generator
	geneticParams = getParams(argv, argc);
	funcAv = getFunctions(argv[2]);
	geneticArray = createGeneration(geneticParams, funcAv);

	input = getData(argv[1], geneticParams);

#ifdef COEVOLUTION
	TCoevParams* params = paramsInit(geneticParams, geneticArray, funcAv, input);
	pthread_t coevolution_var;
	pthread_create(&coevolution_var, NULL, coevolution, (void *)params);
#endif

	for(int i = 0;; i++){
#ifdef COEVOLUTION
		evolutionStep(input, geneticParams, geneticArray, funcAv, params->test);
#else
		evolutionStep(input, geneticParams, geneticArray, funcAv, NULL);
#endif
		//every hundred generations write out actual state,
		//let second thread to do a step and save ind. to archive
		if(!(i%100)){
			cout << i << " " << geneticArray[0].fitness << endl;
#ifdef COEVOLUTION
			changeArchive((nGen_ind%geneticParams->individCount + geneticParams->individCount),
			 params->archive, &geneticArray[0], geneticParams);
			nGen_ind++;
			pthread_mutex_lock(&params->memory->cont_sem);
				params->memory->cont = true;
			pthread_mutex_unlock(&params->memory->cont_sem);
#endif
		}

		//if fitness changed, save it and change archive
		if(geneticArray[0].fitness != fitness){
			fitness = geneticArray[0].fitness;
			gener = i;
#ifdef COEVOLUTION
			changeArchive(fitCh_ind%geneticParams->individCount, params->archive, &geneticArray[0], geneticParams);
			fitCh_ind++;
#endif
		}
		//if fitness didnt change for milion gens, end it
		if((i - gener) > 1000000){
			break;
		}
		//if reached maximal fitness, end it
		if(geneticArray[0].fitness == input->dataCount){
			cout << i + 1 << " " << input->dataCount << endl;
			break;
		}
	}

#ifdef COEVOLUTION
	//ending of second thread
	pthread_mutex_lock(&params->memory->cont_sem);
		params->memory->cont = true;
	pthread_mutex_unlock(&params->memory->cont_sem);
	pthread_mutex_lock(&params->memory->end_sem);
	params->memory->end = true;
	pthread_mutex_unlock(&params->memory->end_sem);
#endif

	TIndividual* solution = &(geneticArray[0]);
	printResult(solution, geneticParams);
	printReadableResult(solution, geneticParams);
	cerr << "Counted nodes: " << geneticParams->countedNodes << endl;

#ifdef COEVOLUTION
	//waiting while second thread doesnt finish
	int retval = 0;
	while((retval = pthread_tryjoin_np(coevolution_var, NULL)) != 0);
#endif	

    destroyGeneration(&geneticArray, geneticParams);
    destroyData(input);
    destroyFunctions(funcAv);
    free(geneticParams);
	return EXIT_SUCCESS;
} 
