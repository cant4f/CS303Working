#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "AssignmentHandler.h"

class User_Interface
{
public:
	User_Interface(AssignmentHandler assignment_handler) : assignment_handler(assignment_handler){}
	void run_menu();
	int menu_selection();
	void handle_selection(int choice);
private:
	AssignmentHandler assignment_handler;
};





#endif
