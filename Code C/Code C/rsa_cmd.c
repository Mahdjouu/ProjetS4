#include "rsa_header.h"

void interpreteur_commande(){
    int nbMots;
    char ** commande = (char**)malloc(4*sizeof(char*));
    char * temp = (char*)malloc(40*sizeof(char));
    printf("> ");
    scanf("%[^\n]", temp);
    nbMots = cut_in_words(temp, commande);
    while ((strcmp(commande[0],"quit"))){
        printf("> Instruction finit\n");
        printf("> On passe à la prochaine instruction...\n");
        for (int i = 0; i <= nbMots; i++){
            free(commande[i]);
        }
        printf("> ");
        scanf("%[^\n]", temp);
        nbMots = cut_in_words(temp, commande);
    }
    free(commande[0]);
    free(commande);
    free(temp);
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
    printf("\n");
    return a;
}