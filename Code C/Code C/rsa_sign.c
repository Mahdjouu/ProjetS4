#include "rsa_header.h"

void text2sha(char * inFilename, char *shaStr){
    FILE * fichier = NULL;
    if ((fichier = fopen(inFilename, "r")) == NULL){
        fprintf(stderr, "Erreur d'ouverture du fichier %s.\n", inFilename);
        fclose(fichier);
        return;
    }
    fseek(fichier, 0, SEEK_END);          
    long filelen = ftell(fichier);
    rewind(fichier);
    BYTE * temp = (BYTE *)malloc(filelen*(sizeof(BYTE)));
    fread(temp, 1, filelen, fichier);
    sha256ofString(temp, shaStr);
    free(temp);
    fclose(fichier);
}

/*tabUint64_t * signText(char *inFilename,rsaKey_t signKey){
    char digest[SHA256_BLOCK_SIZE*2 + 1];
    tabUint64_t * temp = (tabUint64_t *)malloc(sizeof(struct tabUint64_s));
    text2sha(inFilename, digest);
    size_t len_digest = strlen(digest);
    temp->dim = len_digest;
    temp->uint64array = (uint64 *)malloc(temp->dim*sizeof(uint64));
    for (int i = 0; i < len_digest; i++){
        RSAcrypt((unsigned char *)&digest[i], &temp->uint64array[i], signKey);
    }
    return temp;
}*/

tabUint64_t * signText(char *inFilename,rsaKey_t signKey){
    char digest[SHA256_BLOCK_SIZE*2 + 1];
    tabUint64_t * temp = (tabUint64_t *)malloc(sizeof(struct tabUint64_s));
    text2sha(inFilename, digest);
    size_t len_digest = strlen(digest);
    temp->dim = len_digest;
    temp->uint64array = (uint64 *)malloc(temp->dim*sizeof(uint64));
    for (int i = 0; i < len_digest; i++){
        RSAcrypt((unsigned char *)&digest[i], &temp->uint64array[i], signKey);
    }
    return temp;
}

void signatureDigest(tabUint64_t * cryptedBuffer, char * filename){
    FILE * fichier = NULL;
    if ((fichier = fopen(filename, "w")) == NULL){
        fprintf(stderr, "Erreur d'ouverture du fichier %s.\n", filename);
        fclose(fichier);
        return;
    }
    size_t len_buffer = cryptedBuffer->dim;
    size_t output_length;
    for (int i = 0; i < len_buffer; i++){
        char * buffer = base64_encode((const uchar*)&cryptedBuffer->uint64array[i], sizeof(cryptedBuffer->uint64array[i]),&output_length);
        fprintf(fichier, "%s", buffer);
        free(buffer);
    }
    fclose(fichier);
}

bool verifySignText(char *inFilename,tabUint64_t cryptAr, rsaKey_t verifyKey){
    bool res = false;
    char shaStr[SHA256_BLOCK_SIZE*2 + 1];
    text2sha(inFilename, shaStr);
    BYTE * temp = (BYTE *)malloc(MAX_BUFFER*sizeof(BYTE));
    for (int i = 0; i < cryptAr.dim; i++){
        RSAdecrypt(&temp[i], &cryptAr.uint64array[i], verifyKey);
    }
    if (strcmp(shaStr, temp) == 0){
        res = true;
    }
    free(temp);
    return res;
}

bool verifySignFileB64(char *inFileMsg,char * inFileSignB64,tabUint64_t cryptAr, rsaKey_t verifyKey){
    bool res = false;
    (void)cryptAr;
    FILE * fileB64 = NULL;
    if ((fileB64 = fopen(inFileSignB64, "r")) == NULL){
        fprintf(stderr, "Erreur d'ouverture du fichier crypté en Base 64 %s.\n", inFileSignB64);
        fclose(fileB64);
        return res;
    }
    char shaStr[SHA256_BLOCK_SIZE*2+1];
    char shaStr2[SHA256_BLOCK_SIZE*2+1];
    int i = 0;
    text2sha(inFileMsg, shaStr);
    size_t _length;
    char * buffer =(char *)malloc(12*sizeof(char));
    fgets(buffer, 13, fileB64);
    while (!feof(fileB64)){
        uint64 * cryptedBuffer = base64_decode(buffer,12,&_length);
        RSAdecrypt(&shaStr2[i], cryptedBuffer, verifyKey);
        i++;
        free(cryptedBuffer);
        fgets(buffer, 13, fileB64);
    }
    if (strcmp(shaStr, shaStr2) == 0){
        res = true;
    }
    return res;
}