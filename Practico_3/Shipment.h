#ifndef SHIPMENT_H
#define SHIPMENT_H
#define MAX 300
typedef struct
{
    char code[8]; // UniqueID
    int receiverDNI;
    char receiverName[81];
    char receiverAddress[81];
    int senderDNI;
    char senderName[81];
    char sendDate[11]; // yyyy/mm/dd + '\0'
    char receiveDate[11];
} Shipment;

// functions
void inputCode(Shipment *s);
void inputShipment(Shipment *s);
void printShipment(Shipment s);
int compareShipment(Shipment shipment1, Shipment shipment2);


#endif // SHIPMENT_H
