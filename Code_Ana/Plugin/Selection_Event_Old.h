#ifndef SELECTION_EVENT_H
#define SELECTION_EVENT_H

#include "Tools.h"


using namespace std;















// + Use the VBS (charged lepton) selection
//=========================================
void Select_Event_VBSLep (TreeReader &file_input,   vector<Int_t> &eleIDsel,   vector<Int_t> &phoIDsel,   vector<Int_t> &jetIDsel)
{
	// + Read the variables
	//---------------------
	// * electron
	int     nEle       = file_input . GetInt      ("nEle");
	float  *eleCalibPt = file_input . GetPtrFloat ("eleCalibPt");
	float  *eleEta     = file_input . GetPtrFloat ("eleEta");
	float  *elePhi     = file_input . GetPtrFloat ("elePhi");
	float  *eleEn      = file_input . GetPtrFloat ("eleEn");
	int    *eleCharge  = file_input . GetPtrInt   ("eleCharge");
	
	// * Photon
	int     nPho       = file_input . GetInt      ("nPho");
	float  *phoCalibEt = file_input . GetPtrFloat ("phoCalibEt");
	float  *phoEta     = file_input . GetPtrFloat ("phoEta");
	float  *phoPhi     = file_input . GetPtrFloat ("phoPhi");
	
	// * Jet
	int     nJet       = file_input . GetInt      ("nJet");
	float  *jetPt      = file_input . GetPtrFloat ("jetPt");
	float  *jetEta     = file_input . GetPtrFloat ("jetEta");
	float  *jetPhi     = file_input . GetPtrFloat ("jetPhi");
	float  *jetEn      = file_input . GetPtrFloat ("jetEn");
	
	
	
	// + Select electron pair
	//-----------------------
	TLorentzVector v4D_ele1, v4D_ele2, v4D_diele;
	v4D_ele1 . SetPtEtaPhiE (eleCalibPt[0], eleEta[0], elePhi[0], eleEn[0]);
	v4D_ele2 . SetPtEtaPhiE (eleCalibPt[1], eleEta[1], elePhi[1], eleEn[1]);
	v4D_diele = v4D_ele1 + v4D_ele2;
	
	int chargeMult = eleCharge[0] * eleCharge[1];
	
	if (v4D_diele.M()>70 && v4D_diele.M()<110 && chargeMult<0)
	{
		eleIDsel . push_back (0);
		eleIDsel . push_back (1);
	}
	
	
	
	// + Separation of MET and photon
	//-------------------------------
	vector<int>  phoIDsepMET;
	phoIDsepMET . clear ();
	
	for (unsigned int i=0; i<nPho; i++)
	{
		int countFail = 0;
		for (int j=0; j<2; j++)
		{
			Float_t delR = compute_DeltaR (phoEta[i], eleEta[j], phoPhi[i], elePhi[j]);
			if (delR < 0.7)   countFail ++;
		}
		if (countFail > 0)   continue;
		
		phoIDsepMET . push_back (i);
	}
	
	
	
	// + Separation of MET and jet
	//----------------------------
	vector<int>  jetIDsepMET;
	jetIDsepMET . clear ();
	
	for (unsigned int i=0; i<nJet; i++)
	{
		int countFail = 0;
		for (int j=0; j<2; j++)
		{
			Float_t delR = compute_DeltaR (jetEta[i], eleEta[j], jetPhi[i], elePhi[j]);
			if (delR < 0.5)   countFail ++;
		}
		if (countFail > 0)   continue;
		
		if (abs(jetEta[i]) > 4.7)   continue;
		
		jetIDsepMET . push_back (i);
	}
	
	
	
	// + Select tag jets (by dijet mass)
	//----------------------------------
	vector<vector<int>>  jetIDPair;
	jetIDPair . clear ();
	
	vector<int>  tmpPairID;
	tmpPairID . clear ();
	
	TLorentzVector v4D_jet1, v4D_jet2, v4D_dijet;
	float  massDijet;
	
	for (unsigned int i=0; i<jetIDsepMET.size(); i++)
	{
		massDijet = 0.0;
		v4D_jet1 . SetPtEtaPhiE (jetPt[jetIDsepMET[i]], jetEta[jetIDsepMET[i]], jetPhi[jetIDsepMET[i]], jetEn[jetIDsepMET[i]]);
		
		for (unsigned int j=i+1; j<jetIDsepMET.size(); j++)
		{
			tmpPairID . clear();
			
			// * Requirement of the deltaR between 2 jets
			v4D_jet2 . SetPtEtaPhiE (jetPt[jetIDsepMET[j]], jetEta[jetIDsepMET[j]], jetPhi[jetIDsepMET[j]], jetEn[jetIDsepMET[j]]);
			
			float  dRJet   = v4D_jet1.DeltaR(v4D_jet2);
			if (i!=j && dRJet<0.5)   continue;
			
			float  dEtaJet = abs (jetEta[jetIDsepMET[j]] - jetEta[jetIDsepMET[i]]);
			if (i!=j && dEtaJet<2.5)   continue;
			
			// * Requirement on dijet mass
			v4D_dijet = v4D_jet1 + v4D_jet2;
			massDijet = v4D_dijet . M();
			if (i!=j && massDijet<500)   continue;
			
			tmpPairID . push_back (jetIDsepMET[i]);
			tmpPairID . push_back (jetIDsepMET[j]);
			jetIDPair . push_back (tmpPairID);
		}
	}
	
	
	
	// + Separation of jets and photon
	//--------------------------------
	phoIDsel . clear ();
	jetIDsel . clear ();
	
	float dRPhoJet1;
	float dRPhoJet2;
	
	float phiZGvsJJ;
	float zeppenfeld;
	
	TLorentzVector v4D_pho, v4D_Zg;
	
	for (unsigned int i=0; i<jetIDPair.size(); i++)
	{
		for (unsigned int j=0; j<phoIDsepMET.size(); j++)
		{
			// * Jet separation
			dRPhoJet1 = compute_DeltaR (phoEta[phoIDsepMET[j]], jetEta[jetIDPair[i][0]], phoPhi[phoIDsepMET[j]], jetPhi[jetIDPair[i][0]]);
			dRPhoJet2 = compute_DeltaR (phoEta[phoIDsepMET[j]], jetEta[jetIDPair[i][1]], phoPhi[phoIDsepMET[j]], jetPhi[jetIDPair[i][1]]);
			
			if (dRPhoJet1<0.5 || dRPhoJet2<0.5)   continue;
			
			
			
			// * Delta Phi between jj and Zg
			v4D_ele1 . SetPtEtaPhiE (eleCalibPt[0], eleEta[0], elePhi[0], eleEn[0]);
			v4D_ele2 . SetPtEtaPhiE (eleCalibPt[1], eleEta[1], elePhi[1], eleEn[1]);
			v4D_diele = v4D_ele1 + v4D_ele2;
			v4D_pho . SetPtEtaPhiM (phoCalibEt[phoIDsepMET[j]], phoEta[phoIDsepMET[j]], phoPhi[phoIDsepMET[j]], 0);
			v4D_Zg = v4D_diele + v4D_pho;
			
			if (v4D_Zg.M() < 100)   continue;
			
			v4D_jet1 . SetPtEtaPhiE (jetPt[jetIDPair[i][0]], jetEta[jetIDPair[i][0]], jetPhi[jetIDPair[i][0]], jetEn[jetIDPair[i][0]]);
			v4D_jet2 . SetPtEtaPhiE (jetPt[jetIDPair[i][1]], jetEta[jetIDPair[i][1]], jetPhi[jetIDPair[i][1]], jetEn[jetIDPair[i][1]]);
			v4D_dijet = v4D_jet1 + v4D_jet2;
			
			phiZGvsJJ = compute_DeltaPhi(v4D_Zg.Phi(), v4D_dijet.Phi());
			
			if (phiZGvsJJ < 1.90)   continue;
			
			
			zeppenfeld = abs (v4D_Zg.Eta() - (v4D_jet1.Eta() + v4D_jet2.Eta()) / 2);
			if (zeppenfeld > 2.4)   continue;
			
			
			
			// * Insert the value to your vector
			phoIDsel . push_back (phoIDsepMET[j]);
			jetIDsel . push_back (jetIDPair[i][0]);
			jetIDsel . push_back (jetIDPair[i][1]);
		}
	}
}















// + Use the basic VBS selection
//==============================
// * For ggNtuple
//---------------
void Select_Event_VBSLoose (TreeReader &file_input,   bool useCorMETOnly,   int year,   vector<Int_t> &phoIDsel,   vector<Int_t> &jetIDsel)
{
	// + Read the variables
	//---------------------
	// * Photon
	int     nPho        = file_input . GetInt      ("nPho");
	float  *phoCalibEt  = file_input . GetPtrFloat ("phoCalibEt");
	float  *phoEta      = file_input . GetPtrFloat ("phoEta");
	float  *phoPhi      = file_input . GetPtrFloat ("phoPhi");
	
	// * Jet
	int     nJet        = file_input . GetInt      ("nJet");
	float  *jetPt       = file_input . GetPtrFloat ("jetPt");
	float  *jetEta      = file_input . GetPtrFloat ("jetEta");
	float  *jetPhi      = file_input . GetPtrFloat ("jetPhi");
	float  *jetEn       = file_input . GetPtrFloat ("jetEn");
	float   pfMET       = file_input . GetFloat    ("pfMET");
	float   pfMETPhi    = file_input . GetFloat    ("pfMETPhi");
	float   pfMETCor    = file_input . GetFloat    ("pfMETCor");
	float   pfMETCorPhi = file_input . GetFloat    ("pfMETCorPhi");
	
	
	
	// + Separation of MET and photon
	//-------------------------------
	vector<int>  phoIDsepMET;
	phoIDsepMET . clear ();
	
	for (unsigned int i=0; i<nPho; i++)
	{
		Float_t delPhi = (useCorMETOnly) ? compute_DeltaPhi (phoPhi[i], pfMETCorPhi) : compute_DeltaPhi (phoPhi[i], pfMETPhi);
		if (delPhi < 0.5)   continue;
		
		Float_t EToverMET = phoCalibEt[i]/pfMETCor;
		if (EToverMET > 2.50)   continue;
		
		phoIDsepMET . push_back (i);
	}
	
	
	
	// + Separation of MET and jet
	//----------------------------
	vector<int>  jetIDsepMET;
	jetIDsepMET . clear ();
	
	for (unsigned int i=0; i<nJet; i++)
	{
		Float_t delPhi = (useCorMETOnly) ? compute_DeltaPhi (jetPhi[i], pfMETCorPhi) : compute_DeltaPhi (jetPhi[i], pfMETPhi);
		if (delPhi < 0.5)   continue;
		if (abs(jetEta[i]) > 4.7)   continue;
		
		jetIDsepMET . push_back (i);
	}
	
	
	// + Select tag jets (by dijet mass)
	//----------------------------------
	vector<vector<int>>  jetIDPair;
	jetIDPair . clear ();
	
	vector<int>  tmpPairID;
	tmpPairID . clear ();
	
	TLorentzVector v4D_jet1, v4D_jet2, v4D_dijet;
	float  massDijet;
	
	for (unsigned int i=0; i<jetIDsepMET.size(); i++)
	{
		massDijet = 0.0;
		v4D_jet1 . SetPtEtaPhiE (jetPt[jetIDsepMET[i]], jetEta[jetIDsepMET[i]], jetPhi[jetIDsepMET[i]], jetEn[jetIDsepMET[i]]);
		
		for (unsigned int j=i+1; j<jetIDsepMET.size(); j++)
		{
			tmpPairID . clear();
			
			// * Requirement of the deltaR between 2 jets
			v4D_jet2 . SetPtEtaPhiE (jetPt[jetIDsepMET[j]], jetEta[jetIDsepMET[j]], jetPhi[jetIDsepMET[j]], jetEn[jetIDsepMET[j]]);
			
			float  dRJet   = v4D_jet1.DeltaR(v4D_jet2);
			if (i!=j && dRJet<0.5)   continue;
			
			float  dEtaJet = abs (jetEta[jetIDsepMET[j]] - jetEta[jetIDsepMET[i]]);
			if (i!=j && dEtaJet<2.5)   continue;
			
			// * Requirement on dijet mass
			v4D_dijet = v4D_jet1 + v4D_jet2;
			massDijet = v4D_dijet . M();
			if (i!=j && massDijet<500)   continue;
			
			tmpPairID . push_back (jetIDsepMET[i]);
			tmpPairID . push_back (jetIDsepMET[j]);
			jetIDPair . push_back (tmpPairID);
		}
	}
	
	
	// + Separation of jets and photon
	//--------------------------------
	phoIDsel . clear ();
	jetIDsel . clear ();
	
	float dRPhoJet1;
	float dRPhoJet2;
	
	float pxPho;
	float pyPho;
	float pxMET;
	float pyMET;
	
	float phiPhoMET;
	float phiDijet;
	float phiZGvsJJ;
	
	for (unsigned int i=0; i<jetIDPair.size(); i++)
	{
		for (unsigned int j=0; j<phoIDsepMET.size(); j++)
		{
			// * Jet separation
			dRPhoJet1 = compute_DeltaR (phoEta[phoIDsepMET[j]], jetEta[jetIDPair[i][0]], phoPhi[phoIDsepMET[j]], jetPhi[jetIDPair[i][0]]);
			dRPhoJet2 = compute_DeltaR (phoEta[phoIDsepMET[j]], jetEta[jetIDPair[i][1]], phoPhi[phoIDsepMET[j]], jetPhi[jetIDPair[i][1]]);
			
			if (dRPhoJet1<0.5 || dRPhoJet2<0.5)   continue;
			
			
			
			// * Delta Phi between jj and Zg
			pxPho = phoCalibEt[phoIDsepMET[j]] * cos (phoPhi[phoIDsepMET[j]]);
			pyPho = phoCalibEt[phoIDsepMET[j]] * sin (phoPhi[phoIDsepMET[j]]);
			pxMET = pfMETCor * cos (pfMETCorPhi);
			pyMET = pfMETCor * sin (pfMETCorPhi);
			//phiPhoMET = atan ((pyPho+pyMET) / (pxPho+pxMET));
			phiPhoMET = atan2 (pyPho+pyMET, pxPho+pxMET);
			
			v4D_jet1 . SetPtEtaPhiE (jetPt[jetIDPair[i][0]], jetEta[jetIDPair[i][0]], jetPhi[jetIDPair[i][0]], jetEn[jetIDPair[i][0]]);
			v4D_jet2 . SetPtEtaPhiE (jetPt[jetIDPair[i][1]], jetEta[jetIDPair[i][1]], jetPhi[jetIDPair[i][1]], jetEn[jetIDPair[i][1]]);
			v4D_dijet = v4D_jet1 + v4D_jet2;
			phiDijet = v4D_dijet . Phi();
			
			phiZGvsJJ = compute_DeltaPhi(phiPhoMET, phiDijet);
			
			if (phiZGvsJJ<1.90)   continue;
			
			
			
			// * Insert the value to your vector
			phoIDsel . push_back (phoIDsepMET[j]);
			jetIDsel . push_back (jetIDPair[i][0]);
			jetIDsel . push_back (jetIDPair[i][1]);
		}
	}
}
// * For NanoAOD
//--------------
void Select_Event_VBSLooseNano (TreeReader &file_input,   bool useCorMETOnly,   int year,   vector<Int_t> &phoIDsel,   vector<Int_t> &jetIDsel)
{
	// + Read the variables
	//---------------------
	// * Photon
	int     nPho        = file_input . GetInt      ("nPho");
	float  *phoCalibEt  = file_input . GetPtrFloat ("phoCalibEt");
	float  *phoEta      = file_input . GetPtrFloat ("phoEta");
	float  *phoPhi      = file_input . GetPtrFloat ("phoPhi");
	
	// * Jet
	int     nJet        = file_input . GetInt      ("nJet");
	float  *jetPt       = file_input . GetPtrFloat ("jetPt");
	float  *jetEta      = file_input . GetPtrFloat ("jetEta");
	float  *jetPhi      = file_input . GetPtrFloat ("jetPhi");
	float  *jetMass     = file_input . GetPtrFloat ("jetMass");
	float   pfMET       = file_input . GetFloat    ("pfMET");
	float   pfMETPhi    = file_input . GetFloat    ("pfMETPhi");
	float   pfMETCor    = file_input . GetFloat    ("pfMETCor");
	float   pfMETCorPhi = file_input . GetFloat    ("pfMETCorPhi");
	
	
	
	// + Separation of MET and photon
	//-------------------------------
	vector<int>  phoIDsepMET;
	phoIDsepMET . clear ();
	
	for (unsigned int i=0; i<nPho; i++)
	{
		Float_t delPhi = (useCorMETOnly) ? compute_DeltaPhi (phoPhi[i], pfMETCorPhi) : compute_DeltaPhi (phoPhi[i], pfMETPhi);
		if (delPhi < 0.5)   continue;
		
		Float_t EToverMET = phoCalibEt[i]/pfMETCor;
		if (EToverMET > 2.50)   continue;
		
		phoIDsepMET . push_back (i);
	}
	
	
	
	// + Separation of MET and jet
	//----------------------------
	vector<int>  jetIDsepMET;
	jetIDsepMET . clear ();
	
	for (unsigned int i=0; i<nJet; i++)
	{
		Float_t delPhi = (useCorMETOnly) ? compute_DeltaPhi (jetPhi[i], pfMETCorPhi) : compute_DeltaPhi (jetPhi[i], pfMETPhi);
		if (delPhi < 0.5)   continue;
		if (abs(jetEta[i]) > 4.7)   continue;
		
		jetIDsepMET . push_back (i);
	}
	
	
	// + Select tag jets (by dijet mass)
	//----------------------------------
	vector<vector<int>>  jetIDPair;
	jetIDPair . clear ();
	
	vector<int>  tmpPairID;
	tmpPairID . clear ();
	
	TLorentzVector v4D_jet1, v4D_jet2, v4D_dijet;
	float  massDijet;
	
	for (unsigned int i=0; i<jetIDsepMET.size(); i++)
	{
		massDijet = 0.0;
		v4D_jet1 . SetPtEtaPhiM (jetPt[jetIDsepMET[i]], jetEta[jetIDsepMET[i]], jetPhi[jetIDsepMET[i]], jetMass[jetIDsepMET[i]]);
		
		for (unsigned int j=i+1; j<jetIDsepMET.size(); j++)
		{
			tmpPairID . clear();
			
			// * Requirement of the deltaR between 2 jets
			v4D_jet2 . SetPtEtaPhiM (jetPt[jetIDsepMET[j]], jetEta[jetIDsepMET[j]], jetPhi[jetIDsepMET[j]], jetMass[jetIDsepMET[j]]);
			
			float  dRJet   = v4D_jet1.DeltaR(v4D_jet2);
			if (i!=j && dRJet<0.5)   continue;
			
			float  dEtaJet = abs (jetEta[jetIDsepMET[j]] - jetEta[jetIDsepMET[i]]);
			if (i!=j && dEtaJet<2.5)   continue;
			
			// * Requirement on dijet mass
			v4D_dijet = v4D_jet1 + v4D_jet2;
			massDijet = v4D_dijet . M();
			if (i!=j && massDijet<500)   continue;
			
			tmpPairID . push_back (jetIDsepMET[i]);
			tmpPairID . push_back (jetIDsepMET[j]);
			jetIDPair . push_back (tmpPairID);
		}
	}
	
	
	// + Separation of jets and photon
	//--------------------------------
	phoIDsel . clear ();
	jetIDsel . clear ();
	
	float dRPhoJet1;
	float dRPhoJet2;
	
	float pxPho;
	float pyPho;
	float pxMET;
	float pyMET;
	
	float phiPhoMET;
	float phiDijet;
	float phiZGvsJJ;
	
	for (unsigned int i=0; i<jetIDPair.size(); i++)
	{
		for (unsigned int j=0; j<phoIDsepMET.size(); j++)
		{
			// * Jet separation
			dRPhoJet1 = compute_DeltaR (phoEta[phoIDsepMET[j]], jetEta[jetIDPair[i][0]], phoPhi[phoIDsepMET[j]], jetPhi[jetIDPair[i][0]]);
			dRPhoJet2 = compute_DeltaR (phoEta[phoIDsepMET[j]], jetEta[jetIDPair[i][1]], phoPhi[phoIDsepMET[j]], jetPhi[jetIDPair[i][1]]);
			
			if (dRPhoJet1<0.5 || dRPhoJet2<0.5)   continue;
			
			
			
			// * Delta Phi between jj and Zg
			pxPho = phoCalibEt[phoIDsepMET[j]] * cos (phoPhi[phoIDsepMET[j]]);
			pyPho = phoCalibEt[phoIDsepMET[j]] * sin (phoPhi[phoIDsepMET[j]]);
			pxMET = pfMETCor * cos (pfMETCorPhi);
			pyMET = pfMETCor * sin (pfMETCorPhi);
			//phiPhoMET = atan ((pyPho+pyMET) / (pxPho+pxMET));
			phiPhoMET = atan2 (pyPho+pyMET, pxPho+pxMET);
			
			v4D_jet1 . SetPtEtaPhiM (jetPt[jetIDPair[i][0]], jetEta[jetIDPair[i][0]], jetPhi[jetIDPair[i][0]], jetMass[jetIDPair[i][0]]);
			v4D_jet2 . SetPtEtaPhiM (jetPt[jetIDPair[i][1]], jetEta[jetIDPair[i][1]], jetPhi[jetIDPair[i][1]], jetMass[jetIDPair[i][1]]);
			v4D_dijet = v4D_jet1 + v4D_jet2;
			phiDijet = v4D_dijet . Phi();
			
			phiZGvsJJ = compute_DeltaPhi(phiPhoMET, phiDijet);
			
			if (phiZGvsJJ<1.90)   continue;
			
			
			
			// * Insert the value to your vector
			phoIDsel . push_back (phoIDsepMET[j]);
			jetIDsel . push_back (jetIDPair[i][0]);
			jetIDsel . push_back (jetIDPair[i][1]);
		}
	}
}















// + Use a loose VBS selection & Select the back to back pho-MET
//==============================================================
// * For ggNtuple
//---------------
void Select_Event_VBSLoose_ChooseBtB (TreeReader &file_input,   bool useCorMETOnly,   int year,   vector<Int_t> &phoIDsel,   vector<Int_t> &jetIDsel)
{
	// + Read the variables
	//---------------------
	// * Photon
	int     nPho        = file_input . GetInt      ("nPho");
	float  *phoCalibEt  = file_input . GetPtrFloat ("phoCalibEt");
	float  *phoEta      = file_input . GetPtrFloat ("phoEta");
	float  *phoPhi      = file_input . GetPtrFloat ("phoPhi");
	
	// * Jet
	int     nJet        = file_input . GetInt      ("nJet");
	float  *jetPt       = file_input . GetPtrFloat ("jetPt");
	float  *jetEta      = file_input . GetPtrFloat ("jetEta");
	float  *jetPhi      = file_input . GetPtrFloat ("jetPhi");
	float  *jetEn       = file_input . GetPtrFloat ("jetEn");
	float   pfMET       = file_input . GetFloat    ("pfMET");
	float   pfMETPhi    = file_input . GetFloat    ("pfMETPhi");
	float   pfMETCor    = file_input . GetFloat    ("pfMETCor");
	float   pfMETCorPhi = file_input . GetFloat    ("pfMETCorPhi");
	
	
	
	// + Separation of MET and photon
	//-------------------------------
	vector<int>  phoIDsepMET;
	phoIDsepMET . clear ();
	
	for (unsigned int i=0; i<nPho; i++)
	{
		Float_t delPhi = (useCorMETOnly) ? compute_DeltaPhi (phoPhi[i], pfMETCorPhi) : compute_DeltaPhi (phoPhi[i], pfMETPhi);
		if (delPhi < 2.6)   continue;
		
		Float_t EToverMET = phoCalibEt[i]/pfMETCor;
		if (EToverMET > 2.50)   continue;
		
		phoIDsepMET . push_back (i);
	}
	
	
	
	// + Separation of MET and jet
	//----------------------------
	vector<int>  jetIDsepMET;
	jetIDsepMET . clear ();
	
	for (unsigned int i=0; i<nJet; i++)
	{
		Float_t delPhi = (useCorMETOnly) ? compute_DeltaPhi (jetPhi[i], pfMETCorPhi) : compute_DeltaPhi (jetPhi[i], pfMETPhi);
		if (delPhi < 0.5)   continue;
		if (abs(jetEta[i]) > 4.7)   continue;
		
		jetIDsepMET . push_back (i);
	}
	
	
	
	// + Select tag jets (by dijet mass)
	//----------------------------------
	vector<vector<int>>  jetIDPair;
	jetIDPair . clear ();
	
	vector<int>  tmpPairID;
	tmpPairID . clear ();
	
	TLorentzVector v4D_jet1, v4D_jet2, v4D_dijet;
	float  massDijet;
	
	for (unsigned int i=0; i<jetIDsepMET.size(); i++)
	{
		massDijet = 0.0;
		v4D_jet1 . SetPtEtaPhiE (jetPt[jetIDsepMET[i]], jetEta[jetIDsepMET[i]], jetPhi[jetIDsepMET[i]], jetEn[jetIDsepMET[i]]);
		
		for (unsigned int j=i+1; j<jetIDsepMET.size(); j++)
		{
			tmpPairID . clear();
			
			// * Requirement of the deltaR between 2 jets
			v4D_jet2 . SetPtEtaPhiE (jetPt[jetIDsepMET[j]], jetEta[jetIDsepMET[j]], jetPhi[jetIDsepMET[j]], jetEn[jetIDsepMET[j]]);
			
			float  dRJet   = v4D_jet1.DeltaR(v4D_jet2);
			if (i!=j && dRJet<0.5)   continue;
			
			float  dEtaJet = abs (jetEta[jetIDsepMET[j]] - jetEta[jetIDsepMET[i]]);
			if (i!=j && dEtaJet<2.5)   continue;
			
			// * Requirement on dijet mass
			v4D_dijet = v4D_jet1 + v4D_jet2;
			massDijet = v4D_dijet . M();
			if (i!=j && massDijet<500)   continue;
			
			tmpPairID . push_back (jetIDsepMET[i]);
			tmpPairID . push_back (jetIDsepMET[j]);
			jetIDPair . push_back (tmpPairID);
		}
	}
	
	
	
	// + Separation of jets and photon
	//--------------------------------
	phoIDsel . clear ();
	jetIDsel . clear ();
	
	float dRPhoJet1;
	float dRPhoJet2;
	
	float pxPho;
	float pyPho;
	float pxMET;
	float pyMET;
	
	float phiPhoMET;
	float phiDijet;
	float phiZGvsJJ;
	
	for (unsigned int i=0; i<jetIDPair.size(); i++)
	{
		for (unsigned int j=0; j<phoIDsepMET.size(); j++)
		{
			// * Jet separation
			dRPhoJet1 = compute_DeltaR (phoEta[phoIDsepMET[j]], jetEta[jetIDPair[i][0]], phoPhi[phoIDsepMET[j]], jetPhi[jetIDPair[i][0]]);
			dRPhoJet2 = compute_DeltaR (phoEta[phoIDsepMET[j]], jetEta[jetIDPair[i][1]], phoPhi[phoIDsepMET[j]], jetPhi[jetIDPair[i][1]]);
			
			if (dRPhoJet1<0.5 || dRPhoJet2<0.5)   continue;
			
			
			
			// * Delta Phi between jj and Zg
			pxPho = phoCalibEt[phoIDsepMET[j]] * cos (phoPhi[phoIDsepMET[j]]);
			pyPho = phoCalibEt[phoIDsepMET[j]] * sin (phoPhi[phoIDsepMET[j]]);
			pxMET = pfMETCor * cos (pfMETCorPhi);
			pyMET = pfMETCor * sin (pfMETCorPhi);
			//phiPhoMET = atan ((pyPho+pyMET) / (pxPho+pxMET));
			phiPhoMET = atan2 (pyPho+pyMET, pxPho+pxMET);
			
			v4D_jet1 . SetPtEtaPhiE (jetPt[jetIDPair[i][0]], jetEta[jetIDPair[i][0]], jetPhi[jetIDPair[i][0]], jetEn[jetIDPair[i][0]]);
			v4D_jet2 . SetPtEtaPhiE (jetPt[jetIDPair[i][1]], jetEta[jetIDPair[i][1]], jetPhi[jetIDPair[i][1]], jetEn[jetIDPair[i][1]]);
			v4D_dijet = v4D_jet1 + v4D_jet2;
			phiDijet = v4D_dijet . Phi();
			
			phiZGvsJJ = compute_DeltaPhi(phiPhoMET, phiDijet);
			
			if (phiZGvsJJ<2.0)   continue;
			
			
			
			// * Insert the value to your vector
			phoIDsel . push_back (phoIDsepMET[j]);
			jetIDsel . push_back (jetIDPair[i][0]);
			jetIDsel . push_back (jetIDPair[i][1]);
		}
	}
}


// * For NanoAOD
//--------------
void Select_Event_VBSLooseNano_ChooseBtB (TreeReader &file_input,   bool useCorMETOnly,   int year,   vector<Int_t> &phoIDsel,   vector<Int_t> &jetIDsel)
{
	// + Read the variables
	//---------------------
	// * Photon
	int     nPho        = file_input . GetInt      ("nPho");
	float  *phoCalibEt  = file_input . GetPtrFloat ("phoCalibEt");
	float  *phoEta      = file_input . GetPtrFloat ("phoEta");
	float  *phoPhi      = file_input . GetPtrFloat ("phoPhi");
	
	// * Jet
	int     nJet        = file_input . GetInt      ("nJet");
	float  *jetPt       = file_input . GetPtrFloat ("jetPt");
	float  *jetEta      = file_input . GetPtrFloat ("jetEta");
	float  *jetPhi      = file_input . GetPtrFloat ("jetPhi");
	float  *jetMass     = file_input . GetPtrFloat ("jetMass");
	float   pfMET       = file_input . GetFloat    ("pfMET");
	float   pfMETPhi    = file_input . GetFloat    ("pfMETPhi");
	float   pfMETCor    = file_input . GetFloat    ("pfMETCor");
	float   pfMETCorPhi = file_input . GetFloat    ("pfMETCorPhi");
	
	
	
	// + Separation of MET and photon
	//-------------------------------
	vector<int>  phoIDsepMET;
	phoIDsepMET . clear ();
	
	for (unsigned int i=0; i<nPho; i++)
	{
		Float_t delPhi = (useCorMETOnly) ? compute_DeltaPhi (phoPhi[i], pfMETCorPhi) : compute_DeltaPhi (phoPhi[i], pfMETPhi);
		if (delPhi < 2.6)   continue;
		
		Float_t EToverMET = phoCalibEt[i]/pfMETCor;
		if (EToverMET > 2.50)   continue;
		
		phoIDsepMET . push_back (i);
	}
	
	
	
	// + Separation of MET and jet
	//----------------------------
	vector<int>  jetIDsepMET;
	jetIDsepMET . clear ();
	
	for (unsigned int i=0; i<nJet; i++)
	{
		Float_t delPhi = (useCorMETOnly) ? compute_DeltaPhi (jetPhi[i], pfMETCorPhi) : compute_DeltaPhi (jetPhi[i], pfMETPhi);
		if (delPhi < 0.5)   continue;
		if (abs(jetEta[i]) > 4.7)   continue;
		
		jetIDsepMET . push_back (i);
	}
	
	
	
	// + Select tag jets (by dijet mass)
	//----------------------------------
	vector<vector<int>>  jetIDPair;
	jetIDPair . clear ();
	
	vector<int>  tmpPairID;
	tmpPairID . clear ();
	
	TLorentzVector v4D_jet1, v4D_jet2, v4D_dijet;
	float  massDijet;
	
	for (unsigned int i=0; i<jetIDsepMET.size(); i++)
	{
		massDijet = 0.0;
		v4D_jet1 . SetPtEtaPhiM (jetPt[jetIDsepMET[i]], jetEta[jetIDsepMET[i]], jetPhi[jetIDsepMET[i]], jetMass[jetIDsepMET[i]]);
		
		for (unsigned int j=i+1; j<jetIDsepMET.size(); j++)
		{
			tmpPairID . clear();
			
			// * Requirement of the deltaR between 2 jets
			v4D_jet2 . SetPtEtaPhiM (jetPt[jetIDsepMET[j]], jetEta[jetIDsepMET[j]], jetPhi[jetIDsepMET[j]], jetMass[jetIDsepMET[j]]);
			
			float  dRJet   = v4D_jet1.DeltaR(v4D_jet2);
			if (i!=j && dRJet<0.5)   continue;
			
			float  dEtaJet = abs (jetEta[jetIDsepMET[j]] - jetEta[jetIDsepMET[i]]);
			if (i!=j && dEtaJet<2.5)   continue;
			
			// * Requirement on dijet mass
			v4D_dijet = v4D_jet1 + v4D_jet2;
			massDijet = v4D_dijet . M();
			if (i!=j && massDijet<500)   continue;
			
			tmpPairID . push_back (jetIDsepMET[i]);
			tmpPairID . push_back (jetIDsepMET[j]);
			jetIDPair . push_back (tmpPairID);
		}
	}
	
	
	
	// + Separation of jets and photon
	//--------------------------------
	phoIDsel . clear ();
	jetIDsel . clear ();
	
	float dRPhoJet1;
	float dRPhoJet2;
	
	float pxPho;
	float pyPho;
	float pxMET;
	float pyMET;
	
	float phiPhoMET;
	float phiDijet;
	float phiZGvsJJ;
	
	for (unsigned int i=0; i<jetIDPair.size(); i++)
	{
		for (unsigned int j=0; j<phoIDsepMET.size(); j++)
		{
			// * Jet separation
			dRPhoJet1 = compute_DeltaR (phoEta[phoIDsepMET[j]], jetEta[jetIDPair[i][0]], phoPhi[phoIDsepMET[j]], jetPhi[jetIDPair[i][0]]);
			dRPhoJet2 = compute_DeltaR (phoEta[phoIDsepMET[j]], jetEta[jetIDPair[i][1]], phoPhi[phoIDsepMET[j]], jetPhi[jetIDPair[i][1]]);
			
			if (dRPhoJet1<0.5 || dRPhoJet2<0.5)   continue;
			
			
			
			// * Delta Phi between jj and Zg
			pxPho = phoCalibEt[phoIDsepMET[j]] * cos (phoPhi[phoIDsepMET[j]]);
			pyPho = phoCalibEt[phoIDsepMET[j]] * sin (phoPhi[phoIDsepMET[j]]);
			pxMET = pfMETCor * cos (pfMETCorPhi);
			pyMET = pfMETCor * sin (pfMETCorPhi);
			//phiPhoMET = atan ((pyPho+pyMET) / (pxPho+pxMET));
			phiPhoMET = atan2 (pyPho+pyMET, pxPho+pxMET);
			
			v4D_jet1 . SetPtEtaPhiM (jetPt[jetIDPair[i][0]], jetEta[jetIDPair[i][0]], jetPhi[jetIDPair[i][0]], jetMass[jetIDPair[i][0]]);
			v4D_jet2 . SetPtEtaPhiM (jetPt[jetIDPair[i][1]], jetEta[jetIDPair[i][1]], jetPhi[jetIDPair[i][1]], jetMass[jetIDPair[i][1]]);
			v4D_dijet = v4D_jet1 + v4D_jet2;
			phiDijet = v4D_dijet . Phi();
			
			phiZGvsJJ = compute_DeltaPhi(phiPhoMET, phiDijet);
			
			if (phiZGvsJJ<2.0)   continue;
			
			
			
			// * Insert the value to your vector
			phoIDsel . push_back (phoIDsepMET[j]);
			jetIDsel . push_back (jetIDPair[i][0]);
			jetIDsel . push_back (jetIDPair[i][1]);
		}
	}
}















// + Use a tighter VBS selection
//==============================
// * For ggNtuple
//---------------
void Select_Event_VBSTight (TreeReader &file_input,   bool useCorMETOnly,   int year,   vector<Int_t> &phoIDsel,   vector<Int_t> &jetIDsel)
{
	// + Read the variables
	//---------------------
	// * Photon
	int     nPho        = file_input . GetInt      ("nPho");
	float  *phoCalibEt  = file_input . GetPtrFloat ("phoCalibEt");
	float  *phoEta      = file_input . GetPtrFloat ("phoEta");
	float  *phoPhi      = file_input . GetPtrFloat ("phoPhi");
	
	// * Jet
	int     nJet        = file_input . GetInt      ("nJet");
	float  *jetPt       = file_input . GetPtrFloat ("jetPt");
	float  *jetEta      = file_input . GetPtrFloat ("jetEta");
	float  *jetPhi      = file_input . GetPtrFloat ("jetPhi");
	float  *jetEn       = file_input . GetPtrFloat ("jetEn");
	float   pfMET       = file_input . GetFloat    ("pfMET");
	float   pfMETPhi    = file_input . GetFloat    ("pfMETPhi");
	float   pfMETCor    = file_input . GetFloat    ("pfMETCor");
	float   pfMETCorPhi = file_input . GetFloat    ("pfMETCorPhi");
	
	
	
	// + Separation of MET and photon
	//-------------------------------
	vector<int>  phoIDsepMET;
	phoIDsepMET . clear ();
	
	for (unsigned int i=0; i<nPho; i++)
	{
		Float_t delPhi = (useCorMETOnly) ? compute_DeltaPhi (phoPhi[i], pfMETCorPhi) : compute_DeltaPhi (phoPhi[i], pfMETPhi);
		if (delPhi < 1.5)   continue;
		
		Float_t EToverMET = phoCalibEt[i]/pfMETCor;
		if (EToverMET > 2.00)   continue;
		
		phoIDsepMET . push_back (i);
	}
	
	
	
	// + Separation of MET and jet
	//----------------------------
	vector<int>  jetIDsepMET;
	jetIDsepMET . clear ();
	
	for (unsigned int i=0; i<nJet; i++)
	{
		Float_t delPhi = (useCorMETOnly) ? compute_DeltaPhi (jetPhi[i], pfMETCorPhi) : compute_DeltaPhi (jetPhi[i], pfMETPhi);
		if (delPhi < 0.5)   continue;
		if (abs(jetEta[i]) > 4.7)   continue;
		
		jetIDsepMET . push_back (i);
	}
	
	
	
	// + Select tag jets (by dijet mass)
	//----------------------------------
	vector<vector<int>>  jetIDPair;
	jetIDPair . clear ();
	
	vector<int>  tmpPairID;
	tmpPairID . clear ();
	
	TLorentzVector v4D_jet1, v4D_jet2, v4D_dijet;
	float  massDijet;
	
	for (unsigned int i=0; i<jetIDsepMET.size(); i++)
	{
		massDijet = 0.0;
		v4D_jet1 . SetPtEtaPhiE (jetPt[jetIDsepMET[i]], jetEta[jetIDsepMET[i]], jetPhi[jetIDsepMET[i]], jetEn[jetIDsepMET[i]]);
		
		for (unsigned int j=i+1; j<jetIDsepMET.size(); j++)
		{
			tmpPairID . clear();
			
			// * Requirement of the deltaR between 2 jets
			v4D_jet2 . SetPtEtaPhiE (jetPt[jetIDsepMET[j]], jetEta[jetIDsepMET[j]], jetPhi[jetIDsepMET[j]], jetEn[jetIDsepMET[j]]);
			
			float  dRJet   = v4D_jet1.DeltaR(v4D_jet2);
			if (i!=j && dRJet<0.5)   continue;
			
			float  dEtaJet = abs (jetEta[jetIDsepMET[j]] - jetEta[jetIDsepMET[i]]);
			if (i!=j && dEtaJet<2.5)   continue;
			
			// * Requirement on dijet mass
			v4D_dijet = v4D_jet1 + v4D_jet2;
			massDijet = v4D_dijet . M();
			if (i!=j && massDijet<500)   continue;
			
			tmpPairID . push_back (jetIDsepMET[i]);
			tmpPairID . push_back (jetIDsepMET[j]);
			jetIDPair . push_back (tmpPairID);
		}
	}
	
	
	
	// + Separation of jets and photon
	//--------------------------------
	phoIDsel . clear ();
	jetIDsel . clear ();
	
	float dRPhoJet1;
	float dRPhoJet2;
	
	float pxPho;
	float pyPho;
	float pxMET;
	float pyMET;
	
	float phiPhoMET;
	float phiDijet;
	float phiZGvsJJ;
	
	for (unsigned int i=0; i<jetIDPair.size(); i++)
	{
		for (unsigned int j=0; j<phoIDsepMET.size(); j++)
		{
			// * Jet separation
			dRPhoJet1 = compute_DeltaR (phoEta[phoIDsepMET[j]], jetEta[jetIDPair[i][0]], phoPhi[phoIDsepMET[j]], jetPhi[jetIDPair[i][0]]);
			dRPhoJet2 = compute_DeltaR (phoEta[phoIDsepMET[j]], jetEta[jetIDPair[i][1]], phoPhi[phoIDsepMET[j]], jetPhi[jetIDPair[i][1]]);
			
			if (dRPhoJet1<0.5 || dRPhoJet2<0.5)   continue;
			
			
			
			// * Delta Phi between jj and Zg
			pxPho = phoCalibEt[phoIDsepMET[j]] * cos (phoPhi[phoIDsepMET[j]]);
			pyPho = phoCalibEt[phoIDsepMET[j]] * sin (phoPhi[phoIDsepMET[j]]);
			pxMET = pfMETCor * cos (pfMETCorPhi);
			pyMET = pfMETCor * sin (pfMETCorPhi);
			//phiPhoMET = atan ((pyPho+pyMET) / (pxPho+pxMET));
			phiPhoMET = atan2 (pyPho+pyMET, pxPho+pxMET);
			
			v4D_jet1 . SetPtEtaPhiE (jetPt[jetIDPair[i][0]], jetEta[jetIDPair[i][0]], jetPhi[jetIDPair[i][0]], jetEn[jetIDPair[i][0]]);
			v4D_jet2 . SetPtEtaPhiE (jetPt[jetIDPair[i][1]], jetEta[jetIDPair[i][1]], jetPhi[jetIDPair[i][1]], jetEn[jetIDPair[i][1]]);
			v4D_dijet = v4D_jet1 + v4D_jet2;
			phiDijet = v4D_dijet . Phi();
			
			phiZGvsJJ = compute_DeltaPhi(phiPhoMET, phiDijet);
			
			if (phiZGvsJJ<2.5)   continue;
			
			
			
			// * Insert the value to your vector
			phoIDsel . push_back (phoIDsepMET[j]);
			jetIDsel . push_back (jetIDPair[i][0]);
			jetIDsel . push_back (jetIDPair[i][1]);
		}
	}
}


// * For NanoAOD
//--------------
void Select_Event_VBSTightNano (TreeReader &file_input,   bool useCorMETOnly,   int year,   vector<Int_t> &phoIDsel,   vector<Int_t> &jetIDsel)
{
	// + Read the variables
	//---------------------
	// * Photon
	int     nPho        = file_input . GetInt      ("nPho");
	float  *phoCalibEt  = file_input . GetPtrFloat ("phoCalibEt");
	float  *phoEta      = file_input . GetPtrFloat ("phoEta");
	float  *phoPhi      = file_input . GetPtrFloat ("phoPhi");
	
	// * Jet
	int     nJet        = file_input . GetInt      ("nJet");
	float  *jetPt       = file_input . GetPtrFloat ("jetPt");
	float  *jetEta      = file_input . GetPtrFloat ("jetEta");
	float  *jetPhi      = file_input . GetPtrFloat ("jetPhi");
	float  *jetMass     = file_input . GetPtrFloat ("jetMass");
	float   pfMET       = file_input . GetFloat    ("pfMET");
	float   pfMETPhi    = file_input . GetFloat    ("pfMETPhi");
	float   pfMETCor    = file_input . GetFloat    ("pfMETCor");
	float   pfMETCorPhi = file_input . GetFloat    ("pfMETCorPhi");
	
	
	
	// + Separation of MET and photon
	//-------------------------------
	vector<int>  phoIDsepMET;
	phoIDsepMET . clear ();
	
	for (unsigned int i=0; i<nPho; i++)
	{
		Float_t delPhi = (useCorMETOnly) ? compute_DeltaPhi (phoPhi[i], pfMETCorPhi) : compute_DeltaPhi (phoPhi[i], pfMETPhi);
		if (delPhi < 1.5)   continue;
		
		Float_t EToverMET = phoCalibEt[i]/pfMETCor;
		if (EToverMET > 2.00)   continue;
		
		phoIDsepMET . push_back (i);
	}
	
	
	
	// + Separation of MET and jet
	//----------------------------
	vector<int>  jetIDsepMET;
	jetIDsepMET . clear ();
	
	for (unsigned int i=0; i<nJet; i++)
	{
		Float_t delPhi = (useCorMETOnly) ? compute_DeltaPhi (jetPhi[i], pfMETCorPhi) : compute_DeltaPhi (jetPhi[i], pfMETPhi);
		if (delPhi < 0.5)   continue;
		if (abs(jetEta[i]) > 4.7)   continue;
		
		jetIDsepMET . push_back (i);
	}
	
	
	
	// + Select tag jets (by dijet mass)
	//----------------------------------
	vector<vector<int>>  jetIDPair;
	jetIDPair . clear ();
	
	vector<int>  tmpPairID;
	tmpPairID . clear ();
	
	TLorentzVector v4D_jet1, v4D_jet2, v4D_dijet;
	float  massDijet;
	
	for (unsigned int i=0; i<jetIDsepMET.size(); i++)
	{
		massDijet = 0.0;
		v4D_jet1 . SetPtEtaPhiM (jetPt[jetIDsepMET[i]], jetEta[jetIDsepMET[i]], jetPhi[jetIDsepMET[i]], jetMass[jetIDsepMET[i]]);
		
		for (unsigned int j=i+1; j<jetIDsepMET.size(); j++)
		{
			tmpPairID . clear();
			
			// * Requirement of the deltaR between 2 jets
			v4D_jet2 . SetPtEtaPhiM (jetPt[jetIDsepMET[j]], jetEta[jetIDsepMET[j]], jetPhi[jetIDsepMET[j]], jetMass[jetIDsepMET[j]]);
			
			float  dRJet   = v4D_jet1.DeltaR(v4D_jet2);
			if (i!=j && dRJet<0.5)   continue;
			
			float  dEtaJet = abs (jetEta[jetIDsepMET[j]] - jetEta[jetIDsepMET[i]]);
			if (i!=j && dEtaJet<2.5)   continue;
			
			// * Requirement on dijet mass
			v4D_dijet = v4D_jet1 + v4D_jet2;
			massDijet = v4D_dijet . M();
			if (i!=j && massDijet<500)   continue;
			
			tmpPairID . push_back (jetIDsepMET[i]);
			tmpPairID . push_back (jetIDsepMET[j]);
			jetIDPair . push_back (tmpPairID);
		}
	}
	
	
	
	// + Separation of jets and photon
	//--------------------------------
	phoIDsel . clear ();
	jetIDsel . clear ();
	
	float dRPhoJet1;
	float dRPhoJet2;
	
	float pxPho;
	float pyPho;
	float pxMET;
	float pyMET;
	
	float phiPhoMET;
	float phiDijet;
	float phiZGvsJJ;
	
	for (unsigned int i=0; i<jetIDPair.size(); i++)
	{
		for (unsigned int j=0; j<phoIDsepMET.size(); j++)
		{
			// * Jet separation
			dRPhoJet1 = compute_DeltaR (phoEta[phoIDsepMET[j]], jetEta[jetIDPair[i][0]], phoPhi[phoIDsepMET[j]], jetPhi[jetIDPair[i][0]]);
			dRPhoJet2 = compute_DeltaR (phoEta[phoIDsepMET[j]], jetEta[jetIDPair[i][1]], phoPhi[phoIDsepMET[j]], jetPhi[jetIDPair[i][1]]);
			
			if (dRPhoJet1<0.5 || dRPhoJet2<0.5)   continue;
			
			
			
			// * Delta Phi between jj and Zg
			pxPho = phoCalibEt[phoIDsepMET[j]] * cos (phoPhi[phoIDsepMET[j]]);
			pyPho = phoCalibEt[phoIDsepMET[j]] * sin (phoPhi[phoIDsepMET[j]]);
			pxMET = pfMETCor * cos (pfMETCorPhi);
			pyMET = pfMETCor * sin (pfMETCorPhi);
			//phiPhoMET = atan ((pyPho+pyMET) / (pxPho+pxMET));
			phiPhoMET = atan2 (pyPho+pyMET, pxPho+pxMET);
			
			v4D_jet1 . SetPtEtaPhiM (jetPt[jetIDPair[i][0]], jetEta[jetIDPair[i][0]], jetPhi[jetIDPair[i][0]], jetMass[jetIDPair[i][0]]);
			v4D_jet2 . SetPtEtaPhiM (jetPt[jetIDPair[i][1]], jetEta[jetIDPair[i][1]], jetPhi[jetIDPair[i][1]], jetMass[jetIDPair[i][1]]);
			v4D_dijet = v4D_jet1 + v4D_jet2;
			phiDijet = v4D_dijet . Phi();
			
			phiZGvsJJ = compute_DeltaPhi(phiPhoMET, phiDijet);
			
			if (phiZGvsJJ<2.5)   continue;
			
			
			
			// * Insert the value to your vector
			phoIDsel . push_back (phoIDsepMET[j]);
			jetIDsel . push_back (jetIDPair[i][0]);
			jetIDsel . push_back (jetIDPair[i][1]);
		}
	}
}















// + Use a tighter VBS selection & Remove the back to back pho-MET
//================================================================
// * For ggNtuple
//---------------
void Select_Event_VBSTight_CutBtB (TreeReader &file_input,   bool useCorMETOnly,   int year,   vector<Int_t> &phoIDsel,   vector<Int_t> &jetIDsel)
{
	// + Read the variables
	//---------------------
	// * Photon
	int     nPho        = file_input . GetInt      ("nPho");
	float  *phoCalibEt  = file_input . GetPtrFloat ("phoCalibEt");
	float  *phoEta      = file_input . GetPtrFloat ("phoEta");
	float  *phoPhi      = file_input . GetPtrFloat ("phoPhi");
	
	// * Jet
	int     nJet        = file_input . GetInt      ("nJet");
	float  *jetPt       = file_input . GetPtrFloat ("jetPt");
	float  *jetEta      = file_input . GetPtrFloat ("jetEta");
	float  *jetPhi      = file_input . GetPtrFloat ("jetPhi");
	float  *jetEn       = file_input . GetPtrFloat ("jetEn");
	float   pfMET       = file_input . GetFloat    ("pfMET");
	float   pfMETPhi    = file_input . GetFloat    ("pfMETPhi");
	float   pfMETCor    = file_input . GetFloat    ("pfMETCor");
	float   pfMETCorPhi = file_input . GetFloat    ("pfMETCorPhi");
	
	
	
	// + Separation of MET and photon
	//-------------------------------
	vector<int>  phoIDsepMET;
	phoIDsepMET . clear ();
	
	for (unsigned int i=0; i<nPho; i++)
	{
		Float_t delPhi = (useCorMETOnly) ? compute_DeltaPhi (phoPhi[i], pfMETCorPhi) : compute_DeltaPhi (phoPhi[i], pfMETPhi);
		if (delPhi<0.5 || delPhi>2.6)   continue;
		
		Float_t EToverMET = phoCalibEt[i]/pfMETCor;
		if (EToverMET > 2.00)   continue;
		
		phoIDsepMET . push_back (i);
	}
	
	
	
	// + Separation of MET and jet
	//----------------------------
	vector<int>  jetIDsepMET;
	jetIDsepMET . clear ();
	
	for (unsigned int i=0; i<nJet; i++)
	{
		Float_t delPhi = (useCorMETOnly) ? compute_DeltaPhi (jetPhi[i], pfMETCorPhi) : compute_DeltaPhi (jetPhi[i], pfMETPhi);
		if (delPhi<0.5 || delPhi>2.6)   continue;
		if (abs(jetEta[i]) > 4.7)   continue;
		
		jetIDsepMET . push_back (i);
	}
	
	
	
	// + Select tag jets (by dijet mass)
	//----------------------------------
	vector<vector<int>>  jetIDPair;
	jetIDPair . clear ();
	
	vector<int>  tmpPairID;
	tmpPairID . clear ();
	
	TLorentzVector v4D_jet1, v4D_jet2, v4D_dijet;
	float  massDijet;
	
	for (unsigned int i=0; i<jetIDsepMET.size(); i++)
	{
		massDijet = 0.0;
		v4D_jet1 . SetPtEtaPhiE (jetPt[jetIDsepMET[i]], jetEta[jetIDsepMET[i]], jetPhi[jetIDsepMET[i]], jetEn[jetIDsepMET[i]]);
		
		for (unsigned int j=i+1; j<jetIDsepMET.size(); j++)
		{
			tmpPairID . clear();
			
			// * Requirement of the deltaR between 2 jets
			v4D_jet2 . SetPtEtaPhiE (jetPt[jetIDsepMET[j]], jetEta[jetIDsepMET[j]], jetPhi[jetIDsepMET[j]], jetEn[jetIDsepMET[j]]);
			
			float  dRJet   = v4D_jet1.DeltaR(v4D_jet2);
			if (i!=j && dRJet<0.5)   continue;
			
			float  dEtaJet = abs (jetEta[jetIDsepMET[j]] - jetEta[jetIDsepMET[i]]);
			if (i!=j && dEtaJet<2.5)   continue;
			
			// * Requirement on dijet mass
			v4D_dijet = v4D_jet1 + v4D_jet2;
			massDijet = v4D_dijet . M();
			if (i!=j && massDijet<500)   continue;
			
			tmpPairID . push_back (jetIDsepMET[i]);
			tmpPairID . push_back (jetIDsepMET[j]);
			jetIDPair . push_back (tmpPairID);
		}
	}
	
	
	
	// + Separation of jets and photon
	//--------------------------------
	phoIDsel . clear ();
	jetIDsel . clear ();
	
	float dRPhoJet1;
	float dRPhoJet2;
	
	float pxPho;
	float pyPho;
	float pxMET;
	float pyMET;
	
	float phiPhoMET;
	float phiDijet;
	float phiZGvsJJ;
	
	for (unsigned int i=0; i<jetIDPair.size(); i++)
	{
		for (unsigned int j=0; j<phoIDsepMET.size(); j++)
		{
			// * Jet separation
			dRPhoJet1 = compute_DeltaR (phoEta[phoIDsepMET[j]], jetEta[jetIDPair[i][0]], phoPhi[phoIDsepMET[j]], jetPhi[jetIDPair[i][0]]);
			dRPhoJet2 = compute_DeltaR (phoEta[phoIDsepMET[j]], jetEta[jetIDPair[i][1]], phoPhi[phoIDsepMET[j]], jetPhi[jetIDPair[i][1]]);
			
			if (dRPhoJet1<0.5 || dRPhoJet2<0.5)   continue;
			
			
			
			// * Delta Phi between jj and Zg
			pxPho = phoCalibEt[phoIDsepMET[j]] * cos (phoPhi[phoIDsepMET[j]]);
			pyPho = phoCalibEt[phoIDsepMET[j]] * sin (phoPhi[phoIDsepMET[j]]);
			pxMET = pfMETCor * cos (pfMETCorPhi);
			pyMET = pfMETCor * sin (pfMETCorPhi);
			//phiPhoMET = atan ((pyPho+pyMET) / (pxPho+pxMET));
			phiPhoMET = atan2 (pyPho+pyMET, pxPho+pxMET);
			
			v4D_jet1 . SetPtEtaPhiE (jetPt[jetIDPair[i][0]], jetEta[jetIDPair[i][0]], jetPhi[jetIDPair[i][0]], jetEn[jetIDPair[i][0]]);
			v4D_jet2 . SetPtEtaPhiE (jetPt[jetIDPair[i][1]], jetEta[jetIDPair[i][1]], jetPhi[jetIDPair[i][1]], jetEn[jetIDPair[i][1]]);
			v4D_dijet = v4D_jet1 + v4D_jet2;
			phiDijet = v4D_dijet . Phi();
			
			phiZGvsJJ = compute_DeltaPhi(phiPhoMET, phiDijet);
			
			if (phiZGvsJJ<2.5)   continue;
			
			
			
			// * Insert the value to your vector
			phoIDsel . push_back (phoIDsepMET[j]);
			jetIDsel . push_back (jetIDPair[i][0]);
			jetIDsel . push_back (jetIDPair[i][1]);
		}
	}
}


// * For NanoAOD
//--------------
void Select_Event_VBSTightNano_CutBtB (TreeReader &file_input,   bool useCorMETOnly,   int year,   vector<Int_t> &phoIDsel,   vector<Int_t> &jetIDsel)
{
	// + Read the variables
	//---------------------
	// * Photon
	int     nPho        = file_input . GetInt      ("nPho");
	float  *phoCalibEt  = file_input . GetPtrFloat ("phoCalibEt");
	float  *phoEta      = file_input . GetPtrFloat ("phoEta");
	float  *phoPhi      = file_input . GetPtrFloat ("phoPhi");
	
	// * Jet
	int     nJet        = file_input . GetInt      ("nJet");
	float  *jetPt       = file_input . GetPtrFloat ("jetPt");
	float  *jetEta      = file_input . GetPtrFloat ("jetEta");
	float  *jetPhi      = file_input . GetPtrFloat ("jetPhi");
	float  *jetMass     = file_input . GetPtrFloat ("jetMass");
	float   pfMET       = file_input . GetFloat    ("pfMET");
	float   pfMETPhi    = file_input . GetFloat    ("pfMETPhi");
	float   pfMETCor    = file_input . GetFloat    ("pfMETCor");
	float   pfMETCorPhi = file_input . GetFloat    ("pfMETCorPhi");
	
	
	
	// + Separation of MET and photon
	//-------------------------------
	vector<int>  phoIDsepMET;
	phoIDsepMET . clear ();
	
	for (unsigned int i=0; i<nPho; i++)
	{
		Float_t delPhi = (useCorMETOnly) ? compute_DeltaPhi (phoPhi[i], pfMETCorPhi) : compute_DeltaPhi (phoPhi[i], pfMETPhi);
		if (delPhi<0.5 || delPhi>2.6)   continue;
		
		Float_t EToverMET = phoCalibEt[i]/pfMETCor;
		if (EToverMET > 2.00)   continue;
		
		phoIDsepMET . push_back (i);
	}
	
	
	
	// + Separation of MET and jet
	//----------------------------
	vector<int>  jetIDsepMET;
	jetIDsepMET . clear ();
	
	for (unsigned int i=0; i<nJet; i++)
	{
		Float_t delPhi = (useCorMETOnly) ? compute_DeltaPhi (jetPhi[i], pfMETCorPhi) : compute_DeltaPhi (jetPhi[i], pfMETPhi);
		if (delPhi<0.5 || delPhi>2.6)   continue;
		if (abs(jetEta[i]) > 4.7)   continue;
		
		jetIDsepMET . push_back (i);
	}
	
	
	
	// + Select tag jets (by dijet mass)
	//----------------------------------
	vector<vector<int>>  jetIDPair;
	jetIDPair . clear ();
	
	vector<int>  tmpPairID;
	tmpPairID . clear ();
	
	TLorentzVector v4D_jet1, v4D_jet2, v4D_dijet;
	float  massDijet;
	
	for (unsigned int i=0; i<jetIDsepMET.size(); i++)
	{
		massDijet = 0.0;
		v4D_jet1 . SetPtEtaPhiM (jetPt[jetIDsepMET[i]], jetEta[jetIDsepMET[i]], jetPhi[jetIDsepMET[i]], jetMass[jetIDsepMET[i]]);
		
		for (unsigned int j=i+1; j<jetIDsepMET.size(); j++)
		{
			tmpPairID . clear();
			
			// * Requirement of the deltaR between 2 jets
			v4D_jet2 . SetPtEtaPhiM (jetPt[jetIDsepMET[j]], jetEta[jetIDsepMET[j]], jetPhi[jetIDsepMET[j]], jetMass[jetIDsepMET[j]]);
			
			float  dRJet   = v4D_jet1.DeltaR(v4D_jet2);
			if (i!=j && dRJet<0.5)   continue;
			
			float  dEtaJet = abs (jetEta[jetIDsepMET[j]] - jetEta[jetIDsepMET[i]]);
			if (i!=j && dEtaJet<2.5)   continue;
			
			// * Requirement on dijet mass
			v4D_dijet = v4D_jet1 + v4D_jet2;
			massDijet = v4D_dijet . M();
			if (i!=j && massDijet<500)   continue;
			
			tmpPairID . push_back (jetIDsepMET[i]);
			tmpPairID . push_back (jetIDsepMET[j]);
			jetIDPair . push_back (tmpPairID);
		}
	}
	
	
	
	// + Separation of jets and photon
	//--------------------------------
	phoIDsel . clear ();
	jetIDsel . clear ();
	
	float dRPhoJet1;
	float dRPhoJet2;
	
	float pxPho;
	float pyPho;
	float pxMET;
	float pyMET;
	
	float phiPhoMET;
	float phiDijet;
	float phiZGvsJJ;
	
	for (unsigned int i=0; i<jetIDPair.size(); i++)
	{
		for (unsigned int j=0; j<phoIDsepMET.size(); j++)
		{
			// * Jet separation
			dRPhoJet1 = compute_DeltaR (phoEta[phoIDsepMET[j]], jetEta[jetIDPair[i][0]], phoPhi[phoIDsepMET[j]], jetPhi[jetIDPair[i][0]]);
			dRPhoJet2 = compute_DeltaR (phoEta[phoIDsepMET[j]], jetEta[jetIDPair[i][1]], phoPhi[phoIDsepMET[j]], jetPhi[jetIDPair[i][1]]);
			
			if (dRPhoJet1<0.5 || dRPhoJet2<0.5)   continue;
			
			
			
			// * Delta Phi between jj and Zg
			pxPho = phoCalibEt[phoIDsepMET[j]] * cos (phoPhi[phoIDsepMET[j]]);
			pyPho = phoCalibEt[phoIDsepMET[j]] * sin (phoPhi[phoIDsepMET[j]]);
			pxMET = pfMETCor * cos (pfMETCorPhi);
			pyMET = pfMETCor * sin (pfMETCorPhi);
			//phiPhoMET = atan ((pyPho+pyMET) / (pxPho+pxMET));
			phiPhoMET = atan2 (pyPho+pyMET, pxPho+pxMET);
			
			v4D_jet1 . SetPtEtaPhiM (jetPt[jetIDPair[i][0]], jetEta[jetIDPair[i][0]], jetPhi[jetIDPair[i][0]], jetMass[jetIDPair[i][0]]);
			v4D_jet2 . SetPtEtaPhiM (jetPt[jetIDPair[i][1]], jetEta[jetIDPair[i][1]], jetPhi[jetIDPair[i][1]], jetMass[jetIDPair[i][1]]);
			v4D_dijet = v4D_jet1 + v4D_jet2;
			phiDijet = v4D_dijet . Phi();
			
			phiZGvsJJ = compute_DeltaPhi(phiPhoMET, phiDijet);
			
			if (phiZGvsJJ<2.5)   continue;
			
			
			
			// * Insert the value to your vector
			phoIDsel . push_back (phoIDsepMET[j]);
			jetIDsel . push_back (jetIDPair[i][0]);
			jetIDsel . push_back (jetIDPair[i][1]);
		}
	}
}















// + Use a tighter VBS selection & Select the back to back pho-MET
//================================================================
// * For ggNtuple
//---------------
void Select_Event_VBSTight_ChooseBtB (TreeReader &file_input,   bool useCorMETOnly,   int year,   vector<Int_t> &phoIDsel,   vector<Int_t> &jetIDsel)
{
	// + Read the variables
	//---------------------
	// * Photon
	int     nPho        = file_input . GetInt      ("nPho");
	float  *phoCalibEt  = file_input . GetPtrFloat ("phoCalibEt");
	float  *phoEta      = file_input . GetPtrFloat ("phoEta");
	float  *phoPhi      = file_input . GetPtrFloat ("phoPhi");
	
	// * Jet
	int     nJet        = file_input . GetInt      ("nJet");
	float  *jetPt       = file_input . GetPtrFloat ("jetPt");
	float  *jetEta      = file_input . GetPtrFloat ("jetEta");
	float  *jetPhi      = file_input . GetPtrFloat ("jetPhi");
	float  *jetEn       = file_input . GetPtrFloat ("jetEn");
	float   pfMET       = file_input . GetFloat    ("pfMET");
	float   pfMETPhi    = file_input . GetFloat    ("pfMETPhi");
	float   pfMETCor    = file_input . GetFloat    ("pfMETCor");
	float   pfMETCorPhi = file_input . GetFloat    ("pfMETCorPhi");
	
	
	
	// + Separation of MET and photon
	//-------------------------------
	vector<int>  phoIDsepMET;
	phoIDsepMET . clear ();
	
	for (unsigned int i=0; i<nPho; i++)
	{
		Float_t delPhi = (useCorMETOnly) ? compute_DeltaPhi (phoPhi[i], pfMETCorPhi) : compute_DeltaPhi (phoPhi[i], pfMETPhi);
		if (delPhi < 2.6)   continue;
		
		Float_t EToverMET = phoCalibEt[i]/pfMETCor;
		if (EToverMET > 2.00)   continue;
		
		phoIDsepMET . push_back (i);
	}
	
	
	
	// + Separation of MET and jet
	//----------------------------
	vector<int>  jetIDsepMET;
	jetIDsepMET . clear ();
	
	for (unsigned int i=0; i<nJet; i++)
	{
		Float_t delPhi = (useCorMETOnly) ? compute_DeltaPhi (jetPhi[i], pfMETCorPhi) : compute_DeltaPhi (jetPhi[i], pfMETPhi);
		if (delPhi<0.5 || delPhi>2.6)   continue;
		if (abs(jetEta[i]) > 4.7)   continue;
		
		jetIDsepMET . push_back (i);
	}
	
	
	
	// + Select tag jets (by dijet mass)
	//----------------------------------
	vector<vector<int>>  jetIDPair;
	jetIDPair . clear ();
	
	vector<int>  tmpPairID;
	tmpPairID . clear ();
	
	TLorentzVector v4D_jet1, v4D_jet2, v4D_dijet;
	float  massDijet;
	
	for (unsigned int i=0; i<jetIDsepMET.size(); i++)
	{
		massDijet = 0.0;
		v4D_jet1 . SetPtEtaPhiE (jetPt[jetIDsepMET[i]], jetEta[jetIDsepMET[i]], jetPhi[jetIDsepMET[i]], jetEn[jetIDsepMET[i]]);
		
		for (unsigned int j=i+1; j<jetIDsepMET.size(); j++)
		{
			tmpPairID . clear();
			
			// * Requirement of the deltaR between 2 jets
			v4D_jet2 . SetPtEtaPhiE (jetPt[jetIDsepMET[j]], jetEta[jetIDsepMET[j]], jetPhi[jetIDsepMET[j]], jetEn[jetIDsepMET[j]]);
			
			float  dRJet   = v4D_jet1.DeltaR(v4D_jet2);
			if (i!=j && dRJet<0.5)   continue;
			
			float  dEtaJet = abs (jetEta[jetIDsepMET[j]] - jetEta[jetIDsepMET[i]]);
			if (i!=j && dEtaJet<2.5)   continue;
			
			// * Requirement on dijet mass
			v4D_dijet = v4D_jet1 + v4D_jet2;
			massDijet = v4D_dijet . M();
			if (i!=j && massDijet<500)   continue;
			
			tmpPairID . push_back (jetIDsepMET[i]);
			tmpPairID . push_back (jetIDsepMET[j]);
			jetIDPair . push_back (tmpPairID);
		}
	}
	
	
	
	// + Separation of jets and photon
	//--------------------------------
	phoIDsel . clear ();
	jetIDsel . clear ();
	
	float dRPhoJet1;
	float dRPhoJet2;
	
	float pxPho;
	float pyPho;
	float pxMET;
	float pyMET;
	
	float phiPhoMET;
	float phiDijet;
	float phiZGvsJJ;
	
	for (unsigned int i=0; i<jetIDPair.size(); i++)
	{
		for (unsigned int j=0; j<phoIDsepMET.size(); j++)
		{
			// * Jet separation
			dRPhoJet1 = compute_DeltaR (phoEta[phoIDsepMET[j]], jetEta[jetIDPair[i][0]], phoPhi[phoIDsepMET[j]], jetPhi[jetIDPair[i][0]]);
			dRPhoJet2 = compute_DeltaR (phoEta[phoIDsepMET[j]], jetEta[jetIDPair[i][1]], phoPhi[phoIDsepMET[j]], jetPhi[jetIDPair[i][1]]);
			
			if (dRPhoJet1<0.5 || dRPhoJet2<0.5)   continue;
			
			
			
			// * Delta Phi between jj and Zg
			pxPho = phoCalibEt[phoIDsepMET[j]] * cos (phoPhi[phoIDsepMET[j]]);
			pyPho = phoCalibEt[phoIDsepMET[j]] * sin (phoPhi[phoIDsepMET[j]]);
			pxMET = pfMETCor * cos (pfMETCorPhi);
			pyMET = pfMETCor * sin (pfMETCorPhi);
			//phiPhoMET = atan ((pyPho+pyMET) / (pxPho+pxMET));
			phiPhoMET = atan2 (pyPho+pyMET, pxPho+pxMET);
			
			v4D_jet1 . SetPtEtaPhiE (jetPt[jetIDPair[i][0]], jetEta[jetIDPair[i][0]], jetPhi[jetIDPair[i][0]], jetEn[jetIDPair[i][0]]);
			v4D_jet2 . SetPtEtaPhiE (jetPt[jetIDPair[i][1]], jetEta[jetIDPair[i][1]], jetPhi[jetIDPair[i][1]], jetEn[jetIDPair[i][1]]);
			v4D_dijet = v4D_jet1 + v4D_jet2;
			phiDijet = v4D_dijet . Phi();
			
			phiZGvsJJ = compute_DeltaPhi(phiPhoMET, phiDijet);
			
			if (phiZGvsJJ<2.5)   continue;
			
			
			
			// * Insert the value to your vector
			phoIDsel . push_back (phoIDsepMET[j]);
			jetIDsel . push_back (jetIDPair[i][0]);
			jetIDsel . push_back (jetIDPair[i][1]);
		}
	}
}


// * For NanoAOD
//--------------
void Select_Event_VBSTightNano_ChooseBtB (TreeReader &file_input,   bool useCorMETOnly,   int year,   vector<Int_t> &phoIDsel,   vector<Int_t> &jetIDsel)
{
	// + Read the variables
	//---------------------
	// * Photon
	int     nPho        = file_input . GetInt      ("nPho");
	float  *phoCalibEt  = file_input . GetPtrFloat ("phoCalibEt");
	float  *phoEta      = file_input . GetPtrFloat ("phoEta");
	float  *phoPhi      = file_input . GetPtrFloat ("phoPhi");
	
	// * Jet
	int     nJet        = file_input . GetInt      ("nJet");
	float  *jetPt       = file_input . GetPtrFloat ("jetPt");
	float  *jetEta      = file_input . GetPtrFloat ("jetEta");
	float  *jetPhi      = file_input . GetPtrFloat ("jetPhi");
	float  *jetMass     = file_input . GetPtrFloat ("jetMass");
	float   pfMET       = file_input . GetFloat    ("pfMET");
	float   pfMETPhi    = file_input . GetFloat    ("pfMETPhi");
	float   pfMETCor    = file_input . GetFloat    ("pfMETCor");
	float   pfMETCorPhi = file_input . GetFloat    ("pfMETCorPhi");
	
	
	
	// + Separation of MET and photon
	//-------------------------------
	vector<int>  phoIDsepMET;
	phoIDsepMET . clear ();
	
	for (unsigned int i=0; i<nPho; i++)
	{
		Float_t delPhi = (useCorMETOnly) ? compute_DeltaPhi (phoPhi[i], pfMETCorPhi) : compute_DeltaPhi (phoPhi[i], pfMETPhi);
		if (delPhi < 2.6)   continue;
		
		Float_t EToverMET = phoCalibEt[i]/pfMETCor;
		if (EToverMET > 2.00)   continue;
		
		phoIDsepMET . push_back (i);
	}
	
	
	
	// + Separation of MET and jet
	//----------------------------
	vector<int>  jetIDsepMET;
	jetIDsepMET . clear ();
	
	for (unsigned int i=0; i<nJet; i++)
	{
		Float_t delPhi = (useCorMETOnly) ? compute_DeltaPhi (jetPhi[i], pfMETCorPhi) : compute_DeltaPhi (jetPhi[i], pfMETPhi);
		if (delPhi<0.5 || delPhi>2.6)   continue;
		if (abs(jetEta[i]) > 4.7)   continue;
		
		jetIDsepMET . push_back (i);
	}
	
	
	
	// + Select tag jets (by dijet mass)
	//----------------------------------
	vector<vector<int>>  jetIDPair;
	jetIDPair . clear ();
	
	vector<int>  tmpPairID;
	tmpPairID . clear ();
	
	TLorentzVector v4D_jet1, v4D_jet2, v4D_dijet;
	float  massDijet;
	
	for (unsigned int i=0; i<jetIDsepMET.size(); i++)
	{
		massDijet = 0.0;
		v4D_jet1 . SetPtEtaPhiM (jetPt[jetIDsepMET[i]], jetEta[jetIDsepMET[i]], jetPhi[jetIDsepMET[i]], jetMass[jetIDsepMET[i]]);
		
		for (unsigned int j=i+1; j<jetIDsepMET.size(); j++)
		{
			tmpPairID . clear();
			
			// * Requirement of the deltaR between 2 jets
			v4D_jet2 . SetPtEtaPhiM (jetPt[jetIDsepMET[j]], jetEta[jetIDsepMET[j]], jetPhi[jetIDsepMET[j]], jetMass[jetIDsepMET[j]]);
			
			float  dRJet   = v4D_jet1.DeltaR(v4D_jet2);
			if (i!=j && dRJet<0.5)   continue;
			
			float  dEtaJet = abs (jetEta[jetIDsepMET[j]] - jetEta[jetIDsepMET[i]]);
			if (i!=j && dEtaJet<2.5)   continue;
			
			// * Requirement on dijet mass
			v4D_dijet = v4D_jet1 + v4D_jet2;
			massDijet = v4D_dijet . M();
			if (i!=j && massDijet<500)   continue;
			
			tmpPairID . push_back (jetIDsepMET[i]);
			tmpPairID . push_back (jetIDsepMET[j]);
			jetIDPair . push_back (tmpPairID);
		}
	}
	
	
	
	// + Separation of jets and photon
	//--------------------------------
	phoIDsel . clear ();
	jetIDsel . clear ();
	
	float dRPhoJet1;
	float dRPhoJet2;
	
	float pxPho;
	float pyPho;
	float pxMET;
	float pyMET;
	
	float phiPhoMET;
	float phiDijet;
	float phiZGvsJJ;
	
	for (unsigned int i=0; i<jetIDPair.size(); i++)
	{
		for (unsigned int j=0; j<phoIDsepMET.size(); j++)
		{
			// * Jet separation
			dRPhoJet1 = compute_DeltaR (phoEta[phoIDsepMET[j]], jetEta[jetIDPair[i][0]], phoPhi[phoIDsepMET[j]], jetPhi[jetIDPair[i][0]]);
			dRPhoJet2 = compute_DeltaR (phoEta[phoIDsepMET[j]], jetEta[jetIDPair[i][1]], phoPhi[phoIDsepMET[j]], jetPhi[jetIDPair[i][1]]);
			
			if (dRPhoJet1<0.5 || dRPhoJet2<0.5)   continue;
			
			
			
			// * Delta Phi between jj and Zg
			pxPho = phoCalibEt[phoIDsepMET[j]] * cos (phoPhi[phoIDsepMET[j]]);
			pyPho = phoCalibEt[phoIDsepMET[j]] * sin (phoPhi[phoIDsepMET[j]]);
			pxMET = pfMETCor * cos (pfMETCorPhi);
			pyMET = pfMETCor * sin (pfMETCorPhi);
			//phiPhoMET = atan ((pyPho+pyMET) / (pxPho+pxMET));
			phiPhoMET = atan2 (pyPho+pyMET, pxPho+pxMET);
			
			v4D_jet1 . SetPtEtaPhiM (jetPt[jetIDPair[i][0]], jetEta[jetIDPair[i][0]], jetPhi[jetIDPair[i][0]], jetMass[jetIDPair[i][0]]);
			v4D_jet2 . SetPtEtaPhiM (jetPt[jetIDPair[i][1]], jetEta[jetIDPair[i][1]], jetPhi[jetIDPair[i][1]], jetMass[jetIDPair[i][1]]);
			v4D_dijet = v4D_jet1 + v4D_jet2;
			phiDijet = v4D_dijet . Phi();
			
			phiZGvsJJ = compute_DeltaPhi(phiPhoMET, phiDijet);
			
			if (phiZGvsJJ<2.5)   continue;
			
			
			
			// * Insert the value to your vector
			phoIDsel . push_back (phoIDsepMET[j]);
			jetIDsel . push_back (jetIDPair[i][0]);
			jetIDsel . push_back (jetIDPair[i][1]);
		}
	}
}


#endif
