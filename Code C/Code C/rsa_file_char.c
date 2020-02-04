#include "rsa_header.h"

void RSAfile_crypt(char *inFilename,char *outFilename, rsaKey_t pubKey){
    FILE * fichier = fopen(inFilename, "w+b");
    FILE * fichier2 = fopen(outFilename, "w+b");
    char buffer[MAX_BUFFER];
    uint64 cryptedBuffer[MAX_BUFFER];
    fscanf(fichier, "%s", buffer);
    while (!feof(fichier)){
        RSAcrypt(buffer, cryptedBuffer, pubKey);
        fwrite(cryptedBuffer, 1, MAX_BUFFER, fichier2);
        fscanf(fichier, "%s", buffer);
    }
    fclose(fichier);
    fclose(fichier2);
    fseek(fichier, 0, SEEK_SET);
}

void RSAfile_decrypt(char *inFilename,char *outFilename,rsaKey_t privKey){
    FILE * fichier = fopen(inFilename, "w+b");
    FILE * fichier2 = fopen(outFilename, "w+b");
    char buffer[MAX_BUFFER];
    uint64 cryptedBuffer[MAX_BUFFER];
    fscanf(fichier, "%s", buffer);
    while (!feof(fichier)){
        RSAdecrypt(buffer, cryptedBuffer, privKey);
        fwrite(buffer, 1, strlen(buffer), fichier2);
        fscanf(fichier, "%s", buffer);
    }
    fclose(fichier);
    fclose(fichier2);
    fseek(fichier, 0, SEEK_SET);
}