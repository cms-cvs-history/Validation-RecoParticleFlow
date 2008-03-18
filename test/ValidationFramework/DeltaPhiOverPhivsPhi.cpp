/*
 *  DeltaPhiOverPhivsPhi.cpp
 *  ValidationFramework
 *
 *  Created by Thomas Punz on 17.03.08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "DeltaPhiOverPhivsPhi.h"


#include "vsBase.h"
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

DeltaPhiOverPhivsPhi::DeltaPhiOverPhivsPhi(PlotCompareUtility *pc)
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

DeltaPhiOverPhivsPhi::~DeltaPhiOverPhivsPhi()
{
	
}



void DeltaPhiOverPhivsPhi::histo_conf(int type)
{
	if(type==1)
	{
		href->GetXaxis()->SetTitle("Phi");
		href->GetYaxis()->SetTitle("Events");
		href->GetYaxis()->SetTitleOffset(1.5);
		
		hnew->GetXaxis()->SetTitle("Phi");      
		//	href->GetYaxis()->SetTitle("Events");
		
		h1dResults_passed->GetXaxis()->SetTitle("Phi");
		h1dResults_passed->GetYaxis()->SetTitle("Compatibility");
		
		hg1dResults_passed->GetYaxis()->SetTitle("Compatibility");
		hg1dResults_failed->GetYaxis()->SetTitle("Compatibility");
		
		hrefSigmaETOverETvsETsigma->GetXaxis()->SetTitle("Phi");
		hrefSigmaETOverETvsETsigma->GetYaxis()->SetTitle("#sigma(#DeltaPhi/Phi)/Phi");
		
		
		
		
		
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
		hdumb->GetXaxis()->SetTitle("Phi");
		
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



void DeltaPhiOverPhivsPhi::print_gifs(int type,int bin)
{
	
	if(type==0)
	{
		// print the result to gif
		stringstream histo_name;
		histo_name << name + "dPhi_Allbins";
		histo_name << ".gif";
		histo_c1->Print(histo_name.str().c_str(),"gif");
		
		string et_sigma_name = name + "SigmaDeltaPhiOverPhi_vs_Phi.gif";
		
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
		histo_name <<"DeltaPhiOverPhivsPhi/"<< name << "Compare_etBin";
		if (bin < 10) histo_name << "000";
		else if (bin < 100) histo_name << "00";
		else if (bin < 1000) histo_name << "0";
		histo_name << bin << ".gif";
		histo_c.Print(histo_name.str().c_str(),"gif");
	}
}