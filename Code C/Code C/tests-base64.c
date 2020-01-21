
#include "rsa_header.h"
const int batch_length = 4;
FILE *logfp;

int main(){
  logfp = stdout;
  int output_length;
  printf("Petite mise au point...\n");
  printf("tailles : int=%lu ; long long=%lu ; uint=%lu\n",sizeof(int),sizeof(long long int),sizeof(uint));

  // TESTS
  uint nbb=123456789;
  uchar *strTest=base64_encode(&nbb,sizeof(uint),&output_length);
  printf("NB->B64 : nb=%u->b64=%s nbcar==%d ; ",nbb,strTest,output_length);
  uint *intRes;
  intRes = base64_decode(strTest,output_length,&output_length);
  printf("B64->NB : nb=%u\n",*intRes);
  assert(nbb == *intRes);

// plus fort
  block_t test = {'a','b','c','d'};
  uchar *tabRes = malloc(BLOCK_SIZE*sizeof(uchar));
  uchar *tabRes2 = malloc(BLOCK_SIZE*sizeof(uchar));

  uint rest = convert_4byte2int(test);// abcd en uint
  printf("\n\ntab->uint=%u ; ",rest);
  strTest=base64_encode(&rest,sizeof(uint),&output_length);
  printf("uint->b64=%s, nbcar=%d\n",strTest,output_length);

  intRes = base64_decode(strTest,output_length,&output_length);
  printf("b64->uint=%u ; ",*intRes);
  convertInt2uchar(*intRes,tabRes2);
  printf(" int->tabcar=%s\n",tabRes2);

  // avec des uint64
  printf("Avec des uint64 \n");
  uint64 rest2 = convert_4byte2int(test);// abcd en uint
  printf("\n\ntab->uint=%lu ; ",rest2);
  strTest=base64_encode(&rest2,sizeof(uint64),&output_length);
  printf("uint->b64=%s, nbcar=%d\n",strTest,output_length);

  uint64 *intRes2 = base64_decode(strTest,output_length,&output_length);
  printf("b64->uint=%lu ; ",*intRes2);
  convertInt2uchar(*intRes,tabRes2);
  printf(" int->tabcar=%s\n",tabRes2);

  return 0;
}
