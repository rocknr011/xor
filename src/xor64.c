#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>


const char *KEY_ENVIRONMENT = "XOR64_KEY";

int main(void) {
    unsigned char * key; // = "5N6,?-pqmot\\=K/vksrMQO%47n*u|:l.";
    int ch, count=0;
    FILE *fc, *fx;

    key = getenv(KEY_ENVIRONMENT);

    if (key == NULL) {
        printf("Evironment variable %s not found!\n", KEY_ENVIRONMENT);
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

            // fclose(fx);
        } 
        else {
            printf("Error: %d\n", errno);
        } 

        // fclose(fc);
    }
    else {
        printf("Error: %d\n", errno);
    } 
    
}
