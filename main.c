#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include "temp_functions.h"

int main(int argc, char *argv[])
{

    Temperature month [13] = {0};
    Temperature year = {0};

    enum {FILE_NAME_SIZE = 50};
    setlocale(LC_ALL, "Rus");
    FILE *f;
    int arg = 0, month_arg = 0, count_arg = 0, help_page_marker = 400;
    int flag_file_opend = 0, flag_error = 0, ready_for_print = 0, console_cls = 0;
    char file_name[FILE_NAME_SIZE] = {0}, mon_name[15] = "�����������";
    opterr = 0;

    while ((arg=getopt(argc,argv,"f:m:Mhec"))!= -1)
    {
        switch(arg)
        {
        case 'c':
            console_cls = 1;
            break;
        case 'h':
            if (console_cls) system("cls");
            count_arg = help_page_marker;
            printf("\n************************* ���������� ��� ������ ���������� ����������� ************************\n\n");
            printf("��� ������� ���������� ������� ���������� ������� �������� [-f] � ������ �����,\n");
            printf("���������� ������, ���������� � ������� �����������.\n");
            printf("���� ������ ������ � ��� �� �����, ��� ����� ���� ���������.\n");
            printf("��� �������������� ���������� ��������� ������� ������ �� ���.\n\n");
            printf("�������� ����������� ���� -99 � ���� 99 �������� �� ���������� � ��������� ����������.\n\n");
            printf("�������� ��������:\n");
            printf(" -f <filename.csv>        ����������� ������� ��� ����� [-c]\n\n");
            printf("�������������� ���������: \n\n");
            printf(" -m <����� ������ (1-12)> ��������� ���������� ������ �� ��������� �����\n");
            printf(" -M                       ��������� ���������� �� ��� ������\n");
            printf(" -e                       ������������� ��������� ������ � ���������� ������� ����������� � �����\n");
            printf(" -� (��������� ������)    �������� ����� ������� windows ����� ������� ����������\n");
            printf("\n -m <..> ����� ��������� ��� -M !!!!\n");
            break;
        case 'f':
            if (console_cls) system("cls");
            count_arg++;
            strncpy(file_name, optarg,FILE_NAME_SIZE);
            printf("\n���� %s ",file_name);
            if ((f=fopen(file_name,"r")) == NULL) printf("�� ������\n");
            else printf("������\n"), flag_file_opend = 1;
            fclose(f);
            if (f == NULL) return 1;
            break;
        case 'm':
            if (!flag_file_opend)
            {
                printf("\n* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n");
                printf("������� ������� ����!\n");
                printf("��� ������ ������� ������� �������� -h\n");
                printf("------------------------------------------------------------------------------------------------\n");
                return 1;
            }
            month_arg = atoi(optarg);
            if (month_arg > 12 && month_arg < 0)
            {
                printf("\n* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n");
                printf("������������ ����� ������, ������� �������� �� 1 �� 12\n");
                printf("------------------------------------------------------------------------------------------------\n");
                return 1;
            }
            break;
        case '?':
            printf("������ ����������� ��������!\n");
            break;
        case 'e':
            if (!flag_file_opend)
            {
                printf("\n* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n");
                printf("������� ������� ����!\n");
                printf("��� ������ ������� ������� ��������� -h\n");
                printf("------------------------------------------------------------------------------------------------\n");
                return 1;
            }
            flag_error = 1;
            break;
        case 'M':
            if (!flag_file_opend)
            {
                printf("\n* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n");
                printf("������� ������� ����!\n");
                printf("��� ������ ������� ������� ��������� -h\n");
                printf("------------------------------------------------------------------------------------------------\n");
                return 1;
            }
            if (month_arg == 0) month_arg = -1;
            break;
        }

    }
    if (!count_arg && count_arg != help_page_marker)
    {
        printf("\n* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n");
        printf("��������� ��������� � ������������ �����������!\n");
        printf("��� ������ ������� ������� �������� -h\n");
        printf("------------------------------------------------------------------------------------------------\n");
    }
    else if (count_arg != help_page_marker) ready_for_print = data_processing(&flag_error, month, &year, file_name);

    if (month_arg == 0 && ready_for_print) print_year (month, &year);
    if (month_arg > 0 && ready_for_print) print_month (&month_arg, month);
    if (month_arg == -1 && ready_for_print) print_all_month (month);
    return 0;
}
