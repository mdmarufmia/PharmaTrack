#include <stdio.h>
#include "medicine.h"

int main() {
    int choice;
    loadFromFile(); // from utils.c

    while(1) {
        printf("Menu...\n");
        scanf("%d", &choice);
        // switch-case calling medicine/billing functions
    }
}

