#ifndef MAP
#define MAP
	#include<map>
#endif


#ifndef STRING
#define STRING
	#include<string>
#endif


#ifndef IOSTREAM
#define IOSTREAM
	#include<iostream>
#endif


#ifndef FSTREAM
	#define FSTREAM
	#include<fstream>
#endif


#ifndef USER
	#define USER
	#include "user.h"
#endif


#ifndef FLIGHT
	#define FLIGHT
	#include "flight.h"
#endif


#ifndef AIRPLANE
	#define AIRPLANE
	#include "airplane.h"
#endif


#ifndef AIRPORT
	#define AIRPORT
	#include "airport.h"
#endif


#ifndef BOOKING
	#define BOOKING
	#include "booking.h"
#endif


#ifndef MISC
	#define MISC
	#include "misc.h"
#endif


using namespace std;


int max(int a, int b){
	if(a>b) return a;
	else return b;
}



class Database{
/*	The application stores data permanently on disk by means of the database class.
	This is a centralized module which allows access to all the necessary functions via several entry points, thus providing informational cohesion.*/


	private:

	/*The following variables store the names of the database files on disk:	*/
	string users_file_name;
	string flight_file_name;
	string airplane_file_name;
	string airport_file_name;
	string booking_file_name;
	
	/*The following are system-generated variables that must be auto-incremented every time a new item is required:	*/
	int current_flight_id;
	int current_airplane_id;
	int current_booking_id;


	public:
/*	While the application is being used, the database is stored in main memory as a series of hash tables. These correspond to the tables in the ER diagram.
	When the application starts, these hash tables are loaded into main memory from 'database files' stored on disk, using functions with syntax:		load_file_<table name>() 
	Changes made to the hash tables are saved using functions with syntax:		write_to_file_<table name>()
*/

	std::map<string, User> user_map;
	std::map<int, Flight> flight_map;
	std::map<int, Airplane> airplane_map;
	std::map<int, Airport> airport_map;
	std::map<int, Booking> booking_map;

	
/*	The constructor for the database class allows us to set the various database file names; if no input value given, set to the default.
	The constructor also sets the values of the system-generated variables to zero. If the corresponding database files exist, they are overwritten when we load the files.*/

	Database(	string users_file_name="Users.data",
			string flight_file_name="Flights.data", 
			string airplane_file_name="Airplanes.data", 
			string airport_file_name="Airports.data", 
			string booking_file_name="Bookings.data")
	{
		
		/*Set the value of the required database files.*/
		this->users_file_name=users_file_name;
		this->flight_file_name=flight_file_name;
		this->airplane_file_name=airplane_file_name;
		this->airport_file_name=airport_file_name;
		this->booking_file_name=booking_file_name;

		
		/*Create files if they don't exist:*/
		fstream file;
		string temp_file_name;
		for(int i=1; i<=5; i++){
			switch(i){
				case 1: temp_file_name=users_file_name; break;
				case 2: temp_file_name=flight_file_name; break;
				case 3: temp_file_name=airplane_file_name; break;
				case 4: temp_file_name=airport_file_name; break;
				case 5: temp_file_name=booking_file_name; break;
			}

			file.open(temp_file_name.c_str(), ios::binary | ios::in);
			if(!file.is_open()){
				file.close();
				file.open(temp_file_name.c_str(), ios::binary | ios::out | ios::trunc);
			}
			file.close();
		}


		/*The values of the following system-generated variables should get overwritten if the database files exist:	*/
		current_flight_id=0;  
		current_airplane_id=0;
		current_booking_id=0;
	}	



	void load_files();		//loads all the database files from disk.
	/*list of individual loading modules:*/
	void load_file_user();
	void load_file_flight();
	void load_file_airplane();
	void load_file_airport();
	void load_file_booking();


	void write_to_file();		//saves all the database files to disk.
	/*list of individual storing modules:*/
	void write_to_file_user();
	void write_to_file_flight();
	void write_to_file_airplane();
	void write_to_file_airport();
	void write_to_file_booking();


	/*The following functions allow the application to get auto-incremented values of the system-generated variables without allowing explicit access from other modules.*/
	int get_flight_id();
	int get_airplane_id();
	int get_booking_id();



	/*Print the entire database, mostly for debugging purposes:	*/
	void print_database(){
		std::map<string, User>::iterator iter;
		for(iter=user_map.begin(); iter!=user_map.end(); iter++){
			User user=iter->second;
			cout<<user.name<<endl;
		}
	}



	/*Delete all data from the database, start with a fresh application:	*/
	void truncate_database(){
		fstream file;
		file.open(users_file_name.c_str(), ios::trunc | ios::binary | ios::out);
		file.close();
	}

}database; //creates a database object which will be used throughout the application.








/*The following function loads all the files:	*/	
void Database::load_files(){
	load_file_user();	
	load_file_flight();	
	load_file_airplane();	
	load_file_airport();	
	load_file_booking();	
}




/*The following functions are used to load each database file individully:	*/

void Database::load_file_user(){
	ifstream fin;	
	fin.open(users_file_name.c_str(), ios::binary);
	User user=*(new User());
	if(fin.is_open()){
		user_map=*(new std::map<string, User>());
		while(fin.read((char*)&user, sizeof(user))){
			user_map[string(user.username)]=user;
		}
	}
	else{
		cout<<"\n\t\tERROR: cannot open file "<<users_file_name<<". Please confirm that file exists";
	}
}



void Database::load_file_flight(){
	ifstream fin;	
	fin.open(flight_file_name.c_str(), ios::binary);
	Flight fl=*(new Flight());
	if(fin.is_open()){
		current_flight_id=-1;
		flight_map=*(new std::map<int, Flight>());
		while(fin.read((char*)&fl, sizeof(fl))){
			flight_map[fl.flight_id]=fl;
			current_flight_id=max(current_flight_id, fl.flight_id);
		}
		
	}
	else{
		cout<<"\n\t\tERROR: cannot open file "<<flight_file_name<<". Please confirm that file exists";
	}
}




void Database::load_file_airplane(){
	ifstream fin;	
	fin.open(airplane_file_name.c_str(), ios::binary);
	Airplane ap=*(new Airplane());
	if(fin.is_open()){
		current_airplane_id=-1;
		airplane_map=*(new std::map<int, Airplane>());
		while(fin.read((char*)&ap, sizeof(ap))){
			airplane_map[ap.airplane_id]=ap;
			current_airplane_id=max(current_airplane_id, ap.airplane_id);
		}
	}
	else{
		cout<<"\n\t\tERROR: cannot open file "<<airplane_file_name<<". Please confirm that file exists";
	}
}



void Database::load_file_airport(){
	ifstream fin;	
	fin.open(airport_file_name.c_str(), ios::binary);
	Airport apt=*(new Airport());
	if(fin.is_open()){
		airport_map=*(new std::map<int, Airport>());
		while(fin.read((char*)&apt, sizeof(apt))){
			airport_map[apt.airport_code.hash()]=apt;
		}
	}
	else{
		cout<<"\n\t\tERROR: cannot open file "<<airport_file_name<<". Please confirm that file exists";
	}
}




void Database::load_file_booking(){
	ifstream fin;	
	fin.open(booking_file_name.c_str(), ios::binary);
	Booking b=*(new Booking());
	if(fin.is_open()){
		current_booking_id=-1;
		booking_map=*(new std::map<int, Booking>());
		while(fin.read((char*)&b, sizeof(b))){
			booking_map[b.booking_id]=b;
			current_booking_id=max(current_booking_id, b.booking_id);
		}
		
	}
	else{
		cout<<"\n\t\tERROR: cannot open file "<<booking_file_name<<". Please confirm that file exists";
	}
}



/*The following function saves all the files:	*/	
void Database::write_to_file(){
	write_to_file_user();
	write_to_file_flight();
	write_to_file_airplane();
	write_to_file_airport();
	write_to_file_booking();
}





/*The following functions are used to save changes to databases files, individully:	*/

void  Database::write_to_file_user(){
	ofstream fout;
	fout.open(users_file_name.c_str(), ios::trunc | ios::binary);
	std::map<string, User>::iterator iter;
	for(iter=user_map.begin(); iter!=user_map.end(); iter++){
		User user=iter->second;
		fout.write((char*)&user,sizeof(user));
	}
}



void Database::write_to_file_flight(){
	ofstream fout;
	fout.open(flight_file_name.c_str(), ios::trunc | ios::binary);
	std::map<int, Flight>::iterator iter;
	for(iter=flight_map.begin(); iter!=flight_map.end(); iter++){
		Flight fl=iter->second;
		fout.write((char*)&fl,sizeof(fl));
	}
}



void Database::write_to_file_airplane(){
	ofstream fout;
	fout.open(airplane_file_name.c_str(), ios::trunc | ios::binary);
	std::map<int, Airplane>::iterator iter;
	for(iter=airplane_map.begin(); iter!=airplane_map.end(); iter++){
		Airplane ap=iter->second;
		fout.write((char*)&ap,sizeof(ap));
	}
}



void Database::write_to_file_airport(){
	ofstream fout;
	fout.open(airport_file_name.c_str(), ios::trunc | ios::binary);
	std::map<int, Airport>::iterator iter;
	for(iter=airport_map.begin(); iter!=airport_map.end(); iter++){
		Airport apt=iter->second;
		fout.write((char*)&apt,sizeof(apt));
	}
}



void Database::write_to_file_booking(){
	ofstream fout;
	fout.open(booking_file_name.c_str(), ios::trunc | ios::binary);
	std::map<int, Booking>::iterator iter;
	for(iter=booking_map.begin(); iter!=booking_map.end(); iter++){
		Booking b=iter->second;
		fout.write((char*)&b,sizeof(b));
	}
}






/*The following functions allow the application to get auto-incremented values of the system-generated variables without allowing explicit access from other modules.*/
int Database::get_flight_id(){
	current_flight_id++;
	return current_flight_id;
}

int Database::get_airplane_id(){
	current_airplane_id++;
	return current_airplane_id;
}

int Database::get_booking_id(){
	current_booking_id++;
	return current_booking_id;
}


