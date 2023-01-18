#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "db.h"
#include "user.h"
#include <regex.h>
typedef enum
{
    invalid,
    valid,

} Status;

// int check_string(char *word);

int check_data(char *line, User **db, int *i)
{

    Status flag = valid;
    int col = 0;
    //  char line2[100];
    char *line2 = strdup(line);

    char *value = strtok(line, ",");

    while (value)
    {

        /*  if (col == 0)
         {
             if (strlen(value) > 20 || check_string(value))
             {
                 flag = invalid;
             }
         }
         if (col == 1)
         {
             if (strlen(value) > 20 || check_string(value))
             {
                 flag = invalid;
             }
         } */
        /*             if(col==2){
                   if (strlen(value) > 20 || check_string(value))
                       {
                           flag = invalid;
                       }
                  }
                  if(col==3){
                    user.idNumber= malloc(10*sizeof(int));
                    strcpy(user.idNumber,value);
                }
                    if(col==4){
                        user.phone= malloc(10*sizeof(int));
                        strcpy(user.phone,value);
                    }
                 if(col==5){
                    user.debt= malloc(10*sizeof(float));
                     strcpy(user.debt,(float)value);
                 }*/
        if (col == 6)
        {
            regex_t reegex;
            int value;
            value = regcomp(&reegex, "^\d{4}\-(0?[1-9]|1[012])\-(0?[1-9]|[12][0-9]|3[01])$", 0);
            if (value == 0)
            {
                printf("RegEx compiled successfully.");
            }

            // Else for Compilation error
            else
            {
                printf("Compilation error.");
            };
         
        }

        value = strtok(NULL, ", ");
        col++;
    }
    // printf("%s",line2);
    // create_db(line2, &db, i);

    if (flag)
    {
        create_db(line2, db, i);
    }
    return 0;
}

/* int check_string(char *word)
{

    int size = strlen(word);
    int i;
    for (i = 0; i < size; i++)
    {

        if ((*word < 'a' || *word > 'z') || (*word < 'A' || *word > 'Z'))
        {
            return 1;
        }
    }

    while(1){

    }
    return 0;
} */


