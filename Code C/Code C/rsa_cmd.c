#include "rsa_header.h"

void interpreteur_commande(){
    int nbMots;
    char ** commande[4];
    char * temp[40];
    printf("> ");
    scanf(" %[^\n]", temp);
    List *listkeys = list_create();
    nbMots = cut_in_words(temp, commande);
    while ((strcmp(commande[0],"quit"))){
        if (!strcmp(commande[0], "listkeys")){
            if(!commande[1]){

            }
        }

        if (!strcmp(commande[0], "newkeys")){
            int keyid;
            int type;
            keyid = commande[1];
            type = commande[2];
            keyPair_t keyPair;
            genKeysRabin(&keyPair.pubKey, &keyPair.privKey);
            printKeyPair(keyPair);
        }








        // ######### On passe à la commande suivante ###########
        for (int i = 0; i < nbMots; i++){
            free(commande[i]);
        }
        fflush(stdout);
        printf("\n> ");
        scanf(" %[^\n]", temp);
        nbMots = cut_in_words(temp, commande);
    }
}

int cut_in_words(const char * source, char ** dest){
    int i;
    int e = 0;
    int a = 0;
    dest[a] = (char*)malloc(10*sizeof(char));
    for (i = 0; source[i] != '\0'; i++){
        if (source[i] != ' '){
            dest[a][e] = source[i];
            e++;
        }
        else{
            e = 0;
            a = a + 1;
            dest[a] = (char*)malloc(10*sizeof(char));
        }
    }
    if (dest[a][e] == '\n'){

    }
    a++;
    return a;
}