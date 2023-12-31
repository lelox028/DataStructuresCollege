// grupo 26, Pascarelli Giuliano
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//#include "Shipment.h"
#include "Shipment.c"
//#include "RAL.h"
#include "RAL.c"
//#include "RAC.h"
#include "RAC.c"
//#include "RS.h"
#include "RS.c"

/* 
Dada la tabla de costos:
----------------------------------------------------------------------------------------
Operaci├│n              | RAL                      | RAC                      | RS
----------------------------------------------------------------------------------------
Evocacion Exitosa      | Max: 6     Avg: 1.68     | Max: 7     Avg: 1.72     | Max: 5     Avg: 2.29
Evocacion No Exitosa   | Max: 9     Avg: 3.84     | Max: 11    Avg: 3.53     | Max: 4     Avg: 1.36
----------------------------------------------------------------------------------------

Evocacion Exitosa:
El RAL tiene un muy buen rendimiento en la evocación exitosa. El costo máximo es bajo, por lo que, en los peores casos, la cantidad de celdas consultadas es decente. Además, el costo promedio también es bajo, lo que sugiere un rendimiento consistente en general.
RAC también muestra un buen rendimiento en evocación exitosa, con costos máximos y promedio relativamente bajos. Aunque es ligeramente mayor que RAL, sigue siendo eficiente.
RS tiene un costo máximo aún más bajo que RAL y RAC en la evocación exitosa, lo que indica un rendimiento destacable en los casos extremos. Sin embargo, el costo promedio es un poco más alto, lo que puede implicar un rendimiento menos consistente.

Evocacion No Exitosa:
Aunque el RAL tiene un rendimiento aceptable en evocación no exitosa, su costo medio es ligeramente más alto en comparación con las otras estructuras, aunque su costo maximo se encuentra en un punto medio entre ellas, tendiendo mas a la performance del RAC. Sin embargo, sigue siendo eficiente en general.
El RAC posee nuevamente el costo maximo mas elevado, y su costo medio apenas se diferencia del RAL en este caso, por lo que, si bien la diferencia no es mucha, parece ser la menos eficiente en general de las 3.
El RS tiene un rendimiento excepcionalmente bueno en evocación no exitosa, con el costo máximo y promedio más bajo entre las tres estructuras. Esto indica que RS es especialmente eficiente cuando la búsqueda no tiene éxito.

Conclusion: En términos de evocación exitosa, los Rebalses Abiertos son las mas eficientes en costos medios, aunque RS destaca en casos extremos. Para evocación no exitosa, RS supera a las otras estructuras, siendo la opción más eficiente por un buen margen.

*/

int main()
{
    // definiendo controles para diferentes OS
    char clearScreen[6];
    char pause[125];
#ifdef _WIN32
    strcpy(clearScreen, "cls\0");
    strcpy(pause, "pause");
#else
    strcpy(clearScreen, "clear\0");
    strcpy(pause, "read -p 'Presione Enter para continuar...' key");
#endif
    // fin controles OS
    FILE *file;
    // declaracion e inicializacion de estructuras
    RAL ral;
    initRAL(&ral);

    RAC rac;
    initRAC(&rac);

    RS rs;
    rs.size=0;
    initRS(&rs);

    // Aux variables

    int vecesBajaRAL = 0, vecesBajaRAC = 0, vecesBajaRS = 0;
    int vecesNoBajaRAL = 0, vecesNoBajaRAC = 0, vecesNoBajaRS = 0;
    int vecesAltaRAL = 0, vecesAltaRAC = 0, vecesAltaRS = 0;
    int vecesNoAltaRAL = 0, vecesNoAltaRAC = 0, vecesNoAltaRS = 0;

    // Shipment tempShipment;
    int tempPos;
    int choice = -1;
    int choice2;

    // Variables para costos

    // RAL

    // Variables para la operación "locate"
    int ral_locate_success_max_cost = 0;
    int ral_locate_success_count = 0, ral_locate_success_total_cost = 0;
    float ral_locate_success_avg_cost = 0.0f;
    int ral_locate_failure_max_cost = 0;
    int ral_locate_failure_count = 0, ral_locate_failure_total_cost = 0;
    float ral_locate_failure_avg_cost = 0.0f;

    // RAC

    // Variables para la operación "locate"
    int rac_locate_success_max_cost = 0;
    int rac_locate_success_count = 0, rac_locate_success_total_cost = 0;
    float rac_locate_success_avg_cost = 0.0f;
    int rac_locate_failure_max_cost = 0;
    int rac_locate_failure_count = 0, rac_locate_failure_total_cost = 0;
    float rac_locate_failure_avg_cost = 0.0f;

    // RS

    // Variables para la operación "locate"
    int rs_locate_success_max_cost = 0;
    int rs_locate_success_count = 0, rs_locate_success_total_cost = 0;
    float rs_locate_success_avg_cost = 0.0f;
    int rs_locate_failure_max_cost = 0;
    int rs_locate_failure_count = 0, rs_locate_failure_total_cost = 0;
    float rs_locate_failure_avg_cost = 0.0f;

    do
    {
        // strcpy(tempShipment.code, ""); // clear temp var value
        system(clearScreen);
        printf("Main Menu\n");
        printf("1. Mostrar estructura\n");
        printf("2. Comparar estructura\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            do
            {
                printf("Seleccione la estructura que desea mostrar:\n");
                printf("1. RAL\n");
                printf("2. RAC\n");
                printf("3. RS\n");
                printf("Elija una opción (1-3): ");
                scanf(" %d", &choice2);

                switch (choice2)
                {
                case 1:
                    RAL_printStructure(ral);
                    system(pause);
                    break;
                case 2:
                    RAC_printStructure(rac);
                    system(pause);
                    break;
                case 3:
                    RS_printStructure(rs);
                    system(pause);
                    break;
                default:
                    printf("Opción no válida. Por favor, seleccione una opción válida (1-3).\n");
                    system(pause);
                    break;
                }
            } while (choice2 < 1 || choice2 > 3); // Repite hasta que se ingrese una opción válida
            break;
        case 2:
        {
            // borrar estructuras
            initRAL(&ral);
            initRAC(&rac);
            initRS(&rs);
            // aux var
            char operation;
            Shipment s;
            float tempCost=0;

            // Abre el archivo de operaciones
            file = fopen("Operaciones-Envios.txt", "r");

            if (file == NULL)
            {
                printf("Error al abrir el archivo de operaciones.\n");
                system(pause);
                break;
            }

            while (fscanf(file, " %c", &operation) != EOF)
            {
                fscanf(file, "%7s", s.code);
                for (int i = 0; s.code[i]; i++)
                {
                    s.code[i] = toupper(s.code[i]); // Convertir a MAYUSCULAS
                }
                if (operation == '1' || operation == '2')
                {
                    // read shipment

                    fscanf(file, "%d", &s.receiverDNI);
                    fscanf(file, " %[^\n]s", s.receiverName);
                    fscanf(file, " %[^\n]s", s.receiverAddress);
                    fscanf(file, "%d", &s.senderDNI);
                    fscanf(file, " %[^\n]s", s.senderName);
                    fscanf(file, "%10s", s.sendDate);
                    fscanf(file, "%10s", s.receiveDate);
                }

                if (operation == '1')
                {
                    // Operación de alta
                    // RAL
                    if (RAL_createShipment(&ral, s) == 0)
                    {
                        vecesAltaRAL++;
                    }
                    else{
                        vecesNoAltaRAL++;
                    }
                    // RAC
                    if (RAC_createShipment(&rac, s) == 0)
                    {
                        vecesAltaRAC++;
                    }
                    else{
                        vecesNoAltaRAC++;
                    }
                    // RS
                    if (RS_createShipment(&rs, s) == 0)
                    {
                        vecesAltaRS++;
                    }
                     else{
                        vecesNoAltaRS++;
                    }
                }
                else if (operation == '2')
                { // Operación de baja
                  // RAL
                    if (RAL_deleteShipment(&ral, s) == 0)
                    {
                        vecesBajaRAL++;
                    }
                    else{
                        vecesNoBajaRAL++;
                    }
                    // RAC
                    if (RAC_deleteShipment(&rac, s) == 0)
                    {
                        vecesBajaRAC++;
                    }
                     else{
                        vecesNoBajaRAC++;
                    }
                    // RS
                    if (RS_deleteShipment(&rs, s) == 0)
                    {
                        vecesBajaRS++;
                    }
                     else{
                        vecesNoBajaRS++;
                    }
                }
                else if (operation == '3')
                { // Operación de evocación
                    // Ejecuta la operación de evocación
                    // RAL
                    if (RAL_evocateShipment(ral, &s, &tempCost) == 0)
                    {
                        ral_locate_success_count++;
                        ral_locate_success_total_cost += tempCost;
                        if (tempCost > ral_locate_success_max_cost)
                        {
                            ral_locate_success_max_cost = tempCost;
                        }
                        printShipment(s); // si se encuentra es informado por pantalla
                    }
                    else
                    {
                        ral_locate_failure_count++;
                        ral_locate_failure_total_cost += tempCost;
                        if (tempCost > ral_locate_failure_max_cost)
                        {
                            ral_locate_failure_max_cost = tempCost;
                        }
                        printf("El envio solicitado no se encuentra en el sistema. (ral)\n");
                        // system(pause);
                    }
                    // RAC
                    if (RAC_evocateShipment(rac, &s, &tempCost) == 0)
                    {
                        rac_locate_success_count++;
                        rac_locate_success_total_cost += tempCost;
                        if (tempCost > rac_locate_success_max_cost)
                        {
                            rac_locate_success_max_cost = tempCost;
                        }
                        printShipment(s); // si se encuentra es informado por pantalla
                    }
                    else
                    {
                        rac_locate_failure_count++;
                        rac_locate_failure_total_cost += tempCost;
                        if (tempCost > rac_locate_failure_max_cost)
                        {
                            rac_locate_failure_max_cost = tempCost;
                        }
                        printf("El envio solicitado no se encuentra en el sistema. (rac)\n");
                        // system(pause);
                    }

                    // RS

                    if (RS_evocateShipment(rs, &s, &tempCost) == 0)
                    {
                        rs_locate_success_count++;
                        rs_locate_success_total_cost += tempCost;
                        if (tempCost > rs_locate_success_max_cost)
                        {
                            rs_locate_success_max_cost = tempCost;
                        }
                        printShipment(s); // si se encuentra es informado por pantalla
                    }
                    else
                    {
                        rs_locate_failure_count++;
                        rs_locate_failure_total_cost += tempCost;
                        if (tempCost > rs_locate_failure_max_cost)
                        {
                            rs_locate_failure_max_cost = tempCost;
                        }
                        printf("El envio solicitado no se encuentra en el sistema. (rs)\n");
                        // system(pause);
                    }
                }
            }

            // Cierra el archivo
            fclose(file);

            // Realiza otras operaciones

            // RAL
            ral_locate_success_avg_cost = ral_locate_success_total_cost / (float)ral_locate_success_count;
            ral_locate_failure_avg_cost = ral_locate_failure_total_cost / (float)ral_locate_failure_count;

            // RAC
            rac_locate_success_avg_cost = rac_locate_success_total_cost / (float)rac_locate_success_count;
            rac_locate_failure_avg_cost = rac_locate_failure_total_cost / (float)rac_locate_failure_count;

            // RS
            rs_locate_success_avg_cost = rs_locate_success_total_cost / (float)rs_locate_success_count;
            rs_locate_failure_avg_cost = rs_locate_failure_total_cost / (float)rs_locate_failure_count;


            printf("----------------------------------------------------------------------------------------\n");
            printf("Operación              | RAL                      | RAC                      | RS\n");
            printf("----------------------------------------------------------------------------------------\n");

            // Mostrar resultados para la operación "evocacion exitosa"
            printf("Evocacion Exitosa      | Max: %-5d Avg: %-8.2f | Max: %-5d Avg: %-8.2f | Max: %-5d Avg: %-8.2f\n",
                   ral_locate_success_max_cost, ral_locate_success_avg_cost,
                   rac_locate_success_max_cost, rac_locate_success_avg_cost,
                   rs_locate_success_max_cost, rs_locate_success_avg_cost);

            // Mostrar resultados para la operación "evocacion no exitosa"
            printf("Evocacion No Exitosa   | Max: %-5d Avg: %-8.2f | Max: %-5d Avg: %-8.2f | Max: %-5d Avg: %-8.2f\n",
                   ral_locate_failure_max_cost, ral_locate_failure_avg_cost,
                   rac_locate_failure_max_cost, rac_locate_failure_avg_cost,
                   rs_locate_failure_max_cost, rs_locate_failure_avg_cost);

            printf("----------------------------------------------------------------------------------------\n");

            system(pause);
        }
        break;
        case 9:
            printf("Exiting program.\n");
            break;
        default:
            system(clearScreen);
            choice = -1;
            printf("Invalid choice. Please enter a valid option.\n");
            system(pause);
        }

    } while (choice != 9);

    return 0;
}
