#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funkcije.h"

void unesiModel() {
    Porsche novi;

    printf("\n--- Unos novog Porsche modela ---\n");

    printf("Model: ");
    fgets(novi.model, sizeof(novi.model), stdin);
    novi.model[strcspn(novi.model, "\n")] = '\0';

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

    FILE* fp = fopen(FILE_NAME, "a");
    if (!fp) {
        perror("Greska pri otvaranju datoteke");
        return;
    }

    fprintf(fp, "%s|%d|%s|%d|%d\n", novi.model, novi.godina, novi.boja, novi.ks, novi.kw);
    fclose(fp);

    printf("Model je uspjesno dodan!\n");
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

    // Sortiramo modele po nazivu prije nego što pozovemo bsearch
    qsort(modeli, count, sizeof(Porsche), usporediModel);

    printf("\n--- Popis Porsche modela ---\n");
    for (int i = 0; i < count; i++) {
        printf("Model: %s | Godina: %d | Boja: %s | KS: %d | kW: %d\n",
            modeli[i].model, modeli[i].godina, modeli[i].boja, modeli[i].ks, modeli[i].kw);
    }

    free(modeli);
}

int usporediGodinu(const void* a, const void* b) {
    const Porsche* p1 = (const Porsche*)a;
    const Porsche* p2 = (const Porsche*)b;
    return p2->godina - p1->godina;
}

int usporediModel(const void* a, const void* b) {
    const Porsche* p1 = (const Porsche*)a;
    const Porsche* p2 = (const Porsche*)b;
    return strcmp(p1->model, p2->model);
}

Porsche* nadjiModel(Porsche* modeli, int count, const char* trazeniModel) {
    Porsche key;
    strncpy(key.model, trazeniModel, MAX_MODEL);
    key.model[MAX_MODEL - 1] = '\0';
    return (Porsche*)bsearch(&key, modeli, count, sizeof(Porsche), usporediModel);
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
    printf("Unesi model za brisanje: ");
    fgets(trazeniModel, sizeof(trazeniModel), stdin);
    trazeniModel[strcspn(trazeniModel, "\n")] = '\0';

    // Pretražujemo model pomoću bsearch-a
    Porsche* p = nadjiModel(modeli, count, trazeniModel);

    if (!p) {
        printf("Model nije pronadjen.\n");
        free(modeli);
        return;
    }

    int index = (int)(p - modeli);
    for (int i = index; i < count - 1; i++) {
        modeli[i] = modeli[i + 1];
    }
    count--;

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

    printf("Model je uspjesno obrisan.\n");
}
