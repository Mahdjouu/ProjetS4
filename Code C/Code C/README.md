 ##Pour tester la fonction de Bézout (bezout.c)
 gcc test-bezout.c bezout.c rsa_tools.c -o bezout

 ##Pour tester la phase 1 en entier :
 make -f Makefile-phase1

 Enlevez du makefile les fichiers qui ne sont pas encore développés

##Pour tester la conversion de binaire en base64
make -f Makefile-base64

##Pour tester la conversion de 4 octets en uint et vice-verça

gcc test-blocs.c int2char.c -o test-blocs 

## Test du reste du code
Les fichiers de tests et éventuellement les Makefiles correspondants arriveront un peu plus tard. 