#include "rsa_header.h"

FILE *logfp;

int main(){
    printf("\n##############################################\n");
    printf("########## PROJET S4 : Cryptage RSA ##########");
    printf("\n##############################################\n\n");
    logfp = stdout;
    interpreteur_commande();
    printf("Terminaison du programme...\n");
    return 0;
}

