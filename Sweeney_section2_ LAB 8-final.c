//Eighth Program:  Phone Book 3
//Author:  Rick Sweeney  
//March 20, 2015
//Section 2

//This program acts as a phone book and allows the user to add, delete and sort entrie.  The phone book may be saved in a file.

#include <stdio.h>   
#include <stdlib.h>  // free(), system(), rand() , srand()
#include <time.h> //time()
#include <string.h>  //stdcpy()


// STRUCTURE DEFINITION  
typedef struct entry {
     
	 char cFirst[20];
	 char cLast[20];
	 char cPhone[20]; //ALLOWS FOR EXT. XXXX ETC
	 	 
}e;  // end struct with alias e

//  FUNCTION PROTOTYPES 
e* addFriend(e* , int* );
e* deleteFriend(e* , int*);
void displayFriends(e*, int);
void sortFriends(e*, int);
void displayRandom(e*, int);
void searchFriend(e* , int);
e* readFriend( e*, int*);   //
void saveFriend(e*, int);    //
e* deleteAll(e* , int*);

main() {

//declare and initialize variables  
int imenu=0; //variable to hold user's menu selection
int inum_entries=0; // counts number of entries in phone book.  
e* ptrFriend; //points to storage of entries in phone book

srand(time(NULL));

ptrFriend = (e*) malloc(sizeof(e));  
  
if (ptrFriend == NULL)  { 
	    printf("Out of memory.");   
		return 1;
} // end if  that tests if calloc was successful in allocating memory  

printf("\n      Phone Book\n\n");

do {
   printf("\n\n\n");
   printf("(1)  Add Friend\n");
   printf("(2)  Delete Friend\n");
   printf("(3)  Show Phone Book\n");
   printf("(4)  Sort Entries Alphabetically\n");
   printf("(5)  Search Entries by Name\n");
   printf("(6)  Randomly Select an Entry\n");
   printf("(7)  Delete All Entries\n");
   printf("(8)  Save Phone Book\n");   //NEW NEW NEW NEW NEW NEW
   printf("{9)  Open Saved Phone Book\n");   //NEW NEW NEW NEW NEW NEW
   printf("(10)  Exit\n\n");  //NEW NEW NEW NEW NEW NEW

   printf("Please select from the menu above (1-8):  ");
   scanf("%d", &imenu);

   switch(imenu) { 
   	  case 1:  //add entry
		 ptrFriend = addFriend(ptrFriend, &inum_entries);
		 break;
	
	  case 2:  // delete entry
	     printf("\nYou have selected Delete Friend.\n");
	     if (inum_entries == 0) {
	         printf("\nThere are no listings in your phone book at this time.\n\n");
	         break;
	     } //end if
	     else{
	         ptrFriend = deleteFriend(ptrFriend, &inum_entries);	
		 	 break;  
	     } //end else
	     
	  case 3:  // selection to print the phone book-- may assume all names are unique             
		 displayFriends(ptrFriend, inum_entries);
		 break;
	  	
	  case 4:  //sort entries
		 if (inum_entries == 0) {
	        printf("\nThere are no listings in your phone book at this time.\n\n");
	        
	     } //end if
	     else{
	         sortFriends(ptrFriend, inum_entries);
             displayFriends(ptrFriend, inum_entries);
	     } //end else
		 break;
		 
      case 5:  // Search by Name
         printf("\nYou have selected Search for Friend.\n");
	     if (inum_entries == 0) {
	         printf("\nThere are no listings in your phone book at this time.\n\n");
	     } //end if
	     else{
	         searchFriend(ptrFriend, inum_entries);	  
	     } //end else
      	 break;
      case 6:  // Randomly select an Entry
         displayRandom(ptrFriend, inum_entries);
         break;
      
      case 7:  // Delete All Entries
	     if (inum_entries == 0) {
	        printf("\nThere are no listings in your phone book at this time.\n\n");
	        break;
	     } //end if
	     else{
	        ptrFriend = deleteAll(ptrFriend, &inum_entries);	
			break;  
	     } //end else
	  
	  case 8:  // Save Phone Book    ///NEW NEW NEW NEW NEW NEW
	     if (inum_entries == 0) {
	        printf("\nThere are no listings in your phone book at this time.\n\n");
	        break;
	     } //end if
	     else {
	        saveFriend(ptrFriend, inum_entries); 
			break;  
	     } //end else

	  case 9:  // Open Phone Book    
	     ptrFriend = readFriend(ptrFriend, &inum_entries); // trying it here without pbkName
         break;
         
	  case 10:   
	     printf("\n\nExiting Phone Book\n\n");
	     break;
	 
	  default:  // if user entered wrong integers instead of menu #
			 printf("\n\n\nInvalid selection\n\n\n");
			 		 
   }//end of switch
} while (imenu!=10); //end do while loop
					
system("pause");
system("cls");

free(ptrFriend); 
return 1;

} // end of main
 
e* addFriend(e* ptrNew, int* inum_entries){

	e* tmp = (e*) realloc(ptrNew, (((*inum_entries)+1) * sizeof(e)));
	
	if (tmp == NULL)  {  //p240 EXAMPLE 
	     printf("\nMemory not available.\n");
	     return(ptrNew);
    } //end if testing realloc for success or failure
       
	else {
		ptrNew = tmp;
	    printf("\nYou selected Add Friend.  \n\n");
   	    printf("Enter the first name:  ");
   	    scanf("%s", ptrNew[(*inum_entries)].cFirst);
   	    printf("\nEnter the last name:  ");
   	    scanf("%s", ptrNew[(*inum_entries)].cLast);
	    printf("\nEnter the phone number (no spaces):  ");
	    scanf("%s", ptrNew[(*inum_entries)].cPhone);
	    printf("\n\nRecord added to the phone book."); 

		(*inum_entries) = (*inum_entries) + 1;	
		return(ptrNew);
		free(ptrNew);  //necessary?
	}//end of else
}//end of add(

e* deleteFriend(e* ptrNew, int* inum_entries){
	
	char aDelFirst[21] = {'\0'}; //p 183 example  // size 21 array to accept more than one character (up to 20) 
	char aDelLast[21] = {'\0'}; 
	 
	printf("\nEnter the first name of the entry you wish to delete:  ");   
    scanf("%s", aDelFirst);  //p183 example
    printf("\nEnter the last name of the entry you wish to delete:  ");   
    scanf("%s", aDelLast);  //p183 example

	int i;
	
		 for (i=0; i < (*inum_entries); i++ ) {  //p101 for loop example
			   if ((strcmp(ptrNew[i].cFirst, aDelFirst) == 0) && (strcmp(ptrNew[i].cLast, aDelLast) == 0)) {  //p195, 222 examples
			     
		 	     while (i < (*inum_entries ))  {  //shifts values in array to smaller size  
					 ptrNew[i] = ptrNew[i+1];
					 i++;
				 }// end while
				 
	             (*inum_entries) = (*inum_entries) - 1;  //new number of entries 
	             
	             e* tmp = (e*) realloc( ptrNew ,((*inum_entries) * sizeof(e))); // initializes tmp pointer
	             ptrNew = tmp; 
	             printf("\n%s %s has been deleted.\n\n", aDelFirst, aDelLast);
	             return(ptrNew);
				 break;  //p 102 use of break with for loop      
	         } // end if      
	     } // end for  
		 
		 if (i = (*inum_entries)) { 
				  printf("\n\nNo entry with the name of \"%s %s\" was found.\n\n", aDelFirst, aDelLast);
				  return(ptrNew);    
		 } // end IF    	 
}//end of deleteFriend function


e* deleteAll(e* ptrNew, int* inum_entries) // delete all entries
{
	*inum_entries = 0;  //new number of entries 
	free(ptrNew);
	
	ptrNew = (e*) malloc(sizeof(e));
        
	printf("\nAll phonebook entries have been deleted.\n\n");
	return(ptrNew);
}

void searchFriend(e* ptrNew, int inum_entries){
	
	char aFindFirst[21] = {'\0'};  //p 183 example  //size 21 array to accept more than one character (up to 20) 
	char aFindLast[21] = {'\0'}; 
	 
	printf("\nEnter the first name of the entry you wish to find:  ");   
    scanf("%s", aFindFirst);     //p183 example
    printf("\nEnter the last name of the entry you wish to find:  ");   
    scanf("%s", aFindLast);      //p183 example

	int i;
	
	unsigned int found = 0;
	for (i=0; i < (inum_entries); i++ ) {  //p101 for loop example
	   if ((strcmp(ptrNew[i].cFirst, aFindFirst) == 0) && (strcmp(ptrNew[i].cLast, aFindLast) == 0)) {  //p195, 222 examples		     
		    printf("\n%s %s %s\n", (ptrNew[i]).cFirst, (ptrNew[i]).cLast, (ptrNew[i]).cPhone);
		    found = 1;
			break;
       } // end if	
	} // end for  
	     
    if(found == 0) { 
	    printf("\n\nNo entry with the name of \"%s %s\" was found.\n\n", aFindFirst, aFindLast);  
	} // end else
		 
}//end of searchFriend function

void sortFriends(e* ptrNew, int inum_entries)  
{
	char tmp[21] = {'\0'}; //p 183 example  // size 21 array to accept more than one character (up to 20) 
	int i;
	int count;
	
	do {
	   count=0;
	   for (i=0; ((inum_entries > 1) && (i < ( inum_entries - 1))); i++) {

	    	if (strcmp(ptrNew[i].cLast, ptrNew[i+1].cLast) > 0)
	    	{ 
			   strcpy(tmp, ptrNew[i].cLast);
		       strcpy(ptrNew[i].cLast, ptrNew[i+1].cLast);
		       strcpy(ptrNew[i+1].cLast, tmp);
		       strcpy(tmp, ptrNew[i].cFirst);
		       strcpy(ptrNew[i].cFirst, ptrNew[i+1].cFirst);
		       strcpy(ptrNew[i+1].cFirst, tmp);
		       strcpy(tmp, ptrNew[i].cPhone);
		       strcpy(ptrNew[i].cPhone, ptrNew[i+1].cPhone);
		       strcpy(ptrNew[i+1].cPhone, tmp);
		       count=1;
		    } //end if
		    else if (strcmp(ptrNew[i].cLast, ptrNew[i+1].cLast) == 0){
		       if (strcmp(ptrNew[i].cFirst, ptrNew[i+1].cFirst) > 0) {
			       strcpy(tmp, ptrNew[i].cLast);
		           strcpy(ptrNew[i].cLast, ptrNew[i+1].cLast);
		           strcpy(ptrNew[i+1].cLast, tmp);
		           strcpy(tmp, ptrNew[i].cFirst);
		           strcpy(ptrNew[i].cFirst, ptrNew[i+1].cFirst);
		           strcpy(ptrNew[i+1].cFirst, tmp);
		           strcpy(tmp, ptrNew[i].cPhone);
		           strcpy(ptrNew[i].cPhone, ptrNew[i+1].cPhone);
		           strcpy(ptrNew[i+1].cPhone, tmp);
		           count=1;
		       } //end if
		    } //end else if
		//i++;     
       } //end for
    } while (count == 1);  // end do while loop
    
} // end sort function

void displayRandom(e* ptrNew, int inum_entries)  // display a random entry
{
	int i;
	if(inum_entries > 0){
	    int indexR = rand()%inum_entries;
    	printf("\n%s %s %s\n", (ptrNew[indexR]).cFirst, (ptrNew[indexR]).cLast, (ptrNew[indexR]).cPhone);
	} //end if
	else   
	   printf("\nThere are currently no listings in the Phone Book.\n\n");
}

void displayFriends(e* ptrNew, int inum_entries)
{
	int i;
	if(inum_entries > 0){
		printf("\n\nPhone Book Entries:\n\n"); 
		for(i=0; i<inum_entries; i++){
			printf("%d:  %s %s %s\n", (i+1), (ptrNew[i]).cFirst, (ptrNew[i]).cLast, (ptrNew[i]).cPhone);  
		} //end of for
	} //end if
	else   
	   printf("\nThere are currently no listings in the Phone Book.\n\n");
} // end displayFriends function

e* readFriend(e* ptrNew, int* inum_entries){  
    
	char pbkName[60] = {0};  // user's phone book file name  
                                        
	printf("\nPlease enter the name of the file you wish to open:  ");
	scanf("%s", pbkName);
	
	FILE *pRead;     
	pRead = fopen(pbkName, "r");  
    if (pRead == NULL ) {
    
        printf("\n File cannot be opened.\n");
        return(ptrNew);
    } //end if  
	else  {
        free(ptrNew);  //free up any previously held data so ptrNew can take the new pbkName (pRead) data.
    	ptrNew = calloc(1,sizeof(e));  // allocates a minimum amount of space for one entry to ptrNew
        *inum_entries = 0;  // ensure count is back at zero  

		while (!feof(pRead)) { //while loop to use realloc to expand 
           ptrNew = (e*) realloc(ptrNew, (((*inum_entries)+1) * sizeof(e)));
           fscanf(pRead, "%s %s %s\n",(ptrNew[(*inum_entries)]).cFirst, (ptrNew[(*inum_entries)]).cLast, (ptrNew[(*inum_entries)]).cPhone);
	       ( *inum_entries) = ( *inum_entries ) + 1;
        }//end while
                   
		fclose(pRead);
		return(ptrNew);
    } //end else
 } // end readFriends function      
 
 void saveFriend(e* ptrNew, int inum_entries){    
 
 	char pbkName[60] = {0};  // user's phone book file name  

	printf("\nPlease enter the name of the file to which the phone book will be saved:  ");
	scanf("%s", pbkName);
 
 	FILE *pWrite;  
 	pWrite = fopen(pbkName, "w");   // "w" mode will create the file if it doesnt already exist per 4th slide of Lab presentation
    
	if (pWrite == NULL)
        printf("File can not be opened for saving phone book\n");
        
 	else {
 	    int i;
 	    for(i=0; i<inum_entries; i++){
 		   fprintf(pWrite, "%s %s %s\n", ptrNew[i].cFirst, ptrNew[i].cLast, ptrNew[i].cPhone);
 	    } // end for
 	} //end else
 	
 	fclose(pWrite);
 	
} // end saveFriends function 

