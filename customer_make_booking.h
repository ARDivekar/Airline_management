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


using namespace std;


/*	get_booking_details() obtains booking details of a user, in accordance to the Data Flow Diagram. 
This is called by make_booking()*/

Booking* get_booking_details(User* user){
	Booking *b=new Booking();
	Date input_date;
	Airport_code from_code, to_code;
	cin.clear();
	cin.ignore();
	from_code.get_valid_code("\n\t\t\tEnter 'From' airport code:\n\t\t\t>");
	cin.clear();
	to_code.get_valid_code("\n\t\t\tEnter 'To' airport code:\n\t\t\t>");
	/*cin.clear();
	input_date.get_valid_date("\n\t\t\tEnter date of flight:");*/
	
	//Now, we must list the available flights to the customer and let them select which flight to choose:
	std::map<int, Flight>::iterator iter;		//an iterator variable to iterate through the hashtable.
	int count=0;
	cout<<"\n\n\t\t\tFlights available from location "; from_code.print(); cout<<" to "; to_code.print(); /*cout<<" on date "; input_date.print(); */cout<<":";



	for(iter=database.flight_map.begin(); iter!=database.flight_map.end(); iter++){	//iterate through all flights in Flight table.
		Flight temp_fl=iter->second;
		if(temp_fl.remaining_seats_first != 0 || temp_fl.remaining_seats_business != 0 || temp_fl.remaining_seats_economy != 0){			/*look for flights that are not fully booked*/
			if(temp_fl.from==from_code && temp_fl.to==to_code){// && input_date==temp_fl.date){	/*look for flights with 'From', 'To' and 'Date' criterion as mentioned.*/ 
				/*Print details of such flights:*/
				count++;	
				temp_fl.print(count);
			}
		}
	}

	if(count==0){	//there are no flights on that day with that 'From' and that 'To' criterion.	
		cout<<"\n\t\t\tNone. Sorry.\n";
		return NULL;		//exit
	}
	
	//We have a list of flights.
	cout<<"\n\t\t\tWhich flight would you like to take? (enter corresponding Flight ID)\n\t\t\t>";
	cin.clear();
	cin>>b->flight_id;
	
	//copy  username of customer into 'username' field of Booking object.
	for(int i=0; user->username[i]!='\0'; i++)
		b->username[i]=user->username[i];

	//select travelling class:
	int select=-1;
	while(select<1 || select >3){		
		cout<<"\n\t\t\tWhich class would you like to travel?\n\t\t\t1.FIRST\n\t\t\t2.BUSINESS\n\t\t\t3.ECONOMY\n\t\t\t>";
		cin.clear();
		cin>>select;
		if (select<1 || select >3)
			cout<<"\n\n\t\t\tERROR: invalid entry for Booking travel-class.";
	}

	//set travelling class
	switch(select){
		case 1: b->booking_class=FIRST;
				break;
		case 2: b->booking_class=BUSINESS;
				break;
		case 3: b->booking_class=ECONOMY;
				break;
	}	


	//select meal type
	select=-1;
	while(select<1 || select >4){		
		cout<<"\n\t\t\tWhich type of meal would you like?\n\t\t\t1.VEG\n\t\t\t2.NON-VEG\n\t\t\t3.JAIN\n\t\t\t4.KOSHER\n\t\t\t>";
		cin.clear();
		cin>>select;
		if(select<1 || select >4)
			cout<<"\n\n\t\t\tERROR: invalid entry for Booking meal-type.";
	}

	//set meal type
	switch(select){
		case 1: b->meal_type=VEG;
				break;
		case 2: b->meal_type=NON_VEG;
				break;
		case 3: b->meal_type=JAIN;
				break;
		case 4: b->meal_type=KOSHER;
				break;
	}
	
	return b;

}





bool validate_booking(Booking *b){
	bool valid=true;

	//check if flight ID is negative
	if(b->flight_id<0){
		cout<<"\n\t\t\tBooking ERROR: Flight ID cannot be negative.";
		valid=false;
	}


	//check if flight exists:
	if(database.flight_map.find(b->flight_id) == database.flight_map.end()){
		cout<<"\n\t\t\tBooking ERROR: flight does not exist.";
		valid=false;
	}

	//check if the flight is not fully booked:

	switch(b->booking_class){		//reduce the number of available seats as a booking has been made
		case FIRST: 
			if(database.flight_map[b->flight_id].remaining_seats_first == 0) {
				cout<<"\n\t\t\tBooking ERROR: First class of this flight is fully booked.";
				valid=false;
			}
			break;
		case BUSINESS:
			if(database.flight_map[b->flight_id].remaining_seats_business == 0) {
				cout<<"\n\t\t\tBooking ERROR: Business class of this flight is fully booked.";
				valid=false;
			}
			break;
		case ECONOMY:
			if(database.flight_map[b->flight_id].remaining_seats_economy== 0) {
				cout<<"\n\t\tBooking ERROR: Economy class of this flight is fully booked.";
				valid=false;
			}
			break;
	}	

	

	//check if username exists:
	if(database.user_map.find(string(b->username)) == database.user_map.end()){
		cout<<"\n\t\t\tBooking ERROR: username does not exist.";
		valid=false;
	}

	return valid;
}





void save_booking_details(Booking *b){
	b->booking_id=database.get_booking_id();	/*requests the database for a system-generated booking ID. This will never be repeated.*/
	database.booking_map[b->booking_id]=(*b);	//save the booking in the booking table
	database.write_to_file_booking();	//write the booking table to disk.

	
	switch(b->booking_class){		//reduce the number of available seats as a booking has been made
		case FIRST: 
			database.flight_map[b->flight_id].remaining_seats_first--;		
			break;
		case BUSINESS:
			database.flight_map[b->flight_id].remaining_seats_business--;		
			break;
		case ECONOMY:
			database.flight_map[b->flight_id].remaining_seats_economy--;		
			break;
	}	
	database.write_to_file_flight();		//wrtie the flight table to disk.
}





void make_booking(User* user){
	int j=0;
	Booking *b=get_booking_details(user);

	if(b==NULL){
		cout<<"\n\t\t\tBooking status: No booking has been made.";
		return;
	}
	for(j=0; j<string(user->username).length(); j++)
		b->username[j]=user->username[j];
	b->username[j]='\0';
	
	if(validate_booking(b)){	
		//if the booking is valid, check if a booking with the same parameters has been made
		std::map<int, Booking>::iterator iter;
		for(iter=database.booking_map.begin(); iter!=database.booking_map.end(); iter++){
			Booking temp=iter->second;
			//check if flight ID & username matches, meaning we have duplicate bookings:
			if(temp.flight_id==b->flight_id && string(temp.username)==string(b->username)){	
				cout<<"\n\n\t\t\tBooking ERROR: You have already made a booking for this flight. You cannot make another.";
				return;
			}
		}
		
		//if the booking is not a duplicate, save it in the database.
		save_booking_details(b);
		cout<<"\n\n\t\t\tSuccessfully made booking with ID="<<b->booking_id<<endl;
	}
	else {
		cout<<"\n\n\t\t\tERROR: unable to make booking.\n";
	}

}


