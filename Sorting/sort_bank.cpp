#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "bank_structures.h"

#define N 5583		//total 5583 rows of data
using namespace std;

long int comp=0, swp=0;	//comparisons and swaps
row r[N];		//array of objects of class row
// array to store the index of actual data in sorted manner
// begin with s[i] = i; ith element of s points to ith element of r
int s[N];	//initialize in main()

void insertion_sort_str(){
	for(int j=1;j<N;j++){
		
		row key(r[j]);
		int i = j-1;
		while(i>=0 && r[i].get_job().compare(key.get_job())>0){
			r[i+1].copy(r[i]);
			i--;
			swp++;
			comp++;
		}
		r[i+1].copy(key);
		swp++;
	}
}


void bubble_sort(int sort_by_age=1){
	for(int i=0;i<N;i++){
		
		for(int j=0;j<N-i-1;j++){ 
			if(r[j].get_age_or_balance(sort_by_age) > r[j+1].get_age_or_balance(sort_by_age)){
			row temp(r[j]);
			r[j].copy(r[j+1]);
			r[j+1].copy(r[j]);
			swp++;
			comp++;
			}
		}
	}
	// 
	//cout<<"\nNumber of Comparisons: "<<comp<<" and number of swaps: "<<swp;
}


/* Sorts the elements of array r according to column set */
// by default it sorts by date column, if set to false (=0),
// it sorts by AdjClose column
void insertion_sort(int sort_by_age=1){
	//int comp=0, swap=0;	//declared globally now
	for(int j=1;j<N;j++){
		
		row key(r[j]);
		int i = j-1;
		while(i>=0 && r[i].get_age_or_balance(sort_by_age) > key.get_age_or_balance(sort_by_age)){
			r[i+1].copy(r[i]);
			i--;
			swp++;
			comp++;
		}
		r[i+1].copy(key);
		swp++;
	}
	// 
	//cout<<"\nNumber of Comparisons: "<<comp<<" and number of swaps: "<<swp;
}


// partition function for string type data
int partition_string(int p, int t){
	//store last element
	row x(r[t]);	//making copy in x
	int i=p-1;
	
	for(int j=p;j<t;j++){
		comp++;
		if(r[j].get_job().compare(x.get_job())<0){
			comp++;
			i++;
			row temp(r[i]);
			r[i].copy(r[j]);
			r[j].copy(temp);
			swp++;
		}
	}
	// exchange r[t] and r[i+1], r[t] is already copied in x
	r[t].copy(r[i+1]);
	r[i+1].copy(x);
	swp++;
	//cout<<"\nInside partition, done at index "<<i+1;
	return(i+1);
}

int partition(int p, int t, int sort_by_age = 1){
	//store last element
	row x(r[t]);	//making copy in x
	int i=p-1;
	
	for(int j=p;j<t;j++){
		comp++;
		if(r[j].get_age_or_balance(sort_by_age) < x.get_age_or_balance(sort_by_age)){
			comp++;
			i++;
			row temp(r[i]);
			r[i].copy(r[j]);
			r[j].copy(temp);
			swp++;
		}
	}
	// exchange r[t] and r[i+1], r[t] is already copied in x
	r[t].copy(r[i+1]);
	r[i+1].copy(x);
	swp++;
	//cout<<"\nInside partition, done at index "<<i+1;
	return(i+1);
}

// recursive calls, p and r are starting and ending index
// not passing array as it is declared globally
void quick_sort(int p, int r, int sort_by_age=1){
	if(p<r)
	{
		int q = ((sort_by_age == -1) ? partition_string(p, r) : partition(p, r, sort_by_age));
		quick_sort(p, q-1, sort_by_age);
		quick_sort(q+1, r, sort_by_age);
	}
	// 
	//cout<<"\nNumber of Comparisons: "<<comp<<" and number of swaps: "<<swp;
}

void merge_string(int l, int m, int t)
{
    int n1 = m - l + 1;
    int n2 = t - m;
 
    // Create temp arrays
    // these will store the index of row array element
    row L[n1], R[n2];
 
    // Copy r[] to temp arrays L[] and R[]
	for (int i = 0; i < n1; i++)
		L[i].copy(r[l+i]);		// L[i] = arr[l + i];
	for (int j = 0; j < n2; j++)
		R[j].copy(r[m + 1 + j]);	// R[j] = arr[m + 1 + j];
 
    // Merge the temp arrays back into r[l..r]
 
    // Initial index of first subarray
    int i = 0;
 
    // Initial index of second subarray
    int j = 0;
 
    // Initial index of merged subarray
    int k = l;
 
    while (i < n1 && j < n2) {
        if (L[i].get_job().compare(R[j].get_job()) <= 0) {
			r[k].copy(L[i]);
			i++;
        }
        else {
			r[k].copy(R[j]);
			j++;
        }
        k++;
        comp++;
        swp++;
    }
 
    // Copy the remaining elements of
    // L[], if there are any
	while (i < n1) {
		r[k].copy(L[i]);
		i++;
		k++;
		swp++;
	}comp++;
 
	// Copy the remaining elements of
	// R[], if there are any
	while (j < n2) {
		r[k].copy(R[j]);
		j++;
		k++;
		swp++;
	}comp++;
}

void merge(int l, int m, int t, int sort_by_age=1)
{
    int n1 = m - l + 1;
    int n2 = t - m;
 
    // Create temp arrays
    // these will store the index of row array element
    row L[n1], R[n2];
 
    // Copy r[] to temp arrays L[] and R[]
	for (int i = 0; i < n1; i++)
		L[i].copy(r[l+i]);		// L[i] = arr[l + i];
	for (int j = 0; j < n2; j++)
		R[j].copy(r[m + 1 + j]);	// R[j] = arr[m + 1 + j];
 
    // Merge the temp arrays back into r[l..r]
 
    // Initial index of first subarray
    int i = 0;
 
    // Initial index of second subarray
    int j = 0;
 
    // Initial index of merged subarray
    int k = l;
 
    while (i < n1 && j < n2) {
        if (L[i].get_age_or_balance(sort_by_age) <= 
						R[j].get_age_or_balance(sort_by_age)) {
			r[k].copy(L[i]);
			i++;
        }
        else {
			r[k].copy(R[j]);
			j++;
        }
        k++;
        comp++;
        swp++;
    }
 
    // Copy the remaining elements of
    // L[], if there are any
	while (i < n1) {
		r[k].copy(L[i]);
		i++;
		k++;
		swp++;
	}comp++;
 
	// Copy the remaining elements of
	// R[], if there are any
	while (j < n2) {
		r[k].copy(R[j]);
		j++;
		k++;
		swp++;
	}comp++;
}

// sort_by_age value:
// 1, means sort according to the column age (int)
// 0, means sort according to the column balance (float)
// -1, means sort according to the column job (string)
// for -1, call the merge function merge_string()
void merge_sort(int l, int t, int sort_by_age=1){
	if(t > l){
		int m = (l+t)/2;
		merge_sort(l, m, sort_by_age);
		merge_sort(m+1, t, sort_by_age);
		if(sort_by_age == -1)
			merge_string(l, m, t);
		else merge(l, m, t, sort_by_age);
	}
}

void count_sort_age(){
	
	// age range is 18 to 93, taking array of size 93-18=75
	// index of age A, i = A-18-1	//index 0 maps to age 18
	// index 74 maps to age 93
	countLinks * nlist[75];
	int n=75;
	// initialize with null/0
	for(int i=0;i<n;i++){
		nlist[i] = new countLinks;
		nlist[i]->data = 0;
		nlist[i]->link = NULL;
		nlist[i]->next = NULL;
	}
	
	// linear search through rows of data
	// increment respective index
	// add new node that points to each row of data
	for(int i=0;i<N;i++){
		// create new node
		countLinks *node = new countLinks;
		node->link = &r[i];	// set pointer to current row r[i]
		
		int age = r[i].get_age_or_balance();	//get age
		//cout<<"\nAge as read: "<<age<<",\t the index it is stored in: ";
		//cout<<age-19;
		node->next = nlist[age-19]->next;	//insert
		nlist[age-19]->next = node;	// move head pointer to new node
		nlist[age-19]->data++;	//increment count
	}
	
	/*
	for(int i=0;i<n;i++){
		// print no. of occurrence of reaords of each age value
		cout<<"\nAge: "<<i+19<<", N="<<nlist[i]->data;
	}
	*/
}


// there are as many as 12 unique job values
// take an array of size 15
void count_sort_string(){
	int n=0;	//actual number of elements present
	// size of array is 15
	int t = 15;
	countStrings * nlist[15];
	// initialize with null/0
	for(int i=0;i<t;i++){
		nlist[i] = new countStrings;
		nlist[i]->data = "\0";
		nlist[i]->link = NULL;
		nlist[i]->next = NULL;
		nlist[i]->c = 0;
	}
	//cout<<"\nnlist[] initialization by 0 done!";
	// for each new string search linearly upto size n
	// if string not found, add it, increment n
	// if found, increment respective index
	// add new node that points to each row of data
	for(int i=0;i<N;i++){
		// create new node
		countStrings *node = new countStrings;
		node->link = &r[i];	// set pointer to current row r[i]
		//cout<<"\ni: "<<i<<" new node pointing to row i created";
		
		string job = r[i].get_job();	// get job
		//cout<<"\nJob as read: "<<job;
		
		//find index
		int index = 0, j=0;
		do{
			if(nlist[j]->data.compare(job)==0){	//there is an entry for this job
				index = j;
				//cout<<"\nEntry found for this job at index: "<<index;
			}
			j++;
		}while(j<n);
		if(index==0){
				index = n;	// new string found, add it to the last
				nlist[index]->data = job;	//
				//cout<<"\nNew job: "<<job<<" added at index: "<<index;
				n++;	//increment total number of strings
				comp++;	//number of comparisons
			}
		node->next = nlist[index]->next;	//insert
		nlist[index]->next = node;	// move head pointer to new node
		nlist[index]->c++;	//increment count
	}
	
	//all entries counted
	//now we need to sort the entries among themselves
	
	/*
	for(int i=0;i<n;i++){
		// print no. of occurrence of records of each job value
		cout<<"\nJob: "<<nlist[i]->data<<", count: "<<nlist[i]->c;
	}*/
	//
}


// prints the ith data for all the rows
// default: prints date only
// pass ith_element = -1 to print all columns
void print_r(int nRecords=-1, int ith_element = 0){
	//cout<<"Inside print_r, the value of parameter ith_element is: ";
	//cout<<ith_element;
	int n;
	if(nRecords != -1)
		n = nRecords;
	else
		n = N;
	for(int i=0;i<n;i++){
		cout<<"\n";
		r[i].print_ith_data(ith_element);
	}
}

long int findSize(char file_name[]) 
{ 
    // opening the file in read mode 
    FILE* fp = fopen(file_name, "r"); 
  
    // checking if the file exist or not 
    if (fp == NULL) { 
        printf("File Not Found!\n"); 
        return -1; 
    } 
  
    fseek(fp, 0L, SEEK_END); 
  
    // calculating the size of the file 
    long int res = ftell(fp); 
  
    // closing the file 
    fclose(fp); 
  
    return res; 
} 

int main(){
	fstream f;
	f.open("bank.csv");
	
	if(!f.is_open()) {     // validate file open for reading
        perror ("error while opening file ");
        return 1;
    }
	
	string line;                    // string to hold each line
    
    //read first line (headers for csv)
    getline(f, line);
    int i=0, j=0;	// i to iterate over array of rows, j to iterate for each line
    
    // read each line and then store it in row array
    while (getline (f, line)) {         // read each line
        string val;                 // string to hold each value
        stringstream s (line);          // stringstream to parse csv
		//cout<<"New line";
		//cout<<line<<"\n";
        
        while (getline (s, val, ',')){   // for each value in a line
			//if(j==0)	cout<<val<<"\n";
			//cout<<line<<"\nVal: "<<val<<"\nj: "<<j<<"\n";
			// 0, 1, 6, 10, 12, 13, 14, 15 are integers
			// 5, 7, 8, 17 are *bool* values stored in b[] respectively
			// rest all are strings
			switch(j){
				case 0:
				case 1:
				case 6:
				case 10:
				case 12:
				case 13:
				case 14:
				case 15: r[i].set_ith_data(stoi(val), j); // all ints
					break;
				case 5: 
				case 7:
				case 8: // all bools
				case 17:// to lowercase
						for(auto& c : val){
							c = tolower(c);
						}
						if(val=="yes") r[i].set_ith_data(1, j);
						else r[i].set_ith_data(0, j);
					break;
				default: r[i].set_ith_data(val, j);	// all strings here	
			}
			j++;
			// total 17 values
			if(j>17)	j=0;	// start new row
        }
        i++;
    }
    
    cout<<"Total number of records: ";
    cout<<i<<"\n";	//last i=5583 means all data correctly read
    
    f.close();
	//:::::::::::::::::::::All data read and parsed:::::::::::::::::::::
	
	// print file size
	char file_name[] = { "bank.csv" };
	long int res = findSize(file_name);	//size in bytes
	float siz = res/1024;
	if (res != -1) 
        cout<<"Size of file: "<<siz<<" KB ("<<res<<" bytes)";
	
	//calculate the time taken by each sort function
	clock_t t; 
    t = clock();
    ////////////////////////////////////////////////////////////////////
    ///////////////////Do sorting here//////////////////////////////////
	
	//print_r(10, 1);	//age
	//sort by age
	//cout<<"\nBubble Sort: Sorting by Age!\n";
	//bubble_sort(1);
	//cout<<"\nQuick Sort: Sorting by Age!\n";
	//quick_sort(0, N-1, 1);
	//print_r(10, 1);	//age
	//cout<<"\nInsertion Sort: Sorting by Age!\n";
	//insertion_sort(1);
	//cout<<"\nMerge Sort: Sorting by Age!\n";
	//merge_sort(0, N-1, 1);
	//cout<<"\nCount Sort: Sorting by Age!\n";
	//count_sort_age();
	
	//sort by balance
	//cout<<"\nQuick Sort: Sorting by Balance!\n";
	//quick_sort(0, N-1, 0);
	//cout<<"\nInsertion Sort: Sorting by Balance!\n";
	//insertion_sort(0);
	//cout<<"\nMerge Sort: Sorting by Balance!\n";
	//merge_sort(0, N-1, 0);
	//count sort is not possible for float values
	
	// sort by job
	//cout<<"\nQuick Sort: Sorting by Job!\n";
	//quick_sort(0, N-1, -1);
	//cout<<"\nInsertion Sort: Sorting by Job!\n";
	//insertion_sort_str();
	//cout<<"\nMerge Sort: Sorting by Job!\n";
	//merge_sort(0, N-1, -1);
	//cout<<"\nCount Sort: Sorting by Job!\n";
	//count_sort_string();
	
	//print
	//print_r(1);	//age
	//print_r(6);	//balance
	//print_r(2);	//job
	////////////////////////////////////////////////////////////////////
	cout<<"\nNumber of Comparisons: "<<comp<<" and number of swaps: "<<swp;
	t = clock() - t; 
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
    cout<<"\nTime taken to sort: "<<time_taken<<" seconds";
    
	return 0;
}
