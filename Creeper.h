#ifndef Creeper_H
#define Creeper_H

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <map>
#include <set>
#include <chrono>
#include <thread>
#include <condition_variable>

#include <pthread.h>
#include <sys/stat.h>
#include <unistd.h>

#include "downloaders.h"
#include "getLinks.h"
#include "getDomain.h"

#include "int_ts.cpp"
#include "map_ts.cpp"
#include "queue_ts.cpp"

using namespace std;

#define RED "\033[31m"	 	/* Red */
#define CYAN "\033[36m"	/* Cyan */
#define GREEN "\033[32m" 	/* Green */
#define BLUE "\033[34m"	/* Blue */
#define C_END "\033[0m"


class Creeper
{
	// setting public for testing purposes
public:

	int_ts threadsWorking; 	// total no of threads working
	int_ts pagesLimitReached;
	int_ts totalPagesVisited; 	// for storing total processed pages till now

	//mutex timingLock;
	//vector<vector<double>> threadTimings;

	// lock and cond_var for parent
	bool ready = false;
	condition_variable cv;
	mutex cv_m;

	// Parameters
	int maxLinks = 100;
	int pagesLimit = 100;
	int maxThreads = 10;

	
	queue_ts linkQueue; 				// queue for storing linked websites
	map_ts<string, bool> discoveredSites; 	// map for storing visited websites
	//map_ts<string, set<string>> pageRank;		// for storing page relations
	

	// Constructor
	Creeper()
	{
		totalPagesVisited.assign(0);
		threadsWorking.assign(0);
		pagesLimitReached.assign(0);
	}


	// Public Functions

	void init(); 				//Initialize the Creeper
	
	string downloader(string url); 	//Downloads a website and save it in buffer folder

	void parseFile(string filename);	//Parse a file from the buffer and update parameters{concurrency part}
	
	void creep(); 				//Start a crawler to discover a specific website.

	void display();			//Show the results of the crawling
	
	void createThread();		

	void parent_sleep();

	void woke();

} myCreeper;

void child(string url, int th_num);

#endif
