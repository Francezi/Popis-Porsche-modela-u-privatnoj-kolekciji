#include <stdio.h>
#include <stdlib.h>
#include "funkcije.h"

int main() {
    int izbor;

    do {
        printf("\n--- Porsche Modeli ---\n");
        printf("1. Unesi novi model\n");
        printf("2. Prikazi modele\n");
        printf("3. Uredi model\n");
        printf("4. Izbrisi model\n");
        printf("5. Izlaz\n");
        printf("Izbor: ");
        scanf("%d", &izbor);
        getchar(); // da bi pročitao novi red nakon unosa

        switch (izbor) {
        case 1:
            unesiModel();
            break;
        case 2:
            prikaziModele();
            break;
        case 3:
            urediModel();
            break;
        case 4:
            izbrisiModel();
            break;
        case 5:
            printf("Izlaz...\n");
            break;
        default:
            printf("Nepoznata opcija. Pokusajte ponovo.\n");
        }
    } while (izbor != 5);

    return 0;
}
