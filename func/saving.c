#include <stdio.h> 
#include <stdlib.h>  
#include "header.h"
#include "task2.h" 

void queueSave(hosQueue* hosQueue, char* filePath) {
    FILE* file = fileOpener(filePath, "wt");

    hospital* hospital = hosQueue->first;

    while(hospital != NULL) {
        hospitalSave(file, hospital);
        hospital = getNextHospital(hospital);
    }

    fclose(file);
}

void hospitalSave(FILE* file, hospital* hospital) {

    fprintf(file, "\n\n%s\n", hospital->name);
    fprintf(file, "%d\n", hospital->x);
    fprintf(file, "%d\n", hospital->y);

    patientQueueSave(file, hospital->patients);

}

void patientQueueSave(FILE* file, patQueue* patQueue) {
    fprintf(file, "%d\n", patQueue->maxSeats);
    fprintf(file, "%d", patQueue->availableSeats);

    patient* patient = patQueue->first;

    while(patient != NULL) {
        patientSave(file, patient);
        patient = getNextPatient(patient);
    }
}

void patientSave(FILE* file, patient* patient) {

    fprintf(file, "\n%s\n", patient->name);
    fprintf(file, "%d\n", patient->x);
    fprintf(file, "%d", patient->y);

}

