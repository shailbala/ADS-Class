/* Program to read a .csv file, parse it and sort it according to date
 * column and Adj Close column respectively using 4 different sorting
 * techniques: QuickSort, MergeSort, InsertionSort and CountSort
 * Also, print the number of comparisons happened for each sort and the
 * total time taken to run for each sort.
 * */

#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include "vix_structures.h"

#define N 252		//total 252 rows of data
using namespace std;

long int comp=0, swp=0;	//comparisons and swaps
row r[N];		//array of objects of class row
// array to store the index of actual data in sorted manner
// begin with s[i] = i; ith element of s points to ith element of r
int s[N];	//initialize in main()


/* Sorts the elements of array r according to column set */
// by default it sorts by date column,
// if set to false (=0), it sorts by AdjClose column
void insertion_sort(bool sort_by_date=1){
	
	for(int j=1;j<N;j++){
		
		row key(r[j]);
		int i = j-1;
		
		while(i>=0 && r[i].get_intDate_or_AdjClose(sort_by_date) > key.get_intDate_or_AdjClose(sort_by_date)){
			r[i+1].copy(r[i]);
			i--;
			swp++;
			comp++;
		}
		r[i+1].copy(key);
		swp++;
	}
	// 
	//cout<<"\nNumber of Comparisons: "<<comp<<"\t and number of swaps: "<<swp;
}

int partition(int p, int t, int sort_by_date = 1){
	//store last element
	row x(r[t]);	//making copy in x
	int i=p-1;
	
	for(int j=p;j<t;j++){
		comp++;
		if(r[j].get_intDate_or_AdjClose(sort_by_date) < x.get_intDate_or_AdjClose(sort_by_date)){
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
void quick_sort(int p, int t, int sort_by_date=1){
	if(p<t)
	{
		int q = partition(p, t, sort_by_date);
		quick_sort(p, q-1, sort_by_date);
		quick_sort(q+1, t, sort_by_date);
	}
	// 
	//cout<<"\nNumber of Comparisons: "<<comp<<" and number of swaps: "<<swp;
}

void merge(int l, int m, int t, int sort_by_date=1)
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
        if (L[i].get_intDate_or_AdjClose(sort_by_date) <= 
						R[j].get_intDate_or_AdjClose(sort_by_date)) {
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

void merge_sort(int l, int t, int sort_by_date=1){
	if(t > l){
		int m = (l+t)/2;
		merge_sort(l, m, sort_by_date);
		merge_sort(m+1, t, sort_by_date);
		merge(l, m, t, sort_by_date);
	}
}

/*
void count_sort_age(){
	
	// date range is about 1 year, taking array of size 365
	// 13-12-2018 to 11-12-2019
	// 11-12-2019 equals 20191211
	// 13-12-2018 equals 20181213, maps to 0
	// 14-12-2018 equals 20181214, maps to 1
	// 31-12-2018 equals 20181231, maps to 18
	// 01-01-2019 equals 20190101, maps to 19
	// subtract 20180000
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
	
	
	for(int i=0;i<n;i++){
		// print no. of occurrence of reaords of each age value
		cout<<"\nAge: "<<i+19<<", N="<<nlist[i]->data;
	}
	
}
*/


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
	f.open("vix_2018_2019.csv");
	
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
			//if(j==5) cout<<stof(val)<<"\n";
			
			if(j == 0)
				r[i].set_date(val);		// first element is date
			else{
				r[i].set_ith_data(stof(val), j);	//convert to float, add to row
				//cout<<r[i].get_ith_data(j);
			}
			j++;
			// why 6? there is one extra 0 in the end, which we ignore
			if(j>6)	j=0;	// start new row
        }
        i++;
    }
    cout<<"Total number of records:\t";
    cout<<i<<"\n";	//last i=252 means all data correctly read
    
    f.close();
	//:::::::::::::::::::::All data read and parsed:::::::::::::::::::::
	
	// print file size
	char file_name[] = { "vix_2018_2019.csv" };
	long int res = findSize(file_name);	//size in bytes
	float siz = res/1024;
	if (res != -1) 
        cout<<"Size of file: "<<siz<<" KB ("<<res<<" bytes)";
    
    //calculate the time taken by each sort function
	clock_t t; 
    t = clock();
    ////////////////////////////////////////////////////////////////////
    ///////////////////Do sorting here//////////////////////////////////
	
	//sort_by_date
	print_r(10, 0);
	cout<<"\nQuick Sort: Sorting by Date!\n";
	quick_sort(0, N-1, 1);
	print_r(10, 0);
	
	//cout<<"\nInsertion Sort: Sorting by Date!\n";
	//insertion_sort();
	//cout<<"\nMerge Sort: Sorting by Date!\n";
	//merge_sort(0, N-1, 1);
	//cout<<"\nCount Sort: Sorting by Date!\n";
	//count_sort_date();
	
	//sort_by_AdjClose
	//cout<<"\nQuick Sort: Sorting by Price!\n";
	//quick_sort(0, N-1, 0);
	//cout<<"\nInsertion Sort: Sorting by Price!\n";
	//insertion_sort(0);
	//cout<<"\nMerge Sort: Sorting by Price!\n";
	//merge_sort(0, N-1, 0);
	
	//print_r(0);	//date
	//print_r(5);	//AdjClose
		
	////////////////////////////////////////////////////////////////////
	cout<<"\nNumber of Comparisons: "<<comp<<" and number of swaps: "<<swp;
	t = clock() - t; 
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
    cout<<"\nTime taken to sort: "<<time_taken<<" seconds";

	return 0;
}
