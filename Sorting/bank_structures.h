#include <string>
#include <iostream>

using namespace std;

class row{
	/* values of ith column:
	 * 0: sl
	 * 1: age, 2: job, 3: marital, 4: education, 5: defaul,
	 * 6: balance, 7: housing, 8: loan, 9: contact,
	 * 10: day, 11: month, 12: duration, 13: campaign,
	 * 14: pdays, 15: previous, 16: poutcome, 17: deposit
	 * */
	int sl, age, balance, day, duration, campaign, pdays, previous;
	string job, marital, education, contact, month, poutcome;
	// defaul, housing, loan, deposit
	bool b[4];
	
	public:
	//constructor 1, initialize with empty values
	row(){
		sl = age = balance = day = duration = campaign = pdays = previous = 0;
		job = marital = education = contact = month = poutcome = "\0";
		b[0] = b[1] = b[2] = b[3] = 0;
	}
	
	//copy constructor, with another row object
	row(const row & r){
		sl = r.sl;
		age = r.age;
		balance = r.balance;
		day = r.day;
		duration = r.duration;
		campaign = r.campaign;
		pdays = r.pdays;
		previous = r.previous;
		
		job = r.job;
		marital = r.marital;
		education = r.education;
		contact = r.contact;
		month = r.month;
		poutcome = r.poutcome;
		
		for(int i=0;i<4;i++)
			b[i] = r.b[i];
	}
	
	/*:::::::::::::::::::::::::Get data:::::::::::::::::::::::::::::::*/
	
	/* another way to get data, each column corresponds to one data  */
	// 0, 1, 6, 10, 12, 13, 14, 15 are integers
	// 5, 7, 8, 17 are bool values stored in b[] respectively
	int get_ith_data(int i){
		switch(i){
			case 0: return sl;
			case 1: return age;
			case 5: return b[0];
			case 6: return balance;
			case 7: return b[1];
			case 8: return b[2];
			case 10: return day;
			case 12: return duration;
			case 13: return campaign;
			case 14: return pdays;
			case 15: return previous;
			case 17: return b[3];
		}
	}
	
	float get_age_or_balance(int get_age=1){
		if(get_age)	return age;
		return balance;
	}
	
	string get_job(){
		return job;
	}
	
	/*:::::::::::::::::::::::Setting data:::::::::::::::::::::::::::::*/
	
	//for settings intergers and bools only
	void set_ith_data(int data, int i=0){
		switch(i){
			case 0: sl = data;
			break;
			case 1: age = data;
			break;
			case 5: b[0] = data;
			break;
			case 6: balance = data;
			break;
			case 7: b[1] = data;
			break;
			case 8: b[2] = data;
			break;
			case 10: day = data;
			break;
			case 12: duration = data;
			break;
			case 13: campaign = data;
			break;
			case 14: pdays = data;
			break;
			case 15: previous = data;
			break;
			case 17: b[3] = data;
			break;
		}
	}

	// for setting strings only, function overloading
	void set_ith_data(string data, int i=2){
		switch(i){
			case 2: job = data;
			break;
			case 3: marital = data;
			break;
			case 4: education = data;
			break;
			case 9: contact = data;
			break;
			case 11: month = data;
			break;
			case 16: poutcome = data;
			break;
		}
	}
	
	// function overloading, setting data by column name
	void set_ith_data(string data, string col="job"){
		if(col == "job")
			job = data;
		else if(col == "martial")
			marital = data;
		else if(col =="education")
			education = data;
		else if(col == "contact")
			contact = data;
		else if(col == "month")
			month = data;
		else if(col == "poutcome")
			poutcome = data;
	}
	
	void copy(row r){
		sl = r.sl;
		age = r.age;
		balance = r.balance;
		day = r.day;
		duration = r.duration;
		campaign = r.campaign;
		pdays = r.pdays;
		previous = r.previous;
		
		job = r.job;
		marital = r.marital;
		education = r.education;
		contact = r.contact;
		month = r.month;
		poutcome = r.poutcome;
		
		for(int i=0;i<4;i++)
			b[i] = r.b[i];
	}
	
	/*:::::::::::::::::::::::Printing data::::::::::::::::::::::::::::*/
	
	//prints ith data, if ith_data = -1, prints all data in tab spacing
	void print_ith_data(int ith_data = 0){
		switch(ith_data){
			case 0: cout<<sl<<"\t";
			break;
			case 1: cout<<age<<"\t";
			break;
			case 2: cout<<job<<"\t";
			break;
			case 3: cout<<marital<<"\t";
			break;
			case 4: cout<<education<<"\t";
			break;
			case 5: cout<<b[0]<<"\t";
			break;
			case 6: cout<<balance<<"\t";
			break;
			case 7: cout<<b[1]<<"\t";
			break;
			case 8: cout<<b[2]<<"\t";
			break;
			case 9: cout<<contact<<"\t";
			break;
			case 10: cout<<day<<"\t";
			break;
			case 11: cout<<month<<"\t";
			break;
			case 12: cout<<duration<<"\t";
			break;
			case 13: cout<<campaign<<"\t";
			break;
			case 14: cout<<pdays<<"\t";
			break;
			case 15: cout<<previous<<"\t";
			break;
			case 16: cout<<poutcome<<"\t";
			break;
			case 17: cout<<b[3]<<"\t";
			break;
			case -1: cout<<sl<<"\t"<<age<<"\t"<<"\t"<<job<<"\t"<<marital<<"\t"<<education<<"\t"<<b[0];
			cout<<balance<<"\t"<<b[1]<<"\t"<<b[2]<<"\t"<<contact<<"\t"<<day<<"\t"<<month<<"\t"<<duration;
			cout<<campaign<<"\t"<<pdays<<"\t"<<previous<<"\t"<<poutcome<<"\t"<<b[3];
		}
	}
};

// for count sort based on column age (int)
struct countLinks{
	int data;
	row *link;
	struct countLinks *next;
};

// for count sort based on column job (string)
struct countStrings{
	string data;
	int c;	//count
	row *link;
	struct countStrings *next;
};
