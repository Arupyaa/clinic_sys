#include "user_interface.h"

void mainWindow()
{
	while(1)
	{
		UserModes USER_STATUS = NONE;
	
		printf("<<<<<<Welcome to the clinic>>>>>>\n\nPlease choose between Admin Mode or User Mode:\n");
		
		u8 modeChoice;
		printf("Enter 1 for Admin Mode\tEnter 2 for User Mode\tEnter 3 to exit the program\n");
		
		
		printf("Input:");
		scanf("%u",&modeChoice);
		while((getchar()) != '\n');
		
		while(modeChoice!=1  && modeChoice!=2 && modeChoice!=3)
		{
			printf("Incorrect input, please try again\n");
			printf("Enter 1 for Admin Mode\tEnter 2 for User Mode\tEnter 3 to exit the program\n");
			
			printf("Input:");
			scanf("%u",&modeChoice);
			while((getchar()) != '\n');
			
		}
		
		//terminate program if user entered 3
		if(modeChoice == 3)
		{
			clearList();
			return;
		}	
		
		//returning 1 means the admin login has failed and the system should shutdown
		if(modeSet(modeChoice,&USER_STATUS) == 1)
		{
			clearList();
			return;
		}else if(USER_STATUS == ADMIN)
		{
			adminMode();
		}else if(USER_STATUS == PATIENT)
		{
			patientMode();
		}
		
	}
	
}


u8 modeSet(u8 mode,UserModes* USER_STATUS)
{
	if(mode==1)
	{
		AdminStatus AStatus = adminCheck();
		if(AStatus == A_ACCEPTED)
		{
			printf("Welcome Admin\n");
			*USER_STATUS = ADMIN;
			return 0;
		}
		else if(AStatus == A_REJECTED)
		{
			printf("System shutting down\n");
			return 1;
		}
	}
	else if(mode == 2)
	{
		printf("Welcome User\n");
		*USER_STATUS = PATIENT;
		return 0;
		
	}
}


AdminStatus adminCheck()
{
	u8* uPass = (u8*)malloc(sizeof(u8)*100);
	
	for(int c = 0;;c++)
	{
		printf("Please enter your admin password:");
		
		scanf("%[^\n]%*c",uPass);
		
		if(cmpS(uPass,PASSWORD))
		{
			free(uPass);
			return A_ACCEPTED;
		}	
		else if(c >= 2) //3 failed attempts were made
		{
			free(uPass);
			return A_REJECTED;
		}
		else
			printf("Incorrect password. Please try again\n");
	}
	
}


u8 cmpS(const u8* str1,const u8* str2)
{
	//loops until both str1 and str2 are finished
	for(int c = 0;str1[c] != '\0' || str2[c] != '\0';c++)
	{
		if(str1[c] == str2[c])
			continue;
		else
			return 0;
	}
	//if loop reaches the end it means both strings are equal
	return 1;
}


void adminMode()
{
	while(1)
	{
		u8 n;
		u64 i_ID;
		
		
		Gend i_gender =MALE;
		u8 i_genderN[10];
		u8 i_age;
		printf("\n");
		printf("Please enter a number for an operation:\n");
		printf("1:Add new patient record\n");
		printf("2:Edit an existing patient record\n");
		printf("3:Reserve a new appointment slot with the doctor\n");
		printf("4:Cancel an existing appointment with the doctor\n");
		printf("5:Logout of Admin mode\n");
		
		printf("Input:");
		scanf("%d",&n);
		while((getchar()) != '\n');
		
		u8* i_name = (u8*)malloc(sizeof(u8)*100);
		switch(n)
		{
			case 1:
			printf("Enter new patient Name: ");
			gets(i_name);
			
			printf("Enter new patient ID: ");
			scanf("%llu",&i_ID);
			while((getchar()) != '\n');
			
			printf("Enter new patient's gender in all small letters: ");
			scanf("%s",i_genderN);
			while((getchar()) != '\n');
			
			if(cmpS(i_genderN,"male"))
				i_gender = MALE;
			else if(cmpS(i_genderN,"female"))
				i_gender = FEMALE;
			
			printf("Enter new patient age: ");
			scanf("%u",&i_age);
			while((getchar()) != '\n');
			
			if(insertPatientTop(i_ID ,i_name ,i_gender ,i_age)== P_FAILED)
			{
				printf("A patient with this ID already exists, could not add the new patient record\n");
			}
			break;
			
			case 2:
			editWindow();
			break;
			
			case 3:
			printAvailableSlots();
			printf("Desired timeslot number: ");
			
			Slots i_slot;
			scanf("%u",&i_slot);
			while((getchar()) != '\n');
			
			
			printf("please enter the patient's ID for the reservation: ");
			i_ID = 0;
			
			scanf("%llu",&i_ID);
			while((getchar()) != '\n');
			
			if(reserveSlot(i_slot,i_ID) == R_FAILED)
				printf("Couldn't make reservation\n");
			
			break;
			
			case 4:
			printAllslots();
			printf("Enter patient's ID you wish to cancel his reservation: ");
			i_ID =0;
			
			scanf("%llu",&i_ID);
			while((getchar()) != '\n');
			
			if(cancelSlotWID(i_ID) ==R_FAILED)
				printf("Couldn't cancel such a reservation\n");
			else
				printf("Reservation cancelled successfully\n");
			
			break;
			case 5:
			return;
			break;
		}
		
	}
}

void editWindow()
{
	printf("Enter patient's ID you wish to edit: ");
	u64 i_ID;
	scanf("%llu",&i_ID);
	while((getchar()) != '\n');
	
	patient* curr_patient = editPatient(i_ID);
	if(curr_patient == NULL)
	{
		printf("This ID doesn't exist in the database\n");
		return;
	}
		
	while(1)
	{
		u32 str_len = getStrLen(curr_patient->Name);
		printf("\n");
		printf("%-*s|%-*s|%-*s|%-*s\n",str_len+3,"Name",5,"Age",7,"Gender",15,"ID");
		
		printf("%-*s|%-*d|%-*s|%-*llu\n",str_len+3,curr_patient->Name,5,curr_patient->Age,7,Gender(curr_patient->Gender),15,curr_patient->ID);
		printf("\n");
		
		printf("Choose patient parameter to edit: \n");
		printf("1: edit patient name\n");
		printf("2: edit patient ID\n");
		printf("3: edit patient gender\n");
		printf("4: edit patient age\n");
		printf("5: delete patient from records\n");
		printf("6: exit editing this patient\n");
		
		u8 uChoice;
		printf("Input:");
		scanf("%u",&uChoice);
		while((getchar()) != '\n');
		
		u8 i_genderN[10];
		if(uChoice == 6)
			return;
		else if(uChoice != 5)
			printf("Enter new parameter:");
		
		switch(uChoice)
		{
			case 1:
			gets(curr_patient->Name);
			break;
			
			case 2:
			scanf("%llu",&curr_patient->ID);
			while((getchar()) != '\n');
			break;
			
			case 3:
			scanf("%s",i_genderN);
			while((getchar()) != '\n');
			if(cmpS(i_genderN,"male"))
				curr_patient->Gender = MALE;
			else if(cmpS(i_genderN,"female"))
				curr_patient->Gender = FEMALE;
			break;
			
			case 4:
			scanf("%u",&curr_patient->Age);
			while((getchar()) != '\n');
			break;
			
			case 5:
			if(deletePatientWID(curr_patient->ID) == P_SUCCESS)
				printf("Patient deleted successfully from the system\n");
			else
				printf("Could not delete the patient from the system\n");
			return;
			
			
		}
	}
	
}


void patientMode()
{
	while(1)
	{
		printf("\n");
		printf("Enter 1 to view patient's records using his ID\n");
		printf("Enter 2 to view all reservations for today\n");
		printf("Enter 3 to exit user mode\n");
		printf("Input:");
		
		u8 pChoice;
		
		scanf("%d",&pChoice);
		while((getchar()) != '\n');
		
		u64 i_ID;
		switch(pChoice)
		{
			case 1:
			i_ID = 0;
			printf("Enter ID of desired patient to view records: ");
			scanf("%llu",&i_ID);
			while((getchar()) != '\n');
			
			patient* curr = checkWID(i_ID);
			if(curr == NULL)
				printf("Patient of such ID doesn't exist in the system\n");
			else
			{
				//get str length for printing format
				u32 str_len = getStrLen(curr->Name);
				printf("\n");
				printf("%-*s|%-*s|%-*s|%-*s\n",str_len+3,"Name",5,"Age",7,"Gender",15,"ID");
				
				printf("%-*s|%-*d|%-*s|%-*llu\n",str_len+3,curr->Name,5,curr->Age,7,Gender(curr->Gender),15,curr->ID);
			}
			break;
			
			case 2:
			printf("\n");
			printAllslots();
			printf("\n");
			break;
			case 3:
			return;
		}
	}
}

