#include "reservations.h"

//-1 indicates NULL (no reserved ID)
u64 T_Slots[5] = {-1,-1,-1,-1,-1};


RStatus reserveSlot(Slots slot,u64 ID)
{
	//check if the slot is free to be reserved
	if(T_Slots[slot] ==-1)
	{
		T_Slots[slot] = ID;
		return R_SUCCESS;
	}
	else
	{
		return R_FAILED;
	}
}

RStatus cancelSlotWID(u64 ID)
{
	//check if ID exists in reserved slots and delete it if it does
	u8 c= 0;
	while(c<5)
	{
		if(T_Slots[c] == ID)
		{
			T_Slots[c] = -1;
			return R_SUCCESS;
		}
		c++;
	}
	//ID wasn't found in the reserved slots
	return R_FAILED;
	
}

void printAvailableSlots()
{
	printf("Available time slots for the day:\n");
	for(u8 c = 0;c<5;c++)
	{
		if(T_Slots[c] ==-1)
		{
			printf("enter %d for timeslot: ",c);
			printSlot(c);
			printf("\n");
		}
	}
	printf("\n");
}

void printSlot(Slots slot)
{
	switch(slot)
	{
		case TWO:
		printf("2 to 2:30pm");
		break;
		case TWO_THIRTY:
		printf("2:30 to 3pm");
		break;
		case THREE:
		printf("3 to 4pm");
		break;
		case FOUR:
		printf("4 to 4:30pm");
		break;
		case FOUR_THIRTY:
		printf("4:30 to 5pm");
		break;
	}
}

void printAllslots()
{
	printf("Reservations for the day:\n");
	printf("2pm to 2:30pm\t\t2:30pm to 3pm\t\t3pm to 3:30pm\t\t4pm to 4:30pm\t\t4:30pm to 5pm\n");
	
	for(u8 c=0;c<5;c++)
	{
		if(T_Slots[c] ==-1)
		{
			printf("NONE\t\t");
		}
		else
		{
			printf("%llu\t\t",T_Slots[c]);
		}
	}
	printf("\n");
}