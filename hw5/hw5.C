//-------------------------------------------------------------------
// File     :hw4.C
// Author   :Michael Benson
// Course   :CS1129
// Date     :April 5, 2006
//
//-------------------------------------------------------------------

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cctype>
#include <cstring>

using namespace std;

void openFile(ifstream& inStream);
int countInts(ifstream& inStream);
void loadData(int size, int* list, ifstream& inStream);
void quickSort(int* list, int left, int right);
int partition (int* list, int left, int right);
void menuControl(int* list, int size);
void displayList(int* list, int size);
void search(int* list, int first, int last, int key, bool& found, 
		int& location);

const char INPUT[] = "input.txt";

int main()
{

	int size = 0;
	int* list;
	ifstream inStream;
	size = countInts(inStream);
	list = new int[size];
	
	loadData(size, list, inStream);
	quickSort(list, 0, size-1);
	menuControl(list, size);

}

//-------------------------------------------------------------------
//	openFle(ifstream&)
//
// Preconditions	:Needs a reference to an ifstream
//
// Postconditions	:Loads input.txt into the ifstream
//-------------------------------------------------------------------

void openFile(ifstream& inStream)
{
	inStream.open(INPUT);

	if (inStream.fail())
		cout << "There was an error opening the input.txt file\n";
}	

//-------------------------------------------------------------------
//	countInts(ifstream&)
//
// Preconditions	:Needs a reference to an ifstream object
//
// Postconditions	:Calls openFile(ifstream&) and reads in the
// 					 number of int's in the file
//-------------------------------------------------------------------

int countInts(ifstream& inStream)
{
	int test = 0;
	int count = 0;
	
	openFile(inStream);
	
	while (inStream.eof() == false)
	{
		inStream >> test;
		
		if (inStream.eof() == false)
			count++;
	}

	inStream.close();
	return count;
}

//-------------------------------------------------------------------
//	loadData(int, int*, ifstream&)
//
// Preconditions	:Needs the size the list, a int*, and a ifstream
// 					 reference
//
// Postconditions	:Calls openFile(ifstream) and loads the data in
// 					 the file into the array pointed to by list*
//-------------------------------------------------------------------

void loadData(int size, int* list, ifstream& inStream)
{
	int temp = 0;

	openFile(inStream);

	for (int i = 0; i < size; i++)
	{
		inStream >> temp;
		list[i] = temp;
	}

	inStream.close();
}

//-------------------------------------------------------------------
//	quickSort(int*, int, int)
//
// Preconditions	:Needs a int* to an array, a left bound and right
// 					 bound for the array
//
// Postconditions	:Calls partition(int*, int, int) and sorts the
// 					 array pointed to by int* in acending order
//-------------------------------------------------------------------

void quickSort(int* list, int left, int right)
{
	// Check if the indexes are not in order
	if (left < right)
	{
		int split = partition(list, left, right);
		quickSort(list, left, split);
		quickSort(list, split+1, right);
	}
}

//-------------------------------------------------------------------
//	partition(int*, int, int)
//
// Preconditions	:Needs an int* to an array, a left bound, and 
// 					 right bound for the array
//
// Postconditions	:Scans the array for the right most value greater
// 					 than list[left] and the left most value smaller 
// 					 than list[left]. If the left index is smaller
// 					 than the right index it swaps the values and
// 					 continues.  Otherwise it returns the location
// 					 of the right most value.
//-------------------------------------------------------------------

int partition (int* list, int left, int right)
{
	int partValue = list[left];
	int lmargin = left-1;
	int rmargin = right+1;

	while(true) 
	{
		// Move the right margin untill its less than the
		// partition value
		do 
		{
			rmargin--;
		} while (list[rmargin] > partValue);

		// Move the left margin untill its greater than the 
		// partition value
		do
		{
			lmargin++;
		} while (list[lmargin] < partValue);

		// If the left margin is less than (to the left of)
		// the right margin the values of the two location 
		// need to be swaped
		if (lmargin < rmargin)
		{
			int temp = list[rmargin];
			list[rmargin] = list[lmargin];
			list[lmargin] = temp;
		}

		// If the left margin is greater than (to the right of)
		// the right margin (that is they are in the correct order), 
		// break the loop and return the right margin location
		else
			return rmargin;
	}
}

//-------------------------------------------------------------------
//	menuControl(int*, int)
//
// Preconditions	:Needs an int* to an array and its size
//
// Postconditions	:Prompts for a value and passes it to the search
// 					 function.  It then returns the results and asks
// 					 the user if they would like to search again
//-------------------------------------------------------------------

void menuControl(int* list, int size)
{
	int test;
	bool found = false;
	int location = -1;
	
	displayList(list, size);

	// Get the number to search for
	cout << "What value would you like to search for?" << endl;
	cout << ": ";

	while ( isspace(cin.peek()) || ! isdigit(cin.peek()) )	
		cin.ignore(1);
	
	cin >> test;

	if (cin.peek() != '\n')
		return menuControl(list, size);

	// Call the binary search
	search(list, 0, size-1, test, found, location);

	// Report findings back to user
	cout << endl;
	if (found == true)
		cout << "Number found at index " << location << endl;
	else
		cout << "Number not found in list" << endl;
	
	// Ask user to continue searching
	cout << endl;
	cout << "Serach for another number (y/[n])? ";

	while ( isspace(cin.peek()) )	
		cin.ignore(1);

	if (cin.peek() == 'y' || cin.peek() == 'Y')
	{
		while ( cin.peek() != '\n' )
			cin.ignore(1);
		return menuControl(list, size);
	}
}

//-------------------------------------------------------------------
//	displayList(int*, int)
//
// Preconditions	:Needs an int* to an array and its size
//
// Postcionditions	:Prints out the array's values at each index
//-------------------------------------------------------------------

void displayList(int* list, int size)
{
	// Print headers
	cout.setf(ios::left);
	cout.width(7);
	cout << "INDEX";
	cout.width(7);
	cout << "VALUE";
	cout << endl;
	
	// Print List
	for (int i = 0; i < size; i++)
	{
		cout.width(7);
	   	cout << i;
		cout.width(7);
		cout << list[i];
		cout << endl;
	}
	
	cout.unsetf(ios::left);
}

//-------------------------------------------------------------------
//	search(int*, int, int, int, bool&, int&)
//
// Preconditions	:Needs an int* to an array, the location of the
// 					 first location and last location to concider, 
// 					 the number to look for, and a reference to a
// 					 bool found and an int location in the calling
// 					 function
//
// Postconditions	:Modifies found and location to match the results
// 					 of the search
//-------------------------------------------------------------------

void search(int* list, int first, int last, int key, bool& found, 
		int& location)
{
	int mid;
	
	// Check for no remainig posabilities
	if (first > last)
	{
		found = false;
	}

	// If there are still locations to search then
	else
	{
		mid = (first + last)/2;

		// Check if the number has been found
		if (key == list[mid])
		{
			found = true;
			location = mid;
		}

		// If the number is smaller than the midpoint, search the 
		// left half of the list
		else if (key < list[mid])
			search(list, first, mid-1, key, found, location);

		// If the number is larger than the midpoint, search the
		// right half of the list
		else if (key >  list[mid])
			search (list, mid+1, last, key, found, location);
	}
}
