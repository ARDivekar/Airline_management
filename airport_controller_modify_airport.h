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



void get_airport_details(Airport *apt, bool get_airport_code, bool ask_modify=false){
	
	if(get_airport_code && !ask_modify){
		cin.clear();
		cin.ignore();
		apt->airport_code.get_valid_code("\n\t\t\tEnter airport code\n\t\t\t>");
	}

	
	char select=' ';
	string attribute, str;
	int i,j;
	for(i=0; i<4; i++){
		select=' ';
		switch(i){
			case 0: attribute="name of the airport"; break;
			case 1: attribute="city in which airport is situated"; break;
			case 2: attribute="state in which airport is situated"; break;
			case 3: attribute="country where the airport is situated"; break;
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
				case 0: cout<<"\n\t\t\tEnter the name of the airport:\n\t\t\t>";	
					cin.clear();
					cin.ignore();
					getline(cin, str);
					for(j=0; j<str.length() && j<50; j++)
						apt->name[j]=str.at(j);
					apt->name[j]='\0';
					break;

				case 1: cout<<"\n\t\t\tEnter the city in which airport is situated:\n\t\t\t>";
					cin.clear();
					cin.ignore();
					getline(cin, str);
					for(j=0; j<str.length() && j<30; j++)
						apt->city[j]=str.at(j);
					apt->city[j]='\0';
					break;

				case 2: cout<<"\n\t\t\tEnter the state in which airport is situated:\n\t\t\t>";
					cin.clear();
					cin.ignore();
					getline(cin, str);
					for(j=0; j<str.length() && j<30; j++)
						apt->state[j]=str.at(j);
					apt->state[j]='\0';
					break;

				case 3: cout<<"\n\t\t\tEnter the country where the airport is situated:\n\t\t\t>";
					cin.clear();
					cin.ignore();
					getline(cin, str);
					for(j=0; j<str.length() && j<30; j++)
						apt->country[j]=str.at(j);
					apt->country[j]='\0';
					break;
			}
		}
	}
}




bool validate_airport_details(Airport *apt){
	bool valid=true;
	
/*
	if(database.airport_map.find(apt->airport_code) == database.airport_map.end()){
		cout<<"\n\t\tAirport modification ERROR: no such airport code available.";
		valid=false;
	}
*/

	if(string(apt->name).length() > 50){
		cout<<"\n\n\t\t\tAirport modification ERROR: airport name cannot be more than 50 characters long.";
		valid=false;
	}
	
	if(string(apt->city).length() > 30){
		cout<<"\n\n\t\t\tAirport modification ERROR: airport city cannot be more than 30 characters long.";
		valid=false;
	}

	if(string(apt->state).length() > 30){
		cout<<"\n\n\t\t\tAirport modification ERROR: airport state cannot be more than 30 characters long.";
		valid=false;
	}

	if(string(apt->country).length() > 30){
		cout<<"\n\n\t\t\tAirport modification ERROR: airport country cannot be more than 30 characters long.";
		valid=false;
	}


	return valid;

}



void save_airport_details(Airport *apt){
	//Delete any existing airport entry with the same airprt code and add the new one.
	database.airport_map.erase(apt->airport_code.hash());
	database.airport_map[apt->airport_code.hash()]=(*apt);
	database.write_to_file_airport();
}




void modify_airport_details(){
	Airport *apt=new Airport();
	int select=-1;

	cout<<"\n\t\t\tWhat operation would you like to perform on the airport table?\n\t\t\t1. Add new airport.\n\t\t\t2. Modify airport. \n\t\t\t3. Delete airport\n\t\t\t>";
	cin.clear();
	cin>>select;
	while(select<1 || select>3){
		cout<<"\n\n\t\t\tERROR: invalid input.";
		cout<<"\n\t\t\tWhat operation would you like to perform on the airport table?\n\t\t\t1. Add new airport.\n\t\t\t2. Modify airport. \n\t\t\t3. Delete airport\n\t\t\t>";
		cin.clear();
		cin>>select;	
	}


	switch(select){
		case 3: 	//"Delete airport"
			cin.clear();
			cin.ignore();
			apt->airport_code.get_valid_code("\n\t\t\tEnter Airport Code of airport to delete:\n\t\t\t>");

			if(database.airport_map.find(apt->airport_code.hash()) != database.airport_map.end()){
				database.airport_map.erase(apt->airport_code.hash());
				cout<<"\n\n\t\t\tSuccessfully deleted airport with code "; apt->airport_code.print();
			}
			else {
				cout<<"\n\n\t\t\tAirport modification ERROR: no airport exists with airport code "; apt->airport_code.print();
			}
			
		return; 

			
		case 1:	//"add new airport":
			get_airport_details(apt,true);
			
			//if an airport with this airport code exists:			
			if(database.airport_map.find(apt->airport_code.hash()) != database.airport_map.end()){
				cout<<"\n\n\t\t\tAirport modification ERROR: airport with this airport code already exists";
				return;
			}
		break;

		
		case 2:	//"Modify airport"
			cin.clear();
			cin.ignore();
			apt->airport_code.get_valid_code("\n\t\t\tEnter the airport code of the airport you are modifying:\n\t\t\t>");

			//if airport with this airport code exists:
			if(database.airport_map.find(apt->airport_code.hash()) != database.airport_map.end()){
				(*apt)= (database.airport_map.find(apt->airport_code.hash()))->second;	//copy airport details
				get_airport_details(apt, false, true);	//modify airport details
			}
		
			else {	//if airport with this airport code does not exist:
				cout<<"\n\n\t\t\tAirport modification ERROR: no airport with this airport code exists";
				return;
			}
		break;
	}
	
	
	if(validate_airport_details(apt)){		//if airport details are valid, continue
		save_airport_details(apt);
		if(select ==2){
			cout<<"\n\n\t\t\tSuccessfully modified details of airport "; apt->airport_code.print();
		}
		else if(select==1){
			cout<<"\n\n\t\t\tSuccessfully created airport entry with airport code = "; apt->airport_code.print();
		}
	}	
	else {
		cout<<"\n\n\t\t\tERROR: unable to modify airport details.";
	}

}

