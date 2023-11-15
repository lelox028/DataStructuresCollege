#include "Shipment.h"

void inputCode(Shipment *s)
{
    printf("Ingrese el código: ");
    scanf("%7s", s->code); // maximo 7 caracteres
    for (int i = 0; s->code[i]; i++)
    {
        s->code[i] = tolower(s->code[i]); // convierte a minusculas
    }
}

void inputShipment(Shipment *s)
{
    // codigo ingresado afuera

    printf("Ingrese el DNI del receptor: ");
    while (scanf("%d", &(s->receiverDNI)) != 1 || s->receiverDNI < 0 || s->receiverDNI > 99999999)
    {
        printf("Entrada inválida. Por favor, ingrese un DNI válido del receptor: ");
        while (getchar() != '\n')
            ;
    }

    printf("Ingrese el nombre del receptor: ");
    scanf(" %[^\n]s", s->receiverName);

    printf("Ingrese la dirección del receptor: ");
    scanf(" %[^\n]s", s->receiverAddress);

    printf("Ingrese el DNI del remitente: ");
    while (scanf("%d", &(s->senderDNI)) != 1 || s->senderDNI < 0 || s->senderDNI > 99999999)
    {
        printf("Entrada inválida. Por favor, ingrese un DNI válido del remitente: ");
        while (getchar() != '\n')
            ;
    }

    printf("Ingrese el nombre del remitente: ");
    scanf(" %[^\n]s", s->senderName);

    printf("Ingrese la fecha de envío (yyyy/mm/dd): ");
    scanf("%10s", s->sendDate); // limite de 10 caracteres

    printf("Ingrese la fecha de recepción (yyyy/mm/dd): ");
    scanf("%10s", s->receiveDate); // limite de 10 caracteres
}

void printShipment(Shipment s)
{
    printf("Código: %s\n", s.code);
    printf("DNI del receptor: %d\n", s.receiverDNI);
    printf("Nombre del receptor: %s\n", s.receiverName);
    printf("Dirección del receptor: %s\n", s.receiverAddress);
    printf("DNI del remitente: %d\n", s.senderDNI);
    printf("Nombre del remitente: %s\n", s.senderName);
    printf("Fecha de envío: %s\n", s.sendDate);
    printf("Fecha de recepción: %s\n", s.receiveDate);
}

int compareShipment(Shipment shipment1, Shipment shipment2) {
    // Compara los campos uno por uno
    int codeComparison = strcasecmp(shipment1.code, shipment2.code);
    int receiverDNIComparison = shipment1.receiverDNI - shipment2.receiverDNI;
    int receiverNameComparison = strcasecmp(shipment1.receiverName, shipment2.receiverName);
    int receiverAddressComparison = strcasecmp(shipment1.receiverAddress, shipment2.receiverAddress);
    int senderDNIComparison = shipment1.senderDNI - shipment2.senderDNI;
    int senderNameComparison = strcasecmp(shipment1.senderName, shipment2.senderName);
    int sendDateComparison = strcasecmp(shipment1.sendDate, shipment2.sendDate);
    int receiveDateComparison = strcasecmp(shipment1.receiveDate, shipment2.receiveDate);

    // Devuelve el resultado de la comparación combinada
    if (codeComparison != 0) {
        return codeComparison;
    }
    if (receiverDNIComparison != 0) {
        return receiverDNIComparison;
    }
    if (receiverNameComparison != 0) {
        return receiverNameComparison;
    }
    if (receiverAddressComparison != 0) {
        return receiverAddressComparison;
    }
    if (senderDNIComparison != 0) {
        return senderDNIComparison;
    }
    if (senderNameComparison != 0) {
        return senderNameComparison;
    }
    if (sendDateComparison != 0) {
        return sendDateComparison;
    }
    return receiveDateComparison;
}