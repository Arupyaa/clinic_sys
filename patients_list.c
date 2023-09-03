#include "patients_list.h"


patient* Head = NULL;
patient* Tail = NULL;

patient* createPatient(u64 ID,u8* Name, Gend Gender, u32 Age)
{
	//create a new patient obj, fill his elements and return a pointer to it
	patient* newPatient = (patient*)malloc(sizeof(patient));
	newPatient->ID = ID;
	newPatient->Name = Name;
	newPatient->Gender = Gender;
	newPatient->Age = Age;
	newPatient->next = NULL;
	
	return newPatient;
}


PStatus insertPatientTop(u64 ID,u8* Name, Gend Gender, u32 Age)
{

	//check if the ID of the new patient already exists, if it does don't add him and return a failed status message
	if(checkWID(ID)!=NULL)
		return P_FAILED;
	
	//if the new patient ID doesn't exist in the list add the patient to the list
	patient* p_new = createPatient(ID,Name,Gender,Age);
	
	//check if the list is empty
	if(Head == NULL)
	{
		Head = p_new;
		Tail = p_new;
		return P_SUCCESS;
	}
	else //add patient to the start of the list
	{
		p_new->next = Head;
		Head = p_new;
		return P_SUCCESS;
	}
	
}


PStatus insertPatientBottom(u64 ID,u8* Name, Gend Gender, u32 Age)
{
	//check if the ID of the new patient already exists, if it does don't add him and return a failed status message
	if(checkWID(ID)!=NULL)
		return P_FAILED;
	
	//if the new patient ID doesn't exist in the list add the patient to the list
	patient* p_new = createPatient(ID,Name,Gender,Age);
	
	//check if the list is empty
	if(Head == NULL)
	{
		Head = p_new;
		Tail = p_new;
		return P_SUCCESS;
	}
	else //add patient to the end of the list
	{
		Tail->next = p_new;
		Tail = p_new;
		return P_SUCCESS;
	}
}

PStatus deletePatientTop()
{
	//check if the list is empty
	if(Head ==NULL)
		return P_FAILED;
	
	//check if there's only one element in the list
	if(Tail == Head)
	{
		free(Head->Name);
		free(Head);
		Head = NULL;
		Tail = NULL;
		return P_SUCCESS;
	}
	
	
	//delete a patient from the top of the list
	patient* temp = Head;
	Head = temp->next;
	free(temp->Name);
	free(temp);
	return P_SUCCESS;
}


PStatus deletePatientBottom()
{
	//check if the list is empty
	if(Head ==NULL)
		return P_FAILED;
	
	//check if there's only one element in the list
	if(Tail == Head)
	{
		free(Head->Name);
		free(Head);
		Head = NULL;
		Tail = NULL;
		return P_SUCCESS;
	}
	
	//find the address of the obj located before the tail of the list
	patient* temp = findPrevious(Tail->ID);
	free(Tail->Name);
	free(Tail);
	Tail = temp;
	Tail->next = NULL;
	return P_SUCCESS;
}


PStatus deletePatientWID(u64 ID)
{
	//check if patient of the ID is at the top or bottom of the list
	if(Head->ID == ID)
	{
		deletePatientTop();
		return P_SUCCESS;
	}
	else if(Tail->ID == ID)
	{
		deletePatientBottom();
		return P_SUCCESS;
	}
	else
	{
		//find a pointer to the obj before and after the obj of the given ID
		patient* p_prev = findPrevious(ID);
		if(p_prev == NULL) //the ID doesn't exist in the list
			return P_FAILED;
		
		patient* p_curr = p_prev->next;
		patient* p_next = p_curr->next;
		
		//delete patient of given ID and link the obj before and after it together
		free(p_curr->Name);
		free(p_curr);
		p_prev->next = p_next;
		return P_SUCCESS;
	}
}


patient* checkWID(u64 ID)
{
	patient* p_curr = Head;
	while(p_curr!=NULL)
	{
		if(p_curr->ID == ID)
			return p_curr;
		else
			p_curr = p_curr->next;
	}
	//if the loop reaches the end list then the ID wasn't found and p_curr contains a NULL
	return p_curr;
}


patient* findPrevious(u64 ID)
{
	patient* curr = Head;
	
	//if ID of head is equal to the given ID then the obj is at the top of the list and no element is before it
	if(curr->ID == ID)
		return NULL;
	
	while(curr->next!=NULL)
	{
		if(curr->next->ID == ID)
			return curr;
		
		curr = curr->next;
	}
	//if you reach the end of the loop then the ID doesn't exist
	return NULL;
}

void printAllPatients()
{
	printf("Name\tAge\tGender\tID");
	patient* curr = Head;
	while(curr!=NULL)
	{
		
		printf("\n%s\t%d\t%s\t%llu",curr->Name,curr->Age,Gender(curr->Gender),curr->ID);
		curr = curr->next;
	}
	printf("\n");
}


void clearList()
{
	while(Head!=NULL)
		deletePatientTop();
	//printf("List cleared successfully\n");
}