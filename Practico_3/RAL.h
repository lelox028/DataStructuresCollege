#ifndef RAL_h
#define RAL_H
#define FACTOR_RAL 359 // numero primo mas cercano mayor al factor para 300/0.84=357 (n/p)
//#define FACTOR_RAL 60
#include "Shipment.h"
#include "Structures.h"
typedef struct CeldaRAL
{
    Shipment data;
    int status; //-1 virgin, 0 free, 1 occupied
} CeldaRAL;

typedef struct RAL
{
    CeldaRAL baldes[FACTOR_RAL];
    int size;
} RAL;

void initRAL(RAL *ral);
int RAL_locateShipmentIndex(RAL shipments, Shipment s, int *pos, float *cost); // localizar
int RAL_evocateShipment(RAL shipments, Shipment *s, float *cost);                           // evocacion
int RAL_createShipment(RAL *shipments, Shipment s);                                         // alta
int RAL_deleteShipment(RAL *shipments, Shipment s);                                         // baja
void RAL_printStructure(RAL shipments);                                                     // printear estructura                                                // printear balde

#endif