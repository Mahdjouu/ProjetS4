#include "rsa_header.h"

void RSAcrypt(unsigned char *msg, uint64 *cryptedMsg, rsaKey_t pubKey){
    for (int i = 0; msg[i] != '\0'; i++){
        cryptedMsg[i] = puissance_mod_n(msg[i], pubKey.E, pubKey.N);
    }
    *(cryptedMsg+1) = '\0';
}

void RSAdecrypt(unsigned char *msg, uint64 *cryptedMsg, rsaKey_t privKey){
    for (int i = 0; cryptedMsg[i] != '\0'; i++){
        msg[i] = (char)puissance_mod_n(cryptedMsg[i], privKey.E, privKey.N);
    }
    *(msg+1) = '\0';
}