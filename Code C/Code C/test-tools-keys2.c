/// \author Vincent Dugat
/// \date summer 2019
#include "rsa_header.h"

FILE *logfp;

int main(int argc,char **argv){
  if (argc>1){
    logfp = fopen(argv[1],"w+");
    assert(logfp!=NULL);
  }
  else
    logfp = stdout;

// phase 1
  srand(time(NULL));
	rsaKey_t pubKey;
	rsaKey_t privKey;

  uint maxInt = 0xFFFFFFFF;
  uint minInt = maxInt/10;

  printf("max = %u, min = %u\n",maxInt,minInt);

  printf("Création des clefs aléatoires\n\n");
  genKeysRabin2(minInt,maxInt,&pubKey,&privKey);
	printKey(pubKey);
	printKey(privKey);

  return 0;
}
