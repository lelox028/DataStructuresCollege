#include "LSOBB.h"
#include <math.h>

int LSOBB_locateShipmentIndex(const lsobb shipments, Shipment s, int *pos, float *cost)
{
    int vector[MAX] = {0};
    (*cost) = 0;
    if (shipments.lastItem == -1)
    {
        *pos = 0;
        return 0;
    }
    int li = -1, ls = (shipments.lastItem), m;
    while (li + 1 < ls)
    {
        m = ceil((li + 1 + ls) / 2.0);
        if (strcmp(s.code, shipments.shipments[m].code) < 0)
        {
            ls = m - 1;
        }
        else
        {
            li = m - 1;
        }
        // calcular costo
        if (vector[m] == 0)
        {
            (*cost)++;
            vector[m] = 1;
        }
        // m = ceil((li+1+ls)/2.0);
    }
    *pos = ls; // revisar y calcular costo
    int res = strcmp(s.code, shipments.shipments[ls].code);
    if (vector[ls] == 0)
    {
        (*cost)++;
        vector[ls] = 1;
    }
    if (res > 0)
    {
        (*pos)++;
    }
    return (!res);
}

int LSOBB_evocateShipment(lsobb shipments, Shipment *s, float *cost)
{
    if (!(shipments.lastItem >= 0))
    {
        return 1; // empty structure
    }
    int index;
    if (!LSOBB_locateShipmentIndex(shipments, *s, &index, cost))
    {
        return 2; // shipment not found
    }
    *s = shipments.shipments[index];
    return 0; // success
}

int LSOBB_createShipment(lsobb *shipments, Shipment s, float *cost)
{
    int index;
    float temp;
    (*cost) = 0;
    if (!(shipments->lastItem < MAX - 1))
    {
        return 1; // full list
    }
    if (LSOBB_locateShipmentIndex(*shipments, s, &index, &temp))
    {
        return 2; // duplicated code
    }
    int i = 0;
    i = shipments->lastItem;
    while (index <= i)
    {
        shipments->shipments[i + 1] = shipments->shipments[i];
        (*cost)++;
        i--;
    }
    shipments->shipments[index] = s;
    shipments->lastItem++;
    return 0;
}

int LSOBB_deleteShipment(lsobb *shipments, Shipment s, float *cost)
{
    (*cost) = 0;
    float temp;
    if (!(shipments->lastItem >= 0))
    {
        return 1; // empty structure
    }
    int index;
    if (!LSOBB_locateShipmentIndex(*shipments, s, &index, &temp))
    {
        return 2; // shipment not found
    }
    char choice2 = 'y';
    // printf("seguro que desea eleminar el siguiente envio?\n");
    // printShipment(shipments->shipments[index]);
    // do
    // {
    //     printf("Ingrese 'y' para sí o 'n' para no: ");
    //     scanf(" %c", &choice2);
    // } while (choice2 != 'y' && choice2 != 'n');
    if(!compareShipment(s,shipments->shipments[index])){
        choice2='y';
    }
    else{
        choice2='n';
    }
    if (choice2 == 'y')
    {
        int i = index;
        while (i < shipments->lastItem)
        {
            shipments->shipments[i] = shipments->shipments[i + 1];
            (*cost)++;
            i++;
        }
        shipments->lastItem--;
        return 0; // success
    }
    else
    {
        return 3; // abort
    }
}

int LSOBB_updateShipment(lsobb *shipments, Shipment s)
{
    if (shipments->lastItem < 0)
    {
        return 1; // empty structure
    }
    int index;
    float temp;
    if (!LSOBB_locateShipmentIndex(*shipments, s, &index, &temp))
    {
        return 2; // shipment not found
    }
    char choice2;
    printf("seguro que desea modificar el siguiente envio?\n");
    printShipment(shipments->shipments[index]);
    do
    {
        printf("Ingrese 'y' para sí o 'n' para no: ");
        scanf(" %c", &choice2);
    } while (choice2 != 'y' && choice2 != 'n');
    if (choice2 == 'y')
    {
        printf("ingrese los datos del envio nuevamente: \n");
        inputShipment(&s);
        shipments->shipments[index] = s;
        return 0; // success
    }
    else
    {
        return 3; // abort
    }
}

int LSOBB_loadFromFile(lsobb *shipments)
{
    FILE *fp;
    if ((fp = fopen("Envios.txt", "r")) == NULL)
    {
        return 1; // Error de archivo
    }
    Shipment temp;
    int duplicated = 0;
    float tempFloat;

    while (fscanf(fp, "%7s", temp.code) == 1) // Comprobar que se leyó un código correctamente
    {
        for (int i = 0; temp.code[i]; i++)
        {
            temp.code[i] = tolower(temp.code[i]); // Convertir a minúsculas
        }

        fscanf(fp, "%d", &temp.receiverDNI);
        fscanf(fp, " %[^\n]s", temp.receiverName);
        fscanf(fp, " %[^\n]s", temp.receiverAddress);
        fscanf(fp, "%d", &temp.senderDNI);
        fscanf(fp, " %[^\n]s", temp.senderName);
        fscanf(fp, "%10s", temp.sendDate);
        fscanf(fp, "%10s", temp.receiveDate);

        if (LSOBB_createShipment(shipments, temp, &tempFloat) == 2)
        {
            duplicated++;
        }

        if (!(shipments->lastItem < MAX - 1))
        {
            fclose(fp);
            break;
        }

        if (feof(fp))
        {
            break;
        }
    }

    fclose(fp);
    if ((!(shipments->lastItem < MAX - 1)) && duplicated > 0)
    {
        return 4; // duplicates and full structure
    }
    else if (!(shipments->lastItem < MAX - 1))
    {
        return 2; // full list
    }
    else if (duplicated > 0)
    {
        return 3; // duplicates found
    }
    else
    {
        return 0; // success
    }
}

void LSOBB_printStructure(lsobb shipments)
{
    // definiendo controles para diferentes OS
    char clearScreen[6];
    char pause[62];
#ifdef _WIN32
    strcpy(clearScreen, "cls\0");
    strcpy(pause, "pause");
#endif
#ifdef __APPLE__
    strcpy(clearScreen, "clear\0");
    strcpy(pause, "read -n 1 -s -p \"Presione cualquier tecla para continuar...\"\n\0");
#endif
    // fin controles OS
    if (shipments.lastItem >= 0)
    {
        int tempPos = 0;
        while (tempPos <= shipments.lastItem)
        {
            printf("envio %d\n", tempPos + 1);
            printShipment(shipments.shipments[tempPos]);
            printf("\n");
            if ((tempPos + 1) % 5 == 0)
            {
                printf("----------------------------------------------------\n");
                system(pause);
                printf("\n");
            }
            tempPos++;
        }
        if (tempPos % 5 != 0)
            system(pause); // sino se repite
    }
    else
    {
        printf("No hay envios para mostrar.\n");
        system(pause);
    }
}
