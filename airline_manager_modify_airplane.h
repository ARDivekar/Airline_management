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


void get_airplane_details(Airplane *ap, bool get_id=true, bool ask_modify=false){
	
	int i,j;
	char select=' ';
	string attribute, str;
	for(i=0; i<4; i++){
		select=' ';
		switch(i){
			case 0: attribute="airport code of the airplane"; break;
			case 1: attribute="seating capacity of the airplane"; break;
			case 2: attribute="fuel capacity of the airplane"; break;
			case 3: attribute="airplane model of the airplane"; break;
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
				case 0: 
					cin.ignore();
					cin.clear(); 
					ap->current_location.get_valid_code("\n\t\t\tEnter airport code where aiplane is hangared (enter TRA if it is currently in transit)\n\t\t\t>");
					break;
				case 1: cout<<"\n\t\t\tEnter seating capacity:\n\t\t\t>";
					cin.clear();
					cin>>ap->seating_capacity;	
					break;
				case 2:cout<<"\n\t\t\tEnter fuel capacity:\n\t\t\t>";
					cin.clear();
					cin>>ap->fuel_capacity;
					break;
				case 3: cout<<"\n\t\t\tEnter airplane model:\n\t\t\t>";
					cin.clear();
					cin.ignore();
					getline(cin, str);
					for(j=0; j<str.length() && j<20; j++)
						ap->model[j]=str.at(j);
					ap->model[j]='\0';
					break;
			}
		}
	}
}


bool validate_airplane_details(Airplane *ap){
	bool valid=true;

	//check if current_location is a valid airport code
	if(ap->current_location!=*(new Airport_code("TRA")) && database.airport_map.find(ap->current_location.hash()) == database.airport_map.end()){
		cout<<"\n\n\t\t\tAirplane modification ERROR: no airport with entered airport code.";
		valid=false;
	}
	
	//check if seating capacity is not positive
	if(ap->seating_capacity <=0 ){
		cout<<"\n\n\t\t\tAirplane modification ERROR: seating capacity cannot be zero or negative.";
		valid=false;
	}

	//check if fuel capacity is not positive
	if(ap->fuel_capacity <=0 ){
		cout<<"\n\n\t\t\tAirplane modification ERROR: fuel capacity cannot be zero or negative.";
		valid=false;
	}

	return valid;

}


void save_airplane_details(Airplane *ap){
	if(database.airplane_map.find(ap->airplane_id) == database.airplane_map.end()) 	//no entry with such an airplane ID exists, i.e. we are making a new airplane entry
		ap->airplane_id=database.get_airplane_id();
	database.airplane_map.erase(ap->airplane_id);	//delete any existing entry
	database.airplane_map[ap->airplane_id]=(*ap);  //if entry exists, we update; else, we make a new entry and ID
	database.write_to_file_airplane();
}




void modify_airplane_details(){
	Airplane *ap=new Airplane();
	int select=-1;

	cout<<"\n\t\t\tWhat operation would you like to perform on the airplane table?\n\t\t\t1. Add new airplane.\n\t\t\t2. Modify airplane. \n\t\t\t3. Delete airplane\n\t\t\t>";
	cin.clear();
	cin>>select;
	while(select<1 || select>3){
		cout<<"\n\n\t\t\tERROR: invalid input.";
		cout<<"\n\t\t\tWhat operation would you like to perform on the airplane table?\n\t\t\t1. Add new airplane.\n\t\t\t2. Modify airplane. \n\t\t\t3. Delete airplane\n\t\t\t>";
		cin.clear();
		cin>>select;	
	}

	switch(select){
		case 3: 	//"Delete airplane"
			cout<<"\n\t\t\tEnter ID of airplane to delete:\n\t\t\t>";
			cin.clear();
			cin>>ap->airplane_id;
			if(database.airplane_map.find(ap->airplane_id) != database.airplane_map.end()){
				database.airplane_map.erase(ap->airplane_id);	
				cout<<"\n\n\t\t\tSuccessfully deleted airplane with ID "<<ap->airplane_id;
			}
			else {
				cout<<"\n\n\t\t\tAirplane modification ERROR: no airplane exists with airplane ID"<<ap->airplane_id;
			}
			
		return; 


		case 1:	//"add new airplane":
			get_airplane_details(ap, true);
			
			//if an airplane with this ID exists:			
			if(database.airplane_map.find(ap->airplane_id) != database.airplane_map.end()){
				cout<<"\n\n\t\t\tAirplane modification ERROR: airplane with this ID already exists";
				return;
			}
		break;

		
		case 2:	//"Modify airplane"
			cout<<"\n\t\t\tEnter the ID of the airplane you are modifying:\n\t\t\t>";
			cin.clear();
			cin>>ap->airplane_id;

			//if airplane with this ID exists:
			if(database.airplane_map.find(ap->airplane_id) != database.airplane_map.end()){	
				(*ap)= (database.airplane_map.find(ap->airplane_id))->second;	//copy airplane details
				get_airplane_details(ap, false, true);	//modify airplane details
			}
		
			else {	//if airplane with this ID does not exist:
				cout<<"\n\n\t\t\tAirplane modification ERROR: no airplane with this ID exists";
				return;
			}
		break;
	}
	
	
	if(validate_airplane_details(ap)){		//if airplane details are valid, continue
		save_airplane_details(ap);
		if(select ==2)
			cout<<"\n\n\t\t\tSuccessfully modified details of airplane "<<ap->airplane_id;
		else if(select==1) 
			cout<<"\n\n\t\t\tSuccessfully created airplane entry with ID = "<<ap->airplane_id;
	}	
	else {
		cout<<"\n\n\t\t\tERROR: unable to modify airplane details.";
	}

}


