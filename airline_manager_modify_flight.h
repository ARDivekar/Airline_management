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

/*
void get_basic_flight_details(Flight *fl){
	/*The following are all necessary details, and do not change with the ID*
	fl->from.get_valid_code("\n\t\t\tEnter 'From' airport code:\n\t\t\t>");

	fl->to.get_valid_code("\n\t\t\tEnter 'To' airport code:\n\t\t\t>");

	cout<<"\n\t\t\tEnter the airplane id:\n\t\t\t>";	
	cin>>fl->airplane_id;

	fl->date.get_valid_date("\n\t\t\tEnter the date of the flight");

	fl->time.get_valid_time("\n\t\t\tEnter the time of the flight");
	fl->time.seconds=00;
}
*/


/*get those details required for a full flight table entry. This module is only called when adding details or modifying details*/
void get_flight_details(Flight *fl, bool ask_modify=false){ 

	char select=' ';
	string attribute;
	for(int i=0; i<12; i++){
		select=' ';
		switch(i){
			case 0: attribute="Airplane ID"; break;
			case 1: attribute="'From' airport code"; break;
			case 2: attribute="'To' airport code"; break;
			case 3: attribute="Date of flight"; break;
			case 4: attribute="Time of flight"; break;
			case 5: attribute="number of miles of the flight"; break;
			case 6: attribute="number of First Class seats available on flight"; break;
			case 7: attribute="number of Business Class seats available on flight"; break;
			case 8: attribute="number of Economy Class seats available on flight"; break;
			case 9: attribute="flight cost for First Class passengers"; break;
			case 10: attribute="flight cost for Business Class passengers"; break;
			case 11: attribute="flight cost for Economy Class passengers"; break;
		}
		
		if(ask_modify){
			while(select != 'n' && select !='N' && select!='y' && select!='Y'){ 
				cout<<"\n\t\t\tModify the "<<attribute<<"? (Y / n)\n\t\t\t>";
				cin.clear();
				cin>>select;
				if(select != 'n' && select !='N' && select!='y' && select!='Y')
					cout<<"\n\n\t\t\tERROR: invalid input";
			}
		}

		if(!ask_modify || select=='y' || select == 'Y'){
			switch(i){
				case 0: cout<<"\n\t\t\tEnter the airplane ID of airplane used for flight:\n\t\t\t>";
					cin.clear();
					cin>>fl->airplane_id;
					break;
				case 1:
					cin.ignore();
					cin.clear(); 
					fl->from.get_valid_code("\n\t\t\tEnter the 'From' airport code:\n\t\t\t>");
					break;
				case 2: 
//					cin.ignore();
					cin.clear();
					fl->to.get_valid_code("\n\t\t\tEnter the 'To' airport code:\n\t\t\t>");
					break;
				case 3: 
					cin.clear();
					fl->date.get_valid_date("\n\t\t\tEnter date of flight");
					break;
				case 4: 
					cin.clear();
					fl->time.get_valid_time("\n\t\t\tEnter time of flight");
					break;
				case 5: cout<<"\n\t\t\tEnter the number of miles of the flight:\n\t\t\t>";
					cin.clear();
					cin>>fl->miles;
					break;
				case 6: cout<<"\n\t\t\tEnter the number of First Class seats available on flight:\n\t\t\t>";
					cin.clear();
					cin>>fl->remaining_seats_first;
					break;
				case 7: cout<<"\n\t\t\tEnter the number of Business Class seats available on flight:\n\t\t\t>";
					cin.clear();
					cin>>fl->remaining_seats_business;
					break;
				case 8: cout<<"\n\t\t\tEnter the number of Economy Class seats available on flight:\n\t\t\t>";
					cin.clear();
					cin>>fl->remaining_seats_economy;
					break;
				case 9: cout<<"\n\t\t\tEnter the flight cost for First Class passengers:\n\t\t\t>";
					cin.clear();
					cin>>fl->amount_first;		 
					break;
				case 10: cout<<"\n\t\t\tEnter the flight cost for Business Class passengers:\n\t\t\t>";
					cin.clear();
					cin>>fl->amount_business;
					break;
				case 11: cout<<"\n\t\t\tEnter the flight cost for Economy Class passengers:\n\t\t\t>";
					cin.clear();
					cin>>fl->amount_economy;
					break;
			}
		}

	}
	
}



bool validate_flight_details(Flight *fl, bool ask_modify=false){
	bool valid=true;

	//check if airport code in 'From' field exists:
	if(database.airport_map.find(fl->from.hash()) == database.airport_map.end()){
		cout<<"\n\t\t\tFlight modification ERROR: no such airport code in 'From' field.";
		valid=false;
	}
	
	//check if airport code in 'To' field exists:
	if(database.airport_map.find(fl->to.hash()) == database.airport_map.end()){
		cout<<"\n\t\t\tFlight modification ERROR: no such airport code in 'To' field.";
		valid=false;
	}

	//check if airplane exists:
	if(database.airplane_map.find(fl->airplane_id) == database.airplane_map.end()){
		cout<<"\n\t\t\tFlight modification ERROR: no such airplane ID.";
		valid=false;
	}
	else if(database.airplane_map[fl->airplane_id].seating_capacity < (fl->remaining_seats_first+fl->remaining_seats_business+fl->remaining_seats_economy)){
			//check if airplane can seat as many passengers as required.
			cout<<"\n\t\t\tFlight modification ERROR: the airplane with specified ID cannot hold so many passengers.";
			valid=false;
		
	}
	
	//check that miles are not negative.
	if(fl->miles<=0){
		cout<<"\n\t\t\tFlight modification ERROR: number of miles cannot be zero or negative.";
		valid=false;
	}


	//check for valid date:
	if(fl->date.is_valid()==false){
		cout<<"\n\t\t\tFlight modification ERROR: date entered is invalid.";
		valid=false;
	}

	//check for valid time:
	if(fl->time.is_valid()==false){
		cout<<"\n\t\t\tFlight modification ERROR: time entered is invalid.";
		valid=false;
	}


	//check if the amounts entered are non-negative:
	if(fl->amount_first<0){
		cout<<"\n\t\t\tFlight modification ERROR: ticket amount for First Class cannot be negative.";
		valid=false;
	}
	
	if(fl->amount_business<0){
		cout<<"\n\t\t\tFlight modification ERROR: ticket amount for Business Class cannot be negative.";
		valid=false;
	}

	if(fl->amount_economy<0){
		cout<<"\n\t\t\tFlight modification ERROR: ticket amount for Economy Class cannot be negative.";
		valid=false;
	}

	if(!ask_modify){
		//check if a flight with these details already exists:
		std::map<int, Flight>::iterator iter;		
		for(iter=database.flight_map.begin(); iter!=database.flight_map.end(); iter++){
			Flight temp=iter->second;
			//if there already exists a similar flight in the database:
			if((temp.from==fl->from) && (temp.to==fl->to) && (temp.airplane_id==fl->airplane_id) && (temp.time==fl->time) && (temp.date==fl->date)){ 
				cout<<"\n\n\t\t\tFlight modification ERROR: Flight with ID="<<temp.flight_id<<" already exists with these details, you cannot add a flight with these details.";	
				valid=false;
			}
		}
	}

	return valid;
}




void save_flight_details(Flight *fl){
	/*If present, delete and replace. Else, make new flight entry with new ID*/
	if(database.flight_map.find(fl->flight_id) == database.flight_map.end())  
		fl->flight_id=database.get_flight_id();	//gets auto-incremented value of flight_id from system if there is no flight already.
	database.flight_map.erase(fl->flight_id);	//deletes it if it is there	
	database.flight_map[fl->flight_id]=(*fl);	//makes fresh entry
	database.write_to_file_flight();
}





void modify_flight_details(){
	/*this is a consolidated module that modifies the flight table. This includes entering flights which are not there, deleting ones which are there, and changing flight details.*/
	Flight *fl=new Flight();
	char yorn=' ';
	int select=-1;
	cout<<"\n\t\t\tWhat operation would you like to perform on the flight table?\n\t\t\t1. Add new flight.\n\t\t\t2. Modify Flight. \n\t\t\t3. Delete flight\n\t\t\t>";
	cin.clear();
	cin>>select;
	while(select<1 || select>3){
		cout<<"\n\n\t\t\tERROR: invalid input.";
		cout<<"\n\t\t\tWhat operation would you like to perform on the flight table?\n\t\t\t1. Add new flight.\n\t\t\t2. Modify Flight. \n\t\t\t3. Delete flight\n\t\t\t>";
		cin.clear();
		cin>>select;	
	}


	switch(select){
		case 3: 	//"Delete flight"
			cout<<"\n\t\t\tEnter ID of flight to delete:\n\t\t\t>";
			cin.clear();
			cin>>fl->flight_id;
			if(database.flight_map.find(fl->flight_id) != database.flight_map.end()){
				database.flight_map.erase(fl->flight_id);	
				cout<<"\n\n\t\t\tSuccessfully deleted Flight with ID "<<fl->flight_id;
			}
			else {
				cout<<"\n\n\t\t\tFlight modification ERROR: no such flight exists with flight ID"<<fl->flight_id;
			}
			
		return; 

			
		case 1:	//"add new flight":
			get_flight_details(fl, false);
		break;

		
		case 2:	//"Modify flight"
			cout<<"\n\t\t\tEnter the ID of the flight you are modifying:\n\t\t\t>";
			cin.clear();
			cin>>fl->flight_id;

			//if flight with this ID exists
			if(database.flight_map.find(fl->flight_id) != database.flight_map.end()){	
				(*fl)= (database.flight_map.find(fl->flight_id))->second;	//copy flight details
				cin.clear();
				get_flight_details(fl, true);
			}
		
			else {	//if flight with this ID does not exist:
				cout<<"\n\n\t\t\tFlight modification ERROR: no such flight exists";
				return;
			}
		break;
	}
	
	if(select==1){ //add new flight
		if(validate_flight_details(fl)){
			save_flight_details(fl);	
			cout<<"\n\n\t\t\tSuccessfully created flight "<<fl->flight_id<<"\n";
		}
		else cout<<"\n\n\t\t\tERROR: unable to add new flight details.\n";
	}

	if(select==2){
		if(validate_flight_details(fl, true)){ //we are modifying the flight
			save_flight_details(fl);
			cout<<"\n\n\t\t\tSuccessfully modified details of flight "<<fl->flight_id<<"\n";
		}
		else cout<<"\n\n\t\t\tERROR: unable to modify flight details.\n";

	}
	
		
	
}





