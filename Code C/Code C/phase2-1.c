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
  clock_t now,end;
  srand(time(NULL));
	rsaKey_t pubKey;
	rsaKey_t privKey;

  printf("Création des clefs aléatoires\n\n");
  now = clock();
  genKeysRabin(&pubKey,&privKey);
  end = clock();
  printf("Clés générées en %lu secondes\n",(end-now)/CLOCKS_PER_SEC);
	printKey(pubKey);
	printKey(privKey);

// phase 2.1 : chiffrer, déchiffrer un message utf8 dans un tableau
  unsigned char msg[100] = "Mon preux Adalbéron, retrouve-moi en la Tour Magne à la minuit.";
  uint64 *crypt = malloc(100*sizeof(uint64));
  RSAcrypt(msg,crypt,pubKey);

  printf("Message à chiffrer : %s\n\n",msg);

  printf("Message chiffré (entiers) : %s\n\n",msg);
  for (int i=0;i<strlen(msg);i++){
    printf("%lu ",crypt[i]);
  }
  printf("\n\n");

  unsigned char *msgd = malloc(100*sizeof(unsigned char));
  RSAdecrypt(msgd,crypt,privKey);
  printf("Message déchiffré : %s\n",msgd);

  return 0;
}