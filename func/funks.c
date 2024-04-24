#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "task2.h"

void argsCheck(int argc, char** argv, int num) {
	if (argc < num) {
		printf("\n\tIncorrect arguments\n");
		exit(-1);
	}
}

void* mallocWithoutNull(unsigned size) {
	void* returnArr = NULL;
	int count = 0;

	while (1) {
		returnArr = (int*)malloc(size);
		if (returnArr != NULL) return returnArr;

		count++;
		if (count > 50) {
			printf("\n\n\tMalloc cycle error");
			exit(-1);
		}
	}
}

void* reallocWithoutNull(void* inputPtr, unsigned newSize) {
	int count = 0;

	while (1) {
		inputPtr = realloc(inputPtr, newSize);
		if (inputPtr != NULL) return inputPtr;

		count++;
		if (count > 50) {
			printf("\n\n\tRealloc cycle error");
			exit(-1);
		}
	}
	return NULL;
}

int intScanWithLimitCheck(int min, int max, char* decor) {
	int num;

	while (scanf_s("%d", &num) == 0 || getchar() != '\n'
		|| num < min || num > max) {
		printf("%sIncorrect input, make another input - ", decor);
		rewind(stdin);
	}

	return num;
}


// FOR STRINGS
int in(char symb, char* str) {

	for (int i = 0; i < strlen(str); i++) {
		if (str[i] == symb) return 1;
	}

	return 0;
}

char* strCorrection(char* str) {
	str[strlen(str) - 1] = '\0';

	for (int i = 0; i < strlen(str); i++) {
		if (str[i] == '\t' || str[i] == '\n') str[i] == ' ';
	}

	return str;
}

char* strcopy(char copied[]) {
	if (copied == NULL) return NULL;

	char* result = mallocWithoutNull(sizeof(int) * strlen(copied));

	for(int i = 0; i < strlen(copied); i++) result[i] = copied[i];
	result[strlen(copied)] = '\0';

	return result;
}


// FOR FILES
void* fileOpener(void* filePath, void* mode) {
	FILE* file = NULL;
	file = fopen(filePath, mode);

	if (file == NULL) {
		printf("\n\tFailed access to the file\n");
		exit(1);
	}

	return file;
}

char* normalFscanf(FILE* file) {
	char* str = mallocWithoutNull(0);
	char curChar = fgetc(file);
	int len = 0;

	while (curChar != EOF && curChar != '\n') {
		str = reallocWithoutNull(str, sizeof(char) * (++len));
		str[len - 1] = curChar;

		curChar = fgetc(file);
	}

	str[len] = '\0';
	return str;
}

char* lower(char* str) {
	char* temp = mallocWithoutNull(sizeof(char) * strlen(str));
	strcpy(temp, str);

	for(int i = 0; i < strlen(str); i++) {
		if (temp[i] >= 65 && temp[i] <= 90) temp[i] = (char)(((int)temp[i]) + 32);
	}

	return temp;
}


// MATRIX
array_2 array_2_init() {
    array_2 array;
    array.data = mallocWithoutNull(0);
    array.col = 0;
    array.row = 0;

    return array;
}

void array_2_free(array_2 arr) {
    for(int i = 0; i < arr.row; i++) {
        free(arr.data[i]);
    }
    free(arr.data);  
}
    

