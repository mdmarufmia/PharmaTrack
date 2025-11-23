#include <stdio.h>
#include "medicine.h"
#include "utils.h"

/* external arrays */
extern Medicine meds[MAX_MED];
extern int count;
extern int next_id;

int main() {
    loadFromFile();
    int choice;
    while(1) {
        printf("\n===== PharmaTrack Menu =====\n");
        printf("1.Add 2.Display 3.Search 4.Update 5.Delete 6.Expiry 7.Alternatives\n");
        printf("8.Shelf 9.Treatment 10.Billing 11.Save & Exit\n");
        printf("Choice: ");
        if(scanf("%d",&choice)!=1){ clear_stdin(); printf("Invalid\n"); continue;}
        clear_stdin();
        switch(choice){
            case 1: addMedicine(); break;
            case 2: displayAll(); break;
            case 3: {
                char name[NAME_LEN]; printf("Name: "); fgets(name,NAME_LEN,stdin); name[strcspn(name,"\n")]=0;
                int idx = searchMedicineByName(name);
                if(idx==-1) printf("Not found\n");
                else printf("Found %s\n",meds[idx].name);
            } break;
            case 4: updateMedicine(); break;
            case 5: deleteMedicine(); break;
            case 6: checkExpiry(); break;
            case 7: findAlternatives(); break;
            case 8: showShelfLocation(); break;
            case 9: searchByTreatment(); break;
            case 10: billing(); break;
            case 11: saveToFile(); printf("Saved. Exit\n"); return 0;
            default: printf("Invalid\n");
        }
    }
}
