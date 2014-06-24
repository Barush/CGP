#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define E 2.7182818284
#define PI 3.1415926535

double myabs(double x){
	return (x > 0)?x:(-x);
}

double function(double x, double y){
	//printf("e^(abs(%lf)) * sin(%lf) = %lf\n", x, x, exp(abs(x))*sin(x));
	return exp(myabs(x))*sin(x);
}


int main(){
	
	FILE *newF;
	newF = fopen("ex_sinx.txt", "w+");
	//fprintf(newF, "%s\n", "400");
	fprintf(newF, "200\n");
	double y = 0;
	for(double x = -10; x <= 10; x += 0.1){
			fprintf(newF, "%lf %lf\n", x,  function(x, y));
			y -= 0.1;
	}
	fclose(newF);
}