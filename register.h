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


/*	A driver function is called by external modules to allow a user to register. This module calls other registration modules to initialte the registration sequence.*/
User* user_register();		



/*	get_registration_details() obtains regestration details of a user, in accordance to the Data Flow Diagram.*/

User* get_registration_details(){	
	User* user=new User();
	string str_name;

	cout<<"\n\tEnter a username (only underscores, not spaces allowed)\n\t>";
	cin.clear();
	cin>>user->username;

	cout<<"\n\tEnter a password (must be six letters long and must contain a number)\n\t>";
	cin.clear();
	cin>>user->password;

	cout<<"\n\tEnter name\n\t>";
	cin.clear();
	cin.ignore(); 
	getline(cin, str_name);
	//we must now convert the string to a character array.
	int i;
	for(i=0; i<str_name.length() && i<50; i++)
		user->name[i]=str_name.at(i);
	
	cout<<"\n\tEnter age\n\t>";
	cin.clear();
	cin>>user->age;

	cout<<"\n\tEnter email (must be of the form ___@___.___)\n\t>";
	cin.clear();
	cin>>user->email;

	cout<<"\n\tEnter phone number\n\t>";
	cin.clear();
	cin>>user->phone;		

	while(user->gender!='M' && user->gender!='F'){
		cout<<"\n\tEnter gender (M or F)\n\t>";
		cin.clear();
		cin>>user->gender;
		if(user->gender!='M' && user->gender!='F')
			cout<<"\n\tERROR: Invalid gender entry";
	}
	
	return user;

}
	




/*	validate_registration_details(User* user) validates regestration details of a user obtained in get_registration_details(), in accordance to the Data Flow Diagram.
	This module also prints the corresponding error messages.*/

bool validate_registration_details(User* user){

	bool valid=true; 		/*this is the value returned, signalling the calling module as to whether the argument passed is valid or not.*/
	
	//check if username already exists:
	if(database.user_map.find(string(user->username)) != database.user_map.end()){
		cout<<"\n\tRegistration ERROR: this username is unavailable.";
		valid=false;
	}
	

	//check if the password has at least 6 characters.
	bool checked;
	string pass=string(user->password);
	if(pass.length()<6){
		cout<<"\n\tRegistration ERROR: the selected password must be at least 6 character long.";
		valid=false;
	}


	//check if the password has a number in it.
	checked=false;
	for(int i=0; user->password[i]!='\0'  && checked==false; i++)
		if(user->password[i] >= '0' && user->password[i] <= '9'){
			checked=true; //meaning there is a number in the password
			break;
		}
	if(!checked){
		cout<<"\n\tRegistration ERROR: the selected password must contain at least one number.";
		valid=false;
	}
	
	
	//check if the user is above 18 years of  age.
	if(user->age < 18){
		cout<<"\n\tRegistration ERROR: you must be at least 18 years of age to register.";
		valid=false;
	}


	//check if the email contains an '@' symbol
	checked=false;
	for(int j=0; user->email[j]!='\0'; j++){
		if(user->email[j]=='@'){
			checked=true;
		}
	}
	if(!checked){
		cout<<"\n\tRegistration ERROR: an email address must contain an @ address.";
		valid=false;
	}


	//check if the email contains a '.' symbol
	checked=false;
	for(int j=0; user->email[j]!='\0'; j++){
		if(user->email[j]=='.'){
			checked=true;
		}
	}
	if(!checked){
		cout<<"\n\tRegistration ERROR: an email address must contain an @ address.";
		valid=false;
	}

	return valid;		//return the validity status of the input arguments
}






/*	save_user_details(User* user) is a module which saves the user details into the database if they have been deemed valid. */

void save_user_details(User* user){
	database.user_map[string(user->username)]=(*user);		//save the user in the hash table.
	database.write_to_file_user();		/*Write changed user table to file. We use the database object's function to save, thus improving cohesion.*/
}




/*	A driver function is called by external modules to allow a user to register. This module calls other registration modules to initialte the registration sequence.*/

User* user_register(){
	User* user=new User();
	int select=-1;
	while(select<1 || select >3){
		cout<<"\n\n\tWhich type of user are you?\n\t1.Customer\n\t2.Airline manager\n\t3.Airport Controller\n\t>";
		cin.clear();
		cin.ignore();
		cin>>select;
		if(select<1 || select >3){
			cout<<"\n\tInvalid type of user. Please try again.\n";
			select=-1;
		}
		
	}

	user= get_registration_details();

	switch(select){
		case 1: user->type=CUSTOMER;
			break;
		case 2: user->type=AIRL_MGR;
			break;
		case 3: user->type=AIRP_CON;
			break;
		default: cout<<"\n\tERROR: invalid user type.\n";
			return NULL;
	}


	if(validate_registration_details(user)){
		save_user_details(user);
		cout<<"\n\tSuccessfully saved details for user "<<string(user->name)<<endl;
	}
	else {
		cout<<"\n\tERROR: unable to register; invalid details entered.\n";
		return NULL;
	}
	return user;

}

