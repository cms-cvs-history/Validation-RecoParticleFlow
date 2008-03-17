/*
 *  Validator.h
 *  ValidationFramework
 *
 *  Created by Thomas Punz on 26.02.08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include <string.h>
#include <sstream>

class myMath;
class PlotCompareUtility;
class HistoData;
class TH1F;
class TH1D;
class TH2F;
class TF1;
class TPad;
class statusMonitor;

class TCanvas;
class TText;
class DeltaETvsET;
class DeltaPHIvsPHI;
class DeltaEtvsPhi;
class DeltaEtavsEta;
class DeltaPhivsEta;

class DeltaETOverEtvsPhi;
class DeltaEtaOverEtavsPhi; 
class DeltaEtvsDeltaR;
class DeltaRvsEt;
class DeltaEtOverEtvsDeltaR;
class DeltaEtavsEt;
class DeltaPhiOverPhivsEt;
class DeltaRvsEta;
class DeltaEtOverEtvsEt;
class DeltaEtaOverEtavsEt;
class DeltaEtvsEta;
class DeltaPhiOverPhivsEta;
class DeltaRvsPhi;
class DeltaEtOverEtvsEta;
class DeltaEtaOverEtavsEta;
class DeltaEtavsPhi;
class DeltaPhiOverPhivsPhi;


class validator{
	
	
public:
	validator();
	validator(std::string, std::string);
	~validator();

	virtual void histo_Loop();

	myMath *myMathO;
	PlotCompareUtility *pc;
	HistoData *hd;
	
	
	DeltaETvsET *deltaETvsEt;
	DeltaPHIvsPHI *deltaPHIvsPhi;
	DeltaEtvsPhi *deltaEtvsPhi;
	DeltaEtavsEta *deltaEtavsEta;
	DeltaPhivsEta *deltaPhivsEta;
	
	DeltaETOverEtvsPhi *deltaEtOverEtvsPhi;
	DeltaEtaOverEtavsPhi *deltaEtaOverEtavsPhi; 
	DeltaEtvsDeltaR *deltaEtvsDeltaR;
	DeltaRvsEt *deltaRvsEt;
	DeltaEtOverEtvsDeltaR *deltaEtOverEtvsDeltaR;
	DeltaEtavsEt *deltaEtavsEt;
	DeltaPhiOverPhivsEt *deltaPhiOverPhivsEt;
	DeltaRvsEta *deltaRvsEta;
	DeltaEtOverEtvsEt *deltaEtOverEtvsEt;
	DeltaEtaOverEtavsEt *deltaEtaOverEtavsEt;
	DeltaEtvsEta *deltaEtvsEta;
	DeltaPhiOverPhivsEta *deltaPhiOverPhivsEta;
	DeltaRvsPhi *deltaRvsPhi;
	DeltaEtOverEtvsEta *deltaEtOverEtvsEta;
	DeltaEtaOverEtavsEta *deltaEtaOverEtavsEta;
	DeltaEtavsPhi *deltaEtavsPhi;
	DeltaPhiOverPhivsPhi *deltaPhiOverPhivsPhi;
	
	
	
	
	bool combinedFailed;
	int *types;
	int type;
	int num_et_bins;
	int number;
	std::string name;
	int num_histos;
	TH2F *hnew2d;
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

	//int bin;
	double max_et;
	double min_et;
	int NumberHistos;
	std::stringstream ss_title;
	TCanvas *histo_c1;
	TCanvas *sigma_et;
	TCanvas *gmain_c;
	TH1F *hrefSigmaETOverETvsET;
	TH1F *hnewSigmaETOverETvsET;
	TH1F *hrefSigmaETOverETvsETsigma;
	TH1F *hnewSigmaETOverETvsETsigma;
	
	float threshold;
	TH1F *h1dResults_passed;
	TH1F *h1dResults_failed;
	
	TH1F *hg1dResults_passed;
	TH1F *hg1dResults_failed;
	
	TH1D *hnew;
	TH1D *href; 

	
	
	TH1F *h2dResults;
	int counted_bins;
	float running_result;
	
	TText *canvas_title1;
	TText *canvas_title;
	
	statusMonitor *sm;
	TH1F *hdumb; 

private:
	
	
};