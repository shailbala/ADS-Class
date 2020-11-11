//	Dictionary implementation using Hashing
//	29/09/2020

#include<stdio.h>
#define MAX 5
#define h(k) k%MAX

struct node
{
	int key;
	struct node *next;
};
struct node *H[MAX];

void Insert(int k)
{
	int i;

	struct node *temp;
	i=h(k);
	temp=(struct node *)malloc(sizeof(struct node));
	temp->key=k;
	temp->next=H[i];
	H[i]=temp;
}

void Search(int k)
{
	int i;

	i=h(k);
	struct node *temp;
	temp=H[i];

	while(temp!=NULL)
	{
		if(temp->key==k)
		{
			printf("Element found at position %d \n",i+1);
			break;
		}
		temp=temp->next;
	}
	if(temp==NULL)
		printf("Element not found \n");
} 

void Display()
{
	int i;

	printf("The Hash Table is as follows \n");
	for(i=0;i<MAX;i++)
	{
		if(H[i]!=NULL)
		{
			struct node *temp;
			temp=H[i];

			while(temp!=NULL)
			{
				printf("%d \t",temp->key);
				temp=temp->next;
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
	struct node *Curr,*Prev;
	Curr=H[i];
	Prev=Curr;

	if(Curr==NULL)	// Node is not initialised or assigned
		printf("Element not found \n");
	else
	{
		while(Curr!=NULL && Curr->key!=k)
		{
			Prev=Curr;
			Curr=Curr->next;
		}
		if(Curr==NULL)	// Element not present
			printf("Element not found \n");

		else if (Curr==Prev && Curr->next==NULL)	// First and the only node
		{
			printf("Node deleted!\n");
			H[i]=NULL;
			free(Curr);	
		}
		else if(Curr==Prev)	//Deletion of First node
		{
			printf("Node deleted successfully \n");
			H[i]=Curr->next;
			free(Curr);
		}
		else if(Curr->next==NULL)	// Deletion of Last Node
		{
			printf("Node deleted successfully \n");
			Prev->next=NULL;
			free(Curr);
		}
		else	// Intermediate node
		{
			printf("Node deleted successfully \n");
			Prev->next=Curr->next;
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
		if(ch==1||ch==2||ch==3)
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
