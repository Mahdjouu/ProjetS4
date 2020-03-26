#include "rsa_header.h"

// #############

void RSAcryptFile(char *inFilename, char *outFilename, rsaKey_t pubKey, int *output_length){
    FILE * fichier = fopen(inFilename, "r");
    FILE * fichier2 = fopen(outFilename, "w");
    char *buffer = (char*)malloc(MAX_BUFFER*sizeof(char));
    int i = 0;
    size_t _output_length = (size_t)*output_length;
    uint64 *cryptedBuffer = (uint64 *)malloc(MAX_BUFFER*sizeof(uint64));
    printf("\nPhase cryptage : \n\n");
    do{
        fgets(buffer, MAX_BUFFER, fichier);
        printf("phrase : %s\n", buffer);
        for (i = 0; buffer[i] != '\0'; i++){
            RSAcrypt((unsigned char*)&buffer[i], &cryptedBuffer[i], pubKey);
            printf("%d : %lu :",i, &cryptedBuffer[i]);
            char * buffer = base64_encode((const uchar*)&cryptedBuffer[i], sizeof(cryptedBuffer[i]), &_output_length);
            printf("%s\n", buffer);
            fwrite(buffer, 1, 12, fichier2);
        }
        //free(buffer);
        //free(cryptedBuffer);
        *output_length += _output_length;
    }while (!feof(fichier));
    ;
    fseek(fichier, 0, SEEK_SET);
    fseek(fichier2, 0, SEEK_SET);
    fclose(fichier);
    fclose(fichier2)
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
        uint64 *cryptedBuffer = (uint64 *)base64_decode((const char *)buffer,_length,&_length);
        printf("%lu\n", cryptedBuffer);
        //RSAdecrypt(&cUnCrypt, cryptedBuffer, privKey);
        cUnCrypt = puissance_mod_n(cryptedBuffer,privKey.E,privKey.N);
        //fprintf(fichier2, "%c\n", (char)cUnCrypt);
        int * cDecrypt = &cUnCrypt;
        fwrite(cDecrypt, 1, 1, fichier2);
        free(cryptedBuffer);
    }while (!feof(fichier));

    fseek(fichier, 0, SEEK_SET);
    fseek(fichier2, 0, SEEK_SET);
    fclose(fichier);
    fclose(fichier2);
}