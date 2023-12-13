//
//  Project 3 - Animated Bar Chart
//  Course: CS 251, fall 2022. Tues 2pm lab
//  System: Clion and replit
//  Author: Juan Miguel Cruz
//  Net Id: Jcruz85
//
#include <iostream>
#include <string>
#include "myrandom.h" // used in graders, do not remove
using namespace std;

//
// Bar
//
class Bar {
 private:
    // Private member variables for a Bar object
    // TO DO:  Define private member variables for this class
    // NOTE: You should not be allocating memory on the heap for this class.
  string name;
  int value;
  string category;


 public:

    // default constructor:
    Bar() {
        name = "";
        value = 0;
        category = "";
        
    }

    //
    // a second constructor:
    //
    // Parameter passed in constructor Bar object.
    //
    Bar(string name, int value, string category) {

      this->name = name;
      this->value = value;
      this->category = category;
        
    }

    // destructor:
    virtual ~Bar() {
//       delete[] Bar;
      // cout << "success, destructor for bar.h" << endl;
      
        
    }

    // getName:
	string getName() const{ // to access the name
        return name;
	}

    // getValue:
	int getValue() const{ // to access the value
        return value;
	}

    // getCategory:
	string getCategory() const{ // to access the category
        return category;
	}

	// operators
    // TO DO:  Write these operators.  This allows you to compare two Bar
    // objects.  Comparison should be based on the Bar's value.  For example:
	bool operator<(const Bar &other) const { // these operators are used to compare each values of two bar objects
        return value < other.getValue();
	}

	bool operator<=(const Bar &other) const {
        return !(value > other.getValue());
	}

	bool operator>(const Bar &other) const {
        return value > other.getValue();
	}

	bool operator>=(const Bar &other) const {
        return !(value < other.getValue());
	}
};

