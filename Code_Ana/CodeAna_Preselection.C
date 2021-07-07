#ifndef XANA_EVENTSELECTION_H
#define XANA_EVENTSELECTION_H

#include <stdio.h>
#include <iostream>

#include "TRandom.h"
#include "TLorentzVector.h"
#include "TTree.h"
#include "TSystem.h"
#include "TMath.h"
#include "TRandom3.h"

#include "Plugin/untuplizer_work.h"
//#include "Plugin/untuplizer_v08.h"
#include "Plugin/Tools.h"
#include "Plugin/Selection_Lepton.h"
#include "Plugin/Selection_Photon.h"
#include "Plugin/Selection_JetMET.h"

#include "Plugin/puweicalc.h"





void CodeAna_Preselection (int year,   bool isMC,   TString name_input,   TString name_output)
{
	// * List of variables
	//====================
	// * Timer start
	time_t time_0 = time(0);
	
	
	
	// + NOTE this is a cheat to use 2017 MC
	//        Must be removed when the correct MCs arrive
	//---------------------------------------------------
	//if (isMC)   year = 2017;
	bool isSignal = false;
	if (name_input.Contains("tree2017_Z2nuGammaEWK"))
	{
		printf (" [+] Processing signal sample");
		year = 2018;
		isSignal = true;
	}
	
	bool isDiboson = false;
	if (name_input.Contains("_WW.root")  ||  name_input.Contains("_WZ.root"))
	{
		printf (" [+] Processing diboson sample");
		isDiboson = true;
	}
	
	
	
	// * Create neccesary derectories
	//-------------------------------
	system ("mkdir -p /home/hoa/Task_ZgVBS/Output/Tree_preselMC");
	system ("mkdir -p /home/hoa/Task_ZgVBS/Output/Tree_preselDT");
	
	
	
	// * List of in put variables
	//---------------------------
	// * Global variables
	Int_t      run, nVtx;
	Bool_t     isPVGood;
	Long64_t   event;
	ULong64_t  HLTPho;
	Float_t    rho;
	Short_t    genWei;
	
	// * Photon related varaibles
	Int_t    nPho;
	Float_t *phoCalibEt, *phoEta, *phoPhi, *phoHoverE, *phoSigmaEtaEta, *phoSigmaPhiPhi, *phoPFChWorstIso, *phoPFPhoIso, *phoPFNeuIso, *phoSeedTime;
	Int_t   *phohasPixelSeed;
	
	// * Jets related varaibles
	Int_t    nJet;
	Float_t *jetPt, *jetEta, *jetPhi, *jetEn, *jetPUID;
	Int_t   *jetCorID;
	
	// * Missing subject related variables
	Int_t    metFilters;
	Float_t  pfMET,    pfMETPhi;
	Float_t  pfMETCor, pfMETCorPhi;
	
	// * Charged lepton related variables
	Int_t    nEle, nMu;
	Float_t *eleCalibPt, *muPt, *muEta, *muPhi;
	Int_t   *muCharge, *muTrkLayers;
	
	// * Simualtion related variables
	Int_t    nMC;
	Int_t   *mcPID;
	Float_t *mcPt, *mcEta, *mcPhi;
	
	
	
	// + Variables for calculaition
	//-----------------------------
	vector<Float_t>  muCorPt;
	vector<Int_t>    phoID;
	vector<Int_t>    jetID;
	vector<vector<Int_t>>  jetpairID;
	TRandom *randRoccor = new TRandom3 ();
	
	
	
	// + Variables for output
	//-----------------------
	// * Lepton related variables
	Int_t  nElesel, nMusel;
	
	// * Photon related varaibles
	Int_t  nPhosel;
	vector<Float_t>  phoCalibEtsel, phoEtasel, phoPhisel, phoHoverEsel, phoSigmaEtaEtasel, phoSigmaPhiPhisel, phoPFChWorstIsosel, phoPFChIsosel, phoPFPhoIsosel, phoPFNeuIsosel, phoSeedTimesel;
	vector<Bool_t>   phohasPixelSeedsel;
	
	// * Jets related varaibles
	Int_t            nJetsel;
	vector<Float_t>  jetPtsel, jetEtasel, jetPhisel, jetEnsel, jetPUIDsel;
	vector<Int_t>    jetCorIDsel;
	
	// * Missing subject related variables
	Float_t  pfMETsel,    pfMETPhisel;
	Float_t  pfMETCorsel, pfMETCorPhisel;
	
	// * Scale factor and MC weight
	Short_t  genWeight;
	Float_t  puTruesel;
	Float_t *arr_puTrue;
	Float_t  puWeight0;
	
	// * Variables for yield
	Float_t   luminosity   = 0;
	Float_t   crossSection = 0;
	Double_t  normFactor   = 0;
	Bool_t    useNewPU;
	
	Long64_t  nEvent        = 0;
	Long64_t  nEventHLT     = 0;
	Long64_t  nEventPVGood  = 0;
	Long64_t  nEventSkimPho = 0;
	Long64_t  nEventSkimJet = 0;
	Long64_t  nEventSkimMET = 0;
	Long64_t  nEventLepVeto = 0;
	Long64_t  nEventPassPho = 0;
	Long64_t  nEventPassJet = 0;
	Long64_t  nEventPassMET = 0;
	
	Long64_t  nEventNeg        = 0;
	Long64_t  nEventNegHLT     = 0;
	Long64_t  nEventNegPVGood  = 0;
	Long64_t  nEventNegSkimPho = 0;
	Long64_t  nEventNegSkimJet = 0;
	Long64_t  nEventNegSkimMET = 0;
	Long64_t  nEventNegLepVeto = 0;
	Long64_t  nEventNegPassPho = 0;
	Long64_t  nEventNegPassJet = 0;
	Long64_t  nEventNegPassMET = 0;
	
	Double_t  nEventPU        = 0;
	Double_t  nEventPUHLT     = 0;
	Double_t  nEventPUPVGood  = 0;
	Double_t  nEventPUSkimPho = 0;
	Double_t  nEventPUSkimJet = 0;
	Double_t  nEventPUSkimMET = 0;
	Double_t  nEventPULepVeto = 0;
	Double_t  nEventPUPassPho = 0;
	Double_t  nEventPUPassJet = 0;
	Double_t  nEventPUPassMET = 0;
	
	Double_t  nEventNorm        = 0;
	Double_t  nEventNormHLT     = 0;
	Double_t  nEventNormPVGood  = 0;
	Double_t  nEventNormSkimPho = 0;
	Double_t  nEventNormSkimJet = 0;
	Double_t  nEventNormSkimMET = 0;
	Double_t  nEventNormLepVeto = 0;
	Double_t  nEventNormPassPho = 0;
	Double_t  nEventNormPassJet = 0;
	Double_t  nEventNormPassMET = 0;
	
	Float_t  nVtxLepVeto = 0;
	Float_t  nVtxPassPho = 0;
	Float_t  nVtxPassJet = 0;
	Float_t  nVtxPassMET = 0;
	
	
	
	// + Files for input and output
	//-----------------------------
	printf (" [+] Reading file: [ %s ]\n", name_input.Data());
	// * Input file
	TreeReader file_input1 (name_input, "tree_Global");
	TreeReader file_input2 (name_input, "tree_Events");
	// * Output file
	TFile *file_output = new TFile (name_output, "RECREATE");
	
	
	
	// + Tree for output
	//------------------
	TTree *tree_output1 = new TTree ("tree_Global", "Global info from ggNtuples");
	TTree *tree_output2 = new TTree ("tree_Events", "Output mini tree from ggNtuples");
	
	// * Information tree
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
	
	tree_output1 -> Branch ("nVtxLepVeto",  &nVtxLepVeto);
	tree_output1 -> Branch ("nVtxPassPho",  &nVtxPassPho);
	tree_output1 -> Branch ("nVtxPassJet",  &nVtxPassJet);
	tree_output1 -> Branch ("nVtxPassMET",  &nVtxPassMET);
	
	// * Global variables
	tree_output2 -> Branch ("nVtx",       &nVtx);
	
	// * Photon variables
	tree_output2 -> Branch ("nPho",             &nPhosel);
	tree_output2 -> Branch ("phoCalibEt",       &phoCalibEtsel);
	tree_output2 -> Branch ("phoEta",           &phoEtasel);
	tree_output2 -> Branch ("phoPhi",           &phoPhisel);
	
	// * Jets related variables
	tree_output2 -> Branch ("nJet",      &nJetsel);
	tree_output2 -> Branch ("jetPt",     &jetPtsel);
	tree_output2 -> Branch ("jetEta",    &jetEtasel);
	tree_output2 -> Branch ("jetPhi",    &jetPhisel);
	tree_output2 -> Branch ("jetEn",     &jetEnsel);
	
	// * MET related variables
	tree_output2 -> Branch ("pfMET",        &pfMETsel);
	tree_output2 -> Branch ("pfMETPhi",     &pfMETPhisel);
	tree_output2 -> Branch ("pfMETCor",     &pfMETCorsel);
	tree_output2 -> Branch ("pfMETCorPhi",  &pfMETCorPhisel);
	
	// * Weight related variables
	tree_output2 -> Branch ("genWeight",  &genWeight);
	tree_output2 -> Branch ("puWeight0",  &puWeight0);
	if (isMC)
	{
		tree_output2 -> Branch ("puTrue",   &puTruesel);
	}
	
	
	
	// * Start reading ntuple
	//-----------------------
	Long64_t nEventLocal = file_input2 . GetEntriesFast();
	printf ("  |-- There are %lld events to processed\n", nEventLocal);
	
	Long64_t nEventSub = nEventLocal/10;
	if (nEventSub == 0)   nEventSub = 1;
	
	
	// * Get the global information
	file_input1 . GetEntry (0);
	
	luminosity   = file_input1 . GetFloat  ("luminosity");
	crossSection = file_input1 . GetFloat  ("crossSection");
	normFactor   = file_input1 . GetDouble ("normFactor");
	useNewPU     = (isSignal) ? false : file_input1 . GetBool ("useNewPU");
	
	nEvent        = file_input1 . GetLong64 ("nEvent");
	nEventHLT     = file_input1 . GetLong64 ("nEventHLT");
	nEventPVGood  = file_input1 . GetLong64 ("nEventPVGood");
	nEventSkimPho = file_input1 . GetLong64 ("nEventSkimPho");
	nEventSkimJet = file_input1 . GetLong64 ("nEventSkimJet");
	nEventSkimMET = file_input1 . GetLong64 ("nEventSkimMET");
	
	nEventNeg        = file_input1 . GetLong64 ("nEventNeg");
	nEventNegHLT     = file_input1 . GetLong64 ("nEventNegHLT");
	nEventNegPVGood  = file_input1 . GetLong64 ("nEventNegPVGood");
	nEventNegSkimPho = file_input1 . GetLong64 ("nEventNegSkimPho");
	nEventNegSkimJet = file_input1 . GetLong64 ("nEventNegSkimJet");
	nEventNegSkimMET = file_input1 . GetLong64 ("nEventNegSkimMET");
	
	nEventPU        = file_input1 . GetDouble ("nEventPU");
	nEventPUHLT     = file_input1 . GetDouble ("nEventPUHLT");
	nEventPUPVGood  = file_input1 . GetDouble ("nEventPUPVGood");
	nEventPUSkimPho = file_input1 . GetDouble ("nEventPUSkimPho");
	nEventPUSkimJet = file_input1 . GetDouble ("nEventPUSkimJet");
	nEventPUSkimMET = file_input1 . GetDouble ("nEventPUSkimMET");
	
	nEventNorm        = file_input1 . GetDouble ("nEventNorm");
	nEventNormHLT     = file_input1 . GetDouble ("nEventNormHLT");
	nEventNormPVGood  = file_input1 . GetDouble ("nEventNormPVGood");
	nEventNormSkimPho = file_input1 . GetDouble ("nEventNormSkimPho");
	nEventNormSkimJet = file_input1 . GetDouble ("nEventNormSkimJet");
	nEventNormSkimMET = file_input1 . GetDouble ("nEventNormSkimMET");
	
	//printf ("number of weighted events: %lld, normFactor: %.4f\n", nEventNorm, normFactor);
	
	
	
	// + Read the pileup file
	//-----------------------
	PUWeightCalculator puCalc0;
	
	if (isMC)
	{
		if (year == 2016)
		{
			puCalc0 . Init ("/home/hoa/Task_ZgVBS/Code_Ana/PileupWeight/summer16/PU_histo_13TeV_2016_GoldenJSON_69200nb.root");
		}
		
		else if (year == 2017)
		{
			if (!useNewPU)
			{
				puCalc0 . Init ("/home/hoa/Task_ZgVBS/Code_Ana/PileupWeight/fall17/PU_histo_13TeV_2017_GoldenJSON_69200nb.root");
			}
			else
			{
				puCalc0 . Init ("/home/hoa/Task_ZgVBS/Code_Ana/PileupWeight/fall17_corrected/PU_correctedPU_13TeV_2017_GoldenJSON_69200nb.root");
			}
		}
		
		else if (year == 2018)
		{
			puCalc0 . Init ("/home/hoa/Task_ZgVBS/Code_Ana/PileupWeight/autumn18/PU_histo_13TeV_2018_GoldenJSON_69200nb.root");
		}
	}
	
	
	
	// + Main selection
	//-----------------
	for (Long64_t ev=0; ev<nEventLocal; ev++)
	{
		//if (ev%nEventSub==0)   printf ("  |-- This is the event number %lld\n", ev+1);
		file_input2 . GetEntry (ev);
		
		
		
		// + Get global variables and apply the global cut
		//------------------------------------------------
		run    = (isSignal) ? 1 : file_input2 . GetInt    ("run");
		event  = (isSignal) ? 1 : file_input2 . GetLong64 ("event");
		rho    = (isSignal) ? 1 : file_input2 . GetFloat  ("rho");
		HLTPho = (isSignal) ? 0 : file_input2 . GetLong64 ("HLTPho");
		nVtx   = file_input2 . GetInt ("nVtx");
		
		// * Apply HLT cut
		bool passHLT;
		
		if (year == 2016)
			passHLT = (HLTPho>>7&1) || isSignal;
		else
			passHLT = (HLTPho>>10&1) || isSignal || ((HLTPho>>7&1) && isDiboson);
		
		if (passHLT == false)   continue;
		
		// * Get the weight
		if (isMC == true)
		{
			genWeight = file_input2 . GetShort ("genWeight");
			
			if (!isSignal)
			{
				puTruesel  = file_input2 . GetFloat ("puTrue");
				puWeight0 = (float)puCalc0 . GetWeight (run, puTruesel);
			}
			else
			{
				arr_puTrue  = file_input2 . GetPtrFloat ("puTrue");
				puTruesel = arr_puTrue[1];
				puWeight0 = (float)puCalc0 . GetWeight (run, puTruesel);
			}
		}
		else
		{
			genWeight = 1.0;
			puWeight0 = 1.0;
		}
		
		
		
		// + Get the leptons
		//------------------
		nEle = file_input2 . GetInt ("nEle");
		nMu  = file_input2 . GetInt ("nMu");
		
		nElesel = 0;
		nMusel  = 0;
		
		// * Veto electron
		if (nEle == 0)
		{
			nElesel = 0;
		}
		else
		{
			nElesel = Veto_ElectronLooseID (file_input2);
		}
		if (nElesel > 0)  continue;
		
		// * Veto muon
		if (nMu == 0)
		{
			nMusel = 0;
		}
		else
		{
			nMusel = Veto_MuonLooseID (file_input2);
		}
		if (nMusel > 0)  continue;
		
		nEventLepVeto    += 1;
		nEventNegLepVeto += genWeight;
		nEventPULepVeto  += genWeight*puWeight0;
		nVtxLepVeto      += nVtx*genWeight*puWeight0;
		//printf ("done veto lepton\n");
		
		
		
		// + Photon selection
		//-------------------
		// * Clear photon vectors
		phoCalibEtsel      . clear ();
		phoEtasel          . clear ();
		phoPhisel          . clear ();
		
		// * Get data
		phoCalibEt      = file_input2 . GetPtrFloat ("phoCalibEt");
		phoEta          = file_input2 . GetPtrFloat ("phoEta");
		phoPhi          = file_input2 . GetPtrFloat ("phoPhi");
		
		// * Apply selection
		phoID . clear ();
		Select_Photon_EGMediumID (file_input2, phoID);
		
		if (phoID.size() == 0)   continue;
		
		nEventPassPho    += 1;
		nEventNegPassPho += genWeight;
		nEventPUPassPho  += genWeight*puWeight0;
		nVtxPassPho      += nVtx*genWeight*puWeight0;
		//printf ("done phton\n");
		
		
		
		// + Jet selection
		//----------------
		// * Jets
		jetPtsel    . clear ();
		jetEtasel   . clear ();
		jetPhisel   . clear ();
		jetEnsel    . clear ();
		//jetCorIDsel . clear ();
		//jetPUIDsel  . clear ();
		
		//nJet     = file_input2 . GetInt      ("nJet");
		jetPt    = file_input2 . GetPtrFloat ("jetPt");
		jetEta   = file_input2 . GetPtrFloat ("jetEta");
		jetPhi   = file_input2 . GetPtrFloat ("jetPhi");
		jetEn    = file_input2 . GetPtrFloat ("jetEn");
		//jetCorID = file_input2 . GetPtrInt   ("jetCorID");
		//jetPUID  = file_input2 . GetPtrFloat ("jetPUID");
		
		// * Jet selection
		jetID . clear ();
		Select_Jet_ZgVBSTight (year, file_input2, jetID);
		
		if (jetID.size() < 2)   continue;
		
		nEventPassJet    += 1;
		nEventNegPassJet += genWeight;
		nEventPUPassJet  += genWeight*puWeight0;
		nVtxPassJet      += nVtx*genWeight*puWeight0;
		//printf ("done jet\n");
		
		
		
		// + MET selection
		//----------------
		// * Set initial value
		metFilters = 0;
		pfMETPhi   = 0.0;
		pfMET      = 0.0;
		
		// * Get data
		metFilters  = file_input2 . GetInt   ("metFilters");
		pfMET       = file_input2 . GetFloat ("pfMET");
		pfMETPhi    = file_input2 . GetFloat ("pfMETPhi");
		pfMETCor    = file_input2 . GetFloat ("pfMETCor");
		pfMETCorPhi = file_input2 . GetFloat ("pfMETCorPhi");
		
		// * - PF Missing Et selection
		int  nFailedFilter = 0;
		bool passFilter;
		
		if (isMC==false)
		{
			for (unsigned int indexFilter = 0; indexFilter<9; indexFilter++)
			{
				if (year == 2016)
				{
					passFilter = !(metFilters>>(indexFilter+1) & 1);
				}
				else
				{
					passFilter = (indexFilter == 7) ? (metFilters>>(indexFilter+1) & 1) : !(metFilters>>(indexFilter+1) & 1);
				}
				
				if (!passFilter)   nFailedFilter ++;
			}
		}
		
		if (nFailedFilter > 0)   continue;
		if (pfMET < 20)   continue;
		
		nEventPassMET    += 1;
		nEventNegPassMET += genWeight;
		nEventPUPassMET  += genWeight*puWeight0;
		nVtxPassMET      += nVtx*genWeight*puWeight0;
		
		
		
		// + Fill the vector / Set value for output
		//-----------------------------------------
		// * Set value for photon
		nPhosel = phoID . size ();
		for (UInt_t j=0; j<phoID.size(); j++)
		{
			phoCalibEtsel      . push_back (phoCalibEt[phoID[j]]);
			phoEtasel          . push_back (phoEta[phoID[j]]);
			phoPhisel          . push_back (phoPhi[phoID[j]]);
		}
		
		// * Fill vector of jets
		nJetsel = jetID . size ();
		for (UInt_t j=0; j<jetID.size(); j++)
		{
			//printf ("ID of the jet to be filled: %d\n", jetIDseppho[j]);
			jetPtsel  . push_back (jetPt[jetID[j]]);
			jetEtasel . push_back (jetEta[jetID[j]]);
			jetPhisel . push_back (jetPhi[jetID[j]]);
			jetEnsel  . push_back (jetEn[jetID[j]]);
		}
		
		// * Set value for missing energy
		pfMETsel       = pfMET;
		pfMETPhisel    = pfMETPhi;
		pfMETCorsel    = pfMETCor;
		pfMETCorPhisel = pfMETCorPhi;
		
		
		
		// * Fill the tree
		//----------------
		tree_output2 -> Fill ();
	}
	
	
	// + Calculate yield
	//------------------
	nEventNormLepVeto = normFactor * nEventPULepVeto;
	nEventNormPassPho = normFactor * nEventPUPassPho;
	nEventNormPassJet = normFactor * nEventPUPassJet;
	nEventNormPassMET = normFactor * nEventPUPassMET;
	
	nVtxLepVeto = (nEventPULepVeto!=0) ? nVtxLepVeto/nEventPULepVeto : 0;
	nVtxPassPho = (nEventPUPassPho!=0) ? nVtxPassPho/nEventPUPassPho : 0;
	nVtxPassJet = (nEventPUPassJet!=0) ? nVtxPassJet/nEventPUPassJet : 0;
	nVtxPassMET = (nEventPUPassMET!=0) ? nVtxPassMET/nEventPUPassMET : 0;
	
	tree_output1 -> Fill ();
	
	
	
	// + Print log
	//------------
	printf ("  |-- CrossSection   %.4f\n", crossSection);
	printf ("  |-- Luminosity     %.2f\n", luminosity);
	printf ("  |-- NormFactor     %.6f\n", normFactor);
	printf ("  |-- nOriginal      %10lld : %.2f\n", nEvent,          nEventNorm);
	printf ("  |-- passHLT        %10lld : %.2f\n", nEventHLT,       nEventNormHLT);
	printf ("  |-- passGoodPV     %10lld : %.2f\n", nEventPVGood,    nEventNormPVGood);
	printf ("  |-- passLepVeto    %10lld : %.2f\n", nEventLepVeto,   nEventNormLepVeto);
	printf ("  |-- passPhoton     %10lld : %.2f\n", nEventPassPho,   nEventNormPassPho);
	printf ("  |-- passJet        %10lld : %.2f\n", nEventPassJet,   nEventNormPassJet);
	printf ("  |-- passMET        %10lld : %.2f\n", nEventPassMET,   nEventNormPassMET);
	
	
	
	// + Write to files
	//-----------------
	printf (" [+] Writing to file: [ %s ]\n", name_output.Data());
	
	tree_output1 ->Write("", TObject::kOverwrite);
	tree_output2 ->Write("", TObject::kOverwrite);
	delete tree_output2;
	delete file_output;
	
	// * Timer end
	time_t time_1 = time(0);
	
	float time_task = float(time_1 - time_0) / 3600.0;
	
	printf (" [$] Job's done, processing.\n");
	printf ("  |-- Task time: [ %.2f hrs ]\n", time_task);
	printf ("  |-- Number of selected events [ %lld ] / [ %lld ]\n\n", nEventSkimMET, nEvent);
}

#endif
