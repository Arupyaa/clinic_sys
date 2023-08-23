#ifndef PATIENTS_LIST_H
#define PATIENTS_LIST_H
#include "stdTypes.h"
#include <stdlib.h>
#include <stdio.h>

//Gender of the patient is 1 if male and -1 if female
enum Gend{MALE=1,FEMALE=-1};
typedef enum Gend Gend;

//definition of a patient object
typedef struct Patient patient;
struct Patient
{
	u64 ID;
	u8* Name;
	Gend Gender;
	u8 Age;
	
	patient* next;
	
};


#define Gender(gender) gender==1?"Male":"Female"



//func to create a new patient and return a pointer to its obj
patient* createPatient(u64 ID,u8* Name, Gend Gender, u8 Age);

//Status messages indicating if the patient function succeeded or failed
enum PStatus{P_SUCCESS=1,P_FAILED=-1};
typedef enum PStatus PStatus;

//func to add a patient with a new unique ID to the start of the list 
PStatus insertPatientTop(u64 ID,u8* Name, Gend Gender, u8 Age);

//func to add a patient with a new unique ID to the end of the list
PStatus insertPatientBottom(u64 ID,u8* Name, Gend Gender, u8 Age);


//func to delete a patient from start of the list
PStatus deletePatientTop();

//func to delete a patient from the end of the list
PStatus deletePatientBottom();

//func to delete a patient from the list by his ID
PStatus deletePatientWID(u64 ID);

//func to check if the patient exists in the list by his ID and return a pointer to the patient obj if it was found
//returns a NULL if the patient wasn't found
patient* checkWID(u64 ID);

//func to find the address of the obj X located before obj Y in the list using obj Y's ID and return a pointer to obj X
patient* findPrevious(u64 ID);

//func to print all obj in the list
void printAllPatients();


#endif //PATIENTS_LIST_H