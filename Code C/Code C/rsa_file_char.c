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
    printf("\nPhase cryptage : \n\n");
    while (!feof(fichier)){
        fgets(buffer, MAX_BUFFER, fichier);
        printf("phrase : %s\n", buffer);
        for (i = 0; buffer[i] != '\0'; i++){
            RSAcrypt((unsigned char*)&buffer[i], &cryptedBuffer[i], pubKey);
            printf("%d : %lu :",i, &cryptedBuffer[i]);
            char * buffer = base64_encode((const uchar*)&cryptedBuffer[i], sizeof(cryptedBuffer[i]), &_output_length);
            printf("%s\n", buffer);
            fwrite(buffer, 1, 12, fichier2);
            free(buffer);
        }
        *output_length += _output_length;
    }
    free(cryptedBuffer);
    fclose(fichier);
    fclose(fichier2);
    fseek(fichier, 0, SEEK_SET);
    fseek(fichier2, 0, SEEK_SET);
}


void RSAunCryptFile(char *inFilename,char *outFilename,rsaKey_t privKey, int length){
    FILE * fichier = NULL;
    FILE * fichier2 = NULL;
    size_t _length = (size_t)length;
    if ((fichier = fopen(inFilename, "r")) == NULL){
        fprintf(stderr, "Erreur ouverture du fichier %s.\n", inFilename);
    }
    if ((fichier2 = fopen(outFilename, "w")) == NULL){
        fprintf(stderr, "Erreur ouverture du fichier %s.\n", outFilename);
    }
    char * buffer =(char *)malloc(length*sizeof(char));
    uint64 cUnCrypt;
    while (!feof(fichier)){
        fgets(buffer, 13, fichier);
        printf("buffer = %s\n", buffer);
        uint64 * cryptedBuffer = base64_decode(buffer,12,&_length);
        printf("%lu\n", cryptedBuffer);
        RSAdecrypt(&cUnCrypt, cryptedBuffer, privKey);
        fprintf(fichier2, "%c", (char)cUnCrypt);
    }
    fclose(fichier);
    fclose(fichier2);
    fseek(fichier, 0, SEEK_SET);
    fseek(fichier2, 0, SEEK_SET);
}