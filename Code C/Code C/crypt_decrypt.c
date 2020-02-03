#include "rsa_header.h"

void RSAcrypt(unsigned char *msg, uint64 *cryptedMsg, rsaKey_t pubKey){
    for (int i = 0; i < strlen(msg); i++){
        cryptedMsg[i] = (uint64)msg[i]*(pubKey.E%pubKey.N);
    }
}

void RSAdecrypt(unsigned char *msg, uint64 *cryptedMsg, rsaKey_t privKey){
    for (int i = 0; cryptedMsg[i] != '\0'; i++){
        unsigned char c = cryptedMsg[i]*(privKey.E%privKey.N);
        msg[i] = c;
    }
}