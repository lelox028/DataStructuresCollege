#include <stdlib.h>
#include "RAL.h"

void initRAL(RAL *ral)
{
    for (int i = 0; i < FACTOR_RAL; i++)
    {
        ral->baldes[i].status = -1;
    }
}

int RAL_locateShipmentIndex(RAL shipments, Shipment s, int *pos, float *cost)
{
    *pos = hashing(s.code, FACTOR_RAL);
    int freePos = -1;
    int i = *pos;
    int contador = 0;
    int notFound = strcasecmp(shipments.baldes[i].data.code, s.code);
    (*cost) = 1;
    while (contador < FACTOR_RAL && shipments.baldes[i].status != -1 && notFound)
    {
        if (shipments.baldes[i].status == 0 && freePos != -1)
        {
            freePos = i;
        }
        i = (i + 1) % FACTOR_RAL;
        contador++;
        if (shipments.baldes[i].status == 1 && contador < FACTOR_RAL)
        {
            notFound = strcasecmp(shipments.baldes[i].data.code, s.code);
        }
        //(*cost)++;
    }
    *cost += contador; // Suma la cantidad de comparaciones al costo
    if (!notFound)
    {
        *pos = i;

        return 0; // Éxito en la localización
    }
    else if (contador < FACTOR_RAL)
    {
        *pos = freePos;

        return 1; // No se encontró el Shipment ni tampoco una celda virgen
    }
    else
    {
        *pos = i;
        return -1; // No se encontró el Shipment pero si una celda virgen
    }
}

int RAL_evocateShipment(RAL shipments, Shipment *s, float *cost)
{
    if (shipments.size == 0)
    {
        return 1; // empty structure
    }
    *cost = 0;
    int index;
    if (RAL_locateShipmentIndex(shipments, *s, &index, cost))
    {
        *s = shipments.baldes[index].data;
        return 0; // success
    }
    else
        return 2; // not found
}
int RAL_createShipment(RAL *shipments, Shipment s)
{
    if (shipments->size == MAX)
    {
        return 1; // full structure
    }
    int index;
    float *cost;
    if (!RAL_locateShipmentIndex(*shipments, s, &index, cost))
    {
        shipments->baldes[index].data = s;
        shipments->baldes[index].status = 1;
        shipments->size++;
        return 0; // success
    }
    else
        return 2; // duplicated code
}
int RAL_deleteShipment(RAL *shipments, Shipment s)
{
    if (shipments->size == 0)
    {
        return 1; // empty structure
    }
    float cost = 0;
    int index;
    if (!RAL_locateShipmentIndex(*shipments, s, &index, &cost))
    {
        return 2; // not found
    }
    if(compareShipment(s,shipments->baldes[index].data)){
        shipments->baldes[index].status=0;
        shipments->size--;
    }
    else
        return 3; //abort
        
}
void RAL_printStructure(RAL shipments) {
    printf("-------------------------------------------------\n");
    printf("Celda\t| Estado\t| Shipment Data\n");
    printf("-------------------------------------------------\n");

    for (int i = 0; i < FACTOR_RAL; i++) {
        char* state;
        if (shipments.baldes[i].status == -1) {
            state = "Virgin";
        } else if (shipments.baldes[i].status == 0) {
            state = "Free";
        } else {
            state = "Occupied";
        }

        printf("%d\t| %s\t| ", i, state);

        if (shipments.baldes[i].status == 1) {
            printShipment(shipments.baldes[i].data);
        } else {
            printf("N/A\n");
        }
    }

    printf("-------------------------------------------------\n");
}

