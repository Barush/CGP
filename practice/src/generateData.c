/******************************************************************************/
/************************ COEVOLUTION IN CGP **********************************/
/************************* BACHELORS THESIS ***********************************/
/*********************** BARBORA SKRIVANKOVA **********************************/
/********************* xskri01@stud.fit.vutbr.cz ******************************/
/******************************************************************************/

/*********** SEPARATED PROGRAM USED TO GENERATE TRAINING VECTORS **************/
/** file name: 			generateData.c
	creation date:		12/2013
**/


#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define E 2.7182818284
#define PI 3.1415926535

double myAbs(double x){
	return (x > 0)?x:(-x);
}

double f1(double x, double y){
	return x*x - x*x*x;
}


double f2(double x, double y){
	return exp(myAbs(x))*sin(x);
}

double f3(double x, double y){
	return x*x*exp(sin(x)) + x + sin(PI/3);
}

double f4(double x, double y){
	return exp(-x)*pow(x, 3)*cos(x)*sin(x)*( cos(x)*pow(sin(x), 2) - 1 );
}

double f5(double x, double y){
	return 10 / (5 + pow(x-3, 2));
}


int main(){
	
	FILE *newF;
	newF = fopen("ex_sinx.txt", "w+");
	//fprintf(newF, "%s\n", "400");
	fprintf(newF, "200\n");
	double y = 0;
	for(double x = -10; x <= 10; x += 0.1){
			fprintf(newF, "%lf %lf\n", x,  f2(x, y));
			y -= 0.1;
	}
	fclose(newF);
}