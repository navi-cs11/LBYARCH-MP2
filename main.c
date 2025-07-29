#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
extern void mainG();

int main(int argc, char *argv[]) {
	int n = 1 << 25; //this part is where you manually set the number of iterations to be made (currently 2^25)
	// sir said the target is 2^30 but if device can't handle it just lower it a little bit to 29,28,27
	//expect the higher the number the slower the results in the command prompt
	float* x1 = malloc(n * sizeof(float));
	float* y1 = malloc(n * sizeof(float));
	float* x2 = malloc(n * sizeof(float));
	float* y2 = malloc(n * sizeof(float));
	float* z = malloc(n * sizeof(float));

	srand((unsigned)time(NULL));
	for (int i = 0; i < n; i++) {
		x1[i] = (float)rand()*1000.0f;
		y1[i] = (float)rand()*1000.0f;
		x2[i] = (float)rand()*1000.0f;
		y2[i] = (float)rand()*1000.0f;

	}

	int runs = 30;
	double totalTime = 0.0;

	for (int i = 0; i < runs; i++) {
		clock_t start = clock();


		kernelInC(x1, x2, y1, y2, z, n);

		for (int j = 0; j < 5; j++) {
			printf("\nz[%d] = %f\n", j, z[j]);
		}
		clock_t end = clock();
		totalTime += (double)(end - start) / CLOCKS_PER_SEC;
		printf("%d %f", i+1, totalTime / runs);
	}
	//printf("HELLO VS CODE");
	mainG();
	return 0;
}