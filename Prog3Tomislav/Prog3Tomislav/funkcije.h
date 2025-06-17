#define _CRT_SECURE_NO_WARNINGS

#ifndef FUNKCIJE_H
#define FUNKCIJE_H

#define FILE_NAME "porsche_baza.txt"
#define MAX_MODEL 50
#define MAX_BOJA 30

typedef struct {
    char model[MAX_MODEL];
    int godina;
    char boja[MAX_BOJA];
    int ks;
    int kw;
} Porsche;

typedef enum {
    PRIKAZI = 1,
    UNESI,
    UREDI,
    IZBRISI,
    IZLAZ
} Izbornik;

void unesiModel();
void prikaziModele();
void urediModel();
void izbrisiModel();

int usporediGodinu(const void* a, const void* b);
int usporediModel(const void* a, const void* b);
Porsche* nadjiModel(Porsche* modeli, int count, const char* trazeniModel);

#endif
