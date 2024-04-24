#include <stdio.h> 
#include <stdlib.h>  
#include "header.h"
#include "task2.h" 

// INITS
hosQueue* hospitalQueueInit(hosQueue* hosQueue) {

    hosQueue = mallocWithoutNull(sizeof(*hosQueue));
    hosQueue->first = NULL;
    hosQueue->last = NULL;
    hosQueue->ammount = 0;

    return hosQueue;

}

patQueue* patQueueInit(patQueue* patQueue, int max) {

    patQueue = mallocWithoutNull(sizeof(*patQueue));
    patQueue->maxSeats = max;
    patQueue->availableSeats = max;
    patQueue->first = NULL;
    patQueue->last = NULL;

    return patQueue;

}


// PUSHЫ
void hosQueuePush(hosQueue* hosQueue, hospital* hospital) { 
    hosQueue->ammount++;
    
    hospital->next = NULL;

    if (hosQueue->last == NULL && hosQueue->first == NULL) {
        hosQueue->last = hospital;
        hosQueue->first = hospital;

        return;
    }

    hosQueue->last->next = hospital;
    hospital->prev = hosQueue->last;
    
    hosQueue->last = hospital;  
}

void patQueuePush(patQueue* patQueue, patient* patient) {
    if (patQueue->availableSeats == 0) {
        return;
    }

    if (patQueue->availableSeats == patQueue->maxSeats) {
        patQueue->last = patient;
        patQueue->first = patient;
        patQueue->availableSeats--;

        return;
    }

    patQueue->availableSeats--;
    patient->next = NULL;
    patQueue->last->next = patient;
    patient->prev = patQueue->last;
    
    patQueue->last = patient; 
}


// POPЫ
hospital* hosQueuePop(hosQueue* hosQueue) {
    if (hosQueue->ammount == 0) return NULL;
    
    hospital* hospital;

    hosQueue->ammount--;
    hospital = hosQueue->first;
    
    hosQueue->first = hosQueue->first->next;
    hosQueue->first->prev = NULL;

    hospital->next = NULL;
    hospital->prev = NULL;

    return hospital;
}

patient* patQueuePop(patQueue* patQueue) {
    if (patQueue->availableSeats == patQueue->maxSeats) return NULL;

    patient* patient;

    patQueue->availableSeats++;
    patient = patQueue->first;

    patQueue->first = patQueue->first->next;
    patQueue->first->prev = NULL;

    patient->next = NULL;
    patient->prev = NULL;

    return patient;
}


// GETЫ
hospital* getNextHospital(hospital* hospital) {

    return hospital->next;

}

patient* getNextPatient(patient* patient) {

    return patient->next;

}

hospital* getHospital(hosQueue* hosQueue, int ind) {
    if(ind > hosQueue->ammount - 1 || ind < 0) return NULL;
    
    hospital* hospital = hosQueue->first; 

    for(int i = 0; i < ind; i++) hospital = getNextHospital(hospital);
 
    return hospital;
}

patient* getPatient(patQueue* patQueue, int ind) {
    if(ind > patQueue->maxSeats - patQueue->availableSeats - 1 || ind < 0) return NULL;
    
    patient* patient = patQueue->first; 

    for(int i = 0; i < ind; i++) patient = getNextPatient(patient);
 
    return patient;
}


// FREEЫ
void hospitalQueueFree(hosQueue* hosQueue) {
    hospital* hospital = hosQueuePop(hosQueue);

    while(hospital != NULL) {
        hospitalFree(hospital);
        hospital = hosQueuePop(hosQueue);
    }

}

void hospitalFree(hospital* hospital) {

    free(hospital->name);
    patientQueueFree(hospital->patients);

}

void patientFree(patient* patient) {

    free(patient->name);

}

void patientQueueFree(patQueue* patQueue) {
    patient* patient = patQueuePop(patQueue);

    while(patient != NULL) {
        patientFree(patient);
        patient = patQueuePop(patQueue);
    }

}
