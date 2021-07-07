#ifndef CODEANA_SKIM_C
#define CODEANA_SKIM_C


#include <stdio.h>
#include <iostream>

#include "Plugin/untuplizer_work.h"
#include "RochesterCorrection/RoccoR.cc"

#include "TRandom.h"
#include "TRandom3.h"
#include "TLorentzVector.h"
#include "TMath.h"


#include "Plugin/fileBrowser.h"
#include "Plugin/Tools.h"
#include "Plugin/Selection_Lepton.h"
#include "Plugin/Selection_Photon.h"
#include "Plugin/Selection_JetMET.h"








bool CodeAna_Skim (int year,   bool isMC,   TString name_input,   TString name_output,   Bool_t photonRemoval,   Float_t crossSection)
{
	// * List of variables
	//====================
	// * Timer start
	time_t time_0 = time(0);
	
	// + Variables from input
	//-----------------------
	// * - Global variables
    Double_t   normFactor;
	Int_t      run, nVtx;
	Bool_t     isPVGood;
	Long64_t   event;
	ULong64_t  HLTPho;
	Float_t    rho, vtx, vty, vtz;
	
	// * - LHE particle
	Int_t    nLHE;
	Int_t   *lhePID;
	Float_t *lhePx, *lhePy, *lhePz, *lheE;
	
	// * - Muon related variables
	Int_t    nMu;
	Float_t *muPt, *muEta, *muPhi, *muD0, *muDz;
	Int_t   *muCharge, *muTrkLayers, *muIDbit;
	
	// * - Electron related variables
	Int_t    nEle;
	Float_t *eleCalibPt, *eleEta, *eleSCEta, *elePhi, *eleD0, *eleDz;
	Int_t   *eleIDbit;
	
	// * - Photon related varaibles
	Int_t    nPho;
	Int_t   *phohasPixelSeed;
	Float_t *phoCalibEt, *phoEta, *phoSCEta, *phoPhi, *phoSCPhi, *phoHoverE;
	Float_t *phoSigmaEtaEta, *phoSigmaPhiPhi, *phoPFChWorstIso, *phoPFChIso, *phoPFPhoIso, *phoPFNeuIso, *phoSeedTime;
	
	// * - Jets related varaibles
	Int_t    nJet;
	Int_t   *jetID, *jetGenPID, *jetGenMomID;
	Float_t *jetPt, *jetRawPt, *jetEta, *jetPhi, *jetEn, *jetPUID;
	Float_t *jetGenJetPt, *jetGenJetEta, *jetGenJetPhi, *jetGenJetEn, *jetP4Smear;
	Float_t *jetGenPt, *jetGenEta, *jetGenPhi, *jetGenEn;
	Float_t *jetCHF, *jetNHF, *jetCEF, *jetNEF, *jetMUF;
	Int_t   *jetNCH, *jetNNP;
	
	// * - Missing subject related variables
	Int_t    metFilters;
	Float_t  pfMET, pfMETPhi;
	
	// * - Simualtion related variables
	Int_t     nMC;
	Float_t   genWeight;
	Float_t  *puTrue;
	UShort_t *mcStatusFlag;
	Int_t    *mcPID;
	Float_t  *mcPt, *mcEta, *mcPhi;
	
	
	// + Variables for output
	//-----------------------
	// * - LHE particle
	Int_t  nLHEsel;
	vector<Int_t>    lhePIDsel;
	vector<Float_t>  lhePtsel, lheEtasel, lhePhisel, lheEsel;
	
	// * - Muon related variables
	Int_t  nMusel;
	vector<Float_t>  muPtsel, muCorPtsel, muEtasel, muPhisel, muD0sel, muDzsel;
	vector<Int_t>    muIDbitsel, muChargesel, muTrkLayerssel;
	
	// * - Electron related variables
	Int_t  nElesel;
	vector<Float_t>  eleCalibPtsel, eleEtasel, eleSCEtasel, elePhisel, eleD0sel, eleDzsel;
	vector<Int_t>    eleIDbitsel;
	
	// * - Photon related varaibles
	Int_t  nPhosel;
	vector<Int_t>    phohasPixelSeedsel;
	vector<Float_t>  phoCalibEtsel, phoEtasel, phoSCEtasel, phoPhisel, phoSCPhisel, phoHoverEsel;
	vector<Float_t>  phoSigmaEtaEtasel, phoSigmaPhiPhisel, phoPFChWorstIsosel, phoPFChIsosel, phoPFPhoIsosel, phoPFNeuIsosel, phoSeedTimesel;
	
	// * - Jets related varaibles
	Int_t            nJetsel;
	vector<Int_t>    jetIDsel, jetCorIDsel, jetGenPIDsel, jetGenMomIDsel;
	vector<Float_t>  jetPtsel, jetRawPtsel, jetEtasel, jetPhisel, jetEnsel, jetPUIDsel;
	vector<Float_t>  jetGenJetPtsel, jetGenJetEtasel, jetGenJetPhisel, jetGenJetEnsel, jetP4Smearsel;
	vector<Float_t>  jetGenPtsel, jetGenEtasel, jetGenPhisel, jetGenEnsel;
	
	// * - Missing subject related variables
	Int_t    metFilterssel;
	Float_t  pfMETsel,    pfMETPhisel;
	Float_t  pfMETCorsel, pfMETCorPhisel;
	
	// * - Simualtion related variables
	Int_t             nMCsel;
	Short_t           genWeightsel;
	Float_t           puTruesel;
	vector<UShort_t>  mcStatusFlagsel;
	vector<Int_t>     mcPIDsel;
	vector<Float_t>   mcPtsel, mcEtasel, mcPhisel;
	
	// * - Variables for yield
	Long64_t  nEvent        = 0;
	Long64_t  nEventHLT     = 0;
	Long64_t  nEventPVGood  = 0;
	Long64_t  nEventSkimPho = 0;
	Long64_t  nEventSkimJet = 0;
	Long64_t  nEventSkimMET = 0;
	
	Long64_t  nEventNeg        = 0;
	Long64_t  nEventNegHLT     = 0;
	Long64_t  nEventNegPVGood  = 0;
	Long64_t  nEventNegSkimPho = 0;
	Long64_t  nEventNegSkimJet = 0;
	Long64_t  nEventNegSkimMET = 0;
	
	Double_t  nEventPU        = 0;
	Double_t  nEventPUHLT     = 0;
	Double_t  nEventPUPVGood  = 0;
	Double_t  nEventPUSkimPho = 0;
	Double_t  nEventPUSkimJet = 0;
	Double_t  nEventPUSkimMET = 0;
	
	Double_t  nEventNorm        = 0;
	Double_t  nEventNormHLT     = 0;
	Double_t  nEventNormPVGood  = 0;
	Double_t  nEventNormSkimPho = 0;
	Double_t  nEventNormSkimJet = 0;
	Double_t  nEventNormSkimMET = 0;
	
	
	// + Variables for calculation
	//----------------------------
	TRandom *randRoccor = new TRandom3 ();
	
	
	
	// * Files for input and output
	//=============================
	// * Get the list of input files
	string str_nameInput = name_input.Data();
	string str_fileType = "root";
	vector<string>  list_pathInput = fileBrowser (str_nameInput, str_fileType);
	
	// * Skip if no input found
	unsigned int size_vecInput = list_pathInput . size();
	if (size_vecInput<1)
	{
		printf (" [!] No file found in: [ %s ]\n", name_input.Data());
		return false;
	}
	
	printf (" [+] Open file: [ %s ]\n", name_input.Data());
	// + Input file
	TreeReader file_input (list_pathInput, "ggNtuplizer/EventTree");
	// + Output file
	TFile *file_output = new TFile (name_output, "RECREATE");
	// + Rochester correction
	RoccoR  roccor ("RochesterCorrection/RoccoR2017.txt");
	
	Float_t luminosity;
	
	if (year==2016)   luminosity = 35911;
	if (year==2017)   luminosity = 41526;
	if (year==2018)   luminosity = 59402;
	
	Bool_t  useNewPU = Check_StrInStr ("_newPU_", name_input.Data());
	
	
	
	// * Tree for output
	//==================
	TTree *tree_output1 = new TTree ("tree_Global", "Global information");
	TTree *tree_output2 = new TTree ("tree_Events", "Events information");
	// * - tree1: number of events
	tree_output1 -> Branch ("luminosity",    &luminosity);
	tree_output1 -> Branch ("crossSection",  &crossSection);
	tree_output1 -> Branch ("normFactor",    &normFactor);
	tree_output1 -> Branch ("useNewPU",      &useNewPU);
	
	tree_output1 -> Branch ("nEvent",         &nEvent);
	tree_output1 -> Branch ("nEventHLT",      &nEventHLT);
	tree_output1 -> Branch ("nEventPVGood",   &nEventPVGood);
	tree_output1 -> Branch ("nEventSkimMET",  &nEventSkimMET);
	tree_output1 -> Branch ("nEventSkimPho",  &nEventSkimPho);
	tree_output1 -> Branch ("nEventSkimJet",  &nEventSkimJet);
	
	tree_output1 -> Branch ("nEventNeg",         &nEventNeg);
	tree_output1 -> Branch ("nEventNegHLT",      &nEventNegHLT);
	tree_output1 -> Branch ("nEventNegPVGood",   &nEventNegPVGood);
	tree_output1 -> Branch ("nEventNegSkimMET",  &nEventNegSkimMET);
	tree_output1 -> Branch ("nEventNegSkimPho",  &nEventNegSkimPho);
	tree_output1 -> Branch ("nEventNegSkimJet",  &nEventNegSkimJet);
	
	tree_output1 -> Branch ("nEventPU",         &nEventPU);
	tree_output1 -> Branch ("nEventPUHLT",      &nEventPUHLT);
	tree_output1 -> Branch ("nEventPUPVGood",   &nEventPUPVGood);
	tree_output1 -> Branch ("nEventPUSkimMET",  &nEventPUSkimMET);
	tree_output1 -> Branch ("nEventPUSkimPho",  &nEventPUSkimPho);
	tree_output1 -> Branch ("nEventPUSkimJet",  &nEventPUSkimJet);
	
	tree_output1 -> Branch ("nEventNorm",         &nEventNorm);
	tree_output1 -> Branch ("nEventNormHLT",      &nEventNormHLT);
	tree_output1 -> Branch ("nEventNormPVGood",   &nEventNormPVGood);
	tree_output1 -> Branch ("nEventNormSkimMET",  &nEventNormSkimMET);
	tree_output1 -> Branch ("nEventNormSkimPho",  &nEventNormSkimPho);
	tree_output1 -> Branch ("nEventNormSkimJet",  &nEventNormSkimJet);
	
	// * - tree2: Global variables
	tree_output2 -> Branch ("run",       &run);
	tree_output2 -> Branch ("nVtx",      &nVtx);
	tree_output2 -> Branch ("event",     &event);
	tree_output2 -> Branch ("rho",       &rho);
	tree_output2 -> Branch ("vtx",       &vtx);
	tree_output2 -> Branch ("vty",       &vty);
	tree_output2 -> Branch ("vtz",       &vtz);
	tree_output2 -> Branch ("HLTPho",    &HLTPho);
	// * - tree2: LHE particles
	tree_output2 -> Branch ("nLHE",    &nLHEsel);
	tree_output2 -> Branch ("lhePID",  &lhePIDsel);
	tree_output2 -> Branch ("lhePt",   &lhePtsel);
	tree_output2 -> Branch ("lheEta",  &lheEtasel);
	tree_output2 -> Branch ("lhePhi",  &lhePhisel);
	tree_output2 -> Branch ("lheE",    &lheEsel);
	// * - tree2: Muons
	tree_output2 -> Branch ("nMu",          &nMusel);
	tree_output2 -> Branch ("muPt",         &muPtsel);
	tree_output2 -> Branch ("muCorPt",      &muCorPtsel);
	tree_output2 -> Branch ("muEta",        &muEtasel);
	tree_output2 -> Branch ("muPhi",        &muPhisel);
	tree_output2 -> Branch ("muD0",         &muD0sel);
	tree_output2 -> Branch ("muDz",         &muDzsel);
	tree_output2 -> Branch ("muTrkLayers",  &muTrkLayerssel);
	tree_output2 -> Branch ("muIDbit",      &muIDbitsel);
	tree_output2 -> Branch ("muCharge",     &muChargesel);
	// * - tree2: Elctrons
	tree_output2 -> Branch ("nEle",       &nElesel);
	tree_output2 -> Branch ("eleCalibPt", &eleCalibPtsel);
	tree_output2 -> Branch ("eleEta",     &eleEtasel);
	tree_output2 -> Branch ("eleSCEta",   &eleSCEtasel);
	tree_output2 -> Branch ("elePhi",     &elePhisel);
	tree_output2 -> Branch ("eleD0",      &eleD0sel);
	tree_output2 -> Branch ("eleDz",      &eleDzsel);
	tree_output2 -> Branch ("eleIDbit",   &eleIDbitsel);
	// * - tree2: Photon variables
	tree_output2 -> Branch ("nPho",             &nPhosel);
	tree_output2 -> Branch ("phoCalibEt",       &phoCalibEtsel);
	tree_output2 -> Branch ("phoEta",           &phoEtasel);
	tree_output2 -> Branch ("phoSCEta",         &phoSCEtasel);
	tree_output2 -> Branch ("phoPhi",           &phoPhisel);
	tree_output2 -> Branch ("phoSCPhi",         &phoSCPhisel);
	tree_output2 -> Branch ("phoHoverE",        &phoHoverEsel);
	tree_output2 -> Branch ("phoSigmaEtaEta",   &phoSigmaEtaEtasel);
	tree_output2 -> Branch ("phoSigmaPhiPhi",   &phoSigmaPhiPhisel);
	tree_output2 -> Branch ("phoPFChWorstIso",  &phoPFChWorstIsosel);
	tree_output2 -> Branch ("phoPFChIso",       &phoPFChIsosel);
	tree_output2 -> Branch ("phoPFPhoIso",      &phoPFPhoIsosel);
	tree_output2 -> Branch ("phoPFNeuIso",      &phoPFNeuIsosel);
	tree_output2 -> Branch ("phoSeedTime",      &phoSeedTimesel);
	tree_output2 -> Branch ("phohasPixelSeed",  &phohasPixelSeedsel);
	// * - tree2: Jets related variables
	tree_output2 -> Branch ("nJet",          &nJetsel);
	tree_output2 -> Branch ("jetID",         &jetIDsel);
	tree_output2 -> Branch ("jetCorID",      &jetCorIDsel);
	tree_output2 -> Branch ("jetPt",         &jetPtsel);
	tree_output2 -> Branch ("jetRawPt",      &jetRawPtsel);
	tree_output2 -> Branch ("jetEta",        &jetEtasel);
	tree_output2 -> Branch ("jetPhi",        &jetPhisel);
	tree_output2 -> Branch ("jetEn",         &jetEnsel);
	tree_output2 -> Branch ("jetPUID",       &jetPUIDsel);
	// * - tree2: MET related variables
	tree_output2 -> Branch ("pfMET",       &pfMETsel);
	tree_output2 -> Branch ("pfMETPhi",    &pfMETPhisel);
	tree_output2 -> Branch ("pfMETCor",    &pfMETCorsel);
	tree_output2 -> Branch ("pfMETCorPhi", &pfMETCorPhisel);
	tree_output2 -> Branch ("metFilters",  &metFilterssel);
	// * - tree2: MC related variables
	tree_output2 -> Branch ("genWeight",  &genWeightsel);
	if (isMC)
	{
		tree_output2 -> Branch ("nMC",           &nMCsel);
		tree_output2 -> Branch ("mcPID",         &mcPIDsel);
		tree_output2 -> Branch ("mcPt",          &mcPtsel);
		tree_output2 -> Branch ("mcEta",         &mcEtasel);
		tree_output2 -> Branch ("mcPhi",         &mcPhisel);
		tree_output2 -> Branch ("mcStatusFlag",  &mcStatusFlagsel);
		
		tree_output2 -> Branch ("jetGenJetPt",   &jetGenJetPtsel);
		tree_output2 -> Branch ("jetGenJetEta",  &jetGenJetEtasel);
		tree_output2 -> Branch ("jetGenJetPhi",  &jetGenJetPhisel);
		tree_output2 -> Branch ("jetGenJetEn",   &jetGenJetEnsel);
		
		tree_output2 -> Branch ("jetGenPID",     &jetGenPIDsel);
		tree_output2 -> Branch ("jetGenMomID",   &jetGenMomIDsel);
		tree_output2 -> Branch ("jetGenPt",      &jetGenPtsel);
		tree_output2 -> Branch ("jetGenEta",     &jetGenEtasel);
		tree_output2 -> Branch ("jetGenPhi",     &jetGenPhisel);
		tree_output2 -> Branch ("jetGenEn",      &jetGenEnsel);
		
		tree_output2 -> Branch ("puTrue",        &puTruesel);
	}
	
	
	
	// + Start reading ntuple
	//-----------------------
	nEvent = file_input . GetEntriesFast();
	Long64_t  nEventSub = nEvent/5;
	
	// * Timer middle
	time_t time_1 = time(0);
	
	// * - Main selection
	for (Long64_t ev=0; ev<nEvent; ev++)
	{
		if (ev % nEventSub == 0)   printf ("  |-- This is the event number %lld\n", ev+1);
		file_input . GetEntry (ev);
		
		
		
		// + Get global variables and apply the global cut
		//------------------------------------------------
		// * - Obtain the value
		run      = file_input . GetInt    ("run");
		nVtx     = file_input . GetInt    ("nVtx");
		isPVGood = file_input . GetBool   ("isPVGood");
		event    = file_input . GetLong64 ("event");
		HLTPho   = file_input . GetLong64 ("HLTPho");
		rho      = file_input . GetFloat  ("rho");
		vtx      = file_input . GetFloat  ("vtx");
		vty      = file_input . GetFloat  ("vty");
		vtz      = file_input . GetFloat  ("vtz");
		
		if (isMC == true)
		{
			// * Set generator weight
			genWeight = file_input . GetFloat ("genWeight");
			genWeightsel = (genWeight > 0) ? 1 : -1;
			
			// * Get puTrue info
			puTrue  = file_input . GetPtrFloat ("puTrue");
			
			puTruesel = puTrue[1];
			
		}
		else
		{
			// * Set generator weight
			genWeightsel = 1;
		}
		
		//printf ("done MET selection\n");
		nEventNeg += genWeightsel;
		nEventPU  += genWeightsel;
		
		// * - Apply the Global cut
		bool passHLT;
		
		if (year == 2016)
			passHLT = (HLTPho>>7&1);
		else
			passHLT = (HLTPho>>7&1) || (HLTPho>>10&1);
		
		if (passHLT == false)   continue;
		
		nEventHLT    += 1;
		nEventNegHLT += genWeightsel;
		nEventPUHLT  += genWeightsel;
		
		
		if (isPVGood == false)   continue;
		
		nEventPVGood    += 1;
		nEventNegPVGood += genWeightsel;
		nEventPUPVGood  += genWeightsel;
		//printf ("done global\n");
		
		
		
		// + In & Out for MET
		//-------------------
		pfMET    = file_input . GetFloat ("pfMET");
		pfMETPhi = file_input . GetFloat ("pfMETPhi");
		if (!isMC)
		{
			metFilters = file_input . GetInt ("metFilters");
		}
		else
		{
			metFilters = 0;
		}
		
		pair<double,double>  myMET = METXYCorr (pfMET, pfMETPhi, run, year, isMC, nVtx);
		
		// * - Set value for missing energy
		pfMETsel       = pfMET;
		pfMETPhisel    = pfMETPhi;
		pfMETCorsel    = myMET . first;
		pfMETCorPhisel = myMET . second;
		metFilterssel  = metFilters;
		
		if (pfMETCorsel < 75)   continue;
		
		nEventSkimMET    += 1;
		nEventNegSkimMET += genWeightsel;
		nEventPUSkimMET  += genWeightsel;
		
		
		
		// + Get LHE & generator level particle
		//-------------------------------------
		// * Clear LHE vectors
		lhePIDsel . clear ();
		lhePtsel  . clear ();
		lheEtasel . clear ();
		lhePhisel . clear ();
		lheEsel   . clear ();
		
		// * Clear GEN vectors
		mcPIDsel        . clear ();
		mcPtsel         . clear ();
		mcEtasel        . clear ();
		mcPhisel        . clear ();
		mcStatusFlagsel . clear ();
		
		// * Read data
		if (isMC == true)
		{
			// * LHE level
			nLHE   = file_input . GetInt ("nLHE");
			if (nLHE > 0)
			{
				lhePID = file_input . GetPtrInt   ("lhePID");
				lhePx  = file_input . GetPtrFloat ("lhePx");
				lhePy  = file_input . GetPtrFloat ("lhePy");
				lhePz  = file_input . GetPtrFloat ("lhePz");
				lheE   = file_input . GetPtrFloat ("lheE");
			}
			
			TLorentzVector vec4_LHE;
			
			nLHEsel = nLHE;
			
			for (unsigned int i=0; i<nLHE; i++)
			{
				vec4_LHE . SetPxPyPzE (lhePx[i], lhePy[i], lhePz[i], lheE[i]);
				
				lhePIDsel . push_back (lhePID[i]);
				lhePtsel  . push_back (vec4_LHE.Pt());
				lheEtasel . push_back (vec4_LHE.Eta());
				lhePhisel . push_back (vec4_LHE.Phi());
				lheEsel   . push_back (vec4_LHE.E());
			}
			
			// * Generator level
			nMC          =            file_input . GetInt      ("nMC");
			mcPID        =            file_input . GetPtrInt   ("mcPID");
			mcStatusFlag = (UShort_t*)file_input . GetPtrShort ("mcStatusFlag");
			mcPt         =            file_input . GetPtrFloat ("mcPt");
			mcEta        =            file_input . GetPtrFloat ("mcEta");
			mcPhi        =            file_input . GetPtrFloat ("mcPhi");
			
			nMCsel = nMC;
			for (unsigned int i=0; i<nMC; i++)
			{
				mcPIDsel        . push_back (mcPID[i]);
				mcPtsel         . push_back (mcPt[i]);
				mcEtasel        . push_back (mcEta[i]);
				mcPhisel        . push_back (mcPhi[i]);
				mcStatusFlagsel . push_back (mcStatusFlag[i]);
			}
		}
		
		
		
		// + In & out for electrons
		//-------------------------
		// * Clear electron vectors
		eleCalibPtsel . clear ();
		eleEtasel     . clear ();
		eleSCEtasel   . clear ();
		elePhisel     . clear ();
		//eleEnsel      . clear ();
		eleD0sel      . clear ();
		eleDzsel      . clear ();
		eleIDbitsel   . clear ();
		
		// * Get electron data
		nEle    = file_input . GetInt ("nEle");
		nElesel = nEle;
		
		if (nEle > 0)
		{
			eleCalibPt =          file_input . GetPtrFloat ("eleCalibPt");
			eleEta     =          file_input . GetPtrFloat ("eleEta");
			eleSCEta   =          file_input . GetPtrFloat ("eleSCEta");
			elePhi     =          file_input . GetPtrFloat ("elePhi");
			eleD0      =          file_input . GetPtrFloat ("eleD0");
			eleDz      =          file_input . GetPtrFloat ("eleDz");
			eleIDbit   = (Int_t*) file_input . GetPtrShort ("eleIDbit");
			
			for (int i=0; i<nEle; i++)
			{
				eleCalibPtsel . push_back (eleCalibPt[i]);
				eleEtasel     . push_back (eleEta[i]);
				eleSCEtasel   . push_back (eleSCEta[i]);
				elePhisel     . push_back (elePhi[i]);
				eleD0sel      . push_back (eleD0[i]);
				eleDzsel      . push_back (eleDz[i]);
				eleIDbitsel   . push_back (eleIDbit[i]);
			}
		}
		
		
		
		// + In & Out for muons
		//---------------------
		// * Clear Muon vectors
		muPtsel        . clear ();
		muCorPtsel     . clear ();
		muEtasel       . clear ();
		muPhisel       . clear ();
		muD0sel        . clear ();
		muDzsel        . clear ();
		muIDbitsel     . clear ();
		muChargesel    . clear ();
		muTrkLayerssel . clear ();
		
		// * Get data
		nMu    = file_input . GetInt ("nMu");
		nMusel = nMu;
		
		if (nMu > 0)
		{
			muPt        = file_input . GetPtrFloat ("muPt");
			muEta       = file_input . GetPtrFloat ("muEta");
			muPhi       = file_input . GetPtrFloat ("muPhi");
			muD0        = file_input . GetPtrFloat ("muD0");
			muDz        = file_input . GetPtrFloat ("muDz");
			muIDbit     = file_input . GetPtrInt   ("muIDbit");
			muTrkLayers = file_input . GetPtrInt   ("muTrkLayers");
			muCharge    = file_input . GetPtrInt   ("muCharge");
		}
		
		// * Calculate correction for muon
		for (int i=0; i<nMu; i++)
		{
			float  genPt = -1;
			float  random = randRoccor -> Rndm ();
			float  corfact = 1.0;
			float  muCorPt = 0.0;
			float  minDelR = 0.1;
			
			if (isMC == false)
			{
				corfact = roccor . kScaleDT (muCharge[i], muPt[i], muEta[i], muPhi[i], 0, 0);
			}
			else
			{
				TLorentzVector vector4_mu, vector4_mc;
				vector4_mu . SetPtEtaPhiM (muPt[i], muEta[i], muPhi[i], 105.658);
				
				for (int j=0; j<nMC; j++)
				{
					if (abs(mcPID[j]) != 13)   continue;
					
					vector4_mc . SetPtEtaPhiM (mcPt[j], mcEta[j], mcPhi[j], 105.658);
					float delR = vector4_mu . DeltaR (vector4_mc);
					
					if (delR < minDelR)
					{
						genPt = mcPt[j];
						minDelR = delR;
					}
				}
				
				if (genPt > 0)
				{
					corfact = roccor . kSpreadMC (muCharge[i], muPt[i], muEta[i], muPhi[i], genPt, 0, 0);
				}
				else
				{
					corfact = roccor . kSmearMC (muCharge[i], muPt[i], muEta[i], muPhi[i], muTrkLayers[i], random, 0, 0);
				}
			}
			
			muCorPt = muPt[i] * corfact;
			
			muPtsel        . push_back (muPt[i]);
			muCorPtsel     . push_back (muCorPt);
			muEtasel       . push_back (muEta[i]);
			muPhisel       . push_back (muPhi[i]);
			muD0sel        . push_back (muD0[i]);
			muDzsel        . push_back (muDz[i]);
			muIDbitsel     . push_back (muIDbit[i]);
			muChargesel    . push_back (muCharge[i]);
			muTrkLayerssel . push_back (muTrkLayers[i]);
		}
		
		
		
		// + In & out for photons
		//-----------------------
		// * Clear photon vectors
		phoCalibEtsel      . clear ();
		phoEtasel          . clear ();
		phoSCEtasel        . clear ();
		phoPhisel          . clear ();
		phoSCPhisel        . clear ();
		phoHoverEsel       . clear ();
		phoSigmaEtaEtasel  . clear ();
		phoSigmaPhiPhisel  . clear ();
		phoPFChWorstIsosel . clear ();
		phoPFChIsosel      . clear ();
		phoPFPhoIsosel     . clear ();
		phoPFNeuIsosel     . clear ();
		phoSeedTimesel     . clear ();
		phohasPixelSeedsel . clear ();
		
		// * Get data
		vector<int>  phoIndex;
		phoIndex . clear ();
		
		nPho            = file_input . GetInt      ("nPho");
		phoCalibEt      = file_input . GetPtrFloat ("phoCalibEt");
		phoEta          = file_input . GetPtrFloat ("phoEta");
		phoSCEta        = file_input . GetPtrFloat ("phoSCEta");
		phoPhi          = file_input . GetPtrFloat ("phoPhi");
		phoSCPhi        = file_input . GetPtrFloat ("phoSCPhi");
		phoHoverE       = file_input . GetPtrFloat ("phoHoverE");
		phoSigmaEtaEta  = file_input . GetPtrFloat ("phoSigmaIEtaIEtaFull5x5");
		phoSigmaPhiPhi  = file_input . GetPtrFloat ("phoSigmaIPhiIPhiFull5x5");
		phoPFChWorstIso = file_input . GetPtrFloat ("phoPFChWorstIso");
		phoPFChIso      = file_input . GetPtrFloat ("phoPFChIso");
		phoPFPhoIso     = file_input . GetPtrFloat ("phoPFPhoIso");
		phoPFNeuIso     = file_input . GetPtrFloat ("phoPFNeuIso");
		phoSeedTime     = file_input . GetPtrFloat ("phoSeedTime");
		phohasPixelSeed = file_input . GetPtrInt   ("phohasPixelSeed");
		
		// * - Photon selection
		Select_MonoPhoton_SkimZgVBS (file_input, photonRemoval, phoIndex);
		if (phoIndex.size() == 0)   continue;
		
		// * - Fill photon vectors
		nPhosel = phoIndex . size ();
		for (unsigned int i=0; i<phoIndex.size(); i++)
		{
			phoCalibEtsel      . push_back (phoCalibEt[phoIndex[i]]);
			phoEtasel          . push_back (phoEta[phoIndex[i]]);
			phoSCEtasel        . push_back (phoSCEta[phoIndex[i]]);
			phoPhisel          . push_back (phoPhi[phoIndex[i]]);
			phoSCPhisel        . push_back (phoSCPhi[phoIndex[i]]);
			phoHoverEsel       . push_back (phoHoverE[phoIndex[i]]);
			phoSigmaEtaEtasel  . push_back (phoSigmaEtaEta[phoIndex[i]]);
			phoSigmaPhiPhisel  . push_back (phoSigmaPhiPhi[phoIndex[i]]);
			phoPFChWorstIsosel . push_back (phoPFChWorstIso[phoIndex[i]]);
			phoPFChIsosel      . push_back (phoPFChIso[phoIndex[i]]);
			phoPFPhoIsosel     . push_back (phoPFPhoIso[phoIndex[i]]);
			phoPFNeuIsosel     . push_back (phoPFNeuIso[phoIndex[i]]);
			phoSeedTimesel     . push_back (phoSeedTime[phoIndex[i]]);
			phohasPixelSeedsel . push_back (phohasPixelSeed[phoIndex[i]]);
		}
		//printf ("done photon selection\n");
		
		nEventSkimPho    += 1;
		nEventNegSkimPho += genWeightsel;
		nEventPUSkimPho  += genWeightsel;
		
		
		
		// + In & out for jets
		//--------------------
		// * Clear jet vectors
		jetIDsel        . clear ();
		jetCorIDsel     . clear ();
		jetPtsel        . clear ();
		jetRawPtsel     . clear ();
		jetEtasel       . clear ();
		jetPhisel       . clear ();
		jetEnsel        . clear ();
		jetPUIDsel      . clear ();
		jetGenPtsel     . clear ();
		jetGenEtasel    . clear ();
		jetGenPhisel    . clear ();
		jetGenEnsel     . clear ();
		jetP4Smearsel   . clear ();
		jetGenPIDsel    . clear ();
		jetGenMomIDsel  . clear ();
		jetGenJetPtsel  . clear ();
		jetGenJetEtasel . clear ();
		jetGenJetPhisel . clear ();
		jetGenJetEnsel  . clear ();
		
		// * Get data
		vector<int>  jetIndex;
		jetIndex . clear ();
		
		nJet     = file_input . GetInt      ("nJet");
		jetID    = file_input . GetPtrInt   ("jetID");
		jetPt    = file_input . GetPtrFloat ("jetPt");
		jetRawPt = file_input . GetPtrFloat ("jetRawPt");
		jetEta   = file_input . GetPtrFloat ("jetEta");
		jetPhi   = file_input . GetPtrFloat ("jetPhi");
		jetEn    = file_input . GetPtrFloat ("jetEn");
		jetPUID  = file_input . GetPtrFloat ("jetPUID");
		jetCHF   = file_input . GetPtrFloat ("jetCHF");
		jetNHF   = file_input . GetPtrFloat ("jetNHF");
		jetCEF   = file_input . GetPtrFloat ("jetCEF");
		jetNEF   = file_input . GetPtrFloat ("jetNEF");
		jetMUF   = file_input . GetPtrFloat ("jetMUF");
		jetNCH   = file_input . GetPtrInt   ("jetNCH");
		jetNNP   = file_input . GetPtrInt   ("jetNNP");
		if (isMC)
		{
			jetGenPt     = file_input . GetPtrFloat ("jetGenPt");
			jetGenEta    = file_input . GetPtrFloat ("jetGenEta");
			jetGenPhi    = file_input . GetPtrFloat ("jetGenPhi");
			jetGenEn     = file_input . GetPtrFloat ("jetGenEn");
			jetP4Smear   = file_input . GetPtrFloat ("jetP4Smear");
			jetGenPID    = file_input . GetPtrInt   ("jetGenPartonID");
			jetGenMomID  = file_input . GetPtrInt   ("jetGenPartonMomID");
			jetGenJetPt  = file_input . GetPtrFloat ("jetGenJetPt");
			jetGenJetEta = file_input . GetPtrFloat ("jetGenJetEta");
			jetGenJetPhi = file_input . GetPtrFloat ("jetGenJetPhi");
			jetGenJetEn  = file_input . GetPtrFloat ("jetGenJetEn");
		}
		// * - Jet selection
		Select_Jet_SkimZgVBS (file_input, jetIndex, isMC);
		if (jetIndex.size() < 2)   continue;
		
		// * - Fill vector of jets
		nJetsel = jetIndex . size ();
		for (UInt_t i=0; i<jetIndex.size(); i++)
		{
			bool  isLooseID     = 0;
			bool  isTightID     = 0;
			bool  isTightVetoID = 0;
			Int_t tmpJetCorID   = 0;
			
			float CHF = jetCHF[jetIndex[i]];
			float NHF = jetNHF[jetIndex[i]];
			float CEF = jetCEF[jetIndex[i]];
			float NEF = jetNEF[jetIndex[i]];
			float MUF = jetMUF[jetIndex[i]];
			int   NCH = jetNCH[jetIndex[i]];
			int   NNP = jetNNP[jetIndex[i]];
			
			if (year == 2016)
			{
				if (abs(jetEta[jetIndex[i]]) < 2.4)
				{
					isLooseID     = (NHF<0.99  &&  NEF<0.99  &&  (NCH+NNP)>1  &&  CHF>0  &&  NCH>0  &&  CEF<0.99);
					isTightID     = (NHF<0.90  &&  NEF<0.90  &&  (NCH+NNP)>1  &&  CHF>0  &&  NCH>0  &&  CEF<0.99);
					isTightVetoID = (NHF<0.90  &&  NEF<0.90  &&  (NCH+NNP)>1  &&  MUF<0.8  &&  CHF>0  &&  NCH>0  &&  CEF<0.90);
				}
				else if (abs(jetEta[jetIndex[i]]) < 2.7)
				{
					isLooseID     = (NHF<0.99  &&  NEF<0.99  &&  (NCH+NNP)>1);
					isTightID     = (NHF<0.90  &&  NEF<0.90  &&  (NCH+NNP)>1);
					isTightVetoID = (NHF<0.90  &&  NEF<0.90  &&  (NCH+NNP)>1  &&  MUF<0.8);
				}
				else if (abs(jetEta[jetIndex[i]]) < 3.0)
				{
					isLooseID     = (NEF>0.01  &&  NHF<0.98  &&  NNP>2);
					isTightID     = (NEF>0.01  &&  NHF<0.98  &&  NNP>2);
					isTightVetoID = (NEF>0.01  &&  NHF<0.98  &&  NNP>2);
				}
				else
				{
					isLooseID     = (NEF<0.9  &&  NNP>10);
					isTightID     = (NEF<0.9  &&  NNP>10);
					isTightVetoID = (NEF<0.9  &&  NNP>10);
				}
			}
			else if (year == 2017)
			{
				if (abs(jetEta[jetIndex[i]]) < 2.4)
				{
					isLooseID     = 1;
					isTightID     = (NHF<0.90  &&  NEF<0.90  &&  (NCH+NNP)>1  &&  CHF>0  &&  NCH>0);
					isTightVetoID = (NHF<0.90  &&  NEF<0.90  &&  (NCH+NNP)>1  &&  MUF<0.8  &&  CHF>0  &&  NCH>0  &&  CEF<0.80);
				}
				else if (abs(jetEta[jetIndex[i]]) < 2.7)
				{
					isLooseID     = 1;
					isTightID     = (NHF<0.90  &&  NEF<0.90  &&  (NCH+NNP)>1);
					isTightVetoID = (NHF<0.90  &&  NEF<0.90  &&  (NCH+NNP)>1  &&  MUF<0.8);
				}
				else if (abs(jetEta[jetIndex[i]]) < 3.0)
				{
					isLooseID     = 1;
					isTightID     = (NEF>0.02  &&  NEF<0.99  &&  NNP>2);
					isTightVetoID = (NEF>0.02  &&  NEF<0.99  &&  NNP>2);
				}
				else
				{
					isLooseID     = 1;
					isTightID     = (NEF<0.9  &&  NHF>0.02  &&  NNP>10);
					isTightVetoID = (NEF<0.9  &&  NHF>0.02  &&  NNP>10);
				}
			}
			else if (year == 2018)
			{
				if (abs(jetEta[jetIndex[i]]) < 2.6)
				{
					isLooseID     = 1;
					isTightID     = (NHF<0.90  &&  NEF<0.90  &&  (NCH+NNP)>1  &&  CHF>0  &&  NCH>0);
					isTightVetoID = (NHF<0.90  &&  NEF<0.90  &&  (NCH+NNP)>1  &&  MUF<0.8  &&  CHF>0  &&  NCH>0  &&  CEF<0.80);
				}
				else if (abs(jetEta[jetIndex[i]]) < 2.7)
				{
					isLooseID     = 1;
					isTightID     = (NHF<0.90  &&  NEF<0.99  &&  NCH>0);
					isTightVetoID = (NHF<0.90  &&  NEF<0.99  &&  MUF<0.8  &&  NCH>0);
				}
				else if (abs(jetEta[jetIndex[i]]) < 3.0)
				{
					isLooseID     = 1;
					isTightID     = (NEF>0.02  &&  NEF<0.99  &&  NNP>2);
					isTightVetoID = (NEF>0.02  &&  NEF<0.99  &&  NNP>2);
				}
				else
				{
					isLooseID     = 1;
					isTightID     = (NEF<0.9  &&  NHF>0.2  &&  NNP>10);
					isTightVetoID = (NEF<0.9  &&  NHF>0.2  &&  NNP>10);
				}
			}
			
			if (isLooseID == 1)   tmpJetCorID += pow(2,1);
			if (isTightID == 1)   tmpJetCorID += pow(2,2);
			if (isTightVetoID == 1)   tmpJetCorID += pow(2,3);
			
			Float_t jetSmearFactor = (isMC==true) ? jetP4Smear[jetIndex[i]] : 1.0;
			if (jetSmearFactor < 0.0)   jetSmearFactor = 0;
			
			Float_t jetCorPt = jetPt[jetIndex[i]] * jetSmearFactor;
			Float_t jetCorEn = jetEn[jetIndex[i]] * jetSmearFactor;
			
			jetIDsel    . push_back (jetID[jetIndex[i]]);
			jetCorIDsel . push_back (tmpJetCorID);
			jetPtsel    . push_back (jetCorPt);
			jetRawPtsel . push_back (jetRawPt[jetIndex[i]]);
			jetEtasel   . push_back (jetEta[jetIndex[i]]);
			jetPhisel   . push_back (jetPhi[jetIndex[i]]);
			jetEnsel    . push_back (jetCorEn);
			jetPUIDsel  . push_back (jetPUID[jetIndex[i]]);
			if (isMC)
			{
				jetGenPIDsel    . push_back (jetGenPID[jetIndex[i]]);
				jetGenMomIDsel  . push_back (jetGenMomID[jetIndex[i]]);
				jetGenPtsel     . push_back (jetGenPt[jetIndex[i]]);
				jetGenEtasel    . push_back (jetGenEta[jetIndex[i]]);
				jetGenPhisel    . push_back (jetGenPhi[jetIndex[i]]);
				jetGenEnsel     . push_back (jetGenEn[jetIndex[i]]);
				jetGenJetPtsel  . push_back (jetGenJetPt[jetIndex[i]]);
				jetGenJetEtasel . push_back (jetGenJetEta[jetIndex[i]]);
				jetGenJetPhisel . push_back (jetGenJetPhi[jetIndex[i]]);
				jetGenJetEnsel  . push_back (jetGenJetEn[jetIndex[i]]);
			}
		}
		
		//printf ("done jet selection\n");
		
		nEventSkimJet    += 1;
		nEventNegSkimJet += genWeightsel;
		nEventPUSkimJet  += genWeightsel;
		
		
		
		// * Fill the tree
		//----------------
		tree_output2 -> Fill ();
		//printf ("done fill tree\n");
	}
	
	
	
	// + Calculate the normalization factor
	//-------------------------------------
	normFactor = (isMC) ? luminosity*crossSection/nEventNeg : 1.0;
	
	nEventNorm        = normFactor * nEventPU;
	nEventNormHLT     = normFactor * nEventPUHLT;
	nEventNormPVGood  = normFactor * nEventPUPVGood;
	nEventNormSkimMET = normFactor * nEventPUSkimMET;
	nEventNormSkimPho = normFactor * nEventPUSkimPho;
	nEventNormSkimJet = normFactor * nEventPUSkimJet;
	
	tree_output1 -> Fill ();
	
	tree_output1 -> Write("", TObject::kOverwrite);
	tree_output2 -> Write("", TObject::kOverwrite);
	delete tree_output1;
	delete tree_output2;
	delete file_output;
	
	// * Timer end
	time_t time_2 = time(0);
	
	float time_prep = float(time_1 - time_0) / 3600.0;
	float time_proc = float(time_2 - time_1) / 3600.0;
	float time_task = float(time_2 - time_0) / 3600.0;
	
	printf (" [$] Job's done, processing.\n");
	printf ("  |-- Task time: [ %.2f hrs ]; Prep time: [ %.2f hrs ]; Proc time: [ %.2f hrs ]\n", time_task, time_prep, time_proc);
	printf ("  |-- Number of selected events [ %lld ] / [ %lld ]\n\n", nEventSkimMET, nEvent);
	
	return true;
}

#endif
