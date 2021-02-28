


#include <stdio.h>
#include <fstream> 
#include <iostream>
#include <time.h>
//#include <malloc>
#include <vector>

long Maxtransactionsize;
long DimentionSize;
long ProblemSize;
long support;
long GeneralCounter;
int printingflag;
long mxtransaction;
char **stringOutPut;
int stringOutPutCount;


FILE *fp;
FILE *fpoutt;

// data structr for a node of the FP-tree
 struct FPTTree
{
  long  Element;
  long   counter;
  FPTTree* child;  
  FPTTree* brother;
  FPTTree* father;
  FPTTree* next;
};

struct COFITree
{
  long  Element;
  long  counter;
  long  participation;
  COFITree* child;
  COFITree* brother;
  COFITree* father;
  COFITree* next;
};

struct FrequentTree
{
  long  Element;
  long  counter;
  char  text[100];
  int depth;
  FrequentTree* child;
  FrequentTree* brother;
  FrequentTree* father;
  FrequentTree* next;
};

FrequentTree* RootOrignal;
struct FrequentStruc
{
  long  Item;
  long   Frequency;  
  long   COFIFrequency;  
  long   COFIFrequency1; 
  FPTTree* first;
  COFITree* firstCOFI;
 };
 


class Transaction
{ 
public : 
       long ID; 
	   long* Items; 	   
}; 
 


struct TransactionRecord
{
  long  Element;
  long  Index;
};

struct ItemsStructure
{
	long Item;
	long Frequency;

};

struct CandidateStructures
{
	ItemsStructure *ArrayOfCandidates;
};


 long* COFIPattern;
 long* FrequentPattern;
 long DepthArray[500];

 CandidateStructures *Candidate_Items;
 FrequentStruc *F1_Items; 
 long No_Of_Frequent1_Items,F1_Size; 
 TransactionRecord *TransactionArray; 
 long* FindInHashTable;
 int Transaction_Frequent_size;
 std::fstream outfile;
 Transaction Trans;
 int Index_FrequentStruc,New_Index_FrequentStruc;
 FPTTree* First;
 long tran;
 FrequentTree* CurrentF ;
 FrequentTree* FatherF;
 FrequentTree* RootF;
 FrequentTree* NewCurrentF;
 FrequentTree* LastBrotherF;
 long gTotalFTFrequentItemsets;


struct FPTree
{
    struct FPTree *childHead;
    struct FPTree *childNext;
    struct FPTree *parent;
    int item;
    int freq;
    int leaveFreq;
    int Age;
    struct FPTree *headTable;
};
struct FPTree *fpMainRoot;
long gAge = 0;


struct FPHashTable
{   struct FPTree *treeNode;
    struct FPHashTable *next;
    int freq;
};
struct FPHashTable **fpHashRoot;


struct FT_FPTableItems
{
    int item;
    int freq;
    struct FT_FPTableItems *next;
};

struct FT_FPTable
{
    int freq;
    struct FT_FPTableItems *head;
};


struct FT_FPTree
{
    struct FT_FPTree *childHead;
    struct FT_FPTree *childNext;
    struct FT_FPTree *parent;
    int item;
    int freq;
    int leaveFreq;
    struct FT_FPTable *nodeFtTable;
};



int *gCPFreq;
int *gCPAge;
int *gCPAgeTail;

struct FT_FPHashLink
{
    struct FT_FPTree *node;
    struct FT_FPHashLink *next;
};
int gItemsetSupport;
int gItemSupport;
int g_FTFactor;


struct FT_FPTree_LinkedList
{
    struct FT_FPTree *node;
    struct FT_FPTree_LinkedList *next;
    
};
struct FT_FPTree_LinkedList *FT_FPTree_head;




struct FT_FPTable_LinkedList
{
    struct FT_FPTable *node;
    struct FT_FPTable_LinkedList *next;
    
};
struct FT_FPTable_LinkedList *FT_FPTable_head;



struct FT_FPTableItems_LinkedList
{
    struct FT_FPTableItems *node;
    struct FT_FPTableItems_LinkedList *next;
    
};
struct FT_FPTableItems_LinkedList *FT_FPTableItems_head;

int allocate_R = 0;
int deallocate_R = 0;

struct threePairItem
{
    int item;
    int freq;
    struct threePairItem *next;
};


int **twoPair;
struct threePairStruct
{
    struct threePairItem *head;
    int count;
};
struct threePairStruct ***threePair;

//clock_t start1, finish1,start2, finish2,start3, finish3,start4, finish4,start5, finish5,startf, finishf;
//double  duration1,duration2,duration3,duration4,duration5,duration6,duration7,durationp,durationpt;
long LineRead;

//void InitializeItems(long offset, long candidateindex)
void InitializeItems()
{
int i,k;	

	for (i=0;i<=500;++i)
	{
	Candidate_Items[i].ArrayOfCandidates  = (ItemsStructure *)malloc((1000+1)*sizeof(ItemsStructure));
		for (k=0;k<1000;++k)
	{
		
		Candidate_Items[i].ArrayOfCandidates[k].Item =k+(i*1000);
		Candidate_Items[i].ArrayOfCandidates[k].Frequency = 0;
		
				
	}
	}

} // end Initialise Items


long ElementLocation(long element)
{
	long location;
	location = FindInHashTable[element];
	return location;
}

void traverseCOFI(COFITree* Root,int i)

{

	// Recursive deletion of COFI tree
if (Root != NULL)
{
printf ("Item = %ld, depth = %d, counter = %ld ",Root->Element,i,Root->counter);
if (Root->child != NULL)
{
	printf ("Child Item = %ld\n",Root->child->Element);
}
else
{
	printf ("\n");
}
if (Root->brother  != NULL)
{
	printf ("Brother Item = %ld\n",Root->brother->Element);
}
else
{
	printf ("\n");
}
}
if (Root->child != NULL)
		traverseCOFI(Root->child ,i+1);
	
if (Root->brother != NULL)
		traverseCOFI(Root->brother,i);


}


void traverseFrequent(FrequentTree* Root,int i)

{

	// Recursive deletion of COFI tree
if (Root != NULL)
{
printf ("Item = %ld, depth = %d, items = %s, counter = %ld ",Root->Element,i,Root->text ,Root->counter);
if (Root->child != NULL)
{
	printf ("Child Item = %ld\n",Root->child->Element);
}
else {printf ("No child\n");}
}
if (Root->child != NULL)
		traverseFrequent(Root->child ,i+1);
	
if (Root->brother != NULL)
		traverseFrequent(Root->brother,i);


}


long SizeOf1Frequent ()
{
	
	long i,j,k;
	j=0;
	for (i=0;i<=500;++i)
	{
		for (k=0;k<=1000;++k)
			{
				if (Candidate_Items[i].ArrayOfCandidates[k].Frequency >= support)
				{
				++j;					
				}				
			}
	}
	return j;
	
}


void sortfrequent( long lo, long up )
     {
	 int i, j;
     FrequentStruc  tempr;
     while ( up>lo ) {
          i = lo;
          j = up;
          tempr = F1_Items[lo];
          /*** Split file in two ***/
          while ( i<j ) {
               for ( ; F1_Items[j].Frequency > tempr.Frequency; j-- );
               for ( F1_Items[i]=F1_Items[j]; i<j && F1_Items[i].Frequency<=tempr.Frequency; i++ );
               F1_Items[j] = F1_Items[i];
               }
          F1_Items[i] = tempr;
          /*** Sort recursively, the smallest first ***/
          if ( i-lo < up-i ) { sortfrequent(lo,i-1);  lo = i+1; }
               else    { sortfrequent(i+1,up);  up = i-1; }
          }
     }


void Sort_Transaction( long lo, long up )
     {
	 int i, j;
     TransactionRecord  tempr;
     while ( up>lo ) {
          i = lo;
          j = up;
          tempr = TransactionArray[lo];
          /*** Split file in two ***/
          while ( i<j ) 
				{
               for ( ; TransactionArray[j].Index > tempr.Index; j-- );
               for ( TransactionArray[i]=TransactionArray[j]; i<j && TransactionArray[i].Index<=tempr.Index; i++ );
               TransactionArray[j] = TransactionArray[i];
				}
          TransactionArray[i] = tempr;
          /*** Sort recursively, the smallest first ***/
          if ( i-lo < up-i ) { Sort_Transaction(lo,i-1);  lo = i+1; }
               else    { Sort_Transaction(i+1,up);  up = i-1; }
          }
     }


void SortFrequent()
{
		long  i , j,k,d;

	
		j = 0;
		i=0;
		k=0;
		for (d=0;d<=DimentionSize;d++)
		{
		
				if (Candidate_Items[i].ArrayOfCandidates [k].Frequency >= support)
				{
					F1_Items[j].Item = Candidate_Items[i].ArrayOfCandidates[k].Item ;
					F1_Items[j].Frequency  = Candidate_Items[i].ArrayOfCandidates[k].Frequency ;
					F1_Items[j].first = NULL;
					F1_Items[j].firstCOFI = NULL;
					F1_Items[j].COFIFrequency = 0;
					F1_Items[j].COFIFrequency1 = 0;
					++j		;							
				}
				++k;
				if (k%1000 == 0)
				{
					++i;
					k=0;
				}
		}
		sortfrequent(0,j-1);
}

void BuildHashTable()
{
long i;
for (i=0; i<=F1_Size; ++i)
{
	// search for the location of that item	 
	FindInHashTable[F1_Items[i].Item] = i;
} // end for

}


void ReadingFromText()
{
	
char c;
int i;
i=0;

 do {
    int item=0, pos=0;
    c = getc(fp);
    while((c >= '0') && (c <= '9')) {
      item *=10;
      item += int(c)-int('0');
      c = getc(fp);
      pos++;
    }
    if(pos) {
		Trans.Items[i] = item;
		++i;
		}
  }while(c != '\n' && !feof(fp));
 tran = i;
 if (tran > mxtransaction)
	 mxtransaction = tran;

}



bool SearchFrequentBrother(long Item,FrequentTree*& NewCurrent,FrequentTree*& LastBrother)
{

bool found,over;
found = false;
over = false;
LastBrother = NULL;

	while ((NewCurrent != NULL) && (!found) && (!over))
	{
		if (NewCurrent->Element == Item)
		found = true;
		else if (F1_Items[FindInHashTable[Item]].COFIFrequency > F1_Items[FindInHashTable[NewCurrent->Element]].COFIFrequency)
		over = true;
		else 
		{
			LastBrother = NewCurrent;
			NewCurrent  = NewCurrent->brother;
		}
	} // End while ((Current != NULL) && (!found))
return found;

} // End bool SearchFTPBrother(NewTransactionArray[i],Current,NewCurrent)



bool SearchCOFIBrother(long Item,COFITree*& NewCurrent,COFITree*& LastBrother)
{
bool found,over;
found = false;
over = false;
LastBrother = NULL;

	while ((NewCurrent != NULL) && (!found) && (!over))
	{
		if (NewCurrent->Element == Item)
		found = true;
		else if (F1_Items[FindInHashTable[Item]].COFIFrequency > F1_Items[FindInHashTable[NewCurrent->Element]].COFIFrequency)
		over = true;
		else 
		{
			LastBrother = NewCurrent;
			NewCurrent  = NewCurrent->brother;
		}
	} // End while ((Current != NULL) && (!found))
return found;
} // End bool SearchFTPBrother(NewTransactionArray[i],Current,NewCurrent)


bool SearchFTPBrother(struct TransactionRecord Item,FPTTree*& NewCurrent,FPTTree*& LastBrother)
{
bool found,over;
found = false;
over = false;
LastBrother = NULL;

	while ((NewCurrent != NULL) && (!found) && (!over))
	{
		if (NewCurrent->Element == Item.Element)
		found = true;
		else if (F1_Items[FindInHashTable[Item.Element]].COFIFrequency > F1_Items[FindInHashTable[NewCurrent->Element]].Frequency)
		over = true;
		else 
		{
			LastBrother = NewCurrent;
			NewCurrent  = NewCurrent->brother;
		}
	} // End while ((Current != NULL) && (!found))


return found;
} // End bool SearchFTPBrother(NewTransactionArray[i],Current,NewCurrent)

void AddNewChildWithBrother(struct TransactionRecord item,FPTTree* FatherNode,FPTTree* LastBrother,FPTTree*& NewCurrent)
{

	FPTTree* node = new FPTTree;
	node->Element = item.Element;
	node->child = NULL;
	node->next = NULL;
	node->counter = 1;
	node->father = FatherNode;
	
	if (LastBrother == NULL)
	{
	node->brother = FatherNode->child;		
	FatherNode->child = node;
	}
	else
	{
		node->brother = LastBrother->brother;	
		LastBrother->brother = node;
	}
	NewCurrent = node;

}

void AddNewChildNoBrother(struct TransactionRecord item,FPTTree* FatherNode,FPTTree*& NewCurrent)
{
	FPTTree* node = new FPTTree;
	node->Element = item.Element;
	node->brother = NULL;	
	node->child = NULL;		
	node->next = NULL;
	node->counter = 1;
	node->father = FatherNode;
	FatherNode->child = node;
	NewCurrent = node;
}

void AddCOFINewChildWithBrother(long item,COFITree* FatherNode,COFITree* LastBrother,COFITree*& NewCurrent, long branchsupport)
{

	NewCurrent = (COFITree* )malloc(sizeof(COFITree));
	NewCurrent->Element = item;
	NewCurrent->child = NULL;	
	NewCurrent->next = NULL;
	NewCurrent->counter = branchsupport;
	NewCurrent->father = FatherNode;	
	NewCurrent->participation = 0;
	if (LastBrother == NULL)
	{
	NewCurrent->brother = FatherNode->child;		
	FatherNode->child = NewCurrent;
	}
	else
	{
		NewCurrent->brother = LastBrother->brother;	
		LastBrother->brother = NewCurrent;
	}
}


void AddCOFINewChildNoBrother(long item,COFITree* FatherNode,COFITree*& NewCurrent, long branchsupport)
{

	NewCurrent = (COFITree* )malloc(sizeof(COFITree));
	NewCurrent->Element = item;
	NewCurrent->child = NULL;	
	NewCurrent->brother = NULL;
	NewCurrent->next = NULL;
	NewCurrent->counter = branchsupport;
	NewCurrent->father = FatherNode;
	NewCurrent->participation = 0;
	FatherNode->child = NewCurrent;


}

void AddFrequentNewChildWithBrother(long item,FrequentTree* FatherNode,FrequentTree* LastBrother,FrequentTree*& NewCurrent, long branchsupport, long depth)
{

	NewCurrent = (FrequentTree* )malloc(sizeof(FrequentTree));
	sprintf(NewCurrent->text, "%s %ld",FatherNode->text,item);
	NewCurrent->Element = item;
	NewCurrent->child = NULL;
	NewCurrent->depth = depth;
	NewCurrent->next = NULL;
	NewCurrent->counter = branchsupport;
	NewCurrent->father = FatherNode;	

		if (LastBrother == NULL)
	{
	NewCurrent->brother = FatherNode->child;		
	FatherNode->child = NewCurrent;
	}
	else
	{
		NewCurrent->brother = LastBrother->brother;	
		LastBrother->brother = NewCurrent;
	}
}


void AddFrequentNewChildNoBrother(long item,FrequentTree* FatherNode,FrequentTree*& NewCurrent, long branchsupport,long depth)
{

	NewCurrent = (FrequentTree* )malloc(sizeof(FrequentTree));
	sprintf(NewCurrent->text, "%s %ld",FatherNode->text,item);
	NewCurrent->Element = item;
	NewCurrent->depth = depth;
	NewCurrent->brother = NULL;
	NewCurrent->child = NULL;		
	NewCurrent->next = NULL;
	NewCurrent->counter = branchsupport;
	NewCurrent->father = FatherNode;
	FatherNode->child = NewCurrent;
	
}

void UpdateTable(struct TransactionRecord item,FPTTree*& NewCurrent)
{
	int loc = item.Index;
	
		if (F1_Items[loc].first == NULL)
			F1_Items[loc].first = NewCurrent;
		 else
			{
				NewCurrent->next = F1_Items[loc].first;
				F1_Items[loc].first= NewCurrent;
			}

}

void UpdateCOFITable(long item,COFITree*& NewCurrent,long branchsupport)
{
	long loc = FindInHashTable[item];
	
		if (F1_Items[loc].firstCOFI  == NULL)
			F1_Items[loc].firstCOFI = NewCurrent;
		 else
			{
				NewCurrent->next = F1_Items[loc].firstCOFI ;
				F1_Items[loc].firstCOFI =NewCurrent;
			}
}

void AddToFTPTree(struct TransactionRecord Item,FPTTree*& Current,FPTTree* LastBrother,FPTTree* Fathernode)
{
	if (Fathernode->child == NULL)
			AddNewChildNoBrother(Item,Fathernode,Current);
	else
	{
			AddNewChildWithBrother(Item,Fathernode,LastBrother,Current);

	}
	 UpdateTable(Item,Current);
} // End AddToFTPTree(NewTransactionArray[i],FPTTree*& Current);

void AddToCOFITree(long Item,COFITree*& Current,COFITree* LastBrother,COFITree* Fathernode, long branchsupport)
{
	if (Fathernode->child == NULL)
			AddCOFINewChildNoBrother(Item,Fathernode,Current,branchsupport);
	else
	{
			AddCOFINewChildWithBrother(Item,Fathernode,LastBrother,Current,branchsupport);
	}
	 UpdateCOFITable(Item,Current,branchsupport);
} // End AddToFTPTree(NewTransactionArray[i],FPTTree*& Current);

void AddToFrequentTree(long Item,FrequentTree*& Current,FrequentTree* LastBrother,FrequentTree* Fathernode, long branchsupport, long depth)
{
	if (Fathernode->child == NULL)
			AddFrequentNewChildNoBrother(Item,Fathernode,Current,branchsupport,depth);
	else
				AddFrequentNewChildWithBrother(Item,Fathernode,LastBrother,Current,branchsupport,depth);
} // End AddToFTPTree(NewTransactionArray[i],FPTTree*& Current);


void ScanForLocation(int& sizeofFrequent)
{
		int i,j;
		j=0;
		i=0;
		while (j<tran)
		{
			if (FindInHashTable[Trans.Items[j]] != -1)
			{
				TransactionArray[i].Element  = Trans.Items[j] ;
				TransactionArray[i].Index = FindInHashTable[Trans.Items[j]] ;
				++i;
			}
			++j;
		} // End while (j<TransactionSize)
		sizeofFrequent = i-1;
} // End void ScanForLocation()


void FreeCOFITree(COFITree* COFIRoot)
{

	// Recursive deletion of COFI tree
	if (COFIRoot->child != NULL)
			FreeCOFITree(COFIRoot->child);
	if (COFIRoot->brother != NULL)
			FreeCOFITree(COFIRoot->brother);
	free (COFIRoot);
}

void traverseFPtree(FPTTree* Root)

{

	// Recursive deletion of COFI tree
if (Root != NULL)
{
printf ("Item = %ld, counter = %ld ",Root->Element, Root->counter);
if (Root->child != NULL)
{
	printf ("Child Item = %ld\n",Root->child->Element);
}
else {printf ("No child\n");}
}
if (Root->child != NULL)
		traverseFPtree(Root->child );
	
if (Root->brother != NULL)
		traverseFPtree(Root->brother);


}
/*

void traverseFPtree(FPTTree* Root,long depth,long brothers)
{
	// Recursive deletion of COFI tree
	Root = Root->child ;
	long i = 0;
	while (Root->brother != NULL)
	{
		fprintf(fpout,"%ld,Item,%ld,localfrequany,%ld,Global frequancy,%ld\n",i,Root->Element,Root->counter,F1_Items[FindInHashTable[Root->Element]].Frequency); 
		Root = Root->brother ;
		++i;
	}
}

*/

void FreeFrequentTree(FrequentTree* Root)
{
	// Recursive deletion of COFI tree
	
	if (Root->child != NULL)
			FreeFrequentTree(Root->child);
	if (Root->brother != NULL)
			FreeFrequentTree(Root->brother);
	
	if (Root->counter >= support)
	{
		++DepthArray[Root->depth];
		if (printingflag == 1)
		{
		//	fprintf(fpout, "%s ", Root->text);
		//	fprintf(fpout, "(%ld)\n", Root->counter);
		}
	}	
	free (Root);
}



void Generate_frequents (long itemsize, long branchsupport)
{

			FatherF = RootF;
			CurrentF=RootF->child  ;
			NewCurrentF = RootF->child;
			LastBrotherF = RootF->child;
			bool Found;
			
			for (int i=1;i<=itemsize;i++)
				{
					Found = false;
					if (CurrentF != NULL)
					{
						NewCurrentF = CurrentF;
						LastBrotherF = CurrentF;
						Found = SearchFrequentBrother(FrequentPattern[i],NewCurrentF,LastBrotherF);
					}
					if (Found)
					{
						CurrentF = NewCurrentF;
						if (itemsize == i) // only for last item
						CurrentF->counter = CurrentF->counter + branchsupport ; 
					} else
					{

						AddToFrequentTree(FrequentPattern[i],CurrentF,LastBrotherF,FatherF,branchsupport,i+1);
					}

					FatherF=CurrentF;
					CurrentF=CurrentF->child;
				}

			
}

void candidate_generation(FrequentTree* RootNode, int startpoint ,int itemsize, long branchsupport)
{


			FrequentTree* TempNode;
			FatherF = RootNode;
			CurrentF=RootF->child  ;
			NewCurrentF = RootF->child;
			LastBrotherF = RootF->child;
			bool Found;
			TempNode = FatherF;

			for (int i=startpoint;i<itemsize;i++)
				{
					Found = false;
					FatherF = TempNode;
					CurrentF = FatherF->child ;

					if (CurrentF != NULL)
					{
						NewCurrentF = CurrentF;
						LastBrotherF = CurrentF;
						Found = SearchFrequentBrother(COFIPattern[i],NewCurrentF,LastBrotherF);
					}
					if (Found)
					{
						CurrentF = NewCurrentF;
						//if (itemsize == i) // only for last item
						CurrentF->counter = CurrentF->counter + branchsupport ; 
					} else
					{
						
						AddToFrequentTree(COFIPattern[i],CurrentF,LastBrotherF,FatherF,branchsupport,FatherF->depth+1);
					}
					if (i+1 != itemsize)
						candidate_generation(CurrentF,i+1,itemsize,branchsupport);
					
				}

}


long FindNextLocal(long COFIItemlocation, long Originallocation)
{
	long location = Originallocation;
	
	bool found;
	found = false;

	while ((location > COFIItemlocation) && (!found))		
		{
			if ((F1_Items[location].firstCOFI != NULL) && (F1_Items[location].COFIFrequency >= support) && (F1_Items[location].COFIFrequency > F1_Items[location].COFIFrequency1))
				found = true;
			else
				-- location;
		}		
	return location;
}

void MineCOFITree(COFITree* COFIRoot, long itemlocation, long c)
{
	
	long SizeOfFrequent = F1_Size - itemlocation;
	long LocationOfCurrentlocalF = FindNextLocal(itemlocation,F1_Size);
	CurrentF = new FrequentTree;
	FatherF = new FrequentTree;
	NewCurrentF = new FrequentTree;
	LastBrotherF = new FrequentTree;
	RootOrignal = new FrequentTree;

	RootF = (FrequentTree* )malloc(sizeof(FrequentTree));

    RootF->Element = COFIRoot->Element ;
	RootF->depth = 1;
	sprintf(RootF->text, "%ld",COFIRoot->Element);
	RootF->counter = COFIRoot->counter ;
 	RootF->brother = NULL;		
//	RootF->brotherR = NULL;		
	RootF->father   = NULL;
	RootF->next   = NULL;
	RootF->child = NULL;
	RootOrignal = RootF;

	if (LocationOfCurrentlocalF != itemlocation)
	{
	long patternsize;
	
	COFIPattern = (long *)malloc((SizeOfFrequent+1)*sizeof(long));
	COFITree* COFInode;
	COFITree* traverse;
	int counter = 0;
	while (LocationOfCurrentlocalF != itemlocation)
	{
	COFInode = F1_Items[LocationOfCurrentlocalF].firstCOFI;
	while (COFInode != NULL)
			{			
			traverse = COFInode;
			long branchsupport = traverse->counter - traverse->participation  ;
			//COFIPattern[0] = COFIRoot->Element ;
			patternsize = 0;
			while ((traverse  != COFIRoot) && (branchsupport > 0))
				{
				// Item prunning
					COFIPattern[patternsize] = traverse->Element ;				
					traverse->participation = traverse->participation + branchsupport;
					++patternsize;
					F1_Items[FindInHashTable[traverse->Element]].COFIFrequency1 = F1_Items[FindInHashTable[traverse->Element]].COFIFrequency1 + branchsupport;
					traverse = traverse->father ;
				} // end while (traverse->FatherCOFI != root)
			
			COFInode = COFInode->next ;
			if (patternsize > 0)
			{
		
			++GeneralCounter;
			candidate_generation (RootF,0,patternsize,branchsupport);
			RootF = RootOrignal ;

			}
		}  // End (while (COFInode != F1_Items[j].last)
	LocationOfCurrentlocalF = FindNextLocal(itemlocation,LocationOfCurrentlocalF-1);
	++ counter;
	} // end loop (LocationOfCurrentlocalF != itemlocation)
	} // end if (LocationOfCurrentlocalF != itemlocation)
}

void deallocate_FT_FPTree (struct FT_FPTree *node )
{
    allocate_R++; 
  if ( FT_FPTree_head == NULL )
  {
      struct FT_FPTree_LinkedList *temp;
      temp = (struct FT_FPTree_LinkedList *)malloc(sizeof(struct FT_FPTree_LinkedList));
      
      temp->node = node;
      temp->next = NULL;
      
      FT_FPTree_head = temp;
   //   printf("\nhello 3\n");
        
  }
  else
  {
      struct FT_FPTree_LinkedList *temp;
      temp = (struct FT_FPTree_LinkedList *)malloc(sizeof(struct FT_FPTree_LinkedList));
      
      temp->node = node;
      temp->next = FT_FPTree_head;
      FT_FPTree_head = temp; 
    //  printf("\nhello 4\n");
  }
  
    
}

struct FT_FPTree * allocate_FT_FPTree( )
{
    
    
    struct FT_FPTree *fpTreeTemp;
    if ( FT_FPTree_head != NULL )
    {
        
            struct FT_FPTree_LinkedList *nextNode;
            nextNode = FT_FPTree_head->next;
            fpTreeTemp = FT_FPTree_head->node;
           // printf("\n hello 1\n");
            if ( nextNode != NULL )
            {

                    FT_FPTree_head = nextNode;
            }
            else
            {
                    FT_FPTree_head = NULL;
            }
        
            allocate_R--;
        
    }
    else if ( FT_FPTree_head == NULL )
    {
            fpTreeTemp = (struct FT_FPTree *)malloc(sizeof(struct FT_FPTree));
           // printf("\n hello 2\n");
            deallocate_R++;
    }
            
    
     fpTreeTemp->childHead = NULL;
     fpTreeTemp->childNext = NULL;
     fpTreeTemp->freq = 0;
     fpTreeTemp->item = 0;
     fpTreeTemp->leaveFreq = 0;
     fpTreeTemp->nodeFtTable = NULL;
     fpTreeTemp->parent = NULL;
    
      return fpTreeTemp;
    
}


void deallocate_FT_FPTable (struct FT_FPTable *node )
{
   
  if ( FT_FPTable_head == NULL )
  {
      struct FT_FPTable_LinkedList *temp;
      temp = (struct FT_FPTable_LinkedList *)malloc(sizeof(struct FT_FPTable_LinkedList));
      
      temp->node = node;
      temp->next = NULL;
      
      FT_FPTable_head = temp;
   //   printf("\nhello 3\n");
      
        
  }
  else
  {
      struct FT_FPTable_LinkedList *temp;
      temp = (struct FT_FPTable_LinkedList *)malloc(sizeof(struct FT_FPTable_LinkedList));
      
      temp->node = node;
      temp->next = FT_FPTable_head;
      FT_FPTable_head = temp; 
    //  printf("\nhello 4\n");
  }
    
}

struct FT_FPTable * allocate_FT_FPTable( )
{
    struct FT_FPTable *fpTreeTemp;
    if ( FT_FPTable_head != NULL )
    {
        
            struct FT_FPTable_LinkedList *nextNode;
            nextNode = FT_FPTable_head->next;
            fpTreeTemp = FT_FPTable_head->node;
           // printf("\n hello 1\n");
            if ( nextNode != NULL )
            {

                    FT_FPTable_head = nextNode;
            }
            else
            {
                    FT_FPTable_head = NULL;
            }
        
        
    }
    else if ( FT_FPTable_head == NULL )
    {
            fpTreeTemp = (struct FT_FPTable *)malloc((g_FTFactor+2)*sizeof(struct FT_FPTable));
            
            
                          //       struct FT_FPTable *tempFT_FPTable = (struct FT_FPTable *)malloc((g_FTFactor+2)*sizeof(struct FT_FPTable));

                  
           // printf("\n hello 2\n");
    }
            
    

    for ( int kk = 0; kk < (g_FTFactor+2); kk++ )
    {
            fpTreeTemp[kk].head = NULL;
            fpTreeTemp[kk].freq = 0;
    }
            
    return fpTreeTemp;
    
}



















void deallocate_FT_FPTableItems (struct FT_FPTableItems *node )
{
  if ( FT_FPTableItems_head == NULL )
  {
      struct FT_FPTableItems_LinkedList *temp;
      temp = (struct FT_FPTableItems_LinkedList *)malloc(sizeof(struct FT_FPTableItems_LinkedList));
      
      temp->node = node;
      temp->next = NULL;
      
      FT_FPTableItems_head = temp;
   //   printf("\nhello 3\n");
        
  }
  else
  {
      struct FT_FPTableItems_LinkedList *temp;
      temp = (struct FT_FPTableItems_LinkedList *)malloc(sizeof(struct FT_FPTableItems_LinkedList));
      
      temp->node = node;
      temp->next = FT_FPTableItems_head;
      FT_FPTableItems_head = temp; 
    //  printf("\nhello 4\n");
  }
    
}

struct FT_FPTableItems * allocate_FT_FPTableItems( )
{
    struct FT_FPTableItems *fpTreeTemp;
    if ( FT_FPTableItems_head != NULL )
    {
        
            struct FT_FPTableItems_LinkedList *nextNode;
            nextNode = FT_FPTableItems_head->next;
            fpTreeTemp = FT_FPTableItems_head->node;
           // printf("\n hello 1\n");
            if ( nextNode != NULL )
            {

                    FT_FPTableItems_head = nextNode;
            }
            else
            {
                    FT_FPTableItems_head = NULL;
            }
        
        
    }
    else if ( FT_FPTableItems_head == NULL )
    {
            fpTreeTemp = (struct FT_FPTableItems *)malloc(sizeof(struct FT_FPTableItems));
            
            
                          //       struct FT_FPTable *tempFT_FPTable = (struct FT_FPTable *)malloc((g_FTFactor+2)*sizeof(struct FT_FPTable));

                  
           // printf("\n hello 2\n");
    }
            
    

    fpTreeTemp->freq = 0;
    fpTreeTemp->item = 0;
    fpTreeTemp->next = NULL;
            
    return fpTreeTemp;
    
}



int partition( int a[], int l, int r) {
   int pivot, i, j, t;
   pivot = a[l];
   i = l; j = r+1;
		
   while( 1)
   {
   	do ++i; while( a[i] <= pivot && i <= r );
   	do --j; while( a[j] > pivot );
   	if( i >= j ) break;
   	t = a[i]; a[i] = a[j]; a[j] = t;
   }
   t = a[l]; a[l] = a[j]; a[j] = t;
   return j;
}

void quickSort( int a[], int l, int r)
{
   int j;

   if( l < r ) 
   {
   	// divide and conquer
        j = partition( a, l, r);
       quickSort( a, l, j-1);
       quickSort( a, j+1, r);
   }
	
}

void printFPTree(struct FPTree *fpTempRoot,int level)
{
    struct FPTree *fpTreeTraverse;
   // printf("\nprinting\n");

    fpTreeTraverse = fpTempRoot->childHead;
    if ( fpTreeTraverse != NULL )
    {
                    while(true)
                    {
     //                       printf("printing...%d...%d ",fpTreeTraverse->item, level );
                            printFPTree(fpTreeTraverse,(level+1));
                            
                            if ( fpTreeTraverse->childNext == NULL )
                                break;

                            fpTreeTraverse = fpTreeTraverse->childNext;
                    }
    }
            
}

void delete_FT_FPTree(struct FT_FPTree *fpTempRoot,int level)
{
    struct FT_FPTree *fpTreeTraverse,*tempPP;
 //   printf("\nprinting\n");

    fpTreeTraverse = fpTempRoot->childHead;
    if ( fpTreeTraverse != NULL )
    {
                    while(true)
                    {
                         //   printf("printing...%d...%d ",fpTreeTraverse->item, level );
                            
                            delete_FT_FPTree(fpTreeTraverse,(level+1));
                            
                            if ( fpTreeTraverse->childNext == NULL )
                            {
                                
                                deallocate_FT_FPTree(fpTreeTraverse);
                                break;
                            }

                            
                            tempPP = fpTreeTraverse;
                            fpTreeTraverse = fpTreeTraverse->childNext;
                            
                            
                           
                            //free(tempPP);
                            deallocate_FT_FPTree(tempPP);
                    }
                            
    }
            
}




void InsertItemHashTable(int Item,struct FPTree *treeNode)
{
    struct FPHashTable *tempP;
    
    if ( fpHashRoot[Item] == NULL )
    {
        tempP = (struct FPHashTable *)malloc(sizeof(struct FPHashTable));
        tempP->freq = 1;
        tempP->next = NULL;
        tempP->treeNode = treeNode;
        fpHashRoot[Item] = tempP;
    }
    else
    {
        tempP = (struct FPHashTable *)malloc(sizeof(struct FPHashTable));
        tempP->freq = (fpHashRoot[Item]->freq+1);
        tempP->next = fpHashRoot[Item];
        tempP->treeNode = treeNode;  
        fpHashRoot[Item] = tempP;
    }
    
}

void InsertHeadItemsInTable(struct FT_FPTable *tempFT_FPTable,int *headItemArray, int headCount, int ftFactor, int cpFreq, int *headItemArrayFreq)
{
    struct FT_FPTableItems *tempP,*tempTraverse;


    for ( int i = 0; i < headCount; i++)
    {
        //printf("\n hello 6...%d\n",ftFactor);    
        if ( tempFT_FPTable[ftFactor].head == NULL )
        {
           // printf("\n hello 6...%d\n",ftFactor);    
            //tempP = (struct FT_FPTableItems *)malloc(sizeof(struct FT_FPTableItems));
            tempP = allocate_FT_FPTableItems();
            tempP->item = headItemArray[i];
            tempP->freq = headItemArrayFreq[i];
            tempP->next = NULL;
            tempFT_FPTable[ftFactor].head = tempP;
         //   printf("\n hello 6...%d\n",ftFactor);    
        }
        else
        {
            int found = 0;
            tempTraverse = tempFT_FPTable[ftFactor].head;
            while(true)
            {
                if ( tempTraverse->item == headItemArray[i])
                {
                    found = 1;
                    tempTraverse->freq+=headItemArrayFreq[i];;
                    break;
                }
                if ( tempTraverse->next == NULL)
                    break;
                
                tempTraverse = tempTraverse->next;
                
            }
            if ( found == 0 )
            {
                  //tempP = (struct FT_FPTableItems *)malloc(sizeof(struct FT_FPTableItems));
                  tempP = allocate_FT_FPTableItems();
                  tempP->item = headItemArray[i];
                  tempP->freq = headItemArrayFreq[i];;
                  tempP->next = tempFT_FPTable[ftFactor].head;
                  tempFT_FPTable[ftFactor].head = tempP;
            }
                       
        }
    }
}


void generate_FT_FP_Branch(struct FT_FPHashLink *tempFT_HashTable,struct FT_FPTree *ftRoot, int *cpItemArray, int cpSize, int cpFreq, int *headItemArray, int headCount, int ftFactor, int *headItemArrayFreq)
{
    struct FT_FPTree *fpTreeTemp,*fpTreeTraverse,*tempRoot,*tempFPNodeSave;
    int FoundFlag = 0;
    

   // printf("\n hello ===== %d\n",cpFreq);
   
    
    if ( cpSize == 0)
    {
                                if ( ftRoot->nodeFtTable == NULL )
                                {
                                
                                       //ftRoot->nodeFtTable = (struct FT_FPTable *)malloc((g_FTFactor+2)*sizeof(struct FT_FPTable));      
                                       ftRoot->nodeFtTable = allocate_FT_FPTable();
                                       for ( int kk = 0; kk < (g_FTFactor+2); kk++ )
                                       {
                                           ftRoot->nodeFtTable[kk].head = NULL;
                                           ftRoot->nodeFtTable[kk].freq = 0;
                                       }
                                       
                                       ftRoot->nodeFtTable[ftFactor].freq = cpFreq;
    
                                       
                                       InsertHeadItemsInTable(ftRoot->nodeFtTable,headItemArray,headCount,ftFactor,cpFreq,headItemArrayFreq);
                                       
                                       
                                        if ( tempFT_HashTable == NULL )
                                        {
                                               struct FT_FPHashLink *tempHashNode = (struct FT_FPHashLink *)malloc(sizeof(struct FT_FPHashLink));
                                               tempHashNode->node = ftRoot;
                                               tempHashNode->next = NULL;

                                               tempFT_HashTable = tempHashNode;

                                        }
                                        else
                                        {
                                               struct FT_FPHashLink *tempHashNode = (struct FT_FPHashLink *)malloc(sizeof(struct FT_FPHashLink));
                                               tempHashNode->node = ftRoot;
                                               tempHashNode->next = tempFT_HashTable->next;
                                               tempFT_HashTable->next = tempHashNode;
                                        }                                
                                }
                                else
                                {
                                       ftRoot->nodeFtTable[ftFactor].freq+=cpFreq;
                                       InsertHeadItemsInTable(ftRoot->nodeFtTable,headItemArray,headCount,ftFactor,cpFreq,headItemArrayFreq);                                    
                                }
    
                                

                                
             return;
    }
    
    // printf("\n hello ===== %d\n",cpFreq);
    
    tempRoot = ftRoot;
    fpTreeTraverse = tempRoot->childHead;
    for ( int i = 0; i < cpSize; i++ )
    {

            FoundFlag = -1;
            if ( fpTreeTraverse != NULL )
            {
                    while(true)
                    {
                            if ( fpTreeTraverse->item == cpItemArray[i] )
                            {
                                FoundFlag = 1;
                                break;
                            }
                            if ( fpTreeTraverse->childNext == NULL )
                                break;

                            fpTreeTraverse = fpTreeTraverse->childNext;
                    }
                    if ( FoundFlag == 1 )
                    {
                            fpTreeTraverse->freq+=cpFreq;
                            if ( i == (cpSize-1))
                            {
                                fpTreeTraverse->leaveFreq+=cpFreq;
                                
                                if ( fpTreeTraverse->nodeFtTable == NULL )
                                {
                                       struct FT_FPTable *tempFT_FPTable;// = (struct FT_FPTable *)malloc((g_FTFactor+2)*sizeof(struct FT_FPTable));
                                       tempFT_FPTable = allocate_FT_FPTable();
                                       for ( int kk = 0; kk < (g_FTFactor+2); kk++ )
                                       {
                                           tempFT_FPTable[kk].head = NULL;
                                           tempFT_FPTable[kk].freq = 0;
                                       }
                                       
                                       tempFT_FPTable[ftFactor].freq = cpFreq;
                                       InsertHeadItemsInTable(tempFT_FPTable,headItemArray,headCount,ftFactor,cpFreq,headItemArrayFreq);
                                       fpTreeTraverse->nodeFtTable = tempFT_FPTable;
                                       
                                       if ( tempFT_HashTable == NULL )
                                       {
                                               struct FT_FPHashLink *tempHashNode = (struct FT_FPHashLink *)malloc(sizeof(struct FT_FPHashLink));
                                               tempHashNode->node = fpTreeTraverse;
                                               tempHashNode->next = NULL;

                                               tempFT_HashTable->next = tempHashNode;

                                       }
                                       else
                                       {
                                               struct FT_FPHashLink *tempHashNode = (struct FT_FPHashLink *)malloc(sizeof(struct FT_FPHashLink));
                                               tempHashNode->node = fpTreeTraverse;
                                               tempHashNode->next = tempFT_HashTable->next;
                                               tempFT_HashTable->next = tempHashNode;
                                       }
                                       
                                       
                                }
                                else
                                {
                                       fpTreeTraverse->nodeFtTable[ftFactor].freq+=cpFreq;
                                       InsertHeadItemsInTable(fpTreeTraverse->nodeFtTable,headItemArray,headCount,ftFactor,cpFreq,headItemArrayFreq);                                    
                                }
                                
                            }
                   
                            
                            tempRoot = fpTreeTraverse;
                            fpTreeTraverse = fpTreeTraverse->childHead;

                 
                    }
                    else
                    {
                            //fpTreeTemp = (struct FT_FPTree *)malloc(sizeof(struct FT_FPTree));
                            fpTreeTemp = allocate_FT_FPTree();
                            fpTreeTemp->childHead = NULL;
                            fpTreeTemp->childNext = NULL;
                            fpTreeTemp->parent = NULL;
                            fpTreeTemp->item = cpItemArray[i];
                            fpTreeTemp->freq = cpFreq;
                            //printf("\n%d...%d...",cpItemArray[i],headItemArrayFreq[i]);
                            
                            fpTreeTemp->leaveFreq=cpFreq;
                            
                            fpTreeTemp->nodeFtTable = NULL;
                            if ( i == (cpSize-1))
                            {
                                struct FT_FPTable *tempFT_FPTable;// = (struct FT_FPTable *)malloc((g_FTFactor+2)*sizeof(struct FT_FPTable));
                                tempFT_FPTable = allocate_FT_FPTable();
                                for ( int kk = 0; kk < (g_FTFactor+2); kk++ )
                                {
                                           tempFT_FPTable[kk].head = NULL;
                                           tempFT_FPTable[kk].freq = 0;
                                }
                                
                                tempFT_FPTable[ftFactor].freq = cpFreq;
                                InsertHeadItemsInTable(tempFT_FPTable,headItemArray,headCount,ftFactor,cpFreq,headItemArrayFreq);
                                fpTreeTemp->nodeFtTable = tempFT_FPTable;
                                
                                       if ( tempFT_HashTable == NULL )
                                       {
                                               struct FT_FPHashLink *tempHashNode = (struct FT_FPHashLink *)malloc(sizeof(struct FT_FPHashLink));
                                               tempHashNode->node = fpTreeTemp;
                                               tempHashNode->next = NULL;

                                               tempFT_HashTable->next = tempHashNode;

                                       }
                                       else
                                       {
                                               struct FT_FPHashLink *tempHashNode = (struct FT_FPHashLink *)malloc(sizeof(struct FT_FPHashLink));
                                               tempHashNode->node = fpTreeTemp;
                                               tempHashNode->next = tempFT_HashTable->next;
                                               tempFT_HashTable->next = tempHashNode;
                                       }                              
                            }
                             //      printf("\nhello...%d",cpItemArray[i]); 
                            fpTreeTemp->parent = tempRoot;
                            //printf("\ntree2) ");
                      
                            
                            tempFPNodeSave = tempRoot->childHead;
                            tempRoot->childHead = fpTreeTemp;
                            fpTreeTemp->childNext = tempFPNodeSave;
                            
                           // tempFPNodeSave = tempRoot;
                            tempRoot = fpTreeTemp;
                            fpTreeTraverse = fpTreeTemp->childHead;
                         
       //                     printf("\ntree2) %d...%d....%d",ItemArray[i],i,tempFPNodeSave->item);

                    }    
            }
            else
            {
                    //fpTreeTemp = (struct FT_FPTree *)malloc(sizeof(struct FT_FPTree));
                
                    fpTreeTemp = allocate_FT_FPTree();
                    fpTreeTemp->childHead = NULL;
                    fpTreeTemp->childNext = NULL;
                    fpTreeTemp->parent = NULL;
                    fpTreeTemp->item = cpItemArray[i];
                    
                    fpTreeTemp->freq = cpFreq;
                    fpTreeTemp->leaveFreq=cpFreq;
                            
                    fpTreeTemp->nodeFtTable = NULL;
                    
     
                    //printf("\n%d......%d\n",cpSize,cpItemArray[i]);
                    if ( i == (cpSize-1))
                    {
                        struct FT_FPTable *tempFT_FPTable;// = (struct FT_FPTable *)malloc((g_FTFactor+2)*sizeof(struct FT_FPTable));
                        tempFT_FPTable = allocate_FT_FPTable();
                        for ( int kk = 0; kk < (g_FTFactor+2); kk++ )
                        {
                               tempFT_FPTable[kk].head = NULL;
                               tempFT_FPTable[kk].freq = 0;
                        }
                        
                        tempFT_FPTable[ftFactor].freq = cpFreq;
                        InsertHeadItemsInTable(tempFT_FPTable,headItemArray,headCount,ftFactor,cpFreq,headItemArrayFreq);
                        fpTreeTemp->nodeFtTable = tempFT_FPTable;
                        
                                       if ( tempFT_HashTable == NULL )
                                       {
                                               struct FT_FPHashLink *tempHashNode = (struct FT_FPHashLink *)malloc(sizeof(struct FT_FPHashLink));
                                               tempHashNode->node = fpTreeTemp;
                                               tempHashNode->next = NULL;

                                               tempFT_HashTable = tempHashNode;
                                               

                                       }
                                       else
                                       {
                                               struct FT_FPHashLink *tempHashNode = (struct FT_FPHashLink *)malloc(sizeof(struct FT_FPHashLink));
                                               tempHashNode->node = fpTreeTemp;
                                               tempHashNode->next = tempFT_HashTable->next;
                                               tempFT_HashTable->next = tempHashNode;
                                            
                                       }   
                    }
                    
                     
                    
                    fpTreeTemp->parent = tempRoot;
                    tempRoot->childHead = fpTreeTemp;
                    
                    
                    tempFPNodeSave = tempRoot;
                    tempRoot = fpTreeTemp;
                    fpTreeTraverse = fpTreeTemp->childHead;
                    
 
           //         printf("\ntree %d...%d....%d",ItemArray[i],i,tempFPNodeSave->item);
       //             if ( i == 1 )
         //               exit(1);
                    
            }

     
    }
    
    
      
    
}
void InsertIntoFT_FPTree(struct FT_FPHashLink *tempFT_HashTable, struct FT_FPTree *ftRoot, int *cpItemArray, int cpSize, int cpFreq,int *ItemsetArray, int ItemsetArraySize, int *cpItemArrayFreq, int f_ft_Factor)
{
    int countMatching = 0;
    int *cleanTailItems;
    int *cleanHeadItems;
    int *cleanHeadItemsFreq;
    int tailCount = 0;
    int headCount = 0;
    int found = 0;
    
    cleanTailItems = (int *)malloc(sizeof(int)*cpSize);
    cleanHeadItems = (int *)malloc(sizeof(int)*ItemsetArraySize);
    cleanHeadItemsFreq = (int *)malloc(sizeof(int)*ItemsetArraySize);
    
    
    
    
    
    for ( int i = cpSize-1; i >= 0; i-- )
    {
        found = 0;
        for ( int j = 0; j < ItemsetArraySize; j++)
        {
            if ( cpItemArray[i] == ItemsetArray[j])
            {
                countMatching++;
                found = 1;
            }
        }
        if ( found == 1)
        {
                cleanHeadItems[headCount] = cpItemArray[i];
                cleanHeadItemsFreq[headCount] = cpItemArrayFreq[i];
                headCount++;
        }
        else
        {
            
                cleanTailItems[tailCount] = cpItemArray[i];
                tailCount++;
                
        }
    }
    int ftFactor = 0; 
    if ( f_ft_Factor == -1 )
        ftFactor = (ItemsetArraySize-countMatching);
    else
        ftFactor = f_ft_Factor;
    

    
    
  
    
    generate_FT_FP_Branch(tempFT_HashTable,ftRoot,cleanTailItems,tailCount,cpFreq,cleanHeadItems,headCount,ftFactor,cleanHeadItemsFreq);

    
    free (cleanTailItems);
    free (cleanHeadItems);
    free (cleanHeadItemsFreq);
}


int IsFT_Transactions(int *conditionalPattern,int cpCount,int *headItems,int headCount)
{
    int ft_Count = 0;
   // printf("\nhead.....%d...\n",headItems[headCount-1]);
    for ( int i = headCount-1; i < headCount; i++ )
    {
        for ( int j = 0; j < cpCount; j++ )
        {
            if ( conditionalPattern[j] == headItems[i])
            {
                ft_Count++;
                break;
                
            }
        }
    }
    
    if ( ft_Count > 0 )
        return 0;
    else
        return 1;
}

void traverseFT_FPTree(struct FT_FPHashLink *head)
{
    struct FT_FPHashLink *tempP;
    struct FT_FPTree *fpTreeTraverse;
    tempP = head;

    if ( head != NULL )
    {
      
        while(true)
        {
          
            fpTreeTraverse = tempP->node;
            if ( fpTreeTraverse != NULL)
            {

                    printf("\nPrinting FT Table");
                    printf("\nNode = %d,  freq = %d",fpTreeTraverse->item,fpTreeTraverse->freq);
                    for ( int i = 0; i < 2; i++)
                    {
                        printf("\nft factor = %d,   freq=%d,        ",i,fpTreeTraverse->nodeFtTable[i].freq);
                        struct FT_FPTableItems *tempI;
                        tempI = fpTreeTraverse->nodeFtTable[i].head;
                        if ( tempI != NULL )
                        {
                            while (true)
                            {
                                printf("%d(%d),",tempI->item,tempI->freq);
                                if ( tempI->next == NULL )
                                    break;
                                tempI = tempI->next;
                            }
                        }
                    }
            }
            
            if ( tempP->next == NULL )
                break;
            
            tempP = tempP->next;
        }
    }
    
}


void delete_FT_HashTable(struct FT_FPHashLink *head)
{
    struct FT_FPHashLink *tempP, *deleteTemp;
    struct FT_FPTree *fpTreeTraverse,*parentTraverse,*tempParent;
    tempP = head;
   

    if ( head != NULL )
    {
      
        while(true)
        {
          
            fpTreeTraverse = tempP->node;
            if ( fpTreeTraverse != NULL)
            {

  //                  printf("\nPrinting FT Table\n");
    //                printf("\nNode = %d,  freq = %d\n",fpTreeTraverse->item,fpTreeTraverse->freq);
                    if ( fpTreeTraverse->nodeFtTable != NULL )
                    {
                            for ( int i = 0; i < (g_FTFactor+1); i++)
                            {
      //                          printf("\nft factor = %d,   freq=%d,        \n",i,fpTreeTraverse->nodeFtTable[i].freq);
                                struct FT_FPTableItems *tempI,*delete_tempI;

                                tempI = fpTreeTraverse->nodeFtTable[i].head;
                                if ( tempI != NULL )
                                {
                                    while (true)
                                    {
        //                                printf("%d(%d),",tempI->item,tempI->freq);
                                        if ( tempI->next == NULL )
                                        {
                                            deallocate_FT_FPTableItems(tempI);
                                            break;
                                        }

                                        delete_tempI = tempI;
                                        tempI = tempI->next;
                                        
                                       // free (delete_tempI);
                                        deallocate_FT_FPTableItems(delete_tempI);
                                    }
                                }

                            }
                    
                            //free (fpTreeTraverse->nodeFtTable);
                            deallocate_FT_FPTable(fpTreeTraverse->nodeFtTable);
                    }
                    
                      
                            
                            
                            
             
            }
            
            if ( tempP->next == NULL )
                break;
            
            deleteTemp = tempP;
            tempP = tempP->next;
            
            if ( deleteTemp != NULL )
            free (deleteTemp);
        }
    }

    
}
void Merge_FT_Tables (struct FT_FPTable *parent, struct FT_FPTable *child)
{
        
    struct FT_FPTableItems *tempI,*tempY,*tempP;
    for ( int i = 0; i < 2; i++)
    {
        
        tempI = child[i].head;
        if ( tempI != NULL )
        {
             while (true)
             {
                        int found = 0;
                        tempY = parent[i].head;
                        if ( tempY != NULL )
                        {
                            while (true)
                            {
                                        if ( tempY->item == tempI->item )
                                        {
                                            tempI->freq += tempY->freq;
                                            found = 1;
                                            break;
                                        }
                                        if ( tempY->next == NULL )
                                                break;
                                        tempY = tempY->next;
                            }
                        }
                        if ( found == 0 )
                        {
                                    if ( tempY == NULL )
                                     {

                                        // tempP = (struct FT_FPTableItems *)malloc(sizeof(struct FT_FPTableItems));
                                         tempP = allocate_FT_FPTableItems();
                                         tempP->item = tempI->item;
                                         tempP->freq = tempI->freq;
                                         tempP->next = NULL;
                                         parent[i].head = tempP;
 
                                     }
                                     else
                                     {
                                        // tempP = (struct FT_FPTableItems *)malloc(sizeof(struct FT_FPTableItems));
                                         tempP = allocate_FT_FPTableItems();
                                         tempP->item = tempI->item;
                                         tempP->freq = tempI->freq;
                                         tempP->next = parent[i].head;
                                         parent[i].head = tempP;
                                     }
                                 
                        }
                        
                 
                 
                        if ( tempI->next == NULL )
                                 break;
                        tempI = tempI->next;
             }
   
        }
    }
}

void trimLeavesCurrentTree(struct FT_FPHashLink *head, int TItem)
{
        struct FT_FPHashLink *tempP,*lastP,*deleteSave,*futureP;
        struct FT_FPTree *fpTreeTraverse,*parentNode,*nextNode;
        
        
    //    printf("\n hello 1\n");
        
        lastP = NULL;
        tempP = head;
        if ( head != NULL )
        {                        
                while(true)
                {

                            fpTreeTraverse = tempP->node;
                            if ( fpTreeTraverse!= NULL)
                            {
                            

                                      if ( fpTreeTraverse->item == TItem)
                                      {
                                          
                                                if ( fpTreeTraverse->parent != NULL )
                                                {
                                                    parentNode = fpTreeTraverse->parent;
                                                    if ( parentNode->nodeFtTable == NULL )
                                                    {
                                                            parentNode->nodeFtTable = fpTreeTraverse->nodeFtTable;
                                                            parentNode->freq = fpTreeTraverse->freq;
                                                            tempP->node = parentNode;

                                                    }                                    
                                                    else if ( parentNode->nodeFtTable != NULL )
                                                    {
                                                            Merge_FT_Tables (fpTreeTraverse->nodeFtTable, parentNode->nodeFtTable);
                                                            for ( int i = 0; i < (g_FTFactor+1); i++ )
                                                            {
                                                                if (fpTreeTraverse->nodeFtTable[i].head != NULL)
                                                                       parentNode->nodeFtTable[i].freq += fpTreeTraverse->nodeFtTable[i].freq;
                                                            }
                                                            
                                          //                  free (fpTreeTraverse->nodeFtTable);
                                                            
                                                    }

                                                }
                                                
                                          
                                            /*    if ( fpTreeTraverse->childNext == NULL )
                                                {
                                                    fpTreeTraverse = NULL;
                                                 //   free (fpTreeTraverse);
                                                //    exit(1);
                                                    
                                                }
                                                else if ( fpTreeTraverse->childNext != NULL )
                                                {
                                                    nextNode = fpTreeTraverse->childNext;
                                                    fpTreeTraverse->childHead = nextNode->childHead;
                                                    fpTreeTraverse->childNext = nextNode->childNext;
                                                    fpTreeTraverse->freq = nextNode->freq;
                                                    fpTreeTraverse->item = nextNode->item;
                                                    fpTreeTraverse->leaveFreq = nextNode->leaveFreq;
                                                    fpTreeTraverse->nodeFtTable = nextNode->nodeFtTable;
                                                    fpTreeTraverse->parent = nextNode->parent;
                                                    
                                                    
                                                    free (nextNode);
                                                   // exit(1);
                                                    
                                                }*/
                                          
                                          
                                      }

                            }
                     
                        
                            int isDelete = 0;
                            int deleteCase = 0;
                            if ( fpTreeTraverse!= NULL)
                            {
                            
                                parentNode = fpTreeTraverse->parent;
                                if ( fpTreeTraverse->item == TItem && parentNode->nodeFtTable != NULL )
                                {
                                            deleteCase = 1;
                                            deleteSave = NULL;
                                            if ( lastP != NULL )
                                            {
                                                lastP->next = tempP->next;
                                                deleteSave = tempP;
                                                isDelete = 1;

                                            }
                                            else if ( lastP == NULL)
                                            {

                                                futureP = tempP->next;
                                                if ( futureP != NULL )
                                                {
                                                    tempP->node = futureP->node;
                                                    tempP->next = futureP->next;           
                                                }

                                                deleteSave = futureP;
                                                isDelete = 2;

                                            }
                                }
                            }

                            


                            if ( tempP->next == NULL )
                                break;

                            if ( isDelete != 1)
                                lastP = tempP;
                            
                            tempP = tempP->next;
                            
                            if ( deleteSave != NULL && deleteCase == 1)
                            {
                                free (deleteSave);
                               // exit(1);
                            }
                }
         }
 
     //   printf("\n hello 2\n");

}
void WriteItemsetsInFile()
{
    //printf("\n%d...\n",stringOutPutCount);
    for ( int i = 0; i < stringOutPutCount; i++ )
    {
        fprintf(fpoutt,"%s",stringOutPut[i]);
    }
    
}

void minedFT_FPTree(struct FT_FPHashLink *head, int *tailItems, int tailCount, int *headItems, int headCount)
{
    struct FT_FPHashLink *tempP;
    struct FT_FPTree *fpTreeTraverse,*parentTraverse;
    int conditionalPattern[300];
    int conditionalPatternFreq[300];
    int cpCount = 0;
    int cpFreq = 0; 
    int *tailItemsArray;
    long tailItemsCount;
    
    
    int ItemsetSupport = 0;
    FT_FPTree *tempFT_FPTree;
    struct FT_FPHashLink *tempFT_HashTable;
    

             
    tailItemsCount = 0;
    
    
    for ( int i = 0; i < tailCount; i ++ )
    {
            tempFT_HashTable = NULL;
            tempFT_FPTree = NULL;    

            tempFT_HashTable = (struct FT_FPHashLink *)malloc(sizeof(struct FT_FPHashLink));
            tempFT_HashTable->node = NULL;
            tempFT_HashTable->next = NULL;


            tempFT_FPTree = (struct FT_FPTree *)malloc(sizeof(struct FT_FPTree));
            tempFT_FPTree->childHead = NULL;
            tempFT_FPTree->childNext = NULL;
            tempFT_FPTree->parent = NULL;
            tempFT_FPTree->item = -1;
            tempFT_FPTree->freq = -1;
            tempFT_FPTree->nodeFtTable = NULL;
    
    
    
    
        
            ItemsetSupport = 0;
            tempP = head;
            if ( head != NULL )
            {

                headItems[headCount] = tailItems[i];                

                
                while(true)
                {

                    fpTreeTraverse = tempP->node;
                    cpCount = 0;
                    cpFreq = 0;
                    if ( fpTreeTraverse != NULL)
                    {

                         //   printf("\nPrinting FT Table");
                         //   printf("\nNode = %d,  freq = %d",fpTreeTraverse->item,fpTreeTraverse->freq);
                                         int minedTail = 0;
                                         for (int k = 0; k <= headCount; k++ )
                                         {
                                                if ( fpTreeTraverse->item < headItems[k] && minedTail == 0)
                                                {
                                                         minedTail = 1;
                                                }

                                                if ( fpTreeTraverse->item == headItems[k])
                                                         minedTail = 2;
                                         }    
                                            
                            
                                         if ( minedTail == 0 || minedTail == 2 )
                                         {
                                             //    if ( gCPAge[fpTreeTraverse->item] != gAge )
                                                 {
                                                    //     gCPFreq[fpTreeTraverse->item] = fpTreeTraverse->leaveFreq;
                                               //          gCPAge[fpTreeTraverse->item] = gAge;
                                                         if ( minedTail != 2 )
                                                                tailItemsCount++;
                                                       
                                                 }
                                                 //else
                                                 {
                                                      //   gCPFreq[fpTreeTraverse->item]+= fpTreeTraverse->leaveFreq;
                                                 }
                                                 conditionalPattern[cpCount] = fpTreeTraverse->item;
                                                 conditionalPatternFreq[cpCount] = fpTreeTraverse->freq;
                                                 cpCount++;
                                                 
                                               
                                                
                                                 
                                                    
                                         }
                                   
                                   
                                   
                                   
                                   
                      
                      
                            
                            
                            
                            
                            parentTraverse = fpTreeTraverse->parent;
                            if ( parentTraverse != NULL )
                            {
                                while(true)
                                {
                                    
                                   int minedTail = 0;
                                   for (int k = 0; k <= headCount; k++ )
                                   {
                                       
                                         if ( parentTraverse->item < headItems[k] && minedTail == 0)
                                         {
                                                  minedTail = 1;
                                         }
                                        

                                         
                                         if ( parentTraverse->item == headItems[k])
                                                  minedTail = 2;
                                   }      
                                                
                            
                                         if ( minedTail == 0 || minedTail == 2 )
                                         {
                                            //     if ( gCPAge[parentTraverse->item] != gAge )
                                                 {
                                                     
                                                        // gCPFreq[parentTraverse->item] = fpTreeTraverse->leaveFreq;
                                             //            gCPAge[parentTraverse->item] = gAge;
                                                         
                                                         if ( minedTail != 2 )
                                                                tailItemsCount++;
                                                       
                                                 }
                                                // else
                                                 {
                                                     
                                                          //gCPFreq[parentTraverse->item]+=fpTreeTraverse->leaveFreq;
                                                          
                                                 }   
                                                 
                                                 conditionalPattern[cpCount] = parentTraverse->item;
                                                 conditionalPatternFreq[cpCount] = fpTreeTraverse->freq;
                                                 
                                                 cpCount++;   
                                          
                                                    
                                         }
                                   
                                    
                                                                               
                                                                                  
                                    if ( parentTraverse->parent == NULL )
                                    {
                                        break;
                                    }
                                    parentTraverse = parentTraverse->parent;
                                    
                                }
                            }
                            
                            
                         //   printf("\n hello 35 \n");
                            
                            
                            
                            
                            
                            
                            
                            
                            
                            
                            
                            
                            
                            
                                    int Freeze = cpCount;
                                    int ccS = 0;
                            
                            
                                    for ( int i = 0; i < (g_FTFactor+1); i++)
                                    {
                                         //   printf("\nft factor = %d,   freq=%d,        ",i,fpTreeTraverse->nodeFtTable[i].freq);
                                            struct FT_FPTableItems *tempI;
                                            tempI = fpTreeTraverse->nodeFtTable[i].head;
                                            if ( tempI != NULL )
                                            {
                                                    while (true)
                                                    {
                                            //            printf("%d(%d),",tempI->item,tempI->freq);
                                                        
                                                        int minedTail = 0;
                                                        for (int k = 0; k <= headCount; k++ )
                                                        {
                                                              if ( tempI->item < headItems[k] && minedTail == 0)
                                                              {
                                                                       minedTail = 1;
                                                              }

                                                              if ( tempI->item == headItems[k])
                                                                       minedTail = 2;
                                                        }


                                                              if ( minedTail == 0 || minedTail == 2 )
                                                              {
                                                                        conditionalPattern[cpCount] = tempI->item;
                                                                        conditionalPatternFreq[cpCount] = tempI->freq;
                                                                        ccS += tempI->freq;
                                                                        cpCount++;
                                                                        
                                                                        
                                                         //               if ( gCPAge[tempI->item] != gAge )
                                                                        {
                                                                              //  gCPFreq[tempI->item] = tempI->freq;
                                                           //                     gCPAge[tempI->item] = gAge;
                                                                        }
                                                             //           else
                                                                        {
                                                                            //    gCPFreq[tempI->item] += tempI->freq;  
                                                                        }

                                                                        
                                                              }
                                                        
                                                                                           
                                                                                           
                                                        if ( tempI->next == NULL )
                                                            break;
                                                        tempI = tempI->next;
                                                    }
                                            
                                            
                                            
                                                    if ( cpCount > 0 )
                                                    {
                                                //        printf("\n...Conditional Pattern = ");
                                                     //   for ( int i = 0; i < cpCount; i ++ )
                                                        {
                                                  //          printf("%d,",conditionalPattern[i]);
                                                        }
                                                    //    printf("\n");
                                                    }
                                                    int ft_Fact = IsFT_Transactions(conditionalPattern,cpCount,headItems,headCount+1);
                                                    ft_Fact = ft_Fact + i;
                                              //      printf("\n...ft factor = %d....%d",ft_Fact,i);
                                                    if ( ft_Fact < (g_FTFactor+1) )
                                                    {
                                                        ItemsetSupport+=fpTreeTraverse->nodeFtTable[i].freq;
                                                        for ( int kk = 0; kk < cpCount; kk ++ )
                                                        {
                                                              if ( gCPAge[conditionalPattern[kk]] != gAge ) 
                                                              {
                                                                        gCPFreq[conditionalPattern[kk]] = conditionalPatternFreq[kk];
                                                                        gCPAge[conditionalPattern[kk]] = gAge;
                                                              }
                                                              else
                                                              {
                                                                        gCPFreq[conditionalPattern[kk]] += conditionalPatternFreq[kk];
                                                              }
                                                        }
                                                        
                                                        //if ( headItems[0] == 12 && headItems[1] == 14 && headItems[2] == 15)
                                                          //  printf("\nsupport = %d..%d....%d\n",ItemsetSupport,fpTreeTraverse->nodeFtTable[i].freq,fpTreeTraverse->item);
                                                            
                                                    }
                                                    
                                                    
                                                    cpCount = Freeze;
                                            }
                                            
                                            
                                            
                                            
                                    }
                           
                            
                            
                            
                            
                    }

                    
                    
                    
                    

                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
          

                                       
                                       
                    
                    
                    if ( tempP->next == NULL )
                        break;

                    tempP = tempP->next;
                }
            }
            
            
            
            if ( ItemsetSupport >= gItemsetSupport )
            {
                
                            for ( int z1 = 0; z1 <= headCount; z1++ )
                            {
                                if ( gCPFreq[headItems[z1]] < gItemSupport )
                                    return;
                                
                                if ( gCPAge[headItems[z1]] != gAge )
                                    return;
                                
                            //    printf("\n%d..............%d",gCPFreq[headItems[z1]],headItems[z1]);
                            }
                                
                  
                  
                  
                            gAge++;
                            gTotalFTFrequentItemsets++;
                            
                        //    if ( headCount >= 3500 )
                            {
                               //     printf("\nItemset (");
                 
                                    
                
                                    
                                    char scat[90];
                                    strcpy(stringOutPut[stringOutPutCount],"(");
                                    for ( int z1 = 0; z1 <= headCount; z1++)
                                    {
                                        sprintf(scat,"%d,",headItems[z1]);
                                        strcat(stringOutPut[stringOutPutCount],scat);
                                    }
                                    sprintf(scat,") is frequent\n");
                                    strcat(stringOutPut[stringOutPutCount],scat);

                                    stringOutPutCount++;                                    


                                    
                                    
                                    if ( stringOutPutCount == 1998 )
                                    {
                                        WriteItemsetsInFile();
                                        stringOutPutCount = 0;
                                    }
                                    
                            }
                            
                            
                            
                            tailItemsArray = (int *)malloc(tailItemsCount*sizeof(int));
                            tailItemsCount = 0;
                
                
                            ItemsetSupport = 0;
                            tempP = head;
                            if ( head != NULL )
                            {

                                headItems[headCount] = tailItems[i];                


                                while(true)
                                {

                                    fpTreeTraverse = tempP->node;
                                    cpCount = 0;
                                    cpFreq = 0;
                                    if ( fpTreeTraverse != NULL)
                                    {

                                       //     printf("\nPrinting FT Table");
                                       //     printf("\nNode = %d,  freq = %d",fpTreeTraverse->item,fpTreeTraverse->freq);
                                                   int minedTail = 0;
                                                   for (int k = 0; k <= headCount; k++ )
                                                   {
                                                         if ( fpTreeTraverse->item < headItems[k] && minedTail == 0)
                                                         {
                                                                  minedTail = 1;
                                                         }

                                                         if ( fpTreeTraverse->item == headItems[k])
                                                                  minedTail = 2;
                                                   }    


                                                         if ( (minedTail == 0 || minedTail == 2) && gCPFreq[fpTreeTraverse->item] >= gItemSupport)
                                                         {
                                                                 conditionalPattern[cpCount] = fpTreeTraverse->item;
                                                                 conditionalPatternFreq[cpCount] = fpTreeTraverse->leaveFreq;
                                                             //    printf("\n%d...%d\n",fpTreeTraverse->item,fpTreeTraverse->leaveFreq);

                                                                 cpCount++;
                                                                 
                                                                 if ( minedTail != 2)
                                                                 {
                                                                     if ( gCPAgeTail[fpTreeTraverse->item] != gAge )
                                                                     {
                                                                         gCPAgeTail[fpTreeTraverse->item] = gAge;
                                                                         tailItemsArray[tailItemsCount] = fpTreeTraverse->item;
                                                                         tailItemsCount++;
                                                                     }
                                                                 }

                                                         }











                                                 
                                            parentTraverse = fpTreeTraverse->parent;
                                            if ( parentTraverse != NULL )
                                            {
                                                while(true)
                                                {

                                                   int minedTail = 0;
                                                   for (int k = 0; k <= headCount; k++ )
                                                   {
                                                         if ( parentTraverse->item < headItems[k] && minedTail == 0)
                                                         {
                                                                  minedTail = 1;
                                                         }

                                                         if ( parentTraverse->item == headItems[k])
                                                                  minedTail = 2;
                                                   }      


                                                         if ( (minedTail == 0 || minedTail == 2) && gCPFreq[parentTraverse->item] >= gItemSupport )
                                                         {
                                                                 conditionalPattern[cpCount] = parentTraverse->item;
                                                                 conditionalPatternFreq[cpCount] = fpTreeTraverse->leaveFreq;
                                                                 cpCount++;       
                                                                 if ( minedTail != 2)
                                                                 {
                                                                     if ( gCPAgeTail[parentTraverse->item] != gAge )
                                                                     {
                                                                         gCPAgeTail[parentTraverse->item] = gAge;
                                                                         tailItemsArray[tailItemsCount] = parentTraverse->item;
                                                                         tailItemsCount++;
                                                                     }
                                                                 }

                                                         }




                                                    if ( parentTraverse->parent == NULL )
                                                    {
                                                        break;
                                                    }
                                                    parentTraverse = parentTraverse->parent;
                                                }
                                            }














                                            


                                                    int Freeze = cpCount;


                                                    for ( int i = 0; i < (g_FTFactor+1); i++)
                                                    {
                                                        
                                                           // printf("\nft factor = %d,   freq=%d,        ",i,fpTreeTraverse->nodeFtTable[i].freq);
                                                            
                                                            struct FT_FPTableItems *tempI;
                                                            tempI = fpTreeTraverse->nodeFtTable[i].head;
                                                            if ( tempI != NULL )
                                                            {
                                                                    while (true)
                                                                    {
                                                                   //     printf("%d(%d),",tempI->item,tempI->freq);
                                                                        

                                                                        int minedTail = 0;
                                                                        for (int k = 0; k <= headCount; k++ )
                                                                        {
                                                                              if ( tempI->item < headItems[k] && minedTail == 0)
                                                                              {
                                                                                       minedTail = 1;
                                                                              }

                                                                              if ( tempI->item == headItems[k])
                                                                                       minedTail = 2;
                                                                        }


                                                                              if ( minedTail == 0 || minedTail == 2 )
                                                                              {
                                                                                        conditionalPattern[cpCount] = tempI->item;
                                                                                        conditionalPatternFreq[cpCount] = tempI->freq;
                                                                                        cpCount++;

                                                                              }



                                                                        if ( tempI->next == NULL )
                                                                            break;
                                                                        tempI = tempI->next;
                                                                    }



                                                                    if ( cpCount > 0 )
                                                                    {
                                                                  //      printf("\nConditional Pattern = ");
                                                                    //    for ( int i = 0; i < cpCount; i ++ )
                                                                        {
                                                                    //        printf("%d (%d),",conditionalPattern[i],conditionalPatternFreq[i]);
                                                                        }
                                                                      //  printf("\n");
                                                                    }
                                                                    
                                                                    int ft_Fact = IsFT_Transactions(conditionalPattern,cpCount,headItems,headCount+1);
                                                                    ft_Fact = ft_Fact + i;
                                                                    //printf("\n... ft factor = %d",ft_Fact);
                                                                    if ( ft_Fact < (g_FTFactor+1) )
                                                                    {
                                                                     //   ItemsetSupport+=tempP->node->freq;
                                                                        ItemsetSupport+=fpTreeTraverse->nodeFtTable[i].freq;
                                                                        
                                                                        InsertIntoFT_FPTree(tempFT_HashTable,tempFT_FPTree,conditionalPattern,cpCount,tempP->node->freq,headItems,headCount+1,conditionalPatternFreq,ft_Fact);
                                                                        
                                                                        
                                                                    }


                                                                    cpCount = Freeze;
                                                            }




                                                    }





                                    }

























                                    if ( tempP->next == NULL )
                                        break;

                                    tempP = tempP->next;
                                }
                            }
            
            
            
           
                           // printf("\n Tail items = %d\n",tailItemsCount);
                            if ( tailItemsCount >= 1 )
                            {
                                    quickSort(tailItemsArray,0,(tailItemsCount-1));
                                  //  for ( int z = 0; z < tailItemsCount; z++)
                                    {
                                    //    printf("\n Tail item = %d",tailItemsArray[z]);
                                    }
                                    gAge++;
                                    
                                    minedFT_FPTree(tempFT_HashTable,tailItemsArray,tailItemsCount,headItems,headCount+1);
                                    delete_FT_HashTable(tempFT_HashTable);
                                    delete_FT_FPTree(tempFT_FPTree,0);
                                    
                                    
                                    trimLeavesCurrentTree(head,tailItems[i]);
                                    free (tailItemsArray);
                            }
            
            
            }
            
        //    exit(1);
            
       //     printf("\nTraversing FT Tree\n");
            
       //     traverseFT_FPTree(tempFT_HashTable);
         //   break;
    }
    
}



void printFT_FPTree(struct FT_FPTree *fpTempRoot,int level)
{
    struct FT_FPTree *fpTreeTraverse;
   // printf("\nprinting\n");
    

    fpTreeTraverse = fpTempRoot;
    if ( fpTreeTraverse->nodeFtTable != NULL )
    {
        //exit(1);
        printf("\nPrinting FT Table");
        for ( int i = 0; i < 2; i++)
        {
            printf("\nft factor = %d,   freq=%d,        ",i,fpTreeTraverse->nodeFtTable[i].freq);
            struct FT_FPTableItems *tempI;
            tempI = fpTreeTraverse->nodeFtTable[i].head;
            if ( tempI != NULL )
            {
                while (true)
                {
                    printf("%d(%d),",tempI->item,tempI->freq);
                    if ( tempI->next == NULL )
                        break;
                    tempI = tempI->next;
                }
            }
        }
        
    }
    
    fpTreeTraverse = fpTempRoot->childHead;
    
    if ( fpTreeTraverse != NULL )
    {
                    while(true)
                    {
                            printf("printing...%d...%d ",fpTreeTraverse->item, level );
                           /* if ( fpTreeTraverse->nodeFtTable != NULL )
                            {
                                    printf("\nPrinting FT Table");
                                    for ( int i = 0; i < 2; i++)
                                    {
                                        printf("\nft factor = %d,   freq=%d,        ",i,fpTreeTraverse->nodeFtTable[i].freq);
                                        struct FT_FPTableItems *tempI;
                                        tempI = fpTreeTraverse->nodeFtTable[i].head;
                                        if ( tempI != NULL )
                                        {
                                            while (true)
                                            {
                                                printf("%d(%d),",tempI->item,tempI->freq);
                                                if ( tempI->next == NULL )
                                                    break;
                                                tempI = tempI->next;
                                            }
                                        }
                                    }

                            }*/
                            printFT_FPTree(fpTreeTraverse,(level+1));
                            
                            if ( fpTreeTraverse->childNext == NULL )
                                break;

                            fpTreeTraverse = fpTreeTraverse->childNext;
                    }
    }
            
}


void printFPTreeBranch(struct FPTree *node)
{
    struct FPTree *fpTreeTraverse;
    printf("\n FP Branch Printing \n");

    fpTreeTraverse = node;
    if ( fpTreeTraverse != NULL )
    {
                    while(true)
                    {
                            printf("\nFP branch...freq = %d... item = %d ",fpTreeTraverse->freq, fpTreeTraverse->item );
                            
                            
                            if ( fpTreeTraverse->parent == NULL )
                                break;

                            fpTreeTraverse = fpTreeTraverse->parent;
                    }
    }    
}



void printHashTable(int Item)
{
    struct FPHashTable *tempP;
    tempP = fpHashRoot[Item];
    if ( tempP != NULL )
    {
        while(true)
        {
            printf("\n Hash freq = %d, Item = %d",tempP->freq, tempP->treeNode->item);
            printFPTreeBranch(tempP->treeNode);
                    
            if ( tempP->next == NULL )
                break;
            
            tempP = tempP->next;
        }
    }
}









void generateConditionalPatterns(int *Itemset, int size)
{
    struct FPHashTable *tempP;
    struct FPTree *fpTreeTraverse;
    int conditionalPattern[300];
    int conditionalPatternFreq[300];
    int cpCount = 0;
    int cpFreq = 0;
    int *tailItemsArray;
    long tailItemsCount = 0;
    int anyTailItem = 0;
    
    FT_FPTree *tempFT_FPTree;
    struct FT_FPHashLink *tempFT_HashTable;
    
    tempFT_HashTable = NULL;
    tempFT_FPTree = NULL;    
    
    tempFT_HashTable = (struct FT_FPHashLink *)malloc(sizeof(struct FT_FPHashLink));
    tempFT_HashTable->node = NULL;
    tempFT_HashTable->next = NULL;
    
    

    
    tempFT_FPTree = (struct FT_FPTree *)malloc(sizeof(struct FT_FPTree));
    tempFT_FPTree->childHead = NULL;
    tempFT_FPTree->childNext = NULL;
    tempFT_FPTree->parent = NULL;
    tempFT_FPTree->item = -1;
    tempFT_FPTree->freq = -1;
    tempFT_FPTree->nodeFtTable = NULL;
         
    
    
    int localItemsetSupport = 0;
    
    
    for ( int i = 0; i < size; i++ )
    {
            tempP = fpHashRoot[Itemset[i]];
            
            if ( tempP != NULL )
            {   
           //     printf("\n %d \n",Itemset[i]);
           //     printf("\n%d........%d",tempP->treeNode->Age,tempP->treeNode->leaveFreq);
                
            
                
                    
               
                        while(true)
                        {

                            
                                    fpTreeTraverse = tempP->treeNode;
                                    cpCount = 0;
                                    
                                    

                                    if ( fpTreeTraverse != NULL && (tempP->treeNode->Age != gAge || tempP->treeNode->freq > tempP->treeNode->leaveFreq ) )
                                    {

                                             if (tempP->treeNode->Age != gAge)
                                                     cpFreq = fpTreeTraverse->freq;
                                             else
                                                     cpFreq = (fpTreeTraverse->freq-fpTreeTraverse->leaveFreq);


                                             localItemsetSupport += cpFreq;
                                             while(true)
                                             {
                                                    // printf("\nFP branch...freq = %d... item = %d ",fpTreeTraverse->freq, fpTreeTraverse->item );
                                                     int minedTail = 0;
                                                     for (int k = 0; k < size; k++ )
                                                     {
                                                         if ( fpTreeTraverse->item < Itemset[k] && minedTail == 0)
                                                         {
                                                             minedTail = 1;
                                                         }

                                                         if ( fpTreeTraverse->item == Itemset[k])
                                                             minedTail = 2;
                                                     }


                                                     if ( minedTail == 0 || minedTail == 2 )
                                                     {


                                                         conditionalPattern[cpCount] = fpTreeTraverse->item;
                                                         cpCount++;
                                                         if ( fpTreeTraverse->Age != gAge )
                                                         {

                                                              
                                                              if ( gCPAge[fpTreeTraverse->item] != gAge )
                                                              {
                                                                        gCPFreq[fpTreeTraverse->item] = cpFreq;
                                                                        gCPAge[fpTreeTraverse->item] = gAge;         
                                                                        tailItemsCount++;
                                                                        
                                                                        if ( gCPFreq[fpTreeTraverse->item] >= gItemSupport && minedTail != 2)
                                                                            anyTailItem++;
                                                              }
                                                              else
                                                              {
                                                                        gCPFreq[fpTreeTraverse->item] += cpFreq;
                                                                        
                                                                        if ( gCPFreq[fpTreeTraverse->item] >= gItemSupport && minedTail != 2)
                                                                            anyTailItem++;                                                                        
                                                              }
                                                              
                                                              
                                                              fpTreeTraverse->leaveFreq = cpFreq;
                                                         }
                                                         else
                                                         {
                                                              fpTreeTraverse->leaveFreq += cpFreq;
                                                              gCPFreq[fpTreeTraverse->item] += cpFreq;
                                                         }
                                                     }
                                                     fpTreeTraverse->Age = gAge;

                                                     if ( fpTreeTraverse->parent == NULL || fpTreeTraverse->parent->item == -1 )
                                                         break;

                                                     fpTreeTraverse = fpTreeTraverse->parent;
                                             }
                                     //       printf("\nConditional Pattern size = %d,   freq = %d\n",cpCount,cpFreq);
                                       //     for ( int j = 0; j < cpCount; j++ )
                                         //   {
                                       //           printf("%d,",conditionalPattern[j]);
                                           // }
                                         //   printf("\n");

                                          //  InsertIntoFT_FPTree(tempFT_FPTree,conditionalPattern,cpCount,cpFreq,Itemset,size);



                               }                    

                               if ( tempP->next == NULL )
                                    break;

                               tempP = tempP->next;
                         }
                }
         //   break;
            
    }
    
    
   // printf("\n totoal iterations %d\n",size);
   
   // printf("\n total tail items = %d\n",tailItemsCount);
    
    if ( localItemsetSupport >= gItemsetSupport )
    {
   //     printf("\n itemset (");
         char scat[90];
         strcpy(stringOutPut[stringOutPutCount],"(");
         for ( int z = 0; z < size; z++)
         {
             sprintf(scat,"%d,",Itemset[z]);
             strcat(stringOutPut[stringOutPutCount],scat);
         }
         sprintf(scat,") is frequent\n",);
         strcat(stringOutPut[stringOutPutCount],scat);
        
         stringOutPutCount++;
         gTotalFTFrequentItemsets++;
         if ( stringOutPutCount == 1998 )
         {
              WriteItemsetsInFile();
              stringOutPutCount = 0;
         }
        
        
        
    }
    else
    {
        
        return;
    }
    
    if ( anyTailItem == 0 )
        return;
    
    
    
    
    gAge++;
  
    tailItemsArray = (int *)malloc(tailItemsCount*sizeof(int));
    tailItemsCount = 0;
    
   
    for ( int i = 0; i < size; i++ )
    {
            tempP = fpHashRoot[Itemset[i]];
            if ( tempP != NULL )
            {
                //printf("\n%d........%d",tempP->treeNode->Age,tempP->treeNode->leaveFreq);
                
           
                    
               
                        while(true)
                        {
                              // printf("\n Hash freq = %d, Item = %d",tempP->freq, tempP->treeNode->item);
                               fpTreeTraverse = tempP->treeNode;
                               cpCount = 0;

                                    if ( fpTreeTraverse != NULL && (tempP->treeNode->Age != gAge || tempP->treeNode->freq > tempP->treeNode->leaveFreq ) )
                                    {

                                             if (tempP->treeNode->Age != gAge)
                                                     cpFreq = fpTreeTraverse->freq;
                                             else
                                                     cpFreq = (fpTreeTraverse->freq-fpTreeTraverse->leaveFreq);


                                             localItemsetSupport += cpFreq;
                                             while(true)
                                             {
                                                    // printf("\nFP branch...freq = %d... item = %d ",fpTreeTraverse->freq, fpTreeTraverse->item );
                                                     int minedTail = 0;
                                                     for (int k = 0; k < size; k++ )
                                                     {
                                                         if ( fpTreeTraverse->item < Itemset[k] && minedTail == 0)
                                                         {
                                                             minedTail = 1;
                                                         }

                                                         if ( fpTreeTraverse->item == Itemset[k])
                                                             minedTail = 2;
                                                     }


                                                     if ( minedTail == 0 || minedTail == 2 )
                                                     {


                                                   //      printf("\n%d....%d...%d\n",gCPFreq[fpTreeTraverse->item],gItemSupport,fpTreeTraverse->item);
                                                         if ( gCPFreq[fpTreeTraverse->item] >= gItemSupport )
                                                         {
                                                                conditionalPattern[cpCount] = fpTreeTraverse->item;
                                                                conditionalPatternFreq[cpCount] = cpFreq;
                                                                cpCount++;
                                                         }
                                                         
                                                         if ( fpTreeTraverse->Age != gAge )
                                                         {

                                                              if ( gCPAge[fpTreeTraverse->item] != gAge )
                                                              {
                                                                        //gCPFreq[fpTreeTraverse->item] = cpFreq;
                                                                        if ( minedTail != 2 && gCPFreq[fpTreeTraverse->item] >= gItemSupport )
                                                                        {
                                                                              tailItemsArray[tailItemsCount] = fpTreeTraverse->item;
                                                                              gCPAge[fpTreeTraverse->item] = gAge;         
                                                                              tailItemsCount++;
                                                                        }
                                                              }
                                                    
                                                              
                                                              fpTreeTraverse->leaveFreq = cpFreq;
                                                         }
                                                         else
                                                         {
                                                              fpTreeTraverse->leaveFreq += cpFreq;
  
                                                         }
                                                     }
                                                     fpTreeTraverse->Age = gAge;

                                                     if ( fpTreeTraverse->parent == NULL || fpTreeTraverse->parent->item == -1 )
                                                         break;

                                                     fpTreeTraverse = fpTreeTraverse->parent;
                                             }
                                  //          printf("\nConditional Pattern size = %d,   freq = %d\n",cpCount,cpFreq);
                                    //        for ( int j = 0; j < cpCount; j++ )
                                              {
                                    //              printf("%d,",conditionalPattern[j]);
                                              }
                                      //      printf("\n");
                                            
                                            
                                            
                                            
                                           InsertIntoFT_FPTree(tempFT_HashTable,tempFT_FPTree,conditionalPattern,cpCount,cpFreq,Itemset,size,conditionalPatternFreq,-1);

                                           


                               }                    

                               if ( tempP->next == NULL )
                                    break;

                               tempP = tempP->next;
                         }
                
            }
    }
   
    
     
   // printFT_FPTree(tempFT_FPTree,0);
  //  traverseFT_FPTree(tempFT_HashTable);

    // minedFT_FPTree(tempFT_HashTable);
 //   printf("\ntail = %d....%d\n",tailItemsCount,anyTailItem);
    
    if ( tailItemsCount >= 1)
    {
            quickSort(tailItemsArray,0,(tailItemsCount-1));
         //   for ( int k = 0; k < tailItemsCount; k++)
            {
         //        printf("\n Tail Item %d         ",tailItemsArray[k]);
            }
            
            gAge++;
          
            minedFT_FPTree(tempFT_HashTable,tailItemsArray,tailItemsCount,Itemset,size );
            
            delete_FT_HashTable(tempFT_HashTable);
            delete_FT_FPTree(tempFT_FPTree,0);
            free (tailItemsArray);
    }
    
   // exit(1);
    

    
            
            
   // printf("\n");
}

void Insert4PairItem (struct threePairStruct *node, int item)
{
    if ( node->head == NULL )
    {
        struct threePairItem *itemNode;
        node->head = (struct threePairItem *)malloc(sizeof(struct threePairItem *));
        node->head->item = item;
        node->head->freq = 1;
        node->head->next = NULL;
    }
    else
    {
        struct threePairItem *sItem;
        sItem = node->head;
        int found = 0;
        while(1)
        {
            if ( sItem->item == item)
            {
                found = 1;
                sItem->freq++;
                break;
            }
            if (sItem->next == NULL)
                break;
            
            sItem = sItem->next;
            
            
            
        }
        if ( found == 0)
        {
            struct threePairItem *itemNode;
            itemNode = (struct threePairItem *)malloc(sizeof(struct threePairItem *));     
            itemNode->freq = 1;
            itemNode->item = item;
            itemNode->next = node->head;
            node->head = itemNode;
        }
    }
}

void InsertItemFPTree(int *ItemArray,int ItemCount)
{
    struct FPTree *fpTreeTemp,*fpTreeTraverse,*tempRoot,*tempFPNodeSave;
    int FoundFlag = 0;
    
    
    tempRoot = fpMainRoot;
    fpTreeTraverse = tempRoot->childHead;
    for ( int i = 0; i < ItemCount; i++ )
    {
       /* for ( int j = 0; j < ItemCount; j++ )
        {
         //   twoPair[ItemArray[i]][ItemArray[j]]++;
         //   twoPair[ItemArray[j]][ItemArray[i]]++;
            for ( int z = 0; z < ItemCount; z++ )
            {
                threePair[i][j][z].count++;
                for ( int k = 0; k < ItemCount; k++ )
                {
                    Insert4PairItem(&threePair[i][j][z],ItemArray[k]);
                }
            }
        }*/
        
            FoundFlag = -1;
            if ( fpTreeTraverse != NULL )
            {
                    while(true)
                    {
                            if ( fpTreeTraverse->item == ItemArray[i] )
                            {
                                FoundFlag = 1;
                                break;
                            }
                            if ( fpTreeTraverse->childNext == NULL )
                                break;

                            fpTreeTraverse = fpTreeTraverse->childNext;
                    }
                    if ( FoundFlag == 1 )
                    {
                            fpTreeTraverse->freq++;
                            if ( i == (ItemCount-1) )
                                fpTreeTraverse->leaveFreq++;
                            
                            tempRoot = fpTreeTraverse;
                            fpTreeTraverse = fpTreeTraverse->childHead;
                            fpHashRoot[ItemArray[i]]->freq++;
                            
         //                   printf("\ntree1 %d...%d",ItemArray[i],i);
                 
                    }
                    else
                    {
                            fpTreeTemp = (struct FPTree *)malloc(sizeof(struct FPTree));
                            fpTreeTemp->childHead = NULL;
                            fpTreeTemp->childNext = NULL;
                            fpTreeTemp->headTable = NULL;
                            fpTreeTemp->item = ItemArray[i];
                            fpTreeTemp->freq = 1;
                            fpTreeTemp->Age = -1;
                            if ( i == (ItemCount-1) )
                                fpTreeTemp->leaveFreq = 1;
                            
                            fpTreeTemp->parent = tempRoot;
                           // printf("\ntree2) %d...%d....%d",ItemArray[i],i,tempRoot->item);
                            InsertItemHashTable(ItemArray[i],fpTreeTemp);
                            
                            
                            tempFPNodeSave = tempRoot->childHead;
                            tempRoot->childHead = fpTreeTemp;
                            fpTreeTemp->childNext = tempFPNodeSave;
                            
                           // tempFPNodeSave = tempRoot;
                            tempRoot = fpTreeTemp;
                            fpTreeTraverse = fpTreeTemp->childHead;
                         
       //                     printf("\ntree2) %d...%d....%d",ItemArray[i],i,tempFPNodeSave->item);

                    }    
            }
            else
            {
                    fpTreeTemp = (struct FPTree *)malloc(sizeof(struct FPTree));
                    fpTreeTemp->childHead = NULL;
                    fpTreeTemp->childNext = NULL;
                    fpTreeTemp->headTable = NULL;
                    fpTreeTemp->item = ItemArray[i];
                    fpTreeTemp->freq = 1; 
                    fpTreeTemp->Age = -1;
                    if ( i == (ItemCount-1) )
                        fpTreeTemp->leaveFreq = 1;
                    fpTreeTemp->parent = tempRoot;
                    tempRoot->childHead = fpTreeTemp;
                    
                    
                    tempFPNodeSave = tempRoot;
                    tempRoot = fpTreeTemp;
                    fpTreeTraverse = fpTreeTemp->childHead;
                    
                    InsertItemHashTable(ItemArray[i],fpTreeTemp);
           //         printf("\ntree %d...%d....%d",ItemArray[i],i,tempFPNodeSave->item);
       //             if ( i == 1 )
         //               exit(1);
                    
            }

     
    }
    
    
  
        
    
    
    
    
}


void InsertTestItem (FT_FPTableItems *node, int data)
{
 

 
        FT_FPTableItems *temp;
        temp = (struct FT_FPTableItems *)malloc(sizeof(struct FT_FPTableItems));
        temp->item = data;
        temp->next = node->next;
        node->next = temp;        
        
   
}
void PrintTestItem (FT_FPTableItems *node)
{
    FT_FPTableItems *temp;
    temp = node;
    if ( temp != NULL)
    {
        while (true)
        {
            printf("\nTest item = %d",temp->item);
        
            if ( temp->next == NULL)
                break;
            
            temp = temp->next;
            
        }
    }
    else
    {
        printf("\n it is null \n");
    }
    
}

void RemoveTestItem(FT_FPTableItems *node)
{
    FT_FPTableItems *temp,*temp2;
    if ( node->next == NULL || node == NULL )
    {
        return;
    }
    
    printf("\n hello %d\n",node->item);
   
    temp = node->next;
    node->item = temp->item;
    node->next = temp->next;
    free (temp);
    
    
}

void DeleteTestItem (FT_FPTableItems *node)
{
    FT_FPTableItems *temp;
    temp = node;
    if ( temp != NULL)
    {
        while (true)
        {
            if ( temp->item == 4 )
                RemoveTestItem(temp);
        
            if ( temp->next == NULL)
                break;
            
            temp = temp->next;
            
        }
    }

    
}
void fastTailMining(int *head,int count, int tail)
{
    int tailSupport = 0;
    int totalTailItem = 0;
    for ( int i = (tail+1); i < No_Of_Frequent1_Items; i++ )
    {
        tailSupport = 0;
        for ( int j = 0; j < count; j++)
        {
            if ( i != head[j] )
              tailSupport += twoPair[i][ head[j] ];
        } 
        if ( tailSupport >= gItemSupport )
            totalTailItem++;
           
    }
    printf("\nTotal Tail Items = %d",totalTailItem);
    
}
int main(int argc, char *argv[])
{
  
 clock_t start_t, end_t, total_t;
 char *stopstring;
 printf("\n");
 printingflag = 0;
 char inputfilename[81];
 char outputfilename[81];
 DimentionSize = 0;
 Maxtransactionsize = 500;
 sprintf(inputfilename, "%s",argv[1]);
 support = strtol( argv[2], &stopstring, 10 );
 if (argc == 6)
	{
	printingflag = 1;
	sprintf(outputfilename, "%s",argv[3]);
	}
	
  start_t = clock();
  
  int itemsetFreqq = atoi(argv[4]);
  int ftFactor = atoi(argv[5]);


 //sprintf(inputfilename, "%s","chess.dat");
 //support = 1000;
	FPTTree* Current = new FPTTree;
	FPTTree* Father = new FPTTree;
	FPTTree* Root = new FPTTree;

	FPTTree* NewCurrent = new FPTTree;
	FPTTree* LastBrother = new FPTTree;
	

	
	for (int i=1;i<500;i++)
		DepthArray[i]=0;


  Candidate_Items = (CandidateStructures *)malloc((500+1)*sizeof(CandidateStructures));
  Trans.Items = (long *)malloc((Maxtransactionsize+1)*sizeof(long));
  TransactionArray = (TransactionRecord *)malloc((Maxtransactionsize+1)*sizeof(TransactionRecord));

  
  /*
  FT_FPTableItems *headTest;
  headTest = NULL;
  headTest = (struct FT_FPTableItems *)malloc(sizeof(struct FT_FPTableItems));
  headTest->item = 0;
  headTest->next = NULL;
  InsertTestItem (headTest,1);
  InsertTestItem (headTest,2);
  InsertTestItem (headTest,3);
  InsertTestItem (headTest,4);
  InsertTestItem (headTest,5);
  InsertTestItem (headTest,6);
  
  PrintTestItem(headTest);
  DeleteTestItem(headTest);
  printf("\n");
  PrintTestItem(headTest);
  printf("\n");
  
  exit(1);*/
  
  

  
          
          
          
          
  
  
  bool Found;
  fpoutt = fopen( outputfilename, "w" );
  

	
	if( (fp  = fopen( inputfilename,"r" )) == NULL )
			printf( "The file %s was not opened\n",inputfilename );
	   //else
		//	printf( "The file 'data' was opened\n" );

	  
	   // Initialise the Candidate item list;
	   InitializeItems();
//	   start1 = clock();
	   
         

	   int j;
	   // Building Candidate 1 Item-Set
       LineRead = 1;
	   ReadingFromText();
	   long index,offset;
	   while( !feof( fp ) )
	   {
		 
		   for (j=0;j<tran;++j)
		   {
			    index = Trans.Items[j]/1000;
				offset = Trans.Items[j]%1000;
				if (Trans.Items[j] > DimentionSize)
					DimentionSize = Trans.Items[j];
				++Candidate_Items[index].ArrayOfCandidates[offset].Frequency;			
	
		   }
		   ReadingFromText();
		   ++LineRead;
                   
                               if ( LineRead == 30000 )
                                      break;    
		   
		   
	   }
            
//	   finish1 = clock();
//	   start2 = clock();

//	   duration1 = (double)(finish1 - start1) / CLOCKS_PER_SEC;	   
	   //printf( " Actual Transactions = %ld s \n", LineRead ); 	
	   //printf( " Total run time pass1 %2.1f s \n", duration1 ); 
	   //printf( " Max transactionsize = %ld s \n", mxtransaction ); 
	   //printf( " Dimension = %ld s \n", DimentionSize ); 
	   

	 fclose (fp);
	 No_Of_Frequent1_Items = SizeOf1Frequent();
	 FindInHashTable= (long *)malloc((DimentionSize+1)*sizeof(long));
	// FindInHashTable= (long *)malloc((No_Of_Frequent1_Items+1)*sizeof(long));
	 
	for (int i1=0;i1<=DimentionSize;++i1)
	 {
		FindInHashTable[i1] = -1;
	 }
         
         
	 
	if (No_Of_Frequent1_Items > 0)			 
	{
	 F1_Size = No_Of_Frequent1_Items -1 ;
	 F1_Items = (FrequentStruc *)malloc((No_Of_Frequent1_Items+1)*sizeof(FrequentStruc));
//	 finish1 = clock();
//	 start2 = clock();
	 SortFrequent();
//	 finish2 = clock();
  	 BuildHashTable();
	 Root->brother = NULL;		
	 Root->father = NULL;
	 Root->next = NULL;
	 Root->child = NULL;
         long t;

    	free(Candidate_Items);
	 // End Order Items		
		
		// Start Pass II

		if( (fp  = fopen( inputfilename,"r" )) == NULL )
				printf( "The file 'data' was not opened\n" );
	   else
		//	printf+( "The file 'data' was opened for pass II\n" );
	  
	   LineRead = 0;
	   
        
	   ReadingFromText();
           fpMainRoot = NULL;
           fpMainRoot = (struct FPTree *)malloc(sizeof(struct FPTree));
           fpMainRoot->childHead = NULL;
           fpMainRoot->headTable = NULL;
           fpMainRoot->childNext = NULL;
           fpMainRoot->parent = NULL;
           fpMainRoot->item = -1;
           fpMainRoot->freq = -1;
           fpMainRoot->Age = -1;
           int ItemArray[3000];
           int ItemCount = 0;
           
           
           gCPFreq = (int *)malloc((No_Of_Frequent1_Items+2)*sizeof(int *));
           gCPAge = (int *)malloc((No_Of_Frequent1_Items+2)*sizeof(int *));
           gCPAgeTail = (int *)malloc((No_Of_Frequent1_Items+2)*sizeof(int *));
           

           stringOutPut = (char **)malloc((2000)*sizeof(char *));
           for ( int jj = 0; jj < 2000; jj++)
               stringOutPut[jj] = (char *)malloc(100*sizeof(char)); 
                       
                       
                       
     
               
               
           fpHashRoot = (struct FPHashTable **)malloc((No_Of_Frequent1_Items+1)*sizeof(struct FPHashTable *));
           for ( int i = 0; i < No_Of_Frequent1_Items; i++ )
               fpHashRoot[i] = NULL;
          
        
           
         /*  twoPair = (int **)malloc((No_Of_Frequent1_Items+1)*sizeof(int *));
           threePair = (struct threePairStruct ***)malloc((No_Of_Frequent1_Items+1)*sizeof(struct threePairStruct *));
           for ( int i = 0; i < No_Of_Frequent1_Items; i++ )
           {
               twoPair[i] = (int *)malloc((No_Of_Frequent1_Items+1)*sizeof(int *));
               threePair[i] = (struct threePairStruct **)malloc((No_Of_Frequent1_Items+1)*sizeof(struct threePairStruct *));
               for ( int j = 0; j < No_Of_Frequent1_Items; j++)
               {
                    twoPair[i][j] = 0; 
                    threePair[i][j] = (struct threePairStruct *)malloc((No_Of_Frequent1_Items+1)*sizeof(struct threePairStruct *));
                    for ( int z = 0; z < No_Of_Frequent1_Items; z++ )
                    {
                        threePair[i][j][z].count = 0;
                      //  threePair[i][j][z].head = NULL;//(struct threePairItem *)malloc(sizeof(struct threePairItem *));
                    }
               }
           }*/
           //exit(1);
           
           long transLength = 0;
           
           
           
	   while( !feof( fp ) )
	   { 
//			startf = clock();	 
			ScanForLocation(New_Index_FrequentStruc);
			t = New_Index_FrequentStruc;
			Sort_Transaction(0,New_Index_FrequentStruc);
			New_Index_FrequentStruc = t;
//			finishf = clock();
//			durationp = (double)(finishf - startf) / CLOCKS_PER_SEC;
//			durationpt = durationp + durationpt;
				Father = Root;
				Current=Root->child  ;
				NewCurrent = Root->child;
				LastBrother = Root->child;
                                
                        ItemCount = 0;        
			
			for (int i=New_Index_FrequentStruc;i>=0;i--)
				{
					Found = false;
                              //          printf("%ld ",TransactionArray[i].Index);
                                        
                                        ItemArray[ItemCount] = TransactionArray[i].Index;
                                        
                                        ItemCount++;
                                       // if ( ItemCount > 299 )
                                         //   exit(1);
                                   
				}
                        transLength += ItemCount;
                                InsertItemFPTree(ItemArray,ItemCount);
                             //   printf("%d...\n",ItemCount);

			ReadingFromText();
			
			
			++LineRead;
                               if ( LineRead == 30000 )
                                      break;    
				
		}  // End (ReadingIndex < InputSize) Pase II
		fclose (fp);
                
                
              //  exit(1);
                transLength = (transLength/LineRead);
                //printf("\n%ld......%d.......%d\n",transLength,No_Of_Frequent1_Items,LineRead);
                //exit(1);
                
                
                
                //T10    600   300  
                //retail  140  100
                //BMS1   140  100
                //foodmart   20 15
                
                
              //  printFPTree(fpMainRoot,3);
              //  printHashTable(3);

               // Itemset[2] = 7;
                int Itemset[90];
                gItemsetSupport = itemsetFreqq;
                gItemSupport = support;
                g_FTFactor = ftFactor;
                FT_FPTree_head = NULL;
                FT_FPTable_head= NULL;
                
                //int itemsetFreqq = argv[3];
                //int ftFactor = argv[4];
  
                printf("\nTotal Frequent Items %ld....itemset_support = %d,     item_support= %d\n",No_Of_Frequent1_Items,gItemsetSupport,gItemSupport);
                gTotalFTFrequentItemsets = 0;
                stringOutPutCount = 0;
                
                if ( g_FTFactor == 1 )
                {
              
                            for ( int z1 = 1; z1 < No_Of_Frequent1_Items-1; z1++)
                            {
                                for (int z2 = z1+1; z2 < No_Of_Frequent1_Items; z2++ )
                                {
                                 //   for ( int z3 = z2+1; z3 < No_Of_Frequent1_Items; z3++ )
                                    {
                                        Itemset[0] = z1;
                                        Itemset[1] = z2;  
                                     //   Itemset[2] = z3;
                                        gAge++;
                                        generateConditionalPatterns(Itemset,2);
                                    }
                                    //break;

                                }
                                //printf("\n%d....\n",z1);
                            }
                }
                if ( g_FTFactor == 2 )
                {
              
                            for ( int z1 = 1; z1 < No_Of_Frequent1_Items-1; z1++)
                            {
                                for (int z2 = z1+1; z2 < No_Of_Frequent1_Items; z2++ )
                                {
                                    for ( int z3 = z2+1; z3 < No_Of_Frequent1_Items; z3++ )
                                    {
                                        Itemset[0] = z1;
                                        Itemset[1] = z2;  
                                        Itemset[2] = z3;
                                        gAge++;
                                        generateConditionalPatterns(Itemset,3);
                                    }
                                    //break;

                                }
                            }
                }                
                
                end_t = clock();
               
                total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
                                                   
                WriteItemsetsInFile();
                stringOutPutCount = 0;
                fclose(fpoutt);
               
                printf("Total time taken by CPU: %lu.....%d\n", total_t,gTotalFTFrequentItemsets);
} // not 1 frequent


return 0;

}
