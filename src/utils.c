#include <stdio.h>
#include <time.h>
#include "medicine.h"
#include "utils.h"

#define DATA_FILE "data/medicines.dat"

extern Medicine meds[MAX_MED];
extern int count;
extern int next_id;

void clear_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void pauseConsole() {
    printf("Press ENTER to continue...");
    getchar();
}

void loadFromFile() {
    FILE *fp = fopen(DATA_FILE, "rb");
    if (!fp) { count = 0; next_id = 1; return; }
    fread(&count, sizeof(int), 1, fp);
    fread(&next_id, sizeof(int), 1, fp);
    fread(meds, sizeof(Medicine), count, fp);
    fclose(fp);
}

void saveToFile() {
    FILE *fp = fopen(DATA_FILE, "wb");
    if (!fp) { printf("Error saving data.\n"); return; }
    fwrite(&count, sizeof(int), 1, fp);
    fwrite(&next_id, sizeof(int), 1, fp);
    fwrite(meds, sizeof(Medicine), count, fp);
    fclose(fp);
}

/* returns days left or -1 if expired */
int isExpiredOrSoon(int d, int m, int y, int *expiredFlag) {
    time_t t = time(NULL);
    struct tm now = *localtime(&t);

    struct tm exp = {0};
    exp.tm_mday = d; exp.tm_mon = m - 1; exp.tm_year = y - 1900;
    exp.tm_hour = 0; exp.tm_min = 0; exp.tm_sec = 0;
    time_t texp = mktime(&exp);
    if (texp == (time_t)-1) { *expiredFlag = 0; return -2; }

    double diff = difftime(texp, t);
    int days = (int)(diff / (60 * 60 * 24));
    if (days < 0) { *expiredFlag = 1; return -1; }
    *expiredFlag = 0;
    return days;
}
