#ifndef SELECTION_JETMET_H
#define SELECTION_JETMET_H




using namespace std;















// + MET X-Y correction
//=====================
enum TheRunEra {y2016B,y2016C,y2016D,y2016E,y2016F,y2016G,y2016H,y2017B,y2017C,y2017D,y2017E,y2017F,y2018A,y2018B,y2018C,y2018D,y2016MC,y2017MC,y2018MC};

std::pair<double,double> METXYCorr (double uncormet,  double  uncormet_phi,  int runnb,  int year,  bool isMC,  int npv)
{
	std::pair<double,double>  TheXYCorr_Met_MetPhi (uncormet,uncormet_phi);
	
	if (npv > 100)   npv=100;
	
	int runera = -1;
	
	bool usemetv2 = false;
	
	if (isMC == true)
	{
		if (year == 2016)   runera = y2016MC;
		else if (year == 2017)
		{
			runera = y2017MC;
			usemetv2 =true;
		}
		else if (year == 2018)   runera = y2018MC;
	}
	else
	{
		if (runnb>=272007  &&  runnb<=275376)    runera = y2016B;
		else if (runnb>=275657  &&  runnb<=276283)    runera = y2016C;
		else if (runnb>=276315  &&  runnb<=276811)    runera = y2016D;
		else if (runnb>=276831  &&  runnb<=277420)    runera = y2016E;
		else if (runnb>=277772  &&  runnb<=278808)    runera = y2016F;
		else if (runnb>=278820  &&  runnb<=280385)    runera = y2016G;
		else if (runnb>=280919  &&  runnb<=284044)    runera = y2016H;
		else if (runnb>=297020  &&  runnb<=299329)
		{
			runera = y2017B;
			usemetv2 =true;
		}
		else if (runnb>=299337  &&  runnb<=302029)
		{
			runera = y2017C;
			usemetv2 =true;
		}
		else if (runnb>=302030  &&  runnb<=303434)
		{
			runera = y2017D;
			usemetv2 =true;
		}
		else if (runnb>=303435  &&  runnb<=304826)
		{
			runera = y2017E;
			usemetv2 =true;
		}
		else if (runnb>=304911  &&  runnb<=306462)
		{
			runera = y2017F;
			usemetv2 =true;
		}
		else if (runnb>=315252  &&  runnb<=316995)    runera = y2018A;
		else if (runnb>=316998  &&  runnb<=319312)    runera = y2018B;
		else if (runnb>=319313  &&  runnb<=320393)    runera = y2018C;
		else if (runnb>=320394  &&  runnb<=325273)    runera = y2018D;
	}
	
	if (runera == -1)
	{
		printf ("Couldn't find data/MC era => no correction applied\n");
		return TheXYCorr_Met_MetPhi;
	}
	
	
	double METxcorr(0.),METycorr(0.);
	
	if(!usemetv2)
	{
		//Current recommendation for 2016 and 2018
		if(runera==y2016B)
		{
			METxcorr = -(-0.0478335*npv - 0.108032);
			METycorr = -(0.125148*npv + 0.355672);
		}
		else if(runera==y2016C)
		{
			METxcorr = -(-0.0916985*npv + 0.393247);
			METycorr = -(0.151445*npv + 0.114491);
		}
		else if(runera==y2016D)
		{
			METxcorr = -(-0.0581169*npv + 0.567316);
			METycorr = -(0.147549*npv + 0.403088);
		}
		else if(runera==y2016E)
		{
			METxcorr = -(-0.065622*npv + 0.536856);
			METycorr = -(0.188532*npv + 0.495346);
		}
		else if(runera==y2016F)
		{
			METxcorr = -(-0.0313322*npv + 0.39866);
			METycorr = -(0.16081*npv + 0.960177);
		}
		else if(runera==y2016G)
		{
			METxcorr = -(0.040803*npv - 0.290384);
			METycorr = -(0.0961935*npv + 0.666096);
		}
		else if(runera==y2016H)
		{
			METxcorr = -(0.0330868*npv - 0.209534);
			METycorr = -(0.141513*npv + 0.816732);
		}
		else if(runera==y2017B)
		{
			METxcorr = -(-0.259456*npv + 1.95372);
			METycorr = -(0.353928*npv - 2.46685);
		}
		else if(runera==y2017C)
		{
			METxcorr = -(-0.232763*npv + 1.08318);
			METycorr = -(0.257719*npv - 1.1745);
		}
		else if(runera==y2017D)
		{
			METxcorr = -(-0.238067*npv + 1.80541);
			METycorr = -(0.235989*npv - 1.44354);
		}
		else if(runera==y2017E)
		{
			METxcorr = -(-0.212352*npv + 1.851);
			METycorr = -(0.157759*npv - 0.478139);
		}
		else if(runera==y2017F)
		{
			METxcorr = -(-0.232733*npv + 2.24134);
			METycorr = -(0.213341*npv + 0.684588);
		}
		else if(runera==y2018A)
		{
			METxcorr = -(0.362865*npv - 1.94505);
			METycorr = -(0.0709085*npv - 0.307365);
		}
		else if(runera==y2018B)
		{
			METxcorr = -(0.492083*npv - 2.93552);
			METycorr = -(0.17874*npv - 0.786844);
		}
		else if(runera==y2018C)
		{
			METxcorr = -(0.521349*npv - 1.44544);
			METycorr = -(0.118956*npv - 1.96434);
		}
		else if(runera==y2018D)
		{
			METxcorr = -(0.531151*npv - 1.37568);
			METycorr = -(0.0884639*npv - 1.57089);
		}
		else if(runera==y2016MC)
		{
			METxcorr = -(-0.195191*npv - 0.170948);
			METycorr = -(-0.0311891*npv + 0.787627);
		}
		else if(runera==y2017MC)
		{
			METxcorr = -(-0.217714*npv + 0.493361);
			METycorr = -(0.177058*npv - 0.336648);
		}
		else if(runera==y2018MC)
		{
			METxcorr = -(0.296713*npv - 0.141506);
			METycorr = -(0.115685*npv + 0.0128193);
		}
	}
	else
	{
		//these are the corrections for v2 MET recipe (currently recommended for 2017)
		if(runera==y2016B)
		{
			METxcorr = -(-0.0374977*npv + 0.00488262);
			METycorr = -(0.107373*npv - 0.00732239);
		}
		else if(runera==y2016C)
		{
			METxcorr = -(-0.0832562*npv + 0.550742);
			METycorr = -(0.142469*npv - 0.153718);
		}
		else if(runera==y2016D)
		{
			METxcorr = -(-0.0400931*npv + 0.753734);
			METycorr = -(0.127154*npv + 0.0175228);
		}
		else if(runera==y2016E)
		{
			METxcorr = -(-0.0409231*npv + 0.755128);
			METycorr = -(0.168407*npv + 0.126755);
		}
		else if(runera==y2016F)
		{
			METxcorr = -(-0.0161259*npv + 0.516919);
			METycorr = -(0.141176*npv + 0.544062);
		}
		else if(runera==y2016G)
		{
			METxcorr = -(0.0583851*npv - 0.0987447);
			METycorr = -(0.0641427*npv + 0.319112);
		}
		else if(runera==y2016H)
		{
			METxcorr = -(0.0706267*npv - 0.13118);
			METycorr = -(0.127481*npv + 0.370786);
		}
		else if(runera==y2017B)
		{
			METxcorr = -(-0.19563*npv + 1.51859);
			METycorr = -(0.306987*npv - 1.84713);
		}
		else if(runera==y2017C)
		{
			METxcorr = -(-0.161661*npv + 0.589933);
			METycorr = -(0.233569*npv - 0.995546);
		}
		else if(runera==y2017D)
		{
			METxcorr = -(-0.180911*npv + 1.23553);
			METycorr = -(0.240155*npv - 1.27449);
		}
		else if(runera==y2017E)
		{
			METxcorr = -(-0.149494*npv + 0.901305);
			METycorr = -(0.178212*npv - 0.535537);
		}
		else if(runera==y2017F)
		{
			METxcorr = -(-0.165154*npv + 1.02018);
			METycorr = -(0.253794*npv + 0.75776);
		}
		else if(runera==y2018A)
		{
			METxcorr = -(0.362642*npv - 1.55094);
			METycorr = -(0.0737842*npv - 0.677209);
		}
		else if(runera==y2018B)
		{
			METxcorr = -(0.485614*npv - 2.45706);
			METycorr = -(0.181619*npv - 1.00636);
		}
		else if(runera==y2018C)
		{
			METxcorr = -(0.503638*npv - 1.01281);
			METycorr = -(0.147811*npv - 1.48941);
		}
		else if(runera==y2018D)
		{
			METxcorr = -(0.520265*npv - 1.20322);
			METycorr = -(0.143919*npv - 0.979328);
		}
		else if(runera==y2016MC)
		{
			METxcorr = -(-0.159469*npv - 0.407022);
			METycorr = -(-0.0405812*npv + 0.570415);
		}
		else if(runera==y2017MC)
		{
			METxcorr = -(-0.182569*npv + 0.276542);
			METycorr = -(0.155652*npv - 0.417633);
		}
		else if(runera==y2018MC)
		{
			METxcorr = -(0.299448*npv - 0.13866);
			METycorr = -(0.118785*npv + 0.0889588);
		}
	}
	
	double CorrectedMET_x = uncormet *cos(uncormet_phi) + METxcorr;
	double CorrectedMET_y = uncormet *sin(uncormet_phi) + METycorr;
	
	double CorrectedMET = sqrt(CorrectedMET_x*CorrectedMET_x+CorrectedMET_y*CorrectedMET_y);
	double CorrectedMETPhi;
	
	if (CorrectedMET_x==0  &&  CorrectedMET_y>0)    CorrectedMETPhi = TMath::Pi();
	else if (CorrectedMET_x==0 && CorrectedMET_y<0)    CorrectedMETPhi = -TMath::Pi();
	else if (CorrectedMET_x > 0)    CorrectedMETPhi = TMath::ATan(CorrectedMET_y/CorrectedMET_x);
	else if (CorrectedMET_x<0  &&  CorrectedMET_y>0)    CorrectedMETPhi = TMath::ATan(CorrectedMET_y/CorrectedMET_x) + TMath::Pi();
	else if (CorrectedMET_x<0  &&  CorrectedMET_y<0)    CorrectedMETPhi = TMath::ATan(CorrectedMET_y/CorrectedMET_x) - TMath::Pi();
	else    CorrectedMETPhi =0;
	
	
	TheXYCorr_Met_MetPhi.first  = CorrectedMET;
	TheXYCorr_Met_MetPhi.second = CorrectedMETPhi;
	return TheXYCorr_Met_MetPhi;
}















//===========
// + Jet skim
//===========
// * For ggNtuples
//================
void Select_Jet_SkimZgVBS (TreeReader &file_input, vector<Int_t> &jetIDSel, bool isMC)
{
	// + Prepare vector
	//-----------------
	vector<Int_t>::iterator it;
	jetIDSel    . clear ();
	
	
	// + Variables
	//------------
	Int_t    nJet;
	Int_t   *jetID;
	Float_t  jetCorPt;
	Float_t *jetPt, *jetRawPt, *jetEta, *jetP4Smear;
	
	
	// + Get the variables
	//--------------------
	nJet       = file_input . GetInt      ("nJet");
	jetPt      = file_input . GetPtrFloat ("jetPt");
	jetEta     = file_input . GetPtrFloat ("jetEta");
	if(isMC == true)
	{
		jetP4Smear = file_input . GetPtrFloat ("jetP4Smear");
	}
	
	
	// + Start the selection
	//----------------------
	for (int i=0; i<nJet; i++)
	{
		jetCorPt = (isMC==true) ? jetPt[i]*jetP4Smear[i] : jetPt[i];
		if (jetCorPt < 30)   continue;
		if (abs(jetEta[i]) > 5.0)   continue;
		
		jetIDSel . push_back (i);
	}
}




// * For NanoAOD
//==============
void Select_Jet_SkimZgVBSNano (TreeReader &file_input, vector<Int_t> &jetIDSel, bool isMC)
{
	// + Prepare vector
	//-----------------
	vector<Int_t>::iterator it;
	jetIDSel    . clear ();
	
	
	// + Variables
	//------------
	Int_t    nJet;
	Int_t   *jetID;
	Float_t  jetCorPt;
	Float_t *jetPt, *jetRawPt, *jetEta, *jetP4Smear;
	
	
	// + Get the variables
	//--------------------
	nJet       = file_input . GetInt      ("nJet");
	jetPt      = file_input . GetPtrFloat ("Jet_pt");
	jetEta     = file_input . GetPtrFloat ("Jet_eta");
	if(isMC == true)
	{
		jetP4Smear = file_input . GetPtrFloat ("jetP4Smear");
	}
	
	
	// + Start the selection
	//----------------------
	for (int i=0; i<nJet; i++)
	{
		jetCorPt = (isMC==true) ? jetPt[i]*jetP4Smear[i] : jetPt[i];
		if (jetCorPt < 30)   continue;
		if (abs(jetEta[i]) > 5.0)   continue;
		
		jetIDSel . push_back (i);
	}
}















// + VBS selection for jet - tight jet ID and medium PU jet ID
//============================================================
// * For ggNtuples
//----------------
void Select_Jet_ZgVBSTight (int year,   TreeReader &file_input,   vector<Int_t> &jetIDSort)
{
	// + Prepare vector
	//-----------------
	vector<Int_t> jetIDSel;
	vector<Int_t>::iterator it;
	jetIDSel    . clear ();
	jetIDSort   . clear ();
	
	
	// + Variables
	//------------
	Int_t    nJet;
	Int_t   *jetCorID;
	Float_t *jetPt, *jetRawPt, *jetEta, *jetPhi, *jetEn, *jetPUID;
	//Float_t *jetNHF, *jetNEF, *jetMUF, *jetCHF;
	//Int_t   *jetNCH, *jetNConstituents, jetNNP;
	
	
	// + Get the variables
	//--------------------
	nJet       = file_input . GetInt      ("nJet");
	jetCorID   = file_input . GetPtrInt   ("jetCorID");
	jetPt      = file_input . GetPtrFloat ("jetPt");
	jetRawPt   = file_input . GetPtrFloat ("jetRawPt");
	jetEta     = file_input . GetPtrFloat ("jetEta");
	jetPhi     = file_input . GetPtrFloat ("jetPhi");
	jetEn      = file_input . GetPtrFloat ("jetEn");
	jetPUID    = file_input . GetPtrFloat ("jetPUID");
	// * - Variables for calculating
	Int_t    etaind = -1;
	//Float_t  fullDiscriminant[4] = {0.61, -0.35, -0.23, -0.17};  // Medium jet pileup ID, PT from 30 to 50
	Float_t  fullDiscriminant[4] = {0.86, -0.10, -0.05, -0.01};  // Tight jet pileup ID, PT from 30 to 50
	
	
	// + Start the selection
	//----------------------
	int rejectEvent = 0;
	
	for (int i=0; i<nJet; i++)
	{
		// * Basic cuts
		if (jetPt[i] < 30)   continue;
		if (abs(jetEta[i]) > 4.7)   continue;
		
		// * Applied tight jet cut based ID
		bool passID = jetCorID[i]>>3&1;
		if (passID == false)   continue;
		
		// * Reject pile-up jet with medium PUID
		if (abs(jetEta[i]) < 2.50)   etaind = 0;
		else if (abs(jetEta[i]) < 2.75)   etaind = 1;
		else if (abs(jetEta[i]) < 3.00)   etaind = 2;
		else if (abs(jetEta[i]) < 5.00)   etaind = 3;
		
		if (jetPt[i]<50 && jetPUID[i]<fullDiscriminant[etaind])   continue;
		
		// * Remove noisy jets for 2017 & Dead region jet in 2018
		bool isNoiseJet = (year==2017  &&  jetRawPt[i]<50  &&  abs(jetEta[i])>2.65  &&  abs(jetEta[i])<3.139);
		if (isNoiseJet)   continue;
		
		bool isHEM (year==2018  &&  jetEta[i]>-3.0  &&  jetEta[i]<-1.3  &&  jetPhi[i]>-1.57  &&  jetPhi[i]<-0.87);
		if (isHEM)   rejectEvent ++;
		
		
		jetIDSel . push_back (i);
	}
	
	
	// + Sort the jet index by Pt
	//---------------------------
	if (jetIDSel.size() > 0)
	{
		jetIDSort . push_back (jetIDSel[0]);
		
		for (unsigned int i=1; i<jetIDSel.size(); i++)
		{
			bool trigins = 1;
			
			for (it=jetIDSort.begin(); it<jetIDSort.end(); it++)
			{
				if (jetPt[*it] < jetPt[jetIDSel[i]])
				{
					jetIDSort . insert (it, jetIDSel[i]);
					trigins = 0;
					break;
				}
			}
			
			if (trigins == 1)
			{
				jetIDSort . push_back (jetIDSel[i]);
			}
		}
	}
	
	
	// * Remove all jets if contaminated by HEM jets
	if (rejectEvent > 0)   jetIDSort . clear();
}



// * For NanoAOD
//--------------
void Select_Jet_ZgVBSTightNano (int year,   TreeReader &file_input,   vector<Int_t> &jetIDSort)
{
	// + Prepare vector
	//-----------------
	vector<Int_t> jetIDSel;
	vector<Int_t>::iterator it;
	jetIDSel    . clear ();
	jetIDSort   . clear ();
	
	
	// + Variables
	//------------
	Int_t    nJet;
	Int_t   *jetCorID;
	Float_t *jetPt, *jetRawFactor, *jetEta, *jetPhi, *jetPUID;
	
	
	// + Get the variables
	//--------------------
	nJet         = file_input . GetInt      ("nJet");
	jetCorID     = file_input . GetPtrInt   ("jetIDbit");
	jetPt        = file_input . GetPtrFloat ("jetPt");
	jetRawFactor = file_input . GetPtrFloat ("jetRawFactor");
	jetEta       = file_input . GetPtrFloat ("jetEta");
	jetPhi       = file_input . GetPtrFloat ("jetPhi");
	jetPUID      = file_input . GetPtrFloat ("jetPUID");
	// * - Variables for calculating
	Int_t    etaind = -1;
	Float_t  fullDiscriminant[4] = {0.61, -0.35, -0.23, -0.17};  // Medium jet pileup ID, PT from 30 to 50
	
	
	// + Start the selection
	//----------------------
	int rejectEvent = 0;
	
	for (int i=0; i<nJet; i++)
	{
		// * Basic cuts
		if (jetPt[i] < 30)   continue;
		if (abs(jetEta[i]) > 4.7)   continue;
		
		// * Applied tight jet cut based ID
		bool passID = jetCorID[i]>>1&1;
		if (passID == false)   continue;
		
		// * Reject pile-up jet with medium PUID
		if (abs(jetEta[i]) < 2.50)   etaind = 0;
		else if (abs(jetEta[i]) < 2.75)   etaind = 1;
		else if (abs(jetEta[i]) < 3.00)   etaind = 2;
		else if (abs(jetEta[i]) < 5.00)   etaind = 3;
		
		if (jetPt[i]<50 && jetPUID[i]<fullDiscriminant[etaind])   continue;
		
		float jetRawPt = (1-jetRawFactor[i])*jetPt[i];
		
		// * Remove noisy jets for 2017 & Dead region jet in 2018
		bool isNoiseJet = (year==2017  &&  jetRawPt<50  &&  abs(jetEta[i])>2.65  &&  abs(jetEta[i])<3.139);
		if (isNoiseJet)   continue;
		
		bool isHEM (year==2018  &&  jetEta[i]>-3.0  &&  jetEta[i]<-1.3  &&  jetPhi[i]>-1.57  &&  jetPhi[i]<-0.87);
		if (isHEM)   rejectEvent ++;
		
		
		jetIDSel . push_back (i);
	}
	
	
	// + Sort the jet index by Pt
	//---------------------------
	if (jetIDSel.size() > 0)
	{
		jetIDSort . push_back (jetIDSel[0]);
		
		for (unsigned int i=1; i<jetIDSel.size(); i++)
		{
			bool trigins = 1;
			
			for (it=jetIDSort.begin(); it<jetIDSort.end(); it++)
			{
				if (jetPt[*it] < jetPt[jetIDSel[i]])
				{
					jetIDSort . insert (it, jetIDSel[i]);
					trigins = 0;
					break;
				}
			}
			
			if (trigins == 1)
			{
				jetIDSort . push_back (jetIDSel[i]);
			}
		}
	}
	
	
	// * Remove all jets if contaminated by HEM jets
	if (rejectEvent > 0)   jetIDSort . clear();
}










// + GJets selection for jet - tight jet ID
//=========================================
// * For ggNtuples
//----------------
void Select_Jet_GJetsTight (int year,   TreeReader &file_input,   vector<Int_t> &jetIDSort)
{
	// + Prepare vector
	//-----------------
	vector<Int_t> jetIDSel;
	vector<Int_t>::iterator it;
	jetIDSel    . clear ();
	jetIDSort   . clear ();
	
	
	// + Variables
	//------------
	Int_t    nJet;
	Int_t   *jetCorID;
	Float_t *jetPt, *jetRawPt, *jetEta, *jetPhi, *jetEn;
	//Float_t *jetNHF, *jetNEF, *jetMUF, *jetCHF;
	//Int_t   *jetNCH, *jetNConstituents, jetNNP;
	
	
	// + Get the variables
	//--------------------
	nJet       = file_input . GetInt      ("nJet");
	jetCorID   = file_input . GetPtrInt   ("jetCorID");
	jetPt      = file_input . GetPtrFloat ("jetPt");
	jetEta     = file_input . GetPtrFloat ("jetEta");
	jetPhi     = file_input . GetPtrFloat ("jetPhi");
	jetEn      = file_input . GetPtrFloat ("jetEn");
	
	
	// + Start the selection
	//----------------------
	int rejectEvent = 0;
	
	for (int i=0; i<nJet; i++)
	{
		// * Basic cuts
		if (jetPt[i] < 30)   continue;
		if (abs(jetEta[i]) > 2.5)   continue;
		
		// * Applied tight jet cut based ID
		bool passID = jetCorID[i]>>3&1;
		if (passID == false)   continue;
		
		
		jetIDSel . push_back (i);
	}
	
	
	// + Sort the jet index by Pt
	//---------------------------
	if (jetIDSel.size() > 0)
	{
		jetIDSort . push_back (jetIDSel[0]);
		
		for (unsigned int i=1; i<jetIDSel.size(); i++)
		{
			bool trigins = 1;
			
			for (it=jetIDSort.begin(); it<jetIDSort.end(); it++)
			{
				if (jetPt[*it] < jetPt[jetIDSel[i]])
				{
					jetIDSort . insert (it, jetIDSel[i]);
					trigins = 0;
					break;
				}
			}
			
			if (trigins == 1)
			{
				jetIDSort . push_back (jetIDSel[i]);
			}
		}
	}
	
	
	// * Remove all jets if contaminated by HEM jets
	if (rejectEvent > 0)   jetIDSort . clear();
}




/*
bool Select_pfMET_ZgVBS (TreeReader &file_input)
{
}
*/


#endif
