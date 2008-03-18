/*
 *  simpleDistributionBase.cpp
 *  ValidationFramework
 *
 *  Created by Thomas Punz on 17.03.08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "simpleDistributionBase.h"

#include "myMath.h"

#include <iostream>
#include <sstream>
#include <TMath.h>
#include <TH1.h>
#include <TH2.h>
#include <TSystem.h>
#include "TFile.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TF1.h"
#include "TText.h"
#include "TPaveLabel.h"
#include "TLine.h"
#include "TLegend.h"
#include "TRandom.h"
#include "myMath.h"
#include "StatusMonitor.h"
#include <string.h>
#include "PlotCompareUtility.h"
#include "HistoData.h"
#include "ValidationTools.h"

#include "PlotCompareUtility.h"

using namespace std;

const bool KS_TEST = false;
const bool CHI2_TEST = true;

simpleDistributionBase::simpleDistributionBase()
{
	
}

simpleDistributionBase::simpleDistributionBase(PlotCompareUtility *pc)
{
	this->pc=pc;
	num_histos = pc->GetNumHistos();	
	
	// arrays/variables to store test scores and overall pass/fail evaluations
	low_score = new float[num_histos];
	high_score = new float[num_histos];
	testFailed = new bool[num_histos];
	empty = new bool[num_histos];
	types = new int[num_histos];
	combinedFailed = false;
	NumberHistos = 23;
	
	
	for (int index = 0; index < num_histos; index++) 
	{
		// initialize. memset to non-zero is dangerous with float types
		low_score[index] = 1;
		high_score[index] = 0;
		testFailed[index] = false;
		empty[index] = false; //true;
		types[index] = 0;
	}
	
	threshold = KS_TEST ? pc->GetKSThreshold() : pc->GetChi2Threshold();   
	
	
	// create overview results summary histogram
	
	// create summary histograms
	
	hg1dResults_passed=new TH1F("hg1dResults_passed","",NumberHistos, 1, NumberHistos+1);
	hg1dResults_failed=new TH1F("hg1dResults_failed","",NumberHistos, 1, NumberHistos+1);
	h2dResults=new TH1F("h2dResults","h2dResults", num_histos, 1, num_histos + 1);
}

simpleDistributionBase::~simpleDistributionBase()
{
	
}

int simpleDistributionBase::fetch_histos(int histo_index)
{
	int index=histo_index;
	
	number = index + 1;
	hd = pc->GetHistoData(number);
	type = hd->GetType();
	types[index] = type;
	name = hd->GetName();
	string value = hd->GetValueX();
	cout <<"Name of Checked Histogram: "<< name << endl;
	// get the reference and comparison 2d histograms
	hnew2d = (TH1F *)pc->GetNewHisto(name);
	href2d = (TH1F *)pc->GetRefHisto(name);
	
	// ignore if histogram is broken
	if (hnew2d->GetEntries() <= 1 || href2d->GetEntries() <= 1)
	{
		cout << "problem with histogram " << name << endl;
		return 1;
	}
	
	num_et_bins = href2d->GetNbinsX();
	min_et = href2d->GetXaxis()->GetXmin();
	max_et = href2d->GetXaxis()->GetXmax();
	
	cout<<"Num Et bins: "<<num_et_bins<<endl;
	cout<<"Min Et: "<<min_et<<endl;
	cout<<"Max Et: "<<max_et<<endl;
	
	
	
	//--HACK
	if(num_et_bins>100)
	{
		cout<<"WARNING: Too much bins --> Resizing to 100"<<endl;
		num_et_bins = 100;
		min_et = 0;
		max_et = 100;
	}
	
	// create 1d histograms to put projection results into
	string titleP = "h1dResults_passed_" + name;
	string titleF = "h1dResults_failed_" + name;
	h1dResults_passed=new TH1F(titleP.c_str(),titleP.c_str(),num_et_bins,min_et,max_et);
	h1dResults_failed=new TH1F(titleF.c_str(),titleF.c_str(),num_et_bins,min_et,max_et);
	
	// create a subdirectory in which to put resultant histograms
	gSystem->mkdir(name.c_str());
	
	// create a sigma_ET/ET 1-D histogram
	string refTitleSigma = "ref_" + name + "sigmaETOverETvsET";
	string newTitleSigma = "new_" + name + "sigmaETOverETvsET";
	hrefSigmaETOverETvsET=new TH1F(refTitleSigma.c_str(),refTitleSigma.c_str(),num_et_bins,min_et,max_et);
	hnewSigmaETOverETvsET=new TH1F(newTitleSigma.c_str(),newTitleSigma.c_str(),num_et_bins,min_et,max_et);
	hrefSigmaETOverETvsETsigma=new TH1F("temporary_ref",refTitleSigma.c_str(),num_et_bins,min_et,max_et);
	hnewSigmaETOverETvsETsigma=new TH1F("temporary_new",newTitleSigma.c_str(),num_et_bins,min_et,max_et);
	return 0;
}


void simpleDistributionBase::histo_conf(int type)
{
	if(type==1)
	{
		href->GetXaxis()->SetTitle("Eta");
		href->GetYaxis()->SetTitle("Events");
		href->GetYaxis()->SetTitleOffset(1.5);
		
		hnew->GetXaxis()->SetTitle("eta");      
		//	href->GetYaxis()->SetTitle("Events");
		
		h1dResults_passed->GetXaxis()->SetTitle("Eta");
		h1dResults_passed->GetYaxis()->SetTitle("Compatibility");
		
		hg1dResults_passed->GetYaxis()->SetTitle("Compatibility");
		hg1dResults_failed->GetYaxis()->SetTitle("Compatibility");
		
		hrefSigmaETOverETvsETsigma->GetXaxis()->SetTitle("eta");
		hrefSigmaETOverETvsETsigma->GetYaxis()->SetTitle("#sigma(#DeltaEta)/Eta");
		
		
		
		
		
		// set drawing options on the reference histogram
		href->SetStats(0);
		href->SetLineWidth(2);
		href->SetLineColor(14);
		href->SetMarkerColor(14);
		href->SetFillColor(17);
		gfitref->SetLineColor(17);
		//href->SetFillStyle(3001);
		
		// set drawing options on the new histogram
		hnew->SetStats(0);
		hnew->SetLineWidth(2);
		hnew->SetFillStyle(3001);
		
		// set drawing options on the dummy histogram
		hdumb->SetStats(0);
		//hdumb->GetXaxis()->SetTitle(name.c_str());
		hdumb->GetXaxis()->SetTitle("Eta");
		
		hdumb->GetXaxis()->SetLabelSize(0.5 * hdumb->GetXaxis()->GetTitleSize());
		hdumb->GetYaxis()->SetTitle("Entries");
		hdumb->GetYaxis()->SetTitleOffset(1.5);
		hdumb->GetYaxis()->SetLabelSize(0.5 * hdumb->GetXaxis()->GetTitleSize());
		
		
		ss_title.precision(5);
		ss_title << "KS Score = " << ks_score << ", Chi^2 Score = " << chi2_score;	
		
	}
	else if(type==2)
	{
		// make this histogram red to denote failure
		hnew->SetFillColor(kRed);
		//hnew->SetLineColor(kRed);
		hnew->SetMarkerColor(kRed);
		gfitnew->SetLineColor(kRed);
		hnew->SetLineColor(206);
		hnew->SetMarkerColor(206);
	}
	else if(type==3)
	{
		// make this histogram green to denote passing
		hnew->SetFillColor(kGreen);
		//hnew->SetLineColor(kGreen);
		hnew->SetMarkerColor(103);
		gfitnew->SetLineColor(103);
		hnew->SetLineColor(103);
		hnew->SetMarkerColor(103);
	}
	
}

void simpleDistributionBase::loop_over_et_bins(int histo_index, int bin_index)
{
	// loop over Et bins
	int index=histo_index;
	int bin=bin_index;
	// unique names should _NOT_ be used (ProjectionY will re-alloc memory
	// each time... But... Root is buggy and won't reliably display)....
	stringstream hname_new, hname_ref;
	hname_new << "tmp_hnew_" << name << "_" << bin;
	hname_ref << "tmp_href_" << name << "_" << bin;
	
	// get the 1d projection for this ieta bin out of the histogram
	hnew = hnew2d;
	href = href2d;
	 
	
	
	// calculate and set range and number of bins
	double h1RMS =  hnew->GetRMS();
	double h2RMS =  href->GetRMS();
	double h1dRMS = hnew->GetRMSError();
	double h2dRMS = href->GetRMSError();
	double RMS = TMath::Max(h1RMS, h2RMS);
	double h1Mean =  hnew->GetMean();
	double h2Mean =  href->GetMean();
	double Mean = 0.5 * (h1Mean + h2Mean);
	double Nbins = href->GetNbinsX();
	double min = href->GetXaxis()->GetXmin();
	double max = href->GetXaxis()->GetXmax();
	double dX = max - min;
	double dNdX = 1;
	double NewMin = 0;
	double NewMax = 1;
	if (RMS>0) 
	{
		dNdX = 100. / ( 10 * RMS);
		NewMin = Mean - 5 * RMS;
		NewMax = Mean + 5 * RMS;
	}
	int rebinning = 1;
	if ((dX * dNdX)>0) 
		rebinning = (int)(double(Nbins) / (dX * dNdX));
	
	href->GetXaxis()->SetRangeUser(NewMin, NewMax);
	hnew->GetXaxis()->SetRangeUser(NewMin, NewMax);
	
	if (rebinning > 1) {
		href->Rebin(rebinning);
		hnew->Rebin(rebinning);
	}
	
	
	//double scale_ref = href->GetMaximum();
	//double scale_new = hnew->GetMaximum();
	
	
	//href->SetNormFactor(1);
	//hnew->SetNormFactor(1);
	
	// ensure that the peaks of both histograms will be shown
	if (href->GetMaximum() < hnew->GetMaximum())
		href->SetAxisRange(0, 1.03 * hnew->GetMaximum(), "Y");
	
	
	float Nentries_ref = href->GetEntries();
	float Nentries_new = hnew->GetEntries();
	
	
	bool empty=false;
	if(Nentries_ref==0 && Nentries_new==0)
	{
		empty=true;
		result=1;
	}
	
	// test the distributions directly	
	if(!empty)
	{
		ks_score = hnew->KolmogorovTest(href);
		chi2_score = hnew->Chi2Test(href);
		//if (KS_TEST) result = ks_score; else result = chi2_score;
		result = (ks_score>chi2_score) ? ks_score : chi2_score;
	}
	running_result += result; counted_bins++;
	
	if (result > high_score[index]) { high_score[index] = result; }
	if (result < low_score[index]) { low_score[index] = result; }
	
	double et = href2d->GetBinCenter(bin);
	
	
	href->SetNormFactor(hnew->GetEntries());
	
	// ensure that the peaks of both histograms will be shown by making a dummy histogram
	
	float XaxisMin_ref = 0, XaxisMax_ref = 0, YaxisMin_ref = 0, YaxisMax_ref = 0;
	float XaxisMin_new = 0, XaxisMax_new = 0, YaxisMin_new = 0, YaxisMax_new = 0;
	if (Nentries_ref>0) YaxisMax_ref = (href->GetMaximum()+sqrt(href->GetMaximum()))*(Nentries_new/Nentries_ref);
	if (Nentries_new>0) YaxisMax_new = (hnew->GetMaximum()+sqrt(hnew->GetMaximum()));
	
	XaxisMin_ref = href->GetXaxis()->GetXmin()>NewMin  ? href->GetXaxis()->GetXmin() : NewMin;
	XaxisMax_ref = href->GetXaxis()->GetXmax()<=NewMax ? href->GetXaxis()->GetXmax() : NewMax;
	YaxisMax_ref = (YaxisMax_ref>=YaxisMax_new) ? YaxisMax_ref : YaxisMax_new;
	
	cout << "!!! " << Nentries_ref << " " << Nentries_new << " :  " << YaxisMax_ref << " " << YaxisMax_new << endl;
	
	
	
	if (myMathO->myFabs(XaxisMin_ref - XaxisMax_ref)<1E-6)
	{
		XaxisMin_ref = 0;
		XaxisMax_ref = 1;
	}
	
	hdumb = new TH1F("hdumb","", rebinning, XaxisMin_ref, XaxisMax_ref);
	hdumb->SetMinimum(1E-1);
	hdumb->SetMaximum(1.05*YaxisMax_ref);
	
	
	// fit both histograms with a gaussian
	gfitref = new TF1("gfitref","gaus",Mean - 3 * RMS, Mean + 3 * RMS);
	gfitnew = new TF1("gfitnew","gaus",Mean - 3 * RMS, Mean + 3 * RMS);
	
	
	href->Fit(gfitref,"QNR");
	hnew->Fit(gfitnew,"QNR");
	
	// set the resolution
	hrefSigmaETOverETvsET->SetBinContent(bin, h2RMS / et);
	hnewSigmaETOverETvsET->SetBinContent(bin, h1RMS / et);
	//hrefSigmaETOverETvsETsigma.SetBinContent(bin,gfitref->GetParameter(2) / et);
	//hnewSigmaETOverETvsETsigma.SetBinContent(bin,gfitnew->GetParameter(2) / et);
	
	
	// set the resolution errors
	hrefSigmaETOverETvsETsigma->SetBinError(bin, h2dRMS / et);
	hnewSigmaETOverETvsETsigma->SetBinError(bin, h1dRMS / et);
	if(!empty)
	{
		histo_conf(1);
		canvas_title=new TText(0.1,0.97,ss_title.str().c_str());
		if (result <= threshold) {
			
			histo_conf(2);
			// mark the sample as being 'not-compatible'
			testFailed[index] = true;
			combinedFailed = true;
			
			// set the summary bin to failed (only need to set titles for passed h1dResults)
			//h1dResults_passed.GetXaxis()->SetBinLabel(bin, bin_label.str().c_str());
			h1dResults_failed->SetBinContent(bin,result);
			
			// set the canvas title
			canvas_title->SetTextColor(kRed);
			
		} else {
			
			histo_conf(3);
			
			// set the summary bin to passed
			//h1dResults_passed.GetXaxis()->SetBinLabel(bin, bin_label.str().c_str());
			h1dResults_passed->SetBinContent(bin,result);
			
			// set the canvas title
			canvas_title->SetTextColor(kGreen);
			
		}
		
		print_gifs(1,bin);
	}
	// report the obtained KS score
	cout << "  et = " << et << ": result = " << result <<  " : testFailed = " << testFailed[index] << endl; 
	delete hdumb;
	
}


void simpleDistributionBase::draw_score_vs_ET(int histo_index)
{
	int index=histo_index;
	//----------------Start Draw bin-by-bin Score vs ET bin--------------------------------------//
	{
		// create et summary canvas
		TCanvas et_c("et_c","et_c",1000,500);
		et_c.Draw();
		
		TPad et_p("et_p","et_p",0,0,1,1);
		et_p.SetLogy(1);
		et_p.SetFrameFillColor(10);
		et_p.Draw();
		
		et_c.cd();
		TText et_title(.01, .01, "Compatibility with Reference Histograms");
		et_title.Draw("SAME");
		
		et_p.cd();
		
		// setup the passing test bars
		h1dResults_passed->SetStats(0);
		h1dResults_passed->GetXaxis()->SetLabelSize(0.03);
		
		//h1dResults_passed.GetXaxis()->SetBit(TAxis::kLabelsVert);
		
		h1dResults_passed->SetBarWidth(0.7);
		h1dResults_passed->SetBarOffset(0.1);
		//h1dResults_passed.SetLineColor(1);
		h1dResults_passed->GetYaxis()->SetRangeUser(1E-7,2);
		
		// setup the failing test bars
		h1dResults_failed->SetStats(0);
		//h1dResults_failed.GetXaxis()->SetLabelSize(0.04);
		//h1dResults_failed.GetYaxis()->SetTitle("Compatibility");
		h1dResults_failed->SetBarWidth(0.7);
		h1dResults_failed->SetBarOffset(0.1);
		//h1dResults_failed.SetLineColor(1);
		h1dResults_failed->GetYaxis()->SetRangeUser(1E-7,2);
		
		if (empty[index]) {
			// do nothing
			/*  }  else if (type == 1) {
			 h1dResults_passed.SetFillColor(18);
			 h1dResults_passed.SetLineColor(18);
			 h1dResults_passed.Draw("bar");*/
		} else {
			h1dResults_passed->SetFillColor(kGreen);
			h1dResults_passed->SetLineColor(kGreen);
			h1dResults_failed->SetFillColor(kRed);
			h1dResults_failed->SetLineColor(kRed);
			h1dResults_passed->Draw("bar");
			h1dResults_failed->Draw("barSAME");
		}
		
		// draw the pass/fail threshold line
		TLine l(min_et, threshold, max_et, threshold);
		l.SetLineColor(kRed);
		l.SetLineWidth(2);
		l.SetLineStyle(2);
		l.Draw("SAME");
		
		// print the results
		et_c.Update();
		string et_name = name + "dET_Score_vs_et.gif";
		et_c.Print(et_name.c_str(),"gif");
	}
	//----------------End Draw bin-by-bin Score vs ET bin--------------------------------------//
}




void simpleDistributionBase::draw_test_plot_and_delta_et()
{
	//----------------Start Test and Plot Delta ET distribution-----------------------------------//
	// get the 1d projection for this ieta bin out of the histogram
	stringstream hname_new, hname_ref;
	hname_new << "tmp_hnew_" ;
	hname_ref << "tmp_href_" ;
	hnew = hnew2d;
	href = href2d;
	
	//    float ks_score = hnewSigmaETOverETvsET.KolmogorovTest(&hrefSigmaETOverETvsET);
	//float chi2_score = hnewSigmaETOverETvsET.Chi2Test(&hrefSigmaETOverETvsET);
	float ks_score = hnew->KolmogorovTest(href);
	float chi2_score = hnew->Chi2Test(href);
	//double result = KS_TEST ? ks_score : chi2_score;
	float result = (ks_score>chi2_score) ? ks_score : chi2_score;
	
	//----Fill "Global" Delta Et result 
	// determine if test is a "pass" or a "fail"
	if (result <= threshold) {
		// set the summary bin to failed (only need to set titles for passed h1dResults)
		hg1dResults_failed->GetXaxis()->SetBinLabel(NumberHistos-(number-1), "#DeltaE_{T}");
		hg1dResults_failed->GetXaxis()->SetBinLabel(NumberHistos-(number-1)-1, "#DeltaE_{T}[E_{T}] Range");
		hg1dResults_failed->SetBinContent(NumberHistos-(number-1), result);
	} else {
		hg1dResults_passed->GetXaxis()->SetBinLabel(NumberHistos-(number-1), "#DeltaE_{T}");
		hg1dResults_passed->GetXaxis()->SetBinLabel(NumberHistos-(number-1)-1, "#DeltaE_{T}[E_{T}] Range");
		hg1dResults_passed->SetBinContent(NumberHistos-(number-1), result);      
	}
	
	
	ss_title.precision(5);
	ss_title << "KS Score = " << ks_score << ", Chi^2 Score = " << chi2_score;
	canvas_title1=new TText(0.1,0.97,ss_title.str().c_str());
	
	if (result <= threshold) {
		
		// make this histogram red to denote failure
		hnew->SetFillColor(kRed);
		//hnew->SetLineColor(kRed);
		hnew->SetMarkerColor(kRed);
		hnew->SetLineColor(206);
		hnew->SetMarkerColor(206);
		
		// set the canvas title
		canvas_title1->SetTextColor(kRed);
		
	} else {
		
		// make this histogram green to denote passing
		hnew->SetFillColor(kGreen);
		//hnew->SetLineColor(kGreen);
		hnew->SetMarkerColor(103);
		hnew->SetLineColor(103);
		hnew->SetMarkerColor(103);
		// set the canvas title
		canvas_title1->SetTextColor(kGreen);
	}
	
	
	
	//----------------End Test and Plot Delta ET distribution-----------------------------------//
	// setup canvas for displaying the compared histograms
	histo_c1=new TCanvas("histo_c1","histo_c1",785,800);
	histo_c1->Draw();
	
	histo_p1=new TPad("histo_p1","histo_p1",0.01,0.01,0.99,0.94);
	histo_p1->Draw();
	
	histo_c1->cd();
	canvas_title1->SetTextSize(0.025);
	canvas_title1->Draw();
	
	histo_p1->cd();
	histo_p1->SetLogy(1);
	href->SetMinimum(1E-1);
	hnew->SetMinimum(1E-1);
	
	hnew->SetStats(0);
	hnew->SetLineWidth(2);
	href->SetLineWidth(2);
	hnew->SetFillStyle(3001);
	// set drawing options on the reference histogram
	href->SetStats(1);
	href->SetLineWidth(2);
	href->SetLineColor(14);
	href->SetMarkerColor(14);
	href->SetFillColor(17);
	
	href->Rebin(5);
	hnew->Rebin(5);
	
	
	
	href->Draw();
	hnew->Draw("SAME");
	
	TLegend l1(0.15,0.01,0.3, 0.08);
	l1.AddEntry(hnew,"New","lF");
	l1.AddEntry(href,"Reference","lF");
	l1.SetFillColor(kNone);
	l1.Draw("SAME");
	//histo_c1->Print("test.gif");
	
}


void simpleDistributionBase::draw_test_plot_sigma_ET_vs_ET()
{
	//----------------Start Test and Plot sigma(ET)/ET vs ET distribution-------------------------//
	double ks_score = hnewSigmaETOverETvsETsigma->KolmogorovTest(hrefSigmaETOverETvsET,"D");
	double chi2_score = hnewSigmaETOverETvsETsigma->Chi2Test(hrefSigmaETOverETvsET,"p");
	//double result = KS_TEST ? ks_score : chi2_score;
	double result = (ks_score>chi2_score) ? ks_score : chi2_score;
	
	// determine if test is a "pass" or a "fail"
	if (result <= threshold) {
		// set the summary bin to failed (only need to set titles for passed h1dResults)
		hg1dResults_failed->GetXaxis()->SetBinLabel(NumberHistos-(number-1)-3, "#sigma(#DeltaE_{T})/E_{T}");
		hg1dResults_failed->SetBinContent(NumberHistos-(number-1)-3, result);
	} else {
		hg1dResults_passed->GetXaxis()->SetBinLabel(NumberHistos-(number-1)-3, "#sigma(#DeltaE_{T})/E_{T}");
		hg1dResults_passed->SetBinContent(NumberHistos-(number-1)-3, result);
		
	}
	
	// create sigma(ET)/ET summary canvas
	sigma_et=new TCanvas("sigma_et","sigma_et",1000,500);
	sigma_et->Draw();
	
	sigma_et_p=new TPad("sigma_et_p","sigma_et_p",0,0,1,1);
	//sigma_et_p.SetLogy(1);
	sigma_et_p->SetFrameFillColor(10);
	sigma_et_p->Draw();
	
	sigma_et->cd();
	TText sigma_et_title(.01, .01, "");
	sigma_et_title.Draw("SAME");
	
	sigma_et_p->cd();
	
	//hrefSigmaETOverETvsET.SetMarkerStyle(8);
	//hrefSigmaETOverETvsET.SetMarkerSize(.5);
	//hrefSigmaETOverETvsET.GetYaxis()->SetRangeUser(0,0.3);
	//hrefSigmaETOverETvsET.Draw("P");
	
	hrefSigmaETOverETvsETsigma->SetStats(0); 
	hrefSigmaETOverETvsETsigma->SetMarkerStyle(4);
	hrefSigmaETOverETvsETsigma->SetMarkerSize(.5);
	hrefSigmaETOverETvsETsigma->GetYaxis()->SetRangeUser(0,3);
	
	hrefSigmaETOverETvsETsigma->Draw("LSAME");
	
	//hnewSigmaETOverETvsET.SetMarkerStyle(8);
	//hnewSigmaETOverETvsET.SetMarkerSize(.5);
	//hnewSigmaETOverETvsET.SetMarkerColor(kBlue);
	//hnewSigmaETOverETvsET.GetYaxis()->SetRangeUser(0,0.3);
	//hnewSigmaETOverETvsET.Draw("PSAME");
	
	hnewSigmaETOverETvsETsigma->SetStats(0); 
	hnewSigmaETOverETvsETsigma->SetMarkerStyle(4);
	hnewSigmaETOverETvsETsigma->SetMarkerSize(.5);
	hnewSigmaETOverETvsETsigma->SetMarkerColor(kGreen);
	hnewSigmaETOverETvsETsigma->SetLineColor(kGreen);
	hnewSigmaETOverETvsETsigma->GetYaxis()->SetRangeUser(0,3);
	if (result <= threshold) 
	{
		hnewSigmaETOverETvsETsigma->SetMarkerColor(kRed);
		hnewSigmaETOverETvsETsigma->SetLineColor(kRed);
	}
	hnewSigmaETOverETvsETsigma->Draw("LSAME");
	
	sigma_et->Update();
	
	//----------------End Test and Plot sigma(ET)/ET vs ET distribution-------------------------//
	
}

void simpleDistributionBase::draw_summary()
{
	
	//----------------Start Draw Summary Histogram--------------------------------------------------//
	// create summary canvas
	int summary_height = int(780 * float(NumberHistos) / 22); // 780;
	gmain_c=new TCanvas("gmain_c","gmain_c",799,summary_height);
	gmain_c->Draw();
	
	gmain_p=new TPad("gmain_p","gmain_p",0.01,0.01,0.99,0.94);
	gmain_p->SetLeftMargin(0.30);
	gmain_p->SetBottomMargin(0.15);
	gmain_p->SetLogx(1);
	gmain_p->SetGrid();
	gmain_p->SetFrameFillColor(10);
	gmain_p->Draw();
	
	gmain_c->cd();
	TText summary_title(.01, .95, "");
	summary_title.Draw("SAME");
	
	gmain_p->cd();
	
	// setup the passing test bars
	hg1dResults_passed->SetStats(0);
	hg1dResults_passed->GetXaxis()->SetLabelSize(0.04);
	
	hg1dResults_passed->SetBarWidth(0.7);
	hg1dResults_passed->SetBarOffset(0.1);
	hg1dResults_passed->SetFillColor(kGreen);
	hg1dResults_passed->SetLineColor(1);
	hg1dResults_passed->GetYaxis()->SetRangeUser(1E-7,2);
	hg1dResults_passed->Draw("hbar0");
	
	
	
	//----start draw bin-by-bin score
	{
		int ibox=0;
		TBox box;
		box.SetLineWidth(2);
		// form a display box based on the range of scores
		float box_min = low_score[ibox];
		float box_max = high_score[ibox];
		
		// ensure that the box does not go below the range of the results histo
		if (box_min < 1E-7) box_min = 1E-7;
		if (box_max < 1E-7) box_max = 1E-7;
		
		// ensure that something is drawn, even if length = 0 (such as all tests = 1 or 0)
		if (myMathO->myFabs(box_min - box_max) < 0.01) {
			
			TLine box_line;
			box_line.SetLineWidth(4);
			
			float line_pos = (box_max + box_min) / 2;
			if (types[ibox] == 1)
				box_line.SetLineColor(18);
			else if (testFailed[ibox])
				box_line.SetLineColor(kRed);
			else box_line.SetLineColor(kGreen);
			
			box_line.DrawLine(line_pos, NumberHistos - ibox + 1.25 - 2, line_pos, NumberHistos - ibox + 1.9 - 2);
			//continue;
		}
		
		if (empty[ibox]) {
			box_min = 1E-7; box_max = 1;
			box.SetFillStyle(3005);
			box.SetFillColor(18);
			box.SetLineColor(18);
			box.SetLineStyle(1);
			/*  } else if (types[1] == 1) {
			 //box_min = 1E-7; box_max = 1;
			 box.SetFillStyle(1001);
			 box.SetFillColor(18);
			 box.SetLineColor(18);
			 box.SetLineStyle(0);*/
		} else if (testFailed[ibox]) {
			box.SetFillStyle(1001);
			box.SetLineStyle(0);
			box.SetLineColor(kRed);
			box.SetFillColor(kRed);
		} else {
			box.SetFillStyle(1001);
			box.SetLineStyle(0);
			box.SetLineColor(kGreen);
			box.SetFillColor(kGreen);
		}
		
		// draw the box
		box.DrawBox(box_min, NumberHistos - ibox + 1.25 - 2, box_max, NumberHistos - ibox + 1.9 - 2);
		cout << "*********empty=" << empty[ibox] << " :  testFailed=" << testFailed[ibox] << endl;
	}
	//----end draw bin-by-bin score
	
	
	// setup the failing test bars
	hg1dResults_failed->SetStats(0);
	hg1dResults_failed->GetXaxis()->SetLabelSize(0.04);
	
	hg1dResults_failed->SetBarWidth(0.7);
	hg1dResults_failed->SetBarOffset(0.1);
	hg1dResults_failed->SetFillColor(kRed);
	hg1dResults_failed->SetLineColor(1);
	hg1dResults_failed->GetYaxis()->SetRangeUser(1E-7,2);
	hg1dResults_failed->Draw("hbar0SAME");
	
	// draw the pass/fail threshold line
	TLine lg(threshold, 1, threshold, NumberHistos+1);
	lg.SetLineColor(kRed);
	lg.SetLineWidth(2);
	lg.SetLineStyle(2);
	lg.Draw("SAME"); 
	
	// print the results
	gmain_c->Update();
	
	//----------------End Draw Summary Histogram--------------------------------------------------//
	
	
}

void simpleDistributionBase::report(int histo_index)
{
	int index=histo_index;
	// report the result of the tests, if performed
	cout<<"==========================================================="<<endl;
	cout<<"============== R E P O R T ================================"<<endl;
	cout<<"==========================================================="<<endl;
	cout << "result is: ";
	if (type == 1) cout << "no determination made";
	else if (testFailed[index]) cout << "fail";
	else if (empty[index]) cout << "no data";
	else cout << "pass";
	float mean = counted_bins > 0 ? running_result / counted_bins : 0;
	cout << ", mean KS score = " << mean << endl;
	
	// set this histograms label in the allResults histo
	h2dResults->GetXaxis()->SetBinLabel(number, name.c_str());
	cout<<"==========================================================="<<endl;
}

void simpleDistributionBase::print_gifs(int type,int bin)
{
	
	if(type==0)
	{
		// print the result to gif
		stringstream histo_name;
		histo_name << name + "dEt_Allbins";
		histo_name << ".gif";
		histo_c1->Print(histo_name.str().c_str(),"gif");
		
		string et_sigma_name = name + "SigmaEtOverEt_vs_et.gif";
		
		sigma_et->Print(et_sigma_name.c_str(),"gif");
		
		string AllResults_name = "AllResults-1dHistoCheck.gif";   
		gmain_c->Print(AllResults_name.c_str(),"gif");
		
	}
	else if(type==1)
	{
		// setup canvas for displaying the compared histograms
		TCanvas histo_c("histo_c","histo_c",785,800);
		histo_c.Draw();
		
		TPad histo_p("histo_p","histo_p",0.01,0.01,0.99,0.94);
		histo_p.Draw();
		
		histo_c.cd();
		canvas_title->SetTextSize(0.025);
		canvas_title->Draw();
		
		histo_p.cd();
		hdumb->Draw();
		histo_p.SetLogy(1);
		href->Draw("SAME");
		hnew->Draw("SAME");
		hnew->Draw("E1SAME");
		
		
		//href->Draw();
		//gfitref->Draw("SAME");
		//hnew->Draw("SAME");
		//gfitnew->Draw("SAME");
		//hnew->Draw("E1SAME");
		
		TLegend l1(0.15,0.01,0.3, 0.08);
		l1.AddEntry(hnew,"New","lF");
		l1.AddEntry(href,"Reference","lF");
		l1.SetFillColor(kNone);
		l1.Draw("SAME");
		
		// print the result to gif
		stringstream histo_name;
		histo_name <<"DeltaEtavsEta/"<< name << "Compare_etBin";
		if (bin < 10) histo_name << "000";
		else if (bin < 100) histo_name << "00";
		else if (bin < 1000) histo_name << "0";
		histo_name << bin << ".gif";
		histo_c.Print(histo_name.str().c_str(),"gif");
	}
}