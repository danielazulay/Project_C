#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "db.h"
#include "user.h"




int check_date(char *word);
int count_digit(char *value);

int check_data(char *line)
{

    int flag = 1;
    int col = 0;

    char *line2 = strdup(line);

    char *value = strtok(line, ";");

    while (value)
    {
        if (col == 2)
        {

            if (check_date(value))
            {
                flag = 0;

                printf("invalid birth date->>  %s \n", line2);
            }
        }

        if (col == 3)
        {
            if (count_digit(value) != 9)
            {
                flag = 0;
                printf("invalid Id number->>  %s \n", line2);
            }
        }
        if (col == 4)
        {
            char a = '0';
            char b = value[0];

            if (a == b)
            {
                if (count_digit(value) != 9)
                {
                    flag = 0;
                    printf("invalid phone number->>  %s \n", line2);
                }
            }
            else if (count_digit(value) != 10)
            {
                flag = 0;
                printf("invalid phone number->>  %s \n", line2);
            }
        }
        if (col == 6)
        {
            if (check_date(value))
            {
                flag = 0;
                printf("invalid debt date->>  %s \n", line2);
            }
        }

        value = strtok(NULL, "; ");
        col++;
    }

    if (flag)
    {
        create_db(&line2);
    }
    free(line2);
    return 0;
}

int check_date(char *word)
{

    int yy = 0;
    int mm = 0;
    int dd = 0;

    sscanf(word, "%d/%d/%d", &yy, &mm, &dd);

    if (yy >= 1800 && yy <= 9999)
    {
        if (mm >= 1 && mm <= 12)
        {
            if ((dd >= 1 && dd <= 31) && (mm == 1 || mm == 3 || mm == 5 || mm == 7 || mm == 8 || mm == 10 || mm == 12))
            {
                return 0;
            }
            else if ((dd >= 1 && dd <= 30) && (mm == 4 || mm == 6 || mm == 9 || mm == 11))
            {
                return 0;
            }
            else if ((dd >= 1 && dd <= 28) && (mm == 2))
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }
    }
    return 1;
}

int count_digit(char *value)
{
    int x = atoi(value);

    int i = 0;
    do
    {
        x /= 10;
        i++;
    } while (x);

    return i;
}
