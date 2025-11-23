#ifndef UTILS_H
#define UTILS_H

#include "medicine.h"

/* File & utility functions */
void loadFromFile();
void saveToFile();
void clear_stdin();
void pauseConsole();
int isExpiredOrSoon(int d, int m, int y, int *expiredFlag);

#endif

