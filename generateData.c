#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define E 2.7182818284
#define PI 3.1415926535

double function(double x, double y){
	return pow(E, -x)*pow(x, 3)*sin(x)*cos(x)*(pow(sin(x), 2)*cos(x) - 1);
}


int main(){
	
	FILE *newF;
	newF = fopen("salustowitz.txt", "w+");
	//fprintf(newF, "%s\n", "400");
	fprintf(newF, "200\n");
	double y = 0;
	for(double x = 0; x <= 10; x += 0.05){
			fprintf(newF, "%lf %lf\n", x,  function(x, y));
			y -= 0.1;
	}
	fclose(newF);
}