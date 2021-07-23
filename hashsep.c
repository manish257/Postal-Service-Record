       #include "fatal.h"
       #include "hashsep.h"
      
       #include <stdlib.h>
       #include<string.h>
       #include<math.h>
       #define MinTableSize (5)
	   #define MinQueueSize ( 5 )	
        struct ListNode		//this keeps record of an employee	
        {
            ElementType Service_id; 
            char *name;
            char *city;
            char *service_type;
            Position    Next;
        };
        struct GraphNode	//this keeps record for city distances 
        {
        	ElementType Node;
        	ElementType Distance;
			Position1 NextNode;        
		};
        typedef Position List;
		typedef Position1 Graph;
        struct HashTbl		//hashtable for keeping records of all the employees 
        {
            int TableSize;
            List *TheLists;
        };
        struct AdjacencyList		//adjacency list to keep record of a node's neighboring nodes
        {
        	int TableSize;
        	Graph *Adjlist;
		};
		struct info		//to help calculate shortest path
		{
			int Known;
			float dv;
			int pv;
		};
  		 struct QueueRecord		//to push nodes for calculating shortest distance between cities
        {
            int Capacity;
            int Front;
            int Rear;
            int Size;
            ElementType *Array;
        };
        int NumericInput(void){	//this function checks for the input type
        	int input, temp, status;
			status = scanf("%d", &input);	//status will be 1 only when an integer is entered
			while(status!=1){	//for invalid inputs take the input again
				while((temp=getchar()) != EOF && temp != '\n');
					printf("Invalid input... please enter a number: ");
				status = scanf("%d", &input);
			}
			return input;
		}
		 int
        IsEmpty( Queue Q )
        {
            return Q->Size == 0;
        }
        int
        IsFull( Queue Q )
        {
            return Q->Size == Q->Capacity;
        }
        Queue
        CreateQueue( int MaxElements )
        {
            Queue Q;
/* 1*/      if( MaxElements < MinQueueSize )
/* 2*/          Error( "Queue size is too small" );
/* 3*/      Q = malloc( sizeof( struct QueueRecord ) );
/* 4*/      if( Q == NULL )
/* 5*/          FatalError( "Out of space!!!" );
/* 6*/      Q->Array = malloc( sizeof( ElementType ) * MaxElements );
/* 7*/      if( Q->Array == NULL )
/* 8*/          FatalError( "Out of space!!!" );
/* 9*/      Q->Capacity = MaxElements;
/*10*/      MakeEmpty( Q );

/*11*/      return Q;
        }
        void
        MakeEmpty( Queue Q )
        {
            Q->Size = 0;
            Q->Front = 1;
            Q->Rear = 0;
        }
        void
        DisposeQueue( Queue Q )
        {
            if( Q != NULL )
            {
                free( Q->Array );
                free( Q );
            }
        }
        static int
        Succ( int Value, Queue Q )
        {
            if( ++Value == Q->Capacity )
                Value = 0;
            return Value;
        }
        void
        Enqueue( ElementType X, Queue Q )
        {
            if( IsFull( Q ) )
                Error( "Full queue" );
            else
            {
                Q->Size++;
                Q->Rear = Succ( Q->Rear, Q );
                Q->Array[ Q->Rear ] = X;
            }
        }
        ElementType
        Front( Queue Q )
        {
            if( !IsEmpty( Q ) )
                return Q->Array[ Q->Front ];
            Error( "Empty queue" );
            return 0;  
        }
        void
        Dequeue( Queue Q )
        {
            if( IsEmpty( Q ) )
                Error( "Empty queue" );
            else
            {
                Q->Size--;
                Q->Front = Succ( Q->Front, Q );
            }
        }
        ElementType
        FrontAndDequeue( Queue Q )
        {
            ElementType X = 0;

            if( IsEmpty( Q ) )
                Error( "Empty queue" );
            else
            {
                Q->Size--;
                X = Q->Array[ Q->Front ];
                Q->Front = Succ( Q->Front, Q );
            }
            return X;
        }
         int
        NextPrime( int N )
        {
            int i;

            if( N % 2 == 0 )
                N++;
            for( ; ; N += 2 )
            {
                for( i = 3; i * i <= N; i += 2 )
                    if( N % i == 0 )
                        goto ContOuter; 
                return N;
              ContOuter: ;
            }
        }
        Index
        Hash( ElementType Key, int TableSize )
        {
            return Key % TableSize;
        }
        HashTable
        InitializeTable( int TableSize )
        {
            HashTable H;
            int i;
/* 1*/      if( TableSize < MinTableSize )
            {
/* 2*/          Error( "Table size too small" );
/* 3*/          return NULL;
            }
/* 4*/      H = malloc( sizeof( struct HashTbl ) );
/* 5*/      if( H == NULL )
/* 6*/      FatalError( "Out of space!!!" );
/* 7*/      H->TableSize = NextPrime( TableSize );
/* 8*/      H->TheLists = malloc( sizeof( List ) * H->TableSize );
/* 9*/      if( H->TheLists == NULL )
/*10*/          FatalError( "Out of space!!!" );
/*11*/      for( i = 0; i < H->TableSize; i++ )
            {
/*12*/          H->TheLists[ i ] = malloc( sizeof( struct ListNode ) );
/*13*/          if( H->TheLists[ i ] == NULL )
/*14*/              FatalError( "Out of space!!!" );
                else
/*15*/              H->TheLists[ i ]->Next = NULL;
            }
/*16*/      return H;
        }
 List1 InitializeGraph( int TableSize )		//initializes the adjacency list
        {
            List1 H;
            int i;
      if( TableSize < MinTableSize )
            {
        Error( "Table size too small" );
         return NULL;
            }
      H = malloc( sizeof( struct AdjacencyList ) );
     	if( H == NULL )
         FatalError( "Out of space!!!" );

    H->TableSize = TableSize+1;		//size of array is number of nodes +1 so that array index corresponds to city number
      H->Adjlist = malloc( sizeof( Graph) * H->TableSize );	//creates an array for all cities 
     if( H->Adjlist == NULL )
        FatalError( "Out of space!!!" );

      for( i = 0; i < H->TableSize; i++ )
            {
         H->Adjlist[ i ] = malloc( sizeof( struct GraphNode ) );
          if( H->Adjlist[ i ] == NULL )	
            FatalError( "Out of space!!!" );
          else
            H->Adjlist[i]->NextNode=NULL;	//initilize it by making all pointers null
            }
      return H;
        }
        Position
        Find( ElementType Key, HashTable H )
        {
            Position P;
            List L;
			int collision=0;
/* 1*/      L = H->TheLists[ Hash( Key, H->TableSize ) ];
/* 2*/      P = L->Next;
			while( P != NULL && P->Service_id != Key ){
              P = P->Next;                  
              collision++;
        }
/* 5*/      return P;
        }
void InsertGraph (int index,int node,int distance,List1 H){		//function to insert neighboring cities in adjacency list
	Graph G,NewCell;
	NewCell = malloc( sizeof( struct GraphNode ) );		//reserving space to store the city number and its distance 
	if( NewCell == NULL )		//to check if space reserved or not
		FatalError( "Out of space!!!" );
    else{
    G = H->Adjlist[index];	//assigning pointer value stored in the array corresponding to that city because array index is city number
    NewCell->NextNode = G->NextNode;	//assigning next pointer of header to next pointer of current node
	NewCell->Node=node;		//storing the city number
	NewCell->Distance=distance;		//storing the city distance
	G->NextNode=NewCell;		//assigning current node position to the headers next
		
	}
}
void Insert( ElementType Key,char *Name,char *City,char *Service_type , HashTable H )	// function to insert employee data in hashtable 
{
    Position Pos, NewCell;
    List L;
    Pos = Find( Key, H );		//returns the position of header in hashtable using hash function and each employee info is inserted after the header
	if( Pos == NULL ) 		//to check if ID is not already present
    {
        NewCell = malloc( sizeof( struct ListNode ) );		//reserving space for complete employee data
		if( NewCell == NULL )		//to check if space is reserved
		    FatalError( "Out of space!!!" );
        else
        {	NewCell->name=malloc(sizeof(char)*strlen(Name));		//resrerving space for employee name 
            NewCell->city=malloc(sizeof(char)*strlen(City));		//reserving space for employee city
            NewCell->service_type=malloc(sizeof(char)*strlen(Service_type));		//reserving space for employee service type 
     //       printf("string1=%d",strlen(Service_type));
       //     printf("string2=%d",strlen(NewCell->service_type));
		    L = H->TheLists[ Hash( Key, H->TableSize ) ];		//assigning pointer value stored in the array corresponding to that ID using hash function
            NewCell->Next = L->Next;		//assigning next pointer of header to next pointer of current node
            NewCell->Service_id = Key;		//storing employee ID
			strcpy(NewCell->name,Name);		//storing employee name
			strcpy(NewCell->city,City);		//storing employee city
			strncpy(NewCell->service_type,Service_type,2);		//storing employee service type
		    L->Next = NewCell;		//assigning current node position to the headers next
        }
    }
}
        ElementType
        Retrieve( Position P )
        {
            return P->Service_id;
        }
void CreateRecord(HashTable H){		//function to create employee record by storing it in hashtable	O(N)
 		char str[120];
		FILE *fptr;
		char name[50],city[4],type[2];
		int length,id,p=0;
 		if ( ( fptr = fopen("data.txt","r")) == NULL ) 
    		printf("error opening file");
    	while(1){
   			if(p==0){		//to skip the graph portion in the text file 
	   			fgets (str, 120, fptr);		//reads one line from the file and stores in str
 				if(strstr(str,"$Records")){		//to check if records of employee started
 					fgets (str, 120, fptr);		//skip $Records
 					fgets (str, 120, fptr);		//skip number of employees 
 					p=1;
				}
			}
 			if(p==1){	//start saving data once employees information start
 				char *token=strtok(str,"	");		//tokenize words in a line on basis of tab 
 				id=atoi(token);   		//convert employee ID from string to integer
        		token = strtok(NULL,"	");		//separate the next word to get employee name 
        		strcpy(name,token);			// copying employee name in another variable
        		token = strtok(NULL,"	");		//separate next word to get employee city
        		strcpy(city,token);		//copy employee city in another variable
        		token = strtok(NULL,"	");		//separate next word to get employee service type
        		strcpy(type,token);		//copy employee service type in another variable
   				Insert(id,name,city,type,H);	//Insert it in Hashtable
        		fgets (str, 120, fptr);		//move to next employee information
    		}
    		if(strstr(str,"$end"))	//if end of file reached stop savving data
				break;
 		}
}
int RetrieveData(ElementType Key,HashTable H){	//O(N)
	Position P;
	int a=1; 		//to keep track of correct ID
	P= Find( Key, H );	//search for the possible position of the ID
	if(P==NULL){		//to check if any employee registered under the particular ID 
	printf("No such ID\nTry Again\n");
	a=0;	//to get a new ID input 
	}
	else{
		printf("Employee ID: %d\n",P->Service_id);		//display the ID
		printf("Name: %s\n",P->name);		//display name of that employee		
		printf("City: %s\n",P->city);		//display city of that employee
		printf("Service Type: %s\n",P->service_type);	//display service type of that employee
	}
	return a;	//this determines if incorrect ID is entered then get new input and call function until coreect ID is entered	
}
int NewEmployee(HashTable H){		//function to add a new employee to existing records O(N) 
	int id,check=0,a=1;
	Position P;
	char name[20],city[4],type[2],city1[4];
	char temp;	
	printf("Enter Service ID :");		//take Id input
	id=NumericInput();
//	printf("id=%d",id);
	puts("");
	P=Find(id,H);		//search for position of Id in hash table 
	if(P!=NULL ){	//to check if an employee is already registered under that Id
		printf("ID already registered\nTry Again\n");
		check=1;	//to keep record of wrong inputs
		a= 0;		//to not to take next attribute input in case of wrong id
	}
	if(a!=0){
		printf("Enter Name no more than 20 characters : ");
		scanf("%c",&temp);
		fgets(name,20,stdin);		//take input of employee name
		puts("");
		if(strlen(name)>20 ){		//to check if an appropriate name is entered
			printf("Name must not be more than 20 characters\nTry Again\n");
			check=1;		//to keep record of wrong inputs
			a= 0;		//to not to take next attribute input in case of wrong name
		}
	}	
	if(a!=0){
		printf("Select your City:\n->ISB for Islambad\n->SKT for Sialkot\n->LHR for Lahore\n->PEW for Peshawar\n->KHI for Karachi\n->UET for University of engineering and technology\n->MUX for Multan");
		scanf("%s",city);		//take input of employee city
		puts("");		//to check if our services available in that city
		if(!( strcmp(city,"ISB")==0||strcmp(city,"PEW")==0||strcmp(city,"SKT")==0||strcmp(city,"KHI")==0||strcmp(city,"UET")==0||strcmp(city,"LHR")==0||strcmp(city,"MUX")==0)&&a!=0){
			("Postal service not available in this city\nTry Again\n");
			check=1;	//to keep record of wrong inputs
			a=0;		//to not to take next attribute input in case of wrong city
		}
	}
	if(a!=0){
		printf("Enter Service type:\t->E for Express\t->P for Priority\t->S for Standard ");
		scanf("%s",type);		//take input of employee service type
		puts("");
		if(!(strcmp(type,"E")==0||strcmp(type,"P")==0||strcmp(type,"S")==0)&&a!=0){		//to check if any such service is offered
			printf("No such service\nTryAgain\n");
			check=1;		//to keep record of wrong inputs
			a=0 ;		//to not to take next attribute input in case of wrong type
		}
	}
	if(check==0){	//insert new employee information only if all four attributes are entered correct
		Insert(id,name,city,type,H);		//add the information in existing records
		RetrieveData(id,H);
		a=1;
	}
	return a;		//this determines if any incorrect attribute is entered then get new input and call function until coreect information is entered	
}
int UpdateData(int id,HashTable H){	//O(N)
	Position P;
	int choice,a=1;
	char name[20],type[2],city[4];
	char temp;
	P=Find(id,H);			//search for position of Id in hash table 
	if(P==NULL){	//to check if an employee is registered under that Id
		printf("No employee registered under this ID\nTry Again\n");
		a=0;	//to keep record of wrong input
	}
	else{
		printf("Enter attribute to be updated 1-Name 2-City 3-Service Type ");
		choice=NumericInput();	//take the choice of attribute to be updated
		if(choice==1){
		printf("Enter Name ");
		scanf("%c",&temp);
		fgets(name,20,stdin);		//take input of employee name
			if(strlen(name)<20){	//to check if the name is valid
				printf("Employee data before update \n");  //display complete employee information before updating
				RetrieveData(id,H);
				strcpy(P->name,name);		//update name on that position in hashtable to the input name
				printf("Employee data after update \n");  //display complete employee information after updating
				RetrieveData(id,H);
			}
			else{
				printf("Not a valid name\nTry Again\n");
				a=0;		//to keep track of wrong inputs
			}
		}
		if(choice==2){
			printf("Select your City:\n->ISB for Islambad\n->SKT for Sialkot\n->LHR for Lahore\n->PEW for Peshawar\n->KHI for Karachi\n->UET for University of engineering and technology\n->MUX for Multan");
			scanf("%s",&city);		//take city of employee input
			if( strcmp(city,"ISB")==0||strcmp(city,"PEW")==0||strcmp(city,"SKT")==0||strcmp(city,"KHI")==0||strcmp(city,"UET")==0||strcmp(city,"LHR")==0||strcmp(city,"MUX")==0){ 	//to check if our services available in that city
				printf("Employee data before update \n");  //display complete employee information before updating
				RetrieveData(id,H);
				strcpy(P->city,city);	//update city on that position in hashtable to the input city
				printf("Employee data after update \n");  //display complete employee information after updating
				RetrieveData(id,H);
			}
			else{
			printf("Not a valid city\nTry Again\n");
			a=0;		//to keep track of wrong inputs
			}
		}
		if(choice==3){
			printf("Enter Service type:\t->E for Express\t->P for Priority\t->S for Standard ");
			scanf("%s",&type);		//take epmloyee service type input
			if(strcmp(type,"E")==0||strcmp(type,"P")==0||strcmp(type,"S")==0){	//to check if any such service is offered
				printf("Employee data before update \n");  //display complete employee information before updating
				RetrieveData(id,H);
				strncpy(P->service_type,type,2);	//update city on that position in hashtable to the input city
				printf("Employee data after update \n");  //display complete employee information after updating
				RetrieveData(id,H);
			}
			else{
			printf("Not a valid service type\n");
			a=0;	//to keep track of wrong inputs
			}
		}
		if(choice!=1 && choice!=2 && choice!=3){
		printf("No such attribute exists.\n Try again\n");	
		a=0;
		}
	}
		return a;	//this determines if any incorrect attribute is entered then get new input and call function until correct information is entered	
}
void CreateGraph(List1 H){	//function to make adjacency list to keep track of the neighboring cities of each city
		char str[120];
		FILE *fptr;
		int index,node,distance,total_nodes,i;
		if ( ( fptr = fopen("data.txt","r")) == NULL )   //read the text file 
    	printf("error opening file");
    	fgets (str, 120, fptr);
    	fgets (str, 120, fptr);		//skip $graph
    	total_nodes=atoi(str);	//convert total number of nodes from string to integer
    	fgets (str, 120, fptr);	
    	while(!(strstr(str,"$Records"))){	//save information of only the graph portion
    		char *token=strtok(str," ");	//tokenize every word in a line on basis of single space
    		index=atoi(token);	//convert the city number from string to integer
    		for(i=0;i<total_nodes;i++){		//iterate through all possible neighboring cities 
    		token = strtok(NULL," ");		//separate next word to get neighboring city
    		node=atoi(token);	//convert neighboring neighboring city from string to integer
    		if(node==0)	//to check if there are more neighboring cities
    		break;
			token = strtok(NULL," ");	//separate next word to get the distance of neighboring city from current city  
			distance=atoi(token);	//convert distance from string to integer
			InsertGraph(index,node,distance,H);	//insert it in the adjacency list 
			}
    		fgets (str, 120, fptr);	 	 //move to next line	
		}	
}
float ShortestPath (int source,int destination,int nodes ,List1 H ){	//function to find shortest distance between two cities
	int i,y,x,z,a;
	Queue Q ;
	Position1 P;
	Q=CreateQueue(nodes*(nodes-1));		//create a queue
	struct info v[nodes+1];		//an array of structure to keep track of distance corresponding to a city
	for (i=1;i<=nodes;i++){		
		v[i].dv=INFINITY;	//initialize all city distances to infinity
		v[i].Known=0;	//initialize all cities to unknown 
		v[i].pv=0;		//initialize all city preceding cities to 0
	}
	v[source].dv=0;	//keep current city distance to 0
	Enqueue(source,Q);	//insert city in the queue
	while(!IsEmpty(Q)){	//check complete adjacenecy list
		y=FrontAndDequeue(Q);//retrieve and remove city from queue
		P=H->Adjlist[y];
		while(P->NextNode!=NULL){		//keep checking the adjacency list of that city
			x=P->NextNode->Node;
			z=P->NextNode->Distance;
			if((v[y].dv+z<v[x].dv) ){	//update the distance and predecessor only if distance is less
				v[x].dv=v[y].dv+z;	//update city distance
				v[x].pv=y;	//update city predecessor
				Enqueue(x,Q);	//insert city in queue
			} 
			P=P->NextNode;	//move to next neighboring city
		}
		v[y].Known=1;	//update the city to known once all its neighbor has been processed 
	}
	return v[destination].dv;
}
void FindEmployee(int source,char *type,HashTable H){
	int i,p=0;
	char city[4];
	Position P;
	switch(source){		//select the city name based on its number
		case 1:
			strcpy(city,"PEW");
			break;
		case 2:
			strcpy(city,"ISB");
			break;	
		case 3:
			strcpy(city,"SKT");
			break;	
		case 4:
			strcpy(city,"LHR");
			break;
		case 5:
			strcpy(city,"MUX");
			break;
		case 6:
			strcpy(city,"UET");
			break;
		case 7:
			strcpy(city,"KHI");
			break;
	}
	for(i=0;i<H->TableSize;i++){	//search the complete hashtable
		P=H->TheLists[i]->Next;
		while(P!=NULL){	//search each link list
			if((strcmp(P->city,city)==0) && (strcmp(P->service_type,type)==0)){	//search employee whose both city and service type are same
				printf("Employee for your delivery is %s\n",P->name);	//display employee name
				printf("Employee ID is %d\n",P->Service_id); //display employee id
				p=1;	//gives breaking condition for the search
				break; //breaks search in that link list once employee is found
			}
			P=P->Next;	//move to next employee if employee not found
		}
	if(p==1)	// //breaks search in hashtable once employee is found
		break;
	}
	if(p==0)	// checks if such an employee is not in existing records
		printf("Sorry No Employee found\n");
}
void cost(float checkdistance,char *Stype){
		float time,charges;
		if(strcmp(Stype,"E")==0){	//checks what service type is selected by the customer
		time=checkdistance*0.05;	//multiply distance by its per km time
		charges=checkdistance*2.5;	//multiply distance by its per km charges
		printf("time=%f days\n",ceil(time));	//display time ,ceil converts floating number to next integer
		printf("charges=%f Rs\n",charges);	//display cost of delivery
		}
		if(strcmp(Stype,"P")==0){	//checks what service type is selected by the customer
		time=checkdistance*0.025;	//multiply distance by its per km time
		charges=checkdistance*1.5;	//multiply distance by its per km charges
		printf("time=%f days\n",ceil(time));	//display time ,ceil converts floating number to next integer
		printf("charges=%f Rs\n",charges);	//display cost of delivery
		}
		if(strcmp(Stype,"S")==0){	//checks what service type is selected by the customer
		time=checkdistance*0.055;	//multiply distance by its per km time
		charges=checkdistance*0.65;	//multiply distance by its per km charges
		printf("time=%f days\n",ceil(time)); //display time ,ceil converts floating number to next integer
		printf("charges=%f Rs\n",charges);	//display cost of delivery
		}
	}	 
