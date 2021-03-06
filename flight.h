#ifndef STRING
#define STRING
	#include<string>
#endif

#ifndef IOSTREAM
#define IOSTREAM
	#include<iostream>
#endif

#ifndef MISC
	#define MISC
	#include "misc.h"
#endif


#ifndef C_LIMITS
	#define C_LIMITS
	#include "limits.h"
#endif


using namespace std;

#ifndef FLIGHT_CLASS
	#define FLIGHT_CLASS
	enum Class{FIRST, BUSINESS, ECONOMY};
#endif


class Flight{
	public:
	
	int flight_id;
	int airplane_id;
	Airport_code from;
	Airport_code to;
	Date date;
	Time time;
	int miles;	
	int remaining_seats_first;
	int remaining_seats_business;
	int remaining_seats_economy;
	int amount_first;
	int amount_business;
	int amount_economy;

	
	Flight(){
		flight_id=INT_MAX;
		airplane_id=INT_MAX;
		miles=-1;
		remaining_seats_first=-1;
		remaining_seats_business=-1;
		remaining_seats_economy=-1;
		amount_first=0;
		amount_business=0;
		amount_economy=0;
		from=*(new Airport_code());
		to=*(new Airport_code());
	}
	

	void print(int count){
		cout<<"\n\n\t\t\t"<<count<<". Flight ID = "<<flight_id<<"\n\t\t\tFrom: "; from.print(); cout<<"\n\t\t\tTo: "; to.print(); cout<<"\n\t\t\tDate: "; date.print(); cout<<"\n\t\t\tTime: "; time.print();
				cout<<"\n\t\t\tTicket prices:";
				cout<<"\n\t\t\t\tFirst class:\t"<<amount_first<<"\t Seats Remaining: "<<remaining_seats_first;
				cout<<"\n\t\t\t\tBusiness class:\t"<<amount_business<<"\t Seats Remaining: "<<remaining_seats_business;
				cout<<"\n\t\t\t\tEconomy class:\t"<<amount_economy<<"\t Seats Remaining: "<<remaining_seats_economy;
	}

};
