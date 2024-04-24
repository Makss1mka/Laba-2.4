#include <stdio.h>

#include "header.h"
#include "funks.c"

#include "task1.c"
#include "task2.c"

void main(int argc, char* argv[]) {
    argsCheck(argc, argv, 1);

    char filePath[] = "C:\\Users\\User\\Desktop\\PopuskPapka\\C\\laba2.4\\bd.txt";

    while (1) {
		printf("\nPick the task - ");
		switch (intScanWithLimitCheck(1, 2, "\n")) {
		    case 1:
			    task1();
			    break;
		    case 2:
			    task2(filePath);
			    break;
		}
	}

    
}

// c:\Users\User\Desktop\PopuskPapka\C\laba2.4
