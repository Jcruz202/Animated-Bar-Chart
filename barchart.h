//
//  Project 3 - Animated Bar Chart
//  Course: CS 251, fall 2022. Tues 2pm lab
//  System: Clion and replit
//  Author: Juan Miguel Cruz
//  Net Id: Jcruz85
//
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include "myrandom.h" // used in graders, do not remove
#include "bar.h"

using namespace std;

// Constants used for bar chart animation.  You will primarily
// use these in barchartanimate.h, but you might find some useful here.
const string BOX = "\u29C8";
const string CLEARCONSOLE = "\033[2J";
const string RESET("\033[0m");


//
// NOTE: COMMENT AND UNCOMMENT AS NEEDED BASED ON YOUR TERMINAL
//
// Color codes for light mode terminals
// const string RED("\033[1;36m");
// const string PURPLE("\033[1;32m");
// const string BLUE("\033[1;33m");
// const string CYAN("\033[1;31m");
// const string GREEN("\033[1;35m");
// const string GOLD("\033[1;34m");
// const string BLACK("\033[1;37m");
// const vector<string> COLORS = {RED, PURPLE, BLUE, CYAN, GREEN, GOLD, BLACK};

// Color codes for darker mode terminals
const string CYAN("\033[1;36m");
const string GREEN("\033[1;32m");
const string GOLD("\033[1;33m");
const string RED("\033[1;31m");
const string PURPLE("\033[1;35m");
const string BLUE("\033[1;34m");
const string WHITE("\033[1;37m");
const vector<string> COLORS = {CYAN, GREEN, GOLD, RED, PURPLE, BLUE, WHITE};

//
// BarChart
//
class BarChart {
 private:
    //
    // Private member variables for the abstraction.
    // This implementation uses a low-level C array, bars, to store a list of
    // Bars.  As a result, you must also keep track of the number of elements
    // stored (size) and the capacity of the array (capacity).  This is not a
    // dynamic array, so it does not expand.
    //
    Bar* bars;  // pointer to a C-style array
    int capacity;
    int size;
    string frame;

 public:

    // default constructor:
    BarChart() {
        bars = NULL;
        capacity = 0;
        size = 0;
        frame = "";

    }

    // parameterized constructor:
    // Parameter passed in determines memory allocated for bars.
    BarChart(int n) {
      this->bars = new Bar[n];
      this->capacity = n;
      this->size = 0;
      this->frame= "";
    }
    //
    // copy constructor:
    //
    // Called automatically by C++ to create an BarChart that contains
    // a copy of an existing BarChart.  Example: this occurs when passing
    // BarChart as a parameter by value.
    //
    BarChart(const BarChart& other) {
      this->bars = new Bar[other.capacity];
      this->size = other.size;
      this->capacity = other.capacity;
      this->frame = other.frame;

      for(int i = 0; i < other.size; i++){
        this->bars[i] = other.bars[i];
      }
    }
    //
    // copy operator=
    //
    // Called when you assign one BarChart into another, i.e. this = other;
    //
    BarChart& operator=(const BarChart& other) {
      BarChart bc;
      if(bars != NULL){
          delete[] bars;
      }

      this->bars = new Bar[other.capacity];
      this->size = other.size;
      this->capacity = other.capacity;
      this->frame = other.frame;

      for(int i=0; i < other.size; i++){
        this->bars[i] = other.bars[i];
      }

        return *this;
    }

    // clear
    // frees memory and resets all private member variables to default values.
    void clear() {
        delete[] bars;  // since we new'd an array, we delete[] an array

        bars = new Bar[4];
        size = 0;
        capacity = 4;
        frame ="";

    }

    //
    // destructor:
    //
    // Called automatically by C++ to free the memory associated by the
    // BarChart.
    //
    virtual ~BarChart() {
      delete[] bars;
      // cout << "success, destructor for barChart.h" << endl;
      // if (bars != nullptr){

      // }
    }

    // setFrame
    void setFrame(string frame) {
    	  this->frame = frame;
    }

    // getFrame()
    // Returns the frame of the BarChart oboject.
    string getFrame() {
      return frame;
    }

    // addBar
    // adds a Bar to the BarChart.
    // returns true if successful
    // returns false if there is not room
    bool addBar(string name, int value, string category) {
      if(size< capacity){
        Bar b(name, value, category);
        bars [size] = b;
        size++;
        return true;
      }
      return false;
    }

    // getSize()
    // Returns the size (number of bars) of the BarChart object.
    int getSize() {
        return size;
    }

    // operator[]
    // Returns Bar element in BarChart.
    // This gives public access to Bars stored in the Barchart.
    // If i is out of bounds, throw an out_of_range error message:
    // "BarChart: i out of bounds"
    Bar& operator[](int i) {
      if (i < 0 || i >= size){
      throw out_of_range("Bars: i out of bounds");
    }
      return bars[i];
    }

    // dump
    // Used for printing the BarChart object.
    // Recommended for debugging purposes.  output is any stream (cout,
    // file stream, or string stream).
    // Format:
    // "frame: 1
    // a name 5 category1
    // b name 4 category2
    // c name 3 category3" <-newline here
    void dump(ostream &output) {
      output << "Frame: " << getFrame() << endl;
      sort(bars, bars+size, greater<Bar>());
      for(int i=0; i < size; i++){
        output << "Name: " << bars->getName() << " " << "Value: " << bars->getValue() << " " << "Category: " << bars->getCategory() << endl;
      }
    }

    // graph
    // Used for printing out the bar.
    // output is any stream (cout, file stream, string stream)
    // colorMap maps category -> color
    // top is number of bars you'd like plotted on each frame (top 10? top 12?)
    void graph(ostream &output, map<string, string> &colorMap, int top) {
        int lenMax = 60;  // this is number of BOXs that should be printed
                          // for the top bar (max value)
      string barstr = "";
      sort(bars, bars+size, greater<Bar>());

      for(int i=0; i<top; i++) {
          int barLen = (((bars[i].getValue() * 1.0) / (bars[0].getValue() * 1.0)) * lenMax);
//          output << "num of boxes: " << barLen << " //for testing only" << endl;
          for (int i = 0; i < barLen; i++) {
              barstr += BOX;
          }
          output << colorMap.at(bars[i].getCategory()) << barstr << " " << bars[i].getName() << " "
                 << bars[i].getValue() << endl;
          barstr = "";
      }
    }
};

