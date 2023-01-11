#ifndef CREEPER.CPP
#define CREEPER.CPP

#include "Creeper.h"

void Creeper::init()
{
	ifstream url("seeds.txt"); // Extract initial urls
	if(url)
	{
		int n;			// Holds number of urls
		url >> n;		
		string s;
		for(int i = 0; i < n; i++)
		{
			url >> s;		
			if( s != "")
			{
				linkQueue.push(s);
			}
			else
			{
				break;
			}
		}
	}
	else
	{
		cout << "Unable to read starting links from seeds.txt" << endl;
		linkQueue.push("htps://www.google.com");
	
	}			
}

void Creeper::creep()
{
	while(true)
	{
		
		if(pagesLimitReached.value())
		{
			cout << RED << "EXITING!" << C_END <<endl;
			break;
		}
		else
		{
			if(threadsWorking.value() < maxThreads && linkQueue.size() > 0)
			{
				createThread();
			}
			else if(threadsWorking.value() == 0)
			{
				cout << RED << "No threads wokring. EXITING!" << C_END <<endl;	
				break;
			}
			else
			{
				parent_sleep();
			}
		}
	}		
}

void Creeper::createThread()
{	
	string currentSite = linkQueue.pop(); 	//Get current site
	totalPagesVisited.add(1);
	threadsWorking.add(1);

	cout << GREEN << "Creating a thread, total: " << threadsWorking.value() << C_END << endl;
	
	// Make sure to update pagesLimitReached
	if(totalPagesVisited.value() >= pagesLimit)
	{
		pagesLimitReached.add(1);
		cout<< RED << "Page Limit Reached!" << C_END << endl;
	}
	
	thread *th = new thread(child, currentSite, totalPagesVisited.value()); 	//Create a new thread
	(*th).detach();								// Make thread work independently
}	

void child(string url, int th_num)
{	
	//Download html
	string html = myCreeper.downloader(url);
	cout << CYAN << "Thread " << th_num << " has downloaded files." << C_END << endl;
	
	//Parse html
	set<string> linkedSites = getLinks(html, myCreeper.maxLinks);
	cout << CYAN << "Thread " << th_num << " has extracted links." << C_END << endl;
	
	//Update shared variables
	for(auto i : linkedSites)
	{	
		if(!myCreeper.discoveredSites.get(i))
		{
			myCreeper.discoveredSites.inc(i);
			myCreeper.linkQueue.push(i);	
		}
	}	
	
	cout << CYAN << "Thread " << th_num << " has updated shared var." << C_END << endl;
	
	unique_lock<mutex> lk(myCreeper.cv_m); //unique lock for cv
	myCreeper.threadsWorking.add(-1);
	cout << BLUE << "Thread " << th_num << " has finished, total threads: " << myCreeper.threadsWorking.value() << C_END << endl;
	     	
	//Wake up main thread to create more threads or exit if creeping is completed 	
	myCreeper.woke();
}

string Creeper::downloader(string url)
{	
	string html;
	
	// Check if website is http or https then download html accordingly
	if(url.substr(0, 5) == "https")
	{
		html = httpsDownloader(url);
	}
	else
	{
		html = httpDownloader(url);
	}
	return html;		
}

void Creeper::parent_sleep()
{
	unique_lock<mutex> lk(cv_m); //unique lock for conditional variable
	cout << "Parent thread going to sleep" << endl;
	ready = false;			// main thread can't process any data
	
	while(!ready)
	{
		cv.wait(lk);		// Wait until parent becomes not ready
	}
	cout << "Parent thread awake!" << endl;
}		

void Creeper::woke()
{
	ready  = true;		//wake main up
	cv.notify_one();	//notify sleeping thread
}

void Creeper::display()
{
	string dashline  = "--------------------------------------";
	cout << endl;
	cout << "Parameters:" << endl;
	cout << dashline << endl;
	cout << "Maximum urls:" << "\t" << maxLinks << endl;
	cout << "Maximum threads working:" << "\t" << maxThreads << endl;
	cout << "Maximum pages downloaded:" << "\t" << pagesLimit << endl;
	cout << "Total pages visited:" << "\t" << totalPagesVisited.value() << endl;
}		
#endif
		

