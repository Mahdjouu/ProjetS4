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
    uchar * buffer = (uchar*)malloc(BLOCK_SIZE*sizeof(uchar));
    uint64 cryptedBuffer;
    uint temp;
    size_t _output_length;
    do{
        fgets(buffer, BLOCK_SIZE, fichier);
        temp = convert_4byte2int(buffer);
        cryptedBuffer = RSAcrypt1BlockGmp(temp, pubKey);
        char * buffer2 = base64_encode(&cryptedBuffer,sizeof(uint64),&_output_length);
        fprintf(fichier2, "%s", buffer2);
        free(buffer2);
    }while (!feof(fichier));
    free(buffer);
    fseek(fichier, 0, SEEK_SET);
    fseek(fichier2, 0, SEEK_SET);
    fclose(fichier);
    fclose(fichier2);
}

void RSAfile_decrypt(char *inFilename,char *outFilename,rsaKey_t privKey){
    FILE * fichier = fopen(inFilename, "r");
    FILE * fichier2 = fopen(outFilename, "w");
    uchar *buffer = (uchar*)malloc(BLOCK_SIZE*sizeof(uchar));
    uint temp;
    size_t output_length;
    char * buffer2 = malloc(12);
    fread(buffer2, 12, 1, fichier);
    while (!feof(fichier)){
        uint64 * cryptedBuffer = (uint64 *)base64_decode(buffer2, 12, &output_length);
        temp = RSAdecrypt1BlockGmp(*cryptedBuffer, privKey);
        convertInt2uchar(temp, buffer);
        fprintf(fichier2, "%s", buffer);
        fread(buffer2, 12, 1, fichier);
        free(cryptedBuffer);
    }
    free(buffer2);
    free(buffer);
    fclose(fichier);
    fclose(fichier2);
    fseek(fichier, 0, SEEK_SET);
    fseek(fichier2, 0, SEEK_SET);
}