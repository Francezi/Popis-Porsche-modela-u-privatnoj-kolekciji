#ifndef FUNKCIJE_H
#define FUNKCIJE_H

#define MAX_MODEL 50
#define MAX_BOJA 30
#define FILE_NAME "porsche_models.txt"

typedef struct {
    char model[MAX_MODEL];
    int godina;
    char boja[MAX_BOJA];
    int ks;
    int kw;
} Porsche;

// Funkcije koje će se implementirati u funkcije.c
void unesiModel();
void prikaziModele();
void urediModel();
void izbrisiModel();

// Pomocna funkcija za usporedbu modela
int usporediModel(const void* a, const void* b);

// Funkcija za provjeru dupliciranja modela
int provjeriDupliciraniModel(Porsche* modeli, int count, const char* trazeniModel);

#endif
