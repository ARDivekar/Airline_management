#ifndef STRING
#define STRING
	#include<string>
#endif

#ifndef IOSTREAM
#define IOSTREAM
	#include<iostream>
#endif

#ifndef USER
	#define USER
	#include "user.h"
#endif

#ifndef DATABASE
	#define DATABASE
	#include "database.h"
#endif


#ifndef MISC
	#define MISC
	#include "misc.h"
#endif


using namespace std;


void get_flight_query_details(Flight* fl_query){
	char yorn;
	string str;

	string fields[]={"Flight ID", "Airplane ID", "'From' airport code", "'To' airport code", "Date", "Time"};
	for(int i=0; i<sizeof(fields)/8; i++){
		yorn='t';
		while(yorn!='Y' && yorn!='y' && yorn!='N' && yorn!='n'){
			cout<<"\n\t\t\tQuery contains "<<fields[i]<<"? (Y / n)\n\t\t\t>";	//prompt user for entering appropriate field
			cin.clear();
			cin>>yorn;
			if(yorn!='Y' && yorn!='y' && yorn!='N' && yorn!='n')
				cout<<"\n\n\t\t\tERROR: invalid input.";
		}

		if(yorn=='Y' || yorn=='y'){
			switch(i){
				case 0: cout<<"\n\t\t\tEnter Flight ID:\n\t\t\t>";
						cin.clear();
						cin>>fl_query->flight_id;
						return;		//flight ID is sufficient to identify a flight
				case 1: cout<<"\n\t\t\tEnter Airplane ID:\n\t\t\t>";
						cin.clear();
						cin>>fl_query->airplane_id;
						break;	

				case 2: 
						cin.clear();
						cin.ignore();
						fl_query->from.get_valid_code("\n\t\t\tEnter 'From' airport code:\n\t\t\t>");
						break;

				case 3: 						
						cin.clear();
						cin.ignore();
						fl_query->to.get_valid_code("\n\t\t\tEnter 'To' airport code:\n\t\t\t>");
						break;

				case 4: 
						cin.clear();
						fl_query->date.get_valid_date("\n\t\t\tEnter date of flight");
						break;

				case 5: 
						cin.clear();
						fl_query->time.get_valid_time("\n\t\t\tEnter time of flight");
						fl_query->time.seconds=00;
						break;
				
			}	
		}
	}

}




bool validate_flight_query(Flight *fl_query){
	bool valid=true;
	if(fl_query->flight_id < 0){
		cout<<"\n\n\t\t\tFlight query ERROR: Flight ID cannot be negative.";
		valid=false;
	}
	
	if(fl_query->airplane_id < 0){
		cout<<"\n\n\t\t\tFlight query ERROR: airplane ID cannot be negative.";
		valid=false;
	}
	
	
	return valid;

}



void execute_flight_query(Flight *fl_query){

	/*The folowing are the defualt values for all the fields in the 'Flight' query
	If one of the entered fields matches its corresponding default value, we do not include that field in the search criterion:*/
	Flight empty_fl=*(new Flight());
	Airport_code empty_ac=*(new Airport_code());
	Date empty_date=*(new Date());
	Time empty_time=*(new Time());

	//iterate through the Flight table and print any flights matching the entered criterion:
	std::map<int, Flight>::iterator iter; 	
	int count=0;
	cout<<"\n\n\t\t\t<---------------Flight query output--------------->\n";

	for(iter=database.flight_map.begin(); iter!=database.flight_map.end(); iter++){
			Flight temp_fl=iter->second;

			if(fl_query->flight_id!= empty_fl.flight_id && temp_fl.flight_id!=fl_query->flight_id)
				continue;
			
			if(fl_query->airplane_id!= empty_fl.airplane_id && temp_fl.airplane_id!=fl_query->airplane_id)
				continue;
			
			if(fl_query->from != empty_ac && fl_query->from!=temp_fl.from)
				continue;

			if(fl_query->to !=empty_ac && fl_query->to!=temp_fl.to)
				continue;

			if(fl_query->date != empty_date && fl_query->date!=temp_fl.date)
				continue;

			if(fl_query->time != empty_time && fl_query->time!=temp_fl.time)
				continue;
			

			count++;
			temp_fl.print(count);
		
	}
	cout<<"\n\n\t\t\t<---------------End of Flight query output--------------->\n";
}





void view_flight_details(){
	Flight *fl_query=new Flight();
	get_flight_query_details(fl_query);
	if(validate_flight_query(fl_query)){
		execute_flight_query(fl_query);
	}
	else {
		cout<<"\n\n\t\t\tERROR: invalid Flight query entered.";
	}
}

