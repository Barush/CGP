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
		printError(geneticParams->ecode);
		int err = geneticParams->ecode;
		free(geneticParams);
		return err;
	}

	funcAv = getFunctions(argv[2], geneticParams);
	if(geneticParams->ecode != EOK){
		destroyFunctions(funcAv);
		printError(geneticParams->ecode);
		int err = geneticParams->ecode;
		free(geneticParams);
		return err;
	}

	geneticArray = createGeneration(geneticParams, funcAv);
	if(geneticParams->ecode != EOK){
		destroyFunctions(funcAv);
		printError(geneticParams->ecode);
		int err = geneticParams->ecode;
		free(geneticParams);
		return err;	
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

/***************************** EVOLUTION CYCLE *************************************/

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
		if(!(i%1000000)){
			c_fitness == (tmp_fit = C_testGlobalSolution(&geneticArray->at(0), input, geneticParams));
			c_fitness = tmp_fit;
		}
#endif
		//if counting runs for 16M generations, end it
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

	//write out results
	TIndividual* solution = &(geneticArray->at(0));
	printResult(solution, geneticParams);
	printReadableResult(solution, geneticParams);
	cerr << "Counted nodes: " << geneticParams->countedNodes << endl;

	//count statistics
	getrusage(RUSAGE_SELF, &usage);
	double tim = usage.ru_utime.tv_sec + (usage.ru_utime.tv_usec / 1000000.0);

#ifdef COEVOLUTION
	//add statistics for second thread
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

	//destroy all structures
    destroyGeneration(geneticArray, geneticParams);
    destroyData(input);
    destroyFunctions(funcAv);
    free(geneticParams);
	return EXIT_SUCCESS;
} 