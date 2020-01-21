#include "rsa_header.h"

void puissance_mod_n_gmp(mpz_t res,uint64 a, uint64 e, uint64 n) {
  /// /brief puissance modulaire, calcule a^e mod n
  /// avec GMP
  assert(a<n);
  mpz_t aa; // déclaration
  mpz_t ee;
  mpz_t nn;
  mpz_init (aa); // initialisation
  mpz_init (ee);
  mpz_init (nn);
  mpz_init (res);

  mpz_set_ui (aa, a); // affectation aa<-a
  mpz_set_ui (ee, e);
  mpz_set_ui (nn, n);
  mpz_powm (res, aa, ee, nn); // appel de la puissance modulaire de GMP
  // res <-aa^ee mod nn
}
