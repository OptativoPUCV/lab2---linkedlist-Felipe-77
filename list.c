#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {

    List * lista = (List *) malloc(sizeof(List));
    if (lista == NULL)
        exit(EXIT_FAILURE);
    lista->head = NULL;
    lista->tail = NULL;
    lista->current = NULL;


    return lista;
}

void * firstList(List * list) {
    
    list->current = list->head;

    return (list->head == NULL) ? NULL : list->head->data;
}

void * nextList(List * list) {
    if (list->current == NULL) return NULL; //verificamos que el current no sea nulo
    if (list->current->next == NULL) return NULL; //verificamos que el current no sea el ultimo dato de la lista

    list->current = list->current->next;
    return list->current->data;
}

void * lastList(List * list) {
    list->current = list->tail;

    return (list->tail == NULL) ? NULL : list->tail->data;
}

void * prevList(List * list) {
    if (list->current == NULL) return NULL; //verificamos que el current no sea nulo
    else if (list->current->prev == NULL) return NULL; //verificamos que el current no sea el primer dato de la lista


    list->current = list->current->prev;
    return list->current->data;
}

void pushFront(List * list, void * data) {
    Node * new = createNode(data);

    if (list->head == NULL) list->head = list->tail = new; //Si la lista esta vacia, creamos el dato, el cual seria head y tail a la vez
    else {
        list->head->prev = new;
        new->next = list->head;

        list->head = new;
    }
    return;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    if (list){ //Verificamos que exista lista
        Node * new = createNode(data);
        new->prev = list->current;

        if (list->current->next == NULL)
            list->tail = new;
        else if (list->current->prev == NULL)
            list->head = new;
        else new->next = list->current->next;

        list->current->next = new;
    }

    return;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    if (list->current == list->head){
        Node * aux = list->current;

        list->head = list->current->next;
        list->head->prev = NULL;

        void * dato = aux->data;

        free(aux);
        return dato;
    }

    if (list->current == list->tail){
        Node * aux = list->current;

        list->tail = list->current->prev;
        list->tail->next = NULL;

        void* dato = aux->data;

        free(aux);
        return dato;
    }

    if (list){
        Node * aux = list->current;

        list->current->next->prev = list->current->prev;
        list->current->prev->next = list->current->next;

        void* dato = aux->data;
        free(aux);
        return dato;
    }
    return NULL;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}