#include <stdio.h>
#include "medicine.h"
#include "utils.h"

extern Medicine meds[MAX_MED];
extern int count;

void billing() {
    char name[NAME_LEN];
    printf("Enter medicine name to sell: ");
    fgets(name, NAME_LEN, stdin); name[strcspn(name,"\n")]=0;
    int idx=-1;
    for(int i=0;i<count;i++)
        if(strcasecmp(meds[i].name,name)==0){ idx=i; break; }
    if(idx==-1){ printf("Not found.\n"); return; }

    Medicine *m=&meds[idx];
    printf("%s | Price %.2f | Available %d\n", m->name,m->price,m->quantity);
    printf("Quantity to sell: ");
    int q; if(scanf("%d",&q)!=1){ clear_stdin(); printf("Invalid\n"); return; }
    clear_stdin();
    if(q<=0 || q>m->quantity){ printf("Invalid qty\n"); return; }

    float total = q*m->price;
    m->quantity -= q;
    printf("Total = %.2f\n", total);
    printf("Confirm sale? (y/n): ");
    char c=getchar(); clear_stdin();
    if(c=='y'||c=='Y') printf("Sale completed\n");
    else { m->quantity+=q; printf("Cancelled\n"); }
}
