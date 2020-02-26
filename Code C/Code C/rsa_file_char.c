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
    
    // unsigned char buffer[MAX_BUFFER];

    int i = 0;
    
    uint64 cryptedBuffer[MAX_BUFFER];

    char caractereActuel;
    caractereActuel = fgetc(fichier);
    while (caractereActuel != EOF){
        uchar * tab4bytes = (uchar *)malloc(4*sizeof(uchar));
        RSAcrypt(&caractereActuel, &cryptedBuffer[i], pubKey);
        cryptedBuffer[i] = base64_encode(&cryptedBuffer[i], sizeof(uint64), output_length);
        fwrite(cryptedBuffer[i], 1, 1, fichier2);
        caractereActuel = fgetc(fichier);
        free(tab4bytes);
        i++;
    }
    
    fclose(fichier);
    
    fclose(fichier2);
    
    fseek(fichier, 0, SEEK_SET);
    
    fseek(fichier2, 0, SEEK_SET);
}


void RSAunCryptFile(char *inFilename,char *outFilename,rsaKey_t privKey, int length){

    FILE * fichier = NULL;
    FILE * fichier2 = NULL;
    if ((fichier = fopen(inFilename, "rb")) == NULL){
        fprintf(stderr, "Erreur ouverture du fichier %s.\n", inFilename);
    }
    if ((fichier2 = fopen(outFilename, "w")) == NULL){
        fprintf(stderr, "Erreur ouverture du fichier %s.\n", outFilename);
    }
    uint64 *cryptedBuffer = NULL;
    char buffer[MAX_BUFFER];
    char buffer2[MAX_BUFFER];
    do{
        fgets(buffer, MAX_BUFFER,fichier);
        strpy(cryptedBuffer, base64_decode(buffer, length, &length));
        RSAdecrypt(buffer2,cryptedBuffer, privKey);
        fwrite(buffer2, 1, 512, fichier2);
    }while (!feof(fichier));

    fclose(fichier);

    fclose(fichier2);

    fseek(fichier, 0, SEEK_SET);

    fseek(fichier2, 0, SEEK_SET);

}