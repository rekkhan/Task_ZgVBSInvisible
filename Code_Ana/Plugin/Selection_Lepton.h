#ifndef SELECTION_LEPTON_H
#define SELECTION_LEPTON_H




using namespace std;










//==================================
// * Function to calculate lepton ID
//==================================
// * For electron
//---------------
UShort_t calID_Electron (TreeReader &file_input,   int year,   int index)
{
	// + List of variables used
	//-------------------------
	// * full5x5_sigmaIetaIeta
	// * abs(dEtaInSeed)
	// * abs(dPhiIn)
	// * H over E
	// * Rel.Comb.PF iso with EA corr
	// * abs(1/E-1/p)
	// * expected missing inner hits
	// * pass conversion veto
	return 0;
}




// * For muon
//-----------
UShort_t calID_Muon (TreeReader &file_input,   int year)
{
	return 0;
}










//=====================================
// + Function to veto loose ID electron
//=====================================
// * From ggNtuples
//-----------------
Int_t Veto_ElectronLooseID (TreeReader &file_input)
{
	Int_t    nEle;
	Int_t   *eleIDbit;
	Float_t *eleD0, *eleDz;
	Float_t *eleCalibPt, *eleEta;
	
	nEle       = file_input . GetInt      ("nEle");
	eleIDbit   = file_input . GetPtrInt   ("eleIDbit");
	eleCalibPt = file_input . GetPtrFloat ("eleCalibPt");
	eleEta     = file_input . GetPtrFloat ("eleEta");
	eleD0      = file_input . GetPtrFloat ("eleD0");
	eleDz      = file_input . GetPtrFloat ("eleDz");
	
	Int_t   nSelected = 0;
	
	
	float d0ByRegion[2] = {0.10, 0.05};
	float dzByRegion[2] = {0.20, 0.10};

	
	for (Int_t i=0; i<nEle; i++)
	{
		if ((eleIDbit[i]>>1&1) == false)   continue;
		if (eleCalibPt[i] < 10)   continue;
		
		int isEB = (abs(eleEta[i]) < 1.479) ? 1 : 0;
		
		if (eleD0[i] > d0ByRegion[isEB])   continue;
		if (eleDz[i] > dzByRegion[isEB])   continue;
		
		nSelected ++;
	}
	
	
	
	return nSelected;
}


// * From NanoAOD
//---------------
Int_t Veto_ElectronLooseIDNano (TreeReader &file_input)
{
	Int_t    nEle;
	Int_t   *eleIDbit;
	Float_t *eleD0, *eleDz;
	Float_t *eleCalibPt, *eleEta;
	
	nEle       = file_input . GetInt      ("nEle");
	eleIDbit   = file_input . GetPtrInt   ("eleIDbit");
	eleCalibPt = file_input . GetPtrFloat ("eleCalibPt");
	eleEta     = file_input . GetPtrFloat ("eleEta");
	eleD0      = file_input . GetPtrFloat ("eleD0");
	eleDz      = file_input . GetPtrFloat ("eleDz");
	
	Int_t   nSelected = 0;
	
	
	float d0ByRegion[2] = {0.10, 0.05};
	float dzByRegion[2] = {0.20, 0.10};

	
	for (Int_t i=0; i<nEle; i++)
	{
		if (eleIDbit[i] < 2)   continue;
		if (eleCalibPt[i] < 10)   continue;
		
		int isEB = (abs(eleEta[i]) < 1.479) ? 1 : 0;
		
		if (eleD0[i] > d0ByRegion[isEB])   continue;
		if (eleDz[i] > dzByRegion[isEB])   continue;
		//if (eleD0[i] > 0.05)   continue;
		//if (eleDz[i] > 0.10)   continue;
		
		nSelected ++;
	}
	
	
	
	return nSelected;
}










//=================================
// + Function to veto loose ID muon
//=================================
// * For ggNtuples
//================
Int_t Veto_MuonLooseID (TreeReader &file_input)
{
	Int_t    nMu;
	Float_t *muD0, *muDz;
	Int_t   *muIDbit;
	Float_t *muCorPt;
	
	nMu     = file_input . GetInt      ("nMu");
	muIDbit = file_input . GetPtrInt   ("muIDbit");
	muCorPt = file_input . GetPtrFloat ("muCorPt");
	muD0    = file_input . GetPtrFloat ("muD0");
	muDz    = file_input . GetPtrFloat ("muDz");
	
	Int_t   nSelected = 0;
	
	for (Int_t i=0; i<nMu; i++)
	{
		if ((muIDbit[i]>>0&1) == false)   continue;
		if (muCorPt[i] < 10)   continue;
		if (muD0[i] > 0.2)   continue;
		if (muDz[i] > 0.5)   continue;
		
		nSelected ++;
	}
	
	return nSelected;
}


// * For NanoAOD
//==============
Int_t Veto_MuonLooseIDNano (TreeReader &file_input)
{
	Int_t    nMu;
	Float_t *muD0, *muDz;
	Int_t   *muIDbit;
	Float_t *muCorPt;
	
	nMu     = file_input . GetInt      ("nMu");
	muIDbit = file_input . GetPtrInt   ("muIDbit");
	muCorPt = file_input . GetPtrFloat ("muPt");
	muD0    = file_input . GetPtrFloat ("muD0");
	muDz    = file_input . GetPtrFloat ("muDz");
	
	Int_t   nSelected = 0;
	
	for (Int_t i=0; i<nMu; i++)
	{
		if (muIDbit[i] < 1)   continue;
		if (muCorPt[i] < 10)   continue;
		if (muD0[i] > 0.2)   continue;
		if (muDz[i] > 0.5)   continue;
		
		nSelected ++;
	}
	
	return nSelected;
}










//=====================================
// * Function to select medium electron
//=====================================
void Select_ElectronMediumID (TreeReader &file_input,   vector<Int_t> &eleIDSort)
{
	vector<Int_t> eleIDSel;
	eleIDSel . clear();
	
	Int_t     nEle;
	Float_t  *eleCalibPt, *eleEta;
	UShort_t *eleIDbit;
	
	nEle       = file_input . GetInt      ("nEle");
	eleCalibPt = file_input . GetPtrFloat ("eleCalibPt");
	eleEta     = file_input . GetPtrFloat ("eleEta");
	eleIDbit   = (UShort_t*)file_input . GetPtrShort ("eleIDbit");
	
	
	for (Int_t i=0; i<nEle; i++)
	{
		if (!(eleIDbit[i]>>2&1))   continue;
		if (eleCalibPt[i] < 25)   continue;
		if (abs(eleEta[i]) > 2.5)   continue;
		if (abs(eleEta[i])>1.4442 && abs(eleEta[i])<1.566)   continue;
		
		eleIDSel . push_back (i);
	}
	
	// + Sort the vector
	//------------------
	vector<Int_t>::iterator it;
	
	if (eleIDSel.size() > 0)
	{
		eleIDSort . push_back (eleIDSel[0]);
		
		for (unsigned int i=1; i<eleIDSel.size(); i++)
		{
			bool trigins = 1;
			
			for (it=eleIDSort.begin(); it<eleIDSort.end(); it++)
			{
				if (eleCalibPt[*it] < eleCalibPt[eleIDSel[i]])
				{
					eleIDSort . insert (it, eleIDSel[i]);
					trigins = 0;
					break;
				}
			}
			
			if (trigins == 1)
			{
				eleIDSort . push_back (eleIDSel[i]);
			}
		}
	}
}



#endif
