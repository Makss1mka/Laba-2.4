#include <stdio.h> 
#include <stdlib.h>  
#include "stack.c"
#include "header.h"

void task1() {
    
    printf("\n--- CONVERT PREFIX FORM INTO INFIX ---\n");
    
    printf("\n\tInput the prefix form - ");
    char* prefixForm = mallocWithoutNull(200);
    fgets(prefixForm, 200, stdin);
    rewind(stdin);
    prefixForm = strCorrection(prefixForm);

    if (check(prefixForm) != 0) {
        printf("\n--------------------------------------\n");
        free(prefixForm);
        prefixForm = NULL;
        return;
    }

    printf("\n\tResult: %s", getInfixForm(prefixForm));

    free(prefixForm);
    prefixForm = NULL;

    printf("\n--------------------------------------\n");

}

char* getInfixForm(char* prefixForm) {
    stack* stc = NULL;

    for (int i = 0; i < strlen(prefixForm); i++) {
        stc = push(stc, chrToStr(prefixForm[i]));

        if (stcLastThreeNULLCheck(stc) == 0 && stcLastThreeLinkCheck(stc) == 1) {
            stc = push(stc, operandLink(pop(&stc)[0], pop(&stc), pop(&stc)));
        }

    }

    while(stc->next != NULL) {
        stc = push(stc, operandLink(pop(&stc)[0], pop(&stc), pop(&stc)));
    }

    return pop(&stc);
}



char* operandLink(char sign, char* opr1, char* opr2) {
    char* result = mallocWithoutNull(sizeof(char) * (strlen(opr1) + strlen(opr2) + 4));
    result[0] = '(';
    result[strlen(opr1) + strlen(opr2) + 3] = '\0';
    result[strlen(opr1) + strlen(opr2) + 2] = ')';
    
    for(int i = 1; i < 1 + strlen(opr1); i++) {
        result[i] = opr1[i - 1];
    }
    result[1 + strlen(opr1)] = sign;
    for(int i = 2 + strlen(opr1), j = 0; i < strlen(opr1) + strlen(opr2) + 2; i++, j++) {
        result[i] = opr2[j];
    }
    
    free(opr1);
    free(opr2);
    opr1 = NULL;
    opr2 = NULL;

    printf("\n\t%s\n", result);
    return result;
}

char* chrToStr(char chr) {
    char* res = mallocWithoutNull(sizeof(char) * 2);

    res[1] = '\0';
    res[0] = chr;
    
    return res;
}



int check(char* prefixForm) {
    int code = symbolCheck(prefixForm);

    if (code > 0) {
        printf("\n\tIncorrect symbol on %d-th position\n", code + 1);
        return -1;
    }

    code = syntaxCheck(prefixForm);

    if (code > -1) {
        printf("\n\tIncorrect symbol on %d-th position\n", code + 1);
        return -1;
    }

    return 0;
}

int symbolCheck(char* prefixForm) {
    for(int i = 0; i < strlen(prefixForm); i++) {
        if (in(prefixForm[i], ".,<>(){}[]!@\"\'№$;^:&?`~\n\t") || prefixForm[i] == '%') {
            return i;
        }
    }

    return -1;
}

int syntaxCheck(char* prefixForm) {
    stack* stc;
    
    for(int i = strlen(prefixForm) - 1; i >= 0 ; i--) { 
        if (in(prefixForm[i], "+-*/")) {   
            if (stc == NULL || stc->next == NULL) return i;
            
            pop(&stc);
            pop(&stc);
            stc = push(stc, "X");
        } else {
            stc = push(stc, chrToStr(prefixForm[i]));
        }
    }

    if (stc->data[0] == 'X' && stc->next == NULL) return -1;

    return 0;
}

int stcLastThreeNULLCheck(stack* stc) {

    return !(stc != NULL && stc->next != NULL && stc->next->next != NULL);

}

int stcLastThreeLinkCheck(stack* stc) {

    return isOperand(stc->data) && isOperand(stc->next->data) && isSign(stc->next->next->data); 

}

int isOperand(char* str) {

    return !isSign(str);

}

int isSign(char* str) {

    return strlen(str) == 1 && in(str[0], "+-*/");

}


