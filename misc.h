#ifndef STRING
#define STRING
	#include<string>
#endif

#ifndef IOSTREAM
#define IOSTREAM
	#include<iostream>
#endif


#ifndef C_LIMITS
	#define C_LIMITS
	#include "limits.h"
#endif


using namespace std;


#ifndef AIRPORT_CODE
	#define AIRPORT_CODE
class Airport_code{
	public:
	char airport_code[3];

	
	Airport_code(){
		airport_code[0]=' ';
		airport_code[1]=' ';
		airport_code[2]=' ';
	}

	Airport_code(string input_code){
		if(input_code.length() == 3){
			airport_code[0]=input_code.at(0);
			airport_code[1]=input_code.at(1);
			airport_code[2]=input_code.at(2);
		}
		else{
			airport_code[0]=' ';
			airport_code[1]=' ';
			airport_code[2]=' ';
		}
	}

	bool operator==(const Airport_code &ac){
		if(airport_code[0]==ac.airport_code[0] && airport_code[1]==ac.airport_code[1] && airport_code[2]==ac.airport_code[2])
			return true;
		return false;
	}

	bool operator!=(const Airport_code &ac){
		if(airport_code[0]==ac.airport_code[0] && airport_code[1]==ac.airport_code[1] && airport_code[2]==ac.airport_code[2])
			return false;
		return true;
	}

	void operator=(const Airport_code &ac){
		airport_code[0]=ac.airport_code[0];
		airport_code[1]=ac.airport_code[1];
		airport_code[2]=ac.airport_code[2];
	}
/*
	std::ostream& operator<<(std::ostream& out){
		return cout<<airport_code[0]<<airport_code[1]<<airport_code[2];
	}
*/
	void print(){
		cout<<airport_code[0]<<airport_code[1]<<airport_code[2];
	}
	

	int hash(){
		return ((int)airport_code[0])*256*256 + ((int)airport_code[1])*256 +((int)airport_code[2]);
	}

	void get_valid_code(string prompt){
		string str;
		cout<<prompt;
//		cin.clear();
//		cin.ignore(); 
		getline(cin,str);
		while(str.length()!=3){
			cout<<"\n\t\t\tERROR: invalid input: airport code must be exactly 3 characters long.";
			cout<<prompt;
			getline(cin,str);
		}
		for(int i=0; i<3; i++){
			airport_code[i]=str.at(i);		//copy airport code
		}
	}
};

#endif


#ifndef DATE
	#define DATE

class Date{
	public:
	int day;
	int month;
	int year;

	Date(){
		day=INT_MAX;
		month=INT_MAX;
		year=INT_MAX;
	}

	bool is_valid(){
		if(day<0 || day>31 || month<0 || month>12 || year<1970)
			return false;
		else if(day==31 && (month ==4 || month ==6 || month ==9 || month ==11))
			return false;
		else if(day==29 && month==2 && (year%4!=0 || (year%100==0 && year%400!=0)))
			return false;
		return true;
	}
	
	void print(){
		cout<<day<<"/"<<month<<"/"<<year;
	}
	/*std::ostream&  operator<< (std::ostream& out){
		return out<<day<<"/"<<month<<"/"<<year;
	}*/

	bool operator==(const Date &d){
		if(this->day==d.day && this->month==d.month && this->year==d.year)
			return true;
		return false;
	}

	bool operator!=(const Date &d){
		if(this->day==d.day && this->month==d.month && this->year==d.year)
			return false;
		return true;
	}

	void get_valid_date(string prompt){
		cout<<prompt;
		cout<<"\n\t\t\tFormat: day month year (eg: 27 5 2015)\n\t\t\t>";
		cin>>day;
		cin>>month;
		cin>>year;
		while(is_valid()==false){
			cout<<"\n\t\t\tERROR: invalid input date entered.";
			cout<<prompt<<"\n\t\t\tFormat: day month year (eg: 27 5 2015)\n\t\t\t>";
			cin>>day;
			cin>>month;
			cin>>year;
		}
	}

};

#endif


#ifndef TIME
	#define TIME
class Time{
	public:
	int hours; //24-hour format
	int minutes;
	int seconds;

	Time(){
		hours=INT_MAX;
		minutes=INT_MAX;
		seconds=INT_MAX;
	}

	bool is_valid(){
		if(hours<0 || hours>23 || minutes<0 || minutes>59 ||seconds<0 || seconds>59)
			return false;
		return true;
	}
	/*
	std::ostream& operator<< (std::ostream& out){
		return out<<hours<<":"<<minutes<<":"<<seconds;
	}*/

	void print(){
		cout<<hours<<":"<<minutes<<":"<<seconds;
	}


	bool operator==(const Time &t){
		if(this->hours==t.hours && this->minutes==t.minutes && this->seconds==t.seconds)
			return true;
		return false;
	}

	bool operator!=(const Time &t){
		if(this->hours==t.hours && this->minutes==t.minutes && this->seconds==t.seconds)
			return false;
		return true;
	}
	
	void get_valid_time(string prompt){
		cout<<prompt;
		cout<<"\n\t\t\tFormat: hours minutes seconds (eg: 16 45 00)\n\t\t\t>";
		cin>>hours;
		cin>>minutes;
		cin>>seconds;
		while(is_valid()==false){
			cout<<"\n\n\t\t\tERROR: invalid input date entered.";
			cout<<prompt;
			cout<<"\n\t\t\tFormat: hours minutes seconds (eg: 16 45 00)\n\t\t\t>";
			cin>>hours;
			cin>>minutes;
			cin>>seconds;

		}
	}

};

#endif



