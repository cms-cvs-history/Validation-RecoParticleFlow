/*
 *  vsBase.h
 *  ValidationFramework
 *
 *  Created by Thomas Punz on 17.03.08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __VSBASE__
#define __VSBASE__

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

class vsBase{
	
public:
	vsBase();
	vsBase(PlotCompareUtility*);
	~vsBase();
	void loop_over_et_bins(int, int);
	virtual int fetch_histos(int);
	virtual void histo_conf(int);
	virtual void draw_score_vs_ET(int);
	virtual void draw_test_plot_and_delta_et();
	virtual void draw_test_plot_sigma_ET_vs_ET();
	virtual void draw_summary();
	virtual void report(int);
	virtual void print_gifs(int, int);
	HistoData *hd;
	PlotCompareUtility *pc;
	int num_et_bins;
	float ks_score, chi2_score, result;
	TH1D *hnew;
	TH2F *hnew2d;
	TH1D *href;
	TH2F *href2d;
	TF1 *gfitref;
	TF1 *gfitnew;
	TPad *histo_p1;
	TPad *sigma_et_p;
	TPad *gmain_p;
	float *low_score;
	float *high_score;
	bool *testFailed;
	bool *empty;
	TH1F *hdumb; 
	TText *canvas_title1;
	TText *canvas_title;
	std::stringstream ss_title;
	std::string name;
	int counted_bins;
	float running_result;
	TH1F *hrefSigmaETOverETvsET;
	TH1F *hnewSigmaETOverETvsET;
	TH1F *hrefSigmaETOverETvsETsigma;
	TH1F *hnewSigmaETOverETvsETsigma;
	myMath *myMathO;
	float threshold;
	TH1F *h1dResults_passed;
	TH1F *h1dResults_failed;
	int num_histos;
	TH1F *hg1dResults_passed;
	TH1F *hg1dResults_failed;
	bool combinedFailed;
	double max_et;
	double min_et;
	int NumberHistos;
	TCanvas *histo_c1;
	TCanvas *sigma_et;
	TCanvas *gmain_c;
	int number;
	int *types;
	int type;
	TH1F *h2dResults;
	
};

#endif