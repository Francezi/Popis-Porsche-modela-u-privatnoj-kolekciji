#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funkcije.h"

// Funkcija za usporedbu modela (koristi se za sortiranje)
int usporediModel(const void* a, const void* b) {
    const Porsche* p1 = (const Porsche*)a;
    const Porsche* p2 = (const Porsche*)b;
    return strcmp(p1->model, p2->model);
}

// Funkcija za provjeru dupliciranih modela
int provjeriDupliciraniModel(Porsche* modeli, int count, const char* trazeniModel) {
    for (int i = 0; i < count; i++) {
        if (strcmp(modeli[i].model, trazeniModel) == 0) {
            return 1; // Model postoji
        }
    }
    return 0; // Model ne postoji
}

void unesiModel() {
    Porsche novi;

    printf("\n--- Unos novog Porsche modela ---\n");

    printf("Model: ");
    fgets(novi.model, sizeof(novi.model), stdin);
    novi.model[strcspn(novi.model, "\n")] = '\0';

    // Otvaranje datoteke da bi smo učitali postojeće modele
    FILE* fp = fopen(FILE_NAME, "r");
    if (!fp) {
        perror("Greska pri otvaranju datoteke");
        return;
    }

    Porsche* modeli = malloc(5 * sizeof(Porsche));
    if (!modeli) {
        perror("Greska pri alokaciji memorije");
        fclose(fp);
        return;
    }

    int capacity = 5;
    int count = 0;
    char linija[200];

    // Učitavanje postojećih modela u memoriju
    while (fgets(linija, sizeof(linija), fp)) {
        if (count == capacity) {
            capacity *= 2;
            Porsche* temp = realloc(modeli, capacity * sizeof(Porsche));
            if (!temp) {
                perror("Greska pri realokaciji memorije");
                free(modeli);
                fclose(fp);
                return;
            }
            modeli = temp;
        }
        sscanf(linija, "%49[^|]|%d|%29[^|]|%d|%d",
            modeli[count].model,
            &modeli[count].godina,
            modeli[count].boja,
            &modeli[count].ks,
            &modeli[count].kw);
        count++;
    }
    fclose(fp);

    // Provjera dupliciranog modela
    if (provjeriDupliciraniModel(modeli, count, novi.model)) {
        printf("Model već postoji! Unos nije moguć.\n");
        free(modeli);
        return;
    }

    // Ako model nije duplikat, nastavljamo unos
    printf("Godina proizvodnje: ");
    scanf("%d", &novi.godina);
    getchar();

    printf("Boja: ");
    fgets(novi.boja, sizeof(novi.boja), stdin);
    novi.boja[strcspn(novi.boja, "\n")] = '\0';

    printf("Konjske snage (KS): ");
    scanf("%d", &novi.ks);

    printf("Kilovati (kW): ");
    scanf("%d", &novi.kw);
    getchar();

    // Spremanje novog modela u datoteku
    FILE* fpWrite = fopen(FILE_NAME, "a");
    if (!fpWrite) {
        perror("Greska pri otvaranju datoteke");
        free(modeli);
        return;
    }

    fprintf(fpWrite, "%s|%d|%s|%d|%d\n", novi.model, novi.godina, novi.boja, novi.ks, novi.kw);
    fclose(fpWrite);

    printf("Model je uspjesno dodan!\n");
    free(modeli);
}

void prikaziModele() {
    FILE* fp = fopen(FILE_NAME, "r");
    if (!fp) {
        printf("Jos nema unesenih modela.\n");
        return;
    }

    Porsche* modeli = malloc(5 * sizeof(Porsche));
    if (!modeli) {
        perror("Greska pri alokaciji memorije");
        fclose(fp);
        return;
    }
    int capacity = 5;
    int count = 0;
    char linija[200];

    while (fgets(linija, sizeof(linija), fp)) {
        if (count == capacity) {
            capacity *= 2;
            Porsche* temp = realloc(modeli, capacity * sizeof(Porsche));
            if (!temp) {
                perror("Greska pri realokaciji memorije");
                free(modeli);
                fclose(fp);
                return;
            }
            modeli = temp;
        }
        sscanf(linija, "%49[^|]|%d|%29[^|]|%d|%d",
            modeli[count].model,
            &modeli[count].godina,
            modeli[count].boja,
            &modeli[count].ks,
            &modeli[count].kw);
        count++;
    }
    fclose(fp);

    if (count == 0) {
        printf("Jos nema unesenih modela.\n");
        free(modeli);
        return;
    }

    // Sortiramo modele po nazivu
    qsort(modeli, count, sizeof(Porsche), usporediModel);

    printf("\n--- Popis Porsche modela ---\n");
    for (int i = 0; i < count; i++) {
        printf("Model: %s | Godina: %d | Boja: %s | KS: %d | kW: %d\n",
            modeli[i].model, modeli[i].godina, modeli[i].boja, modeli[i].ks, modeli[i].kw);
    }

    free(modeli);
}

void urediModel() {
    FILE* fp = fopen(FILE_NAME, "r");
    if (!fp) {
        perror("Greska pri otvaranju datoteke");
        return;
    }

    Porsche* modeli = malloc(5 * sizeof(Porsche));
    if (!modeli) {
        perror("Greska pri alokaciji memorije");
        fclose(fp);
        return;
    }
    int capacity = 5;
    int count = 0;
    char linija[200];

    while (fgets(linija, sizeof(linija), fp)) {
        if (count == capacity) {
            capacity *= 2;
            Porsche* temp = realloc(modeli, capacity * sizeof(Porsche));
            if (!temp) {
                perror("Greska pri realokaciji memorije");
                free(modeli);
                fclose(fp);
                return;
            }
            modeli = temp;
        }
        sscanf(linija, "%49[^|]|%d|%29[^|]|%d|%d",
            modeli[count].model,
            &modeli[count].godina,
            modeli[count].boja,
            &modeli[count].ks,
            &modeli[count].kw);
        count++;
    }
    fclose(fp);

    if (count == 0) {
        printf("Nema modela u bazi.\n");
        free(modeli);
        return;
    }

    // Sortiramo modele po nazivu
    qsort(modeli, count, sizeof(Porsche), usporediModel);

    char trazeniModel[MAX_MODEL];
    printf("Unesi model za uredivanje: ");
    fgets(trazeniModel, sizeof(trazeniModel), stdin);
    trazeniModel[strcspn(trazeniModel, "\n")] = '\0';

    // Pretražujemo model pomoću bsearch-a
    Porsche* p = nadjiModel(modeli, count, trazeniModel);

    if (!p) {
        printf("Model nije pronadjen.\n");
        free(modeli);
        return;
    }

    printf("Unesi novi naziv modela: ");
    fgets(p->model, sizeof(p->model), stdin);
    p->model[strcspn(p->model, "\n")] = '\0';

    printf("Nova godina proizvodnje: ");
    scanf("%d", &p->godina);
    getchar();

    printf("Nova boja: ");
    fgets(p->boja, sizeof(p->boja), stdin);
    p->boja[strcspn(p->boja, "\n")] = '\0';

    printf("Nove konjske snage (KS): ");
    scanf("%d", &p->ks);

    printf("Novi kilovati (kW): ");
    scanf("%d", &p->kw);
    getchar();

    FILE* fw = fopen(FILE_NAME, "w");
    if (!fw) {
        perror("Greska pri otvaranju datoteke za pisanje");
        free(modeli);
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fw, "%s|%d|%s|%d|%d\n",
            modeli[i].model,
            modeli[i].godina,
            modeli[i].boja,
            modeli[i].ks,
            modeli[i].kw);
    }
    fclose(fw);
    free(modeli);

    printf("Model je uspjesno azuriran.\n");
}

void izbrisiModel() {
    FILE* fp = fopen(FILE_NAME, "r");
    if (!fp) {
        printf("Nema modela u bazi.\n");
        return;
    }

    Porsche* modeli = malloc(5 * sizeof(Porsche));
    if (!modeli) {
        perror("Greska pri alokaciji memorije");
        fclose(fp);
        return;
    }
    int capacity = 5;
    int count = 0;
    char linija[200];

    while (fgets(linija, sizeof(linija), fp)) {
        if (count == capacity) {
            capacity *= 2;
            Porsche* temp = realloc(modeli, capacity * sizeof(Porsche));
            if (!temp) {
                perror("Greska pri realokaciji memorije");
                free(modeli);
                fclose(fp);
                return;
            }
            modeli = temp;
        }
        sscanf(linija, "%49[^|]|%d|%29[^|]|%d|%d",
            modeli[count].model,
            &modeli[count].godina,
            modeli[count].boja,
            &modeli[count].ks,
            &modeli[count].kw);
        count++;
    }
    fclose(fp);

    if (count == 0) {
        printf("Nema modela u bazi.\n");
        free(modeli);
        return;
    }

    char trazeniModel[MAX_MODEL];
    printf("Unesi model koji zelis izbrisati: ");
    fgets(trazeniModel, sizeof(trazeniModel), stdin);
    trazeniModel[strcspn(trazeniModel, "\n")] = '\0';

    // Pretražujemo model pomoću bsearch-a
    Porsche* p = nadjiModel(modeli, count, trazeniModel);

    if (!p) {
        printf("Model nije pronadjen.\n");
        free(modeli);
        return;
    }

    FILE* fw = fopen(FILE_NAME, "w");
    if (!fw) {
        perror("Greska pri otvaranju datoteke za pisanje");
        free(modeli);
        return;
    }

    for (int i = 0; i < count; i++) {
        if (strcmp(modeli[i].model, trazeniModel) != 0) {
            fprintf(fw, "%s|%d|%s|%d|%d\n",
                modeli[i].model,
                modeli[i].godina,
                modeli[i].boja,
                modeli[i].ks,
                modeli[i].kw);
        }
    }

    fclose(fw);
    free(modeli);

    printf("Model je uspjesno izbrisan.\n");
}
