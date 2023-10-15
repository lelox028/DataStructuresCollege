#ifndef LSO_H
#define LSO_H
#include "Shipment.h"
#define MAX 300

typedef struct
{
    Shipment shipments[MAX];
    int lastItem; // Index of last element
} lso;

int LSO_evocateShipment(lso shipments, Shipment *s, float *cost);                    // evocacion
int LSO_createShipment(lso *shipments, Shipment s, float *cost);                     // alta
int LSO_deleteShipment(lso *shipments, Shipment s, float *cost);                     // baja
int LSO_updateShipment(lso *shipments, Shipment s);                                  // modificacion
int LSO_loadFromFile(lso *shipments);                                                // memorizacion previa
int LSO_locateShipmentIndex(const lso shipments, Shipment s, int *pos, float *cost); // localizar indice que un envio deberia ocupar en la estructura
void LSO_printStructure(lso shipments);

#endif