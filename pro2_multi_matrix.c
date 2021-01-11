
#include<omp.h>
#include<stdio.h>
#include<stdlib.h>


int main() {
	int** arr1, ** arr2, ** arr3;
	int size = 1000;
	int i, j, k;

	// Init
	arr1 = (int**)malloc(size * sizeof(int*));
	for (i = 0; i < size; i++)
		arr1[i] = (int*)malloc(size * sizeof(int));

	arr2 = (int**)malloc(size * sizeof(int*));
	for (i = 0; i < size; i++)
		arr2[i] = (int*)malloc(size * sizeof(int));

	arr3 = (int**)malloc(size * sizeof(int*));
	for (i = 0; i < size; i++)
		arr3[i] = (int*)malloc(size * sizeof(int));

	// Assigning values
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++)
			arr1[i][j] = (i + 1) * (j + 1);
	}

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++)
			arr2[i][j] = (i + 1) * (j + 1);
	}

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++)
			arr3[i][j] = 0;
	}


double t1 = omp_get_wtime();
#pragma omp parallel for private(j, k) num_threads(16)
	// Multiplication
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			int sum = 0;
			for (k = 0; k < size; k++) {
				sum += arr1[i][k] * arr2[k][j];
			}
			arr3[i][j] = sum;
		}
	}
	double t2 = omp_get_wtime();
	printf("time take with openmp %lf \n", t2-t1);


	t1 = omp_get_wtime();

	// Multiplication
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			int sum = 0;
			for (k = 0; k < size; k++) {
				sum += arr1[i][k] * arr2[k][j];
			}
			arr3[i][j] = sum;
		}
	}
	t2 = omp_get_wtime();
	printf("time take without openmp %lf \n", t2-t1);
}

/**
int main() {

	int r = 500, c = 500, i, j, count = 0, sum = 0, k;
	//dynamically allocate arrays

	int** arr1 = (int**)malloc(r * sizeof(int*));
	for (i = 0; i < r; i++)
		arr1[i] = (int*)malloc(c * sizeof(int));
	int** arr2 = (int**)malloc(r * sizeof(int*));
	for (i = 0; i < r; i++)
		arr2[i] = (int*)malloc(c * sizeof(int));
	int** arr3 = (int**)malloc(r * sizeof(int*));
	for (i = 0; i < r; i++)
		arr3[i] = (int*)malloc(c * sizeof(int));

	for (i = 0; i < r; i++)
		for (j = 0; j < c; j++)
			arr1[i][j] = count++;

	for (i = 0; i < r; i++)
		for (j = 0; j < c; j++)
			arr2[i][j] = count++;
	double x = omp_get_wtime();
	omp_set_num_threads(2);
#pragma omp parallel for private(j, k)
	for (i = 0; i < r; i++)
		for (j = 0; j < c; j++)
			for (k = 0; k < r; k++)
				arr3[i][j] += arr1[i][k] * arr2[k][j];

	double y = omp_get_wtime();
	printf("%lf\n", y - x);
	return 0;
}

**/