#include <stdio.h>
#include <time.h>
#include <conio.h>

void output(int*** a, int rows, int columns) {
	static count = 0;
	if (count == 0) {

		printf("\nYour array :\n");
		count++;
	}
	else {
		printf("\nNew array witout one 1 in row/column :\n");

	}
	for (int i = 0; i < rows; i++) {

		for (int j = 0; j < columns; j++) {

			printf("%d\t", (*a)[i][j]);

		}
		printf("\n");
	}

}

void input(int*** a, int N, int M) {


	srand(time(NULL));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {

			(*a)[i][j] = rand() % 2;

		}
	}

};


void delrow(int*** arr, int* N, int* M, int number) {

	int** temp;
	if (!(temp = (int**)malloc((*N) * sizeof(int*)))) {
		printf("Error with memory allocation");
		exit();
	}

	for (int i = 0; i < (*N); i++)
	{
		temp[i] = (int*)malloc((*M) * sizeof(int));
	}


	for (int i = 0; i < number; i++)
	{
		for (int j = 0; j < (*M); j++)
		{
			int t = (*arr)[i][j];
			*(*(temp + i) + j) = t;
		}
	}
	for (int i = number; i < (*N); i++)
		for (int j = 0; j < (*M); j++)
		{
			temp[i][j] = (*arr)[i + 1][j];
		}


	for (int i = 0; i < (*N) + 1; i++)
		free((*arr)[i]);
	free(*arr);

	if (!((*arr) = (int**)malloc((*N) * sizeof(int*)))) {
		printf("Error with memory allocation");
		exit();
	}

	for (int i = 0; i < (*N); i++)
	{
		(*arr)[i] = (int*)malloc((*M) * sizeof(int));
	}

	for (int i = 0; i < (*N); i++)
	{
		for (int j = 0; j < (*M); j++)
		{
			(*arr)[i][j] = temp[i][j];
		}
	}
	for (int i = 0; i < (*N); i++)
		free(temp[i]);
	free(temp);

	find(&(*arr), &(*N), &(*M));
}
void delcolumn(int*** a, int* N, int* M, int number) {
	int** temp;
	if (!(temp = (int**)malloc((*N) * sizeof(int*)))) {
		printf("Error with memory allocation");
	}

	for (int i = 0; i < (*N); i++)
	{
		temp[i] = (int*)malloc((*M) * sizeof(int));
	}

	for (int i = 0; i < (*N); i++)
	{
		for (int j = 0; j < number; j++)
		{
			int t = (*a)[i][j];
			*(*(temp + i) + j) = t;
		}
	}
	for (int i = 0; i < (*N); i++)
		for (int j = number; j < (*M); j++)
		{
			temp[i][j] = (*a)[i][j + 1];
		}


	for (int i = 0; i < (*N); i++)
		free((*a)[i]);
	free(*a);

	if (!((*a) = (int**)malloc((*N) * sizeof(int*)))) {
		printf("Error with memory allocation");
		exit();
	}

	for (int i = 0; i < (*N); i++)
	{
		(*a)[i] = (int*)malloc((*M) * sizeof(int));
	}

	for (int i = 0; i < (*N); i++)
	{
		for (int j = 0; j < (*M); j++)
		{
			(*a)[i][j] = temp[i][j];
		}
	}

	for (int i = 0; i < (*N); i++)
		free(temp[i]);
	free(temp);
	find(&(*a), &(*N), &(*M));
}




int find(int*** arr, int* N, int* M) {
	for (int i = 0; i < *N; i++)
	{
		int count = 0;
		for (int j = 0; j < *M; j++)
		{
			if ((*arr)[i][j] == 1)count++;
		}

		if (count == 1) {
			(*N)--;
			delrow(&(*arr), &(*N), &(*M), i);
		}
	}
	for (int i = 0; i < *M; i++)
	{
		int count = 0;
		for (int j = 0; j < *N; j++)
		{
			if ((*arr)[j][i] == 1)count++;
		}

		if (count == 1) {
			(*M)--;
			delcolumn(&(*arr), &(*N), &(*M), i);
		}
	}

}
int create(int*** a, int N, int M) {
	(*a) = (int**)malloc(N * sizeof(int*));
	if (!(*a)) {
		printf("Error with memory allocation");
		return 1;
	}
	for (int i = 0; i < N; i++) {
		(*a)[i] = (int*)malloc(M * sizeof(int));
	}


	return 0;
}


int main()
{

	int rows, columns, choice;
	int** array;
	int t = 1;
	while (t) {

		printf("\nEnter number of rows: ");
		while (!(scanf_s("%d", &rows))) {
			printf("\nError. Please try again. Enter number of rows: ");
			getchar();
		}

		printf("\nEnter number of columns: ");
		while (!(scanf_s("%d", &columns))) {
			printf("\nError. Please try again. Enter number of columns: ");
			getchar();
		}




		if (create(&array, rows, columns)) {
			return 0;
		}
		input(&array, rows, columns);
		output(&array, rows, columns);
		find(&array, &rows, &columns);
		output(&array, rows, columns);


		printf("\nWould you like to continue?  Press 1, if you want end. \n");
		while (!(scanf_s("%d", &choice))) {
			printf("\nThere isn't this choice, please try again.  Press 1, if you want end. \n");
			getchar();

		}
		if (choice == 1) {
			t = 0;
		}

	}
	return 0;
}

