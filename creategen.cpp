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
	vector< vector<TCell> >* program = new vector< vector<TCell> >(row);
	if(program == NULL){
		geneticP->ecode = EALLOC;
		return NULL;
	}

	//make columns in all rows
	for(int i = 0; i < row; i++){
		program->at(i).resize(col);
		/*if(program->at(i) == NULL){
			geneticP->ecode = EALLOC;
			delete(program);
			return NULL;
		}*/
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
			subject->CgpProgram->at(i)[j].function = functions->funArr->at(rand() % functions->funCnt);

			if(subject->CgpProgram->at(i)[j].function == CONST){
				subject->CgpProgram->at(i)[j].input1 = rand() % CONSTCOUNT;
				subject->CgpProgram->at(i)[j].input2 = 0;
			}
			else {
				int index = j * geneticP->rows + i;		//in which cell we are
				if((index / geneticP->rows - geneticP->l_back) < 0){
					//lback is not used
					subject->CgpProgram->at(i)[j].input1 = rand() % ((index / geneticP->rows) * 
						geneticP->rows + geneticP->inCount);
					subject->CgpProgram->at(i)[j].input2 = rand() % ((index / geneticP->rows) * 
						geneticP->rows + geneticP->inCount);
				}
				else {
					//lback is in usage
					subject->CgpProgram->at(i)[j].input1 = 
						(rand() % (geneticP->rows * geneticP->l_back)) + (index / geneticP->rows - geneticP->l_back) * geneticP->rows + geneticP->inCount;
					subject->CgpProgram->at(i)[j].input2 = 
						(rand() % (geneticP->rows * geneticP->l_back)) + (index / geneticP->rows - geneticP->l_back) * geneticP->rows + geneticP->inCount;
				}
			}
		} //end of one row
	} // end of whole matrix

	if((geneticP->cols - geneticP->l_back) <= 0){
		//output can be every node
		subject->output.input1 = rand() % (geneticP->cols * geneticP->rows) + geneticP->inCount;
	}
	else{
		//output has lback restriction
		subject->output.input1 = (rand() % (geneticP->rows * geneticP->l_back)) + (geneticP->cols - geneticP->l_back) * geneticP->rows + geneticP->inCount;
	}

	return subject;
}

//create an array of individuals as a generation
vector<TIndividual>* createGeneration(TCgpProperties* geneticP, TFuncAvailable* functions){
	vector<TIndividual>* generation = new vector<TIndividual>(geneticP->individCount);
	if(generation == NULL){
		geneticP->ecode == EALLOC;
		return NULL;
	}

	for(int i = 0; i < geneticP->individCount ; i++){
		generation->at(i) = *(createIndividual(geneticP, &generation->at(i), functions));
		/*if(generation->at(i) == NULL)
			return NULL;*/
	}

	return generation;
}


void destroyGeneration(vector<TIndividual>* geneticArray, TCgpProperties* geneticP){
	for(int i = 0; i < geneticP->individCount; i++){
		delete((*geneticArray)[i].CgpProgram);
		delete((*geneticArray)[i].activeNodes);
	}
	delete(geneticArray);
	return;
}
