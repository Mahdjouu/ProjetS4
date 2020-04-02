/// \file rsa_header.h
/// \author Vincent Dugat
/// \date august 2019
#ifndef RSA_H
#define RSA_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include "Sha-256/Sha-256/sha256_utils.h"
#include <gmp.h>

#define MAX_U_INT 4294967296
#define MAX_U_INT64 18446744073709551616
#define OK 0
#define ERREUR -1
#define READ_ERROR -1
#define BLOCK_SIZE 4 // octets
#define BLOCK_BASE_64 12
#define NAME_MAX_SIZE 32 // caractères
#define MAX_STR 10 //
#define MAX_BUFFER 512

#define CHIFFREMENT 47
#define SIGNATURE 48

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAXI(a,b) (((a)>(b))?(a):(b))

extern FILE * logfp;

typedef unsigned long int uint64;
typedef unsigned int uint; // même taille que int aka uint32
typedef unsigned char uchar; // 8 bits = octet aka uint8

/* Type of a block of data */
typedef uchar block_t[BLOCK_SIZE]; // une case par octet

typedef struct tabUint64_s{
	uint64 * uint64array;
	int dim;
} tabUint64_t;

typedef struct rsaKey_s {
	uint64 E;// exposant
	uint64 N;// modulo
} rsaKey_t;

// struct pour définir une paire de clefs
typedef struct keyPair_s {
	rsaKey_t pubKey; // (C,N)
	rsaKey_t privKey; //(U,N)
} keyPair_t;

// struct pour la gestion des clefs avec l'interpréteur de commande

typedef struct s_List List;
typedef struct node_Keys Node;
typedef List * ptrList;
typedef int(*SimpleFunctor)(int, int);

// Fonction pour utiliser les listes

List *list_create();
List *list_push_back(List *l, int identificateur, int type, keyPair_t keyPair) ;

// prototypes de sp
void erreur(char* msg); // pour afficher les msg d'erreurs
uint random_uint(uint min,uint max);
int premier (uint n);
int decompose (uint facteur[], uint64 n);
uint puissance(uint a, uint e);
uint64 puissance_mod_n (uint64 a, uint64 e, uint64 n);
uint genereUint(uint max,int *cpt);
int rabin (uint a, uint n);
uint genereUintRabin(uint max,int *cpt);
uint pgcdFast(uint a,uint b); // permet de calculer rapidement le PGCD de a et b
void genKeysRabin(rsaKey_t *pubKey,rsaKey_t *privKey);
void inputKey(uint64 E,uint64 N,rsaKey_t *key);

// phase 1
int decompose (uint facteur[], uint64 n) ; // reçoit n, remplit le tableau de facteurs premiers (realloc)
uint64 puissance_mod_n (uint64 a, uint64 e, uint64 n); // puissance modulaire
long bezoutRSA(uint a,uint b,long *u,long *v); // Bézout
void printKey(rsaKey_t key);
void printUint64Array(tabUint64_t tab);
void genKeysRabin(rsaKey_t *pubKey,rsaKey_t *privKey);

//phase 2
void RSAcrypt(unsigned char *msg, uint64 *cryptedMsg, rsaKey_t pKey);
void RSAdecrypt(unsigned char *msg, uint64 *cryptedMsg, rsaKey_t privKey);
uint convert_4byte2int(uchar *b);
void printBlock(block_t blk);
void convertInt2uchar(uint nb,uchar *tab4bytes);
char *base64_encode(const uchar *data,size_t input_length,size_t *output_length);
unsigned char *base64_decode(const char *data,size_t input_length,size_t *output_length);

// avec les blocs
uint64 RSAcrypt1BlockGmp(uint64 blockInt, rsaKey_t pubKey);
uint64 RSAdecrypt1BlockGmp(uint64 blockInt, rsaKey_t privKey);

// avec les fichiers
void RSAfile_crypt(char *inFilename,char *outFilename, rsaKey_t pubKey);
void RSAfile_decrypt(char *inFilename,char *outFilename,rsaKey_t privKey);
void RSAcryptFile(char *inFilename, char *outFilename, rsaKey_t pubKey, int *output_length);
void RSAunCryptFile(char *inFilename,char *outFilename,rsaKey_t privKey, int length);

// signature
tabUint64_t * signText(char *inFilename,rsaKey_t signKey);
void inputKey(uint64 E,uint64 N,rsaKey_t *key);
tabUint64_t * string2intBlocks(uchar *str);
uchar * num2string(tabUint64_t numArray);
uint64 * giveMeMem(int dim);
tabUint64_t * RSAcryptUint64(tabUint64_t numMsg,rsaKey_t pubKey);
tabUint64_t * RSAunCryptUint64(tabUint64_t numMsgC,rsaKey_t privKey);
// GMP
void mersenneGmp(mpz_t resGmp,uint64 max,uint64 p); // ovni
void printKeyPair(keyPair_t keyPair);
char * verifySignText(char *inFilename,tabUint64_t cryptAr, rsaKey_t verifyKey);
void puissance_mod_n_gmp(mpz_t res,uint64 a, uint64 e, uint64 n); // puis mod avec gmp

// RSA COMMANDE

void interpreteur_commande();
int cut_in_words(const char * source, char ** dest);
#endif

