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

// Phase 1.1 outils de théorie des nombres

// création de clefs,
// test de factorisation avec des uint64
printf("Validation de la factorisation\n");
	uint64 tab[10]={8,42,1245,78954,12465,23,12,741,8889895013,3865086887};
  uint64 prod; // pour vérif factorisation
  uint tabRes[10];
	for (int i=0;i<10;i++){
		int res = decompose(tabRes, tab[i]);
    printf("Factorisation de %lu : ",tab[i]);
    prod = 1;
		for (int i=0;i<res;i++){
      prod = prod *tabRes[i];
			printf("%d ",tabRes[i]);
    }
    printf(" ** vérif : prod=%lu ",prod);
    assert(prod == tab[i]);
    printf(" OK\n");
	}

  uint64 num1,num2,N,M;
  long U,V,C;
  int res;
// tests de calcul des clefs
// exemple "zeste de savoir"
  num1 = 53;
  num2 = 97;
  printf("\nCalcul des clefs avec num1=%lu et num2=%lu\n",num1,num2);
  N = num1*num2;
  M = (num1-1)*(num2-1);
  assert(N==5141 && M == 4992);
  C = 7;
  res = bezoutRSA(C,M,&U,&V);// aka algorithme d'Euclide étendu
  printf("U=%ld\n",U);
  assert(2<U && U<M);

  rsaKey_t pubKey = {C,N};
  rsaKey_t privKey = {U,N};
  printf("AVANT clé privée : U=%lu, N=%lu\n",privKey.E,privKey.N);
  printf("pub ");printKey(pubKey);
  printf("priv ");printKey(privKey);

  // test de factorisation des calculs précédents

  printf("\nRefactorisation..\n");
  res = decompose(tabRes, N);
  printf("Factorisation de %lu :\n",N);
  for (int i=0;i<res;i++)
    printf("%d ",tabRes[i]);
  printf("\n");

// test génération du nombres premiers et de clefs
  printf("test génération de nombres premiers et de clefs (Rabin)\n");
  genKeysRabin(&pubKey,&privKey);
  printf("pub ");printKey(pubKey);
  printf("priv ");printKey(privKey);

  printf("\nRefactorisation..\n");
  res = decompose(tabRes, pubKey.N);
  printf("Factorisation de %lu :\n",pubKey.N);
  assert(res==2);
  for (int i=0;i<res;i++)
    printf("%d ",tabRes[i]);
  printf("\n");
  return 0;
}
