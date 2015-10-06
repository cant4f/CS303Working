#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "Assignment.h"
#include "AssignmentHandler.h"
#include "Date.h"
#include "List.h"
#include "List_Const_Iterator.h"
#include "List_Iterator.h"
#include "Ordered_List.h"
#include "StringTokenizer.h"
using namespace std;


int start_menu();

AssignmentHandler handle_choice(const int choice, AssignmentHandler assignment_handler);

int main()
{
	/*list<int> my_list;
	list<int>::const_iterator itr1;
	my_list.push_front(5);
	list<int>::const_iterator itr = my_list.begin();
	//cout << "Front is " << my_list.front() << endl;
	//cout << "Back is " << my_list.back() << endl;
	my_list.push_back(4);
	itr++;
	//cout << "New back is " << my_list.back() << endl;
	my_list.insert(itr, 6);
	for(itr1 = my_list.begin(); itr1 != my_list.end(); itr1++)
	{
	cout << *itr1 << endl;
	}*/

	
	AssignmentHandler assignment_handler;
	string filename;
	string textline;
	string due, description, assigned, status;//to use to pass into the constructor
	int index = 0;//to use for parsing the lines of the textfile
	int choice = 0;
	ifstream fin;// ("testfile.txt");
	ofstream fout;

	/*cout << "Please enter text file name to populate lists from without the .txt extension: ";
	cin >> filename;
	fin.open(filename + ".txt");//need to add error handling around this*/

	/*while (!fin.eof())
	{
		getline(fin, textline);
		String_Tokenizer LineParser(textline, ",");
		while (LineParser.has_more_tokens())//parses the textline, should make separate function
		{
			switch (index)
			{
			case 0:
				std::istringstream(LineParser.next_token()) >> due;
				break;
			case 1:
				std::istringstream(LineParser.next_token()) >> description;
				break;
			case 2:
				std::istringstream(LineParser.next_token()) >> assigned;
				break;
			case 3:
				std::istringstream(LineParser.next_token()) >> status;
			}
			++index;
		}
		if (status == "Assigned")
			AssignedAssignments.insert(Assignment(due, description, assigned, status));
		else
			CompletedAssignments.insert(Assignment(due, description, assigned, status));
		index = 0;
	}*/

	cout << "Please enter text file name to populate lists from without the .txt extension: ";
	cin >> filename;
	filename += ".txt";
	fin.open(filename);//need to add error handling around this
	if (fin.fail())
		cout << "file failed" << endl;

	while (!fin.eof())
	{
		getline(fin, textline, '\n');
		//cout << "\n" << textline << endl;//just wanted to confirm i was reading in ok
		assignment_handler.Add_Assignment(textline);
	}

	do
	{ 
		choice = start_menu();
		assignment_handler = handle_choice(choice, assignment_handler);
	} while (choice != 8); // exits program if choice is 8
	
	

	fin.close();
	fout.close();
	system("pause");
	return 0;
}

// Function prints the start menu to the screen
// Takes integer input from user: number is 1 - 8
// Clears input and prompts user again if invalid input
// Returns the int value
int start_menu()
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
			//else if (menu_choice == 8)
				//still_in_menu = false;
		} while (menu_choice < 1 || menu_choice > 8);
	}
	return menu_choice;
}

// Function takes int value returned by start_menu() function
// Performs corresponding task based on user input
// Returns nothing
AssignmentHandler handle_choice(const int choice, AssignmentHandler assignment_handler)
{
	string textline;
	string due, description, assigned, status;
	switch (choice)//will probably put into seperate function to reduce clutter
	{
	case 1://display assignments
		cout << "\nDue Date,Description,Assign Date,Status\n";
		assignment_handler.DisplayAssignments(cout);
		cout << endl;
		break;
	case 2://add an assignment
		cout << "\nPlease enter the assignments data in one line in the following manner;\nDue date,description,assigned dates,status\nwith the dates in the format MM/DD/YYYY\n:";
		cin >> textline;
		assignment_handler.Add_Assignment(textline);
		break;
	case 3://change due date
		cout << "Please enter the assign date of the assignment you wish to change using the format MM/DD/YYYY\n:";
		cin >> assigned;
		cout << "Please enter the new due date of the assignment you are changing in the format MM/DD/YYYY\n:";
		cin >> due;
		assignment_handler.EditAssignmentDue(assigned, due);
		break;
	case 4://change description BE VERY CAREFUL!!! IT DOES NOT LIKE HAVING A STRING WITH SPACES PASSED IN!!!
		cout << "Please enter the assign date of the assignment you wish to change using the format MM/DD/YYYY\n:";
		cin >> assigned;
		cout << "Please enter the new description of the assignment you are changing\n:";//avoid using spaces for the moment
		cin >> description;//NO SPACES!!!!
		assignment_handler.EditAssignmentDescrip(assigned, description);
		break;
	case 5://complete an assignment
		cout << "Please enter the assign date of the assignmeent you wish to complete using the format MM/DD/YYYY\n:";
		cin >> assigned;
		cout << "Please enter the date the assignment was completed in the format MM/DD/YYYY\n:";
		cin >> due;//using due again instead of making a new variable
		assignment_handler.CompleteAssignment(assigned, due);
		break;
	case 6://count late assignments
		cout << to_string(assignment_handler.CountLate()) << " late assignments.\n";
		break;
	case 7://saves assignments to textfile
		//i need to be very careful doing this, because i am writing to the same file i depend on reading from
		//going to try a couple different things in a separate copy, will upload best option
		break;
	case 8://exists program
		break;
	}
	return assignment_handler;
}


