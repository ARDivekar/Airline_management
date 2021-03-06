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


int get_deletion_details(User* user){
	int booking_id, i;
	cout<<"\n\t\t\tEnter booking ID (Enter -1 to list all bookings in your name):\n\t\t\t>";	
	cin.clear();
	cin>>booking_id;
	
	if(booking_id==-1){	//if the user does not know the booking ID, list all bookings made by them.
		std::map<int, Booking>::iterator iter;
		int count=0;
		cout<<"\n\t\t\tBooking made in your name (i.e. "<<string(user->username)<<"):";

		//iterate through the Bookings table, looking for bookings made with their username.
		for(iter=database.booking_map.begin(); iter!=database.booking_map.end(); iter++){
			Booking temp_b=iter->second;
			Flight temp_fl=database.flight_map[temp_b.flight_id];
			
			//if the user's username matches the booking's username, print details:
			if(string(temp_b.username)==string(user->username)){	
				count++;
				cout<<"\n\n\t\t\t"<<count<<". Booking ID="<<temp_b.booking_id<<"\n\t\t\tFrom: "; temp_fl.from.print(); cout<<"\n\t\t\tTo: "; temp_fl.to.print(); cout<<"\n\t\t\tDate: "; temp_fl.date.print(); cout<<"\n\t\t\tTime: "; temp_fl.time.print(); 

				cout<<"\n\t\t\tTravelling Class: ";
				switch(temp_b.booking_class){
					case FIRST: 
						cout<<"First";
						break;
					case BUSINESS:
						cout<<"Business";
						break;
					case ECONOMY:
						cout<<"Economy";				
						break;
				}	

				cout<<"\n\t\t\tTicket Price: ";
				switch(temp_b.booking_class){
					case FIRST: 
						cout<<temp_fl.amount_first;
						break;
					case BUSINESS:
						cout<<temp_fl.amount_business;
						break;
					case ECONOMY:
						cout<<temp_fl.amount_economy;	
						break;
				}
			}
		}	
		

		if(count==0){	//if no bookings made in user's name.
			cout<<"\n\t\t\tNone. Sorry.";
			return -1;	//informs calling module that we are not going to delete any booking.
		}
		
		cout<<"\n\n\n\t\t\tEnter booking ID:\n\t\t\t>";	
		cin.clear();
		cin>>booking_id;
		
	}

	return booking_id;
}






bool validate_booking_existence(int booking_id, User* user){
	bool valid=true;
	if(database.booking_map.find(booking_id) != database.booking_map.end()){	//if booking exists.
		Booking temp=database.booking_map[booking_id];
		if(string(temp.username)!=string(user->username)){	//if booking is not in the user's name.
			cout<<"\n\n\t\t\tBooking deletion ERROR: you cannot delete a booking which was not made in your name.";
			valid=false;
		}
	}
	else {
		cout<<"\n\n\t\t\tBooking deletion ERROR: no such booking ID.";
		valid=false;
	}

	return valid;
}




void delete_booking_details(int booking_id){
	Booking _b=database.booking_map[booking_id];
	Booking *b=&_b;
	switch(b->booking_class){		//increase the number of available seats as a booking has been removed
		case FIRST: 
			database.flight_map[b->flight_id].remaining_seats_first++;		
			break;
		case BUSINESS:
			database.flight_map[b->flight_id].remaining_seats_business++;		
			break;
		case ECONOMY:
			database.flight_map[b->flight_id].remaining_seats_economy++;		
			break;
	}	

	database.booking_map.erase(booking_id);	//erases the entry with the key booking_id

	database.write_to_file_flight();		//wrtie the flight table to disk.
}




void delete_booking(User* user){
	int booking_id=get_deletion_details(user);
	if(booking_id==-1){
		cout<<"\n\n\t\t\tBooking ERROR: Could not delete any bookings.";
		return;
	}
	if(validate_booking_existence(booking_id, user)){
		delete_booking_details(booking_id);
		cout<<"\n\n\t\t\tSuccessfully deleted booking with ID = "<<booking_id<<"\n";
	}
	else {
		cout<<"\n\n\t\t\tBooking ERROR: unable to delete booking.\n";
	}

}



