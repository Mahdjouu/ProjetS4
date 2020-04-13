#include "rsa_header.h"

void interpreteur_commande(){
    int nbMots;
    char * commande[4];
    char temp[100];
    printf("> ");
    int length;
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
        if (strcmp(commande[0], "rmkeys") == 0){
            if (nbMots == 2){
                rm_keys(listkeys, atoi(commande[1]));
            }
            else{
                fprintf(stderr, " Usage : rmkeys <keyid>\n");
            }
        }


        // ######### NEWKEYS #########
        if (strcmp(commande[0], "newkeys") == 0){
            if (nbMots == 3){
                new_keys(listkeys, atoi(commande[1]), atoi(commande[2]));
            }
            else {
                fprintf(stderr, "Usage : newkeys <keyid> <type>\n");
            }
        }

        // ######### CRYPT #########

        if (strcmp(commande[0], "crypt") == 0){
            if(nbMots == 4){
                Node * myKey = list_id(listkeys,atoi(commande[3]));
                if(myKey->type == CHIFFREMENT){
                    rsaKey_t pubKey = myKey->keyPair.pubKey;
                    RSAcryptFile(commande[1], commande[2], myKey->keyPair.pubKey, &length);
                }
                else{
                    fprintf(stderr, "<keyid> doit être une clé de chiffrement\n");
                }
            }
            else{
                fprintf(stderr, "Usage : crypt <fileIn> <fileOut> <keyid>\n");
            }
        }

        // ######### UNCRYPT #########

        if (strcmp(commande[0], "uncrypt") == 0){
            if(nbMots == 4){
                Node *myKey = list_id(listkeys,atoi(commande[3]));
                if(myKey->type == CHIFFREMENT){
                    RSAunCryptFile(commande[1], commande[2], myKey->keyPair.privKey, length);
                }
                else{
                    fprintf(stderr, "<keyid> doit être une clé de chiffrement\n");
                }
            }
            else{
                fprintf(stderr, "Usage : uncrypt <fileIn> <fileOut> <keyid>\n");
            }
        }

        // ######### SAVE #########

        if (strcmp(commande[0], "save") == 0){
            char * fic = "default.txt";
            if (nbMots == 1){
                save(listkeys, &saveList, fic);
            }
        }

        // ######### SAVEPUB #########

        if (strcmp(commande[0], "savepub") == 0){
            if (nbMots == 3){
                savePub(listkeys, atoi(commande[1]), commande[2]);
            }
        }

        // ######### LOAD #########

        if (strcmp(commande[0], "load") == 0){
            if (nbMots != 2){
                fprintf(stderr, "Usage : load <file>");
            }
            else{
                load(listkeys, commande[1]);
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
    dest[a] = (char*)malloc(30*sizeof(char));
    while (source[i] != '\n'){
        if (source[i] != ' '){
            dest[a][e] = source[i];
            e++;
        }
        else{
            e = 0;
            a = a + 1;
            dest[a] = (char*)malloc(30*sizeof(char));
        }
        i++;
    }
    a++;
    return a;
}