#define SepChain    /* Define the appropriate hash algorithm */

#ifdef SepChain
    #include "hashsep.h"
   
#endif

#ifdef QuadProb
    #include "hashquad.h"
#endif


#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include<math.h> 
#define NumItems 400
#include<time.h>
char str[120];
FILE *fptr;
int main(){
	int length,id,graph,x,y,z,source,destination,choice,choice2,choice_e,ID;
	char city[4], name[20],type[2],Stype[2];
	float time,charges;
	HashTable H;
	List1 H1;
	if ( ( fptr = fopen("data.txt","r")) == NULL )    
    printf("error opening file");
    while(1){		//keeps on reading the file 
    	if(strstr(str,"$Graph")){
    	fgets (str, 120, fptr);		//reads the file line by line
    	graph=atoi(str);		//converts the number of nodes in graph from string to integer
    	H1=InitializeGraph(graph);	//initializes the adjacency list for keeping nodes record
		}
       	fgets (str, 120, fptr);
 		if(strstr(str,"$Records")){
 		fgets (str, 120, fptr);
 		length=atoi(str);		//converts the number of employees in record from string to integer
 		H=InitializeTable(length);	//initializes hashtable for keeping employee record
 		break;
	 }
	}
	fclose(fptr);		//close the text file 
	CreateRecord(H);	//creates the employee record in hashtable by separate chaining
	CreateGraph(H1);	//creates the adjacency list ie the record of neighboring cities of each city		
	Position P;
	while(1){		//for any wrong input choice keep on asking for the choice
		printf("**********Welcome to the login portal**********\n");
		printf("Enter 1-Customer login 2-Employee login and -1 to signout \n");	
		choice=NumericInput();		//takes input again if a string is entered and avoids infinite loop
		if (choice==-1){
			printf("Signed Out\n");			// only in case of -1 signout
			break;
		}
		if (choice==1){
		float checkdistance;	
		printf("Signed in as a customer\n");
		while(1){		//for any wrong city and service type input keep on asking for the customer choice
		printf("Select your City:\n1-Peshawar\n2-Islambad\n3-Sialkot\n4-Lahore\n5-Multan\n6-University of engineering and technology\n7-Karachi\n");
		source=NumericInput();
		if(source==1 || source==2 || source==3 || source==4 || source==5 || source==6 || source==7)		//proceed only if current city is in record
		{
		printf("Select the City where you want to deliver:\n1-Peshawar\n2-Islambad\n3-Sialkot\n4-Lahore\n5-Multan\n6-University of engineering and technology\n7-Karachi\n");
		destination=NumericInput();
		if((destination==1 || destination==2 || destination==3 || destination==4 || destination==5 || destination==6 || destination==7) && destination!=source){	//proceed only if destination city is in record
		printf("Enter Service type:\t->E for Express\t->P for Priority\t->S for Standard ");		
		scanf("%s",Stype);
		if(strcmp(Stype,"E")==0||strcmp(Stype,"P")==0||strcmp(Stype,"S")==0){		//proceed only if the service type is in record
		checkdistance=ShortestPath(source,destination,graph,H1);	//finds the shortest distance in km between two cities 
		printf("Shortest distance=%f km\n",checkdistance);
		break;
		}
		else 
		printf("Try Again\n");
		}
		else 
		printf("Try Again\n");
		}
		else 
		printf("Try Again\n");
		}
		cost(checkdistance,Stype);		//finds the cost and number of days required for delivery based on distance and service type
		FindEmployee(source,Stype,H);	//searches the employee based on current city and the service type in the current record
		}
		if (choice==2){
		printf("Signed in as an employee\n");
		while(1){		//for any wrong input choice keep on asking for the choice
		printf("Enter 1-Retrieve data  2-Update data  3-New Employee ");
		choice_e=NumericInput();
		if(choice_e==1){
			while(1){
			printf("Enter your ID\n");
			choice2=NumericInput();
			x=RetrieveData(choice2,H);		//displays the complete record of employee based on the ID
			if(x==1)	//gives breaking condition
			break;
			}
			break;
		}
		if(choice_e==2)
		{	while(1){
			printf("Enter the employee ID: ");
			ID=NumericInput();
			y=UpdateData(ID,H);		//updates the employee name,city or service type
			if(y==1)	//gives breaking condition
			break;
			}
			break;
		}
		if (choice_e==3){
			while(1){
			z=NewEmployee(H);		//adds a new employee to the existing record 
			if(z==1)	//gives breaking condition
			break;
			}
			break;
		}
		}
	}
}
}

