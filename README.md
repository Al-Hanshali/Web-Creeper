# Web-Creeper
Web Creeper:
Web Creeper is a web crawler that basically copies visited sites for later processing by a search engine. Its main purpose is web indexing. The goal of this project is to create a multi-threaded web crawler.

Flowchart:
 

Table of contents:
•	Web Creeper’s Components
•	How to Creep the Web
•	Future Developments
•	PowerPoint
•	How to Use this Repository

Web Creeper’s Components:
•	Creeper Initializer: Gets links from a file
•	A parent thread: for creating independent child threads
•	A downloader: to download the html of a website
•	A parser: to parse all urls from html
•	A displayer: to display the results




How to Creep the Web:
•	Compiling using make assigns parameters to default. Such parameters would be assigned in the following manner: maxlinks = 100 pagelimit = 100 threads = 10. You can change the default values in Creeper.h  
•	You can assign parameters different arguments. E.g:  make maxlinks = 50 pagelimit = 90 threads=20

Future Developments:
•	Implement a PageRank algorithm
•	Create a search engine that uses the indexed and ranked websites

PowerPoint:

Want to Use this Repository?
git clone https://github.com/hanshali/Web-Creeper
cd Web-Creeper
Make

Credits:
•	Dr. Lin Chase
•	http://www.andreas-hess.info/programming/webcrawler/index.html
•	https://github.com/kshru9
