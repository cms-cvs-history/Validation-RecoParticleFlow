#include <string>

#include <TFile.h>
#include <TStyle.h>
#include <TObject.h>
#include <iostream>

#include "HistoData.h"
#include "TDRStyle.h"
#include "PlotCompareUtility.h"

using namespace std;

#define DEFAULT_KS_THRESHOLD 1e-6
#define DEFAULT_CHI2_THRESHOLD 1e-6

PlotCompareUtility::PlotCompareUtility(string Reference, string New, string DataPath, string Prefix)
{
	ref_file = new TFile(Reference.c_str());
	
	// check the reference file
	//if (ref_file == 0x0) status += 1L << 1;
	if (ref_file == 0) cout << ref_file << " = " << 0 << endl;
	if (ref_file->Get(DataPath.c_str()) == NULL) status += 1L << 2;
	
	new_file = new TFile(New.c_str());
	
	// check the new validation file
	//if (new_file == NULL) status += 1L << 3;
	if (new_file == 0)  cout << new_file << " = " << 0 << endl;
	if (new_file->Get(DataPath.c_str()) == NULL) status += 1L << 4;
	
	// set the current style to the tdr standard
	style = tdrstyle();
	style.cd();
	
	// set the thresholds to their default values
	ks_threshold = DEFAULT_KS_THRESHOLD;
	chi2_threshold = DEFAULT_CHI2_THRESHOLD;
	
	// set the data path and prefix
	base_path = DataPath;
	prefix = Prefix;
	
}

PlotCompareUtility::~PlotCompareUtility() {

  // check, close, and delete the reference file
  if (ref_file != NULL) {
    ref_file->Close();
    delete ref_file;
  }

  // check, close, and delete the validation file
  if (new_file != NULL) {
    new_file->Close();
    delete new_file;
  }

  // check and delete the HistoData objects
  for (unsigned int i = 0; i < histo_d.size(); i++)
    if (histo_d[i] != NULL) delete histo_d[i];
  histo_d.clear();

}

int PlotCompareUtility::GetNumHistos() {

  return histo_d.size();

}

HistoData *PlotCompareUtility::AddHistoData(string Name) {

  // make sure the histogram data does not already exist
  HistoData *hd;
  for (unsigned int i = 0; i < histo_d.size(); i++) {
    hd = histo_d[i];
    if (hd->GetName() == Name) { status += 1L << 5; return hd; }
  }

  // add the histogram data and return it's address for access
  hd = new HistoData(Name,histo_d.size() + 1);
  if (hd == NULL) { status += 1L << 6; return hd; }

  // verify that the histogram exists in both of the TFiles 
  if (GetNewHisto(Name) == NULL) status += 1L << 7;
  if (GetRefHisto(Name) == NULL) status += 1L << 8;

  histo_d.push_back(hd);
  return hd;

}


HistoData *PlotCompareUtility::GetHistoData(string Name) {

  // make sure the HistoData is found
  HistoData *hd;
  for (unsigned int i = 0; i < histo_d.size(); i++) {
    hd = histo_d[i];
    if (hd->GetName() == Name) return hd;
  }

  status += 1L << 9;
  return NULL;

}

HistoData *PlotCompareUtility::GetHistoData(int Number) {

  // make sure it is a valid number
  int index = Number - 1;
  if (Number < 0 || (unsigned int)Number > histo_d.size()) {
    status += 1L << 10;
    return NULL;
  }

  return histo_d[index];

}

TObject *PlotCompareUtility::GetNewHisto(string Name) {

  string path = base_path + "/" + prefix + Name;
  return new_file->Get(path.c_str());

}

TObject *PlotCompareUtility::GetRefHisto(string Name) {

  string path = base_path + "/" + prefix + Name;
  return ref_file->Get(path.c_str());

}
