#ifndef STRING
#define STRING
	#include<string>
#endif


#ifndef C_LIMITS
	#define C_LIMITS
	#include "limits.h"
#endif


using namespace std;

#ifndef USER_TYPE
	#define USER_TYPE
	enum user_type {CUSTOMER, AIRL_MGR, AIRP_CON};
#endif



class User{
	public:
	
	char username[50];
	char password[50];	
	user_type type;
	char name[50];
	int age;
	char email[100];
	char phone[15];
	char gender;

	User(){
		age=INT_MAX;
		gender=' ';
	}

};



