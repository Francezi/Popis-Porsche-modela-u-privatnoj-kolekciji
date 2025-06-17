#ifndef FUNKCIJE_H
#define FUNKCIJE_H

#define MAX_MODEL 50
#define MAX_BOJA 30
#define FILE_NAME "porsche_models.txt"

// Struktura za pohranu podataka o Porsche modelima
typedef struct {
    char model[MAX_MODEL];
    int godina;
    char boja[MAX_BOJA];
    int ks;
    int kw;
} Porsche;

// Funkcije
void unesiModel();
void prikaziModele();
void urediModel();
void izbrisiModel();
int unosBroja(const char* poruka);
int usporediModel(const void* a, const void* b);
int usporediGodinu(const void* a, const void* b);
Porsche* nadjiModel(Porsche* modeli, int count, const char* trazeniModel);

#endif
