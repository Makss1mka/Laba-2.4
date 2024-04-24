#pragma once
#include <stdio.h> 
#include <stdlib.h>  

typedef struct Patient {

    char* name;
    int x;
    int y;
    struct Patient* next;
    struct Patient* prev;

} patient;

typedef struct PatientQueue {

    int maxSeats;
    int availableSeats;
    struct Patient* first;
    struct Patient* last;

} patQueue;

typedef struct Hospital {

    char* name;
    int x;
    int y;
    double (*range) (int, int, int, int);

    patQueue* patients;

    struct Hospital* next;
    struct Hospital* prev;

} hospital;

typedef struct HospitalQueue {

    int ammount;
    struct Hospital* first;
    struct Hospital* last;

} hosQueue;

typedef struct array_2 {
    int** data;
    int row;
    int col;
} array_2;



void task2(char* filePath);
void menu(char* filePath);
hosQueue* getAll(hosQueue* hosList, char* filePath);
hospital* readOneHosEntry(FILE* file);
patient* readOnePatEntry(FILE* file);
void hosQueuePrint(hosQueue* hospitalQueue);
void patQueuePrint(patQueue* patientQueue);


// QUEUES
hosQueue* hospitalQueueInit(hosQueue* hosQueue);
patQueue* patQueueInit(patQueue* patQueue, int max);
void hosQueuePush(hosQueue* hosQueue, hospital* hospital);
void patQueuePush(patQueue* patQueue, patient* patient);
hospital* hosQueuePop(hosQueue* hosQueue);
patient* patQueuePop(patQueue* patQueue);

hospital* getNextHospital(hospital* hospital);
patient* getNextPatient(patient* patient);
patient* getPatient(patQueue* patQueue, int ind);
hospital* getHospital(hosQueue* hosQueue, int ind);


// MEMORY FREE
void patientQueueFree(patQueue* patQueue);
void patientFree(patient* patient);
void hospitalFree(hospital* hospital);
void hospitalQueueFree(hosQueue* hosQueue);


// CREATING
void addHospital(hosQueue* hosQueue, char* filePath);
hospital* createHospital();
void addPatient(hosQueue* hospitalQueue, char* filePath);
patient* createPatient();
double distanceCounter(int hosX, int hosY, int patX, int patY);
int getHospitalByDistance(hosQueue* hosQueue, patient* patient);


// FILE SAVING
void queueSave(hosQueue* hospitalQueue, char* filePath);
void hospitalSave(FILE* file, hospital* hospital);
void patientQueueSave(FILE* file, patQueue* patientQueue);
void patientSave(FILE* file, patient* patient);


// DELETING
void hospitalDelete(hosQueue* hospitalQueue, char* filePath);
void patientManipulations(hosQueue* hosQueue, char* filePath);
void patientDelete(hosQueue* hosQueue, int* place);


// ARRAY 2
array_2 patientsFind(hosQueue* hosQueue, char* str);
array_2 array_2_init();
void array_2_free(array_2 arr);


