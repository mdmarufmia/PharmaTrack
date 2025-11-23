#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "medicine.h"
#include "utils.h"

Medicine meds[MAX_MED];
int count = 0;
int next_id = 1;

void addMedicine() {
    if (count >= MAX_MED) { printf("Inventory full.\n"); return; }
    Medicine m;
    memset(&m, 0, sizeof(Medicine));

    printf("Medicine Name: ");
    fgets(m.name, NAME_LEN, stdin); m.name[strcspn(m.name,"\n")]=0;

    printf("Treatment/Category: ");
    fgets(m.treatment, TREAT_LEN, stdin); m.treatment[strcspn(m.treatment,"\n")]=0;

    printf("Quantity: "); scanf("%d",&m.quantity); clear_stdin();
    printf("Price per unit: "); scanf("%f",&m.price); clear_stdin();
    printf("Expiry Date (DD MM YYYY): "); scanf("%d %d %d",&m.day,&m.month,&m.year); clear_stdin();
    printf("Shelf number: "); scanf("%d",&m.shelf); clear_stdin();
    printf("Row number: "); scanf("%d",&m.row); clear_stdin();

    m.id = next_id++;
    meds[count++] = m;
    printf("Medicine '%s' added with ID %d.\n", m.name, m.id);
}

void displayAll() {
    if(count==0){ printf("No medicines.\n"); return; }
    printf("\n%-4s | %-30s | %-10s | %-5s | %-8s | %-10s | %-6s\n",
           "ID","Name","Treatment","Qty","Price","Expiry","Shelf/Row");
    printf("-----------------------------------------------------------------------------\n");
    for(int i=0;i<count;i++){
        Medicine *m=&meds[i];
        printf("%-4d | %-30s | %-10s | %-5d | %-8.2f | %02d-%02d-%04d | %02d/%02d\n",
               m->id,m->name,m->treatment,m->quantity,m->price,m->day,m->month,m->year,m->shelf,m->row);
    }
    pauseConsole();
}

int searchMedicineByName(const char *name){
    for(int i=0;i<count;i++)
        if(strcasecmp(meds[i].name,name)==0) return i;
    return -1;
}

void updateMedicine() {
    char name[NAME_LEN];
    printf("Enter medicine name to update: ");
    fgets(name, NAME_LEN, stdin); name[strcspn(name,"\n")]=0;
    int idx = searchMedicineByName(name);
    if(idx==-1){ printf("Not found.\n"); return; }
    Medicine *m=&meds[idx];

    printf("New quantity (current %d): ", m->quantity);
    int q; if(scanf("%d",&q)==1 && q>0) m->quantity=q; clear_stdin();
    printf("New price (current %.2f): ", m->price);
    float p; if(scanf("%f",&p)==1 && p>0) m->price=p; clear_stdin();
    printf("Medicine updated.\n");
}

void deleteMedicine() {
    char name[NAME_LEN];
    printf("Enter medicine name to delete: ");
    fgets(name, NAME_LEN, stdin); name[strcspn(name,"\n")]=0;
    int idx = searchMedicineByName(name);
    if(idx==-1){ printf("Not found.\n"); return; }
    printf("Confirm delete '%s'? (y/n): ", meds[idx].name);
    char c=getchar(); clear_stdin();
    if(c=='y'||c=='Y'){
        for(int i=idx;i<count-1;i++) meds[i]=meds[i+1];
        count--; printf("Deleted.\n");
    } else printf("Cancelled.\n");
}

void checkExpiry() {
    if(count==0){ printf("No medicines.\n"); return; }
    int expiredFlag;
    printf("\n%-4s | %-30s | %-5s | %-10s\n", "ID","Name","Qty","Status");
    printf("-------------------------------------------------------------\n");
    for(int i=0;i<count;i++){
        int days = isExpiredOrSoon(meds[i].day,meds[i].month,meds[i].year,&expiredFlag);
        if(expiredFlag || (days>=0 && days<=30)){
            printf("%-4d | %-30s | %-5d | %s\n", meds[i].id, meds[i].name, meds[i].quantity, expiredFlag?"EXPIRED":"Expiring soon");
        }
    }
    pauseConsole();
}

void findAlternatives() {
    char name[NAME_LEN];
    printf("Enter medicine name for alternatives: ");
    fgets(name, NAME_LEN, stdin); name[strcspn(name,"\n")]=0;
    int idx = searchMedicineByName(name);
    if(idx==-1){ printf("Not found.\n"); return; }
    char *treat=meds[idx].treatment;
    int found=0;
    for(int i=0;i<count;i++){
        if(i==idx) continue;
        if(strcasecmp(meds[i].treatment,treat)==0 && meds[i].quantity>0){
            printf("- %s | Qty %d | Price %.2f | Shelf %d Row %d\n",
                   meds[i].name,meds[i].quantity,meds[i].price,meds[i].shelf,meds[i].row);
            found++;
        }
    }
    if(!found) printf("No alternatives found.\n");
    pauseConsole();
}

void showShelfLocation() {
    char name[NAME_LEN];
    printf("Enter medicine name: ");
    fgets(name, NAME_LEN, stdin); name[strcspn(name,"\n")]=0;
    int idx=searchMedicineByName(name);
    if(idx==-1){ printf("Not found.\n"); return; }
    Medicine *m=&meds[idx];
    printf("Shelf: %d, Row: %d | Quantity: %d\n", m->shelf,m->row,m->quantity);
}

void searchByTreatment() {
    char treat[TREAT_LEN];
    printf("Enter treatment: ");
    fgets(treat, TREAT_LEN, stdin); treat[strcspn(treat,"\n")]=0;
    int found=0;
    for(int i=0;i<count;i++){
        if(strcasecmp(meds[i].treatment,treat)==0){
            printf("%s | Qty: %d | Price: %.2f\n", meds[i].name,meds[i].quantity,meds[i].price);
            found++;
        }
    }
    if(!found) printf("No medicines found.\n");
    pauseConsole();
}
