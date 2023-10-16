#include <stdio.h>
#include <stdlib.h>
#include "Shipment.c"
#define MAX 300

/*
p=n/m y n=300 => m=n/p
RAL p=0.84 => m= 357
RAC p=0.75  =>m=400
RS p=1.45 =>m=207
*/

int hashing (char*x, int M){
    int longitud,i;
    int contador=0;
    longitud=strlen(x);
    for (i=0;i<longitud;i++){
        contador+=((int)x[i]) * (i+1);
    }
    return (contador%M);
}

int main(){
    printf("Hello World!");
    getchar();
    return 0;
}