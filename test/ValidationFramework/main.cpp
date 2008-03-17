#include <iostream>
#include "HistoManager.h"
#include "StatusMonitor.h"
#include "Validator.h"

#include "TFile.h"

using namespace std;

int main (int argc, char* argv[]) {
	validator *val=new validator(argv[1] ,argv[2]);
	delete val;
	return 0;
}
