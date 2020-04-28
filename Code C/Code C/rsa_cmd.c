#include "rsa_header.h"

void interpreteur_commande(){
    int nbMots;
    char * commande[4];
    char * temp = NULL;
    int length;
    char userenv[100];
    while(!saisie_mdp());
    sprintf(userenv, "@%s> ", getenv("USER"));
    temp = readline(userenv);
    List *listkeys = list_create();
    nbMots = cut_in_words((const char *)temp, commande);
    while (strcmp(commande[0],"quit") != 0){
        // ######### LIST KEYS #########
        if (strcmp(commande[0], "listkeys") == 0){
            if (nbMots > 2){
                fprintf(stderr, "Usage : listkeys [<keyid>]\nkeyid : entier\n");
            }
            if (nbMots == 2){
                if (isNumber(commande[1])){
                    list_keys(listkeys, 1, atoi(commande[1]));
                }
                else{
                    fprintf(stderr, "Usage : listkeys [<keyid>]\nkeyid : entier\n");
                }
            }
            else{
                list_keys(listkeys, 0, 0);
            }
        }

        // ######### RMKEYS #########
        if (strcmp(commande[0], "rmkeys") == 0){
            if (nbMots == 2){
                if (isNumber(commande[1])){
                    rm_keys(listkeys, atoi(commande[1]));
                }
                else{
                    fprintf(stderr, "Usage : rmkeys <keyid>\nkeyid : entier\n");
                }
            }
            else{
                fprintf(stderr, "Usage : rmkeys <keyid>\nkeyid : entier\n");
            }
        }


        // ######### NEWKEYS #########
        if (strcmp(commande[0], "newkeys") == 0){
            if (nbMots == 3){
                if (isNumber(commande[1])){
                    if (isType(commande[2])){
                        new_keys(listkeys, atoi(commande[1]), quelType(commande[2]));
                    }
                    else{
                        fprintf(stderr, "Usage : newkeys <keyid> <type>\nkeyid : entier\ntype : \"chiffrement\"/\"signature\"\n");
                    }
                }
                else{
                    fprintf(stderr, "Usage : newkeys <keyid> <type>\nkeyid : entier\ntype : \"chiffrement\"/\"signature\"\n");
                }
            }
            else {
                fprintf(stderr, "Usage : newkeys <keyid> <type>\nkeyid : entier\ntype : \"chiffrement\"/\"signature\"\n");
            }
        }

        // ######### CRYPT #########
        if (strcmp(commande[0], "crypt") == 0){
            if(nbMots == 4){
                if (isNumber(commande[3])){
                    Node * myKey = list_id(listkeys,atoi(commande[3]));
                    if(myKey->type == CHIFFREMENT){
                        rsaKey_t pubKey = myKey->keyPair.pubKey;
                        RSAcryptFile(commande[1], commande[2], myKey->keyPair.pubKey, &length);
                    }
                    else{
                        fprintf(stderr, "Usage : crypt <fileIn> <fileOut> <keyid>\nkeyid : entier (doit être une clé de chiffrement)\n");
                    }
                }
                else{
                    fprintf(stderr, "Usage : crypt <fileIn> <fileOut> <keyid>\nkeyid : entier (doit être une clé de chiffrement)\n");
                }
            }
            else{
                fprintf(stderr, "Usage : crypt <fileIn> <fileOut> <keyid>\nkeyid : entier (doit être une clé de chiffrement)\n");
            }
        }

        // ######### UNCRYPT #########

        if (strcmp(commande[0], "uncrypt") == 0){
            if(nbMots == 4){
                if (isNumber(commande[3])){
                    Node *myKey = list_id(listkeys,atoi(commande[3]));
                    if(myKey->type == CHIFFREMENT){
                        RSAunCryptFile(commande[1], commande[2], myKey->keyPair.privKey, length);
                    }
                    else{
                        fprintf(stderr, "Usage : uncrypt <fileIn> <fileOut> <keyid>\nkeyid : entier (doit être une clé de chiffrement)\n");
                    }
                }
                else{
                    fprintf(stderr, "Usage : uncrypt <fileIn> <fileOut> <keyid>\nkeyid : entier (doit être une clé de chiffrement)\n");
                }
            }
            else{
                fprintf(stderr, "Usage : uncrypt <fileIn> <fileOut> <keyid>\nkeyid : entier (doit être une clé de chiffrement)\n");
            }
        }

        // ######### SAVE #########

        if (strcmp(commande[0], "save") == 0){
            if (nbMots == 1){
                char * fic = "default.txt";
                save(listkeys, &saveList, fic);
            }
            else if(nbMots == 2){
                save(listkeys, &saveList, commande[1]);
            }
            else{
                fprintf(stderr, "Usage : save [<fileOut>]\nfileOut : fichier de sauvegarde (par défault \"default.txt\")");
            }
        }

        // ######### SAVEPUB #########

        if (strcmp(commande[0], "savepub") == 0){
            if (nbMots == 3){
                if (isNumber(commande[1])){
                    savePub(listkeys, atoi(commande[1]), commande[2]);
                }
                else{
                    fprintf(stderr, "Usage : savepub <keyid> <file>\nkeyid : entier\nfile : fichier de sauvegarde de la clé\n");
                }
            }
            else{
                fprintf(stderr, "Usage : savepub <keyid> <file>\nkeyid : entier\nfile : fichier de sauvegarde de la clé\n");
            }
        }

        // ######### LOAD #########

        if (strcmp(commande[0], "load") == 0){
            if (nbMots == 2){
                load(listkeys, commande[1]);
            }
            else if (nbMots == 1){
                load(listkeys, "default.txt");
            }
            else{
                fprintf(stderr, "Usage : load [<file>]\nfile : fichier de sauvegarde à charger (\"default.txt\" âr défaut sinon)");
            }
        }

        // ######### SHOW #########
        if (strcmp(commande[0], "show") == 0){
            if (commande[1] != NULL){
                if (isNumber(commande[1])){
                    show(listkeys, atoi(commande[1]), nbMots, commande);
                }
                else{
                    fprintf(stderr, "Usage : show <keyid> [\"pub\"] [\"priv\"]\nkeyid : entier (clé)\n");
                    fprintf(stderr, "pub : argument pour afficher la clé publique\npriv : argument pour afficher la clé privé\n");
                }
            }
            else{
                fprintf(stderr, "Usage : show <keyid> [\"pub\"] [\"priv\"]\nkeyid : entier (clé)\n");
                fprintf(stderr, "pub : argument pour afficher la clé publique\npriv : argument pour afficher la clé privé\n");
            }
        }

        // ######### SIGNTEXT #########

        if (strcmp(commande[0], "signtext") == 0){
            if (nbMots == 4){
                if(isNumber(commande[2])){
                    Node *myKey = list_id(listkeys,atoi(commande[2]));
                    if(myKey->type == SIGNATURE){
                        signtext(commande[1], myKey->keyPair.privKey, commande[3]);
                    }
                    else{
                        fprintf(stderr, "Usage : signtext <filein> <keyid> <fileout>\nfilein : nom du fichier en entrée\nkeyid : entier (doit être une clé de signature)\n");
                        fprintf(stderr, "fileout : fichier de sortie\n");
                    }
                }
                else{
                    fprintf(stderr, "Usage : signtext <filein> <keyid> <fileout>\nfilein : nom du fichier en entrée\nkeyid : entier (doit être une clé de signature)\n");
                    fprintf(stderr, "fileout : fichier de sortie\n");
                }
            }
            else{
                fprintf(stderr, "Usage : signtext <filein> <keyid> <fileout>\nfilein : nom du fichier en entrée\nkeyid : entier (doit être une clé de signature)\n");
                fprintf(stderr, "fileout : fichier de sortie\n");
            }
        }

        // ######### VERIFYSIGN #########

        if (strcmp(commande[0], "verifysign") == 0){
            if (nbMots == 4){
                if (isNumber(commande[3])){
                    Node *myKey = list_id(listkeys,atoi(commande[3]));
                    if (myKey->type == SIGNATURE){
                        verifysign(commande[1], commande[2], myKey->keyPair.pubKey);
                    }
                    else{
                        fprintf(stderr, "Usage : verifysign <filein> <filesign> <keyid>\nfilein : Nom du fichier en entrée\n");
                        fprintf(stderr, "filesign : Nom du fichier contenant la signature\nkeyid : entier (doit être une clé de signature)\n");
                    }
                }
                else{
                    fprintf(stderr, "Usage : verifysign <filein> <filesign> <keyid>\nfilein : Nom du fichier en entrée\n");
                    fprintf(stderr, "filesign : Nom du fichier contenant la signature\nkeyid : entier (doit être une clé de signature)");
                }
            }
            else{
                fprintf(stderr, "Usage : verifysign <filein> <filesign> <keyid>\nfilein : Nom du fichier en entrée\n");
                fprintf(stderr, "filesign : Nom du fichier contenant la signature\nkeyid : entier (doit être une clé de signature)");
            }
        }

        // ######### On passe à la commande suivante ###########
        for (int i = 0; i < nbMots; i++){
            free(commande[i]);
            commande[i] = NULL;
        }
        add_history(temp);
        free(temp);
        temp = NULL;
        fflush(stdout);
        temp = readline(userenv);
        nbMots = cut_in_words((const char *)temp, commande);
    }
    free(temp);
    temp = NULL;
}

int cut_in_words(const char * source, char ** dest){
    int i = 0;
    int e = 0;
    int a = 0;
    dest[a] = (char*)malloc(30*sizeof(char));
    while (source[i] != '\0'){
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

bool isNumber(char * nombreATester){
    bool res = true;
    int len = strlen(nombreATester);
    char c;
    for(int i = 0; i < len; i++)
    {
        c = nombreATester[i];
        if ((c < '0') || (c > '9'))
        {
            res = false;
        }
    }
    return res;
}

bool isType(char * type){
    bool res;
    int len = strlen(type);
    for (int i = 0; i < len; i++){
        if (type[i] >= 'a' && type[i] <= 'z'){
            type[i] = type[i] - 32;
        }
    }
    if (strcmp(type, "CHIFFREMENT") == 0){
        res = true;
    }
    else if(strcmp(type, "SIGNATURE") == 0){
        res = true;
    }
    else{
        res = false;
    }
    return res;
}

int quelType(char * type){
    int len = strlen(type);
    for (int i = 0; i < len; i++){
        if (type[i] >= 'a' && type[i] <= 'z'){
            type[i] = type[i] - 32;
        }
    }
    if (strcmp(type, "CHIFFREMENT") == 0){
        return 47;
    }
    else if(strcmp(type, "SIGNATURE") == 0){
        return 48;
    }
}