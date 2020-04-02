#include "rsa_header.h"

struct s_List{
	struct node_Keys *sentinel;
	int size;
};

struct node_Keys{
	int keyid;
	int type; // CHIFFREMENT ou SIGNATURE
	keyPair_t keyPair;
	struct node_Keys *next;
	struct node_Keys *previous;
};

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
        printf("Attention la liste ne contient pas de cle.");
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