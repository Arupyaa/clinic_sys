#include "stdTypes.h"
#include "patients_list.h"
#include "reservations.h"
#include "user_interface.h"

int main()
{
	//insertPatientTop(5219273,"Rami",MALE,32);
	//insertPatientTop(5,"Gihan",FEMALE,14);
	//insertPatientBottom(52353273,"Mona",FEMALE,58);
	//insertPatientBottom(21219273,"Ezzat",MALE,22);
	//insertPatientTop(24419273,"Hossam",MALE,25);
	
	mainWindow();
	
	printAllPatients();
	
	
	
	//reserveSlot(TWO_THIRTY,52353273);
	//reserveSlot(FOUR_THIRTY,5219273);
	//reserveSlot(FOUR,5);
	//cancelSlotWID(521927311);
	//printAllslots();
	//
	//printAvailableSlots();
	
	return 0;
}

/*
TO DO:
align reservations in printslots func

print numbers to choose timeslot in printavailableslots func
and make it compatiable with choosing a slot

add security: static funcs and constant arg
*/