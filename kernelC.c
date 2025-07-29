#include <math.h>

void kernelInC(const float *x1, const float *x2, const float *y1, const float *y2, float *z, int n) {
	for (int i = 0; i < n; i++) {
		float dx = x1[i] - x2[i];
		float dy = y1[i] - y2[i];
		z[i] = sqrtf(dx * dx + dy * dy);
	}

}