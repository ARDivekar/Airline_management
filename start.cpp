#ifndef IOSTREAM
#define IOSTREAM
	#include<iostream>
#endif


#ifndef DATABASE
	#define DATABASE
	#include "database.h"
#endif


#ifndef USER
	#define USER
	#include "user.h"
#endif


#ifndef REGISTER
	#define REGISTER
	#include "register.h"
#endif


#ifndef LOGIN
	#define LOGIN
	#include "login.h"
#endif


#ifndef CUSTOMER_H
	#define CUSTOMER_H
	#include "customer.h"
#endif


#ifndef AIRLINE_MANAGER
	#define AIRLINE_MANAGER
	#include "airline_manager.h"
#endif


#ifndef AIRPORT_CONTROLLER
	#define AIRPORT_CONTROLLER
	#include "airport_controller.h"
#endif

	
using namespace std;


int main(){
	//database.truncate_database();	//create a fresh application with no data.
	database.load_files(); 	//load all database files from disk into corresponding hash tables.

	int select=-1;
	User* user;
	while(true){
		//cout<<"\n\nEnter action:\n0. Delete all existing data\n1. Register\n2. Login\n3. Exit application\n>";
		cout<<"\n\nEnter action:\n1. Register\n2. Login\n3. Exit application\n>";
		cin.clear();
		cin>>select; 	//get user input.
		switch(select){
			/*case 0: 	//"Delete all existing data":
				database.truncate_database();
				cout<<"\n\nDatabase successfully truncated.";
				break;
			*/

			case 1: 	//"Register":
				user=user_register();
				if(user!=NULL){		//we have successfully registered.
					cout<<"\n\tLogging into account of user '"<<string(user->name)<<"'....";	//successful login
					switch(user->type){
						case AIRL_MGR:
							load_airline_manager_page(user);
							break;
						case AIRP_CON:
							load_airport_controller_page(user);
							break;
						case CUSTOMER:
							load_customer_page(user);
							break;
					}	
				}
			break;

			
			case 2: 	//"Login":
				user=user_login();
				if(user!=NULL){
					cout<<"\n\tLogging into account of user '"<<string(user->name)<<"'....";	//successful login
					switch(user->type){
						case AIRL_MGR:
							load_airline_manager_page(user);
							break;
						case AIRP_CON:
							load_airport_controller_page(user);
							break;
						case CUSTOMER:
							load_customer_page(user);
							break;
					}	
				}
				break;


			case 3:	//"Exit application"
				cout<<"\n\n\t\t\t<----------THANK YOU FOR USING OUR APPLICATION--------->\n\t\t\n\n\n";
				return 0;

			default:
				cout<<"\n\tERROR: Invalid entry. Please try again.";
		}
			
	}	
	cout<<"\n\n\n";
	return 0;
}
