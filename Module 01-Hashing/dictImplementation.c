//	Dictionary implementation using Hashing
//	29/09/2020

#include<stdio.h>
#define MAX 5
#define Hash(K) K%MAX

typedef struct List Node;

struct List
{
	int roll;
	char name[20];
	Node *Next;
};

Node *H[MAX];

void Insert()
{
	int roll;
	char n[20];
	Node *Temp,*Curr,*Prev=NULL;

	printf("Enter roll no:\t");
	scanf("%d",&roll);
	printf("Enter name:\t");
	scanf("%s",&n);

	Curr=H[Hash(roll)];
	//printf("%d\n",*Curr);

	if(Curr==NULL)	//Assignment of the Node
	{
		Temp=(Node *)malloc(sizeof(Node));
		Temp->roll=roll;
		strcpy(Temp->name,value);
		H[Hash(roll)]=Temp;
		Temp->Next=NULL;
		return;
	}
	while(Curr!=NULL)
	{
		Prev=Curr;
		if(key==Curr->roll)
		{
			printf("Duplicate entries not allowed \n");
			return;
		}
		Curr=Curr->Next;
	}
	if(Curr==NULL)	//Insert at the end of the list
	{
		Temp=(Node *)malloc(sizeof(Node));
		Temp->roll=roll;
		strcpy(Temp->name,n);
		Prev->Next=Temp;
		Temp->Next=NULL;

	}
}

void Delete()
{
	int num;

	printf("Enter the roll number to delete\t");
	scanf("%d",&num);

	Node *Curr,*Prev;
	Curr=H[Hash(num)];
	Prev=Curr;

	if(Curr==NULL)	// Node is not initialised or assigned
		printf("Element not found \n");
	else
	{
		while(Curr!=NULL && Curr->roll!=num)
		{
			Prev=Curr;
			Curr=Curr->Next;
		}
		if(Curr==NULL)	// Element not present
			printf("Element not found \n");

		else if (Curr==Prev && Curr->Next==NULL)	// First and the only node
		{
			printf("Node deleted successfully \n");
			H[Hash(num)]=NULL;
			free(Curr);	
		}
		else if(Curr==Prev)	//Deletion of First node
		{
			printf("Node deleted successfully \n");
			H[Hash(num)]=Curr->Next;
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

void Search()
{
	int num,i;

	printf("Enter a roll number to search\t");
	scanf("%d",&num);

	Node *Temp;
	Temp=H[Hash(num)];

	while(Temp!=NULL)
	{
		if(Temp->roll==num)
		{
			printf("Roll number found\t Corresponding Name  %s \n",Temp->name);
			break;
		}
		Temp=Temp->Next;
	}
	if(Temp==NULL)
		printf("Roll no. not found \n");
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
				printf("%d %s\t",temp->roll,temp->name);
				temp=temp->Next;
			}
			printf("\n");
		}
		else
			printf("NULL \n");
	}
	printf("\n");
}

int main()
{
	int ch=1,i;

	for(i=0;i<MAX;i++)
		H[i]=NULL;

	while(ch!=0)
	{
		printf("1-Insert\n2-Delete\n3-Search\n4-Display\n0-Exit\nEnter your choice\t");
		scanf("%d",&ch);
		if(ch==1)
			Insert();
		else if(ch==2)
			Delete();
		else if(ch==3)
			Search();
		else if(ch==4)
			Display();
		else
			break;
	}
}
