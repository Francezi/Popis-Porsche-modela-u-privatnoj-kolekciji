#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funkcije.h"

int main() {
    int izbor;

    while (1) {
        printf("\n--- Glavni izbornik ---\n");
        printf("1. Unesi novi model\n");
        printf("2. Prikazi modele\n");
        printf("3. Uredi model\n");
        printf("4. Izbrisi model\n");
        printf("5. Izlaz\n");

        izbor = unosBroja("Izbor: ");

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
                return 0;
            default:
                printf("Nepoznata opcija, pokusajte ponovo.\n");
        }
    }

    return 0;
}
