#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define E 2.7182818284
#define PI 3.1415926535

double function(double x, double y){
	return 10 / (5 + pow((x - 3), 2));
}


int main(){
	
	FILE *newF;
	newF = fopen("ball_1d.txt", "w+");
	//fprintf(newF, "%s\n", "400");
	fprintf(newF, "200\n");
	double y = 0;
	for(double x = -10; x < 15; x += 0.125){
			fprintf(newF, "%lf %lf\n", x,  function(x, y));
			y -= 0.1;
	}
}