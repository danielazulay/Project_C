#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "user.h"
#include "db.h"
#include "validate.h"

int sel(char *line,char *newBuffer)
{

  char reply[1024] = {0};
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

    sprintf(reply, "%s;%s;%s", variable,comp, value);


   

   
 select2(reply,newBuffer);
 return 0;
}

int set(char *value)
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

  check_data(line);
  return 1;
}