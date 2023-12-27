#include "pr_map.h"
#include <stdio.h>
#include <stdlib.h>


struct tmp {
    char *symbol;
    char *priceChange;
    char *priceChangePerc;
    char *weightavgprice;
    char *openprice;
    char *highprice;
    char *lowPrice;
    char *lastPrice;
    char *volume;
    char *quoteVolume;
    char *openTime;
    char *closeTime;
    char *firstId;
    char *lastId;
    char *count;
};


int main() {

    int *size = malloc(sizeof(int));
    *size = 0;
    char *response = "{\"symbol\":\"BTCUSDT\",\"priceChange\":\"-20.61000000\",\"priceChangePercent\":\"-0.048\",\"weightedAvgPrice\":\"42380.93691068\",\"openPrice\":\"42677.24000000\",\"highPrice\":\"42827.68000000\",\"lowPrice\":\"41637.60000000\",\"lastPrice\":\"42656.63000000\",\"volume\":\"35630.46712000\",\"quoteVolume\":\"1510052579.11089440\",\"openTime\":1703581860000,\"closeTime\":1703668287576,\"firstId\":3337447677,\"lastId\":3338793564,\"count\":1345888}";

    Property **prop = parse_get_response(response, size);

    for(int i = 0; i < *size; i++) {
        printf("Key is %s, value is %s\n", prop[i]->key, prop[i]->val);
    }

    struct tmp *tmp = malloc(sizeof(*tmp));

    set_property_in_struct_map(*size, tmp, prop);
    puts("----------------------------------------------------");

    printf("%s\n", tmp->symbol);
    printf("%s\n", tmp->priceChange);
    printf("%s\n", tmp->priceChangePerc);
    printf("%s\n", tmp->weightavgprice);
    printf("%s\n", tmp->openprice);
    printf("%s\n", tmp->highprice);
    printf("%s\n", tmp->lowPrice);
    printf("%s\n", tmp->lastPrice);
    printf("%s\n", tmp->volume);
    printf("%s\n", tmp->quoteVolume);
    printf("%s\n", tmp->openTime);
    printf("%s\n", tmp->closeTime);
    printf("%s\n", tmp->firstId);
    printf("%s\n", tmp->lastId);
    printf("%s\n", tmp->count);

    free_property(prop, *size);

    return 0;
}
