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


#ifndef AIRLINE_MANAGER_MODIFY_FLIGHT
	#define AIRLINE_MANAGER_MODIFY_FLIGHT
	#include "airline_manager_modify_flight.h"
#endif


#ifndef AIRLINE_MANAGER_MODIFY_AIRPLANE
	#define AIRLINE_MANAGER_MODIFY_AIRPLANE
	#include "airline_manager_modify_airplane.h"
#endif


#ifndef AIRLINE_MANAGER_VIEW_FLIGHT
	#define AIRLINE_MANAGER_VIEW_FLIGHT
	#include "airline_manager_view_flight.h"
#endif


#ifndef AIRLINE_MANAGER_VIEW_AIRPLANE
	#define AIRLINE_MANAGER_VIEW_AIRPLANE
	#include "airline_manager_view_airplane.h"
#endif


using namespace std;


void modify_flight_details();	//imported from "airline_manager_modify_flight.h"


void modify_airplane_details();	//imported from "airline_manager_modify_airplane.h"


void view_flight_details();		//imported from "airline_manager_view_flight.h"


void view_airplane_details();	//imported from "airline_manager_view_airplane.h"


void load_airline_manager_page(User *user){
	int select=-1;
	while(true){
		cout<<"\n\n\t\tEnter your choice:\n\t\t1. Modify flight details\n\t\t2. Modify airplane details\n\t\t3. View flight details\n\t\t4. View airplane details\n\t\t5. Log Out\n\t\t>";
		cin.clear();
		cin>>select;
		switch(select){
			case 1: modify_flight_details();
				break;
			case 2: modify_airplane_details();
				break;
			case 3: view_flight_details();
				break;
			case 4: view_airplane_details();
				break;
			case 5: cout<<"\n\n\t\tLogging out of Airline Manager page...";
				return;
			default: cout<<"\n\n\t\tERROR: invalid option entered. Please try again";

		}
		select=-1;
	}
}
