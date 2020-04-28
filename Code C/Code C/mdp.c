#include "rsa_header.h"

bool saisie_mdp(){
    bool res = false;
    BYTE pass[MAX_BUFFER];
    char passSha[SHA256_BLOCK_SIZE*2+1];
    char passTemp[SHA256_BLOCK_SIZE*2+1];
    int fichier = open("hash_pass.bin", O_RDONLY, S_IRUSR);
    if (fichier == -1){
        fichier = creat("hash_pass.bin", S_IWUSR | S_IRUSR);
        printf("Veuillez saisir votre nouveau mot de passe :\n> ");
        scanf("%s", pass);
        sha256ofString(pass, passSha);
        if (write(fichier, passSha, sizeof(passSha)) != sizeof(passSha)){
            printf("ERREUR : Erreur création du mot de passe ! \n");
            exit(3);
        }
        printf("passSha = %s\n", passSha);
        close(fichier);
        res = true;
    }
    else{
        printf("Veuillez saisir votre mot de passe\n> ");
        scanf("%s", pass);
        sha256ofString(pass, passSha);
        read(fichier, passTemp, sizeof(passTemp));
        if (strcmp(passTemp, passSha) == 0){
            printf("Le mot de passe est bon !\n");
            res = true;
        }
        else{
            printf("Le mot de passe est erroné !\n\n");
        }
        close(fichier);
    }
    return res;
}