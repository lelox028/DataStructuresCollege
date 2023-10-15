#include "ABB.h"
#include <stdlib.h>

Node *Abb_locateShipment(const Abb tree, Shipment s, Node **parent, float *cost)
{
    *parent = NULL;
    (*cost) = 0;
    Node *current = tree.root;
    while (current != NULL)
    {

        int res = strcmp(current->data.code, s.code);
        (*cost)++;

        if (res == 0)
        {
            return current;
        }
        else if (res < 0)
        {

            *parent = current;
            current = current->right;
        }
        else
        {
            *parent = current;
            current = current->left;
        }
    }
    return NULL;
}

int Abb_evocateShipment(Abb tree, Shipment *s, float *cost)
{
    if (tree.root == NULL)
        return 2; // empty structure
    Node *parent;
    Node *current = Abb_locateShipment(tree, *s, &parent, cost);
    if (current == NULL)
    {
        return 1; // not found
    }
    else
    {
        *s = current->data;
        return 0;
    }
}

int Abb_createShipment(Abb *tree, Shipment s, float *cost)
{
    float temp;
    Node *parent;
    Node *current = Abb_locateShipment(*tree, s, &parent, &temp);
    (*cost) = (float)0; // resets value

    if (current == NULL)
    {
        Node *newNode = (Node *)malloc(sizeof(Node));
        if (newNode == NULL)
        {
            // no se pudo asignar memoria
            return 1; // Indica falla
        }

        // Asigna los datos al nuevo nodo
        newNode->data = s;
        newNode->left = NULL;
        newNode->right = NULL;

        if (tree->root == NULL)
        {
            // Si el árbol estaba vacío, el nuevo nodo se convierte en la raíz
            tree->root = newNode;
            (*cost) = ((*cost) + 0.5f);
        }
        else
        {
            // Inserta el nuevo nodo en la posición adecuada
            if (strcmp(parent->data.code, s.code) < 0)
            {
                parent->right = newNode;
                (*cost) = ((*cost) + 0.5f);
            }
            else
            {
                parent->left = newNode;
                (*cost) = ((*cost) + 0.5f);
            }
        }

        // Incrementa el tamaño del árbol
        tree->size++;
        //(*cost)+=0.5f;
        return 0; // success
    }
    else
    {
        return 2; // duplicado
    }
}

int Abb_updateShipment(Abb *tree, Shipment s)
{
    if (tree->root == NULL)
        return 2; // empty structure
    Node *parent;
    float temp;
    Node *current = Abb_locateShipment(*tree, s, &parent, &temp);
    if (current == NULL)
    {
        return 1; // not found
    }
    // control para abortar
    char choice2;
    printf("seguro que desea eleminar el siguiente envio?\n");
    printShipment(current->data);
    do
    {
        printf("Ingrese 'y' para sí o 'n' para no: ");
        scanf(" %c", &choice2);
    } while (choice2 != 'y' && choice2 != 'n');
    if (choice2 == 'y')
    {
        current->data = s;
        return 0; // success
    }
    else
    {
        return 3; // abort
    }
}

int Abb_deleteShipment(Abb *tree, Shipment s, float *cost)
{
    if (tree->root == NULL)
        return 2; // empty structure
    Node *parent = NULL;
    Node *current = Abb_locateShipment(*tree, s, &parent, cost);
    (*cost) = (float)0; // cleaning value
    if (current == NULL)
    {
        return 1; // not found
    }
    // control para abortar
    char choice2 = 'y';
    // printf("seguro que desea eleminar el siguiente envio?\n");
    // printShipment(current->data);
    // do
    // {
    //     printf("Ingrese 'y' para sí o 'n' para no: ");
    //     scanf(" %c", &choice2);
    // } while (choice2 != 'y' && choice2 != 'n');
    if(!compareShipment(s,current->data)){
        choice2='y';
    }
    else{
        choice2='n';
    }
    if (choice2 == 'y')
    {
        // logica para borrar
        //  Caso 1: Nodo sin hijos
        if (current->left == NULL && current->right == NULL)
        {
            if (parent == NULL)
            {
                free(tree->root);
                tree->root = NULL;
                (*cost) += 0.5f;
            }
            else if (parent->left == current)
            {
                free(parent->left);
                parent->left = NULL;
                (*cost) += 0.5f;
            }
            else
            {
                free(parent->right);
                parent->right = NULL;
                (*cost) += 0.5f;
            }
        }
        // Caso 2: Nodo con un hijo
        else if (current->left == NULL || current->right == NULL)
        {
            Node *child = (current->left != NULL) ? current->left : current->right;
            if (parent == NULL)
            {
                free(tree->root);
                tree->root = child;
                (*cost) += 0.5f;
            }
            else if (parent->left == current)
            {
                free(parent->left);
                parent->left = child;
                (*cost) += 0.5f;
            }
            else
            {
                free(parent->right);
                parent->right = child;
                (*cost) += 0.5f;
            }
        }
        // Caso 3: Nodo con dos hijos
        else
        {
            // Menor de los mayores
            Node *successor = current->right;
            parent = current;
            while (successor->left != NULL)
            {
                parent = successor;
                successor = successor->left;
                //(*cost) += 0.5f;
            }

            current->data = successor->data;
            (*cost)++;

            if (parent->left == successor)
            {
                parent->left = successor->right;
                (*cost) += 0.5f;
            }
            else
            {
                parent->right = successor->right;
                (*cost) += 0.5f;
            }
            free(successor);
        }

        tree->size--;

        return 0; // Success
    }
    else
    {
        return 3; // abort
    }
}
/*
int Abb_loadFromFile(Abb *tree)
{
    FILE *fp;
    if ((fp = fopen("Envios.txt", "r")) == NULL)
    {
        return 1; // Error de archivo
    }
    Shipment temp;
    int res;
    int duplicated = 0;

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

        res = Abb_createShipment(tree, temp);
        if (res == 2) {
            duplicated++;
        }

        if (res ==1) {
            fclose(fp);
            break;
        }

        if (feof(fp)) {
            break;
        }
    }

    fclose(fp);
    if((res ==1)&&duplicated>0){
        return 4; //duplicates and full structure
    }
    else if (res ==1){
        return 2; // full list
    }
    else if (duplicated > 0) {
        return 3; // duplicates found
    } else {
        return 0; // success
    }
}
*/
void Abb_printStructure(Node *root)
{
    if (root != NULL)
    {
        printShipment(root->data);

        if (root->left != NULL)
        {
            printf("Código de Envío Hijo Izquierdo: %s\n", root->left->data.code);
        }
        else
        {
            printf("No existe un Hijo Izquierdo.\n");
        }
        if (root->right != NULL)
        {
            printf("Código de Envío Hijo Derecho: %s\n", root->right->data.code);
        }
        else
        {
            printf("No existe un Hijo Derecho.\n");
        }

        Abb_printStructure(root->left);
        Abb_printStructure(root->right);
    }
}

void freeAbbNodes(Node *node) {
    if (node == NULL) {
        return;
    }

    freeAbbNodes(node->left);
    freeAbbNodes(node->right);

    free(node);
}

void freeAbb(Abb *tree) {
    freeAbbNodes(tree->root);
    tree->root = NULL; 
    tree->size = 0;    
}
