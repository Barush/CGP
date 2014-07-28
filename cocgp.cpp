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

void changeArchive(int index, TArchive* archive, TIndividual* genotype, TCgpProperties* params){
	pthread_mutex_lock(&archive->arch_sem);
	copyGenotype(genotype, &archive->arch[index], params);
	pthread_mutex_unlock(&archive->arch_sem);

	return;
}

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

int main(int argc, char** argv){

/************************** INITIALIZATIONS **********************************/

	vector<TIndividual>* geneticArray;		//array for one generation
	TCgpProperties* geneticParams;	//parameters of CGP
	TData* input;					//matrix of input-output data
	TFuncAvailable* funcAv;			//struct with array of used functions
	int fitness = 0, gener = 0;		//vars used to know how good cgp works
#ifdef COEVOLUTION
	int fitCh_ind = 0, nGen_ind = 0;//variables for archive indexes
	int c_fitness = 0, tmp_fit;
#endif
 	
	// initiate random generator
 	struct timeval time;
    gettimeofday(&time,NULL);
    // nastaveni promene pro generovani nahodnych cisel
    srand((time.tv_sec * 1000) + (time.tv_usec / 1000));

	struct rusage usage, childusage;

	if(!strcmp(argv[1], "--help")){
		//parameter help
		printUsage();
		return EXIT_SUCCESS;
	}

	geneticParams = getParams(argv, argc);
	if(geneticParams->ecode != EOK){
		free(geneticParams);
		printError(geneticParams->ecode);
		return geneticParams->ecode;
	}

	funcAv = getFunctions(argv[2], geneticParams);
	if(geneticParams->ecode != EOK){
		destroyFunctions(funcAv);
		free(geneticParams);
		printError(geneticParams->ecode);
		return geneticParams->ecode;
	}

	geneticArray = createGeneration(geneticParams, funcAv);
	if(geneticParams->ecode != EOK){
		destroyFunctions(funcAv);
		free(geneticParams);
		printError(geneticParams->ecode);
		return geneticParams->ecode;		
	}	

	input = getData(argv[1], geneticParams);
	if(geneticParams->ecode != EOK){
		destroyData(input);
		destroyGeneration(geneticArray, geneticParams);
		destroyFunctions(funcAv);
		printError(geneticParams->ecode);
		int err = geneticParams->ecode;
		free(geneticParams);
		return err;
	}

#ifdef COEVOLUTION
	//COEV: initiate the second thread
	TCoevParams* params = paramsInit(geneticParams, geneticArray, funcAv, input);
	pthread_t coevolution_var;
	pthread_create(&coevolution_var, NULL, coevolution, (void *)params);
#endif

/***************************** EVOLUTION *************************************/

	for(int i = 0;; i++){
		
#ifdef COEVOLUTION
		evolutionStep(input, geneticParams, geneticArray, funcAv, params->test);
#else
		evolutionStep(input, geneticParams, geneticArray, funcAv, NULL);
#endif

		//every hundred generations write out actual state,
		//COEV: let second thread to do a step and save ind. to archive
		if(!(i%100)){
			cout << i << " " << geneticArray->at(0).fitness << endl;
#ifdef COEVOLUTION
			int arch_index = 0;
			switch(geneticParams->archiveSize){
				case 1: arch_index = (nGen_ind%geneticParams->individCount + geneticParams->individCount) / 2;
						break;
				case 2: arch_index = (nGen_ind%geneticParams->individCount + geneticParams->individCount);
						break;
				case 3: arch_index = (int)((nGen_ind%geneticParams->individCount + geneticParams->individCount) * 1.5);
			}
			changeArchive(arch_index,params->archive, &geneticArray->at(0), geneticParams);
			nGen_ind++;
			pthread_mutex_lock(&params->memory->cont_sem);
				params->memory->cont = true;
			pthread_mutex_unlock(&params->memory->cont_sem);
#endif
		}

#ifdef COEVOLUTION
		//COEV: every milion generations check and save the global fitness
		//if it didnt change since last time, end counting
		if(!(i%1600000) && i > 0){
			if(c_fitness == (tmp_fit = C_testGlobalSolution(&geneticArray->at(0), input, geneticParams))){
				//break;
			}
			//else{
				c_fitness = tmp_fit;
			//}
		}
#endif
		//if counting runs for 20M generations, end it
		if(i > 16000000){
#ifdef COEVOLUTION
			cout << i + 1 << " " << C_testGlobalSolution(&geneticArray->at(0), input, geneticParams) << endl;
#endif
			break;
		}


		//if fitness changed, save it
		//COEV: change archive
		if(geneticArray->at(0).fitness != fitness){
			fitness = geneticArray->at(0).fitness;
			gener = i;
#ifdef COEVOLUTION
			changeArchive(fitCh_ind%geneticParams->individCount, params->archive, &geneticArray->at(0), geneticParams);
			fitCh_ind++;
#endif
		}
		//if fitness didnt change for milion geners, end it
		//if((i - gener) > 1000000){
		//	break;
		//}

#ifdef COEVOLUTION
		//COEV: if reached maximal fitness, test if has global solution
		if(geneticArray->at(0).fitness == geneticParams->testSize){
			if(C_testGlobalSolution(&geneticArray->at(0), input, geneticParams) > (int)(0.97 * input->dataCount)){
				cout << i + 1 << " " << input->dataCount << endl;
				break;
			}
		}
#else
		//if reached maximal fitness, end it
		if(geneticArray->at(0).fitness > (int)(0.97 * input->dataCount)){
			cout << i + 1 << " " << input->dataCount << endl;
			break;
		}
#endif
	}

//**************************** TIDING UP *************************************/

#ifdef COEVOLUTION
	//ending of second thread
	pthread_mutex_lock(&params->memory->cont_sem);
		params->memory->cont = true;
	pthread_mutex_unlock(&params->memory->cont_sem);
	pthread_mutex_lock(&params->memory->end_sem);
	params->memory->end = true;
	pthread_mutex_unlock(&params->memory->end_sem);
#endif

	TIndividual* solution = &(geneticArray->at(0));
	printResult(solution, geneticParams);
	printReadableResult(solution, geneticParams);
	cerr << "Counted nodes: " << geneticParams->countedNodes << endl;
	getrusage(RUSAGE_SELF, &usage);
	double tim = usage.ru_utime.tv_sec + (usage.ru_utime.tv_usec / 1000000.0);
#ifdef COEVOLUTION
	getrusage(RUSAGE_CHILDREN, &childusage);
	double childtime = childusage.ru_utime.tv_sec + (childusage.ru_utime.tv_usec / 1000000.0);
	tim += childtime;
#endif
	cerr << "CPU time (s): " << tim  << endl;

#ifdef COEVOLUTION
	//waiting till second thread finishes
	int retval = 0;
//	while((retval = pthread_tryjoin_np(coevolution_var, NULL)) != 0);
	//m_unmap(archive, test)
	//shm_unlink()
#endif	

    destroyGeneration(geneticArray, geneticParams);
    destroyData(input);
    destroyFunctions(funcAv);
    free(geneticParams);
	return EXIT_SUCCESS;
} 