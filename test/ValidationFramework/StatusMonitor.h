/*
 *  StatusMonitor.h
 *  ValidationFramework
 *
 *  Created by Thomas Punz on 18.02.08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __STATUSMONITOR__
#define __STATUSMONITOR__

#include <vector>
#include <string.h>

class statusMonitor{
public:
	statusMonitor();
	~statusMonitor();
	void report_error(int=0);
	void printErrorLog();
private:
	std::string **errors;
	std::vector <int> *error_log;
};

#endif