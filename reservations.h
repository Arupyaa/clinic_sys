#ifndef RESERVATIONS_H
#define RESERVATIONS_H
#include "stdTypes.h"
#include <stdio.h>


enum Slots{TWO,TWO_THIRTY,THREE,FOUR,FOUR_THIRTY};
typedef enum Slots Slots;

enum RStatus{R_SUCCESS=1,R_FAILED=-1};
typedef enum RStatus RStatus;

//func to reserve a slot with an ID
RStatus reserveSlot(Slots slot,u64 ID);

//func to cancel a reservation with ID
RStatus cancelSlotWID(u64 ID);

//func to print available slots only
void printAvailableSlots();

//func to print slot given its enum
void printSlot(Slots slot);

//func to print all reservations
void printAllslots();

#endif //RESERVATIONS_H