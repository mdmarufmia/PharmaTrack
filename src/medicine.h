#ifndef MEDICINE_H
#define MEDICINE_H

#define MAX_MED 1000
#define NAME_LEN 80
#define TREAT_LEN 80

typedef struct {
    char name[NAME_LEN];
    char treatment[TREAT_LEN];
    int quantity;
    float price;
    int day, month, year;  // expiry date
    int shelf, row;        // location
    int id;                // unique ID
} Medicine;

/* Medicine management functions */
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
