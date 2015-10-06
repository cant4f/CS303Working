#include <string>
#include "AssignmentHandler.h"
#include "Date.h"
#include "Assignment.h"
#include "List.h"
#include "List_Const_Iterator.h"
#include "List_Iterator.h"

//will be adding more error detection/correction to the code - CN

//adds an assignment to the appropriate list
void AssignmentHandler::Add_Assignment(const string& dataline)
{
	Assignment temp(dataline);
	if (temp.getStringStatus() == "Assigned")
		Add_To_Assignments(temp);
	else
		Add_To_Completes(temp);
}

//prints the assignments from both lists to the designated ostream
void AssignmentHandler::DisplayAssignments(ostream& cout)
{
	cout << endl << "Assigned Assignments:" << endl;
	List<Assignment>::iterator itr = Assigned_Assignments.begin();
	while (itr != Assigned_Assignments.end())
	{
		cout << itr->GetdueDate() << "," << itr->getDescription() << "," << itr->GetAssignDate() << "," << itr->getStringStatus() << endl;
		++itr;
	}
	cout << endl << "Completed Assignments:" << endl;
	itr = Completed_Assignments.begin();
	while (itr != Completed_Assignments.end())
	{
		cout << itr->GetdueDate() << "," << itr->getDescription() << "," << itr->GetAssignDate() << "," << itr->getStringStatus() << endl;
		++itr;
	}
}

void AssignmentHandler::SaveToFile(ostream& cout)
{
	List<Assignment>::iterator itr = Assigned_Assignments.begin();
	while (itr != Assigned_Assignments.end())
	{
		cout << itr->GetdueDate() << "," << itr->getDescription() << "," << itr->GetAssignDate() << "," << itr->getStringStatus() << endl;
		++itr;
	}
	itr = Completed_Assignments.begin();
	while (itr != Completed_Assignments.end())
	{
		cout << itr->GetdueDate() << "," << itr->getDescription() << "," << itr->GetAssignDate() << "," << itr->getStringStatus() << endl;
		++itr;
	}
}

//counts the number of late assignments
int AssignmentHandler::CountLate()
{
	int count = 0;
	List<Assignment>::iterator itr = Completed_Assignments.begin();
	while (itr != Completed_Assignments.end())
	{
		if (itr->getStatus() == AssignStatus::Late)
			++count;
		++itr;//forgot to incriment the iterator, my bad
	}
	return count;
}

//finds an assignment, marks it complete or late, adds it to the completed list and removes it from the assigned list
void AssignmentHandler::CompleteAssignment(string uniqueDate, string completeDate)
{
	List<Assignment>::iterator litr = findAssignment(uniqueDate);
	litr->completeAssignment(Date(completeDate));
	Assignment temp(*litr);
	List<Assignment>::iterator citr = Completed_Assignments.begin();
	while (citr != Completed_Assignments.end() && *citr < temp)
	{
		++citr;
	}
	Completed_Assignments.insert(citr, temp);
	Assigned_Assignments.remove(temp);
}

//finds an assignment and edits its description
void AssignmentHandler::EditAssignmentDescrip(string uniqueDate, string newDescrip)
{
	List<Assignment>::iterator itr = findAssignment(uniqueDate);
	itr->changeDescription(newDescrip);

}

//finds an asignment and edits its due date
void AssignmentHandler::EditAssignmentDue(string uniqueDate, string newDue)
{
	List<Assignment>::iterator itr = findAssignment(uniqueDate);
	itr->changeDueDate(newDue);
}

//puts an assignment into the assigned list IN ORDERED FASHION
void AssignmentHandler::Add_To_Assignments(Assignment assignment)
{
	List<Assignment>::iterator itr = Assigned_Assignments.begin();
	while (itr != Assigned_Assignments.end() && *itr < assignment)
	{
		++itr;
	}
	Assigned_Assignments.insert(itr, assignment);
}

//puts an assignment into the completed list IN ORDERED FASHION
void AssignmentHandler::Add_To_Completes(Assignment assignment)
{
	List<Assignment>::iterator itr = Completed_Assignments.begin();
	while (itr != Completed_Assignments.end() && *itr < assignment)
	{
		++itr;
	}
	Completed_Assignments.insert(itr, assignment);
}

//finds an assignment since the find function of list wont find an assignment based on a string
List<Assignment>::iterator AssignmentHandler::findAssignment(string uniqueDate)
{
	List<Assignment>::iterator itr = Assigned_Assignments.begin();
	while (itr != Assigned_Assignments.end())
	{
		if (itr->GetAssignDate() == uniqueDate)
			return itr;
		++itr;
	}
	itr = Completed_Assignments.begin();
	while (itr != Completed_Assignments.end())
	{
		if (itr->GetAssignDate() == uniqueDate)
			return itr;
		++itr;
	}
}
AssignmentHandler& AssignmentHandler::operator =(const AssignmentHandler& other)
{
	Assigned_Assignments = other.Assigned_Assignments;
	Completed_Assignments = other.Completed_Assignments;
	return *this;
}
