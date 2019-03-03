//
// Created by Alistair The Gecko on 2/25/2019.
//

#include "operations.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int insert(product **l, product *node) {
    product *tmp = *l;
    while (tmp != NULL){
        if (strcmp(tmp->name, node->name) == 0){
            tmp->quantity_value += node->quantity_value;
            return 1;
        }
        if (tmp->next == NULL){
            tmp->next = node;
            return 2;
        }
        tmp = tmp->next;
    }
    *l = node;
    return 0;
}

void rmItem(product *l, product *node) {
    product *tmp = l;
    product *prev = tmp;
    while (tmp != NULL){
        if (strcmp(tmp->name, node->name) == 0){
            if (tmp == prev)
                l = l->next;
            else
                prev->next = tmp->next;
            free(tmp);
            break;
        }
        prev = tmp;
        tmp = tmp->next;
    }
}

void showList(product *l) {

}

int loadData(char inf[], product **l) {
    char q_unit[N], p_unit[N], name[N];
    int args;
    float quantity, price;
    product * tmp = *l;
    FILE *fin;
    fin = fopen(inf, "r");
    if (fin == NULL){
        printf("Failed to open file (%s)", inf);
        return 0;
    }
    while(1){
        args = fscanf(fin, "%s %f %s %f %s", name, &quantity,
                q_unit, &price, p_unit);
        if (args < 5)
            break;
        if (tmp == NULL){
            tmp = makeProduct(name, quantity, q_unit, price, p_unit);
        } else {
            tmp = tmp->next;
        }
    }


    return 1;
}

int saveData(char *outf, product *l) {
    FILE * fout = fopen(outf, "w");
    if(fout == NULL) {
        printf("InSave: File open failed (%s)\n", outf);
        return 0;
    }
    product * tmp = l;
    while (tmp != NULL) {
        fprintf(fout, "%s %f %s %f %s", tmp->name, tmp->quantity_value,
                tmp->quantity_unit, tmp->price_value, tmp->price_unit);
        tmp = tmp->next;
    }
    fclose(fout);
    return 1;
}

float purchase(product *l, char *product, float q) {
    return 0;
}

void check_price(product *l, char *p) {

}

void findItem(product *l, char *p) {
    product *tmp = l;
    while (tmp != NULL){
        if (strcmp(tmp->name, p) == 0){
            printf("\nName: %s\nQuantity: %.2f %s\n"
                   "Price: $%.2f %s\n", tmp->name, tmp->quantity_value,
                   tmp->quantity_unit, tmp->price_value, tmp->price_unit);
        }
        tmp = tmp->next;
    }

}

int doIt(char *data) {



    return 0;
}

product *makeProduct(char n[], float qv, char qu[], float pv, char pu[]) {
    product * tmp = (product *)malloc(sizeof(product));
    strcpy(tmp->name, n);
    tmp->quantity_value = qv;
    strcpy(tmp->quantity_unit, qu);
    tmp->price_value = pv;
    strcpy(tmp->price_unit, pu);
    tmp->next = NULL;
    return tmp;
}
