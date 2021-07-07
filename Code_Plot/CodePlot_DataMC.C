#include <stdio.h>
#include <iostream>

#include "TError.h"

#include "Plugin/fileBrowser.h"
#include "Plugin/Tool_Utilities.h"
#include "Plugin/Tool_Computing.h"
#include "Plugin/Tool_PlottingStyle.h"

#ifndef CODEPLOT_DATAMC
#define CODEPLOT_DATAMC


//=================
// * Colour & style
//=================
// + Data
//-------
int colour_data = kBlack;


// + MC
//-----
// * DY visible
int colour_DYVis = kPink+7;
int colour_DYinv = kPink-6;

// * Massive boson(s)
int colour_1BosEWK = kSpring+4;
int colour_2Bos    = kSpring+5;
int colour_3Bos    = kSpring+6;

// * Boson+jets
int colour_GJets = kOrange-2;
int colour_WJets = kOrange-5;

// * W+gamma+jets
int colour_WGJets = kAzure+2;

// * Z + gamma
int colour_Z2lepG = kTeal-8;
int colour_Z2nuG  = kTeal-7;

// * Top jets
int colour_TGJets  = kViolet+1;
int colour_TTGJets = kViolet+2;

// * QCD background
int colour_QCDJets = kCyan;

// * Signal
int colour_signal = kOrange+7;





//=================
// + Get the colour
//=================
vector<int>   Get_Colour (vector<TString> &vec_string)
{
	vector<int>   vec_colour;
	vec_colour . clear();
	
	for (int i=0; i<vec_string.size(); i++)
	{
		if (vec_string[i] == "01.Z(ll)")                vec_colour . push_back (colour_DYVis);
		if (vec_string[i] == "02.Z(#nu#nu)")            vec_colour . push_back (colour_DYinv);
		if (vec_string[i] == "03.Monoboson EWK")        vec_colour . push_back (colour_1BosEWK);
		if (vec_string[i] == "04.#gamma+Jets")          vec_colour . push_back (colour_GJets);
		if (vec_string[i] == "05.W+Jets")               vec_colour . push_back (colour_WJets);
		if (vec_string[i] == "06.Diboson")              vec_colour . push_back (colour_2Bos);
		if (vec_string[i] == "07.W#gamma+Jets")         vec_colour . push_back (colour_WGJets);
		if (vec_string[i] == "08.Z(ll)#gamma")          vec_colour . push_back (colour_Z2lepG);
		if (vec_string[i] == "09.Z(#nu#nu)#gamma")      vec_colour . push_back (colour_Z2nuG);
		if (vec_string[i] == "10.Triboson")             vec_colour . push_back (colour_3Bos);
		if (vec_string[i] == "11.t#gamma+Jets")         vec_colour . push_back (colour_TGJets);
		if (vec_string[i] == "12.t#bar{t}#gamma+Jets")  vec_colour . push_back (colour_TTGJets);
		if (vec_string[i] == "13.QCD Bkg")              vec_colour . push_back (colour_QCDJets);
		if (vec_string[i] == "14.Signal")               vec_colour . push_back (colour_signal);
	}
	
	return vec_colour;
}





//=================
// + Get group name
//=================
TString   Get_GroupName (TString name_dataset)
{
	TString name_group = name_dataset;
	
	if (name_dataset == "DYJets")      name_group = ("01.Z(ll)");
	if (name_dataset == "DYJetsInv")   name_group = ("02.Z(#nu#nu)");
	if (name_dataset == "WmEWK")       name_group = ("03.Monoboson EWK");
	if (name_dataset == "WpEWK")       name_group = ("03.Monoboson EWK");
	if (name_dataset == "Z2lepEWK")    name_group = ("03.Monoboson EWK");
	if (name_dataset == "Z2nuEWK")     name_group = ("03.Monoboson EWK");
	if (name_dataset == "GJets")       name_group = ("04.#gamma+Jets");
	if (name_dataset == "WJetsToLNu")  name_group = ("05.W+Jets");
	if (name_dataset == "WW")          name_group = ("06.Diboson");
	if (name_dataset == "WZ")          name_group = ("06.Diboson");
	if (name_dataset == "ZZ")          name_group = ("06.Diboson");
	if (name_dataset == "WGJets")      name_group = ("07.W#gamma+Jets");
	if (name_dataset == "Z2lepG")      name_group = ("08.Z(ll)#gamma");
	if (name_dataset == "Z2nuG")       name_group = ("09.Z(#nu#nu)#gamma");
	if (name_dataset == "WWG")         name_group = ("10.Triboson");
	if (name_dataset == "WZG")         name_group = ("10.Triboson");
	if (name_dataset == "TGJets")      name_group = ("11.t#gamma+Jets");
	if (name_dataset == "TTGJets")     name_group = ("12.t#bar{t}#gamma+Jets");
	if (name_dataset == "QCD")         name_group = ("13.QCD Bkg");
	if (name_dataset == "Z2nuGEWK")    name_group = ("14.Signal");
	
	return name_group;
}





//=================
// + Get the legend
//=================
vector<TString>   Get_Legend (vector<TString> &vec_string)
{
	vector<TString>   vec_legend;
	vec_legend . clear();
	
	for (int i=0; i<vec_string.size(); i++)
	{
		if (vec_string[i] == "01.Z(ll)")                vec_legend . push_back ("Z(ll)");
		if (vec_string[i] == "02.Z(#nu#nu)")            vec_legend . push_back ("Z(#nu#nu)");
		if (vec_string[i] == "03.Monoboson EWK")        vec_legend . push_back ("Monoboson EWK");
		if (vec_string[i] == "04.#gamma+Jets")          vec_legend . push_back ("#gamma+Jets");
		if (vec_string[i] == "05.W+Jets")               vec_legend . push_back ("W+Jets");
		if (vec_string[i] == "06.Diboson")              vec_legend . push_back ("Diboson");
		if (vec_string[i] == "07.W#gamma+Jets")         vec_legend . push_back ("W#gamma+Jets");
		if (vec_string[i] == "08.Z(ll)#gamma")          vec_legend . push_back ("Z(ll)#gamma");
		if (vec_string[i] == "09.Z(#nu#nu)#gamma")      vec_legend . push_back ("Z(#nu#nu)#gamma");
		if (vec_string[i] == "10.Triboson")             vec_legend . push_back ("Triboson");
		if (vec_string[i] == "11.t#gamma+Jets")         vec_legend . push_back ("t#gamma+Jets");
		if (vec_string[i] == "12.t#bar{t}#gamma+Jets")  vec_legend . push_back ("t#bar{t}#gamma+Jets");
		if (vec_string[i] == "13.QCD Bkg")              vec_legend . push_back ("QCD Bkg");
		if (vec_string[i] == "14.Signal")               vec_legend . push_back ("Signal");
	}
	
	return vec_legend;
}





//===============
// * Main program
//===============
void CodePlot_DataMC (int year,   bool setLogY,   int tightness,   int corMETVer,   int cutScenario)
{
	TH1::AddDirectory(kFALSE);
	gErrorIgnoreLevel = kError, kBreak, kSysError, kFatal;
	
	
	
	// + List of scenario
	//-------------------
	TString prefixTightness[4] = {"Loose", "Medium", "Tight", "Lead2jets"};
	TString prefixUseCorMET[3] = {"Org", "Mix", "Cor"};
	
	TString strAdvancedCut[2] =
	{
		Form ("VBS_%s_%sMET_Default",   prefixTightness[tightness].Data(), prefixUseCorMET[corMETVer].Data()),
		Form ("VBS_%s_%sMET_CutAllBtB", prefixTightness[tightness].Data(), prefixUseCorMET[corMETVer].Data())
	};
	
	printf ("    Creating output directory: %s ...\n", Form("/home/hoa/Task_ZgVBS/Output/Plot_DataMC/%s/", strAdvancedCut[cutScenario].Data()));
	system (Form("mkdir -p /home/hoa/Task_ZgVBS/Output/Plot_DataMC/%s/", strAdvancedCut[cutScenario].Data()));
	
	gStyle -> SetOptStat (0);
	
	
	
	// + Get list of files from data
	//------------------------------
	vector<TString>  vec_nameFileinDT;
	vec_nameFileinDT . clear();
	
	printf ("    Getting input for data from: %s ...\n", Form("/home/hoa/Task_ZgVBS/Output/Hist_selDT/%s/", strAdvancedCut[cutScenario].Data()));
	TString strDirInputDT  = Form("/home/hoa/Task_ZgVBS/Output/Hist_selDT/%s/", strAdvancedCut[cutScenario].Data());
	
	string dir_inputDT = strDirInputDT.Data();
	vector<string> list_fileDT = fileBrowser (dir_inputDT, string("root"));
	
	for (unsigned int i=0; i<list_fileDT.size(); i++)
	{
		TString name_file = list_fileDT[i];
		if (!name_file . Contains (Form("hist%d",year-2000)))   continue;
		
		vec_nameFileinDT . push_back (name_file);
	}
	
	printf ("    [*] Found %zu data input:\n", vec_nameFileinDT.size());
	
	for (int i=0; i<vec_nameFileinDT.size(); i++)
	{
		printf ("     |-->-- %s\n", vec_nameFileinDT[i].Data());
	}
	
	printf ("\n");
	
	
	
	// + Get list of files from MC
	//----------------------------
	printf ("    Getting input for MC from: %s ...\n", Form("/home/hoa/Task_ZgVBS/Output/Hist_selMC/%s/", strAdvancedCut[cutScenario].Data()));
	vector<TString>  vec_nameProcess;
	vec_nameProcess . clear();
	vector<TString>  vec_nameDataset;
	vec_nameDataset . clear();
	vector<TString>  vec_nameIndir;
	vec_nameIndir . clear();
	
	vector<vector<TString>>  vec_nameFileinMC;
	vec_nameFileinMC . clear();
	
	TString strDirInputMC  = Form("/home/hoa/Task_ZgVBS/Output/Hist_selMC/%s/", strAdvancedCut[cutScenario].Data());
	string dir_inputMC = strDirInputMC.Data();
	
	vector<string> list_fileMC = fileBrowser (dir_inputMC, string("root"));
	
	// * Get list of datasets and file
	for (unsigned int i=0; i<list_fileMC.size(); i++)
	{
		// * Check for the valid file
		TString name_file = list_fileMC[i];
		name_file = name_file . ReplaceAll (strDirInputMC, "");
		if (!name_file . Contains (Form("hist%d",year-2000)))   continue;
		
		// * Save files' names
		vec_nameIndir . push_back(name_file);
		
		// * Save datasets' names
		name_file . ReplaceAll (".root", "");
		TObjArray *arr_splitStr = name_file . Tokenize ("_");
		
		TString str_split = ((TObjString*)(arr_splitStr->At(1)))->String();
		TString name_group = Get_GroupName (str_split);
		
		vec_nameDataset . push_back (name_group);
	}
	
	// * Get list of interactions
	for (unsigned int i=0; i<vec_nameDataset.size(); i++)
	{
		bool isNotAvail = true;
		
		for (unsigned int j=0; j<vec_nameProcess.size(); j++)
		{
			if (vec_nameDataset[i]==vec_nameProcess[j])
			{
				isNotAvail = false;
				break;
			}
		}
		
		if (isNotAvail)
		{
			vec_nameProcess . push_back (vec_nameDataset[i]);
		}
	}
	
	std::sort (vec_nameProcess.begin(), vec_nameProcess.end());
	
	// * Get list of full path for each interaction
	vector<TString>::iterator iset;
	
	for (int i=0; i<vec_nameProcess.size(); i++)
	{
		vector<TString>  vec_tmp;
		vec_tmp . clear();
		
		for (iset=vec_nameIndir.begin(); iset!=vec_nameIndir.end(); iset++)
		{
			TString name_tmp = Form("%s", iset->Data());
			TObjArray *name_split = name_tmp . Tokenize("_.");
			TString name_sample = ((TObjString*)(name_split->At(1)))->String();
			TString name_group = Get_GroupName (name_sample);
			
			if (name_group == vec_nameProcess[i])
			{
				TString path_full = Form ("%s%s", strDirInputMC.Data(), iset->Data());
				vec_tmp . push_back (path_full);
				
				vec_nameIndir . erase (iset);
				iset --;
			}
		}
		
		vec_nameFileinMC . push_back (vec_tmp);
	}
	
	printf ("    [*] Found %zu MC sample input:\n", vec_nameFileinMC.size());
	for (int i=0; i<vec_nameFileinMC.size(); i++)
	{
		printf ("     |-- Sample %s has:\n", vec_nameProcess[i].Data());
		for (int j=0; j<vec_nameFileinMC[i].size(); j++)
		{
			printf ("     |-->-- %s\n", vec_nameFileinMC[i][j].Data());
		}
	}
	printf ("\n");
	
	
	
	// + List of histogram name
	//-------------------------
	vector<TString>  vec_nameHist;
	vec_nameHist . clear();
	vector<TString>  vec_nameXaxis;
	vec_nameXaxis . clear();
	vector<TString>  vec_nameFileout;
	vec_nameFileout . clear();
	
	// * Get list of names of histograms
	TFile *file_tmpDT = new TFile (vec_nameFileinDT[0].Data(), "read");
	printf ("    Getting list of histograms from first data input ...\n");
	
	unsigned int nVar = GetInfo_Histograms (file_tmpDT, vec_nameHist, vec_nameFileout, vec_nameXaxis);
	
	printf ("    [*] Done reading, there are %03d histograms:\n", nVar);
	for (int i=0; i<vec_nameHist.size(); i++)
	{
		printf ("     |-->-- %2d) Histogram: %s\n", i+1, vec_nameHist[i].Data());
		//printf ("                 Variables: %s\n", vec_nameXaxis[i].Data());
		//printf ("                 Output:    %s\n", vec_nameFileout[i].Data());
	}
	printf ("\n");
	
	file_tmpDT -> Close();
	
	
	
	printf ("    Looping over all variable ...\n");
	// + Run over the variables, make the plots
	//-----------------------------------------
	for (int plotID=0; plotID<nVar; plotID++)
	{
		// + Declare all types of variables
		//---------------------------------
		printf ("    [*] Variable number %02d\n", plotID+1);
		// * Declare histogram
		TH1F *hist_allDT;
		TH1F *hist_allMC;
		TH1F *hist_MCSignal;
		vector<TH1F*> vec_histMC;
		vec_histMC . clear();
		TH1F *hist_ratio;
		
		
		
		// + Fill the histograms
		//----------------------
		// * Data
		Double_t nEventDT = 0;
		
		printf ("     |-- Getting histograms for data ...\n");
		for (int i=0; i<vec_nameFileinDT.size(); i++)
		{
			Double_t tmpEventDT;
			//printf ("     |-->-- Getting: <%s>  from: %s\n", vec_nameHist[plotID].Data(), vec_nameFileinDT[i].Data());
			
			TFile *file = new TFile (vec_nameFileinDT[i].Data(), "read");
			//printf ("     |-->-->-- File opened\n");
			TH1F *hist = (TH1F*)file -> Get (vec_nameHist[plotID]);
			//printf ("     |-->-->-- Got <%s> with integral = %.3f\n", hist->GetName(), hist->Integral());
			
			TTree *tree = (TTree*)file -> Get ("tree_Global");
			tree -> SetBranchAddress ("nEventNormVBS",  &tmpEventDT);
			//printf ("     |-->-->-- Tree initiated\n");
			tree -> GetEvent (0);
			nEventDT += tmpEventDT;
			
			if (i == 0)
			{
				//printf ("     |-->-->-- Cloning <%s> ...\n", histclone->GetName());
				hist_allDT = (TH1F*)hist -> Clone();
				//printf ("     |-->-->-- Histogram is cloned ...\n");
			}
			else
			{
				//printf ("     |-->-->-- Adding <%s> to <%s>\n", histclone->GetName(), hist_allDT->GetName());
				hist_allDT -> Add (hist);
				//printf ("     |-->-->-- Histogram %s is appedned ...\n");
			}
			
			file -> Close();
			//printf ("     |-->-->-- File closed\n");
			
			delete file;
		}
		printf ("     |-->-- Histograms for data filled, total integral = %.4f\n", hist_allDT->Integral());
		
		// * Monte Carlo
		vector<double>   vec_nEventMC;
		vec_nEventMC . clear();
		
		printf ("     |-- Getting histograms for MC ...\n");
		for (int i=0; i<vec_nameFileinMC.size(); i++)
		{
			Double_t tmpEventMC;
			Double_t nEventMC = 0;
			
			TH1F *histClone;
			TString name_new = Form ("%s%02d", vec_nameHist[plotID].Data(), i);
			
			for (int j=0; j<vec_nameFileinMC[i].size(); j++)
			{
				TFile *file = new TFile (vec_nameFileinMC[i][j].Data(), "read");
				TH1F *hist = (TH1F*)file -> Get (vec_nameHist[plotID]);
				
				TTree *tree = (TTree*)file -> Get ("tree_Global");
				tree -> SetBranchAddress ("nEventNormVBS",  &tmpEventMC);
				tree -> GetEvent (0);
				nEventMC += tmpEventMC;
				
				if (j == 0)   histClone = (TH1F*)hist -> Clone (name_new);
				else   histClone -> Add (hist);
				
				delete hist;
				
				file -> Close();
			}
			
			if (vec_nameProcess[i]=="14.Signal")
			{
				hist_MCSignal = (TH1F*)histClone -> Clone();
			}
			
			if (i==0)
			{
				hist_allMC = (TH1F*)histClone -> Clone();
			}
			else
			{
				hist_allMC -> Add (histClone);
			}
			
			vec_histMC . push_back (histClone);
			vec_nEventMC . push_back (nEventMC);
		}
		
		/*printf ("     |-->-- Histograms for MC filled, total integral = %.4f\n", hist_allMC->Integral());
		for (int i=0; i<vec_nameProcess.size(); i++)
		{
			printf ("             |-- Histograms for %s filled, integral = %.4f\n", vec_nameProcess[i].Data(), vec_histMC[i]->Integral());
		}
		printf ("             |-- Done this step here\n");*/
		
		// * Calculate ratio
		hist_ratio = (TH1F*)hist_allDT -> Clone ();
		hist_ratio -> Divide (hist_allMC);
		
		
		// * Determine the maximum height
		float heightMax = max (hist_allDT->GetMaximum(),  hist_allMC->GetMaximum());
		float heightMin = min (hist_allDT->GetMinimum(1), hist_allMC->GetMinimum(1));
		float multFactor = (setLogY) ? pow(10, 0.2*(log10(heightMax)-log10(heightMin))) : 1.2;
		
		hist_allDT -> SetMaximum (heightMax*multFactor);
		hist_allMC -> SetMaximum (heightMax*multFactor);
		
		// * Scale up signal
		int tmpScaleSig = int (0.5 * hist_allDT->Integral() / hist_MCSignal->Integral());
		
		int   scaleSig    = Calc_Rounding    (tmpScaleSig);
		int   valExponent = Calc_valExponent (tmpScaleSig);
		float valBase     = Calc_valBase     (scaleSig);
		
		hist_MCSignal -> Scale (scaleSig);
		
		TString strSigScale = (valExponent < 4) ? Form ("%d", scaleSig) : Form ("%.1f#times10^{%d}", valBase, valExponent);
		
		
		
		// + Characterize the histograms
		//------------------------------
		printf ("     |-- Setting up plotting style ...\n");
		// * The observables - Data
		Characterize_Dist1D (hist_allDT, 3.0, 1, colour_data, 0, colour_data, 20, 1, vec_nameXaxis[plotID], setLogY);
		
		// * The observables - MC
		vector<TString>  vec_legend = Get_Legend (vec_nameProcess);
		vector<int>      vec_colour = Get_Colour (vec_nameProcess);
		
		for (int i=0; i<vec_histMC.size(); i++)
		{
			Characterize_Dist1D (vec_histMC[i], 3.0, 1, vec_colour[i], 1001, vec_colour[i], 20, 0, vec_nameXaxis[plotID], setLogY);
		}
		Characterize_Dist1D (hist_MCSignal, 3.0, 1, colour_signal, 0, colour_signal, 20, 3, vec_nameXaxis[plotID], setLogY);
		
		// * The ratio
		Characterize_Rate1D (hist_ratio, colour_data, 20, vec_nameXaxis[plotID]);
		
		
		
		// + Stack histogram
		//------------------
		THStack *hstack_MCall = new THStack ("hstack_MCall", "");
		for (int i=0; i<vec_histMC.size(); i++)   hstack_MCall -> Add (vec_histMC[i]);
		
		
		
		// + Drawing stuff
		//----------------
		printf ("     |-- Making plots ...\n");
		// * Canvas
		TCanvas *canvas = new TCanvas ("canvas", "", 750, 700);
		
		// * Pads for observables
		canvas -> cd ();
		TPad *pad_obs = new TPad ("pad_obs", "", 0.0, 0.25, 1.0, 1.0);
		Characterize_Pad (pad_obs, 0.100, 0.030, 0.325, 0.005, setLogY);
		pad_obs -> Draw ();
		
		// * Pads for ratio
		canvas -> cd ();
		TPad *pad_rat = new TPad ("pad_rat", "", 0.0, 0.0, 1.0, 0.25);
		Characterize_Pad (pad_rat, 0.100, 0.030, 0.005, 0.350, 0);
		pad_rat -> Draw ();
		
		// * Draw the observables
		pad_obs -> cd ();
		hist_allDT    -> Draw ("ep");
		hstack_MCall  -> Draw ("hist same");
		hist_MCSignal -> Draw ("hist same");
		hist_allDT    -> Draw ("ep same");
		
		pad_obs -> RedrawAxis ("g");
		pad_obs -> Update ();
		
		TLegend *legend = new TLegend (0.100, 0.675, 0.970, 0.920);
		legend -> SetNColumns (5);
		legend -> SetTextFont (42);
		legend -> SetTextSize (0.035);
		legend -> AddEntry (hist_allDT,     "Data", "EP");
		
		for (int i=0; i<vec_legend.size(); i++)
		{
			legend -> AddEntry (vec_histMC[i], vec_legend[i].Data(), "F");
		}
		legend -> AddEntry (hist_MCSignal, Form("signal#times%s", strSigScale.Data()), "F");
		
		legend -> Draw ("same");
		
		// * Write CMS logo
		TLatex *texLogo = new TLatex ();
		texLogo -> SetNDC      ();
		texLogo -> SetTextFont (42);
		texLogo -> SetTextSize (0.052);
		texLogo -> DrawLatex   (0.100, 0.935, "#bf{CMS}");
		
		// * Write analysis status
		TLatex *texStt = new TLatex ();
		texStt -> SetNDC      ();
		texStt -> SetTextFont (42);
		texStt -> SetTextSize (0.052);
		texStt -> DrawLatex   (0.170, 0.935, "#it{Work-in-progress}");
		
		// * Write luminosity
		float titleLumi[3] = {35.921, 41.525, 59.402};
		TLatex *texLumi = new TLatex ();
		texLumi -> SetNDC       ();
		texLumi -> SetTextAlign (31);
		texLumi -> SetTextFont  (42);
		texLumi -> SetTextSize  (0.052);
		//texLumi -> DrawLatex    (0.975, 0.945, Form("%.1f fb^{-1} (13 TeV) %d", titleLumi[year-2016], year));
		texLumi -> DrawLatex    (0.970, 0.935, Form("%.1f fb^{-1} (13 TeV)", titleLumi[year-2016]));
		
		// * Draw the ratio
		pad_rat -> cd ();
		hist_ratio -> Draw ("ep");
		
		
		
		// + Save the plot
		//----------------
		TString name_toSave = Form("/home/hoa/Task_ZgVBS/Output/Plot_DataMC/%s/plot%d_%s_logY%d.png", strAdvancedCut[cutScenario].Data(), year, vec_nameFileout[plotID].Data(), setLogY);
		canvas -> SaveAs (name_toSave.Data());
		printf ("     |-- Plot is saved to file: %s\n", name_toSave.Data());
	}
}


#endif
