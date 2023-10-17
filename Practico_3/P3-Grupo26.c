// grupo 26, Pascarelli Giuliano
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Shipment.h"
#include "Shipment.c"
#include "RAL.h"
#include "RAL.c"
#include "RAC.h"
#include "RAC.c"
#include "RS.h"
#include "RS.c"

/* 
Dada la tabla de costos:
----------------------------------------------------------------------------------------
Operacion              | RAL                      | RAC                    | RS
----------------------------------------------------------------------------------------
Evocacion Exitosa      | Max: 60    Avg: 23.97    | Max: 6     Avg: 5.57     | Max: 12    Avg: 5.71
Evocacion No Exitosa   | Max: 42    Avg: 16.70    | Max: 6     Avg: 4.87     | Max: 10    Avg: 5.27
Alta                   | Max: 58    Avg: 15.07    | Max: 58    Avg: 15.07    | Max: 0.500000 Avg: 0.50
Baja                   | Max: 47    Avg: 16.77    | Max: 47    Avg: 16.77    | Max: 1.500000 Avg: 0.98
----------------------------------------------------------------------------------------

En el análisis comparativo de las estructuras de datos, se destacó que la Lista Secuencial Ordenada exhibió el peor rendimiento, especialmente en las operaciones de evocación, donde sus costos fueron significativamente más altos que los de las otras estructuras. Su única ventaja aparente radica en su facilidad de programación.

En contraste, la Lista Secuencial Ordenada con Búsqueda Binaria demostró ser la opción más eficiente en términos de costos para las operaciones de evocación, especialmente en cuanto a los costos máximos. Aunque sus costos esperados apenas mostraron diferencias significativas en comparación con los del Árbol Binario de Búsqueda, sus operaciones de Alta y Baja presentaron costos idénticos a los de la Lista Secuencial Ordenada.

Finalmente, el Árbol Binario de Búsqueda destacó por su notable eficiencia en las operaciones de Alta y Baja en comparación con las otras estructuras. Incluso logró costos medios similares a los de la Lista Secuencial Ordenada con Búsqueda Binaria en las operaciones de Evocación. Es por esto, que considero que el Arbol Binario de Busqueda es la estructura con mejor rendimiento, ya que la diferencia de costos en evocacion con la estructura mas eficiente en esa operacion es infima, mientras que la ventaja que esta presenta en altas y bajas respecto de las demas alternativas es demasiado pronunciada, y esta diferencia quedara cada vez mas evidenciada a medida que la cantidad de elementos en las estructuras aumente.
*/
int main()
{
    // definiendo controles para diferentes OS
    char clearScreen[6];
    char pause[62];
#ifdef _WIN32
    strcpy(clearScreen, "cls\0");
    strcpy(pause, "pause");
#else
    strcpy(clearScreen, "clear\0");
    strcpy(pause, "read -n 1 -s -p \"Presione cualquier tecla para continuar...\"\n\0");
#endif
    // fin controles OS
    FILE *file;
    // declaracion e inicializacion de estructuras
    RAL ral;
    initRAL(&ral);

    RAC rac;
    initRAC(&rac);

    RS rs;
    initRS(&rs);

    // Aux variables

    int vecesBajaRAL = 0, vecesBajaRAC = 0, vecesBajaRS = 0;
    int vecesAltaRAL = 0, vecesAltaRAC = 0, vecesAltaRS = 0;

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
            float tempCost;

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
                    s.code[i] = tolower(s.code[i]); // Convertir a minúsculas
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
                    // RAC
                    if (RAC_createShipment(&rac, s) == 0)
                    {
                        vecesAltaRAC++;
                    }
                    // RS
                    if (RS_createShipment(&rs, s) == 0)
                    {
                        vecesAltaRS++;
                    }
                }
                else if (operation == '2')
                { // Operación de baja
                  // RAL
                    if (RAL_deleteShipment(&ral, s) == 0)
                    {
                        vecesBajaRAL++;
                    }
                    // RAC
                    if (RAC_deleteShipment(&rac, s) == 0)
                    {
                        vecesBajaRAC++;
                    }
                    // RS
                    if (RS_deleteShipment(&rs, s) == 0)
                    {
                        vecesBajaRS++;
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
            printf("Operación              | RAL                      | RAC                    | RS\n");
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
