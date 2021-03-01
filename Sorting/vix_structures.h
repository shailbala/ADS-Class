#include <string>
#include <iostream>

using namespace std;

class row{
	string date;
	float opn, high, low, clos, AdjClose;
	// never update it directly, call inbuilt method calc_intDate()
	int intDate;	//integer corresponding to date value for easy sorting
	
	public:
	
	//constructor 1, initialize with empty values
	row(){
		date = "\0";
		opn = 0.0;
		high = 0.0;
		low = 0.0;
		clos = 0.0;
		AdjClose = 0.0;
		intDate = 0;
	}
	
	//constructor2, with parameters
	row(string d, float o, float h, float l, float c, float aClose){
		date = d;
		opn = o;
		high = h;
		low = l;
		clos = c;
		AdjClose = aClose;
		calc_intDate();	//set intDate
	}
	
	//constructor 3
	row(const row & r){
		date = r.date;
		opn = r.opn;
		high = r.high;
		low = r.low;
		clos = r.clos;
		AdjClose = r.AdjClose;
		calc_intDate();	//set intDate
	}
	
	// converts date in string to int with formula
	// dd*1 + mm*100 + yyyy*10000
	void calc_intDate(){
		if(date!="\0"){
			stringstream d (date);
			intDate = 0;
			int k = 1;
			string val;
			//break d into val breaking at -
			while(getline (d, val, '-')){
				intDate += k*stoi(val);
				k *= 100;
			}
		}
		//cout<<intDate<<"\n";
	}
	
	string get_date(){
		return date;
	}
	
	// i=1 means return intDate
	// i=0 means return AdjClose
	float get_intDate_or_AdjClose(int i){
		if(i)
			return intDate;
		return AdjClose;
	}
	
	/* another way to get data, each column corresponds to one data
	 * i starts from 1 to n-1
	 * i = 1 to 5 are float data
	 *   */
	float get_ith_data(int i){
		switch(i){
			case 1: return opn;
			case 2: return high;
			case 3: return low;
			case 4: return clos;
			case 5: return AdjClose;
		}
	}
	
	int get_intDate(){	return intDate; }
	
	/*:::::::::::::::::::::::Setting data:::::::::::::::::::::::::::::*/
	//function overloading to account for i=0 which corresponds to a string type data
	void set_ith_data(float ith_data, int i){
		switch(i){
			case 1: opn = ith_data;
			break;
			case 2: high = ith_data;
			break;
			case 3: low = ith_data;
			break;
			case 4: clos = ith_data;
			break;
			case 5: AdjClose = ith_data;
			//cout<<"\nSetting AdjClose to: "<<ith_data<<"\n";
			break;
		}
	}
	
	//function overloading 
	void set_ith_data(string ith_data, int i=0){
		if(i==0){
			date = ith_data;
			calc_intDate();
		}
	}
	
	void set_date(string d){
		date = d;
		calc_intDate();
	}
	
	void set_open(float o){
		opn = o;
	}
	
	void set_high(float h){
		high = h;
	}
	
	void set_low(float l){
		low = l;
	}
	
	void set_close(float c){
		clos = c;
	}
	
	void set_aclose(float ac){
		AdjClose = ac;
	}

	void copy(row r){
		date = r.date;
		opn = r.opn;
		high = r.high;
		low = r.low;
		clos = r.clos;
		AdjClose = r.AdjClose;
		calc_intDate();	//set intDate
	}

	//prints ith data, if ith_data = -1, prints all data in tab spacing
	void print_ith_data(int ith_data = 0){
		//cout<<"\nInside print_ith_data() function of class";
		//cout<<"\nThe value of ith_data is "<<ith_data<<"\n";
		switch(ith_data){
			case 0: cout<<date<<"\t";
			break;
			case 1: cout<<opn<<"\t";
			break;
			case 2: cout<<high<<"\t";
			break;
			case 3: cout<<low<<"\t";
			break;
			case 4: cout<<clos<<"\t";
			break;
			case 5: cout<<AdjClose<<"\t";
			break;
			case -1: cout<<date<<"\t"<<opn<<"\t"<<high<<"\t"<<low<<"\t"<<clos<<"\t"<<AdjClose;
		}
	}
};

// for count sort
struct countLinks{
	int data;	//intDate
	row *link;
	struct countLinks *next;
};
