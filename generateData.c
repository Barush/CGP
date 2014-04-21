#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define E 2.7182818284
#define PI 3.1415926535

double function(double x, double y){
	return pow(x, 2) * pow(E, sin(x)) + x + sin(PI / pow(x, 3));
}


int main(){
	
	FILE *newF;
	newF = fopen("sums.txt", "w+");
	//fprintf(newF, "%s\n", "400");
	fprintf(newF, "200\n");
	double y = 0;
	for(double x = -10; x < 10; x += 0.1){
			fprintf(newF, "%lf %lf\n", x,  function(x, y));
			y -= 0.1;
	}
	fclose(newF);
}