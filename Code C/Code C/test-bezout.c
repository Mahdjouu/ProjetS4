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

// test de factorisation avec des uint64

  uint64 num1,num2,N,M;
  long U,V,E;
  int res;
// tests de calcul des clefs
// exemple "zeste de savoir"
  num1 = 53;
  num2 = 97;
  printf("\nCalcul des paramètres des clefs avec num1=%lu et num2=%lu\n",num1,num2);
  N = num1*num2;
  M = (num1-1)*(num2-1);
  assert(N==5141 && M == 4992);
  printf("N et M ok\n");
  E = 7;
  res = bezoutRSA(E,M,&U,&V);// aka algorithme d'Euclide étendu
  printf("U (aka E dans zeste de savoir)=%ld\n",U);
  assert(2<U && U<M);
  assert(U==4279);
  printf("OK\n");
  return 0;
}
