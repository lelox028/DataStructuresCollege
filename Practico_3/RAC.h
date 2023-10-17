#ifndef RAC_h
#define RAC_H
#define FACTOR_RAC 401 // numero primo mas cercano mayor al factor para 300/0.75 = 400 (n/p)
#include "Shipment.c"
#include "Structures.h"
typedef struct CeldaRAC
{
    Shipment data;
    int status; //-1 virgin, 0 free, 1 occupied
} CeldaRAC;

typedef struct RAC
{
    CeldaRAC baldes[FACTOR_RAC];
    int size;
} RAC;

void initRAC(RAC *rac);
int RAC_locateShipmentIndex(RAC shipments, Shipment s, int *pos, float *cost); // localizar
int RAC_evocateShipment(RAC shipments, Shipment *s, float *cost);                           // evocacion
int RAC_createShipment(RAC *shipments, Shipment s);                                         // alta
int RAC_deleteShipment(RAC *shipments, Shipment s);                                         // baja
void RAC_printStructure(RAC shipments);                                                     // printear estructura                                                // printear balde

#endif