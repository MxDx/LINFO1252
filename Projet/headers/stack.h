#ifndef STACK_H
#define STACK_H

#include <stdint.h>
#include <stdlib.h>

/**
 * Structure node_t qui représente les noeuds dans une linked list.
 * 
 * @param data : pointeur vers la donnée contenue par le noeud
 * @param next : pointeur vers le noeud suivant
 */
typedef struct node_t {
    void* data;
    struct node_t* next;
} node_t;

/**
 * Structure stack_t est une structure qui va indiquer le premier élément d'une linked
 * list ainsi que sa taille.
 * 
 * @param head: pointeur vers le premier élément de la liste
 * @param size: taille de la liste
 */
typedef struct stack_t {
    node_t* head;
    uint32_t size;
} stack_t;

/**
 * Fonction qui initialise les paramètres d'un stack_t passé en argument a des 
 * valeurs par défaut.
 *  
 * @param stack: pointeur vers un stack_t vide
 */
void init_stack(stack_t* stack);

/**
 * Fonction qui rajoute un noeud au somment d'une stack_t et qui update sa 
 * taille.
 * 
 * @param stack: pointeur vers une structure stack_t 
 * @param data: pointeur vers la donnée qui sera ajoutée dans le nouveau noeud à la tête de la liste 
 */
void push(stack_t* stack, void* data);

/**
 * Fonction qui enlève le premier noeud d'une stack_t et renvoie les données
 * qu'il contenais dans un pointeur vide. La fonction update la taille de la stack.
 * 
 * @param stack: pointeur vers une structure stack_t non-vide
 * @return void*: pointeur void vers le pointeur data contenu dans le noeud supprimé
 */
void* pop(stack_t* stack);

#endif /* STACK_H */