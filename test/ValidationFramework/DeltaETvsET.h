/*
 *  DeltaET.h
 *  ValidationFramework
 *
 *  Created by Thomas Punz on 11.03.08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "vsBase.h"
#include <string.h>
#include <sstream>

class myMath;
class TH1F;
class TH2F;
class TH1D;
class TF1;
class TPad;
class TText;
class TCanvas;
class PlotCompareUtility;
class HistoData;

class DeltaETvsET : public vsBase{
	
public:
	DeltaETvsET(PlotCompareUtility*);
	~DeltaETvsET();
	virtual void histo_conf(int);
	virtual void print_gifs(int, int);
	
};