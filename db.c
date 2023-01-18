#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "user.h"




int create_db(char *line, User **db, int *i)
{



     if (*i != 0)
  {
    int x = (*i) + 1;
    *db = realloc(*db, x * sizeof(User));
    if (!db)
    {
      printf("Error on realloc");
    }
  }

  User user;

  char *value = strtok(line, ",");
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

    value = strtok(NULL, ", ");
    col++;
  }

if(*i==0){
  (*db)[*i] = user;
}else{
int x=1;
for(int j=0;j<*i;j++){

  if((*db)[j].idNumber==user.idNumber){
      if((*db)[j].debt<user.debt){
        User aux = (*db)[j];
            (*db)[j] = user;
            user= aux;
          x=0;
  }
  }
  if((*db)[j].debt<user.debt){
        User aux = (*db)[j];
            (*db)[j] = user;
            user= aux;
          x=0;
  }
}

    (*db)[*i] = user;


}
  *i = (*i) + 1; 

  free(line);
return 0;

}

