// grupo 26, Pascarelli Giuliano
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Shipment.h"
#include "Shipment.c"
#include "LSO.h"
#include "LSO.c"
#include "LSOBB.h"
#include "LSOBB.c"
#include "ABB.h"
#include "ABB.c"

/* 
Dada la tabla de costos:
----------------------------------------------------------------------------------------
Operacion              | LSO                      | LSOBB                    | ABB
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
#endif
#ifdef __APPLE__
    strcpy(clearScreen, "clear\0");
    strcpy(pause, "read -n 1 -s -p \"Presione cualquier tecla para continuar...\"\n\0");
#endif
    // fin controles OS
    FILE *file;
    // declaracion e inicializacion de estructuras
    lso lso;
    lso.lastItem = -1;

    lsobb lsobb;
    lsobb.lastItem = -1;

    Abb tree;
    tree.root = NULL;

    // Aux variables

    int vecesBajaLSO = 0, vecesBajaLSOBB = 0, vecesBajaABB = 0;
    int vecesAltaLSO = 0, vecesAltaLSOBB = 0, vecesAltaABB = 0;

    // Shipment tempShipment;
    int tempPos;
    int choice = -1;
    int choice2;

    // Variables para costos

    // LSO

    // Variables para la operación "locate"
    int lso_locate_success_max_cost = 0;
    int lso_locate_success_count = 0, lso_locate_success_total_cost = 0;
    float lso_locate_success_avg_cost = 0.0f;
    int lso_locate_failure_max_cost = 0;
    int lso_locate_failure_count = 0, lso_locate_failure_total_cost = 0;
    float lso_locate_failure_avg_cost = 0.0f;

    // Variables para la operación "create"
    int lso_create_success_max_cost = 0;
    int lso_create_success_count = 0, lso_create_success_total_cost = 0;
    float lso_create_success_avg_cost = 0.0f;

    // Variables para la operación "delete"
    int lso_delete_success_max_cost = 0;
    int lso_delete_success_count = 0, lso_delete_success_total_cost = 0;
    float lso_delete_success_avg_cost = 0.0f;

    // LSOBB

    // Variables para la operación "locate"
    int lsobb_locate_success_max_cost = 0;
    int lsobb_locate_success_count = 0, lsobb_locate_success_total_cost = 0;
    float lsobb_locate_success_avg_cost = 0.0f;
    int lsobb_locate_failure_max_cost = 0;
    int lsobb_locate_failure_count = 0, lsobb_locate_failure_total_cost = 0;
    float lsobb_locate_failure_avg_cost = 0.0f;

    // Variables para la operación "create"
    int lsobb_create_success_max_cost = 0;
    int lsobb_create_success_count = 0, lsobb_create_success_total_cost = 0;
    float lsobb_create_success_avg_cost = 0.0f;

    // Variables para la operación "delete"
    int lsobb_delete_success_max_cost = 0;
    int lsobb_delete_success_count = 0, lsobb_delete_success_total_cost = 0;
    float lsobb_delete_success_avg_cost = 0.0f;

    // ABB

    // Variables para la operación "locate"
    int abb_locate_success_max_cost = 0;
    int abb_locate_success_count = 0, abb_locate_success_total_cost = 0;
    float abb_locate_success_avg_cost = 0.0f;
    int abb_locate_failure_max_cost = 0;
    int abb_locate_failure_count = 0, abb_locate_failure_total_cost = 0;
    float abb_locate_failure_avg_cost = 0.0f;

    // Variables para la operación "create"
    float abb_create_success_max_cost = 0.0f;
    float abb_create_success_count = 0.0f, abb_create_success_total_cost = 0.0f;
    float abb_create_success_avg_cost = 0.0f;

    // Variables para la operación "delete"
    float abb_delete_success_max_cost = 0.0f;
    float abb_delete_success_count = 0.0f, abb_delete_success_total_cost = 0.0f;
    float abb_delete_success_avg_cost = 0.0f;

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
                printf("1. LSO\n");
                printf("2. LSOBB\n");
                printf("3. ABB\n");
                printf("Elija una opción (1-3): ");
                scanf(" %d", &choice2);

                switch (choice2)
                {
                case 1:
                    LSO_printStructure(lso);
                    break;
                case 2:
                    LSOBB_printStructure(lsobb);
                    break;
                case 3:
                    Abb_printStructure(tree.root);
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
            freeAbb(&tree);
            lso.lastItem = -1;
            lsobb.lastItem = -1;
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
                    // LSO
                    if (LSO_createShipment(&lso, s, &tempCost) == 0)
                    {
                        vecesAltaLSO++;
                        lso_create_success_count++;
                        lso_create_success_total_cost += tempCost;
                        if (tempCost > lso_create_success_max_cost)
                        {
                            lso_create_success_max_cost = tempCost;
                        }
                    }
                    // LSOBB
                    if (LSOBB_createShipment(&lsobb, s, &tempCost) == 0)
                    {
                        vecesAltaLSOBB++;
                        lsobb_create_success_count++;
                        lsobb_create_success_total_cost += tempCost;
                        if (tempCost > lsobb_create_success_max_cost)
                        {
                            lsobb_create_success_max_cost = tempCost;
                        }
                    }
                    // ABB
                    if (Abb_createShipment(&tree, s, &tempCost) == 0)
                    {
                        vecesAltaABB++;
                        abb_create_success_count++;
                        abb_create_success_total_cost += tempCost;
                        if (tempCost > abb_create_success_max_cost)
                        {
                            abb_create_success_max_cost = tempCost;
                        }
                    }
                }
                else if (operation == '2')
                { // Operación de baja
                  // LSO
                    if (LSO_deleteShipment(&lso, s, &tempCost) == 0)
                    {
                        vecesBajaLSO++;
                        lso_delete_success_count++;
                        lso_delete_success_total_cost += tempCost;
                        if (tempCost > lso_delete_success_max_cost)
                        {
                            lso_delete_success_max_cost = tempCost;
                        }
                    }
                    // LSOBB
                    if (LSOBB_deleteShipment(&lsobb, s, &tempCost) == 0)
                    {
                        vecesBajaLSOBB++;
                        lsobb_delete_success_count++;
                        lsobb_delete_success_total_cost += tempCost;
                        if (tempCost > lsobb_delete_success_max_cost)
                        {
                            lsobb_delete_success_max_cost = tempCost;
                        }
                    }
                    // ABB
                    if (Abb_deleteShipment(&tree, s, &tempCost) == 0)
                    {
                        vecesBajaABB++;
                        abb_delete_success_count++;
                        abb_delete_success_total_cost += tempCost;
                        if (tempCost > abb_delete_success_max_cost)
                        {
                            abb_delete_success_max_cost = tempCost;
                        }
                    }
                }
                else if (operation == '3')
                { // Operación de evocación
                    // Ejecuta la operación de evocación
                    // LSO
                    if (LSO_evocateShipment(lso, &s, &tempCost) == 0)
                    {
                        lso_locate_success_count++;
                        lso_locate_success_total_cost += tempCost;
                        if (tempCost > lso_locate_success_max_cost)
                        {
                            lso_locate_success_max_cost = tempCost;
                        }
                        printShipment(s); // si se encuentra es informado por pantalla
                    }
                    else
                    {
                        lso_locate_failure_count++;
                        lso_locate_failure_total_cost += tempCost;
                        if (tempCost > lso_locate_failure_max_cost)
                        {
                            lso_locate_failure_max_cost = tempCost;
                        }
                        printf("El envio solicitado no se encuentra en el sistema. (lso)\n");
                        // system(pause);
                    }
                    // LSOBB
                    if (LSOBB_evocateShipment(lsobb, &s, &tempCost) == 0)
                    {
                        lsobb_locate_success_count++;
                        lsobb_locate_success_total_cost += tempCost;
                        if (tempCost > lsobb_locate_success_max_cost)
                        {
                            lsobb_locate_success_max_cost = tempCost;
                        }
                        printShipment(s); // si se encuentra es informado por pantalla
                    }
                    else
                    {
                        lsobb_locate_failure_count++;
                        lsobb_locate_failure_total_cost += tempCost;
                        if (tempCost > lsobb_locate_failure_max_cost)
                        {
                            lsobb_locate_failure_max_cost = tempCost;
                        }
                        printf("El envio solicitado no se encuentra en el sistema. (lsobb)\n");
                        // system(pause);
                    }

                    // ABB

                    if (Abb_evocateShipment(tree, &s, &tempCost) == 0)
                    {
                        abb_locate_success_count++;
                        abb_locate_success_total_cost += tempCost;
                        if (tempCost > abb_locate_success_max_cost)
                        {
                            abb_locate_success_max_cost = tempCost;
                        }
                        printShipment(s); // si se encuentra es informado por pantalla
                    }
                    else
                    {
                        abb_locate_failure_count++;
                        abb_locate_failure_total_cost += tempCost;
                        if (tempCost > abb_locate_failure_max_cost)
                        {
                            abb_locate_failure_max_cost = tempCost;
                        }
                        printf("El envio solicitado no se encuentra en el sistema. (abb)\n");
                        // system(pause);
                    }
                }
            }

            // Cierra el archivo
            fclose(file);

            // Realiza otras operaciones

            // LSO
            lso_locate_success_avg_cost = lso_locate_success_total_cost / (float)lso_locate_success_count;
            lso_locate_failure_avg_cost = lso_locate_failure_total_cost / (float)lso_locate_failure_count;
            lso_create_success_avg_cost = lso_create_success_total_cost / (float)lso_create_success_count;
            lso_delete_success_avg_cost = lso_delete_success_total_cost / (float)lso_delete_success_count;

            // LSOBB
            lsobb_locate_success_avg_cost = lsobb_locate_success_total_cost / (float)lsobb_locate_success_count;
            lsobb_locate_failure_avg_cost = lsobb_locate_failure_total_cost / (float)lsobb_locate_failure_count;
            lsobb_create_success_avg_cost = lsobb_create_success_total_cost / (float)lsobb_create_success_count;
            lsobb_delete_success_avg_cost = lsobb_delete_success_total_cost / (float)lsobb_delete_success_count;

            // ABB
            abb_locate_success_avg_cost = abb_locate_success_total_cost / (float)abb_locate_success_count;
            abb_locate_failure_avg_cost = abb_locate_failure_total_cost / (float)abb_locate_failure_count;
            abb_create_success_avg_cost = abb_create_success_total_cost / (float)abb_create_success_count;
            abb_delete_success_avg_cost = abb_delete_success_total_cost / (float)abb_delete_success_count;

            // muestra resultados
            // // LSO
            // printf("----------------------------------------\n");
            // printf("los costos de la lso fueron:...\n");
            // printf("----------------------------------------\n");
            // printf("evocacion exitosa:\n");
            // printf("costo máximo: %d, costo promedio: %f\n", lso_locate_success_max_cost, lso_locate_success_avg_cost);
            // printf("----------------------------------------\n");
            // printf("evocacion no exitosa:\n");
            // printf("costo máximo: %d, costo promedio: %f\n", lso_locate_failure_max_cost, lso_locate_failure_avg_cost);
            // printf("----------------------------------------\n");
            // printf("Alta:\n");
            // printf("costo máximo: %d, costo promedio: %f\n", lso_create_success_max_cost, lso_create_success_avg_cost);
            // printf("----------------------------------------\n");
            // printf("Baja:\n");
            // printf("costo máximo: %d, costo promedio: %f\n", lso_delete_success_max_cost, lso_delete_success_avg_cost);
            // // LSOBB
            // printf("----------------------------------------\n");
            // printf("los costos de la lsobb fueron:...\n");
            // printf("----------------------------------------\n");
            // printf("evocacion exitosa:\n");
            // printf("costo máximo: %d, costo promedio: %f\n", lsobb_locate_success_max_cost, lsobb_locate_success_avg_cost);
            // printf("----------------------------------------\n");
            // printf("evocacion no exitosa:\n");
            // printf("costo máximo: %d, costo promedio: %f\n", lsobb_locate_failure_max_cost, lsobb_locate_failure_avg_cost);
            // printf("----------------------------------------\n");
            // printf("Alta:\n");
            // printf("costo máximo: %d, costo promedio: %f\n", lsobb_create_success_max_cost, lsobb_create_success_avg_cost);
            // printf("----------------------------------------\n");
            // printf("Baja:\n");
            // printf("costo máximo: %d, costo promedio: %f\n", lsobb_delete_success_max_cost, lsobb_delete_success_avg_cost);

            // // ABB
            // printf("----------------------------------------\n");
            // printf("los costos del abb fueron:...\n");
            // printf("----------------------------------------\n");
            // printf("evocacion exitosa:\n");
            // printf("costo máximo: %d, costo promedio: %f\n", abb_locate_success_max_cost, abb_locate_success_avg_cost);
            // printf("----------------------------------------\n");
            // printf("evocacion no exitosa:\n");
            // printf("costo máximo: %d, costo promedio: %f\n", abb_locate_failure_max_cost, abb_locate_failure_avg_cost);
            // printf("----------------------------------------\n");
            // printf("Alta:\n");
            // printf("costo máximo: %f, costo promedio: %f\n", abb_create_success_max_cost, abb_create_success_avg_cost);
            // printf("----------------------------------------\n");
            // printf("Baja:\n");
            // printf("costo máximo: %f, costo promedio: %f\n", abb_delete_success_max_cost, abb_delete_success_avg_cost);

            printf("----------------------------------------------------------------------------------------\n");
            printf("Operación              | LSO                      | LSOBB                    | ABB\n");
            printf("----------------------------------------------------------------------------------------\n");

            // Mostrar resultados para la operación "evocacion exitosa"
            printf("Evocacion Exitosa      | Max: %-5d Avg: %-8.2f | Max: %-5d Avg: %-8.2f | Max: %-5d Avg: %-8.2f\n",
                   lso_locate_success_max_cost, lso_locate_success_avg_cost,
                   lsobb_locate_success_max_cost, lsobb_locate_success_avg_cost,
                   abb_locate_success_max_cost, abb_locate_success_avg_cost);

            // Mostrar resultados para la operación "evocacion no exitosa"
            printf("Evocacion No Exitosa   | Max: %-5d Avg: %-8.2f | Max: %-5d Avg: %-8.2f | Max: %-5d Avg: %-8.2f\n",
                   lso_locate_failure_max_cost, lso_locate_failure_avg_cost,
                   lsobb_locate_failure_max_cost, lsobb_locate_failure_avg_cost,
                   abb_locate_failure_max_cost, abb_locate_failure_avg_cost);

            // Mostrar resultados para la operación "Alta"
            printf("Alta                   | Max: %-5d Avg: %-8.2f | Max: %-5d Avg: %-8.2f | Max: %-5f Avg: %-8.2f\n",
                   lso_create_success_max_cost, lso_create_success_avg_cost,
                   lsobb_create_success_max_cost, lsobb_create_success_avg_cost,
                   abb_create_success_max_cost, abb_create_success_avg_cost);

            // Mostrar resultados para la operación "Baja"
            printf("Baja                   | Max: %-5d Avg: %-8.2f | Max: %-5d Avg: %-8.2f | Max: %-5f Avg: %-8.2f\n",
                   lso_delete_success_max_cost, lso_delete_success_avg_cost,
                   lsobb_delete_success_max_cost, lsobb_delete_success_avg_cost,
                   abb_delete_success_max_cost, abb_delete_success_avg_cost);

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
