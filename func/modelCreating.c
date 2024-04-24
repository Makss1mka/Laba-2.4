#include <stdio.h> 
#include <stdlib.h>  
#include <string.h> 
#include <math.h>
#include "header.h"
#include "task2.h" 

void addHospital(hosQueue* hosQueue, char* filePath) {
    hospital* hospital = createHospital();

    hosQueuePush(hosQueue, hospital);

    FILE* file = fileOpener(filePath, "at");
    hospitalSave(file, hospital);
    fclose(file);
}

hospital* createHospital() {
    hospital* hospital = mallocWithoutNull(sizeof(*hospital));

    printf("\n\tHospital creating:\n\t\tInput hospital name - ");
    char* temp = mallocWithoutNull(30);
	temp = fgets(temp, 30, stdin);
	rewind(stdin);
    hospital->name = strCorrection(temp);

    printf("\t\tInput hospital X cordinat - ");
    hospital->x = intScanWithLimitCheck(-1000000, 100000, "\t\t");

    printf("\t\tInput hospital Y cordinat - ");
    hospital->y = intScanWithLimitCheck(-1000000, 100000, "\t\t");

    printf("\t\tInput hospital maximum seats cordinat - ");
    hospital->patients = patQueueInit(hospital->patients, intScanWithLimitCheck(1, 1000, "\t\t"));

    hospital->range = &distanceCounter;

    return hospital;
}

void addPatient(hosQueue* hosQueue, char* filePath) {
    if (hosQueue->ammount == 0) {
        printf("\n\t\tThere aren't hospitals in queue.\n");
        return;
    }

    patient* patient = createPatient();
    hospital* hospital = getHospital(hosQueue, getHospitalByDistance(hosQueue, patient));

    if (hospital == NULL) {
        printf("\n\t\tAll hospitals are full.\n");
        return;
    }

    patQueuePush(hospital->patients, patient);
}

patient* createPatient() {
    patient* patient = mallocWithoutNull(sizeof(*patient));

    printf("\n\tCreating of patient:\n\t\tInput patient name - ");
    char* temp = mallocWithoutNull(50);
	temp = fgets(temp, 50, stdin);
	rewind(stdin);
    patient->name = strCorrection(temp);

    printf("\t\tInput hospital X cordinat - ");
    patient->x = intScanWithLimitCheck(-1000000, 100000, "\t\t");

    printf("\t\tInput hospital Y cordinat - ");
    patient->y = intScanWithLimitCheck(-1000000, 100000, "\t\t");
    
    return patient;
}




int getHospitalByDistance(hosQueue* hosQueue, patient* patient) {
    hospital* hospital = hosQueue->first;
    double distance, curDistance;
    int flag = 0, hosInd = -1;

    for(int i = 0; hospital != NULL; i++) {
        if (hospital->patients->availableSeats == 0) continue;
        
        curDistance = hospital->range(hospital->x, hospital->y, patient->x, patient->y);

        hospital = getNextHospital(hospital);

        if (flag == 0) {
            flag++;
            distance = curDistance;
            hosInd = i;
            continue;
        }

        if (curDistance < distance) {
            distance = curDistance;
            hosInd = i;
        }
    }

    return hosInd;
}

double distanceCounter(int hosX, int hosY, int patX, int patY) {

    return sqrt(pow(hosX - patX, 2) + pow(hosY - patY, 2));

}




void hospitalDelete(hosQueue* hosQueue, char* filePath) {
    printf("\n\tInput index of hospital which will be deleted (0-%d) - ", hosQueue->ammount - 1);

    int ind = intScanWithLimitCheck(0, hosQueue->ammount - 1, "\t"), ammount = hosQueue->ammount;

    hospital* hospital = getHospital(hosQueue, ind);

    if (hospital->next == NULL && hospital->prev == NULL) {
        hosQueue->first = NULL;
        hosQueue->last = NULL;
        return;
    }

    if (hospital->next == NULL) {
        hosQueue->last = hospital->prev;
        hosQueue->last->next = NULL;
        return;
    }

    if (hospital->prev == NULL) {  
        hosQueue->first = hospital->next;
        hosQueue->first->prev = NULL;
        return;
    }

    hospital->prev->next = hospital->next;
    hospital->next->prev = hospital->prev;

    hospitalFree(hospital);
    free(hospital);
    hospital = NULL;
}

void patientManipulations(hosQueue* hosQueue, char* filePath) {

    printf("\n\tInput the name of patient - ");
    char* temp = mallocWithoutNull(50);
	temp = fgets(temp, 50, stdin);
	rewind(stdin);
    temp = lower(strCorrection(temp));
    
    array_2 places = patientsFind(hosQueue, temp);

    if(places.col == 0) {
        array_2_free(places);
        printf("\n\tThis patient doesn't settled in any hospital\n");
        return;
    }

    printf("\n\tDo you want to discharged someone?! (0 - no | 1 - yes) - ");

    if(intScanWithLimitCheck(0, 1, "\t") == 0) {
        array_2_free(places);
        return;
    }

    printf("\n\tChouse whom you want to discharged?! (0-%d) - ", places.row - 1);
     
    patientDelete(hosQueue, places.data[intScanWithLimitCheck(0, places.row - 1, "\t")]);
    array_2_free(places);
}

array_2 patientsFind(hosQueue* hosQueue, char* str) {
    hospital* hospital = hosQueue->first;
    patient* patient;
    array_2 res = array_2_init();
    res.col = 2;
    
    for(int i = 0; i < hosQueue->ammount; i++) {
        patient = hospital->patients->first;

        for(int j = 0; j < hospital->patients->maxSeats - hospital->patients->availableSeats; j++) {
            
            if(strcmp(lower(patient->name), str) == 0) {
                res.data = reallocWithoutNull(res.data, sizeof(int*) * (res.row + 1));
                res.data[res.row] = mallocWithoutNull(sizeof(int) * 2);
                res.data[res.row][0] = i;
                res.data[res.row][1] = j;
                res.row++;
                
                printf("\n\tPatient was found in %s (%d-th hospital)\n", hospital->name, i);
            }

            patient = getNextPatient(patient);
        }

        hospital = getNextHospital(hospital);
    }

    return res;
}

void patientDelete(hosQueue* hosQueue, int* place) {
    if(place[0] < 0 || place[0] > hosQueue->ammount) {
        printf("Incorrect argument. This hospital doen't exist.");    
        return;
    }
    
    hospital* hospital = getHospital(hosQueue, place[0]);

    if(place[1] > hospital->patients->maxSeats - hospital->patients->availableSeats || place[1] < 0) {
        printf("Incorrect argument. This doesn't settled in %s hospital.", hospital->name);    
        return;
    }

    patient* patient = getPatient(hospital->patients, place[1]);
    
    hospital->patients->availableSeats++;

    if (hospital->patients->availableSeats == hospital->patients->maxSeats) {
        hospital->patients->first = NULL;
        hospital->patients->last = NULL;
        return;
    }

    if (patient->next == NULL) {
        hospital->patients->last = patient->prev;
        hospital->patients->last->next = NULL;
        return;
    }

    if (patient->prev == NULL) {  
        hospital->patients->first = patient->next;
        hospital->patients->first->prev = NULL;
        return;
    }

    patient->prev->next = patient->next;
    patient->next->prev = patient->prev;

}

