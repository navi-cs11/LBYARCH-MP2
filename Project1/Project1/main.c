#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
extern void mainG(const float* x1, const float* x2, const float* y1, const float* y2, float* z, int n);
void kernelInC(const float* x1, const float* x2, const float* y1, const float* y2, float* z, int n);

int main(int argc, char* argv[]) {

	int n;
	printf("Enter N: ");
	scanf("%d", &n);
	n = 1 << n; //this part is where you manually set the number of iterations to be made (currently 2^25)
	// sir said the target is 2^30 but if device can't handle it just lower it a little bit to 29,28,27
	//expect the higher the number the slower the results in the command prompt

	float* x1 = malloc(n * sizeof(float));
	float* y1 = malloc(n * sizeof(float));
	float* x2 = malloc(n * sizeof(float));
	float* y2 = malloc(n * sizeof(float));
	float* c_z = malloc(n * sizeof(float));
	float* asm_z = malloc(n * sizeof(float));

	srand((unsigned)time(NULL));
	for (int i = 0; i < n; i++) {
		x1[i] = (float)rand() * 1000.0f;
		y1[i] = (float)rand() * 1000.0f;
		x2[i] = (float)rand() * 1000.0f;
		y2[i] = (float)rand() * 1000.0f;

	}

	int runs = 30;
	double c_totalTime = 0.0;
	double asm_totalTime = 0.0;

	for (int i = 0; i < runs; i++) {
		// C version
		clock_t start = clock();
		kernelInC(x1, x2, y1, y2, c_z, n);
		clock_t end = clock();
		double c_time = (double)(end - start) / CLOCKS_PER_SEC;
		c_totalTime += c_time;

		// ASM version
		start = clock();
		mainG(x1, x2, y1, y2, asm_z, n);
		end = clock();
		double asm_time = (double)(end - start) / CLOCKS_PER_SEC;
		asm_totalTime += asm_time;

		printf("Run %d: C=%f sec, ASM=%f sec, Speedup=%fx\n",
			i + 1, c_time, asm_time, c_time / asm_time);
	}

	printf("\nFirst 10 elements of vector Z:\n");
	printf("Index\tC Version\tASM Version\n");
	printf("---------------------------------\n");
	for (int i = 0; i < 10 && i < n; i++) {
		printf("[%d]\t%f\t%f\n", i, c_z[i], asm_z[i]);
	}

	double avg_c_time = c_totalTime / runs;
	double avg_asm_time = asm_totalTime / runs;

	printf("\nFinal averages (%d runs):\n", runs);
	printf("C version avg: %f sec\n", avg_c_time);
	printf("ASM version avg: %f sec\n", avg_asm_time);
	printf("Average speedup: %fx\n", avg_c_time / avg_asm_time);

	return 0;
}