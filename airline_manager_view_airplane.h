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


void get_airplane_query_details(Airplane* ap_query){
	char yorn;
	string str;
	int j;

	string fields[]={"Airplane ID", "Current Location", "Seating capacity (greater than)", "Fuel capacity (greater than)", "Model"};
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
				case 0: cout<<"\n\t\t\tEnter Airplane ID:\n\t\t\t>";
						cin.clear();
						cin>>ap_query->airplane_id;
						return;		//airplane ID is sufficient to identify an airplane

				case 1: 
						cin.clear();
						cin.ignore();
						ap_query->current_location.get_valid_code("\n\t\t\tEnter airport code to search (enter TRA for transit):\n\t\t\t>");
						break;

				case 2: 						
						cout<<"\n\t\t\tEnter minimum seating capacity of airplane:\n\t\t\t>";
						cin.clear();
						cin>>ap_query->seating_capacity;
						break;

				case 3: 
						cout<<"\n\t\t\tEnter minimum fuel capacity of airplane:\n\t\t\t>";
						cin.clear();
						cin>>ap_query->fuel_capacity;
						break;

				case 4: cout<<"\n\t\t\tEnter airplane model:\n\t\t\t>";
						cin.clear();
						cin.ignore();
						getline(cin, str);
						for(j=0; j<str.length() && j<50; j++)
							ap_query->model[j]=str.at(j);
						ap_query->model[j]='\0';
						break;
				
			}	
		}
	}

}





bool validate_airplane_query(Airplane *ap_query){
	bool valid=true;
	if(ap_query->airplane_id < 0){
		cout<<"\n\n\t\t\tAirplane query ERROR: airplane ID cannot be negative.";
		valid=false;
	}
	
	if(ap_query->seating_capacity <= 0){
		cout<<"\n\n\t\t\tAirplane query ERROR: seating capacity must be positive.";
		valid=false;
	}

	if(ap_query->fuel_capacity <= 0){
		cout<<"\n\n\t\t\tAirplane query ERROR: fuel capacity must be positive.";
		valid=false;
	}

	if(string(ap_query->model).length() > 20){
		cout<<"\n\n\t\t\tAirplane query ERROR: model name cannot be more than 20 characters.";
		valid=false;
	}
	
	return valid;

}



void execute_airplane_query(Airplane *ap_query){

	/*The folowing are the defualt values for all the fields in the 'Airplane' query
	If one of the entered fields matches its corresponding default value, we do not include that field in the search criterion:*/
	Airplane empty_ap=*(new Airplane());
	Airport_code empty_ac=*(new Airport_code());
	
	//iterate through the Airplane table and print any airplanes matching the entered criterion:
	std::map<int, Airplane>::iterator iter; 	
	int count=0;
	cout<<"\n\n\t\t\t<---------------Airplane query output--------------->\n";

	for(iter=database.airplane_map.begin(); iter!=database.airplane_map.end(); iter++){
			Airplane temp_ap=iter->second;

			if(ap_query->airplane_id!= empty_ap.airplane_id && temp_ap.airplane_id!=ap_query->airplane_id)
				continue;

			if(ap_query->current_location !=empty_ac && ap_query->current_location!=temp_ap.current_location)
				continue;

			if(ap_query->seating_capacity !=empty_ap.seating_capacity && ap_query->seating_capacity!=temp_ap.seating_capacity)
				continue;
			
			if(ap_query->fuel_capacity !=empty_ap.fuel_capacity && ap_query->fuel_capacity!=temp_ap.fuel_capacity)
				continue;

			if(string(ap_query->model) != string(empty_ap.model) && string(ap_query->model)!=string(temp_ap.model))
				continue;

			count++;
			temp_ap.print(count);
		
	}
	cout<<"\n\n\t\t\t<---------------End of Airplane query output--------------->\n";
}



void view_airplane_details(){
	Airplane *ap_query=new Airplane();
	get_airplane_query_details(ap_query);
	if(validate_airplane_query(ap_query)){
		execute_airplane_query(ap_query);
	}
	else {
		cout<<"\n\n\t\t\tERROR: invalid Airplane query entered.";
	}
}
