#ifndef HEAD_F
#define HEAD_F

#include <stdio.h>
#include <stdlib.h>
#include<string.h>

void read();
void add();
void del();
void exp();
void longest();
void save();

struct eks{
    char code[20];
    int day;
    int month;
    int year;
    int dur;
    double price;
    struct eks*next;
};
struct eks* head=NULL;
struct eks*current=NULL;

#enddif
