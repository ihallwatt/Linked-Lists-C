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
                *l = *l->next;
            else
                prev->next = tmp->next;
            break;
        }
        prev = tmp;
        tmp = tmp->next;
    }
}

void showList(product *l) {
    product *tmp = l;
    while (tmp != NULL){
        printf("\nName: %s\nQuantity: %.2f %s\n"
               "Price: $%.2f %s\n", tmp->name, tmp->quantity_value,
               tmp->quantity_unit, tmp->price_value, tmp->price_unit);
        tmp = tmp->next;
    }
}

int loadData(char inf[], product **l) {
    char q_unit[N], p_unit[N], name[N], q[N], p[N];
    int args;
    float quantity, price;
    FILE *fin = fopen(inf, "r");
    if (fin == NULL){
        printf("Failed to open file (%s)", inf);
        return 0;
    }
    while(1){
        args = fscanf(fin, "%s %s %s %s %s\n", name, q,
                q_unit, p, p_unit);
        if (args < 5)
            break;
        quantity = strtof(q, NULL);
        price = strtof(p, NULL);
        if (*l == NULL){
            *l = makeProduct(name, quantity, q_unit, price, p_unit);
        } else {
            insert(l, makeProduct(name, quantity, q_unit, price, p_unit));
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
        fprintf(fout, "%s %f %s %f %s\n", tmp->name, tmp->quantity_value,
                tmp->quantity_unit, tmp->price_value, tmp->price_unit);
        tmp = tmp->next;
    }
    fclose(fout);
    return 1;
}

float purchase(product *l, char *name, float q) {
    product *tmp = l;
    while (tmp != NULL){
        if (strcmp(tmp->name, name) == 0){
            if (q > tmp->quantity_value){
                q = tmp->quantity_value * tmp->price_value;
                rmItem(l, tmp);
                return q;
            }
            tmp->quantity_value -= q;
            return tmp->price_value * q;
        }
        tmp = tmp->next;
    }
    return 0;
}

void check_price(product *l, char *p) {
    product *tmp = l;
    while (tmp != NULL){
        if (strcmp(tmp->name, p) == 0){
            printf("%s Price = $%.2f %s\n", p, tmp->price_value, tmp->price_unit);
            break;
        }
        tmp = tmp->next;
    }

    if (tmp == NULL)
        printf("Product not currently available\n");
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
    float sales = 0;
    product *store = NULL;
    loadData("catalogue.txt", &store);
    int choice, done = 0;
    while(!done) {
        printf("\nWelcome to Ian Hall-Watt's grocery store!\n"
               "Please enter the number of the action you'd like to perform\n"
               "============================================================\n"
               "%s %31s\n%s %30s\n%s %20s\n%s %40s\n"
               "What do you want to do?\n", "1: Add product to store",
               "2: Purchase product", "3: Check price of product", "4: Show all products",
               "5: Clean up product from store", "6: Find product", "7: Inventory",
               "8: Done for today");

        fflush(stdin);
        scanf("%d", &choice);
        fflush(stdin);

        switch(choice){
            case 1:
                printf("Name of product?\n");
                char name[N], qv[N], pv[N];
                float q, p;
                fflush(stdin);
                scanf("%s", name);
                fflush(stdin);
                printf("Quantity and quantity unit (separated by a space)\n");
                scanf("%f %s", &q, qv);
                fflush(stdin);
                printf("Price and price unit (separated by a space)\n");
                scanf("%f %s", &p, pv);
                fflush(stdin);
                insert(&store, makeProduct(name, q, qv, p, pv));
                break;
            case 2:
                printf("Name and amount to purchase (separated by a space)\n");
                float amount, change;
                char pro[N], f[N];
                fflush(stdin);
                scanf("%s %s", pro, f);
                amount = strtof(f, NULL);
                change = purchase(store, pro, amount);
                sales += change;
                if (change == 0)
                    printf("Product misspelled or unavailable\n");
                break;
            case 3:
                printf("Input name of product\n");
                char in[N];
                fflush(stdin);
                scanf("%s", in);
                fflush(stdin);
                check_price(store, in);
                break;
            case 7:
                printf("\nSales so far: %f\n", sales);
            case 4:
                showList(store);
                break;
            case 5:
                printf("Input name of product\n");
                char inp[N];
                fflush(stdin);
                scanf("%s", inp);
                fflush(stdin);
                product *tmp = makeProduct(inp, 0, " ", 0, " ");
                rmItem(store, tmp);
                break;
            case 6:
                printf("Input name of product\n");
                char inpu[N];
                fflush(stdin);
                scanf("%s", inpu);
                fflush(stdin);
                findItem(store, inpu);
                break;

            case 8:
                printf("\nClosing Store. Goodbye!\n");
                done = 1;
                break;
            default:
                printf("\nInvalid response. Please try again.\n");
                break;
        }
    }
    saveData("catalogue.txt", store);
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
