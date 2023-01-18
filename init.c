#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "user.h"
#include "validate.h"
#define SIZE_LEN(x) sizeof(x) / sizeof(x[0])

void printdb(User *db, int *i);
void set_in_order(User **db, int *pt_i, int field);
void free_all(User **db, int *pt_i);

int main(int argc, char **argv)
{

  User *db = malloc(sizeof(User));
  int i = 0;
  int *pt_i = &i;

  char line[100];

  /*    if (argc < 0)
    {
      printf("Usage: %s <file name to read> <file name to write> <max area>\n", argv[0]);
      return 1;
    }  */

  // FILE *file = fopen(argv[1], "r");
  FILE *file = fopen("arquivo.csv", "r");
  if (!file)
  {
    printf("Error: file %s does not exist.\n", argv[1]);
    return 1;
  }

  if (!file)
  {
    printf("Error");
    exit(1);
  }

  while (fgets(line, sizeof(line), file))
  {
    check_data(line, &db, pt_i);
  }

  fclose(file);

  int op;

  printdb(db, &i);

  while (1)
  {
    printf("--------------MENU-----------------\n");
    printf("(0) print the name in Order Alphabethic \n");
    printf("(1) print the last in Order Alphabethic \n");
    printf("(2) Free memory\n");
    printf("(3) exit from the program\n");
    printf("------------------------------------\n");
    scanf("%u", &op);

    switch (op)
    {
    case 0:
      puts("Print in Order by Name:\n");
      set_in_order(&db, pt_i, 0);
      // printdb(db, pt_i);

      break;
    case 1:
      puts("Print in Order by Last Name:\n");
      set_in_order(&db, pt_i, 1);

      break;

    case 2:
      free_all(&db, pt_i);
      break;
    case 3:
      return 0;
      break;
    case 8:
      break;
    case 7:

    default:
      break;
    }
  }

  return 0;
}

void printdb(User *db, int *i)
{
  for (int k = 0; k < *i; k++)
  {
    printf("******Registre %d*******\n", k + 1);
    puts("");
    printf("First Name: %s Last Name: %s birth: %s Id Number: %i Debt: %.2f Debt Date: %s \n", db[k].firstName, db[k].lastName, db[k].birth, db[k].idNumber, db[k].debt, db[k].debt_date);

    puts("********************\n");
  }
}

void set_in_order(User **db, int *i, int field)
{

  if (field == 0)
  {
    for (int j = 0; j < *i - 2; j++)
    {

      for (int k = 0; k < *i - 1; k++)
      {

        if ((*db)[k].firstName[0] > (*db)[k + 1].firstName[0])
        {
          User aux = (*db)[k + 1];
          (*db)[k + 1] = (*db)[k];
          (*db)[k] = aux;
        }
        else if ((*db)[k].firstName[0] == (*db)[k + 1].firstName[0])
        {
          int l = 0;

          while (((*db)[k].firstName[l] == (*db)[k + 1].firstName[l]) && (l <= strlen((*db)[k].firstName) || l <= strlen((*db)[k + 1].firstName)))
          {
            l++;
          }
          if ((*db)[k].firstName[l] > (*db)[k + 1].firstName[l])
          {
            User aux = (*db)[k + 1];
            (*db)[k + 1] = (*db)[k];
            (*db)[k] = aux;
          }
        }
      }
    }
  }
  else if (field == 1)
  {
    for (int j = 0; j < *i - 2; j++)
    {

      for (int k = 0; k < *i - 1; k++)
      {

        if ((*db)[k].lastName[0] > (*db)[k + 1].lastName[0])
        {

          User aux = (*db)[k + 1];
          (*db)[k + 1] = (*db)[k];
          (*db)[k] = aux;
        }
        else if ((*db)[k].lastName[0] == (*db)[k + 1].lastName[0])
        {
          int l = 0;

          while (((*db)[k].lastName[l] == (*db)[k + 1].lastName[l]) && (l <= strlen((*db)[k].lastName) || l <= strlen((*db)[k + 1].lastName)))
          {
            l++;
          }
          if ((*db)[k].lastName[l] > (*db)[k + 1].lastName[l])
          {

            User aux = (*db)[k + 1];
            (*db)[k + 1] = (*db)[k];
            (*db)[k] = aux;
          }
        }
      }
    }
  }

  printdb(*db, i);
}

void free_all(User **db, int *i)
{

  for (int k = 0; k < *i; k++)
  {

    free((*db)[k].firstName);
    free((*db)[k].lastName);
    free((*db)[k].birth);
    free((*db)[k].debt_date);
  }
  free(*db);
  puts("");
  printf("---memory freed---\n");
  puts("");
}
