#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <getopt.h>

#define MAX_KEY_LENGTH 64

const char *ENVIRONMENT_KEY_VAR = "XOR_KEY";


unsigned char * get_key_from_file(char *key_fn, unsigned char *buf, int buf_len) {
    
    FILE *fk;
    unsigned char *p = NULL;

    fk =  fopen(key_fn, "r");
    if (fk != NULL) {
        memset(buf, 0, buf_len);
        p = fgets(buf, buf_len, fk);
        buf[strcspn(buf, "\r\n")] = 0;
    }
    else {
        fprintf(stderr, "Unable to open the key file: errno=%d!\n", errno);
    }

    return p;

}    

int main(int argc, char **argv) {

    char *ifn = NULL;
    char *ofn = NULL;
    char *kfn = NULL;
    unsigned char *key;
    unsigned char key_buf[MAX_KEY_LENGTH];
    int ch;
    int count = 0;
    FILE *fi, *fo;

    static const struct option long_options[] = {
        {"help", no_argument, NULL, 'h'},
        {"in-file", required_argument, NULL, 'i'},
        {"out-file", required_argument, NULL, 'o'},
        {"key-file", required_argument, NULL, 'k'},
        {0, 0, 0, 0}
    };

    const char *usage =
        "Usage: xor [options]\n"
        "\n"
        "  -h, --help       Show help message and quit.\n"
        "  -i, --in-file    Specify source file.\n"
        "  -o, --out-file   Specify out file.\n"
        "  -k, --key-file   Specify file contained xor key.\n"
        "\n";
    
    int c;
    while (1) {
        int option_index = 0;
        c = getopt_long(argc, argv, "hi:o:k:", long_options, &option_index);
        if (c == -1) {
            break;
        }
        switch (c) {
        case 'h': // help
            printf("%s", usage);
            exit(EXIT_SUCCESS);
            break;
        case 'i': 
            ifn = optarg;
            break; 
        case 'o': 
            ofn = optarg;
            break; 
        case 'k': 
            kfn = optarg;
            break; 
        default:
            fprintf(stderr, "%s", usage);
            exit(EXIT_FAILURE);
        }
    }

    key = getenv(ENVIRONMENT_KEY_VAR);
    if (key == NULL) {
        if (kfn == NULL) {
            fprintf(stderr, "Key %s not found!\n", ENVIRONMENT_KEY_VAR);
            exit(1);
        }
        else {
            key = get_key_from_file(kfn, key_buf, sizeof(key_buf));
            if (key == NULL) {
                exit(4);
            }
        }
    }

    if (ifn == NULL) {
        fi = stdin;
    } 
    else {
        fi = fopen(ifn, "r");
        if (fi == NULL) {
            fprintf(stderr, "Unable to open the file: errno=%d!\n", errno);
            exit(2);
        }
    }

    if (ofn == NULL) {
        fo = stdout;
    }
    else {
        fo = fopen(ofn, "w");
        if (fo == NULL) {
            fprintf(stderr, "Unable to open the file for writing: errno=%d!\n", errno);
            exit(3);
        }
    }

    if (fi != NULL) {
        if (fo != NULL) {
            while ((ch = fgetc(fi)) != EOF) {
                fputc(ch ^ key[count % strlen(key)], fo);
                count++;
            } 
            fclose(fo);
        } 
        fclose(fi);
    }
    
}
