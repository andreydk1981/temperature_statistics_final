#ifndef TEMP_FUNCTIONS_H_INCLUDED
#define TEMP_FUNCTIONS_H_INCLUDED

struct date
    {
        int ye, mon, day, hour, minute, temp;
    };

    struct temperature
    {
        int count, sum;
        struct date min;
        struct date max;

    };

typedef struct temperature Temperature;

int data_processing (int*, Temperature*, Temperature*, char*);
void print_year(Temperature*, Temperature*);
void print_month(int*, Temperature*);
void print_all_month(Temperature*);
char* month_name (int*, char[]);

#endif // TEMP_FUNCTIONS_H_INCLUDED
