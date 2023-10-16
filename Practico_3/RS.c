#include<stdlib.h>
#include"RS.h"

void initRS(RS *rs) {
    for (int i = 0; i < FACTOR_RS; i++) {
        rs->baldes[i] = NULL;
    }
    rs->size = 0;
}
