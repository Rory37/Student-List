
#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <iomanip>

using namespace std;

//Student List Tracker
//10/11/17
//By Aidan Derocher
//Is able to record name, id, and gpa of students and put them into a vector
//One can add students, remove students, print out all students in the list, and quit

struct name { //struct that is for all students on list
  char fname [80];//all student info
  char lname [80];
  int id;
  float gpa;
};

void add(vector<name*>*);
void print(vector<name*>*);
void deletestruct(vector<name*>*);

int main ()
{
  cout << "This is Student List, which is currently studentless" << endl;
  vector<name*>* namel = new vector<name*>();//Creates a vector pointing to all the struct names
  bool running = true;
  while (running) {
    cout << "Please input a command. Valid comands include ADD, PRINT, DELETE, and QUIT" << endl;
    char command [80];
    cin.getline(command, 80);
    for (int i = 0; i < strlen(command); i++) {
      command[i] = toupper(command[i]);
    }
    if (strcmp(command, "ADD") == 0) {
      add(namel);
    }
    else if (strcmp(command, "PRINT") == 0) {
      print(namel);
    }
    else if (strcmp(command, "DELETE") == 0) {
      deletestruct(namel);
    }
    else if (strcmp(command, "QUIT") == 0) {
      running = false;
    }
  }
}

void add(vector<name*>*namel) { //Passes in the vector pointer
  name* newStudent = new name(); //Makes new struct of name with pointer
  namel -> push_back(newStudent); //Adds struct to vector

  //inputting first name
  cout << "Please input the first name of the student" << endl;
  char firname [80];
  cin.getline(firname, 80);
  for (int i = 0; i < strlen(firname); i++) {
    firname[i] = tolower(firname[i]); //Makes sure only first letter is capitalized
  }
  firname[0] = toupper(firname [0]);
  strcpy(newStudent -> fname, firname); //Puts the firstname int the struct
  
  //inputting last name

  cout << "Please input the last name of the student" << endl;
  char lasname [80];
  cin.getline(lasname, 80);
  for (int i = 0; i < strlen(lasname); i++) {
    lasname[i] = tolower(lasname[i]); //Makes sure only first letter is capitalized
  }
  lasname[0] = toupper(lasname [0]);
  strcpy(newStudent -> lname, lasname); //puts lastname into struct
  
  //inputting student id

  int studid; //stands for student id
  bool valid = false; //stands for valid id, or valID
  while (valid == false) {
    cout << "Please input the 6 digit student id" << endl;
    bool corchar = true; //stands for correct character
    char potin [80]; //stands for potential input
    cin.getline(potin, 80); //Puts input in char array
    for (int i = 0; i < strlen(potin); i++) { 
      if (!isdigit(potin[i])) { //Verifies all characters are numbers
	  cout << "Please do not include any non-numerical characters" << endl;
	  corchar = false;
	  break;//break for loop
	}
    }
    if (corchar == false) {
      continue; //restart while loop
    }
    studid = atoi(potin); //converts char array to in
    if (studid > 99999 && studid < 1000000) { //if int is 6 digits
      valid = true;
    }
    else {
      cout << "Please type in a 6 digit id" << endl;
    }
    
    for (vector<name*>::iterator it = namel -> begin(); it != namel -> end(); ++it) {//Checks if student id matches any other id in the vector
      if (studid == (*it) -> id) {
	valid = false;
	cout << "Please make sure the student id is unique" << endl;
      }
    }
    
  }
  newStudent -> id = studid; //copies id into struct
 
  //Inputting GPA

  double grapa; //GRAde Point Average
  bool val2 = false;
  while (val2 == false) {
    cout << "Please input the gpa of the student as whole number, decimal point, and the decimal" << endl;
    bool corchar = true;
    char potin [80];
    cin.getline(potin, 80);
    if (!isdigit(potin[0]) || (potin[1] != '.' && potin[1] != '\0')) {//Makes sure first section of input is number, followed by decimal.
      cout << "Please type in the gpa as a whole number, a decimal point, and then the decimal" << endl;
      //continue;
    }
    if (potin[1] != '\0') {
      for (int i = 2; i < strlen(potin)-2; i++) {
	if (!isdigit(potin[i])) {
	  cout << "Please type in the gpa as a whole number, a decimal point, and then the decimal" << endl;
	  corchar = false;
	  break;//exits for loop
	}
      }
    }
    if (corchar == false) {
      continue;
    }
    val2 = true;
    grapa = atof(potin);
  }
  newStudent -> gpa = grapa;
  cout << "Success" << endl;
}

void print (vector<name*>*namel) {
  for (vector<name*>::iterator it = namel -> begin() ; it != namel -> end(); ++it) {//Creates iterator to go through vector
    //Prints out all information from structs in vector, with gpa being set to print with a precision of two decimals
    cout << "First Name: " << (*it) -> fname << endl << "Last Name: " << (*it) -> lname << endl << "Student id: " << (*it) -> id << endl << "GPA: " << fixed << setprecision(2) << (*it) -> gpa << endl << endl; 
  }
}
void deletestruct (vector<name*>*namel) {
  bool trying = true;
  while (trying == true) {
    int remove = 0;//student id to remove initiallization
    bool legit = false;
    while(legit == false) {
      cout << "Please input the student id of the student you wish to remove" << endl;
      char delid [80];
      cin.getline(delid, 80);// Gets input
      bool num = true;
      for(int i = 0; i < strlen(delid); i++) {//Makes sure all characters are numbers
	if (!isdigit(delid[i])) {
	  num = false;
	}
      }
      remove = atoi(delid); // Converts to int
      if(!(remove > 99999 || !remove < 1000000)) { //makes sure the int is 6 digits
	num = false;
      }
      
      if (num == true) {
	legit = true;
      }
      else {
	cout << "Make sure the student id is 6 digits and all numbers" << endl;
      }
    }
    
    for(vector<name*>::iterator it = namel -> begin(); it != namel -> end(); ++it) {//Creates iterator for vector
      if((*it) -> id == remove) { //Searches all structs in vector for matching student id
	delete (*it); //Removes from heap
	namel -> erase(it);//removes from vector
	trying = false;
	cout << "Student is removed" << endl;
	break;
      }
    }
    if (trying == true) {
      cout << "Make sure that the inputted student id matches one that is in the system" << endl;
    }
  }
  
}
