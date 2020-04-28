/// \author Vincent Dugat
/// \date summer 2019
/// \brief test de signature de documents
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
  rsaKey_t pubKey = {23,8889895013};
  rsaKey_t privKey = {3865086887,8889895013};

// phase 4
  tabUint64_t * cryptedMsg;
  rsaKey_t signKey = {privKey.E,privKey.N};
  rsaKey_t verifyKey = {pubKey.E,pubKey.N};
  cryptedMsg = signText("Data/msg.txt",signKey);
  //printf("hash signé (chiffré) :\n");
  //printUint64Array(*cryptedMsg);
	// trad b64+fichier
  printf("Vérification de la signature et du hash du message : \n");
  bool res = verifySignText("Data/msg.txt",*cryptedMsg,verifyKey);
  printf("Valide : %d\n",res);
  return 0;
}
