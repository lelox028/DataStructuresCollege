#ifndef RS_h
#define RS_H
#define FACTOR_RS 207 //factor para 300/1.45 (n/p)
#include "Shipment.c"

typedef struct Node
{
    Shipment data;
    struct Node *siguiente;
} Node;

typedef struct RS
{
    Node* baldes[FACTOR_RS];
    int size;
} RS;

void initRS(RS *rs);

#endif