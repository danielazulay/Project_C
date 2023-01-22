#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "user.h"
#include "validate.h"

typedef struct
{
  const char *func_Name;
  void (*function)(char *, char *, char *, int *, User *);
} functions;

typedef struct
{
  const char *func_Name;
  void (*function)(char *, int *, User **);
} functions2;

void print_one(User *db);
void sel(char *variable, char *comp, char *value, int *i, User *db);
void set(char *value, int *i, User **db);
void printdb(User *db, int *i);
void free_all(User **db, int *pt_i);
int compare_dates(char *value, char *date, int *i, char *comp);

int main(int argc, char **argv)
{

  User *db;
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
  functions2 arr_func2[] = {{"set", &set}};
  int op;
  char select[10] = {0};
  char variable[10] = {0};
  char cop[2] = {0};
  char value[10] = {0};
  char comand[1024];
  while (1)
  {
    printf("--------------MENU-----------------\n");
    printf("(0) console select \n");
    printf("(1) console set \n");
    printf("(2) Free memory\n");
    printf("(3) exit from the program\n");
    printf("------------------------------------\n");

    scanf("%d%*c", &op);

    switch (op)
    {
    case 0:

      scanf("%s %s %s %s", select, variable, cop, value);
      if(strcmp("select", select)){
        printf("Did you mean select");
        puts("");
        scanf("%s %s %s %s", select, variable, cop, value);
      }      
      puts("");
      (*arr_func[0].function)(variable, cop, value, &i, db);
      break;

    case 1:

      fgets(comand, sizeof(comand), stdin);
      (*arr_func2[0].function)(comand, &i, &db);
      printdb(db, &i);
      break;

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

  if (!strcmp("birth", variable)&&(!strcmp(">", comp) || !strcmp("<", comp)))
  {
      int flag = 0;
      for (int k = 0; k < *i; k++)
      {

        if (compare_dates(value, db[k].birth, i, comp))
        {
          flag = 1;
          User use = db[k];
          print_one(&use);
        }
      }
      if (flag == 0)
        printf("%s %s %s not found \n", variable, comp, value);
    }
    else if (!strcmp("debtdate", variable)&&(!strcmp(">", comp) || !strcmp("<", comp)))
    {

    
        int flag = 0;
        for (int k = 0; k < *i; k++)
        {

          if (compare_dates(value, db[k].debt_date, i, comp))
          {
            flag = 1;
            User use = db[k];
            print_one(&use);
          }
        }
        if (flag == 0)
          printf("%s %s %s not found \n", variable, comp, value);
    
    }
    else if (!strcmp("firstname", variable)&&!strcmp("=", comp))
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
      } else if (!strcmp("<", comp))
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
  void set(char *value, int *i, User **db)
  {

    char line[1024] = {0};

    char str[1024];
    strcpy(str, value);
    char *st1 = str;

    char *arr[7] = {0};

    for (int i = 0; i < 7; i++)
    {
      char *str2 = strtok(st1, "=");
      str2 = strtok(NULL, " ");
      arr[i] = str2;
      st1 = strstr(str, str2);
    }

    snprintf(line, 6 * sizeof(arr), "%s;%s;%s;%s;%s;%s;%s", arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], arr[6]);

    check_data(line, db, i);
  }

  int compare_dates(char *value, char *date, int *i, char *comp)
  {

    char valuedate[10];
    strcpy(valuedate, value);

    for (int j = 0; j < 10; j++)
    {
      if (!strcmp("<", comp))
      {
        if (date[j] > valuedate[j])
        {
          return 0;
        }
        else if (date[j] < valuedate[j])
        {
          return 1;
        }
      }

      if (!strcmp(">", comp))
      {
        if (date[j] < valuedate[j])
        {
          return 0;
        }
        else if (date[j] > valuedate[j])
        {
          return 1;
        }
      }
    }

    return 0;
  }

  // set firstname=carol lastname=setman birth=1986/04/24 idnumber=123456789 phonenumber=1234567891 debt=111 debtdate=2011/01/01