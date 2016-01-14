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


using namespace std;

/*	A driver function is called by external modules to allow a user to login. This module calls other login modules to initialte the login sequence.*/
User* user_login();



/*	get_login_details() obtains login details of a user, in accordance to the Data Flow Diagram.*/
void get_login_details(User *user){
	cout<<"\n\nEnter username:\n>";
	cin.clear();
	cin>>user->username;
	
	cout<<"\n\nEnter password:\n>";
	cin.clear();
	cin>>user->password;
}





/*	validate_login_details(User user) validates login details of a user obtained in get_login_details(), in accordance to the Data Flow Diagram.
	This module also prints the corresponding error messages.*/

bool validate_login_details(User* user){
	bool valid=true; 		/*this is the value returned, signalling the calling module as to whether the argument passed is valid or not.*/

	if(database.user_map.find(string(user->username)) != database.user_map.end()){
		//if the username exists:
		User temp=database.user_map[string(user->username)];
		
		//validate password:
		for(int i=0; temp.password[i]!='\0' && user->password[i]!='\0' && i<50; i++){
			if(temp.password[i]!=user->password[i]){
				cout<<"\n\tLogin ERROR: password is does not match username.";
				valid= false;
			}
		}
	}
	else {		//username does not exist
		cout<<"\n\tLogin ERROR: username does not exist.";
		valid= false;
	}


	return valid;		//return the validity status of the input arguments

}





/*	A driver function is called by external modules to allow a user to login. This module calls other login modules to initialte the login sequence.*/

User* user_login(){
	User *user =new User();
	get_login_details(user);		//obtain login details from user.

	if(validate_login_details(user)){
		(*user)=database.user_map[string(user->username)];	//pass on the user object to the calling module
		return user;		//return address of user object to calling function
	}
	else {
		cout<<"\n\tERROR: Unable to log in.";
		return NULL;
	}

}

