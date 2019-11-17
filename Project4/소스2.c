#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#define MAX_SIZE 100001
//https://bit.ly/2mfYLl9
void insertion_sort(int* a, int n) {
	for (int i = 1; i < n; i++) {
		int tmp = a[i], j = i;
		while (j > 0 && a[j - 1] > tmp) {
			a[j] = a[j - 1];
			j--;
		}
		a[j] = tmp;
	}
	return;
}
void print_array(char* ment, int* a, int n) {
	printf("%s", ment);
	for (int i = 0; i < n; i++)
		printf("%d ", a[i]);
	puts("");
}
int main() {
	FILE* fp = fopen("lab1.data", "r");
	int n = 0, t;
	while (~fscanf(fp, "%d", &t)) n++;
	fclose(fp);
	fp = fopen("lab1.data", "r");
	int* a = (int*)malloc(sizeof(int) * n);
	for (int i = 0; ~fscanf(fp, "%d", &t); )
		a[i++] = t;
	fclose(fp);
	print_array("Input : ", a, n);
	insertion_sort(a, n);
	for (int i = 0; i + 1 < n; i++) {
		assert(a[i] <= a[i + 1]);
	}
	print_array("Sorted : ", a, n);

	//Complexity

	//int worst_i, worst_n, step = 10000;
	//int worst_a[MAX_SIZE];
	//double duration, first = clock();
	//printf("\tN\t\ttime\n");
	//for (worst_n = 10000; worst_n <= 100000; worst_n += step) {
	//	clock_t start = clock();
	//	//init worst case data
	//	for (worst_i = 0; worst_i < worst_n; worst_i++)
	//		worst_a[worst_i] = worst_n - worst_i;
	//	insertion_sort(worst_a, worst_n);
	//	duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
	//	printf("%9d	\t%lf\n", worst_n, duration);
	//}
	return 0;
}
