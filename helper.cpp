#include <helper.h>

float dot_product (float* a, float* b, int n){
	float c=0;
	for (int i = 0; i < n; i++) {
		c+=a[i]*b[i];
	}
	return c;
}

