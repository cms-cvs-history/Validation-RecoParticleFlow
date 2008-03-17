/*
 *  StatusMonitor.cpp
 *  ValidationFramework
 *
 *  Created by Thomas Punz on 18.02.08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "StatusMonitor.h"
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;


statusMonitor::statusMonitor()
{
	errors=new string*[10];
	errors[0]=new string("unkown error");
	errors[1]=new string("no_data in root file");
	errors[2]=new string("can not add histoData");
	
	error_log=new vector<int>;
}

statusMonitor::~statusMonitor()
{
	
}

void statusMonitor::report_error(int errorNumber)
{
	error_log->push_back(errorNumber);
	if(errorNumber==1 || errorNumber==2)
	{
		printErrorLog();
		exit(1);
	}
}

void statusMonitor::printErrorLog()
{
	for(int i=0; i<error_log->size(); i++)
	{
		cout<<(*errors[(*error_log)[i]])<<endl;
	}
}