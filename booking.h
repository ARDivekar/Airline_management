#ifndef STRING
#define STRING
	#include<string>
#endif


#ifndef C_LIMITS
	#define C_LIMITS
	#include "limits.h"
#endif

using namespace std;

#ifndef FLIGHT_CLASS
	#define FLIGHT_CLASS
	enum Class{FIRST, BUSINESS, ECONOMY};
#endif

#ifndef MEAL_TYPE
	#define MEAL_TYPE
	enum Meal_type{VEG, NON_VEG, JAIN, KOSHER};	
#endif


class Booking{
	public:
	int booking_id;
	int flight_id;
	char username[50];
	Class booking_class;
	Meal_type meal_type;

	Booking(){
		booking_id=INT_MAX;
		flight_id=INT_MAX;
	}


};
