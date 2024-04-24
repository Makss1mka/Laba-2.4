#pragma once

typedef struct Stack {
    char* data;
    struct Stack* next;
} stack;

stack* push(stack* top, char* data);
char* pop(stack** top);
stack* get(stack* stc, int ind);
stack* getNext(stack* stack);
void printStack(stack* stc, char message[]);

char* operandLink(char sign, char* opr1, char* opr2);
char* chrToStr(char chr);

int check(char* prefixForm);
int symbolCheck(char* prefixForm);
int syntaxCheck(char* prefixForm);
int stcLastThreeNULLCheck(stack* stc);
int stcLastThreeLinkCheck(stack* stc);
int isOperand(char* str);
int isSign(char* str);

