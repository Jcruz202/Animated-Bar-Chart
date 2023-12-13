//
//  Project 3 - Animated Bar Chart
//  Course: CS 251, fall 2022. Tues 2pm lab
//  System: Clion and replit
//  Author: Juan Miguel Cruz
//  Net Id: Jcruz85
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <map> 
#include <vector>
#include <unistd.h>
#include "myrandom.h" // used by graders, do not remove
#include "barchart.h"
//#include <boost/range/adaptor/reversed.hpp>

using namespace std;

//
// BarChartAnimate
//
class BarChartAnimate {
 private:
    //
    // Private member variables for the abstraction.
    // This implementation uses a low-level C array, bars, to store a list of
    // BarCharts.  As a result, you must also keep track of the number of
    // elements stored (size) and the capacity of the array (capacity).
    // This IS dynamic array, so it must expand automatically, as needed.
    //

    BarChart* barcharts;  // pointer to a C-style array
    int size;
    int capacity;
    map<string, string> colorMap;
    int num;
    string title;
    string xlabel;
    string source;

 public:

    // a parameterized constructor:
    // Like the ourvector, the barcharts C-array should be constructed here
    // with a capacity of 4.
    BarChartAnimate(string title, string xlabel, string source) {

        this->barcharts = new BarChart[4];
        this->title = title;
        this->xlabel = xlabel;
        this->source = source;
        size =0;
        capacity = 4;
        num=0;
        
    }

    //
    // destructor:
    //
    // Called automatically by C++ to free the memory associated
    // by BarChartAnimate.
    //
    virtual ~BarChartAnimate() {
        delete [] barcharts;
//        cout << "barchartanimate destructor success" << endl;
    }

    // addFrame:
    // adds a new BarChart to the BarChartAnimate object from the file stream.
    // if the barcharts has run out of space, double the capacity (see
    // ourvector.h for how to double the capacity).
    // See application.cpp and handout for pre and post conditions.
    void addFrame(ifstream &file) {
        string numFrame, temp;
        getline(file, temp);
        getline(file, numFrame);
        int amount;
        if(numFrame == ""){ // to check the if the last line of the file is just an empty string
            amount = 0;
        }
        else{
            amount = stoi(numFrame);
        }

        if(capacity == size){
            int newCapacity = capacity * 2;
             BarChart *newBar = new BarChart[newCapacity];
             for(int i=0; i < size; i++){
                 newBar[i] = barcharts[i];
             }
             delete[] barcharts;
             barcharts = newBar;
             capacity = newCapacity;
        }
        BarChart bca(amount);

        for(int i=0; i < amount; i++){
            string year, name, country, value, category, readString;
            getline(file, readString);
            stringstream ss(readString);
            getline(ss, year, ',');
            getline(ss, name, ',');
            getline(ss, country, ',');
            getline(ss, value, ',');
            getline(ss, category, ',');
            //cout << "for test: " << "year: "<<  year << " " << "name: " << name << " " << "country: " << country << " " << "value: " << value << " " << "category: " << category << " " << endl;
            int val = stoi(value);
            bca.addBar(name, val, category);
            bca.setFrame(year);

             if(colorMap.find(category) == colorMap.end()){
                colorMap[category] = COLORS[num];
//                cout << "colors: " << COLORS[num] << "category: " <<  category << endl;
                 num++;
             }
             if(num == COLORS.size()){
                 num = 0;
             }

        }
        barcharts[size] = bca;
        size++;
//        cout << "frame: " << bca.getFrame() << endl;
//        bca.graph(cout, colorMap, amount);
    }

    // animate:
    // this function plays each frame stored in barcharts.  In order to see the
    // animation in the terminal, you must pause between each frame.  To do so,
    // type:  usleep(3 * microsecond);
    // Additionally, in order for each frame to print in the same spot in the
    // terminal (at the bottom), you will need to type: output << CLEARCONSOLE;
    // in between each frame.
	void animate(ostream &output, int top, int endIter) {
		unsigned int microsecond = 50000;

        for(int i=0; i < endIter; i++){
            usleep(3 * microsecond);
            output << CLEARCONSOLE;
            output << WHITE << title << endl;
            output << WHITE << source << endl;
            barcharts[i].graph(cout , colorMap, top);
            output << WHITE << xlabel << endl;
            output << WHITE << "Frame: " << barcharts[i].getFrame() << endl;
        }
	}

    //
    // Public member function.
    // Returns the size of the BarChartAnimate object.
    //
    int getSize(){
        return size;  // it returns the size
    }

    //
    // Public member function.
    // Returns BarChart element in BarChartAnimate.
    // This gives public access to BarChart stored in the BarChartAnimate.
    // If i is out of bounds, throw an out_of_range error message:
    // "BarChartAnimate: i out of bounds"
    //
    BarChart& operator[](int i){
        if (i < 0 || i >= size){
            throw out_of_range("Bars: i out of bounds");
        }
        return barcharts[i];
    }
};
