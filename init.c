#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "user.h"
#include "validate.h"

typedef struct
{
  const char *func_Name;
  void (*function)(char *, int *, User **);
} functions;

void print_one(User *db);
void sel(char *value, int *i, User **db);
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

  if (argc < 0)
  {
    printf("Usage: %s <file name to read> <file name to write> <max area>\n", argv[0]);
    return 1;
  }

  FILE *file = fopen(argv[1], "r");

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

  functions arr_func[] = {{"select", &sel}, {"set", &set}};

  char comand[1024];
  while (1)
  {

    fgets(comand, sizeof(comand), stdin);

    if (strstr(comand, "select"))
    {
      (*arr_func[0].function)(comand, &i, &db);
    }
    else if (strstr(comand, "set"))
    {
      (*arr_func[1].function)(comand, &i, &db);
      printdb(db, &i);
    }
    else if (strstr(comand, "exit"))
    {
      free_all(&db, pt_i);
      break;
    }
  }
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

void sel(char *line, int *i, User **db)
{

  char str[1024] = {0};
  strcpy(str, line);

  char *point;
  char comp[2] = {0};
  char value[40] = {0};
  char variable[50] = {0};
  char *vr[] = {"firstname", "lastname", "birth", "idnumber", "phonenumber", "debt", "debtdate"};

  for (int i = 0; i < 7; i++)
  {
    char *str2 = strstr(str, *(vr + i));
    if (str2)
    {
      strcpy(variable, vr[i]);
      point = strtok(str2, " ");
      point = strtok(NULL, " ");
      strcpy(comp, point);
      point = strtok(line, point);
      point = strtok(NULL, "\n");
      point++;
      strcpy(value, point);
      break;
    }
  }

  if (!strcmp("birth", variable) && (!strcmp(">", comp) || !strcmp("<", comp)))
  {
    int flag = 0;
    for (int k = 0; k < *i; k++)
    {

      if (compare_dates(value, (*db)[k].birth, i, comp))
      {
        flag = 1;
        User use = (*db)[k];
        print_one(&use);
      }
    }
    if (flag == 0)
      printf("%s %s %s not found \n", variable, comp, value);
  }
  else if (!strcmp("debtdate", variable) && (!strcmp(">", comp) || !strcmp("<", comp)))
  {

    int flag = 0;
    for (int k = 0; k < *i; k++)
    {

      if (compare_dates(value, (*db)[k].debt_date, i, comp))
      {
        flag = 1;
        User use = (*db)[k];
        print_one(&use);
      }
    }
    if (flag == 0)
      printf("%s %s %s not found \n", variable, comp, value);
  }
  else if (!strcmp("firstname", variable) && !strcmp("=", comp))
  {
    int flag = 0;
    for (int k = 0; k < *i; k++)
    {

      if (!strcmp((*db)[k].firstName, value))
      {
        flag = 1;
        User use = (*db)[k];
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

      if (!strcmp((*db)[k].lastName, value))
      {
        flag = 1;
        User use = (*db)[k];
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
        if ((*db)[k].debt == atoi(value))
        {
          flag = 1;
          User use = *db[k];
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
        if ((*db)[k].debt < atoi(value))
        {
          flag = 1;
          User use = (*db)[k];
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
        if ((*db)[k].debt > atoi(value))
        {
          flag = 1;
          User use = (*db)[k];
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
        if ((*db)[k].debt > atoi(value))
        {
          flag = 1;
          User use = (*db)[k];
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
        if ((*db)[k].debt <= atoi(value))
        {
          flag = 1;
          User use = (*db)[k];
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

  char *arr[7] = {0};

  char *vr[] = {"firstname=", "lastname=", "birth=", "idnumber=", "phonenumber=", "debt=", "debtdate="};

  for (int i = 0; i < 7; i++)
  {

    char *str2 = strstr(str, vr[i]);
    arr[i] = strtok(str2, "=");
    arr[i] = strtok(NULL, " ");
    printf("%s ", arr[i]);
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
