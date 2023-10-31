#include <stdlib.h>
#include "RS.h"

void initRS(RS *rs)
{
    if (rs->size == 0)
    {
        for (int i = 0; i < FACTOR_RS; i++){
            rs->baldes[i]=NULL;
        }
        return;
    }

    for (int i = 0; i < FACTOR_RS; i++)
    {
        Node *currentNode = rs->baldes[i];
        while (currentNode != NULL)
        {
            Node *temp = currentNode;
            currentNode = currentNode->siguiente;
            free(temp); // Libera memoria del nodo
        }
        rs->baldes[i] = NULL;
    }
    rs->size = 0;
}

int RS_locateShipmentIndex(RS rs, Shipment s, Node **parent, Node **current, int *bucket, float *cost)
{
    (*bucket) = hashing(s.code, FACTOR_RS); // Calcula el índice utilizando la función de hashing
    *parent = NULL;
    *current = rs.baldes[*bucket];
    // *pos = 0;
    *cost = 0; // la cabezera cuenta?
    while (*current != NULL)
    {
        (*cost)++;
        if (stricmp((*current)->data.code, s.code) == 0)
        {
            return 1; // El Shipment fue encontrado
        }
        // (*pos)++;
        *parent = *current;
        *current = (*current)->siguiente;
    }
    if ((*cost) == 0)
        (*cost)++; // cuento la cabecera vacia
    return 0;      // El Shipment no fue encontrado
}
int RS_evocateShipment(RS shipments, Shipment *s, float *cost)
{
    if (shipments.size == 0)
    {
        return 1; // empty structure
    }
    int bucket;
    Node *parent = NULL;
    *cost = 0;
    Node *current = NULL;
    if (RS_locateShipmentIndex(shipments, *s, &parent, &current, &bucket, cost))
    {
        (*s) = current->data;
        return 0;
    }
    return 2; // not found
}
int RS_createShipment(RS *shipments, Shipment s)
{
    if (shipments->size == MAX)
    {
        return 1; // full structure
    }
    Node *parent = NULL, *current = NULL;
    int bucket;
    float cost;
    if (!RS_locateShipmentIndex(*shipments, s, &parent, &current, &bucket, &cost))
    {

        Node *newShipment = (Node *)malloc(sizeof(Node));
        if (newShipment == NULL)
        {
            return 2; // out of memory
        }
        newShipment->data = s;
        newShipment->siguiente = shipments->baldes[bucket];
        shipments->baldes[bucket] = newShipment;
        shipments->size++;
        return 0;
    }
    else
    {
        return 2; // duplicated code
    }
}
int RS_deleteShipment(RS *shipments, Shipment s)
{
    if (shipments->size == 0)
    {
        return 1; // empty structure
    }
    int bucket, index;
    float cost = 0;
    Node *parent = NULL;
    Node *current = NULL;
    if (!RS_locateShipmentIndex(*shipments, s, &parent, &current, &bucket, &cost))
    {
        return 2; // shipment not found
    }
    if (!compareShipment(s, current->data))
    {

        if (parent != NULL)
        {
            parent->siguiente = current->siguiente;
        }
        else
        {
            shipments->baldes[bucket] = current->siguiente;
        }

        free(current); // free node
        shipments->size--;
        return 0; // success
    }
    else
    {
        return 3; // abort
    }
}

void RS_printBucket(Node *list)
{
    Node *cur = list;
    while (cur != NULL)
    {
        printShipment(cur->data);
        cur = cur->siguiente;
    }
}
void RS_printStructure(RS shipments)
{
    for (int i = 0; i < FACTOR_RS; i++)
    {
        if (shipments.baldes[i] != NULL)
        {

            printf("Bucket[%d]: ", i);
            RS_printBucket(shipments.baldes[i]);
            printf("\n");
        }
    }
    printf("\n--------------------------------------------------------------------\n");
    printf("tamanio de rs: %d\n", shipments.size);
}
