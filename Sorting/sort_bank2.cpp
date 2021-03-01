#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <random>
#include <iostream>
#include "bank_structures.h"

#define N 5583		//total 5583 rows of data
using namespace std;


long int comp=0, swp=0;	//comparisons and swaps
row r[N];		//array of objects of class row
// array to store the index of actual data in sorted manner
// begin with s[i] = i; ith element of s points to ith element of r
int s[N];	//initialize in main()


/* Sorts the elements of array r according to column set */
// by default it sorts by date column, if set to false (=0),
// it sorts by AdjClose column
void bubble_sort(int sort_by_age=1){
	//int comp=0, swap=0;	//declared globally now
	for(int i=0;i<N;i++){
		for(int j=0;j<N-i-1;j++){
			if(r[j].get_age_or_balance(sort_by_age) > r[j+1].get_age_or_balance(sort_by_age)){
				comp++;
				row temp(r[j+1]);
				r[j+1].copy(r[j]);
				r[j].copy(temp);
				swp++;
			}
		}
	}
	
	// 
	//cout<<"\nNumber of Comparisons: "<<comp<<" and number of swaps: "<<swp;
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

int r_partition(int p, int t, int sort_by_age = 1){
	
	// generate random index
	int i = p + ( std::rand() % ( p - t + 1 ) );
	
	row x(r[i]);	//making copy in x
	for(int j=p;j<i;j++){
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
	r[i].copy(r[i+1]);
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
		int q = partition(p, r, sort_by_age);
		quick_sort(p, q-1, sort_by_age);
		quick_sort(q+1, r, sort_by_age);
	}
	// 
	//cout<<"\nNumber of Comparisons: "<<comp<<" and number of swaps: "<<swp;
}

void r_quick_sort(int p, int r, int sort_by_age=1){
	if(p<r)
	{
		int q = r_partition(p, r, sort_by_age);
		r_quick_sort(p, q-1, sort_by_age);
		r_quick_sort(q+1, r, sort_by_age);
	}
	// 
	//cout<<"\nNumber of Comparisons: "<<comp<<" and number of swaps: "<<swp;
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
	int m = (l+t)/2;
	if(t > l){
		merge_sort(l, m, sort_by_age);
		merge_sort(m+1, t, sort_by_age);
	}
	else merge(l, m, t, sort_by_age);
}

// prints the ith data for all the rows
// default: prints date only
// pass ith_element = -1 to print all columns
void print_r(int ith_element = 0){
	for(int i=0;i<N;i++){
		cout<<"\n";
		r[i].print_ith_data(ith_element);
	}
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
	
	//calculate the time taken by each sort function
	clock_t t; 
    t = clock();
    ////////////////////////////////////////////////////////////////////
    ///////////////////Do sorting here//////////////////////////////////

	//sort by balance
	//cout<<"\nRandomized Quick Sort: Sorting by Balance!\n";
	//r_quick_sort(0, N-1, 0);
	//cout<<"\nBubble Sort: Sorting by Balance!\n";
	//bubble_sort(0);
	//cout<<"\nMerge Sort: Sorting by Balance!\n";
	//merge_sort(0, N-1, 0);
	//count sort is not possible for float values
	
	////////////////////////////////////////////////////////////////////
	cout<<"\nNumber of Comparisons: "<<comp<<" and number of swaps: "<<swp;
	t = clock() - t; 
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
    cout<<"\nTime taken to sort: "<<time_taken<<" seconds";
    
	return 0;
}
