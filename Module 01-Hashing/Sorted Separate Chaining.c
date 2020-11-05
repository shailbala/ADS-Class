// hashing program on modulo operation
// 23/9/2020
// creating a sorted list of unique elements

#include<stdio.h>
#define MAX 5
#define h(k) = k%MAX

typedef struct List Node;

struct List
{
	int key;
	Node *Next;
};
struct node *H[MAX];

void Insert(int k)
{
	int i;

	i=h(k);
	Node *Temp,*Curr=NULL,*Prev=NULL;

	Curr=H[i];

	if(Curr==NULL)	// Assignmment of first node/ head node
	{
		Temp=(Node *)malloc(sizeof(Node));
		Temp->key=k;
		H[i]=Temp;
		Temp->Next=NULL;
		return;
	}

	while(Curr!=NULL && k > Curr->key)
	{
		/*if(num==Curr->key)
		{
			printf("Duplicate element \n");
			return;
		}*/
		Prev=Curr;
		Curr=Curr->Next;
	}
	if(Curr==NULL && Prev!=NULL && Prev->key!=k)		//Checking unique key for last node
	{
		Temp=(Node *)malloc(sizeof(Node));
		Temp->key=k;
	}
	else if(Curr->key!=k)		// Checking unique key for other nodes
	{
		Temp=(Node *)malloc(sizeof(Node));
		Temp->key=k;
	}
	else
	{
		printf("Duplicate element II \n");
		return;
	}

	if(Prev==NULL)	//Insert in front of first node
	{
		Temp->Next=H[i];
		H[i]=Temp;
	}
	else if(Curr==NULL)		// Insert after last node
	{
		printf("reached here last Insert\n");
		Prev->Next=Temp;
		Temp->Next=NULL;
	}
	else 	// Insert within intermediate node
	{
		Temp->Next=Curr;
		Prev->Next=Temp;
	}
}

void Search(int k)
{
	int i;

	i=h(k);
	Node *Temp;

	Temp=H[i];

	while(Temp!=NULL)
	{
		if(Temp->key==k)
			printf("Number found in the list \n");
		else if(k > Temp->key)
			Temp=Temp->Next;
		else
		{
			printf("Number not found \n");
			break;
		}
	}
}

void Display()
{
	int i;

	printf("The Hash Table is as follows \n");
	for(i=0;i<MAX;i++)
	{
		if(H[i]!=NULL)
		{
			Node *temp;
			temp=H[i];

			while(temp!=NULL)
			{
				printf("%d \t",temp->key);
				temp=temp->Next;
			}
			printf("\n");
		}
		else
			printf("NULL \n");
	}
	printf("\n");
}

void Delete(int k)
{
	int i;

	i=h(k);
	Node *Curr,*Prev;
	Curr=H[i];
	Prev=Curr;

	if(Curr==NULL)	// Node is not initialised or assigned
		printf("Element not found \n");
	else
	{
		while(Curr!=NULL && Curr->key!=k)
		{
			Prev=Curr;
			Curr=Curr->Next;
		}
		if(Curr==NULL)	// Element not present
			printf("Element not found \n");

		else if (Curr==Prev && Curr->Next==NULL)	// First and the only node
		{
			printf("Node deleted successfully \n");
			H[i]=NULL;
			free(Curr);	
		}
		else if(Curr==Prev)	//Deletion of First node
		{
			printf("Node deleted successfully \n");
			H[i]=Curr->Next;
			free(Curr);
		}
		else if(Curr->Next==NULL)	// Deletion of Last Node
		{
			printf("Node deleted successfully \n");
			Prev->Next=NULL;
			free(Curr);
		}
		else	// Intermediate node
		{
			printf("Node deleted successfully \n");
			Prev->Next=Curr->Next;
			free(Curr);
		}
	}
}

int main()
{
	int ch=1,i;

	for(i=0;i<MAX;i++)
		H[i]=NULL;

	while(ch!=0)
	{
		printf("Menu: \n 1- Insert\n 2- Search\n 3- Delete\n 4- Display\n Enter 0 to Exit\n");
		scanf("%d",&ch);
		if(ch!=4||ch!=0)
		{
			int num;
			printf("Enter number\t");
			scanf("%d",&num);
			if(ch==1)
				Insert(num);
			else if(ch==2)
				Search(num);
			else if(ch==3)
				Delete(num);
		}
		else if(ch==4)
			Display();
		else
			break;
	}
	return 0;
}
