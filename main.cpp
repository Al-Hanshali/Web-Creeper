#include <iostream>
#include "Creeper.h"
#include "Creeper.cpp"
// gives a Crawler object named `myCreeper` from default

using namespace std;

int main(int argc, const char *argv[])
{

  //Get parameters
  	myCreeper.maxLinks = stoi(argv[1]);
  	myCreeper.pagesLimit = stoi(argv[2]);
  	myCreeper.maxThreads = stoi(argv[3]);

  	myCreeper.init();
  	myCreeper.creep();
  	myCreeper.display();
	
	cout << "FINISHED." << endl;


  return 0;
}
