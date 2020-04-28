#include "rsa_header.h"

List *list_create(){
    List *l = malloc(sizeof(struct s_List));
    l->sentinel = malloc(sizeof(struct node_Keys));
    l->sentinel->next = l->sentinel;
    l->sentinel->previous = l->sentinel;
    l->size = 0;
    return l;
}

List *list_push_front(List *l, int keyId, int type, keyPair_t keyPair){
    Node * n = malloc(sizeof(struct node_Keys));
    n->keyid = keyId;
    n->type = type;
    n->keyPair = keyPair;
    n->previous = l->sentinel;
  	n->next = l->sentinel->next;
  	n->next->previous = n;
  	l->sentinel->next = n;
  	++(l->size);
    return l;
}

bool list_is_empty(List *l) {
	return l->size == 0;
}

void list_delete(ptrList * l){
  Node * n = (*l)->sentinel->next;
  while (n != (*l)->sentinel) {
		(*l)->sentinel->next = n->next;
		free(n);
		n = (*l)->sentinel->next;
	}
	free((*l)->sentinel);
	free (*l);
	*l=NULL;
}

void node_delete(ptrList * l, int delete_id){
    Node * temp1 = (*l)->sentinel->next;
    Node * temp2 = (*l)->sentinel->next;
    if(!list_is_empty(l)){
        while(temp1->keyid != delete_id){
            temp1 = temp1->next;
            
        }
        while(temp2->next != temp1){
            temp2 = temp2->next;
        }
        temp2->next = temp1->next;
        free(temp1);
    }
}

void printList(int i, int j){
	printf("ID: %d ", i);
    char type_key[12];
    if(j == CHIFFREMENT){
        strcpy(type_key, "CHIFFREMENT");
    }
    else if (j == SIGNATURE){
        strcpy(type_key, "SIGNATURE");
    }
    printf("TYPE: %s\n", type_key);
}

List * list_map(List *l, SimpleFunctor f) {
	for(Node * n = l->sentinel->next; n != l->sentinel; n = n->next)
		f(n->keyid, n->type);
	return l;
}

Node *list_id(List * l, int id_search){
    Node * temp = l->sentinel->next;
    while(temp->keyid != id_search){
        temp = temp->next;
    }
    return temp;
}

void list_keys(List * l, int nb_arg, int id_search){
    if(list_is_empty(l)){
        printf("Attention la liste ne contient pas de cle.\n");
    }
    else{
        if(nb_arg == 0){
            list_map(l,&printList);
        }
        else{
            Node * n = l->sentinel->next;
            while(n->keyid != id_search){
                n = n->next;
            }
            printList(n->keyid, n->type);
        }
    }
}

void new_keys(List * l, int keyId, int type){
    keyPair_t newKeyPair;
    genKeysRabin(&newKeyPair.pubKey,&newKeyPair.privKey);
    list_push_front(l, keyId, type, newKeyPair);
}

void rm_keys(List * l, int keyId){
    node_delete(&l, keyId);
}

void save(List *l, SimpleFunctor2 f, char * save) {
    FILE * fic = NULL;
    if ((fic = fopen(save, "w")) == NULL){
        fprintf(stderr, "Erreur ouverture du fichier %s.\n", save);
        fclose(fic);
        return;
    }
    for(Node * n = l->sentinel->previous; n != l->sentinel; n = n->previous){
        f(n, fic);
    }
    fclose(fic);
}

void saveList(Node * n, FILE * fic){
    fprintf(fic,"ID: %d\n", n->keyid);
    if (n->type == 47){
        fprintf(fic,"TYPE: %s\n", "CHIFFREMENT");
    }
    else if(n->type == 48){
        fprintf(fic, "TYPE: %s\n", "SIGNATURE");
    }
    fprintf(fic,"PUBKEY: {%lu, %lu}\n", n->keyPair.pubKey.E, n->keyPair.pubKey.N);
    fprintf(fic,"PRIVKEY: {%lu, %lu}\n\n", n->keyPair.privKey.E, n->keyPair.privKey.N);
}

void savePub(List * l, int id, char * savePub){
    FILE * fic = NULL;
    char * pubE;
    char * pubN;
    int output_length;
    if((fic = fopen(savePub, "w")) == NULL){
        fprintf(stderr, "Impossible d'ouvrir le fichier %s en écriture\n", savePub);
        fclose(fic);
        return;
    }
    Node * n = list_id(l,id);
    uint64 temp1 = n->keyPair.pubKey.E;
    uint64 temp2 = n->keyPair.pubKey.N;
    pubE = base64_encode((const uchar *)&temp1, sizeof(temp1), &output_length);
    pubN = base64_encode((const uchar *)&temp2, sizeof(temp2), &output_length);
    fprintf(fic, "PUBKEY: %d\n", id);
    fprintf(fic, "PUBKEY_E: %s\n", pubE);
    fprintf(fic, "PUBKEY_N: %s\n", pubN);
    free(pubE);
    free(pubN);
    fclose(fic);
}

void load(List * l, char * filename){
    FILE * fichier = NULL;
    char * type = (char*)malloc(MAX_BUFFER*sizeof(char));
    keyPair_t keyPair;
    int id = 0;
    if ((fichier = fopen(filename, "r")) == NULL){
        fprintf(stderr, "Impossible d'ouvrir le fichier %s avec la fonction load.\n", filename);
        fclose(fichier);
        return;
    }
    while(!feof(fichier)){
        fscanf(fichier, "ID: %d\n", &id);
        fscanf(fichier, "TYPE: %s\n", type);
        fscanf(fichier, "PUBKEY: {%lu, %lu}\n", &keyPair.pubKey.E, &keyPair.pubKey.N);
        fscanf(fichier, "PRIVKEY: {%lu, %lu}\n\n", &keyPair.privKey.E, &keyPair.privKey.N);
        if (strcmp(type, "CHIFFREMENT") == 0){
            l = list_push_front(l, id, CHIFFREMENT, keyPair);
        }
        else if(strcmp(type, "SIGNATURE") == 0){
            l = list_push_front(l, id, SIGNATURE, keyPair);
        }
    }
}

void show(List * l, int id, int nbarg, char ** arg){
    Node * n = list_id(l, id);
    char * pubE ;
    char * pubN;
    char * privE;
    char * privN;
    int output_length;
    uint64 temp1 = n->keyPair.pubKey.E;
    uint64 temp2 = n->keyPair.pubKey.N;
    uint64 temp3 = n->keyPair.privKey.E;
    uint64 temp4 = n->keyPair.privKey.N;
    pubE = base64_encode((const uchar *)&temp1, sizeof(temp1), &output_length);
    pubN = base64_encode((const uchar *)&temp2, sizeof(temp2), &output_length);
    privE = base64_encode((const uchar *)&temp3, sizeof(temp3), &output_length);
    privN = base64_encode((const uchar *)&temp4, sizeof(temp4), &output_length);

    if(nbarg == 2 || nbarg == 4){
        printf("PUBKEY: (%s , %s)\n", pubE, pubN);
        printf("PRIVKEY: (%s , %s)\n\n", privE, privN);
    }
    else{
        if(strcmp(arg[2],"pub") == 0){
            printf("PUBKEY: (%s , %s)\n\n", pubE, pubN);
        }
        else if(strcmp(arg[2],"priv") == 0){
            printf("PRIVKEY: (%s , %s)\n\n", privE, privN);
        }
        else{
            fprintf(stderr, "Usage : show <keyid> [\"pub\"] [\"priv\"]\nkeyid : entier (clé)\n");
            fprintf(stderr, "pub : argument pour afficher la clé publique\npriv : argument pour afficher la clé privé\n");
        }
    }
    free(pubE);
    free(pubN);
    free(privE);
    free(privN);
}

void signtext(char * inFilename, rsaKey_t signKey, char * outFilename){
    tabUint64_t * temp = signText(inFilename, signKey);
    signatureDigest(temp, outFilename);
}

void verifysign(char * inFilename, char * inFileB64, rsaKey_t verifyKey){
    tabUint64_t temp;
    if(verifySignFileB64(inFilename, inFileB64, temp, verifyKey)){
        printf("Le message est bien signé !\n");
    }
    else{
        printf("Le message n'est pas bien signé !\n");
    }
}