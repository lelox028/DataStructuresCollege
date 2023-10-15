#ifndef ABB_H
#define ABB_H
#include "Shipment.h"

typedef struct Node
{
    Shipment data;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct
{
    Node *root;
    int size;
} Abb;

Node *Abb_locateShipment(const Abb shipments, Shipment s, Node **parent, float *cost); // localizar indice que un envio deberia ocupar en la estructura
int Abb_evocateShipment(Abb tree, Shipment *s, float *cost);                           // evocacion
int Abb_createShipment(Abb *shipments, Shipment s, float *cost);                       // alta
int Abb_deleteShipment(Abb *shipments, Shipment s, float *cost);                       // baja
int Abb_updateShipment(Abb *shipments, Shipment s);                                    // modificacion
int Abb_loadFromFile(Abb *shipments);                                                  // memorizacion previa
void Abb_printStructure(Node *root);
void freeAbb(Abb *tree);
void freeAbbNodes(Node *node);

#endif