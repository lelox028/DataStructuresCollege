#include <stdlib.h>
#include "RAC.h"

void initRAC(RAC *rac)
{
    for (int i = 0; i < FACTOR_RAC; i++)
    {
        rac->baldes[i].status = -1;
    }
    rac->size=0;
}

int RAC_locateShipmentIndex(RAC shipments, Shipment s, int *pos, float *cost)
{
    *pos = hashing(s.code, FACTOR_RAC);
    int freePos = -1;
    int i = *pos;
    int contador = 0, k = 1;
    int notFound = shipments.baldes[i].status == 1 ? stricmp(shipments.baldes[i].data.code, s.code) : 1;
    (*cost) = 1;
    while (contador < FACTOR_RAC && shipments.baldes[i].status != -1 && notFound)
    {
        if (shipments.baldes[i].status == 0 && freePos != -1)
        {
            freePos = i;
        }
        i = (i + k) % FACTOR_RAC;
        k++;
        contador++;
        if (shipments.baldes[i].status == 1 && contador < FACTOR_RAC)
        {
            notFound = stricmp(shipments.baldes[i].data.code, s.code);
        }
    }
    *cost += contador; // Suma la cantidad de comparaciones al costo
    if (!notFound)
    {
        *pos = i;
        return 1; // Éxito en la localización
    }
   else if (shipments.baldes[i].status == -1)
    {
        *pos = i;
        return 0; // No se encontró el Shipment pero si una celda virgen
    }
    else
    {
        *pos = freePos;
        return 0; // No se encontró el Shipment ni tampoco una celda virgen
    }
}

int RAC_evocateShipment(RAC shipments, Shipment *s, float *cost)
{
    if (shipments.size == 0)
    {
        return 1; // empty structure
    }
    *cost = 0;
    int index;
    if (RAC_locateShipmentIndex(shipments, *s, &index, cost))
    {
        *s = shipments.baldes[index].data;
        return 0; // success
    }
    else
        return 2; // not found
}
int RAC_createShipment(RAC *shipments, Shipment s)
{
    if (shipments->size == MAX)
    {
        return 1; // full structure
    }
    int index;
    float cost;
    if (!RAC_locateShipmentIndex(*shipments, s, &index, &cost))
    {
        shipments->baldes[index].data = s;
        shipments->baldes[index].status = 1;
        shipments->size++;
        return 0; // success
    }
    else
        return 2; // duplicated code
}
int RAC_deleteShipment(RAC *shipments, Shipment s)
{
    if (shipments->size == 0)
    {
        return 1; // empty structure
    }
    float cost = 0;
    int index;
    if (!RAC_locateShipmentIndex(*shipments, s, &index, &cost))
    {
        return 2; // not found
    }
    if (!compareShipment(s, shipments->baldes[index].data))
    {
        shipments->baldes[index].status = 0;
        shipments->size--;
        return 0;
    }
    else{
        return 3; // abort
    }
}
void RAC_printStructure(RAC shipments)
{
    printf("-------------------------------------------------\n");
    printf("Celda\t| Estado\t| Shipment Data\n");
    printf("-------------------------------------------------\n");

    for (int i = 0; i < FACTOR_RAC; i++)
    {
        char *state;
        if (shipments.baldes[i].status == -1)
        {
            state = "Virgin";
        }
        else if (shipments.baldes[i].status == 0)
        {
            state = "Free";
        }
        else
        {
            state = "Occupied";
        }

        printf("%d\t| %s\t| ", i, state);

        if (shipments.baldes[i].status == 1)
        {
            printShipment(shipments.baldes[i].data);
        }
        else
        {
            printf("N/A\n");
        }
    }

    printf("-------------------------------------------------\n");
}
