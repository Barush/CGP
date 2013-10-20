#include <stdlib.h>
#include <stdio.h>

double function(double x, double y, double z){
	return x*y + x*x*x - z;
}


int main(){
	
	FILE *newF;
	newF = fopen("testdata.txt", "w+");
	//fprintf(newF, "%s\n", "400");
	fprintf(newF, "400");
	double y = 5;
	for(double x = -20; x < 20; x += 0.1, y --){
			double z = x * y;
			fprintf(newF, "%lf %lf %lf %lf\n", x, y, z, function(x, y, z));
	}
}