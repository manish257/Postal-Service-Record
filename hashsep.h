/* Interface for separate chaining hash table */
typedef int ElementType;

/* START: fig5_2.txt */
        typedef unsigned int Index;
/* END */

/* START: fig5_7.txt */
        #ifndef _HashSep_H
        #define _HashSep_H

        struct ListNode;
        typedef struct ListNode *Position;
        struct HashTbl;
        typedef struct HashTbl *HashTable;
        struct GraphNode;
        typedef struct GraphNode *Position1;
        struct AdjacencyList;
		typedef struct AdjacencyList *List1;
		struct QueueRecord;
        typedef struct QueueRecord *Queue;
		struct info;

        HashTable InitializeTable( int TableSize );
        List1 InitializeGraph( int TableSize );
        Position Find( ElementType Key, HashTable H );
        void Insert( ElementType Key,char *Name,char *City,char *Service_type, HashTable H );
        ElementType Retrieve( Position P );
        void CreateRecord(HashTable H);
        int RetrieveData(ElementType Key,HashTable H);
        int NewEmployee(HashTable H);	
        int UpdateData(int id,HashTable H);
        int NextPrime( int N );
        void CreateGraph(List1 H);
        void InsertGraph (int index,int node,int distance,List1 H);
        float ShortestPath (int source,int destination,int nodes ,List1 H );
        void FindEmployee(int source,char *type,HashTable H);
        void cost(float check_distance,char *Stype);
        int NumericInput(void);
        
        int IsEmpty( Queue Q );
        int IsFull( Queue Q );
        Queue CreateQueue( int MaxElements );
        void DisposeQueue( Queue Q );
        void MakeEmpty( Queue Q );
        void Enqueue( ElementType X, Queue Q );
        ElementType Front( Queue Q );
        void Dequeue( Queue Q );
        ElementType FrontAndDequeue( Queue Q );
        /* Routines such as Delete are MakeEmpty are omitted */

        #endif  /* _HashSep_H */
/* END */
