#ifndef MEDICINE_H
#define MEDICINE_H

#define MAX_MED 1000
typedef struct {
    char name[80];
    char treatment[80];
    int quantity;
    float price;
    int day, month, year;
    int shelf, row;
    int id;
} Medicine;

/* Function prototypes */
void addMedicine();
void displayAll();
int searchMedicineByName(const char *name);
void updateMedicine();
void deleteMedicine();
void checkExpiry();
void findAlternatives();
void showShelfLocation();
void searchByTreatment();

#endif

