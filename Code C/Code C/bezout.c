// Entrée : a, b entiers (naturels)
// Sortie : r entier (naturel) et  u, v entiers relatifs tels que r = pgcd(a, b) et r = a*u+b*v
//
// Initialisation : r := a, r' := b, u := 1, v := 0, u' := 0, v' := 1
// 								 q  quotient entier
// 								 rs, us, vs  variables de stockage intermédiaires
//
// les égalités r = a*u+b*v et r' = a*u'+b*v' sont des invariants de boucle
//
// tant que (r' ≠ 0) faire
// 	 q := r÷r'
// 	 rs := r, us := u, vs := v,
// 	 r := r', u := u', v := v',
// 	 r' := rs - q*r', u' = us - q*u', v' = vs - q*v'
// 	fait
// renvoyer (r, u, v)
#include "rsa_header.h"

long bezout(uint a,uint b,long *u,long *v){
/// \pre a, b entier naturels
/// \post r entier (naturel) et  u, v entiers relatifs tels que r = pgcd(a, b) et r = a*u+b*v
/// \param[in] : a, b entiers (naturels)
/// \param[out] : u, v entiers relatifs tels que r = pgcd(a, b) et r = a*u+b*v
/// \returns r entier
 	long r = a;
	long rp = b;
  *u = 1;
  *v = 0;
	long up = 0;
	long vp = 1;
	long rs,vs,us,q;
 	while (rp != 0){
    assert(r = a*(*u) + b*(*v));
    assert(rp = a * up + b * vp);
    q = r / rp;
    rs = r;
    us = *u;
    vs = *v;
    r = rp;
    *u = up;
    *v = vp;
    rp = rs - (q * rp);
    up = us - (q * up);
    vp = vs - (q * vp);
   }
	return r;
}

long bezoutRSA(uint a,uint b,long *u,long *v){
  /// \brief récupère (r,u,v) de Bézout. Si u est négatif on le remplace par
  /// \brief le premier qui est supérieur à 2
  long r = bezout(a,b,u,v);
  while (*u<=2){
    *u = *u+b;
  }
  return *u;
}
