/*
 *  Validator.cpp
 *  ValidationFramework
 *
 *  Created by Thomas Punz on 26.02.08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */


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


#include "PlotCompareUtility.h"
#include "HistoData.h"
#include "ValidationTools.h"

#include "Validator.h"
#include "myMath.h"
#include "StatusMonitor.h"
#include <string.h>

#include "DeltaETvsET.h"
#include "DeltaPHIvsPHI.h"
#include "DeltaEtvsPhi.h"
#include "DeltaEtavsEta.h"
#include "DeltaPhivsEta.h"
#include "DeltaETOverEtvsPhi.h"
#include "DeltaEtaOverEtavsPhi.h"
#include "DeltaEtvsDeltaR.h"
#include "DeltaPhivsEt.h"
#include "DeltaRvsEt.h"
#include "DeltaEtOverEtvsDeltaR.h"
#include "DeltaPhiOverPhivsEt.h"
#include "DeltaRvsEta.h"
#include "DeltaEtavsEt.h"
#include "DeltaEtOverEtvsEt.h"
#include "DeltaEtaOverEtavsEt.h"
#include "DeltaEtvsEta.h"
#include "DeltaPhiOverPhivsEta.h"
#include "DeltaRvsPhi.h"
#include "DeltaEtOverEtvsEta.h"
#include "DeltaEtaOverEtavsEta.h"
#include "DeltaEtavsPhi.h"
#include "DeltaPhiOverPhivsPhi.h"


using namespace std;



validator::validator(string new_file, string ref_file)
{
	//create StatusMonitor
	sm=new statusMonitor();
	
	// create the comparison class
	//pc = new PlotCompareUtility(ref_file, new_file,"DQMData/PFTask/Benchmarks/ParticleFlow/Reco","");
	pc = new PlotCompareUtility(ref_file, new_file,"DQMData/PFTask/Benchmarks/PFlowJets/Reco","");
	
	if (pc->GetStatus() != 0)
	{
		sm->report_error(1);	
	}

	// add histogram information
	
	hd = pc->AddHistoData("DeltaEtvsEt"); hd->SetType(2); hd->SetValueX("Et (GeV)");              // 0
	hd = pc->AddHistoData("DeltaPhivsPhi"); hd->SetType(2); hd->SetValueX("Phi (deg)");          // 1
	hd = pc->AddHistoData("DeltaEtavsEta"); hd->SetType(2); hd->SetValueX("Eta");                 //2
	hd = pc->AddHistoData("DeltaEtvsPhi"); hd->SetType(2); hd->SetValueX("Phi (deg)");            //3
	hd = pc->AddHistoData("DeltaPhivsEta"); hd->SetType(2); hd->SetValueX("Eta");                //4
	hd = pc->AddHistoData("DeltaEtOverEtvsPhi"); hd->SetType(2); hd->SetValueX("Phi (deg)");       //5
	hd = pc->AddHistoData("DeltaEtaOverEtavsPhi"); hd->SetType(2); hd->SetValueX("Phi (deg)");    //6
	hd = pc->AddHistoData("DeltaEtvsDeltaR"); hd->SetType(2); hd->SetValueX("Delta R");            //7
	hd = pc->AddHistoData("DeltaRvsEt"); hd->SetType(2); hd->SetValueX("Et (GeV)");                //8
	hd = pc->AddHistoData("DeltaEtOverEtvsDeltaR"); hd->SetType(2); hd->SetValueX("Delta R");        //9
	hd = pc->AddHistoData("DeltaEtavsEt"); hd->SetType(2); hd->SetValueX("Et (GeV)");               //10
	hd = pc->AddHistoData("DeltaPhiOverPhivsEt"); hd->SetType(2); hd->SetValueX("Et (GeV)");         //11
	hd = pc->AddHistoData("DeltaRvsEta"); hd->SetType(2); hd->SetValueX("Eta");                     //12
	hd = pc->AddHistoData("DeltaEtOverEtvsEt"); hd->SetType(2); hd->SetValueX("Et (GeV)");           //13
	hd = pc->AddHistoData("DeltaEtaOverEtavsEt"); hd->SetType(2); hd->SetValueX("Et (GeV)");         //14
	hd = pc->AddHistoData("DeltaEtvsEta"); hd->SetType(2); hd->SetValueX("Eta");                      //15
	hd = pc->AddHistoData("DeltaPhiOverPhivsEta"); hd->SetType(2); hd->SetValueX("Eta");               //16
	hd = pc->AddHistoData("DeltaRvsPhi"); hd->SetType(2); hd->SetValueX("Phi (deg)");                  //17
	hd = pc->AddHistoData("DeltaEtOverEtvsEta"); hd->SetType(2); hd->SetValueX("Eta");                 //18
	hd = pc->AddHistoData("DeltaEtaOverEtavsEta"); hd->SetType(2); hd->SetValueX("Eta");               //19
	hd = pc->AddHistoData("DeltaEtavsPhi"); hd->SetType(2); hd->SetValueX("Phi (deg)");                 //20
	hd = pc->AddHistoData("DeltaPhiOverPhivsPhi"); hd->SetType(2); hd->SetValueX("Phi (deg)");           //21
	
	
	if (pc->GetStatus() != 0) 
	{
			sm->report_error(2);
	}


	deltaETvsEt=new DeltaETvsET(pc);
	deltaPHIvsPhi=new DeltaPHIvsPHI(pc);
	deltaEtvsPhi=new DeltaEtvsPhi(pc);
	deltaPhivsEta=new DeltaPhivsEta(pc);
	deltaEtavsEta=new DeltaEtavsEta(pc);
	deltaEtOverEtvsPhi=new DeltaETOverEtvsPhi(pc);
	deltaEtaOverEtavsPhi=new  DeltaEtaOverEtavsPhi(pc); 
	deltaEtvsDeltaR =new	DeltaEtvsDeltaR(pc);
	deltaRvsEt=new DeltaRvsEt(pc);
	deltaEtOverEtvsDeltaR=new  DeltaEtOverEtvsDeltaR(pc);
	deltaEtavsEt=new  DeltaEtavsEt(pc);
	deltaPhiOverPhivsEt=new DeltaPhiOverPhivsEt(pc);
	deltaRvsEta=new  DeltaRvsEta(pc);
	deltaEtOverEtvsEt =new DeltaEtOverEtvsEt(pc);
	deltaEtaOverEtavsEt=new  DeltaEtaOverEtavsEt(pc);
	deltaEtvsEta=new  DeltaEtvsEta(pc);
	deltaPhiOverPhivsEta=new  DeltaPhiOverPhivsEta(pc);
	deltaRvsPhi=new DeltaRvsPhi(pc);
	deltaEtOverEtvsEta=new DeltaEtOverEtvsEta(pc);
	deltaEtaOverEtavsEta=new DeltaEtaOverEtavsEta(pc);
	deltaEtavsPhi=new DeltaEtavsPhi(pc);
	deltaPhiOverPhivsPhi=new DeltaPhiOverPhivsPhi(pc);
	
	
	histo_Loop();
}

validator::~validator()
{
	
}



void validator::histo_Loop()
{
//	for (int index = 0; index < pc->GetNumHistos(); index++)
	for (int index = 0; index < 22; index++)
	{
		if(index==0)
		{
			deltaETvsEt->fetch_histos(index);
			running_result = 0;
			counted_bins = 0;
			//for (int bin = 1; bin <= num_et_bins; bin++)
			//{
			for (int bin = 1; bin <= 100; bin++)
			{
				cout<<"Bin: "<<bin<<endl;
				deltaETvsEt->loop_over_et_bins(index,bin);
			}
			
			deltaETvsEt->draw_score_vs_ET(index);
			deltaETvsEt->report(index);
			deltaETvsEt->draw_test_plot_and_delta_et();
			deltaETvsEt->draw_test_plot_sigma_ET_vs_ET();
			deltaETvsEt->draw_summary();
			deltaETvsEt->report(index);
			deltaETvsEt->print_gifs(0,0);
		}
		else if(index==1)
		{
			deltaPHIvsPhi->fetch_histos(index);
			running_result = 0;
			counted_bins = 0;
		//	for (int bin = 1; bin <= num_et_bins; bin++)
		//	{
			for (int bin = 1; bin <= 100; bin++)
			{
				cout<<"Bin: "<<bin<<endl;
				deltaPHIvsPhi->loop_over_et_bins(index,bin);
			}
			
			deltaPHIvsPhi->draw_score_vs_ET(index);
			deltaPHIvsPhi->report(index);
			deltaPHIvsPhi->draw_test_plot_and_delta_et();
			deltaPHIvsPhi->draw_test_plot_sigma_ET_vs_ET();
			deltaPHIvsPhi->draw_summary();
			deltaPHIvsPhi->report(index);
			deltaPHIvsPhi->print_gifs(0,0);
		}
		
		else if(index==2)
		{
			deltaEtavsEta->fetch_histos(index);
			running_result = 0;
			counted_bins = 0;
			//for (int bin = 1; bin <= num_et_bins; bin++)
			//{
			for (int bin = 1; bin <= 100; bin++)
			{
				cout<<"Bin: "<<bin<<endl;
				deltaEtavsEta->loop_over_et_bins(index,bin);
			}
			
			deltaEtavsEta->draw_score_vs_ET(index);
			deltaEtavsEta->report(index);
			deltaEtavsEta->draw_test_plot_and_delta_et();
			deltaEtavsEta->draw_test_plot_sigma_ET_vs_ET();
			deltaEtavsEta->draw_summary();
			deltaEtavsEta->report(index);
			deltaEtavsEta->print_gifs(0,0);
		}
		
		else if(index==3)
		{
			deltaEtvsPhi->fetch_histos(index);
			running_result = 0;
			counted_bins = 0;
			//for (int bin = 1; bin <= num_et_bins; bin++)
			//{
			for (int bin = 1; bin <= 100; bin++)
			{
				cout<<"Bin: "<<bin<<endl;
				deltaEtvsPhi->loop_over_et_bins(index,bin);
			}
			
			deltaEtvsPhi->draw_score_vs_ET(index);
			deltaEtvsPhi->report(index);
			deltaEtvsPhi->draw_test_plot_and_delta_et();
			deltaEtvsPhi->draw_test_plot_sigma_ET_vs_ET();
			deltaEtvsPhi->draw_summary();
			deltaEtvsPhi->report(index);
			deltaEtvsPhi->print_gifs(0,0);
		}
		
		else if(index==4)
		{
			deltaPhivsEta->fetch_histos(index);
			running_result = 0;
			counted_bins = 0;
		//	for (int bin = 1; bin <= num_et_bins; bin++)
	//		{
			for (int bin = 1; bin <= 100; bin++)
			{
				cout<<"Bin: "<<bin<<endl;
				deltaPhivsEta->loop_over_et_bins(index,bin);
			}
			
			deltaPhivsEta->draw_score_vs_ET(index);
			deltaPhivsEta->report(index);
			deltaPhivsEta->draw_test_plot_and_delta_et();
			deltaPhivsEta->draw_test_plot_sigma_ET_vs_ET();
			deltaPhivsEta->draw_summary();
			deltaPhivsEta->report(index);
			deltaPhivsEta->print_gifs(0,0);
		}
			
		else if(index==5)
		{
			deltaEtOverEtvsPhi->fetch_histos(index);
			running_result = 0;
			counted_bins = 0;
			//	for (int bin = 1; bin <= num_et_bins; bin++)
			//		{
			for (int bin = 1; bin <= 100; bin++)
			{
				cout<<"Bin: "<<bin<<endl;
				deltaEtOverEtvsPhi->loop_over_et_bins(index,bin);
			}
			
			deltaEtOverEtvsPhi->draw_score_vs_ET(index);
			deltaEtOverEtvsPhi->report(index);
			deltaEtOverEtvsPhi->draw_test_plot_and_delta_et();
			deltaEtOverEtvsPhi->draw_test_plot_sigma_ET_vs_ET();
			deltaEtOverEtvsPhi->draw_summary();
			deltaEtOverEtvsPhi->report(index);
			deltaEtOverEtvsPhi->print_gifs(0,0);
		}
		
		else if(index==6)
		{
			deltaEtaOverEtavsPhi->fetch_histos(index);
			running_result = 0;
			counted_bins = 0;
			//	for (int bin = 1; bin <= num_et_bins; bin++)
			//		{
			for (int bin = 1; bin <= 100; bin++)
			{
				cout<<"Bin: "<<bin<<endl;
				deltaEtOverEtvsPhi->loop_over_et_bins(index,bin);
			}
			
			deltaEtOverEtvsPhi->draw_score_vs_ET(index);
			deltaEtOverEtvsPhi->report(index);
			deltaEtOverEtvsPhi->draw_test_plot_and_delta_et();
			deltaEtOverEtvsPhi->draw_test_plot_sigma_ET_vs_ET();
			deltaEtOverEtvsPhi->draw_summary();
			deltaEtOverEtvsPhi->report(index);
			deltaEtOverEtvsPhi->print_gifs(0,0);
		}
		
	
		else if(index==7)
		{
			deltaEtvsDeltaR->fetch_histos(index);
			running_result = 0;
			counted_bins = 0;
			//	for (int bin = 1; bin <= num_et_bins; bin++)
			//		{
			for (int bin = 1; bin <= 100; bin++)
			{
				cout<<"Bin: "<<bin<<endl;
				deltaEtvsDeltaR->loop_over_et_bins(index,bin);
			}
			
			deltaEtvsDeltaR->draw_score_vs_ET(index);
			deltaEtvsDeltaR->report(index);
			deltaEtvsDeltaR->draw_test_plot_and_delta_et();
			deltaEtvsDeltaR->draw_test_plot_sigma_ET_vs_ET();
			deltaEtvsDeltaR->draw_summary();
			deltaEtvsDeltaR->report(index);
			deltaEtvsDeltaR->print_gifs(0,0);
		}
		
		else if(index==8)
		{
			deltaRvsEt->fetch_histos(index);
			running_result = 0;
			counted_bins = 0;
			//	for (int bin = 1; bin <= num_et_bins; bin++)
			//		{
			for (int bin = 1; bin <= 100; bin++)
			{
				cout<<"Bin: "<<bin<<endl;
				deltaRvsEt->loop_over_et_bins(index,bin);
			}
			
			deltaRvsEt->draw_score_vs_ET(index);
			deltaRvsEt->report(index);
			deltaRvsEt->draw_test_plot_and_delta_et();
			deltaRvsEt->draw_test_plot_sigma_ET_vs_ET();
			deltaRvsEt->draw_summary();
			deltaRvsEt->report(index);
			deltaRvsEt->print_gifs(0,0);
		}
		
		else if(index==9)
		{
			deltaEtOverEtvsDeltaR->fetch_histos(index);
			running_result = 0;
			counted_bins = 0;
			//	for (int bin = 1; bin <= num_et_bins; bin++)
			//		{
			for (int bin = 1; bin <= 100; bin++)
			{
				cout<<"Bin: "<<bin<<endl;
				deltaEtOverEtvsDeltaR->loop_over_et_bins(index,bin);
			}
			
			deltaEtOverEtvsDeltaR->draw_score_vs_ET(index);
			deltaEtOverEtvsDeltaR->report(index);
			deltaEtOverEtvsDeltaR->draw_test_plot_and_delta_et();
			deltaEtOverEtvsDeltaR->draw_test_plot_sigma_ET_vs_ET();
			deltaEtOverEtvsDeltaR->draw_summary();
			deltaEtOverEtvsDeltaR->report(index);
			deltaEtOverEtvsDeltaR->print_gifs(0,0);
		}
		
		else if(index==10)
		{
			deltaEtavsEt->fetch_histos(index);
			running_result = 0;
			counted_bins = 0;
			//	for (int bin = 1; bin <= num_et_bins; bin++)
			//		{
			for (int bin = 1; bin <= 100; bin++)
			{
				cout<<"Bin: "<<bin<<endl;
				deltaEtavsEt->loop_over_et_bins(index,bin);
			}
			
			deltaEtavsEt->draw_score_vs_ET(index);
			deltaEtavsEt->report(index);
			deltaEtavsEt->draw_test_plot_and_delta_et();
			deltaEtavsEt->draw_test_plot_sigma_ET_vs_ET();
			deltaEtavsEt->draw_summary();
			deltaEtavsEt->report(index);
			deltaEtavsEt->print_gifs(0,0);
		}
		
		else if(index==11)
		{
			deltaPhiOverPhivsEt->fetch_histos(index);
			running_result = 0;
			counted_bins = 0;
			//	for (int bin = 1; bin <= num_et_bins; bin++)
			//		{
			for (int bin = 1; bin <= 100; bin++)
			{
				cout<<"Bin: "<<bin<<endl;
				deltaPhiOverPhivsEt->loop_over_et_bins(index,bin);
			}
			
			deltaPhiOverPhivsEt->draw_score_vs_ET(index);
			deltaPhiOverPhivsEt->report(index);
			deltaPhiOverPhivsEt->draw_test_plot_and_delta_et();
			deltaPhiOverPhivsEt->draw_test_plot_sigma_ET_vs_ET();
			deltaPhiOverPhivsEt->draw_summary();
			deltaPhiOverPhivsEt->report(index);
			deltaPhiOverPhivsEt->print_gifs(0,0);
		}
		else if(index==12)
		{
			deltaRvsEta->fetch_histos(index);
			running_result = 0;
			counted_bins = 0;
			//	for (int bin = 1; bin <= num_et_bins; bin++)
			//		{
			for (int bin = 1; bin <= 100; bin++)
			{
				cout<<"Bin: "<<bin<<endl;
				deltaRvsEta->loop_over_et_bins(index,bin);
			}
			
			deltaRvsEta->draw_score_vs_ET(index);
			deltaRvsEta->report(index);
			deltaRvsEta->draw_test_plot_and_delta_et();
			deltaRvsEta->draw_test_plot_sigma_ET_vs_ET();
			deltaRvsEta->draw_summary();
			deltaRvsEta->report(index);
			deltaRvsEta->print_gifs(0,0);
		}
		else if(index==13)
		{
			deltaEtOverEtvsEt->fetch_histos(index);
			running_result = 0;
			counted_bins = 0;
			//	for (int bin = 1; bin <= num_et_bins; bin++)
			//		{
			for (int bin = 1; bin <= 100; bin++)
			{
				cout<<"Bin: "<<bin<<endl;
				deltaEtOverEtvsEt->loop_over_et_bins(index,bin);
			}
			
			deltaEtOverEtvsEt->draw_score_vs_ET(index);
			deltaEtOverEtvsEt->report(index);
			deltaEtOverEtvsEt->draw_test_plot_and_delta_et();
			deltaEtOverEtvsEt->draw_test_plot_sigma_ET_vs_ET();
			deltaEtOverEtvsEt->draw_summary();
			deltaEtOverEtvsEt->report(index);
			deltaEtOverEtvsEt->print_gifs(0,0);
		}
		else if(index==14)
		{
			deltaEtaOverEtavsEt->fetch_histos(index);
			running_result = 0;
			counted_bins = 0;
			//	for (int bin = 1; bin <= num_et_bins; bin++)
			//		{
			for (int bin = 1; bin <= 100; bin++)
			{
				cout<<"Bin: "<<bin<<endl;
				deltaEtaOverEtavsEt->loop_over_et_bins(index,bin);
			}
			
			deltaEtaOverEtavsEt->draw_score_vs_ET(index);
			deltaEtaOverEtavsEt->report(index);
			deltaEtaOverEtavsEt->draw_test_plot_and_delta_et();
			deltaEtaOverEtavsEt->draw_test_plot_sigma_ET_vs_ET();
			deltaEtaOverEtavsEt->draw_summary();
			deltaEtaOverEtavsEt->report(index);
			deltaEtaOverEtavsEt->print_gifs(0,0);
		}
		
		else if(index==15)
		{
			deltaEtvsEta->fetch_histos(index);
			running_result = 0;
			counted_bins = 0;
			//	for (int bin = 1; bin <= num_et_bins; bin++)
			//		{
			for (int bin = 1; bin <= 100; bin++)
			{
				cout<<"Bin: "<<bin<<endl;
				deltaEtvsEta->loop_over_et_bins(index,bin);
			}
			
			deltaEtvsEta->draw_score_vs_ET(index);
			deltaEtvsEta->report(index);
			deltaEtvsEta->draw_test_plot_and_delta_et();
			deltaEtvsEta->draw_test_plot_sigma_ET_vs_ET();
			deltaEtvsEta->draw_summary();
			deltaEtvsEta->report(index);
			deltaEtvsEta->print_gifs(0,0);
		}
		
		else if(index==16)
		{
			deltaPhiOverPhivsEta->fetch_histos(index);
			running_result = 0;
			counted_bins = 0;
			//	for (int bin = 1; bin <= num_et_bins; bin++)
			//		{
			for (int bin = 1; bin <= 100; bin++)
			{
				cout<<"Bin: "<<bin<<endl;
				deltaPhiOverPhivsEta->loop_over_et_bins(index,bin);
			}
			
			deltaPhiOverPhivsEta->draw_score_vs_ET(index);
			deltaPhiOverPhivsEta->report(index);
			deltaPhiOverPhivsEta->draw_test_plot_and_delta_et();
			deltaPhiOverPhivsEta->draw_test_plot_sigma_ET_vs_ET();
			deltaPhiOverPhivsEta->draw_summary();
			deltaPhiOverPhivsEta->report(index);
			deltaPhiOverPhivsEta->print_gifs(0,0);
		}
		
		else if(index==17)
		{
			if(deltaRvsPhi->fetch_histos(index)!=1)
			{
				running_result = 0;
				counted_bins = 0;
				//	for (int bin = 1; bin <= num_et_bins; bin++)
				//		{
				for (int bin = 1; bin <= 100; bin++)
				{
					cout<<"Bin: "<<bin<<endl;
					deltaRvsPhi->loop_over_et_bins(index,bin);
				}
				
				deltaRvsPhi->draw_score_vs_ET(index);
				deltaRvsPhi->report(index);
				deltaRvsPhi->draw_test_plot_and_delta_et();
				deltaRvsPhi->draw_test_plot_sigma_ET_vs_ET();
				deltaRvsPhi->draw_summary();
				deltaRvsPhi->report(index);
				deltaRvsPhi->print_gifs(0,0);
			}
		}
		
		else if(index==18)
		{
			deltaEtOverEtvsEta->fetch_histos(index);
			running_result = 0;
			counted_bins = 0;
			//	for (int bin = 1; bin <= num_et_bins; bin++)
			//		{
			for (int bin = 1; bin <= 100; bin++)
			{
				cout<<"Bin: "<<bin<<endl;
				deltaEtOverEtvsEta->loop_over_et_bins(index,bin);
			}
			
			deltaEtOverEtvsEta->draw_score_vs_ET(index);
			deltaEtOverEtvsEta->report(index);
			deltaEtOverEtvsEta->draw_test_plot_and_delta_et();
			deltaEtOverEtvsEta->draw_test_plot_sigma_ET_vs_ET();
			deltaEtOverEtvsEta->draw_summary();
			deltaEtOverEtvsEta->report(index);
			deltaEtOverEtvsEta->print_gifs(0,0);
		}
		
				
		else if(index==19)
		{
			deltaEtaOverEtavsEta->fetch_histos(index);
			running_result = 0;
			counted_bins = 0;
			//	for (int bin = 1; bin <= num_et_bins; bin++)
			//		{
			for (int bin = 1; bin <= 100; bin++)
			{
				cout<<"Bin: "<<bin<<endl;
				deltaEtaOverEtavsEta->loop_over_et_bins(index,bin);
			}
			
			deltaEtaOverEtavsEta->draw_score_vs_ET(index);
			deltaEtaOverEtavsEta->report(index);
			deltaEtaOverEtavsEta->draw_test_plot_and_delta_et();
			deltaEtaOverEtavsEta->draw_test_plot_sigma_ET_vs_ET();
			deltaEtaOverEtavsEta->draw_summary();
			deltaEtaOverEtavsEta->report(index);
			deltaEtaOverEtavsEta->print_gifs(0,0);
		}
		
		else if(index==20)
		{
			deltaEtavsPhi->fetch_histos(index);
			running_result = 0;
			counted_bins = 0;
			//	for (int bin = 1; bin <= num_et_bins; bin++)
			//		{
			for (int bin = 1; bin <= 100; bin++)
			{
				cout<<"Bin: "<<bin<<endl;
				deltaEtavsPhi->loop_over_et_bins(index,bin);
			}
			
			deltaEtavsPhi->draw_score_vs_ET(index);
			deltaEtavsPhi->report(index);
			deltaEtavsPhi->draw_test_plot_and_delta_et();
			deltaEtavsPhi->draw_test_plot_sigma_ET_vs_ET();
			deltaEtavsPhi->draw_summary();
			deltaEtavsPhi->report(index);
			deltaEtavsPhi->print_gifs(0,0);
		}
		else if(index==21)
		{
			deltaPhiOverPhivsPhi->fetch_histos(index);
			running_result = 0;
			counted_bins = 0;
			//	for (int bin = 1; bin <= num_et_bins; bin++)
			//		{
			for (int bin = 1; bin <= 100; bin++)
			{
				cout<<"Bin: "<<bin<<endl;
				deltaPhiOverPhivsPhi->loop_over_et_bins(index,bin);
			}
			
			deltaPhiOverPhivsPhi->draw_score_vs_ET(index);
			deltaPhiOverPhivsPhi->report(index);
			deltaPhiOverPhivsPhi->draw_test_plot_and_delta_et();
			deltaPhiOverPhivsPhi->draw_test_plot_sigma_ET_vs_ET();
			deltaPhiOverPhivsPhi->draw_summary();
			deltaPhiOverPhivsPhi->report(index);
			deltaPhiOverPhivsPhi->print_gifs(0,0);
		}
		
	}
}











