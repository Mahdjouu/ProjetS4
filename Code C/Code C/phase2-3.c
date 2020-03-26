#include "rsa_header.h"
const int batch_length = 4;
FILE *logfp;

int main(){
  logfp = stdout;

  rsaKey_t pubKey = {23,8889895013};
  rsaKey_t privKey = {3865086887,8889895013};

  RSAfile_crypt("Data/msg.txt","Data/res.txt",pubKey);
  RSAfile_decrypt("Data/res.txt","Data/msg_decrypt.txt",privKey);
  return 0;
}