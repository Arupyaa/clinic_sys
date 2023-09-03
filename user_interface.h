#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H
#include "patients_list.h"
#include "reservations.h"

#define PASSWORD "1234"

//main runtime window for the interfacing program
void mainWindow();

//user modes of interfacing with the system
enum UserModes{ADMIN=1,PATIENT=0,NONE=-1};
typedef enum UserModes UserModes;

//function to choose the mode of operation
u32 modeSet(u32 mode,UserModes* USER_STATUS);

//boolean check to see if the admin password was accepted or not
enum AdminStatus{A_ACCEPTED=1,A_REJECTED=0};
typedef enum AdminStatus AdminStatus;

//function to check for the admin password
AdminStatus adminCheck();


//function to compare 2 strings
//returns 1 for equal strings and 0 for unequal strings
u32 cmpS(const u8* str1,const u8* str2);


//main runtime window for admin user
void adminMode();

void patientMode();


//runtime window for adding new patient
void addWindow();


//runtime window for editing patient info
void editWindow();



#endif //USER_INTERFACE_H