#include <stdlib.h>
#include <stdio.h>

double function(double x){
	return x*x + x*x*x;
}


int main(){
	
	FILE *newF;
	newF = fopen("testdata.txt", "w+");
	//fprintf(newF, "%s\n", "400");
	for(double x = -20; x < 20; x += 0.1){
		fprintf(newF, "%lf %lf \n", x, function(x));
	}
}