#include <iostream>
#include <string>
#include <chrono>
#include <ctime> 
#include <iomanip>
#include <time.h>
#include <stdio.h>
#include <fstream>

using namespace std;

enum class EventType { created, edited, deleted, renamed };

class Event {
private:
	EventType mType;
	string mPath;
public:

	Event(EventType event, string path) {
		this->mType = event;
		this->mPath = path;
		time_t my_time = time(NULL);
		ofstream logs ("logs.txt");
		logs.open("logs.txt");
		switch (event) {
		case EventType::created:
			cout<< ctime(&my_time) << " File created " << path << endl;
			logs << ctime(&my_time) << " File created " << path << endl;
			break;
		case EventType::edited:
			cout << ctime(&my_time) << " File edited " << path << endl;
			logs << ctime(&my_time) << " File edited " << path << endl;
			break;
		case EventType::deleted:
			cout << ctime(&my_time) << " File deleted " << path << endl;
			logs << ctime(&my_time) << " File deleted " << path << endl;
			break;
		case EventType::renamed:
			cout<< ctime(&my_time) << " File renamed " << path << endl;
			logs << ctime(&my_time) << " File renamed " << path << endl;
			break;
		}
		logs.close();
	}
};