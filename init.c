#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "validate.h"




void free_all(User **db, int *pt_i);


int main(int argc, char **argv)
{



  char line[100];

  if (argc < 0)
  {
    printf("Usage: %s <file name to read> <file name to write> <max area>\n", argv[0]);
    return 1;
  }

  //FILE *file = fopen(argv[1], "r");
FILE *file = fopen("arquivo.csv", "r");
  if (!file)
  {
    printf("Error: file %s does not exist.\n", argv[1]);
    return 1;
  }

init_db();

  while (fgets(line, sizeof(line), file))
  {
    check_data(line);
    
  }
  printdb();

  fclose(file);

}





