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


#ifndef BOOKING
	#define BOOKING
	#include "booking.h"
#endif


#ifndef CUSTOMER_MAKE_BOOKING
	#define CUSTOMER_MAKE_BOOKING
	#include "customer_make_booking.h"
#endif


#ifndef CUSTOMER_DELETE_BOOKING
	#define CUSTOMER_DELETE_BOOKING
	#include "customer_delete_booking.h"
#endif


using namespace std;



/*A driver function is called by to allow a Customer to make a booking. This module calls other modules to initialte the booking sequence.*/
void make_booking(User* user);


/*A driver function is called by to allow a Customer to delete a booking. This module calls other modules to initialte the actions needed to delete a booking.*/
void delete_booking(User* user);


/*A module which is called by external modules to loads the customer page, which allows us to select from the various actions a customer can perform.*/
void load_customer_page(User* user){
	int select=-1;
while(true){
		cout<<"\n\n\t\tEnter your choice:\n\t\t1. Make new booking\n\t\t2. Delete existing booking\n\t\t3. Log Out\n\t\t>";
		cin.clear();
		cin>>select;
		switch(select){
			case 1: make_booking(user);
				break;
			case 2: delete_booking(user);
				break;
			case 3: cout<<"\n\n\t\tLogging out of Customer page...";
				return;
			default: cout<<"\n\n\t\tERROR: invalid option entered. Please try again";
		}
		select=-1;
	}

}
