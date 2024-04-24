void task1();
void task2();
void argsCheck(int argc, char** argv, int num);


// MEMORY
void* mallocWithoutNull(unsigned size);
void* reallocWithoutNull(void* inputPtr, unsigned newSize);


int intScanWithLimitCheck(int min, int max, char* decor);
char* getInfixForm(char* prefixForm);


// STRINGS
int in(char symb, char* str);
int getSignAmmount(char* str);
char* strCorrection(char* str);
char* normalFscanf(FILE* file);
char* lower(char* str);
char* strcopy(char copied[]);


// FOR FILES
void* fileOpener(void* filePath, void* mode);
