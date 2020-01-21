/// \file rsa_tools.c
/// \author Vincent Dugat
/// \date summer 2019
/// \brief calculs sur les nombres premiers, génération de clefs RSA

#include "rsa_header.h"

void erreur(char* msg){
  printf("*** %s ***\n",msg);
  exit(-1);
}

uint random_uint(uint min,uint max){
/// \brief génère un uint aléatoire entre min et max
/// \param[in] min et max des uint
/// \return n : min≤n≤max
  return (rand()%(max-min)) + min;
}

int premier (uint n) {
/// \brief test de primarité, crible d'Erathostène
/// \returns 1 le nombre est premier, 0 sinon
  uint d;

  if (n % 2 == 0)
    return (n == 2);
  for (d = 3; d * d <= n; d = d + 2)
    if (n % d == 0)
      return 0;
  return 1;
}

int decompose (uint facteur[], uint64 n){
  /// \brief décompose un entier en facteurs premiers
  /// \param[in] : n l'entier
  /// \pram[out] : facteur = tableau de facteurs
  /// \returns la dimension du tableau facteur.
  uint d = 3;
  int i = 0;

  while (n % 2 == 0) {
    facteur[i++] = 2;
    n = n / 2;
  }
  while (d * d <= n)
    if (n % d == 0) {
      facteur[i++] = d;
      n = n / d;
    }
    else
      d = d + 2;
  if (n > 1)
    facteur[i++] = n;
  return i;
}

uint puissance(uint a, uint e) {
  /// \brief puissance russe
  /// \param[in] : a l'entier et e l'exposant
  /// \returns : a^e
  uint p;

  for (p = 1; e > 0; e = e / 2) {
    if (e % 2 != 0)
      p = (p * a);
    a = (a * a);
  }
  return p;
}

uint64 puissance_mod_n (uint64 a, uint64 e, uint64 n) {
  /// /brief puissance modulaire, calcule a^e mod n
  /// a*a peut dépasser la capacité d'un uint64
  // https://www.labri.fr/perso/betrema/deug/poly/exp-rapide.html
  uint64 p;
  for (p = 1; e > 0; e = e / 2) {
    if (e % 2 != 0)
      p = (p * a) % n;
    a = (a * a) % n;
  }
  return p;
}

uint genereUint(uint max,int *cpt){
  /// \brief génère un nombre premier inférieur à max
  /// \param[in] max : la borne sup
  /// \param[out] cpt : nombre d'essais
  /// \returns : le nombre premier
  uint num;
  *cpt=1;
  do{
    num = random_uint(17,max);
  } while (num%2!=1);

  while (!premier(num) && num<max){
    (*cpt)++;
    num=num+2;
  }
  if (num>=max)
    erreur("pb de génération de nombre premier (borne ?)\n");
  return num;
}

int rabin (uint a, uint n) {
  /// \brief test de Rabin sur la pimarité d'un entier
  /// \brief c'est un test statistique
  uint p, e, m;
  int i, k;

  e = m = n - 1;
  for (k = 0; e % 2 == 0; k++)
    e = e / 2;

  p = puissance_mod_n (a, e, n);
  if (p == 1) return 1;

  for (i = 0; i < k; i++) {
    if (p == m) return 1;
    if (p == 1) return 0;
    p = (p * p) % n;
  }

  return 0;
}

uint genereUintRabin(uint max,int *cpt){
  /// \brief fournit un nombre premier vérifié avec le test de rabin
  uint num;
  *cpt=1;
  int a=2;
  do{
    num = random_uint(17,max);
  } while (num%2!=1);

  while (!rabin(a,num) && num<max){
    (*cpt)++;
    num=num+2;
  }
  return num;
}

uint pgcdFast(uint a,uint b){
  /// \brief pgcd rapide de a et b
  /// \param[in] a et b les deux entiers
  /// \returns pgcd(a,b)
  uint pow2;
  // cas trivial ... PGCD(a,0)=a ou PGCD(0,b)=b
  // dans les deux cas : PGCD(a,b)=a+b si l'un des deux nombres est nul
  if(0==a || b==0) return a+b;
  // on s'occupe de toutes les puissances de deux contenues dans le PGCD(a,b)
  // PGCD( a=2^n.a' , b=2^n.b' )=2^n.PGCD(a',b')
  pow2 = 1u;
  while(!(a&1)) // tant que a est pair
    {
    if(!(b&1)) // si b est de plus pair
      {
      // PGCD( a=2.a' , b=2.b' )=2.PGCD(a',b')
      a     >>= 1;
      b     >>= 1;
      pow2  <<= 1;
      }
    else
      {
      // on rend <a> pair
      do a>>=1;while(!(a&1));
      break; // toutes les puissances de 2 du PGCD(a,b) ont ete traitees
      }
    }

  // on rend <b> pair
  while(!(b&1)) b>>=1;
  // ici les deux nombres sont pairs, le temps de calcul precedent est negligeable
  // devant ce qui suit...
  // information : la difference de deux nombres impairs est pair
  do
    {
    if(a==b)
      {
      break; // bingo ! PGCD(a,b)=a
      }
    else if(a > b)
      {
      a -= b; // PGCD(a,b)=PGCD(a-b,b)
      do a>>=1;while(!(a&1)); // on peut rendre <a> pair car on a plus de puissance de deux dans le PGCD
      }
    else // b > a
      {
      b -= a; // PGCD(a,b)=PGCD(a,b-a)
      do b>>=1;while(!(b&1)); // on peut rendre <b> pair car on a plus de puissance de deux dans le PGCD
      }
    }while(1);

return pow2*a;
} // pgcdFast()

void genKeysRabin(rsaKey_t *pubKey,rsaKey_t *privKey){
  /// \brief génère une paire de clefs
  /// \param[out] pubKey : clef publique
  /// \param[out] privKey : clef privée
  ///
  int cpt1,cpt2;
  uint64 num1 = genereUintRabin(2000,&cpt1);
  uint64 num2 = genereUintRabin(2000,&cpt2);

  fprintf(logfp,"num1=%lu, cpt1=%d\n",num1,cpt1);
  fprintf(logfp,"num2=%lu, cpt2=%d\n",num2,cpt2);
  uint64 N = num1*num2;
  uint64 M = (num1-1)*(num2-1);

  uint C = 2;
  // recherche d'un nombre premier avec M
  while (pgcdFast(C,M)!=1 && C<M){
    C++;
  }
  assert(C<M);
  long U,V;
  long res = bezoutRSA(C,M,&U,&V);
  assert(2<U && U<M);
  fprintf(logfp,"N=%lu, M=%lu, C=%u, U=%ld, V=%ld\n",N,M,C,U,V);

  pubKey->E = C;
  pubKey->N = N;
  privKey->E = U;
  privKey->N = N;
}

void inputKey(uint64 E,uint64 N,rsaKey_t *key){
  /// \brief pour debug : permet de saisir une clef
  /// \note ça peut servir... ou pas.
  printf("Entrez l'exposant : ");
  scanf("%lu",&E);
  printf("\nEntrez le modulo : ");
  scanf("%lu",&N);
  key->E = E;
  key->N = N;
}
