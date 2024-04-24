#include <stdio.h> 
#include <stdlib.h>  

#include "queue.c"
#include "modelCreating.c"
#include "saving.c"

#include "header.h"
#include "task2.h" 

void task2(char* filePath) {

    printf("\n--- HOSPITAL MODEL ---\n");
	
	menu(filePath);

	printf("\n----------------------\n");

}

void menu(char* filePath) {
    int choice;
	hosQueue* curQueue = NULL;
	curQueue = getAll(curQueue, filePath);
	
	while (1) {
		printf("\n\tMenu:\n\t1) Add hospital\n\t2) Add patient\n\t3) Patient find/discharge\n\t4) Delete hospital by id\n\t5) Print current queue\n\t6) Save the current queue\n\t7) Exit\n\tSelect the option - ");

		switch (choice = intScanWithLimitCheck(1, 7, "\n\t")) {
		case 1:
			addHospital(curQueue, filePath);
			break;
		case 2:
			addPatient(curQueue, filePath);
			break;
		case 3:
			patientManipulations(curQueue, filePath);
			break;
		case 4:
			hospitalDelete(curQueue, filePath);
			break;
		case 5:
			hosQueuePrint(curQueue);
			break;
		case 6:
			queueSave(curQueue, filePath);
			break;
		case 7:
			hospitalQueueFree(curQueue);
			free(curQueue);
			printf("\n----------------------\n");
			exit(0);
			break;
		default:
			printf("\n\nIncorrect input");
			break;
		}
	}
}



hosQueue* getAll(hosQueue* hosQueue, char* filePath) {
    FILE* file = fileOpener(filePath, "rt");

    hosQueue = hospitalQueueInit(hosQueue);
    
	fgetc(file);
	fgetc(file);

    while (fgetc(file) != EOF) {	
		fseek(file, -1, SEEK_CUR);
		hosQueuePush(hosQueue, readOneHosEntry(file));
    }

	return hosQueue;
}

hospital* readOneHosEntry(FILE* file) {
	hospital* hospital = mallocWithoutNull(sizeof(*hospital));
	int temp;	

	hospital->name = normalFscanf(file);
	
	fscanf(file, "%d\n", &hospital->x);
	fscanf(file, "%d\n", &hospital->y);
	fscanf(file, "%d\n", &temp);
	
	hospital->patients = patQueueInit(hospital->patients, temp);

	fscanf(file, "%d\n", &temp);

	hospital->range = &distanceCounter;

	for(int i = 0; i < hospital->patients->maxSeats - temp; i++) {
		patQueuePush(hospital->patients, readOnePatEntry(file));
	}

	hospital->next = NULL;
	hospital->prev = NULL;

	return hospital;
}

patient* readOnePatEntry(FILE* file) {
	patient* patient = mallocWithoutNull(sizeof(*patient));

	patient->name = normalFscanf(file);
	
	fscanf(file, "%d\n", &patient->x);
	fscanf(file, "%d\n", &patient->y);
	
	patient->next = NULL;
	patient->prev = NULL;

	return patient;
}



void hosQueuePrint(hosQueue* hosQueue) {
	hospital* hospital = hosQueue->first;

	while (hospital != NULL) {	
		printf("\n\tHospital name: %s, adress: %d %d, max seats: %d, available seats: %d", hospital->name, hospital->x, hospital->y, hospital->patients->maxSeats, hospital->patients->availableSeats);
		patQueuePrint(hospital->patients);

		hospital = getNextHospital(hospital);	
	} 
	
	printf("\n");
}

void patQueuePrint(patQueue* patQueue) {
	patient* patient = patQueue->first;

	while(patient != NULL) {
		printf("\n\t\tName: %s, adress: %d, %d", patient->name, patient->x, patient->y);
		patient = getNextPatient(patient);
	}
}





