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
#include <unistd.h>

void* coevolution(void *arg){
	cout << "Im in the coevolution thread" << endl;
	int i = 0;
	while(1){
		sleep(1);
		if(i == 10){
			return NULL; //np
		}
		cout << "Coevolution thread is not sleeping!" << endl;
		i++;
	}
}
