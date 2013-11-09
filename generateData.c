#include <stdlib.h>
#include <stdio.h>

double function(double x, double y){
	return x*x + y*y - x;
}


int main(){
	
	FILE *newF;
	newF = fopen("testdata.txt", "w+");
	//fprintf(newF, "%s\n", "400");
	fprintf(newF, "400\n");
	double y = 20;
	for(double x = -20; x < 20; x += 0.1){
			fprintf(newF, "%lf %lf %lf\n", x, y,  function(x, y));
			y -= 0.1;
	}
}