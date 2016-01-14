#ifndef STRING
#define STRING
	#include<string>
#endif

#ifndef MISC
	#define MISC
	#include "misc.h"
#endif


#ifndef C_LIMITS
	#define C_LIMITS
	#include "limits.h"
#endif


using namespace std;


class Airplane{
	public:
	
	int airplane_id;
	Airport_code current_location;
	int seating_capacity;
	int fuel_capacity; //in miles
	char model[20];
	
		
	Airplane(){
		airplane_id=INT_MAX;
		seating_capacity=INT_MAX;
		fuel_capacity=INT_MAX;
		current_location=*(new Airport_code());
	}
	

	void print(int count){
		cout<<"\n\n\t\t\t"<<count<<". Airplane ID="<<airplane_id<<"\n\t\t\tCurrent Location: "; current_location.print(); cout<<"\n\t\t\tSeating capacity: "<<seating_capacity<<"\n\t\t\tFuel capacity: "<<fuel_capacity<<"\n\t\t\tModel: "<<string(model);
	}
};
