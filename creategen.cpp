/******************************************************************************/
/************************ COEVOLUTION IN CGP **********************************/
/************************* BACHELORS THESIS ***********************************/
/*********************** BARBORA SKRIVANKOVA **********************************/
/********************* xskri01@stud.fit.vutbr.cz ******************************/
/******************************************************************************/

/******************** MODUL FOR GENERATION CREATION ***************************/
/** file name: 			creategen.cpp
	creation date:		10/2013
**/

#include "creategen.h"

//alocation of a single subject of CGP
TIndividual* alocateIndividual(int row, int col, TIndividual* subject, TCgpProperties* geneticP){
	TCell** program = (TCell**)malloc(row * sizeof(TCell*));
	if(program == NULL){
		geneticP->ecode = EALLOC;
		return NULL;
	}

	subject->output = (TCell*)malloc(sizeof(struct cell));
	if(subject->output == NULL){
		geneticP->ecode = EALLOC;
		free(program);
		return NULL;
	}

	for(int i = 0; i < row; i++){
		program[i] = (TCell*)malloc(col * sizeof(TCell));
		if(program[i] == NULL){
			geneticP->ecode = EALLOC;
			free(subject->output);
			free(program);
			return NULL;
		}
	}
	
	subject->fitness = 0;
	vector<bool> *vect = new vector<bool>(geneticP->rows * geneticP->cols);	
	subject->activeNodesCount = 0;
	subject->activeNodes = vect;
	subject->CgpProgram = program;
	
	return subject;
}

//fill in the CGP matrix
TIndividual* createIndividual(TCgpProperties* geneticP, TIndividual *subject, TFuncAvailable* functions){
	alocateIndividual(geneticP->rows, geneticP->cols, subject, geneticP);
	if(geneticP->ecode != EOK)
		return NULL;

	for(int i = 0; i < geneticP->rows; i++){
		for(int j = 0; j < geneticP->cols; j++){
			subject->CgpProgram[i][j].function = functions->funArr[rand() % functions->funCnt];
			if(subject->CgpProgram[i][j].function == CONST){
				subject->CgpProgram[i][j].input1 = rand() % CONSTCOUNT;
				subject->CgpProgram[i][j].input2 = 0;
			}
			else {
				int index = j * geneticP->rows + i;		//in which cell we are
				if((index / geneticP->rows - geneticP->l_back) < 0){
					subject->CgpProgram[i][j].input1 = rand() % ((index / geneticP->rows) * 
						geneticP->rows + geneticP->inCount);
					subject->CgpProgram[i][j].input2 = rand() % ((index / geneticP->rows) * 
						geneticP->rows + geneticP->inCount);
				}
				else {
					subject->CgpProgram[i][j].input1 = 
						(rand() % (geneticP->rows * geneticP->l_back)) + (index / geneticP->rows - geneticP->l_back) * geneticP->rows + geneticP->inCount;
					subject->CgpProgram[i][j].input2 = 
						(rand() % (geneticP->rows * geneticP->l_back)) + (index / geneticP->rows - geneticP->l_back) * geneticP->rows + geneticP->inCount;
				}
			}
		} //end of one row
	} // end of whole matrix
	if((geneticP->cols - geneticP->l_back) <= 0){
		subject->output->input1 = rand() % (geneticP->cols * geneticP->rows) + geneticP->inCount;
	}
	else{
		subject->output->input1 = (rand() % (geneticP->rows * geneticP->l_back)) + (geneticP->cols - geneticP->l_back) * geneticP->rows + geneticP->inCount;
	}

	return subject;
}

//create an array of individuals as a generation
TIndividual* createGeneration(TCgpProperties* geneticP, TFuncAvailable* functions){
	TIndividual* generation = NULL;
	if((generation = (TIndividual*)malloc(geneticP->individCount * sizeof(struct individual))) == NULL){
		geneticP->ecode == EALLOC;
		return NULL;
	}

	for(int i = 0; i < geneticP->individCount ; i++){
		generation[i] = *(createIndividual(geneticP, &(generation[i]), functions));
	}

	return generation;
}


void destroyGeneration(TIndividual** geneticArray, TCgpProperties* geneticP){
	for(int i = 0; i < geneticP->individCount; i++){
		for(int j = 0; j < geneticP->rows; j++){
			//destroy each line
			free((*geneticArray)[i].CgpProgram[j]);
		}
		free((*geneticArray)[i].CgpProgram);
		free((*geneticArray)[i].output);
		delete((*geneticArray)[i].activeNodes);
	}
	free(*geneticArray);
	return;
}
