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


void get_airport_query_details(Airport* apt_query){
	char yorn;
	string str;
	int j;

	string fields[]={"Airport code", "Airport name", "City", "State", "Country"};
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
				case 0: cin.clear();
						cin.ignore();
						apt_query->airport_code.get_valid_code("\n\t\t\tEnter Airport code:\n\t\t\t>");
						return;		//Airport code is sufficient to identify an airport

				case 1: 
						cout<<"\n\t\t\tEnter name of airport:\n\t\t\t>";
						cin.clear();
						cin.ignore();
						getline(cin, str);
						for(j=0; j<str.length() && j<50; j++)
							apt_query->name[j]=str.at(j);
						break;

				case 2: 						
						cout<<"\n\t\t\tEnter city of airport:\n\t\t\t>";
						cin.clear();
						cin.ignore();
						getline(cin, str);
						for(j=0; j<str.length() && j<50; j++)
							apt_query->city[j]=str.at(j);
						apt_query->city[j]='\0';
						break;

				case 3: 
						cout<<"\n\t\t\tEnter state of airport:\n\t\t\t>";
						cin.clear();
						cin.ignore();
						getline(cin, str);
						for(j=0; j<str.length() && j<50; j++)
							apt_query->state[j]=str.at(j);
						apt_query->state[j]='\0';
						break;

				case 4: 
						cout<<"\n\t\t\tEnter country of airport:\n\t\t\t>";
						cin.clear();
						cin.ignore();
						getline(cin, str);
						for(j=0; j<str.length() && j<50; j++)
							apt_query->country[j]=str.at(j);
						apt_query->country[j]='\0';
						break;
				
			}	
		}
	}

}





bool validate_airport_query(Airport *apt_query){
	bool valid=true;
	if(string(apt_query->name).length() > 50){
		cout<<"\n\n\t\t\tAirport query ERROR: airport name cannot be more than 50 characters long.";
		valid=false;
	}

	if(string(apt_query->city).length() > 30){
		cout<<"\n\n\t\t\tAirport query ERROR: airport city cannot be more than 30 characters long.";
		valid=false;
	}

	if(string(apt_query->state).length() > 30){
		cout<<"\n\n\t\t\tAirport query ERROR: airport state cannot be more than 30 characters long.";
		valid=false;
	}

	if(string(apt_query->country).length() > 30){
		cout<<"\n\n\t\t\tAirport query ERROR: airport country cannot be more than 30 characters long.";
		valid=false;
	}
	
	return valid;

}



void execute_airport_query(Airport *apt_query){

	/*The folowing are the defualt values for all the fields in the 'Airport' query
	If one of the entered fields matches its corresponding default value, we do not include that field in the search criterion:*/
	Airport empty_apt=*(new Airport());
	Airport_code empty_ac=*(new Airport_code());
	
	//iterate through the Airport table and print any airports matching the entered criterion:
	std::map<int, Airport>::iterator iter; 	
	int count=0;
	cout<<"\n\n\t\t\t<---------------Airport query output--------------->\n";

	for(iter=database.airport_map.begin(); iter!=database.airport_map.end(); iter++){
			Airport temp_apt=iter->second;

			if(apt_query->airport_code !=empty_ac && apt_query->airport_code!=temp_apt.airport_code)
				continue;

			if(string(apt_query->name) != string(empty_apt.name) && string(apt_query->name) != string(temp_apt.name))
				continue;

			if(string(apt_query->city) != string(empty_apt.city) && string(apt_query->city) != string(temp_apt.city))
				continue;

			if(string(apt_query->state) != string(empty_apt.state) && string(apt_query->state) != string(temp_apt.state))
				continue;

			if(string(apt_query->country) != string(empty_apt.country) && string(apt_query->country) != string(temp_apt.country))
				continue;

			count++;
			temp_apt.print(count);
		
	}
	cout<<"\n\n\t\t\t<---------------End of Airport query output--------------->\n";
}



void view_airport_details(){
	Airport *apt_query=new Airport();
	get_airport_query_details(apt_query);
	if(validate_airport_query(apt_query)){
		cout<<"\n\t\t\tExecuting Airport query.....";
		execute_airport_query(apt_query);
	}
	else {
		cout<<"\n\n\t\t\tERROR: invalid Airport query entered.";
	}
}






