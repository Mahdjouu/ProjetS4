#include "rsa_header.h"

void RSAfile_crypt(char *inFilename,char *outFilename, rsaKey_t pubKey){
    FILE * fichier = fopen(inFilename, "r+b");
    FILE * fichier2 = fopen(outFilename, "w+b");
    unsigned char buffer[MAX_BUFFER];
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
    FILE * fichier = fopen(inFilename, "r+b");
    FILE * fichier2 = fopen(outFilename, "w+b");
    char *buffer = (char *)malloc(MAX_BUFFER*sizeof(char));
    uint64 *cryptedBuffer = (uint64 *)malloc(MAX_BUFFER*sizeof(uint64));
    fscanf(fichier, "%s", buffer);
    while (!feof(fichier)){
        RSAdecrypt((unsigned char*)buffer, cryptedBuffer, privKey);
        fwrite((const void *)buffer, 1, strlen(buffer), fichier2);
        fscanf(fichier, "%s", buffer);
    }
    fclose(fichier);
    fclose(fichier2);
    fseek(fichier, 0, SEEK_SET);
    fseek(fichier2, 0, SEEK_SET);
}

// #############

void RSAcryptFile(char *inFilename, char *outFilename, rsaKey_t pubKey, int *output_length){
    FILE * fichier = fopen(inFilename, "r");
    FILE * fichier2 = fopen(outFilename, "w");
    char *buffer = (char*)malloc(MAX_BUFFER*sizeof(char));
    int i = 0;
    size_t _output_length = (size_t)*output_length;
    uint64 *cryptedBuffer = (uint64 *)malloc(MAX_BUFFER*sizeof(uint64));
    do{
        fgets(buffer, MAX_BUFFER, fichier);
        printf("phrase : %s\n", buffer);
        RSAcrypt((unsigned char*)buffer, cryptedBuffer, pubKey);
        for (i = 0; cryptedBuffer[i] != '\0'; i++){
            fwrite(base64_encode((const uchar*)&cryptedBuffer[i], sizeof(cryptedBuffer[i]), &_output_length), 1, sizeof(base64_encode((const uchar*)&cryptedBuffer[i], sizeof(cryptedBuffer[i]), &_output_length)), fichier2);
        }
        free(buffer);
        free(cryptedBuffer);
    }while (!feof(fichier));
    *output_length = _output_length;
    fclose(fichier);
    fclose(fichier2);
    fseek(fichier, 0, SEEK_SET);
    fseek(fichier2, 0, SEEK_SET);
}


void RSAunCryptFile(char *inFilename,char *outFilename,rsaKey_t privKey, int length){
    FILE * fichier = NULL;
    FILE * fichier2 = NULL;
    size_t _length = (size_t)length;
    if ((fichier = fopen(inFilename, "rb")) == NULL){
        fprintf(stderr, "Erreur ouverture du fichier %s.\n", inFilename);
    }
    if ((fichier2 = fopen(outFilename, "wb")) == NULL){
        fprintf(stderr, "Erreur ouverture du fichier %s.\n", outFilename);
    }
    char * buffer =(char *)malloc(length*sizeof(char));
    uint64 cUnCrypt;
    do{
        fread(buffer, 1, _length, fichier);
        printf("%s\n", buffer);
        uint64 *cryptedBuffer = base64_decode((const char *)buffer,_length,&_length);
        //printf("%d\n", cryptedBuffer);
        // RSAdecrypt(&cUnCrypt, cryptedBuffer, privKey);
        cUnCrypt = puissance_mod_n(cryptedBuffer,privKey.E,privKey.N);
        //fprintf(fichier2, "%c\n", (char)cUnCrypt);
        fwrite(&cUnCrypt, 1, 1, fichier2);
        free(cryptedBuffer);
    }while (!feof(fichier));
    fclose(fichier);
    fclose(fichier2);
    fseek(fichier, 0, SEEK_SET);
    fseek(fichier2, 0, SEEK_SET);
}