#ifndef USER_DB
#define USER_DB

typedef struct {
   char *firstName;
   char *lastName;
   char *birth;
   int idNumber;
   int phone;
   float debt;
   char *debt_date;  
}User;

#endif