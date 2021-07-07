#include <stdio.h>
#include <iostream>

#include "Plugin/untuplizer_work.h"
#include "Plugin/Tools.h"
#include "Plugin/Selection_Event.h"



//================
// + Main function
//================
void CodeAna_EventSelection (int year = 2018,   bool isMC = 0,   int fileID = 1,   int tightness = 0,   int corMETVer = 0,   char cutScenario = 0)
{
	// + Strings for file name
	//------------------------
	// * List of input & output file name
	vector<TString>  name_input;
	name_input . clear();
	
	vector<TString>  name_output;
	name_output . clear();
	
	// * Directory for input & output
	TString prefixTightness[4] = {"Loose", "Medium", "Tight", "Lead2jets"};
	TString prefixUseCorMET[3] = {"Org", "Mix", "Cor"};
	
	TString strAdvancedCut[2] =
	{
		Form ("VBS_%s_%sMET_Default/",   prefixTightness[tightness].Data(), prefixUseCorMET[corMETVer].Data()),
		Form ("VBS_%s_%sMET_CutAllBtB/", prefixTightness[tightness].Data(), prefixUseCorMET[corMETVer].Data())
	};
	
	TString strDirInput  = (isMC) ? "/home/hoa/Task_ZgVBS/Output/Tree_preselMC/" : "/home/hoa/Task_ZgVBS/Output/Tree_preselDT/";
	TString strDirOutput = (isMC) ? Form("/home/hoa/Task_ZgVBS/Output/Hist_selMC/%s", strAdvancedCut[cutScenario].Data()) : Form("/home/hoa/Task_ZgVBS/Output/Hist_selDT/%s", strAdvancedCut[cutScenario].Data());
	
	// * Create directory for output
	system (Form ("mkdir -p %s", strDirOutput.Data()));
	
	// * Open the directory containing input
	TSystemDirectory dirInput (strDirInput, strDirInput);
	
	// * Read the direcotry for file name (DT)
	TList *listFile = dirInput . GetListOfFiles();
	
	TIter iterFile (listFile);
	while (TSystemFile* file = (TSystemFile*)iterFile())
	{
		TString nameFile = file -> GetName();
		if (!nameFile . Contains (Form("tree%d",year-2000)))   continue;
		
		TString namePathIn  = strDirInput + nameFile;
		
		nameFile . ReplaceAll ("tree", "hist");
		TString namePathOut = strDirOutput + nameFile;
		
		name_input  . push_back (namePathIn);
		name_output . push_back (namePathOut);
	}
	
	printf ("  |-- There are %zu files in %s\n", name_input.size(), strDirInput.Data());
	
	
	
	// + Load the Scale-factor histogram
	//----------------------------------
	// * File containing scale factor
	string path_filePhoSF[3] =
	{
		"/home/hoa/Task_ZgVBS/Code_Ana/ScaleFactor/PhoIDSF_Medium_2016_rereco_New.root",
		"/home/hoa/Task_ZgVBS/Code_Ana/ScaleFactor/PhoIDSF_Medium_2017_rereco.root",
		"/home/hoa/Task_ZgVBS/Code_Ana/ScaleFactor/PhoIDSF_Medium_2018_rereco.root"
	};
	
	// * Load scale-factor
	TFile *file_phoSF = new TFile (path_filePhoSF[year-2016].data(), "read");
	TH2F  *hist_2DPhoSF = (TH2F*)file_phoSF -> Get ("EGamma_SF2D");
	
	
	
	// + Open files to read
	//---------------------
	// * TFile objects
	printf ("  |-- Now processing file: %s\n", name_input[fileID-1].Data());
	
	TreeReader file_input1 (name_input[fileID-1], "tree_Global");
	TreeReader file_input2 (name_input[fileID-1], "tree_Events");
	
	
	
	
	
	// + Global variables
	//-------------------
	file_input1 . GetEntry (0);
	
	// * Number of event
	Float_t   luminosity   = file_input1 . GetFloat  ("luminosity");
	Float_t   crossSection = file_input1 . GetFloat  ("crossSection");
	Double_t  normFactor   = file_input1 . GetDouble ("normFactor");
	
	Long64_t  nEvent        = file_input1 . GetLong64 ("nEvent");
	Long64_t  nEventHLT     = file_input1 . GetLong64 ("nEventHLT");
	Long64_t  nEventPVGood  = file_input1 . GetLong64 ("nEventPVGood");
	Long64_t  nEventSkimPho = file_input1 . GetLong64 ("nEventSkimPho");
	Long64_t  nEventSkimJet = file_input1 . GetLong64 ("nEventSkimJet");
	Long64_t  nEventSkimMET = file_input1 . GetLong64 ("nEventSkimMET");
	Long64_t  nEventLepVeto = file_input1 . GetLong64 ("nEventLepVeto");
	Long64_t  nEventPassPho = file_input1 . GetLong64 ("nEventPassPho");
	Long64_t  nEventPassJet = file_input1 . GetLong64 ("nEventPassJet");
	Long64_t  nEventPassMET = file_input1 . GetLong64 ("nEventPassMET");
	Long64_t  nEventPhoMET  = 0;
	Long64_t  nEventJetMET  = 0;
	Long64_t  nEventPhoJet  = 0;
	Long64_t  nEventJetJet  = 0;
	Long64_t  nEventVBS     = 0;
	vector<long>  nEventEvsel = {0, 0, 0, 0};
	
	Long64_t  nEventNeg        = file_input1 . GetLong64 ("nEventNeg");
	Long64_t  nEventNegHLT     = file_input1 . GetLong64 ("nEventNegHLT");
	Long64_t  nEventNegPVGood  = file_input1 . GetLong64 ("nEventNegPVGood");
	Long64_t  nEventNegSkimPho = file_input1 . GetLong64 ("nEventNegSkimPho");
	Long64_t  nEventNegSkimJet = file_input1 . GetLong64 ("nEventNegSkimJet");
	Long64_t  nEventNegSkimMET = file_input1 . GetLong64 ("nEventNegSkimMET");
	Long64_t  nEventNegLepVeto = file_input1 . GetLong64 ("nEventNegLepVeto");
	Long64_t  nEventNegPassPho = file_input1 . GetLong64 ("nEventNegPassPho");
	Long64_t  nEventNegPassJet = file_input1 . GetLong64 ("nEventNegPassJet");
	Long64_t  nEventNegPassMET = file_input1 . GetLong64 ("nEventNegPassMET");
	Long64_t  nEventNegVBS     = 0;
	
	Double_t  nEventPU        = file_input1 . GetDouble ("nEventPU");
	Double_t  nEventPUHLT     = file_input1 . GetDouble ("nEventPUHLT");
	Double_t  nEventPUPVGood  = file_input1 . GetDouble ("nEventPUPVGood");
	Double_t  nEventPUSkimPho = file_input1 . GetDouble ("nEventPUSkimPho");
	Double_t  nEventPUSkimJet = file_input1 . GetDouble ("nEventPUSkimJet");
	Double_t  nEventPUSkimMET = file_input1 . GetDouble ("nEventPUSkimMET");
	Double_t  nEventPULepVeto = file_input1 . GetDouble ("nEventPULepVeto");
	Double_t  nEventPUPassPho = file_input1 . GetDouble ("nEventPUPassPho");
	Double_t  nEventPUPassJet = file_input1 . GetDouble ("nEventPUPassJet");
	Double_t  nEventPUPassMET = file_input1 . GetDouble ("nEventPUPassMET");
	Double_t  nEventPUVBS     = 0;
	
	Double_t  nEventNorm        = file_input1 . GetDouble ("nEventNorm");
	Double_t  nEventNormHLT     = file_input1 . GetDouble ("nEventNormHLT");
	Double_t  nEventNormPVGood  = file_input1 . GetDouble ("nEventNormPVGood");
	Double_t  nEventNormSkimPho = file_input1 . GetDouble ("nEventNormSkimPho");
	Double_t  nEventNormSkimJet = file_input1 . GetDouble ("nEventNormSkimJet");
	Double_t  nEventNormSkimMET = file_input1 . GetDouble ("nEventNormSkimMET");
	Double_t  nEventNormLepVeto = file_input1 . GetDouble ("nEventNormLepVeto");
	Double_t  nEventNormPassPho = file_input1 . GetDouble ("nEventNormPassPho");
	Double_t  nEventNormPassJet = file_input1 . GetDouble ("nEventNormPassJet");
	Double_t  nEventNormPassMET = file_input1 . GetDouble ("nEventNormPassMET");
	Double_t  nEventNormVBS     = 0;
	
	Float_t  nVtxLepVeto = file_input1 . GetFloat ("nVtxLepVeto");
	Float_t  nVtxPassPho = file_input1 . GetFloat ("nVtxPassPho");
	Float_t  nVtxPassJet = file_input1 . GetFloat ("nVtxPassJet");
	Float_t  nVtxPassMET = file_input1 . GetFloat ("nVtxPassMET");
	Float_t  nVtxPhoMET  = 0;
	Float_t  nVtxJetMET  = 0;
	Float_t  nVtxPhoJet  = 0;
	Float_t  nVtxJetJet  = 0;
	Float_t  nVtxVBS     = 0;
	vector<double>  nVtxEvsel = {0.0, 0.0, 0.0, 0.0};
	
	
	
	
	// + Variables for the histograms
	//-------------------------------
	// * From input
	Int_t    nVtx;
	Float_t  puTrue;
	Float_t  nPUTrue;
	Float_t  puWeight;
	Short_t  genWeight;
	Int_t    nPho;
	Float_t *phoCalibEt, *phoPhi, *phoEta;
	Float_t  pfMET, pfMETPhi, pfMETCor, pfMETCorPhi;
	Int_t    nJet;
	Float_t *jetPt, *jetPhi, *jetEta, *jetEn;
	
	// * For calculation
	TLorentzVector v4D_jet1, v4D_jet2, v4D_dijet;
	TLorentzVector v4D_pho, v4D_phoboost;
	TLorentzVector v4D_inv, v4D_Zg;
	TLorentzVector v4D_system;
	TVector3       v3D_BoostVector;
	vector<int>  phoID, jetID;
	float  pxPho, pyPho, pxMET, pyMET;
	float  phiPhoMET, phiDijet;
	
	// * For result
	Double_t  jetDijetMass;
	Double_t  phoDiphoMass;
	Double_t  phoDiphoEta;
	Double_t  dphi_phoMET;
	Double_t  dphi_jet1MET;
	Double_t  dphi_jet2MET;
	Double_t  dR_2jet;
	Double_t  dEta_2jet;
	Double_t  dPhi_2jet;
	Double_t  dTheta_2jet;
	Double_t  jetEtaEta;
	Double_t  dPhi_ZGvsJets;
	Double_t  EToMET;
	Double_t  rat_rETrPT;
	Double_t  rat_BosptFerpt;
	Double_t  J1oMET;
	Double_t  J2oMET;
	Double_t  phoZeppen;
	Double_t  dR_phojet1, dR_phojet2;
	Double_t  phoBoostTheta;
	Double_t  sigPt;
	Double_t  sigHt;
	Double_t  dPhiPhoDijet;
	
	
	
	
	
	
	// + Create outpur file and tree and histograms
	//---------------------------------------------
	// * Output file
	TFile *file_output = new TFile (name_output[fileID-1], "recreate");
	
	// * Output tree
	TTree *tree_output1 = new TTree ("tree_Global", "Global information");
	
	// * * Global information
	tree_output1 -> Branch ("luminosity",    &luminosity);
	tree_output1 -> Branch ("crossSection",  &crossSection);
	tree_output1 -> Branch ("normFactor",    &normFactor);
	
	tree_output1 -> Branch ("nEvent",         &nEvent);
	tree_output1 -> Branch ("nEventHLT",      &nEventHLT);
	tree_output1 -> Branch ("nEventPVGood",   &nEventPVGood);
	tree_output1 -> Branch ("nEventSkimPho",  &nEventSkimPho);
	tree_output1 -> Branch ("nEventSkimJet",  &nEventSkimJet);
	tree_output1 -> Branch ("nEventSkimMET",  &nEventSkimMET);
	tree_output1 -> Branch ("nEventLepVeto",  &nEventLepVeto);
	tree_output1 -> Branch ("nEventPassPho",  &nEventPassPho);
	tree_output1 -> Branch ("nEventPassJet",  &nEventPassJet);
	tree_output1 -> Branch ("nEventPassMET",  &nEventPassMET);
	tree_output1 -> Branch ("nEventPhoMET",   &nEventPhoMET);
	tree_output1 -> Branch ("nEventJetMET",   &nEventJetMET);
	tree_output1 -> Branch ("nEventJetJet",   &nEventJetJet);
	tree_output1 -> Branch ("nEventPhoJet",   &nEventPhoJet);
	tree_output1 -> Branch ("nEventVBS",      &nEventVBS);
	
	tree_output1 -> Branch ("nEventNeg",         &nEventNeg);
	tree_output1 -> Branch ("nEventNegHLT",      &nEventNegHLT);
	tree_output1 -> Branch ("nEventNegPVGood",   &nEventNegPVGood);
	tree_output1 -> Branch ("nEventNegSkimPho",  &nEventNegSkimPho);
	tree_output1 -> Branch ("nEventNegSkimJet",  &nEventNegSkimJet);
	tree_output1 -> Branch ("nEventNegSkimMET",  &nEventNegSkimMET);
	tree_output1 -> Branch ("nEventNegLepVeto",  &nEventNegLepVeto);
	tree_output1 -> Branch ("nEventNegPassPho",  &nEventNegPassPho);
	tree_output1 -> Branch ("nEventNegPassJet",  &nEventNegPassJet);
	tree_output1 -> Branch ("nEventNegPassMET",  &nEventNegPassMET);
	tree_output1 -> Branch ("nEventNegVBS",      &nEventNegVBS);
	
	tree_output1 -> Branch ("nEventPU",         &nEventPU);
	tree_output1 -> Branch ("nEventPUHLT",      &nEventPUHLT);
	tree_output1 -> Branch ("nEventPUPVGood",   &nEventPUPVGood);
	tree_output1 -> Branch ("nEventPUSkimPho",  &nEventPUSkimPho);
	tree_output1 -> Branch ("nEventPUSkimJet",  &nEventPUSkimJet);
	tree_output1 -> Branch ("nEventPUSkimMET",  &nEventPUSkimMET);
	tree_output1 -> Branch ("nEventPULepVeto",  &nEventPULepVeto);
	tree_output1 -> Branch ("nEventPUPassPho",  &nEventPUPassPho);
	tree_output1 -> Branch ("nEventPUPassJet",  &nEventPUPassJet);
	tree_output1 -> Branch ("nEventPUPassMET",  &nEventPUPassMET);
	tree_output1 -> Branch ("nEventPUVBS",      &nEventPUVBS);
	
	tree_output1 -> Branch ("nEventNorm",         &nEventNorm);
	tree_output1 -> Branch ("nEventNormHLT",      &nEventNormHLT);
	tree_output1 -> Branch ("nEventNormPVGood",   &nEventNormPVGood);
	tree_output1 -> Branch ("nEventNormSkimPho",  &nEventNormSkimPho);
	tree_output1 -> Branch ("nEventNormSkimJet",  &nEventNormSkimJet);
	tree_output1 -> Branch ("nEventNormSkimMET",  &nEventNormSkimMET);
	tree_output1 -> Branch ("nEventNormLepVeto",  &nEventNormLepVeto);
	tree_output1 -> Branch ("nEventNormPassPho",  &nEventNormPassPho);
	tree_output1 -> Branch ("nEventNormPassJet",  &nEventNormPassJet);
	tree_output1 -> Branch ("nEventNormPassMET",  &nEventNormPassMET);
	tree_output1 -> Branch ("nEventNormVBS",      &nEventNormVBS);
	
	tree_output1 -> Branch ("nVtxLepVeto",  &nVtxLepVeto);
	tree_output1 -> Branch ("nVtxPassPho",  &nVtxPassPho);
	tree_output1 -> Branch ("nVtxPassJet",  &nVtxPassJet);
	tree_output1 -> Branch ("nVtxPassMET",  &nVtxPassMET);
	tree_output1 -> Branch ("nVtxPhoMET",   &nVtxPhoMET);
	tree_output1 -> Branch ("nVtxJetMET",   &nVtxJetMET);
	tree_output1 -> Branch ("nVtxJetJet",   &nVtxJetJet);
	tree_output1 -> Branch ("nVtxVBS",      &nVtxVBS);
	
	// * Histogram binning
	double binPhoET[15]   = {0, 200, 225, 250, 275, 300, 350, 400, 450, 500, 600, 700, 800,  900, 1000};
	double binJet1Pt[15]  = {0,  30,  60, 100, 150, 200, 250, 300, 350, 400, 500, 600, 700,  800, 1000};
	double binJet2Pt[15]  = {0,  30,  60, 100, 150, 200, 250, 300, 350, 400, 500, 600, 700,  800, 1000};
	double binDjMass[15]  = {0, 100, 150, 200, 250, 300, 350, 400, 500, 600, 700, 800, 900, 1000, 1500};
	double binDpMass[15]  = {0,  20,  30,  40,  50,  60,  70,  80, 100, 120, 140, 160, 180,  200,  300};
	double binMET[14]     = {0,  50,  70, 100, 150, 200, 250, 300, 350, 400, 500, 650, 800, 1000};
	double bin2dPhoET[8]  = {0, 200, 250, 300, 400, 500, 700, 1000};
	double bin2dJet1Pt[8] = {0,  30, 100, 200, 300, 400, 600, 1000};
	double bin2dJet2Pt[8] = {0,  30, 100, 200, 300, 400, 600, 1000};
	double bin2dDjMass[8] = {0, 100, 200, 300, 400, 600, 800, 1500};
	double bin2dMET[8]    = {0,  50, 150, 250, 350, 450, 550, 1000};
	
	// * Photon histograms
	TH1F *hist_ET_Pho         = new TH1F ("hist_ET_Pho",         "", 14, binPhoET);
	TH1F *hist_eta_Pho        = new TH1F ("hist_eta_Pho",        "",  8, -1.60, 1.60);
	TH1F *hist_Phi_Pho        = new TH1F ("hist_Phi_Pho",        "", 10, -4.0, 4.0);
	TH1F *hist_theta_Phoboost = new TH1F ("hist_theta_Phoboost", "",  9,  0.0, 3.6);
	
	// * Jet histograms
	TH1F *hist_pT_Jet1    = new TH1F ("hist_pT_Jet1",    "", 14, binJet1Pt);
	TH1F *hist_pT_Jet2    = new TH1F ("hist_pT_Jet2",    "", 14, binJet2Pt);
	TH1F *hist_eta_Jet1   = new TH1F ("hist_eta_Jet1",   "", 16, -5.6, 5.6);
	TH1F *hist_eta_Jet2   = new TH1F ("hist_eta_Jet2",   "", 16, -5.6, 5.6);
	TH1F *hist_Phi_Jet1   = new TH1F ("hist_Phi_Jet1",   "", 10, -4.0, 4.0);
	TH1F *hist_Phi_Jet2   = new TH1F ("hist_Phi_Jet2",   "", 10, -4.0, 4.0);
	TH1F *hist_Mass_Dijet = new TH1F ("hist_Mass_Dijet", "", 14, binDjMass);
	
	// * MET histograms
	TH1F *hist_ET_Invis  = new TH1F ("hist_ET_Invis",  "", 13, binMET);
	TH1F *hist_Phi_Invis = new TH1F ("hist_Phi_Invis", "", 10, -4.0, 4.0);
	
	// * Angular separation histograms
	TH1F *hist_dPhi_Pho_Invis     = new TH1F ("hist_dPhi_Pho_Invis",     "", 18, 0.0, 3.6);
	TH1F *hist_dR_Pho_Jet1        = new TH1F ("hist_dR_Pho_Jet1",        "", 13, 0.0, 6.5);
	TH1F *hist_dR_Pho_Jet2        = new TH1F ("hist_dR_Pho_Jet2",        "", 13, 0.0, 6.5);
	TH1F *hist_dPhi_Invis_Jet1    = new TH1F ("hist_dPhi_Invis_Jet1",    "", 18, 0.0, 3.6);
	TH1F *hist_dPhi_Invis_Jet2    = new TH1F ("hist_dPhi_Invis_Jet2",    "", 18, 0.0, 3.6);
	TH1F *hist_dR_Jet_Jet         = new TH1F ("hist_dR_Jet_Jet",         "", 13, 0.0, 6.5);
	TH1F *hist_deta_Jet_Jet       = new TH1F ("hist_deta_Jet_Jet",       "", 13, 0.0, 6.5);
	TH1F *hist_dPhi_Jet_Jet       = new TH1F ("hist_dPhi_Jet_Jet",       "", 18, 0.0, 3.6);
	TH1F *hist_ratio_ETPho_Invis  = new TH1F ("hist_ratio_ETPho_Invis",  "", 18, 0.0, 3.6);
	TH1F *hist_lratio_EToET_PToPT = new TH1F ("hist_lratio_EToET_PToPT", "", 20, -1.0, 1.0);
	TH1F *hist_lratio_PtBos_PtFer = new TH1F ("hist_lratio_PtBos_PtFer", "", 20, -1.0, 1.0);
	TH1F *hist_ratio_pTJet1_Invis = new TH1F ("hist_ratio_pTJet1_Invis", "", 18, 0.0, 7.2);
	TH1F *hist_ratio_pTJet2_Invis = new TH1F ("hist_ratio_pTJet2_Invis", "", 18, 0.0, 3.6);
	
	// * VBS System properties
	TH1F *hist_prod_EtaJet_EtaJet = new TH1F ("hist_prod_EtaJet_EtaJet", "", 20, -15, 5);
	TH1F *hist_dPhi_ZPho_Dijet    = new TH1F ("hist_dPhi_ZPho_Dijet",    "", 18, 0.0, 3.6);
	TH1F *hist_Zeppen_Pho         = new TH1F ("hist_Zeppen_Pho",         "", 20, 0.0, 4.0);
	TH1F *hist_pT_Signal          = new TH1F ("hist_pT_Signal",          "", 10, 0.0, 400);
	
	// * Distribution to study the PU
	TH1F *hist_no_VtxPres   = new TH1F ("hist_no_VtxPres",   "", 40, 0, 80);
	TH1F *hist_no_VtxPresWd = new TH1F ("hist_no_VtxPresWd", "", 20, 0, 80);
	TH1F *hist_no_Vtx       = new TH1F ("hist_no_Vtx",       "", 40, 0, 80);
	TH1F *hist_no_VtxWei    = new TH1F ("hist_no_VtxWei",    "", 40, 0, 80);
	TH1F *hist_no_VtxWd     = new TH1F ("hist_no_VtxWd",     "", 20, 0, 80);
	TH1F *hist_no_VtxWeiWd  = new TH1F ("hist_no_VtxWeiWd",  "", 20, 0, 80);
	TH1F *hist_no_PUtruePos = new TH1F ("hist_no_PUtruePos", "", 40, 0, 80);
	TH1F *hist_no_PUtrueNeg = new TH1F ("hist_no_PUtrueNeg", "", 40, 0, 80);
	
	// * Distribution before selection
	TH1F *hist_no_Pho       = new TH1F ("hist_no_Pho",       "", 20, 0, 20);
	TH1F *hist_no_Jet       = new TH1F ("hist_no_Jet",       "", 20, 0, 20);
	TH1F *hist_SumdPhi_Pho_Invis = new TH1F ("hist_SumdPhi_Pho_Invis", "", 20, 0, 5);
	TH1F *hist_SumdPhi_Jet_Invis = new TH1F ("hist_SumdPhi_Jet_Invis", "", 16, 0, 32);
	TH1F *hist_SumdR_Jet_Pho     = new TH1F ("hist_SumdR_Jet_Pho",     "", 30, 0, 30);
	TH1F *hist_SumdR_Jet_Jet     = new TH1F ("hist_SumdR_Jet_Jet",  "",    30, 0, 30);
	
	// * Distribution to study the "peak"
	TH1F *hist_dPhi_Pho_Dijet = new TH1F ("hist_dPhi_Pho_Dijet", "", 10, 0.0, 4.0);
	TH1F *hist_dPhi_Invis_All = new TH1F ("hist_dPhi_Invis_All", "", 10, 0.0, 4.0);
	
	// * Two-dimensional distributions
	TH2F *hist2D_EoM_phoEt        = new TH2F ("hist2D_EoM_phoEt",        "",  16, 0, 3.2,     14, binPhoET);
	TH2F *hist2D_sigPt_MET        = new TH2F ("hist2D_sigPt_MET",        "",  7, bin2dMET,    10, 0, 200);
	TH2F *hist2D_sigPt_phoBTheta  = new TH2F ("hist2D_sigPt_phoBTheta",  "",  9, 0.0, 3.6,    10, 0, 200);
	TH2F *hist2D_sigPt_sigHT      = new TH2F ("hist2D_sigPt_sigHT",      "",  12, 300, 1500,  10, 0, 200);
	TH2F *hist2D_ZGvsJets_jet1Phi = new TH2F ("hist2D_ZGvsJets_jet1Phi", "",  9, -3.6, 3.6,   9, 0.0, 3.6);
	TH2F *hist2D_ZGvsJets_jet1Eta = new TH2F ("hist2D_ZGvsJets_jet1Eta", "",  8, -5.6, 5.6,   9, 0.0, 3.6);
	TH2F *hist2D_jet1Eta_jet1Phi  = new TH2F ("hist2D_jet1Eta_jet1Phi",  "",  8, -5.6, 5.6,   9, -3.6, 3.6);
	
	
	
	
	// + Force calculate the error by weight
	//======================================
	// * Sumw2 the photons
	hist_ET_Pho         -> Sumw2 ();
	hist_eta_Pho        -> Sumw2 ();
	hist_Phi_Pho        -> Sumw2 ();
	hist_theta_Phoboost -> Sumw2 ();
	
	// * Sumw2 the Jets
	hist_pT_Jet1    -> Sumw2 ();
	hist_pT_Jet2    -> Sumw2 ();
	hist_eta_Jet1   -> Sumw2 ();
	hist_eta_Jet2   -> Sumw2 ();
	hist_Phi_Jet1   -> Sumw2 ();
	hist_Phi_Jet2   -> Sumw2 ();
	hist_Mass_Dijet -> Sumw2 ();
	
	// * Sumw2 the Missing ET
	hist_ET_Invis  -> Sumw2 ();
	hist_Phi_Invis -> Sumw2 ();
	
	// * Sumw2 the angular separation
	hist_dPhi_Pho_Invis  -> Sumw2 ();
	hist_dR_Pho_Jet1     -> Sumw2 ();
	hist_dR_Pho_Jet2     -> Sumw2 ();
	hist_dPhi_Invis_Jet1 -> Sumw2 ();
	hist_dPhi_Invis_Jet2 -> Sumw2 ();
	hist_dR_Jet_Jet      -> Sumw2 ();
	hist_deta_Jet_Jet    -> Sumw2 ();
	hist_dPhi_Jet_Jet    -> Sumw2 ();
	
	// * Sumw2 the vertices
	hist_no_VtxPres   -> Sumw2();
	hist_no_VtxPresWd -> Sumw2();
	hist_no_Vtx       -> Sumw2();
	hist_no_VtxWd     -> Sumw2();
	hist_no_VtxWei    -> Sumw2();
	hist_no_VtxWeiWd  -> Sumw2();
	hist_no_PUtruePos -> Sumw2();
	hist_no_PUtrueNeg -> Sumw2();
	
	// * Distribution before selection
	hist_no_Pho            -> Sumw2();
	hist_no_Jet            -> Sumw2();
	hist_SumdPhi_Pho_Invis -> Sumw2();
	hist_SumdPhi_Jet_Invis -> Sumw2();
	hist_SumdR_Jet_Pho     -> Sumw2();
	hist_SumdR_Jet_Jet     -> Sumw2();
	
	// * Distribution to study the "peak"
	hist_dPhi_Pho_Dijet -> Sumw2();
	hist_dPhi_Invis_All -> Sumw2();
	
	// * Sumw2 the signal system information
	hist_prod_EtaJet_EtaJet -> Sumw2 ();
	hist_ratio_ETPho_Invis  -> Sumw2 ();
	hist_lratio_EToET_PToPT -> Sumw2 ();
	hist_lratio_PtBos_PtFer -> Sumw2 ();
	hist_ratio_pTJet1_Invis -> Sumw2 ();
	hist_ratio_pTJet2_Invis -> Sumw2 ();
	hist_dPhi_ZPho_Dijet    -> Sumw2 ();
	hist_Zeppen_Pho         -> Sumw2 ();
	hist_pT_Signal          -> Sumw2 ();
	
	
	
	
	
	
	
	// + Read the events
	//------------------
	// * Get the number of events
	Long64_t nEventLocal = file_input2 . GetEntriesFast ();
	
	Long64_t nEventSub = nEventLocal/10;
	if (nEventSub == 0)   nEventSub = 1;
	
	
	// * Decide if back-to-back photon/jet-MET pair should be removed
	bool cutBtBPho = (cutScenario==1) ? true : false;
	bool cutBtBJet = (cutScenario==1) ? true : false;
	//bool choose2Jet = (cutScenario==1) ? true : false;
	bool choose2Jet = false;
	
	
	// * Read tree
	for (Long64_t ev=0; ev<nEventLocal; ev++)
	{
		//if (ev%nEventSub==0)   printf ("  |-- |-- This is the event number %lld\n", ev);
		file_input2 . GetEntry (ev);
		
		
		
		
		// + Get the variables
		//--------------------
		// * Get photon
		nPho           = file_input2 . GetInt      ("nPho");
		phoCalibEt     = file_input2 . GetPtrFloat ("phoCalibEt");
		phoEta         = file_input2 . GetPtrFloat ("phoEta");
		phoPhi         = file_input2 . GetPtrFloat ("phoPhi");
		
		// * Get MET
		pfMET       = file_input2 . GetFloat ("pfMET");
		pfMETPhi    = file_input2 . GetFloat ("pfMETPhi");
		pfMETCor    = file_input2 . GetFloat ("pfMETCor");
		pfMETCorPhi = file_input2 . GetFloat ("pfMETCorPhi");
		float invPt  = (corMETVer > 0) ? pfMETCor    : pfMET;
		float invPhi = (corMETVer > 1) ? pfMETCorPhi : pfMETPhi;
		
		// * Get Jets
		nJet   = file_input2 . GetInt      ("nJet");
		jetPt  = file_input2 . GetPtrFloat ("jetPt");
		jetEta = file_input2 . GetPtrFloat ("jetEta");
		jetPhi = file_input2 . GetPtrFloat ("jetPhi");
		jetEn  = file_input2 . GetPtrFloat ("jetEn");
		
		// * Get PU information
		nVtx   = file_input2 . GetInt      ("nVtx");
		
		// * Get weight (MC only)
		puWeight  = 1.0;
		genWeight = 1;
		nPUTrue   = nVtx;
		if (isMC == true)
		{
			puTrue    = file_input2 . GetFloat ("puTrue");
			nPUTrue   = puTrue;
			
			puWeight  = file_input2 . GetFloat ("puWeight0");
			genWeight = file_input2 . GetShort ("genWeight");
		}
		
		//puWeight  = 1.0;
		
		
		
		// + Compute the azimuthal angle between MET and all other
		//--------------------------------------------------------
		TLorentzVector v4d_visible;
		v4d_visible . SetPtEtaPhiE (0, 0, 0, 0);
		
		TLorentzVector v4d_obj;
		
		for (int i=0; i<nPho; i++)
		{
			v4d_obj . SetPtEtaPhiM (phoCalibEt[i], phoEta[i], phoPhi[i], 0);
			v4d_visible += v4d_obj;
		}
		
		for (int i=0; i<nJet; i++)
		{
			v4d_obj . SetPtEtaPhiE (jetPt[i], jetEta[i], jetPhi[i], jetEn[i]);
			v4d_visible += v4d_obj;
		}
		
		float visPhi = v4d_visible . Phi();
		float dPhi_Invis_All = compute_DeltaPhi (visPhi, invPhi);
		
		
		
		// + The deltaR between any 2 jets
		//--------------------------------
		float sumdR_Jet_Jet = 0.0;
		for (int i=0; i<nJet-1; i++)
		{
			for (int j=i+1; j<nJet; j++)
			{
				sumdR_Jet_Jet += compute_DeltaR (jetEta[i], jetEta[j], jetPhi[i], jetPhi[j]);
			}
		}
		
		
		
		// + Get histograms of preselection
		//---------------------------------
		// * Number of photons and jets
		hist_no_VtxPres   -> Fill (nVtx, normFactor*genWeight);
		hist_no_VtxPresWd -> Fill (nVtx, normFactor*genWeight);
		
		// * Total angular distance
		float  sumdPhi_Pho_Invis = 0.0;
		float  sumdPhi_Jet_Invis = 0.0;
		float  sumdR_Jet_Pho     = 0.0;
		
		for (int i=0; i<nPho; i++)
		{
			sumdPhi_Pho_Invis += compute_DeltaPhi (phoPhi[i], invPhi);
			
			for (int j=0; j<nJet; j++)
			{
				sumdR_Jet_Pho += compute_DeltaR (phoEta[i], jetEta[j], phoPhi[i], jetPhi[j]);
				if (i==0)   sumdPhi_Jet_Invis += compute_DeltaPhi (jetPhi[j], invPhi);
			}
		}
		
		
		
		// + Applying cut based on the scenario
		//-------------------------------------
		phoID . clear ();
		jetID . clear ();
		
		if (tightness == 0)
		{
			// + Use loose VBS cut
			//--------------------
			Select_Event_VBSLoose (file_input2, corMETVer, year, phoID, jetID, cutBtBPho, cutBtBJet, nEventEvsel, nVtxEvsel);
		}
		else if (tightness == 1)
		{
			// + Use tighter VBS cut
			//----------------------
			Select_Event_VBSMedium (file_input2, corMETVer, year, phoID, jetID, cutBtBPho, cutBtBJet, nEventEvsel, nVtxEvsel);
		}
		else if (tightness == 2)
		{
			// + Use tighter VBS cut
			//----------------------
			Select_Event_VBSTight (file_input2, corMETVer, year, phoID, jetID, cutBtBPho, cutBtBJet, nEventEvsel, nVtxEvsel);
		}
		else if (tightness == 3)
		{
			// + Use tighter VBS cut
			//----------------------
			Select_Event_VBSLead2jets (file_input2, corMETVer, year, phoID, jetID, cutBtBPho, cutBtBJet, nEventEvsel, nVtxEvsel);
		}
		
		// * Reject events that have less than 2 jets and no photon
		if (jetID.size()<2 || phoID.size()<1)   continue;
		
		// * Reject events contains more than 2 jets in the scen #1
		if (choose2Jet && jetID.size()>2)   continue;
		
		
		
		// + Get the scale-factor
		//-----------------------
		int    binx = hist_2DPhoSF -> GetXaxis() -> FindBin(phoEta[phoID[0]]);
		int    biny = hist_2DPhoSF -> GetYaxis() -> FindBin(phoCalibEt[phoID[0]]);
		float  sf_pho = hist_2DPhoSF -> GetBinContent (binx, biny);
		
		
		
		// + Calculate the variables
		//--------------------------
		// * Delta phi
		dphi_phoMET  = compute_DeltaPhi (phoPhi[phoID[0]], invPhi);
		dphi_jet1MET = compute_DeltaPhi (jetPhi[jetID[0]], invPhi);
		dphi_jet2MET = compute_DeltaPhi (jetPhi[jetID[1]], invPhi);
		
		// * Delta R and eta
		dR_phojet1 = compute_DeltaR (phoEta[phoID[0]], jetEta[jetID[0]], phoPhi[phoID[0]], jetPhi[jetID[0]]);
		dR_phojet2 = compute_DeltaR (phoEta[phoID[0]], jetEta[jetID[1]], phoPhi[phoID[0]], jetPhi[jetID[1]]);
		
		dR_2jet   = compute_DeltaR (jetEta[jetID[0]], jetEta[jetID[1]], jetPhi[jetID[0]], jetPhi[jetID[1]]);
		dEta_2jet = abs (jetEta[jetID[0]] - jetEta[jetID[1]]);
		
		// * Dijet mass
		v4D_jet1 . SetPtEtaPhiE (jetPt[jetID[0]], jetEta[jetID[0]], jetPhi[jetID[0]], jetEn[jetID[0]]);
		v4D_jet2 . SetPtEtaPhiE (jetPt[jetID[1]], jetEta[jetID[1]], jetPhi[jetID[1]], jetEn[jetID[1]]);
		v4D_dijet = v4D_jet1 + v4D_jet2;
		jetDijetMass = v4D_dijet . M();
		
		// * Delta Phi of 2 jets
		dPhi_2jet = compute_DeltaPhi (jetPhi[jetID[0]], jetPhi[jetID[1]]);
		
		// * Jet Etas sign
		jetEtaEta = jetEta[jetID[0]] * jetEta[jetID[1]];
		
		// * ratio of ET and PT
		EToMET = phoCalibEt[phoID[0]]/invPt;
		J1oMET = jetPt[jetID[0]] / invPt;
		J2oMET = jetPt[jetID[1]] / invPt;
		float EToET = (EToMET > 1) ? EToMET : 1/EToMET;
		float PToPT = jetPt[jetID[0]] / jetPt[jetID[1]];
		rat_rETrPT = log10 (EToET / PToPT);
		
		// * Delta Phi between jj and Zg
		/*pxPho = phoCalibEt[phoID[0]] * cos (phoPhi[phoID[0]]);
		pyPho = phoCalibEt[phoID[0]] * sin (phoPhi[phoID[0]]);
		pxMET = (corMETVer > 0) ? pfMETCor * cos(pfMETCorPhi) : pfMET * cos(pfMETPhi);
		pyMET = (corMETVer > 0) ? pfMETCor * sin(pfMETCorPhi) : pfMET * sin(pfMETPhi);
		
		phiPhoMET = atan2 (pyPho+pyMET, pxPho+pxMET);
		phiDijet  = v4D_dijet . Phi();
		
		dPhi_ZGvsJets = compute_DeltaPhi (phiPhoMET, phiDijet);*/
		v4D_pho . SetPtEtaPhiM (phoCalibEt[phoID[0]], phoEta[phoID[0]], phoPhi[phoID[0]], 0);
		v4D_inv . SetPtEtaPhiM (invPt, 0, invPhi, 0);
		v4D_Zg = v4D_pho + v4D_inv;
		
		dPhi_ZGvsJets = compute_DeltaPhi (v4D_Zg.Phi(), v4D_dijet.Phi());
		
		// * Ratio between diboson and dijet pT
		rat_BosptFerpt = log10 (v4D_Zg.Pt() / v4D_dijet.Pt());
		
		
		// * Tranverse momentum of the system
		//sigPt = sqrt (pow(pyPho+pyMET+v4D_dijet.Py(),2) + pow(pxPho+pxMET+v4D_dijet.Px(),2));
		v4D_system = v4D_dijet + v4D_Zg;
		sigPt = v4D_system . Pt();
		
		// * Scalar sum of tranverse momentum
		sigHt = jetPt[jetID[0]] + jetPt[jetID[1]] + phoCalibEt[phoID[0]] + invPt;
		
		// * Zeppenfeld variable
		phoZeppen = abs (phoEta[phoID[0]] - (jetEta[jetID[0]]+jetEta[jetID[1]])/2) / dEta_2jet;
		
		// * Delta Phi of photon to Sig / dijet
		dPhiPhoDijet = compute_DeltaPhi (phoPhi[phoID[0]], v4D_dijet.Phi());
		
		
		
		// + Boosted theta of photon
		//--------------------------
		// * Define the photon 4-momentum
		v4D_phoboost . SetPtEtaPhiM (phoCalibEt[phoID[0]], phoEta[phoID[0]], phoPhi[phoID[0]], 0);
		
		// * Rotate the vectors
		float rotTheta = -v4D_system . Theta();
		float rotPhi   = -v4D_system . Phi();
		v4D_system   . RotateZ (rotPhi);
		v4D_system   . RotateY (rotTheta);
		v4D_jet1     . RotateZ (rotPhi);
		v4D_jet1     . RotateY (rotTheta);
		v4D_jet2     . RotateZ (rotPhi);
		v4D_jet2     . RotateY (rotTheta);
		v4D_phoboost . RotateZ (rotPhi);
		v4D_phoboost . RotateY (rotTheta);
		
		// * Boost the photon
		v3D_BoostVector = v4D_system . BoostVector ();
		v4D_phoboost . Boost (-v3D_BoostVector);
		v4D_jet1 . Boost (-v3D_BoostVector);
		v4D_jet2 . Boost (-v3D_BoostVector);
		
		//phoBoostTheta = compute_DeltaR2 (v4D_phoboost.Theta(), v4D_jet1.Theta(), v4D_phoboost.Phi(), v4D_jet1.Phi());
		phoBoostTheta = compute_DeltaR2 (v4D_phoboost.Theta(), 0, v4D_phoboost.Phi(), 0);
		
		
		
		// + Fill the histograms
		//----------------------
		// NOTE Cheating here
		//puWeight  = 1.0;
		//genWeight = 1;
		
		hist_SumdPhi_Pho_Invis -> Fill (sumdPhi_Pho_Invis, normFactor*puWeight*genWeight*sf_pho);
		hist_SumdPhi_Jet_Invis -> Fill (sumdPhi_Jet_Invis, normFactor*puWeight*genWeight*sf_pho);
		hist_SumdR_Jet_Pho     -> Fill (sumdR_Jet_Pho,     normFactor*puWeight*genWeight*sf_pho);
		hist_SumdR_Jet_Jet     -> Fill (sumdR_Jet_Jet,     normFactor*puWeight*genWeight*sf_pho);
		
		hist_ET_Pho         -> Fill (phoCalibEt[phoID[0]], normFactor*puWeight*genWeight*sf_pho);
		hist_eta_Pho        -> Fill (phoEta[phoID[0]],     normFactor*puWeight*genWeight*sf_pho);
		hist_Phi_Pho        -> Fill (phoPhi[phoID[0]],     normFactor*puWeight*genWeight*sf_pho);
		hist_theta_Phoboost -> Fill (phoBoostTheta,        normFactor*puWeight*genWeight*sf_pho);
		
		hist_pT_Jet1    -> Fill (jetPt[jetID[0]],  normFactor*puWeight*genWeight*sf_pho);
		hist_pT_Jet2    -> Fill (jetPt[jetID[1]],  normFactor*puWeight*genWeight*sf_pho);
		hist_eta_Jet1   -> Fill (jetEta[jetID[0]], normFactor*puWeight*genWeight*sf_pho);
		hist_eta_Jet2   -> Fill (jetEta[jetID[1]], normFactor*puWeight*genWeight*sf_pho);
		hist_Phi_Jet1   -> Fill (jetPhi[jetID[0]], normFactor*puWeight*genWeight*sf_pho);
		hist_Phi_Jet2   -> Fill (jetPhi[jetID[1]], normFactor*puWeight*genWeight*sf_pho);
		hist_Mass_Dijet -> Fill (jetDijetMass,     normFactor*puWeight*genWeight*sf_pho);
		
		hist_ET_Invis  -> Fill (invPt,    normFactor*puWeight*genWeight*sf_pho);
		hist_Phi_Invis -> Fill (invPhi, normFactor*puWeight*genWeight*sf_pho);
		
		hist_dPhi_Pho_Invis  -> Fill (dphi_phoMET,   normFactor*puWeight*genWeight*sf_pho);
		hist_dR_Pho_Jet1     -> Fill (dR_phojet1,    normFactor*puWeight*genWeight*sf_pho);
		hist_dR_Pho_Jet2     -> Fill (dR_phojet2,    normFactor*puWeight*genWeight*sf_pho);
		hist_dPhi_Invis_Jet1 -> Fill (dphi_jet1MET,  normFactor*puWeight*genWeight*sf_pho);
		hist_dPhi_Invis_Jet2 -> Fill (dphi_jet2MET,  normFactor*puWeight*genWeight*sf_pho);
		hist_dR_Jet_Jet      -> Fill (dR_2jet,       normFactor*puWeight*genWeight*sf_pho);
		hist_deta_Jet_Jet    -> Fill (dEta_2jet,     normFactor*puWeight*genWeight*sf_pho);
		hist_dPhi_Jet_Jet    -> Fill (dPhi_2jet,     normFactor*puWeight*genWeight*sf_pho);
		
		hist_ratio_ETPho_Invis  -> Fill (EToMET,          normFactor*puWeight*genWeight*sf_pho);
		hist_lratio_EToET_PToPT -> Fill (rat_rETrPT,      normFactor*puWeight*genWeight*sf_pho);
		hist_lratio_PtBos_PtFer -> Fill (rat_BosptFerpt,  normFactor*puWeight*genWeight*sf_pho);
		hist_ratio_pTJet1_Invis -> Fill (J1oMET,          normFactor*puWeight*genWeight*sf_pho);
		hist_ratio_pTJet2_Invis -> Fill (J2oMET,          normFactor*puWeight*genWeight*sf_pho);
		hist_prod_EtaJet_EtaJet -> Fill (jetEtaEta,       normFactor*puWeight*genWeight*sf_pho);
		hist_dPhi_ZPho_Dijet    -> Fill (dPhi_ZGvsJets,   normFactor*puWeight*genWeight*sf_pho);
		hist_Zeppen_Pho         -> Fill (phoZeppen,       normFactor*puWeight*genWeight*sf_pho);
		hist_pT_Signal          -> Fill (sigPt,           normFactor*puWeight*genWeight*sf_pho);
		
		hist_no_Pho       -> Fill (nPho, normFactor*genWeight);
		hist_no_Jet       -> Fill (nJet, normFactor*genWeight);
		hist_no_Vtx       -> Fill (nVtx, normFactor*genWeight);
		hist_no_VtxWd     -> Fill (nVtx, normFactor*genWeight);
		hist_no_VtxWei    -> Fill (nVtx, normFactor*puWeight*genWeight*sf_pho);
		hist_no_VtxWeiWd  -> Fill (nVtx, normFactor*puWeight*genWeight*sf_pho);
		if (genWeight > 0)
		{
			hist_no_PUtruePos -> Fill (nPUTrue, normFactor);
		}
		else
		{
			hist_no_PUtrueNeg -> Fill (nPUTrue, normFactor);
		}
		
		/*if (EToMET < 1.6)
		{
			hist_dPhi_Pho_Dijet -> Fill (dPhiPhoDijet, normFactor*puWeight*genWeight*sf_pho);
		}*/
		hist_dPhi_Pho_Dijet -> Fill (dPhiPhoDijet, normFactor*puWeight*genWeight*sf_pho);
		hist_dPhi_Invis_All -> Fill (dPhi_Invis_All, normFactor*puWeight*genWeight*sf_pho);
		
		hist2D_EoM_phoEt        -> Fill (EToMET,            phoCalibEt[phoID[0]],  normFactor*puWeight*genWeight*sf_pho);
		hist2D_sigPt_MET        -> Fill (pfMET,             sigPt,                 normFactor*puWeight*genWeight*sf_pho);
		hist2D_sigPt_phoBTheta  -> Fill (phoBoostTheta,     sigPt,                 normFactor*puWeight*genWeight*sf_pho);
		hist2D_sigPt_sigHT      -> Fill (sigHt,             sigPt,                 normFactor*puWeight*genWeight*sf_pho);
		hist2D_ZGvsJets_jet1Eta -> Fill (jetEta[jetID[0]],  dPhi_ZGvsJets,         normFactor*puWeight*genWeight*sf_pho);
		hist2D_ZGvsJets_jet1Phi -> Fill (jetPhi[jetID[0]],  dPhi_ZGvsJets,         normFactor*puWeight*genWeight*sf_pho);
		hist2D_jet1Eta_jet1Phi  -> Fill (jetPhi[jetID[0]],  jetEta[jetID[0]],      normFactor*puWeight*genWeight*sf_pho);
		
		
		// + Count the passing event
		//--------------------------
		nEventVBS    += 1;
		nEventNegVBS += genWeight;
		nEventPUVBS  += genWeight*puWeight;
		
		nVtxVBS += nVtx*genWeight*puWeight;
	}
	
	
	
	
	
	// + Fill the info tree
	//---------------------
	nEventPhoMET = nEventEvsel[0];
	nEventJetMET = nEventEvsel[1];
	nEventPhoJet = nEventEvsel[2];
	nEventJetJet = nEventEvsel[3];
	
	nVtxPhoMET = (nEventEvsel[0]!=0) ? nVtxEvsel[0]/nEventEvsel[0] : 0;
	nVtxJetMET = (nEventEvsel[1]!=0) ? nVtxEvsel[1]/nEventEvsel[1] : 0;
	nVtxPhoJet = (nEventEvsel[2]!=0) ? nVtxEvsel[2]/nEventEvsel[2] : 0;
	nVtxJetJet = (nEventEvsel[3]!=0) ? nVtxEvsel[3]/nEventEvsel[3] : 0;
	
	nEventNormVBS = nEventPUVBS * normFactor;
	nVtxVBS = (nEventPUVBS!=0) ? nVtxVBS/nEventPUVBS : 0;
	
	tree_output1 -> Fill ();
	printf ("  |-- There are %lld events selected\n", nEventVBS);
	
	tree_output1 -> Write ("", TObject::kOverwrite);
	
	
	
	// + Wrtie to file
	//================
	// * Navigate to file
	file_output -> cd ();
	
	// * Write the photons
	hist_ET_Pho         -> Write();
	hist_eta_Pho        -> Write();
	hist_Phi_Pho        -> Write();
	hist_theta_Phoboost -> Write();
	
	// * Write the Jets
	hist_pT_Jet1    -> Write();
	hist_pT_Jet2    -> Write();
	hist_eta_Jet1   -> Write();
	hist_eta_Jet2   -> Write();
	hist_Phi_Jet1   -> Write();
	hist_Phi_Jet2   -> Write();
	hist_Mass_Dijet -> Write();
	
	// * Write the Missing ET
	hist_ET_Invis  -> Write();
	hist_Phi_Invis -> Write();
	
	// * Write the angular separation
	hist_dPhi_Pho_Invis  -> Write();
	hist_dR_Pho_Jet1     -> Write();
	hist_dR_Pho_Jet2     -> Write();
	hist_dPhi_Invis_Jet1 -> Write();
	hist_dPhi_Invis_Jet2 -> Write();
	hist_dR_Jet_Jet      -> Write();
	hist_deta_Jet_Jet    -> Write();
	hist_dPhi_Jet_Jet    -> Write();
	
	// * Write the signal system information
	hist_prod_EtaJet_EtaJet -> Write();
	hist_ratio_ETPho_Invis  -> Write();
	hist_lratio_EToET_PToPT -> Write();
	hist_lratio_PtBos_PtFer -> Write();
	hist_ratio_pTJet1_Invis -> Write();
	hist_ratio_pTJet2_Invis -> Write();
	hist_dPhi_ZPho_Dijet    -> Write();
	hist_Zeppen_Pho         -> Write();
	hist_pT_Signal          -> Write();
	
	// * Write the 2-D histograms
	hist2D_EoM_phoEt        -> Write();
	hist2D_sigPt_MET        -> Write();
	hist2D_sigPt_phoBTheta  -> Write();
	hist2D_sigPt_sigHT      -> Write();
	hist2D_ZGvsJets_jet1Eta -> Write();
	hist2D_ZGvsJets_jet1Phi -> Write();
	hist2D_jet1Eta_jet1Phi  -> Write();
	
	// * Distribution to study the PU
	hist_no_VtxPres   -> Write();
	hist_no_VtxPresWd -> Write();
	hist_no_Vtx       -> Write();
	hist_no_VtxWd     -> Write();
	hist_no_VtxWei    -> Write();
	hist_no_VtxWeiWd  -> Write();
	hist_no_PUtruePos -> Write();
	hist_no_PUtrueNeg -> Write();
	
	// * Distribution before selection
	hist_no_Pho            -> Write();
	hist_no_Jet            -> Write();
	hist_SumdPhi_Pho_Invis -> Write();
	hist_SumdPhi_Jet_Invis -> Write();
	hist_SumdR_Jet_Pho     -> Write();
	hist_SumdR_Jet_Jet     -> Write();
	
	// * Distribution to study the "peak"
	hist_dPhi_Pho_Dijet -> Write();
	hist_dPhi_Invis_All -> Write();
	
	// * Write file
	//file_output -> Write();
	
	// * Close file
	file_output -> Close();
	file_phoSF  -> Close();
	
	printf ("  |-- Done selection, file is saved at: %s\n\n", name_output[fileID-1].Data());
}
