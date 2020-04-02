#include "rsa_header.h"

void interpreteur_commande(){
    int nbMots;
    char * commande[4];
    char temp[40];
    printf("> ");
    fgets(temp, "%[^\n]", stdin);
    List *listkeys = list_create();
    nbMots = cut_in_words(temp, commande);
    while (strcmp(commande[0],"quit") != 0){
        // ######### LIST KEYS #########
        if (strcmp(commande[0], "listkeys") == 0){
            if (nbMots == 2){
                list_keys(listkeys, 1, atoi(commande[1]));
            }
            else{
                list_keys(listkeys, 0, 0);
            }
        }

        // ######### RMKEYS #########


        // ######### NEWKEYS #########
        if (!strcmp(commande[0], "newkeys")){
            if (nbMots == 3){
                new_keys(listkeys, atoi(commande[1]), atoi(commande[2]));
            }
            else {
                fprintf(stderr, "Usage : newkeys <keyid> <type>\n");
            }
        }

        // ######### On passe à la commande suivante ###########
        for (int i = 0; i < nbMots; i++){
            commande[i] = NULL;
            free(commande[i]);
        }
        // fflush(stdout);
        printf("\n> ");
        fgets(temp, "%[^\n]", stdin);
        nbMots = cut_in_words(temp, commande);
    }
}

int cut_in_words(const char * source, char ** dest){
    int i = 0;
    int e = 0;
    int a = 0;
    dest[a] = (char*)malloc(10*sizeof(char));
    while (source[i] != '\n'){
        if (source[i] != ' '){
            dest[a][e] = source[i];
            e++;
        }
        else{
            e = 0;
            a = a + 1;
            dest[a] = (char*)malloc(10*sizeof(char));
        }
        i++;
    }
    a++;
    return a;
}