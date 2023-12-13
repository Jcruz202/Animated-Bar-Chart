#include <iostream>
#include "barchartanimate.h"
using namespace std;

bool testBarChartDefaultConstructor() {
	BarChart bc;
  cout <<"Size: " <<bc.getSize()<<endl;
  cout<<"Frame: "<<bc.getFrame()<<endl;
    if (bc.getSize() != 0) {
    	cout << "test BarChart: DefaultConstructor: getValue failed" << endl;
    	return false;
    } 
    else if (bc.getFrame() != "") {
    	cout << "test BarChart: DefaultConstructor: getCategory failed" << endl;
    	return false;
    }
    cout << "test BarChart: DefaultConstructor: all passed!" << endl;
    return true;
}
// bool testBarChartParamConstructor() {
// 	BarChart bc(10);
//     if (bc.capacity != 10) {
//     	cout << "testBarChartParamConstructor: getName failed" << endl;
//     	return false;
//     }
//     else{
//       cout << "testBarChartParamConstructor: all passed!" << endl;
//       return true;
//     }
    
// }
//------------------------------------------------------------------------------

bool testBarDefaultConstructor() {
	Bar b;
  cout << "Value: "<< b.getValue() << endl;
  cout <<"Category: " <<b.getCategory()<<endl;
  cout<<"Name: "<<b.getName()<<endl;
  // BarChart bc;
    if (b.getName() != "") {
    	cout << "test Bar: DefaultConstructor: getName failed" << endl;
    	return false;
    } else if (b.getValue() != 0) {
    	cout << "test Bar: DefaultConstructor: getValue failed" << endl;
    	return false;
    } else if (b.getCategory() != "") {
    	cout << "test Bar: DefaultConstructor: getCategory failed" << endl;
    	return false;
    }
    cout << "test Bar: DefaultConstructor: all passed!" << endl;
    return true;
}


bool testBarParamConstructor() {
	Bar b("Chicago", 9234324, "US");
    if (b.getName() != "Chicago") {
    	cout << "test Bar: ParamConstructor: getName failed" << endl;
    	return false;
    } else if (b.getValue() != 9234324) {
    	cout << "test Bar: ParamConstructor: getValue failed" << endl;
    	return false;
    } else if (b.getCategory() != "US") {
    	cout << "test Bar: ParamConstructor: getCategory failed" << endl;
    	return false;
    }
    cout << "test Bar: ParamConstructor: all passed!" << endl;
    return true;
}

bool testGraph(){
  BarChart bc(10);
    bc.addBar("Chicago", 1020, "US");
    bc.addBar("NYC", 1300, "US");
    bc.addBar("Paris", 1200, "France");
    bc.addBar("Beijing",1400, "China");

    string red("\033[1;36m");
    string blue("\033[1;33m");
    string GREEN("\033[1;32m");
    map<string, string> colorMap;
    colorMap["US"] = red;
    colorMap["France"] = blue;
    colorMap["China"] = GREEN;
    bc.graph(cout, colorMap, 4);
  
  return true;
}

bool barChartCopyConst(){
  BarChart bc1;
  BarChart bc2(10);
    bc2.addBar("Chicago", 1020, "US");
    bc2.addBar("NYC", 1300, "US");
  bc1=bc2;

//    cout << bc1.getSize() << endl;
//    cout << bc2.getSize() << endl;
   if(bc1.getSize() == bc2.getSize()){
     cout << "barchart copy constructor success" << endl;
     return true;
   }

   else if(bc1.getFrame() == bc2.getFrame()){
        cout << "barchart opy constructor success" << endl;
        return true;
    }
   else{
       cout << "barchart copy constructor failed" << endl;
       return false;
   }

}

bool addFrame(){
//    bca.addFrame(inFile);
    string filename = "cities.txt";
    ifstream inFile(filename);
    string title;
    getline(inFile, title);
    string xlabel;
    getline(inFile, xlabel);
    string source;
    getline(inFile, source);

    BarChartAnimate bca(title, xlabel, source);

    while (!inFile.eof()) {
        bca.addFrame(inFile);
//        break;
    }
    return true;

}

int main() {
    testBarDefaultConstructor();
    testBarParamConstructor();
    testBarChartDefaultConstructor();
    barChartCopyConst();
    testGraph();
    addFrame();

    return 0;
}