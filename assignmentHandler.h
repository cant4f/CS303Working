#ifndef ASSIGNMENTHANDLER_H
#define ASSIGNMENTHANDLER_H

#include <string>
#include "Assignment.h"
#include "List.h"
#include "List_Iterator.h"
#include "List_Const_Iterator.h"


class AssignmentHandler
{
public:
	void DisplayAssignments(ostream& cout);//displays assignments to ostream of choice
	int CountLate();//counts late assignments
	void EditAssignmentDescrip(string uniqueDate, string newDescrip);//way number 2, puts it on the main to prompt for new descrip
	void EditAssignmentDue(string uniqueDate, string newDue);//allows for the editing of an assignments due date
	void SaveToFile(ostream& out);//just need to use DisplayAssignments to do this, just pass in fout(the file ofstream) you are writing too
	void CompleteAssignment(string uniqueDate, string completeDate);//completes an assignment and moves it to the completed list
	void Add_To_Assignments(Assignment assignment);//adds assignment to the assigned list
	void Add_To_Completes(Assignment assignment);//adds assignment to the completed list
	void Add_Assignment(const string& dataline);//adds assignment to the appropriate list
	AssignmentHandler& operator =(const AssignmentHandler& other);
private:
	List<Assignment> Assigned_Assignments;//to hold assigned assignments
	List<Assignment> Completed_Assignments;//to hold completed and late assignments
	List<Assignment>::iterator findAssignment(string uniqueDate);//finds an assignment by string, not usable by main
};
#endif;
