#ifndef LSOBB_H
#define LSOBB_H
#include "Shipment.h"
#define MAX 300

typedef struct
{
    Shipment shipments[MAX];
    int lastItem; // Index of last element
} lsobb;

int LSOBB_evocateShipment(lsobb shipments, Shipment *s, float *cost);                    // evocacion
int LSOBB_createShipment(lsobb *shipments, Shipment s, float *cost);                     // alta
int LSOBB_deleteShipment(lsobb *shipments, Shipment s, float *cost);                     // baja
int LSOBB_updateShipment(lsobb *shipments, Shipment s);                                  // modificacion
int LSOBB_loadFromFile(lsobb *shipments);                                                // memorizacion previa
int LSOBB_locateShipmentIndex(const lsobb shipments, Shipment s, int *pos, float *cost); // localizar indice que un envio deberia ocupar en la estructura
void LSOBB_printStructure(lsobb shipments);

#endif