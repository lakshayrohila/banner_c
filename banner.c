#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "conio.h"

#ifndef TOTAL
#define TOTAL 50
#endif

unsigned short isFile(char *file_name) {
    // always use r+ as file mode to check if a file exists, since mode r might sometimes not return NULL when opening directory
    FILE *fo = fopen(file_name, "r+");

    if(fo == NULL) {
        return 0;
    }

    fclose(fo);
    return 1;
}

int main(int argc, char *argv[]) {
    if(argc < 2) {
        fprintf(stderr, "\033[31mError:\033[37m ");
        fprintf(stderr, "No file name given.\n");
        return 1;
    } else if(!isFile(argv[1])) {
        fprintf(stderr, "\033[31mError:\033[37m ");
        fprintf(stderr, "\033[36m%s\033[37m is not a file.\n", argv[1]);
        return 1;
    }

    FILE *fo = fopen(argv[1], "r");
    char *msg = malloc(2), c;
    unsigned long f_len = 0, i = 0, i1, prefix = TOTAL-1, c_f_len;

    while((c != EOF)) {
        c = getc(fo);
        msg = realloc(msg, ((f_len+2)*sizeof(char))+1);
        *(msg+f_len) = (c != '\n') ? c : ' ';
        f_len++;
    }
    *(msg+f_len-1) = ' ';

    c_f_len = f_len;

    while(f_len <= (c_f_len+TOTAL)) {
        msg = realloc(msg, ((f_len+2)*sizeof(char))+1);
        *(msg+f_len) = ' ';
        f_len++;
    }
    *(msg+f_len) = '\0';

    while(!kbhit()) {
        printf("\r");

        for(i1 = prefix;i1 > 0;i1--) {
            printf(" ");
        }

        for(i1 = i;i1 < ((TOTAL+i)-prefix);i1++) {
            printf("%c", *(msg+i1));
        }

        if(prefix > 0) {
            prefix--;
        } else {
            i++;
        }

        if(i >= (f_len-TOTAL)) {
            i = 0;
            prefix = TOTAL-1;
        }
        
        usleep(95000);
    }

    printf("\n");

    return 0;
}
