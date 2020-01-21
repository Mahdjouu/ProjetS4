#include "rsa_header.h"

void printKey(rsaKey_t key){
	printf("key=(%lu,%lu)\n",key.E,key.N);
}

void printKeyPair(keyPair_t keyPair){
	printf("Public ");
	printKey(keyPair.pubKey);
	printf("Private ");
	printKey(keyPair.privKey);
}

void printUint64Array(tabUint64_t tab){
	for (int i=0;i<tab.dim;i++)
		printf("%lu ",tab.uint64array[i]);
	printf("\n");
}

uint64 * giveMeMem(int dim){
	return (uint64 *) malloc(dim*sizeof(uint64));
}

void printBlock(block_t blk){
	for(int i=0;i<BLOCK_SIZE;i++)
		printf("%c",blk[i]);
}
