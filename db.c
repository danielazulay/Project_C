#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "user.h"

int insert_duplicate(User *db, User *user, int *i);
int insert_new(User *db, User *user, int *i);
void insert_db(User **db, int *i);

int create_db(char **line, User **db, int *i)
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
  if (*i == 0)
  {
    *db= malloc(sizeof(User));
    (*db)[*i] = user;
 *i = (*i) + 1;
  }
  else if (insert_duplicate(*db, &user, i))
  {
    insert_db(db, i);
    insert_new(*db, &user, i);
   *i = (*i) + 1;
  }
   
  return 0;
}

int insert_duplicate(User *db, User *user, int *i)
{

  for (int j = 0; j < *i; j++)
  {

    if (db[j].idNumber == user->idNumber)
    {
      db[j].debt += user->debt;
      return 0;
    }
  }
  return 1;
}

int insert_new(User *db, User *user, int *i)
{
  int j;

  for (j = 0; j < *i - 1; j++)
  {

    if (db[j].debt < user->debt)
    {

      User aux = db[j];
      db[j] = *user;
      *user = aux;
    }
  }

  (db)[*i] = *user;
  
  return 0;
}

void insert_db(User **db, int *i)
{
  

  int x = (*i) + 1;
  *db = realloc(*db, x * sizeof(User));

  if (!db)
  {
    printf("Error on realloc");
  }
}