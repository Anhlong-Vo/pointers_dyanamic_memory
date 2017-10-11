//============================================================================
// Name        : pointers_dyanamic_memory.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

//============================================================================
// Name        : 10_Memory.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string.h>
using namespace std;

//globals
int globalInt=12;

//constants
const int MY_SIZE =10;

//forward declarations
bool static_good();
bool dynamic_memleak();
bool dynamic_good();
void pointerDereference();
void pointerPassingInFunctions();
void pointerByValue(char *myPointer);
void pointerByRef(char* &myPointer);
void pointerAndConst();
void pointerMischief();
bool danglingPointer();

int main() {
	//common things to know
	static_good();
	dynamic_good();
	danglingPointer();
	dynamic_memleak();
	pointerDereference();
	pointerPassingInFunctions();

	//less common but useful
	pointerAndConst();
	pointerMischief();

	int *i=new int[10];
	i[1]=3;
	i[5]=5;

}
//================ POINTERS dereference ===============================
void pointerDereference(){
	//some pointers
	int 	*pInt;

	//pointers to globals
	pInt		= &globalInt;

	int myInt[5] 	= {0,1,2,3,4};

	//2 ways to set pointers to an array
	pInt		= &myInt[0];	//pInt points to myInt which equals 10
	pInt		= myInt;	// "

	cout<<"\nIn pointerDereference, myInt[5] contains: ";
	//iterate over array using a pointer
	for (int i=0;i<5;i++)
	{
		cout<< *(pInt + i) <<" ";
	}
	cout<<std::endl;
}



//================ POINTERS allocations ===============================
void pointerDiffType(){
	int *pInt =0;
	double *pdouble = 0;
//	pInt = pdouble;

}
bool static_good() {
	int p[MY_SIZE];			//no worries, stack based, fine, goes out of scope
	return true;			//right after this statement
}

bool dynamic_memleak() {
	//p is a local var on the stack when this function exits it disappears
	//along with only way to free the MY_SIZE ints we just allocated
	//the new new int[MY_SIZE] allocates 10 ints on the heap p points to them
	int *p = new int[MY_SIZE];
	if (!p)
		return false;		//if cannot allocate new returns a 0

	return 0;  				//Exiting without freeing the allocated memory
							//no dangling pointer, just undeleted memory
}

bool danglingPointer() {
	int *p = new int[MY_SIZE];
	if (!p)
		return false;

	int *p2 = p;

	if (p)
	{
		delete [] p;
		p=0;
	}

	//what about p2?


	return 0;
}

bool dynamic_good() {
	//STACK BASED
	int pStack[] = {1,1,1,1,1,1,1,1,1,1};

	//set to 0, should only bother during debug builds, lets you start with a baseline
	memset(pStack, 0, (MY_SIZE) * sizeof(int));

	cout<<"\nIn dynamic_good, stack array contains: ";

	//lets take a look at the memory
	for (int j  = 0; j < MY_SIZE; ++j) {
		cout<<(*pStack+j)<<" ";
	}
	cout<<std::endl;

	//HEAP BASED
	int *pHeap = new int[MY_SIZE];
	if (!pHeap)
		return false;	//if cannot allocate new returns a 0

	//set to 0, should only bother during debug builds, lets you start with a baseline
	memset(pHeap, 0, (MY_SIZE) * sizeof(int));

	cout<<"\nIn dynamic_good, dynamic array contains: ";

	//lets take a look at the memory
	for (int j  = 0; j < MY_SIZE; ++j) {
		cout<<*(pHeap+j)<<" ";
	}
	cout<<std::endl;

	//dont forget to free it, not
	//very robust though, if exception is thrown
	//you never free this memory, better to use
	//objects to allocate and free memory (coming soon)
	//or try-catch (coming soon)
	//or on some compilers(MSVC) __try __finally (coming maybe)
	if (pHeap)
	{
		delete [] pHeap;
		pHeap=0;			//not really necessary since p bout to go out of scope, but its a good habit to get into
	}
	return true;
}

//================ POINTER Mischief ===============================
void pointerMischief(){
	//some pointers
	int 	*pInt;

	//pointer mischief that you cant do
//	pInt		= &MY_SIZE;	//cant do this (invalid conversion from constant int* to int*)
//	*pInt 		= 9;

	//pointer mischief that you CAN do but should not do
	char *pChar = 0;
	char& myChar = *pChar;	//great scott! refeferences cannot be NULL,
							//but the reference myChar is now NULL
							//results are undefined
							//programmers who do this sort of thing MUST be shunned
}
//================ POINTERS and const ===============================
//you see this sort of thing in others code
void pointerAndConst(){
	//trick mentally draw a vertical line thru pointer asterix
	//const to left		-whats pointed to is constant
	//const to right	-pointer itself is constant

	char 					*p1	= "hello";  //non const pointer
											//non const data
	const 	char 			*p2	= "hello";	//non const pointer
											//const data
	char 	* 		const 	 p3 = "hello";	//const pointer
											//non const data
	const 	char* 	const 	 p4	= "hello";	//const pointer
											//const data

	char *pn= new char[5];
	const char* const p = pn;
}
//================ POINTERS in functions ===============================
void pointerPassingInFunctions(){
	//passing a pointer
	char myString[] = "I am at an alpha low";
	char *pChar = myString;

	cout<<"\nBefore constPointer: char string is: "<<myString<<'\n';
	pointerByValue(pChar);
	cout<<"After constPointer: char string is: "<<myString<<'\n';

	cout<<"\nBefore nonconstPointer: char string is: "<<pChar<<'\n';
	pointerByRef(pChar);
	cout<<"After nonconstPointer: char string is: "<<pChar<<'\n';
}

//pointers by value
void pointerByValue(char *myPointer){
	if (myPointer)
	{
		//fine change what is pointed to
		*(myPointer+2) = 'A';

		//change pointer itself, but when return unchanged
		myPointer=myPointer+2;

		cout<<"In pointerByValue: char string is: "<<myPointer<<'\n';
	}
}
//pointersbtyRef
void pointerByRef(char *&myPointer){
	if (myPointer)
		{
			//fine change what is pointed to
			*(myPointer+2) = 'A';

			//dandy, change pointer itself
			myPointer=myPointer+2;

			cout<<"In pointerByRef: char string is: "<<myPointer<<'\n';
		}
}
