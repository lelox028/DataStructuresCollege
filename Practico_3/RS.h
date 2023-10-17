#ifndef RS_h
#define RS_H
#define FACTOR_RS 207 // factor para 300/1.45 (n/p)
#include "Shipment.h"
#include "Structures.h"

typedef struct Node
{
    Shipment data;
    struct Node *siguiente;
} Node;

typedef struct RS
{
    Node *baldes[FACTOR_RS];
    int size;
} RS;

void initRS(RS *rs);
int RS_locateShipmentIndex(RS rs, Shipment s, int *pos, int *bucket, float *cost); // localizar
int RS_evocateShipment(RS shipments, Shipment *s, float *cost);                    // evocacion
int RS_createShipment(RS *shipments, Shipment s);                                  // alta
int RS_deleteShipment(RS *shipments, Shipment s);                                  // baja
// int RS_updateShipment(RS *shipments, Shipment s);                               // modificacion
void RS_printStructure(RS shipments);                                              // printear estructura
void RS_printBucket(Node *list);                                                   // printear balde

#endif