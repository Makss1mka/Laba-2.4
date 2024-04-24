#include <stdio.h> 
#include <stdlib.h>  
#include <string.h>  
#include "header.h"
#include "task1.h"

stack* push(stack* top, char* data) {
    stack* next = mallocWithoutNull(sizeof(stack));
    
    next->next = top;
    next->data = data;

    return next;
}

char* pop(stack** top) {
    if (*top == NULL) return NULL;
    
    char* data = (*top)->data;
    
    *top = (*top)->next;
    
    return data;
}

stack* strToStc(stack** stc, char* str) {
    for(int i = 0; i < strlen(str); i++) {
        *stc = push(*stc, chrToStr(str[i]));
    }
    
    return *stc;
}

stack* getNext(stack* stack) {

    return stack->next;

}

stack* get(stack* stc, int ind) {
    stack* temp = stc;

    for(int i = 0; i < ind; i++) {
        temp = getNext(temp);
    }

    return temp;
}



void printStack(stack* stc, char message[]) {
    fputs(message, stdout);
    rewind(stdout);

    stack* temp = stc;

    while(temp != NULL) {
        printf("%s", temp->data);
        temp = getNext(temp);
    }
}





