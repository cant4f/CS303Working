#include <iostream>
#include <fstream>
#include <string>
#include "AssignmentHandler.h"
#include "User_Interface.h"



void User_Interface::run_menu()
{
	int choice = 0;
	do
	{
		choice = menu_selection();
		handle_selection(choice);
	} while (choice != 8);
}

int User_Interface::menu_selection()
{
	int menu_choice;
	bool still_in_menu = true;

	while (still_in_menu)
	{
		cout << "What would you like to do?" << endl;
		cout << "1. Display the assignments" << endl;
		cout << "2. Add an assignment" << endl;
		cout << "3. Edit an assignment's due date" << endl;
		cout << "4. Edit the description of an assignment" << endl;
		cout << "5. Complete an assignment" << endl;
		cout << "6. See the number of late assignments" << endl;
		cout << "7. Save the assignments to a text file" << endl;
		cout << "8. Exit" << endl << endl;

		do
		{
			cout << "Enter a number, 1 through 8" << endl;
			cin >> menu_choice;
			cout << endl;

			if (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); //got this code from stackoverflow.com/questions/16934183/integer-validation-for-input
			}
			else if (menu_choice > 0 && menu_choice < 9)
				still_in_menu = false;
		} while (menu_choice < 1 || menu_choice > 8);
	}
	return menu_choice;
}

void User_Interface::handle_selection(int choice)
{
	string textline;
	string due, description, assigned, status;
	switch (choice)
	{
	case 1: //display assignments
		cout << "\nDue Date,Description,Assign Date,Status\n";
		assignment_handler.DisplayAssignments(cout);
		cout << endl;
		break;
	case 2: //add an assignment
		cout << "\nPlease enter the assignments data in one line in the following manner;\nDue date,description,assigned dates,status\nwith the dates in the format MM/DD/YYYY\n:";
		cin >> textline;
		assignment_handler.Add_Assignment(textline);
		break;
	case 3: //change due date
		cout << "Please enter the assign date of the assignment you wish to change using the format MM/DD/YYYY\n:";
		cin >> assigned;
		cout << "Please enter the new due date of the assignment you are changing in the format MM/DD/YYYY\n:";
		cin >> due;
		assignment_handler.EditAssignmentDue(assigned, due);
		break;
	case 4: //change description BE VERY CAREFUL!!! IT DOES NOT LIKE HAVING A STRING WITH SPACES PASSED IN!!!
		cout << "Please enter the assign date of the assignment you wish to change using the format MM/DD/YYYY\n:";
		cin >> assigned;
		cout << "Please enter the new description of the assignment you are changing\n:";//avoid using spaces for the moment
		cin >> description;//NO SPACES!!!!
		assignment_handler.EditAssignmentDescrip(assigned, description);
		break;
	case 5: //complete an assignment
		cout << "Please enter the assign date of the assignmeent you wish to complete using the format MM/DD/YYYY\n:";
		cin >> assigned;
		cout << "Please enter the date the assignment was completed in the format MM/DD/YYYY\n:";
		cin >> due; //using due again instead of making a new variable
		assignment_handler.CompleteAssignment(assigned, due);
		break;
	case 6: //count late assignments
		cout << to_string(assignment_handler.CountLate()) << " late assignments.\n";
		break;
	case 7: //overwrites text file that data was read in from
		assignment_handler.SaveToFile();
		break;
	case 8: //exits program
		break;
	}
}
