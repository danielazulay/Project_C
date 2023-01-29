#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "user.h"

int pti;
User *db;

int insert_duplicate( User *user);
int insert_new( User *user);
int insert_db();
int compare_dates(char *value, char *date, char *comp);
void init_db();



int create_db(char **line)
{

  User user;

  char *value = strtok(*line, ";");
  int col = 0;

  while (value)
  {

    if (col == 0)
    {
      user.firstName = strdup(value);
    }

    if (col == 1)
    {
      user.lastName = strdup(value);
    }
    if (col == 2)
    {
      user.birth = strdup(value);
    }

    if (col == 3)
    {
      user.idNumber = atoi(value);
    }

    if (col == 4)
    {
      user.phone = atoi(value);
    }
    if (col == 5)
    {
      user.debt = atof(value);
    }
    if (col == 6)
    {
      user.debt_date = strdup(value);
    }

    value = strtok(NULL, "; ");
    col++;
  }
  if (pti == 0)
  {
    db = malloc(sizeof(User));
    db[pti] = user;
    pti++;
  }
  else if (insert_duplicate( &user))
  {
    insert_db();
    insert_new(&user);
    pti++;
  }

  return 0;
}

int insert_duplicate(User *user)
{

  for (int j = 0; j < pti; j++)
  {

    if (db[j].idNumber == user->idNumber)
    {
      db[j].debt += user->debt;

      return 0;
    }
  }
  return 1;
}

int insert_new( User *user)
{
  int j;

  for (j = 0; j < pti - 1; j++)
  {

    if (db[j].debt < user->debt)
    {

      User aux = db[j];
      db[j] = *user;
      *user = aux;
    }
  }

  (db)[pti] = *user;

  return 0;
}

int insert_db()
{
  int x = pti + 1;
  db = realloc(db, x * sizeof(User));

  if (!db)
  {
    printf("Error on realloc");
  }
  return 0;
}

void printdb()
{
  for (int k = 0; k < pti; k++)
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
};

int select2(char *line ,char *newBuffer)
{

  char variable[50];
  char comp[50];
  char value[50];

  int col = 0;
  char *val = strtok(line, ";");

  while (val)
  {
    if (col == 0)
    {
      strcpy(variable, val);
    }
    if (col == 1)
    {

      strcpy(comp, val);
    }

    if (col == 2)
    {
      strcpy(value, val);
    }

    val = strtok(NULL, "; ");
    col++;
  }

  

  if (!strcmp("birth", variable) && (!strcmp(">", comp) || !strcmp("<", comp)))
  {
    int flag = 0;
    for (int k = 0; k < pti; k++)
    {

      if (compare_dates(value, db[k].birth, comp))
      {
        flag = 1;
        User use = db[k];
        print_one(&use);
      }
    }
    if (flag == 0)
      printf("%s %s %s not found \n", variable, comp, value);
  }
  else if (!strcmp("debtdate", variable) && (!strcmp(">", comp) || !strcmp("<", comp)))
  {

    int flag = 0;
    int i=0;
    for (int k = 0; k < pti; k++)
    {

      if (compare_dates(value, db[k].debt_date, comp))
      {
 
        flag = 1;
        User use = db[k];
        print_one(&use);
       
      
      }
    }
    if (flag == 0){
      
   printf("%s %s %s %d not found \n", variable, comp, value,pti);

    }

  }
  else if (!strcmp("firstname", variable) && !strcmp("=", comp))
  {
    int flag = 0;

    for (int k = 0; k < pti; k++)
    {

      if (!strcmp(db[k].firstName, value))
      {
        flag = 1;
        //User use = db[k];
        //print_one(&use);
        
    snprintf(newBuffer,1024, "First Name: %s Last Name: %s birth: %s Id Number: %d Phonne Number: %d Debt: %.2f Debt Date: %s \n",db[k].firstName, db[k].lastName, db[k].birth, db[k].idNumber, db[k].phone, db[k].debt, db[k].debt_date);

      }
    }
    if (flag == 0){

    snprintf(newBuffer, 1024,"%s %s %s not found \n", variable,comp, value );
     // printf("%s %s %s %d not found \n", variable, comp, value,pti);
   
    }
  
  }
  else if (!strcmp("lastname", variable))
  {
    int flag = 0;
    for (int k = 0; k < pti; k++)
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
      for (int k = 0; k < pti; k++)
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
      for (int k = 0; k < pti; k++)
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
      for (int k = 0; k < pti; k++)
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
      for (int k = 0; k < pti; k++)
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
      for (int k = 0; k < pti; k++)
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


   return 0;
}

int compare_dates(char *value, char *date, char *comp)
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


void init_db(){
pti=0;
}

