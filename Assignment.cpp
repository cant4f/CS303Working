//Christian Nissen
//cant4f@mail.umkc.edu
//uses Date.h and StringTokenizer.h classes provided by instructor
#include <string>
#include "Assignment.h"
#include "Date.h"
//#include "AssignStatus.h" //took out because i think i found a better way to do the enum

using namespace std;

//will be adding more error detection/correction to the code - CN

//blank constructor, likely won't be used
Assignment::Assignment()
{
	Description = "";
	AssignmentStatus = AssignStatus::Assigned;
	//provide a default date for due date and assigndate
}

//allows user to 
Assignment::Assignment(string due, string descrip, string assigned, string status)
{
	Description = descrip;
	makeStatus(status);//look into doing this having had a string passed in
	//possible error handling?
	try
	{
		DueDate = Date(due, US);//need to 
	}
	catch(const exception&){
		throw std::exception(" Due Date was not valid");
	}
	try
	{
		AssignDate = Date(assigned,US);
	}
	catch(const exception&)
	{
		throw std::exception(" Assigned Date was not valid");
	}
	if(!DatesValid())
		throw std::exception("Due date must be after Assign date");
}

Assignment::Assignment(string dataline)
{
	*this = parseAssignment(dataline);
}

//copy constructor
Assignment::Assignment(const Assignment& original)
{
	Description = original.Description;
	AssignDate = original.AssignDate; //uses operator = as overloaded in Date class
	DueDate = original.DueDate; //uses operator = as overloaded in Date class
	AssignmentStatus = original.AssignmentStatus;
}

//parses the data from a single line
Assignment Assignment::parseAssignment(const string& dataLine)
{
	String_Tokenizer LineParser(dataLine,",");
	int index=0;
	string due,description,assigned,status;

	while(LineParser.has_more_tokens())
	{
		switch(index)
		{
		case 0:
			std::istringstream(LineParser.next_token())>>due;
			break;
		case 1:
			std::istringstream(LineParser.next_token())>>description;//doesn't put the full string if it has spaces, working on fixing
			break;
		case 2:
			std::istringstream(LineParser.next_token())>>assigned;
			break;
		case 3:
			std::istringstream(LineParser.next_token())>>status;
			break;
		}
		++index;
	}
	return Assignment(due,description,assigned,status);
}

//returns a const string of the value for Description
const string Assignment::getDescription()
{
	return Description;
}

//returns a const string of the value for AssignDate
const string Assignment::GetAssignDate()
{
	return AssignDate.toString();//make sure this works to return date as a string
}

//returns a const string of the value for DueDate
const string Assignment::GetdueDate()
{
	return DueDate.toString();//make sure this will return a string
}

//returns the value of AssignmentStatus
AssignStatus Assignment::getStatus()
{
	return AssignmentStatus;// does not return a string, need to decide what to do about it
}

//returns string value of AssignmentStatus
const string Assignment::getStringStatus()
{
	switch(AssignmentStatus)
	{
	default:
		return "Status Error"; // need to think of a dbetter default
	case AssignStatus::Assigned:
		return "Assigned";
	case AssignStatus::Complete:
		return "Complete";
	case AssignStatus::Late:
		return "Late";
	}

}
//changes AssignmentStatus to Late or Complete based on passed in Date
void Assignment::completeAssignment(Date completeDate)
{
	if(completeDate > AssignDate)
	{
		//will add date validation for complete date here
		if(completeDate > DueDate)//checks  if the completion date was past the due date
		{
			AssignmentStatus = AssignStatus::Late;//changes AssignmentStatus to late
		}
		else
		{
			AssignmentStatus = AssignStatus::Complete;//changes assignment status to complete
		}
	}
	else
		throw std::exception("Invalid Complete Date");
}

//changes value of Description to that of the passed in string
void Assignment::changeDescription(string newDescrip)
{
	Description = newDescrip;
}

//changes the due date to the date value of the passed in string
void Assignment::changeDueDate(string newDueDate)
{
	//add try catch block around this statement
	DueDate = Date(newDueDate, US);//uses the built in parsing and date validation of the date class
}

//converts a string to a status
void Assignment::makeStatus(const string& stringStatus)
{
	//couldn't make switch work so made ugly if statements
	if(stringStatus == "Assigned")
		AssignmentStatus = AssignStatus::Assigned;
	else if(stringStatus == "Complete")
		AssignmentStatus = AssignStatus::Complete;
	else if(stringStatus == "Late")
		AssignmentStatus = AssignStatus::Late;
	else
		throw std::exception("Invalid Status");
}

//defines < operator for use in Assignment class to make ordering assignments easier
bool Assignment::operator <(const Assignment& other) const
{
	return DueDate < other.DueDate;//uses the built in < operator in Date class to compare assignments for use in ordering them
}

//for use in making sure the Assignment is unique
bool Assignment::operator ==(const Assignment& other) const
{
	return AssignDate == other.AssignDate;//uses operator == as overloaded in Date class
}

//private function to check if due date and assigndate are within valid parameters
bool Assignment::DatesValid()
{
	if(DueDate <= AssignDate)//uses the operator <= as overloaded in Date class
		return false;
	else
		return true;
}

