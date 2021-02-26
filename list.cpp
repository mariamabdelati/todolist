#include "list.h"

List::List()
{
	linetext = "";
	isdone = false;
}

List::List(string listline)
{
	int notdone_start = listline.find("not done"); 
	/*
	if found, the index for when the string starts
	if not found, the index stored is -1
	*/
	int done_start = listline.find("done");
	string strtext;

	if (notdone_start > -1 && done_start == -1) // item has false
	{
		//this stores the line substring without the word done (subtract one to end right before the index of done)
		strtext = listline.substr(0, notdone_start - 1); 
		isdone = false;
	} else if (done_start > -1 && notdone_start == -1) {
		strtext = listline.substr(0, done_start - 1);
		isdone = true;
	} else if (notdone_start == -1 && done_start == -1) { // identifies that this is a user input
		strtext = listline;
		isdone = false;
	}
	linetext = strtext;
}

//this function will return the line text
//string List::text()
//{
//	return linetext;
//}

//this function marks off a task
//void List::done()
//{
//	isdone = true;
//}

//this function identifies if a task is done
//bool List::is_done()
//{
//	return isdone;
//}