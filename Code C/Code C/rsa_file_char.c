#include "rsa_header.h"

void RSAcryptFile(char *inFilename, char *outFilename, rsaKey_t pubKey, int *output_length){
    FILE * fichier = fopen(inFilename, "r");
    FILE * fichier2 = fopen(outFilename, "w");
    char *buffer = (char*)malloc(MAX_BUFFER*sizeof(char));
    int i = 0;
    size_t _output_length = (size_t)*output_length;
    uint64 *cryptedBuffer = (uint64 *)malloc(MAX_BUFFER*sizeof(uint64));
    while (!feof(fichier)){
        fgets(buffer, MAX_BUFFER, fichier);
        for (i = 0; buffer[i] != '\0'; i++){
            RSAcrypt((unsigned char*)&buffer[i], &cryptedBuffer[i], pubKey);
            char * buffer2 = base64_encode((const uchar*)&cryptedBuffer[i], sizeof(cryptedBuffer[i]), &_output_length);
            fwrite(buffer2, 1, 12, fichier2);
            free(buffer2);
        }
        *output_length += _output_length;
    }
    free(buffer);
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
    fgets(buffer, 13, fichier);
    while (!feof(fichier)){
        uint64 * cryptedBuffer = base64_decode(buffer,12,&_length);
        RSAdecrypt(&cUnCrypt, cryptedBuffer, privKey);
        fprintf(fichier2, "%c", (char)cUnCrypt);
        free(cryptedBuffer);
        fgets(buffer, 13, fichier);
    }
    free(buffer);
    fclose(fichier);
    fclose(fichier2);
    fseek(fichier, 0, SEEK_SET);
    fseek(fichier2, 0, SEEK_SET);
}