// hashing program on modulo hashing implementing BST by using double way link list
// 24/09/2020

#include<stdio.h>
#define MAX 5
#define Hash(K) K%MAX

typedef struct Node BST;

struct Node
{
	BST *Left;
	int key;
	BST *Right;
};

BST *root[MAX];

void Insert(int num)
{
	BST *Temp,*Curr,*Prev=NULL;

	Curr=root[Hash(num)];

	Temp=(BST *)malloc(sizeof(BST));
	Temp->Left=NULL;
	Temp->key=num;
	Temp->Right=NULL;

	if(Curr==NULL)	// Insertion at root
	{
		root[Hash(num)]=Temp;
		return;
	}
	while(Curr!=NULL)
	{
		Prev=Curr;
		if(num==Curr->key)
		{
			printf("Duplicate element not allowed \n");
			return;
		}
		else if (num > Curr->key)
			Curr=Curr->Right;
		else
			Curr=Curr->Left;
	}
	if(num > Prev->key)		// Assigning to right
		Prev->Right=Temp;
	else	// Assigning to left
		Prev->Left=Temp;
}

void Search(int num)
{
	BST *Temp;

	Temp=root[Hash(num)];

	while(Temp!=NULL)
	{
		if(num==Temp->key)
		{
			printf("Number found \n");
			break;
		}
		else if(num > Temp->key)
			Temp=Temp->Right;
		else
			Temp=Temp->Left;
	}
	if(Temp==NULL)
		printf("Number not found \n");
}

int main()
{
	int ch=1,i;

	for(i=0;i<MAX;i++)
		root[i]=NULL;

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
