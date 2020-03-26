#include "rsa_header.h"

uint64 RSAcrypt1BlockGmp(uint64 blockInt, rsaKey_t pubKey){
    mpz_t crypted;
    uint64 res;
    puissance_mod_n_gmp(crypted, blockInt,pubKey.E, pubKey.N);
    res =  mpz_get_ui(crypted);
    return res;
}

uint64 RSAdecrypt1BlockGmp(uint64 blockInt, rsaKey_t privKey){
    mpz_t decrypted;
    uint64 res;
    puissance_mod_n_gmp(decrypted, blockInt, privKey.E, privKey.N);
    res = mpz_get_ui(decrypted);
    return res;
}

void RSAfile_crypt(char *inFilename,char *outFilename, rsaKey_t pubKey){
    FILE * fichier = fopen(inFilename, "r");
    FILE * fichier2 = fopen(outFilename, "w");
    uchar buffer[5];
    uint64 cryptedBuffer;
    uint temp;
    fgets(buffer, 5, fichier);
    do{
        printf("buffer = %s\n", buffer);
        temp = convert_4byte2int(buffer);
        cryptedBuffer = RSAcrypt1BlockGmp(temp, pubKey);
        fprintf(fichier2, "%lu\n", cryptedBuffer);
        fgets(buffer, 5, fichier);
    }while (!feof(fichier));
    fseek(fichier, 0, SEEK_SET);
    fseek(fichier2, 0, SEEK_SET);
    fclose(fichier);
    fclose(fichier2);
}

void RSAfile_decrypt(char *inFilename,char *outFilename,rsaKey_t privKey){
    FILE * fichier = fopen(inFilename, "r");
    FILE * fichier2 = fopen(outFilename, "w");
    uchar buffer[5];
    uint64 cryptedBuffer;
    uint temp;
    fscanf(fichier, "%lu", &cryptedBuffer);
    do{
        temp = RSAdecrypt1BlockGmp(cryptedBuffer, privKey);
        convertInt2uchar(temp, buffer);
        fprintf(fichier2, "%s", buffer);
        fscanf(fichier, "%lu", &cryptedBuffer);
    }while (!feof(fichier));
    fclose(fichier);
    fclose(fichier2);
    fseek(fichier, 0, SEEK_SET);
    fseek(fichier2, 0, SEEK_SET);
}