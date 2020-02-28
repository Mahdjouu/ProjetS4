/// \file phase2-2.c
/// \brief test de la phase 2.2 

#include "rsa_header.h"
const int batch_length = 4;
FILE *logfp;

int main(){
  logfp = stdout;

  rsaKey_t pubKey = {7,5141};
  rsaKey_t privKey = {4279,5141};

  int nbCar;
  printf("Chiffement du message...\n");
  RSAcryptFile("Data/msg.txt","Data/res.txt",pubKey, &nbCar);
  printf("Fini, %d caractères lus\n",nbCar);
  printf("Chiffement du message...\n");
  RSAunCryptFile("Data/res.txt","Data/msg_decrypt.txt",privKey, nbCar);
  printf("Fini, %d caractères lus\n",nbCar);
  return 0;
}