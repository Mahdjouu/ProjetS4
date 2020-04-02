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

List * list_push_front(List * l, int keyid, int type, keyPair_t keypair) {
    Node * n = malloc(sizeof(struct node_Keys));
    n->keyid = keyid;
    n->type = type;
    n->keyPair = keypair;
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
    Node * temp1 = l;
    Node * temp2 = l;

    if(!list_is_empty(l)){
        while(temp1->keyid != delete_id){
            temp1 = temp1->next;
        }
        while(temp2->next != delete_id){
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
    else{
        strcpy(type_key, "SIGNATURE");
    }
    printf("TYPE: %s\n", type_key);
}

List * list_map(List *l, SimpleFunctor f) {
	for(Node * n = l->sentinel->next; n != l->sentinel; n = n->next)
		f(n->keyid, n->type);
	return l;
}