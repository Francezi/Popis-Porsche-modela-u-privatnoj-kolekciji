#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "funkcije.h"

int main() {
    int izbor;

    do {
        printf("\n--- Porsche kolekcija ---\n");
        printf("1. Prikazi modele\n");
        printf("2. Unesi novi model\n");
        printf("3. Uredi model\n");
        printf("4. Izbrisi model\n");
        printf("5. Izlaz\n");
        printf("Izbor: ");
        scanf("%d", &izbor);
        getchar();

        switch (izbor) {
        case PRIKAZI:
            prikaziModele();
            break;
        case UNESI:
            unesiModel();
            break;
        case UREDI:
            urediModel();
            break;
        case IZBRISI:
            izbrisiModel();
            break;
        case IZLAZ:
            printf("Dovidjenja!\n");
            break;
        default:
            printf("Nepostojeca opcija, pokusajte ponovo.\n");
            break;
        }

    } while (izbor != IZLAZ);

    return 0;
}
