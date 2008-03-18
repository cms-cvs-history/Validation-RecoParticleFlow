/*
 *  DeltaEta.h
 *  ValidationFramework
 *
 *  Created by Thomas Punz on 18.03.08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "simpleDistributionBase.h"
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

class    DeltaEta : public simpleDistributionBase{
	
public:
	DeltaEta(PlotCompareUtility*);
	~DeltaEta();
	virtual void histo_conf(int);
	virtual void print_gifs(int, int);
	
};