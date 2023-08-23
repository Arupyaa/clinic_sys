#include "user_interface.h"

void mainWindow()
{
	while(1)
	{
		UserModes USER_STATUS = NONE;
	
		printf("Welcome to the clinic\nPlease choose between Admin Mode or User Mode:\n");
		
		u8 modeChoice;
		printf("Enter 1 for Admin Mode\tEnter 2 for User Mode\tEnter 3 to exit the program\n");
		
		
		
		scanf("%u",&modeChoice);
		while((getchar()) != '\n');
		
		while(modeChoice!=1  && modeChoice!=2 && modeChoice!=3)
		{
			printf("Incorrect input, please try again\n");
			printf("Enter 1 for Admin Mode\tEnter 2 for User Mode\tEnter 3 to exit the program\n");
			
			scanf("%u",&modeChoice);
			while((getchar()) != '\n');
			
		}
		
		//terminate program if user entered 3
		if(modeChoice == 3)
			return;
		
		//returning 1 means the admin login has failed and the system should shutdown
		if(modeSet(modeChoice,&USER_STATUS) == 1)
		{
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
		printf("Please enter your admin password: ");
		
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
		printf("Please enter a number for an operation:\n");
		printf("1:Add new patient record\n");
		printf("2:Edit an existing patient record\n");
		printf("3:Delete an existing patient record\n");
		printf("4:Reserve a new appointment slot with the doctor\n");
		printf("5:Cancel an existing appointment with the doctor\n");
		printf("6:Logout of Admin mode\n");
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
			
			printf("Enter new patient's gender in all small letters: ");
			scanf("%s",i_genderN);
			if(cmpS(i_genderN,"male"))
				i_gender = MALE;
			else if(cmpS(i_genderN,"female"))
				i_gender = FEMALE;
			
			printf("Enter new patient age: ");
			scanf("%u",&i_age);
			
			if(insertPatientTop(i_ID ,i_name ,i_gender ,i_age)== P_FAILED)
			{
				printf("A patient with this ID already exists, could not add the new patient record\n");
			}
			break;
			
			case 2:
			break;
			
			case 3:
			break;
			case 4:
			break;
			case 5:
			break;
			case 6:
			return;
			break;
		}
		
	}
}

void patientMode()
{
	
}