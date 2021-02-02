#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>


const char *ENVIRONMENT_KEY_VAR = "XOR64_KEY";

int main(void) {
    unsigned char * key; // = "5N6,?-pqmot\\=K/vksrMQO%47n*u|:l.";
    int ch, count=0;
    FILE *fc, *fx;

    key = getenv(ENVIRONMENT_KEY_VAR);

    if (key == NULL) {
        printf("Evironment variable %s not found!\n", ENVIRONMENT_KEY_VAR);
        exit(1);
    }

    fc = stdin;
    fx = stdout;
    if (fc != NULL) {

        if (fx != NULL) {
            while ((ch = fgetc(fc)) != EOF) {
                fputc(ch ^ key[count % strlen(key)], fx);
                count++;
            } 
        } 
        else {
            printf("Error: %d\n", errno);
        } 
    }
    else {
        printf("Error: %d\n", errno);
    } 
    
}
