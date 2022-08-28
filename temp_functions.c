#include <stdio.h>
#include "temp_functions.h"
#include <string.h>


int data_processing (int *err_msg, Temperature *month, Temperature *year, char *file_name)
{
    FILE *f;
    f = fopen(file_name,"r");

    int scaned;
    int y,m,d,h,mi,t;
    int line_counter = 0;
    int error_counter = 0;

    while((scaned = fscanf(f, "%d;%d;%d;%d;%d;%d;", &y, &m, &d, &h, &mi, &t))!=EOF)
    {
        line_counter++;
        if (scaned < 6 || t < -99 || t > 99)
        {
            error_counter++;
            char error[100] = {0};
            fscanf(f,"%[^\n]",error);
            if (*err_msg == 1)
            {
                printf("в строке:%d %d;%02d;%02d;%02d;%02d;",line_counter,y,m,d,h,mi);
                if (t < -99 || t > 99)printf("%d значение вышло за пределы\n",t);
                else printf("%s нет данных о температуре\n",error);
            }
        }
        else
        {
            year->count++;
            year->sum+=t;
            month[m].count++;
            month[m].sum+=t;

            if (year->count == 1)
            {
                year->max.ye = y;
                year->max.mon = m;
                year->max.day = d;
                year->max.hour = h;
                year->max.minute = mi;
                year->max.temp = t;

                year->min.ye = y;
                year->min.mon = m;
                year->min.day = d;
                year->min.hour = h;
                year->min.minute = mi;
                year->min.temp = t;
            }
            else
            {
                if (year->max.temp < t)
                {
                    year->max.ye = y;
                    year->max.mon = m;
                    year->max.day = d;
                    year->max.hour = h;
                    year->max.minute = mi;
                    year->max.temp = t;
                }

                if (year->min.temp > t)
                {
                    year->min.ye = y;
                    year->min.mon = m;
                    year->min.day = d;
                    year->min.hour = h;
                    year->min.minute = mi;
                    year->min.temp = t;
                }
            }
            if (month[m].count == 1)
            {
                month[m].max.ye = y;
                month[m].max.mon = m;
                month[m].max.day = d;
                month[m].max.hour = h;
                month[m].max.minute = mi;
                month[m].max.temp = t;

                month[m].min.ye = y;
                month[m].min.mon = m;
                month[m].min.day = d;
                month[m].min.hour = h;
                month[m].min.minute = mi;
                month[m].min.temp = t;
            }
            else
            {
                if (month[m].max.temp < t)
                {
                    month[m].max.ye = y;
                    month[m].max.mon = m;
                    month[m].max.day = d;
                    month[m].max.hour = h;
                    month[m].max.minute = mi;
                    month[m].max.temp = t;
                }
                if (month[m].min.temp > t)
                {
                    month[m].min.ye = y;
                    month[m].min.mon = m;
                    month[m].min.day = d;
                    month[m].min.hour = h;
                    month[m].min.minute = mi;
                    month[m].min.temp = t;
                }
            }
        }
    }
    fclose(f);
    printf("прочитано %d строк(и), из них %d с ошибками", line_counter, error_counter);
    if (line_counter > error_counter) return 1;
        else
        {
        printf("\n\n !!!! Все данные в файле с ошибками !!!!\n");
        return 0;
        }
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= ВЫВОД ПОЛУЧЕННОЙ ИНОФРМАЦИИ -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
void print_year(Temperature *month, Temperature *year)
{
    char mon_name[15] = "Неизвестный";
    printf("\n");
    printf("Выборка за год:\n");
    printf("------------------------------------------------------------------------------------------------\n");
    printf("В %d году ", year->max.ye);
    printf("среднегодовая температура составила: %d C\n",year->sum/year->count);
    printf("Относительно среднегодовой температуры теплыми месяцами были:\n");
    for (size_t i = 1; i <= 12; i++)
    {
        if (month[i].sum / month[i].count >= (year->sum/year->count)) printf("%s ",month_name(&month[i].max.mon, mon_name));
    }
    printf("\nмаксимальная температура составила %d град. и зафиксирована:\n", year->max.temp);
    for (size_t i = 1; i <= 12; i++)
    {
        if (year->max.temp == month[i].max.temp)
        {
            printf("%02d.%02d.%d ", month[i].max.day,month[i].max.mon, month[i].max.ye);
            printf("в %02d ч.%02d мин.\n",month[i].max.hour, month[i].max.minute);
        }
    }
    printf("Относительно среднегодовой температуры холодными месяцами были:\n");
    for (size_t i = 1; i <= 12; i++)
    {
        if (month[i].sum / month[i].count < (year->sum/year->count)) printf("%s ",month_name(&month[i].min.mon, mon_name));
    }
    printf("\nминимальная температура составила %d град. и зафиксирована:\n", year->min.temp);
    for (size_t i = 1; i <= 12; i++)
    {
        if (year->min.temp == month[i].min.temp)
        {
            printf("%02d.%02d.%d ", month[i].min.day,month[i].min.mon, month[i].min.ye);
            printf("в %02d ч.%02d мин.\n",month[i].min.hour, month[i].min.minute);
        }
    }
    printf("------------------------------------------------------------------------------------------------\n");

}

void print_month (int *month_arg, Temperature *month)
{
    char mon_name[15] = "Неизвестный";
    printf("\n");
    printf("Выборка за %s:\n", month_name(month_arg, mon_name));
    //printf("------------------------------------------------------------------------------------------------\n");
    printf("среднемесячная температура составила: %d C\n",month[*month_arg].sum/ month[*month_arg].count);
    printf("максимальная температура зафиксирована %02d.%02d.%d ", month[*month_arg].max.day,month[*month_arg].max.mon, month[*month_arg].max.ye);
    printf("в %02d ч.%02d мин. ",month[*month_arg].max.hour, month[*month_arg].max.minute);
    printf("и составила %d град.\n", month[*month_arg].max.temp);
    printf("минимальная температура зафиксирована %02d.%02d.%d ", month[*month_arg].min.day,month[*month_arg].min.mon, month[*month_arg].min.ye);
    printf("в %02d ч.%02d мин. ",month[*month_arg].min.hour, month[*month_arg].min.minute);
    printf("и составила %d град.\n", month[*month_arg].min.temp);
    printf("------------------------------------------------------------------------------------------------");
}
void print_all_month (Temperature *month)
{
    for (int i = 1; i <=12; i++) print_month(&i, month);
}




char* month_name(int *mon_numb, char name[])
{
    char s1[] = "Январь";
    char s2[] = "Февраль";
    char s3[] = "Март";
    char s4[] = "Апрель";
    char s5[] = "Май";
    char s6[] = "Июнь";
    char s7[] = "Июль";
    char s8[] = "Август";
    char s9[] = "Сентябрь";
    char s10[] = "Октябрь";
    char s11[] = "Ноябрь";
    char s12[] = "Декабрь";
    char s0[] = "--------";
    switch(*mon_numb)
    {
    case 1:
        strcpy(name,s1);
        break;
    case 2:
        strcpy(name,s2);
        break;
    case 3:
        strcpy(name,s3);
        break;
    case 4:
        strcpy(name,s4);
        break;
    case 5:
        strcpy(name,s5);
        break;
    case 6:
        strcpy(name,s6);
        break;
    case 7:
        strcpy(name,s7);
        break;
    case 8:
        strcpy(name,s8);
        break;
    case 9:
        strcpy(name,s9);
        break;
    case 10:
        strcpy(name,s10);
        break;
    case 11:
        strcpy(name,s11);
        break;
    case 12:
        strcpy(name,s12);
        break;
    default:
        strcpy(name,s0);
        break;
    }
    return name;
}
