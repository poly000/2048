#ifndef FUNC_H

#define FUNC_H

#include <conio.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void movnum(int [],char);
void newnum(time_t *,int []);
void printout(time_t *,int []);
void add(int [],char);
bool is_lost(int []);
void lost(time_t *,int []);

#endif