#include <iostream>
#include <string>
#include <fstream>
//#include <typeinfo>
#include "Assignment.h"
#include "Date.h"
#include "StringTokenizer.h""
#include "assignmentHandler.h"
#include "list.h"

using namespace std;

//will be adding more error detection/correction to the code - CN

bool validEntry(int entry);
void DisplayMenu();
int getResponse(istream& read);

//all of this was me just trying to correctly parse an example of a line of data and make assignments from it
int main()
{
	AssignmentHandler assignment_handler;//this class will handle the assignments, main just passes it the data

	string filename;
	string textline="";
	string due,description,assigned,status;//to use to pass into the constructor
	int index=0;//to use for parsing the lines of the textfile
	bool still_in_menu = true;
	int menu_choice=0;

	ifstream fin;
	ofstream fout;

	cout<<"Please enter text file name to populate lists from without the .txt extension: ";
	cin>>filename;
	filename += ".txt";
	fin.open(filename);//need to add error handling around this
	if(fin.fail())
		cout<<"file failed"<<endl;
	while(!fin.eof())
	{
		getline(fin,textline,'\n');
		cout<<"\n"<<textline<<endl;//just wanted to confirm i was reading in ok
		assignment_handler.Add_Assignment(textline);
	}

	//menu block

	while (still_in_menu)
	{
		DisplayMenu();//function that just prints to screen, made to reduce clutter
		cin>>menu_choice;//decided to ignore checking for valid response so i could test things-CN
		//menu_choice = getResponse(cin);
		//cout<<endl;
		switch (menu_choice)//will probably put into seperate function to reduce clutter
		{
		case 1://display assignments
			cout<<"\nDue Date,Description,Assign Date,Status\n";
			assignment_handler.DisplayAssignments(cout);
			break;
		case 2://add an assignment
			cout<<"\nPlease enter the assignments data in one line in the following manner;\nDue date,description,assigned dates,status\nwith the dates in the format MM/DD/YYYY\n:";
			cin>>textline;
			assignment_handler.Add_Assignment(textline);
			break;
		case 3://change due date
			cout<<"Please enter the assign date of the assignment you wish to change using the format MM/DD/YYYY\n:";
			cin>>assigned;
			cout<<"Please enter the new due date of the assignment you are changing in the format MM/DD/YYYY\n:";
			cin>>due;
			assignment_handler.EditAssignmentDue(assigned,due);			
			break;
		case 4://change description
			cout<<"Please enter the assign date of the assignment you wish to change using the format MM/DD/YYYY\n:";
			cin>>assigned;
			cout<<"Please enter the new description of the assignment you are changing\n:";
			cin>>description;
			assignment_handler.EditAssignmentDescrip(assigned,description);
			break;
		case 5://complete an assignment
			cout<<"Please enter the assign date of the assignmeent you wish to complete using the format MM/DD/YYYY\n:";
			cin>>assigned;
			cout<<"Please enter the date the assignment was completed in the format MM/DD/YYYY\n:";
			cin>>due;//using due again instead of making a new variable
			assignment_handler.CompleteAssignment(assigned,due);
			break;
		case 6://count late assignments
			cout<<to_string(assignment_handler.CountLate())<<" late assignments.\n";
			break;
		case 7://saves assignments to textfile
			//i need to be very careful doing this, because i am writing to the same file i depend on reading from
			//going to try a couple different things in a separate copy, will upload best option
			break;
		case 8://exists program
			still_in_menu = false;
			break;
		}
	}
	fin.close();//always close your files
	system("pause");
	return 0;
}

//prints out the menu, made to reduce clutter
void DisplayMenu()
{
	cout<<"Would you like to:"<<endl;
	cout<<"1. Display the assignments"<<endl;
	cout<<"2. Add an assignment"<<endl;
	cout<<"3. Edit an assignment's due date"<<endl;
	cout<<"4. Edit the description of an assignment"<<endl;
	cout<<"5. Complete an assignment"<<endl;
	cout<<"6. See the number of late assignments"<<endl;
	cout<<"7. Save the assignments to a text file"<<endl;
	cout<<"8. Exit"<<endl<<endl;
	cout<<"Type a number (1-8) for the corresponding menu choice"<<endl<<":";
}

//was attempting to solve the menu problem
int getResponse(istream& read)
{
	int choice;
	cout<<"\nPlease enter a valid number (1-8)\n:";
	read>>choice;
	if(validEntry(choice))
		return choice;
	else
	{
		return getResponse(read);
	}
}

//was attempting to solve the menu problem
bool validEntry(int entry)
{
	if(entry>=1 && entry<=8)
		return true;
	else
		return false;
}
