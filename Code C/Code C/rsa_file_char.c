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
    unsigned char buffer[MAX_BUFFER];
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
    fseek(fichier2, 0, SEEK_SET);
}

// #############

void RSAcryptFile(char *inFilename, char *outFilename, rsaKey_t pubKey, int *output_length){
    FILE * fichier = fopen(inFilename, "r");
    FILE * fichier2 = fopen(outFilename, "w+b");
    unsigned char buffer[MAX_BUFFER];
    int i = 0;
    uint64 cryptedBuffer[MAX_BUFFER];
    uint64 *strTest = NULL;
    do{
        fgets(buffer, MAX_BUFFER, fichier);
        printf("phrase : %s\n", buffer);
        RSAcrypt(buffer, cryptedBuffer, pubKey);
        for (i = 0; cryptedBuffer[i] != '\0'; i++){
            fwrite(base64_encode(&cryptedBuffer[i], sizeof(cryptedBuffer[i]), output_length), 1, sizeof(base64_encode(&cryptedBuffer[i], sizeof(cryptedBuffer[i]), output_length)), fichier2);
        }
    }while (!feof(fichier));
    fclose(fichier);
    fclose(fichier2);
    fseek(fichier, 0, SEEK_SET);
    fseek(fichier2, 0, SEEK_SET);
}


void RSAunCryptFile(char *inFilename,char *outFilename,rsaKey_t privKey, int length){

    FILE * fichier = NULL;
    FILE * fichier2 = NULL;
    int i;
    if ((fichier = fopen(inFilename, "rb")) == NULL){
        fprintf(stderr, "Erreur ouverture du fichier %s.\n", inFilename);
    }
    if ((fichier2 = fopen(outFilename, "w+b")) == NULL){
        fprintf(stderr, "Erreur ouverture du fichier %s.\n", outFilename);
    }
    uint64 *cryptedBuffer = (uint64 *)malloc(sizeof(uint64));
    char buffer[MAX_BUFFER];
    do{
        fgets(cryptedBuffer, 12, fichier);
        printf("%s\n", cryptedBuffer);
        strcpy(cryptedBuffer, base64_decode(cryptedBuffer, length, &length));
        RSAdecrypt(buffer, cryptedBuffer, privKey);
        fwrite(cryptedBuffer, 1, 11, fichier2);
    }while (!feof(fichier));
    fclose(fichier);
    fclose(fichier2);
    fseek(fichier, 0, SEEK_SET);
    fseek(fichier2, 0, SEEK_SET);

}