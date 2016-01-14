#ifndef STRING
#define STRING
	#include<string>
#endif

#ifndef IOSTREAM
#define IOSTREAM
	#include<iostream>
#endif

#ifndef MISC
	#define MISC
	#include "misc.h"
#endif



using namespace std;


class Airport{
	public:
	Airport_code airport_code;
	char name[50];
	char city[30];
	char state[30];
	char country[30];



	Airport(){
		name[0]=(char)0;
		city[0]=(char)0;
		state[0]=(char)0;
		country[0]=(char)0;
		airport_code=*(new Airport_code());
	}

	void print(int count){
		cout<<"\n\n\n\t\t\t"<<count<<". Airport code="; airport_code.print(); cout<<"\n\t\t\tAirport name: "<<string(name)<<"\n\t\t\tCity: "<<string(city)<<"\n\t\t\tState: "<<string(state)<<"\n\t\t\tCountry: "<<string(country);
	}	
};
