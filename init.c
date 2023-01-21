#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "user.h"
#include "validate.h"
#define SIZE_LEN(x) sizeof(x) / sizeof(x[0])
typedef struct
{
  const char *func_Name;
  void (*function)(char *, char *, char *, int *, User *);
} functions;



void print_one(User *db);
void sel(char *variable, char *comp, char *value, int *i, User *db);
void printdb(User *db, int *i);
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

  while (fgets(line, sizeof(line), file))
  {
    check_data(line, &db, pt_i);
  }

  fclose(file);

  printdb(db, &i);
    functions arr_func[] = {{"select", &sel}};
  int op;
  char select[10] = {0};
  char variable[10] = {0};
  char cop[2] = {0};
  char value[10] = {0};
/*   char set[4] = {0};
  char variable1[10] = {0};
  char cop1[2] = {0};
  char value1[10] = {0};
  char variable2[10] = {0};
  char cop2[2] = {0};
  char value2[10] = {0};
  char variable3[10] = {0};
  char cop3[2] = {0};
  char value3[10] = {0};
  char variable4[10] = {0};
  char cop4[2] = {0};
  char value4[10] = {0};
  char variable5[10] = {0};
  char cop5[2] = {0};
  char value5[10] = {0}; */
  while (1)
  {
    printf("--------------MENU-----------------\n");
    printf("(0) console search \n");
    printf("(1) console input \n");
    printf("(2) Free memory\n");
    printf("(3) exit from the program\n");
    printf("------------------------------------\n");
    scanf("%u", &op);

    switch (op)
    {
    case 0:

      scanf("%s %s %s %s", select, variable, cop, value);
      puts("");
    
      (*arr_func[0].function)(variable, cop, value, &i, db);
      break;
    case 1:
/* 
      scanf("%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s", set, variable1, cop1, value1, variable2, cop2, value2, variable3, cop3, value3, variable4, cop4, value4, variable5, cop5, value5);
      puts("");
      (*arr_func[0].function)(variable1, cop1, value1, variable2, cop2, value2, variable3, cop3, value3, variable4, cop4, value4, variable5, cop5, value5, &i, db);

      break; */

    case 2:
      free_all(&db, pt_i);
      break;
    case 3:
      return 0;
      break;
    }
  }

  free_all(&db, pt_i);
  return 0;
}

void printdb(User *db, int *i)
{
  for (int k = 0; k < *i; k++)
  {
    printf("******Registre %d*******\n", k + 1);
    puts("");
    printf("First Name: %s Last Name: %s birth: %s Id Number: %d Phonne Number: %d Debt: %.2f Debt Date: %s \n", db[k].firstName, db[k].lastName, db[k].birth, db[k].idNumber, db[k].phone, db[k].debt, db[k].debt_date);

    puts("********************\n");
  }
}

void print_one(User *db)
{

  puts("");
  printf("First Name: %s Last Name: %s birth: %s Id Number: %d Phonne Number: %d Debt: %.2f Debt Date: %s \n", db->firstName, db->lastName, db->birth, db->idNumber, db->phone, db->debt, db->debt_date);
  puts("");
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

void sel(char *variable, char *comp, char *value, int *i, User *db)
{

 if (!strcmp("firstname", variable))
  {
    int flag = 0;
    for (int k = 0; k < *i; k++)
    {

      if (!strcmp(db[k].firstName, value))
      {
        flag = 1;
        User use = db[k];
        print_one(&use);
      }
    }
    if (flag == 0)
      printf("%s %s %s not found \n", variable, comp, value);
  }
  else if (!strcmp("lastname", variable))
  {
    int flag = 0;
    for (int k = 0; k < *i; k++)
    {

      if (!strcmp(db[k].lastName, value))
      {
        flag = 1;
        User use = db[k];
        print_one(&use);
      }
    }
    if (flag == 0)
      printf("%s %s %s not found \n", variable, comp, value);
  }
  else if (!strcmp("debt", variable))
  {

    if (!strcmp("=", comp))
    {
      int flag = 0;
      for (int k = 0; k < *i; k++)
      {
        if (db[k].debt == atoi(value))
        {
          flag = 1;
          User use = db[k];
          print_one(&use);
        }
      }
      if (flag == 0)
        printf("%s %s %s not found \n", variable, comp, value);
    }
    else if (!strcmp("<", comp))
    {
      int flag = 0;
      for (int k = 0; k < *i; k++)
      {
        if (db[k].debt < atoi(value))
        {
          flag = 1;
          User use = db[k];
          print_one(&use);
        }
      }
      if (flag == 0)
        printf("%s %s %s not found \n", variable, comp, value);
    }
    else if (!strcmp(">", comp))
    {
      int flag = 0;
      for (int k = 0; k < *i; k++)
      {
        if (db[k].debt > atoi(value))
        {
          flag = 1;
          User use = db[k];
          print_one(&use);
        }
      }
      if (flag == 0)
        printf("%s %s %s not found \n", variable, comp, value);
    }
    else if (!strcmp(">=", comp))
    {
      int flag = 0;
      for (int k = 0; k < *i; k++)
      {
        if (db[k].debt > atoi(value))
        {
          flag = 1;
          User use = db[k];
          print_one(&use);
        }
      }
      if (flag == 0)
        printf("%s %s %s not found \n", variable, comp, value);
    }
    else if (!strcmp("<=", comp))
    {
      int flag = 0;
      for (int k = 0; k < *i; k++)
      {
        if (db[k].debt <= atoi(value))
        {
          flag = 1;
          User use = db[k];
          print_one(&use);
        }
      }
      if (flag == 0)
        printf("%s %s %s not found \n", variable, comp, value);
    }
  } 
    
  
}
