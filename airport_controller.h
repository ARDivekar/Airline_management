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


#ifndef AIRPORT_CONTROLLER_MODIFY_AIRPORT
	#define AIRPORT_CONTROLLER_MODIFY_AIRPORT
	#include "airport_controller_modify_airport.h"
#endif


#ifndef AIRPORT_CONTROLLER_VIEW_AIRPORT
	#define AIRPORT_CONTROLLER_VIEW_AIRPORT
	#include "airport_controller_view_airport.h"
#endif


using namespace std;


void modify_airport_details();



void view_airport_details();



void load_airport_controller_page(User *user){
	int select=-1;
	while(true){
		cout<<"\n\n\t\tEnter your choice:\n\t\t1. Modify airport details\n\t\t2. View airport details\n\t\t3. Log Out\n\t\t>";
		cin.clear();
		cin>>select;
		switch(select){
			case 1: modify_airport_details();
				break;
			case 2: view_airport_details();
				break;
			case 3: 	
				cout<<"\n\n\t\tLogging out of Airport Controller page...";
				return;
			default:	cout<<"\n\n\t\tERROR: invalid option entered. Please try again";
				break;
		}
		select=-1;

	}

}
