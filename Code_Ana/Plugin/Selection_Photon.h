#ifndef SELECTION_PHOTON_H
#define SELECTION_PHOTON_H




using namespace std;
















//===========================================
// + Simple cut for mini tree (Skimming step)
//===========================================
// * For ggNutples
//----------------
void Select_MonoPhoton_SkimZgVBS (TreeReader &file_input,   Bool_t photonRemoval,   vector<Int_t> &phoIDSel)
{
	// + Prepare the vector
	//---------------------
	vector<Int_t>::iterator it;
	phoIDSel  . clear ();
	
	
	// + Variables
	//------------
	// * - From input file
	Float_t    rho;
	Int_t      nPho;
	Float_t   *phoCalibEt, *phoEta, *phoPhi;
	Int_t      nMC;
	Int_t     *mcPID;
	Float_t   *mcEta, *mcPhi;
	UShort_t  *mcStatusFlag;
	
	
	// + Get the values
	//-----------------
	// * - From file
	rho             = file_input . GetFloat    ("rho");
	nPho            = file_input . GetInt      ("nPho");
	phoCalibEt      = file_input . GetPtrFloat ("phoCalibEt");
	phoEta          = file_input . GetPtrFloat ("phoEta");
	phoPhi          = file_input . GetPtrFloat ("phoPhi");
	if (file_input . HasMC())
	{
		nMC          =            file_input . GetInt      ("nMC");
		mcPID        =            file_input . GetPtrInt   ("mcPID");
		mcEta        =            file_input . GetPtrFloat ("mcEta");
		mcPhi        =            file_input . GetPtrFloat ("mcPhi");
		mcStatusFlag = (UShort_t*)file_input . GetPtrShort ("mcStatusFlag");
	}
	
	
	// + Select the photon
	//--------------------
	for (Int_t i=0; i<nPho; i++)
	{
		// * Normal selection
		if (phoCalibEt[i] < 80)   continue;
		if (abs(phoEta[i])>2.5 || (abs(phoEta[i])<1.566 && abs(phoEta[i])>1.4442))   continue;
		
		
		if (file_input.HasMC())
		{
			bool match = 0;
			if (photonRemoval == 1)
			{
				for (int j=0; j<nMC; j++)
				{
					if (mcPID[j] != 22)   continue;
					if ((mcStatusFlag[j]>>0&0) && (mcStatusFlag[j]>>1&0))   continue;
					if (compute_DeltaR (mcEta[j], phoEta[i], mcPhi[j], phoPhi[i]) < 0.1)    match = 1;
				}
			}
			
			if (match == 1)   continue;
		}
		
		phoIDSel . push_back (i);
	}
}




// * For NanoAOD
//--------------
void Select_MonoPhoton_SkimZgVBSNano (TreeReader &file_input,   Bool_t photonRemoval,   vector<Int_t> &phoIDSel)
{
	// + Prepare the vector
	//---------------------
	vector<Int_t>::iterator it;
	phoIDSel  . clear ();
	
	
	// + Variables
	//------------
	// * - From input file
	Float_t    rho;
	Int_t      nPho;
	Float_t   *phoCalibEt, *phoEta, *phoPhi;
	Int_t      nMC;
	Int_t     *mcPID;
	Float_t   *mcEta, *mcPhi;
	UShort_t  *mcStatusFlag;
	
	
	// + Get the values
	//-----------------
	// * - From file
	nPho            = file_input . GetInt      ("nPhoton");
	phoCalibEt      = file_input . GetPtrFloat ("Photon_pt");
	phoEta          = file_input . GetPtrFloat ("Photon_eta");
	phoPhi          = file_input . GetPtrFloat ("Photon_phi");
	if (file_input . HasMC())
	{
		nMC          =            file_input . GetInt      ("nMC");
		mcPID        =            file_input . GetPtrInt   ("mcPID");
		mcEta        =            file_input . GetPtrFloat ("mcEta");
		mcPhi        =            file_input . GetPtrFloat ("mcPhi");
		mcStatusFlag = (UShort_t*)file_input . GetPtrShort ("mcStatusFlag");
	}
	
	
	// + Select the photon
	//--------------------
	for (Int_t i=0; i<nPho; i++)
	{
		// * Normal selection
		if (phoCalibEt[i] < 80)   continue;
		if (abs(phoEta[i])>2.5 || (abs(phoEta[i])<1.566 && abs(phoEta[i])>1.4442))   continue;
		
		
		if (file_input.HasMC())
		{
			bool match = 0;
			if (photonRemoval == 1)
			{
				for (int j=0; j<nMC; j++)
				{
					if (mcPID[j] != 22)   continue;
					if ((mcStatusFlag[j]>>0&0) && (mcStatusFlag[j]>>1&0))   continue;
					if (compute_DeltaR (mcEta[j], phoEta[i], mcPhi[j], phoPhi[i]) < 0.1)    match = 1;
				}
			}
			
			if (match == 1)   continue;
		}
		
		phoIDSel . push_back (i);
	}
}




// * For leptonic channel
//-----------------------
void Select_MonoPhoton_SkimZgVBSLep (TreeReader &file_input,   Bool_t photonRemoval,   vector<Int_t> &phoIDSel)
{
	// + Prepare the vector
	//---------------------
	vector<Int_t>::iterator it;
	phoIDSel  . clear ();
	
	
	// + Variables
	//------------
	// * - From input file
	Float_t    rho;
	Int_t      nPho;
	Float_t   *phoCalibEt, *phoEta, *phoPhi;
	Int_t      nMC;
	Int_t     *mcPID;
	Float_t   *mcEta, *mcPhi;
	UShort_t  *mcStatusFlag;
	
	
	// + Get the values
	//-----------------
	// * - From file
	rho             = file_input . GetFloat    ("rho");
	nPho            = file_input . GetInt      ("nPho");
	phoCalibEt      = file_input . GetPtrFloat ("phoCalibEt");
	phoEta          = file_input . GetPtrFloat ("phoEta");
	phoPhi          = file_input . GetPtrFloat ("phoPhi");
	if (file_input . HasMC())
	{
		nMC          =            file_input . GetInt      ("nMC");
		mcPID        =            file_input . GetPtrInt   ("mcPID");
		mcEta        =            file_input . GetPtrFloat ("mcEta");
		mcPhi        =            file_input . GetPtrFloat ("mcPhi");
		mcStatusFlag = (UShort_t*)file_input . GetPtrShort ("mcStatusFlag");
	}
	
	
	// + Select the photon
	//--------------------
	for (Int_t i=0; i<nPho; i++)
	{
		// * Normal selection
		if (phoCalibEt[i] < 20)   continue;
		if (abs(phoEta[i])>2.5 || (abs(phoEta[i])<1.566 && abs(phoEta[i])>1.4442))   continue;
		
		
		if (file_input.HasMC())
		{
			bool match = 0;
			if (photonRemoval == 1)
			{
				for (int j=0; j<nMC; j++)
				{
					if (mcPID[j] != 22)   continue;
					if ((mcStatusFlag[j]>>0&0) && (mcStatusFlag[j]>>1&0))   continue;
					if (compute_DeltaR (mcEta[j], phoEta[i], mcPhi[j], phoPhi[i]) < 0.1)    match = 1;
				}
			}
			
			if (match == 1)   continue;
		}
		
		phoIDSel . push_back (i);
	}
}















//===========================
// + EGamma: Photon medium ID
//===========================
// * For ggNutples
//----------------
void Select_Photon_EGMediumID (TreeReader &file_input,   vector<Int_t> &phoIDSort)
{
	// + Prepare the vector
	//---------------------
	vector<Int_t>   phoIDSel;
	vector<Int_t>::iterator it;
	phoIDSel  . clear ();
	phoIDSort . clear ();
	
	
	// + Variables
	//------------
	// * - From input file
	Float_t   rho;
	Int_t     nPho;
	Float_t  *phoCalibEt, *phoEta, *phoPhi, *phoHoverE, *phoSigmaEtaEta, *phoSigmaPhiPhi, *phoPFChIso, *phoPFPhoIso, *phoPFNeuIso, *phoSeedTime;
	Int_t    *phohasPixelSeed;
	Int_t      nMC;
	Int_t     *mcPID;
	Float_t   *mcEta, *mcPhi;
	UShort_t  *mcStatusFlag;
	// * - for calculation
	Int_t    etaInd;
	Float_t  phoCorPFChIso, phoCorPFPhoIso, phoCorPFNeuIso;
	
	
	// + Get the values
	//-----------------
	// * - From file
	rho             = file_input . GetFloat    ("rho");
	nPho            = file_input . GetInt      ("nPho");
	phoCalibEt      = file_input . GetPtrFloat ("phoCalibEt");
	phoEta          = file_input . GetPtrFloat ("phoEta");
	phoPhi          = file_input . GetPtrFloat ("phoPhi");
	phoHoverE       = file_input . GetPtrFloat ("phoHoverE");
	phoSigmaEtaEta  = file_input . GetPtrFloat ("phoSigmaEtaEta");
	phoSigmaPhiPhi  = file_input . GetPtrFloat ("phoSigmaPhiPhi");
	phoPFChIso      = file_input . GetPtrFloat ("phoPFChIso");
	phoPFPhoIso     = file_input . GetPtrFloat ("phoPFPhoIso");
	phoPFNeuIso     = file_input . GetPtrFloat ("phoPFNeuIso");
	phoSeedTime     = file_input . GetPtrFloat ("phoSeedTime");
	phohasPixelSeed = file_input . GetPtrInt   ("phohasPixelSeed");
	if (file_input . HasMC())
	{
		nMC          =            file_input . GetInt      ("nMC");
		mcPID        =            file_input . GetPtrInt   ("mcPID");
		mcEta        =            file_input . GetPtrFloat ("mcEta");
		mcPhi        =            file_input . GetPtrFloat ("mcPhi");
		mcStatusFlag = (UShort_t*)file_input . GetPtrShort ("mcStatusFlag");
	}
	
	// * - Effective area from EGamma POG
	Float_t  effareaCH[2] = {0.0112, 0.0108};
	Float_t  effareaPh[2] = {0.1113, 0.0953};
	Float_t  effareaNH[2] = {0.0668, 0.1054};
	
	
	// + Select the photon
	//--------------------
	for (Int_t i=0; i<nPho; i++)
	{
		// * Normal selection
		if (phoCalibEt[i] < 210)   continue;
		if (abs(phoEta[i]) > 1.4442)   continue;
		if (phoHoverE[i] > 0.02197)   continue;
		// * The following cut which require a minimum sigma eta-eta or phi-phi is meant to remove spike
		if (phoSigmaEtaEta[i] > 0.01015 || phoSigmaEtaEta[i] < 0.0010)   continue;
		if (phoSigmaPhiPhi[i] < 0.0010)   continue;
		// * Photon seed time is required to be less than 3 nanoseconds to reject cosmic & beam halo
		if (abs(phoSeedTime[i]) > 3)   continue;
		// * Remove electron mimicking photon
		if (phohasPixelSeed[i] == 1)   continue;
		
		// * Iso selection
		etaInd = (abs(phoEta[i]) < 1) ? 0 : 1;
		
		phoCorPFChIso = max (double(phoPFChIso[i] - rho*effareaCH[etaInd]), 0.0);
		if (phoCorPFChIso > 1.141)   continue;
		
		phoCorPFPhoIso = max (double(phoPFPhoIso[i] - rho*effareaPh[etaInd]), 0.0);
		if (phoCorPFPhoIso > (2.08 + 0.004017*phoCalibEt[i]))   continue;
		
		phoCorPFNeuIso = max (double(phoPFNeuIso[i] - rho*effareaNH[etaInd]), 0.0);
		if (phoCorPFNeuIso > (1.189 + 0.01512*phoCalibEt[i] + 0.00002259*phoCalibEt[i]*phoCalibEt[i]))   continue;
		
		phoIDSel . push_back (i);
	}
	//printf ("fuck here\n");
	
	
	// + Sort the vector
	//------------------
	if (phoIDSel.size() > 0)
	{
		phoIDSort . push_back (phoIDSel[0]);
		
		for (unsigned int i=1; i<phoIDSel.size(); i++)
		{
			bool trigins = 1;
			
			for (it=phoIDSort.begin(); it<phoIDSort.end(); it++)
			{
				if (phoCalibEt[*it] < phoCalibEt[phoIDSel[i]])
				{
					phoIDSort . insert (it, phoIDSel[i]);
					trigins = 0;
					break;
				}
			}
			
			if (trigins == 1)
			{
				phoIDSort . push_back (phoIDSel[i]);
			}
		}
	}
}




// * For NanoAOD
//--------------
void Select_Photon_EGMediumIDNano (TreeReader &file_input,   vector<Int_t> &phoIDSort)
{
	// + Prepare the vector
	//---------------------
	vector<Int_t>   phoIDSel;
	vector<Int_t>::iterator it;
	phoIDSel  . clear ();
	phoIDSort . clear ();
	
	
	// + Variables
	//------------
	// * - From input file
	Int_t     nPho;
	Float_t  *phoCalibEt, *phoEta, *phoPhi;
	Int_t    *phoIDbit;
	
	
	// + Get the values
	//-----------------
	// * - From file
	nPho       = file_input . GetInt      ("nPho");
	phoCalibEt = file_input . GetPtrFloat ("phoCalibEt");
	phoEta     = file_input . GetPtrFloat ("phoEta");
	phoPhi     = file_input . GetPtrFloat ("phoPhi");
	phoIDbit   = file_input . GetPtrInt   ("phoIDbit");
	
	
	// + Select the photon
	//--------------------
	for (Int_t i=0; i<nPho; i++)
	{
		// * Normal selection
		if (phoCalibEt[i] < 210)   continue;
		if (abs(phoEta[i]) > 1.4442)   continue;
		if (phoIDbit[i] < 2)   continue;
		
		phoIDSel . push_back (i);
	}
	//printf ("fuck here\n");
	
	
	// + Sort the vector
	//------------------
	if (phoIDSel.size() > 0)
	{
		phoIDSort . push_back (phoIDSel[0]);
		
		for (unsigned int i=1; i<phoIDSel.size(); i++)
		{
			bool trigins = 1;
			
			for (it=phoIDSort.begin(); it<phoIDSort.end(); it++)
			{
				if (phoCalibEt[*it] < phoCalibEt[phoIDSel[i]])
				{
					phoIDSort . insert (it, phoIDSel[i]);
					trigins = 0;
					break;
				}
			}
			
			if (trigins == 1)
			{
				phoIDSort . push_back (phoIDSel[i]);
			}
		}
	}
}




// * For leptonic channel
//-----------------------
void Select_Photon_EGMediumIDLep (TreeReader &file_input,   vector<Int_t> &phoIDSort)
{
	// + Prepare the vector
	//---------------------
	vector<Int_t>   phoIDSel;
	vector<Int_t>::iterator it;
	phoIDSel  . clear ();
	phoIDSort . clear ();
	
	
	// + Variables
	//------------
	// * - From input file
	Float_t   rho;
	Int_t     nPho;
	Float_t  *phoCalibEt, *phoEta, *phoPhi, *phoHoverE, *phoSigmaEtaEta, *phoSigmaPhiPhi, *phoPFChIso, *phoPFPhoIso, *phoPFNeuIso, *phoSeedTime;
	Int_t    *phohasPixelSeed;
	Int_t      nMC;
	Int_t     *mcPID;
	Float_t   *mcEta, *mcPhi;
	UShort_t  *mcStatusFlag;
	// * - for calculation
	Int_t    etaInd;
	Float_t  phoCorPFChIso, phoCorPFPhoIso, phoCorPFNeuIso;
	
	
	// + Get the values
	//-----------------
	// * - From file
	rho             = file_input . GetFloat    ("rho");
	nPho            = file_input . GetInt      ("nPho");
	phoCalibEt      = file_input . GetPtrFloat ("phoCalibEt");
	phoEta          = file_input . GetPtrFloat ("phoEta");
	phoPhi          = file_input . GetPtrFloat ("phoPhi");
	phoHoverE       = file_input . GetPtrFloat ("phoHoverE");
	phoSigmaEtaEta  = file_input . GetPtrFloat ("phoSigmaEtaEta");
	phoSigmaPhiPhi  = file_input . GetPtrFloat ("phoSigmaPhiPhi");
	phoPFChIso      = file_input . GetPtrFloat ("phoPFChIso");
	phoPFPhoIso     = file_input . GetPtrFloat ("phoPFPhoIso");
	phoPFNeuIso     = file_input . GetPtrFloat ("phoPFNeuIso");
	phoSeedTime     = file_input . GetPtrFloat ("phoSeedTime");
	phohasPixelSeed = file_input . GetPtrInt   ("phohasPixelSeed");
	if (file_input . HasMC())
	{
		nMC          =            file_input . GetInt      ("nMC");
		mcPID        =            file_input . GetPtrInt   ("mcPID");
		mcEta        =            file_input . GetPtrFloat ("mcEta");
		mcPhi        =            file_input . GetPtrFloat ("mcPhi");
		mcStatusFlag = (UShort_t*)file_input . GetPtrShort ("mcStatusFlag");
	}
	
	// * - Effective area from EGamma POG
	Float_t  effareaCH[2] = {0.0112, 0.0108};
	Float_t  effareaPh[2] = {0.1113, 0.0953};
	Float_t  effareaNH[2] = {0.0668, 0.1054};
	
	
	// + Select the photon
	//--------------------
	for (Int_t i=0; i<nPho; i++)
	{
		// * Normal selection
		if (phoCalibEt[i] < 20)   continue;
		if (abs(phoEta[i]) > 1.4442)   continue;
		if (phoHoverE[i] > 0.02197)   continue;
		if (phoSigmaEtaEta[i] > 0.01015)   continue;
		
		// * Iso selection
		etaInd = (abs(phoEta[i]) < 1) ? 0 : 1;
		
		phoCorPFChIso = max (double(phoPFChIso[i] - rho*effareaCH[etaInd]), 0.0);
		if (phoCorPFChIso > 1.141)   continue;
		
		phoCorPFPhoIso = max (double(phoPFPhoIso[i] - rho*effareaPh[etaInd]), 0.0);
		if (phoCorPFPhoIso > (2.08 + 0.004017*phoCalibEt[i]))   continue;
		
		phoCorPFNeuIso = max (double(phoPFNeuIso[i] - rho*effareaNH[etaInd]), 0.0);
		if (phoCorPFNeuIso > (1.189 + 0.01512*phoCalibEt[i] + 0.00002259*phoCalibEt[i]*phoCalibEt[i]))   continue;
		
		phoIDSel . push_back (i);
	}
	//printf ("fuck here\n");
	
	
	// + Sort the vector
	//------------------
	if (phoIDSel.size() > 0)
	{
		phoIDSort . push_back (phoIDSel[0]);
		
		for (unsigned int i=1; i<phoIDSel.size(); i++)
		{
			bool trigins = 1;
			
			for (it=phoIDSort.begin(); it<phoIDSort.end(); it++)
			{
				if (phoCalibEt[*it] < phoCalibEt[phoIDSel[i]])
				{
					phoIDSort . insert (it, phoIDSel[i]);
					trigins = 0;
					break;
				}
			}
			
			if (trigins == 1)
			{
				phoIDSort . push_back (phoIDSel[i]);
			}
		}
	}
}










//==================================
// + Other preselction ID for photon
//==================================
// + Modified photon medium ID from AN2018-178
//--------------------------------------------
void Select_Photon_ModEGMediumID (TreeReader &file_input,   vector<Int_t> &phoIDSort)
{
	// + Prepare the vector
	//---------------------
	vector<Int_t>   phoIDSel;
	vector<Int_t>::iterator it;
	phoIDSel  . clear ();
	phoIDSort . clear ();
	
	
	// + Variables
	//------------
	// * - From input file
	Float_t   rho;
	Int_t     nPho;
	Float_t  *phoCalibEt, *phoEta, *phoPhi, *phoHoverE, *phoSigmaEtaEta, *phoSigmaPhiPhi, *phoPFChWorstIso, *phoPFPhoIso, *phoPFNeuIso, *phoSeedTime;
	Int_t    *phohasPixelSeed;
	Int_t      nMC;
	Int_t     *mcPID;
	Float_t   *mcEta, *mcPhi;
	UShort_t  *mcStatusFlag;
	// * - for calculation
	Int_t    etaInd;
	Float_t  phoCorPFChWorstIso, phoCorPFPhoIso, phoCorPFNeuIso;
	
	
	// + Get the values
	//-----------------
	// * - From file
	rho             = file_input . GetFloat    ("rho");
	nPho            = file_input . GetInt      ("nPho");
	phoCalibEt      = file_input . GetPtrFloat ("phoCalibEt");
	phoEta          = file_input . GetPtrFloat ("phoEta");
	phoPhi          = file_input . GetPtrFloat ("phoPhi");
	phoHoverE       = file_input . GetPtrFloat ("phoHoverE");
	phoSigmaEtaEta  = file_input . GetPtrFloat ("phoSigmaEtaEta");
	phoSigmaPhiPhi  = file_input . GetPtrFloat ("phoSigmaPhiPhi");
	phoPFChWorstIso = file_input . GetPtrFloat ("phoPFChWorstIso");
	phoPFPhoIso     = file_input . GetPtrFloat ("phoPFPhoIso");
	phoPFNeuIso     = file_input . GetPtrFloat ("phoPFNeuIso");
	phoSeedTime     = file_input . GetPtrFloat ("phoSeedTime");
	phohasPixelSeed = file_input . GetPtrInt   ("phohasPixelSeed");
	if (file_input . HasMC())
	{
		nMC          =            file_input . GetInt      ("nMC");
		mcPID        =            file_input . GetPtrInt   ("mcPID");
		mcEta        =            file_input . GetPtrFloat ("mcEta");
		mcPhi        =            file_input . GetPtrFloat ("mcPhi");
		mcStatusFlag = (UShort_t*)file_input . GetPtrShort ("mcStatusFlag");
	}
	
	// * - Effective area from AN2018-178
	Float_t  effareaCH[2] = {0.01064, 0.10260};
	Float_t  effareaPh[2] = {0.05970, 0.08070};
	Float_t  effareaNH[2] = {0.12100, 0.11070};
	
	
	// + Select the photon
	//--------------------
	for (Int_t i=0; i<nPho; i++)
	{
		// * Normal selection
		if (phoCalibEt[i] < 210)   continue;
		if (abs(phoEta[i]) > 1.4442)   continue;
		if (phoHoverE[i] > 0.0260)   continue;
		if (phoSigmaEtaEta[i] > 0.0104 || phoSigmaEtaEta[i] < 0.0010)   continue;
		if (phoSigmaPhiPhi[i] < 0.0010)   continue;
		if (abs(phoSeedTime[i]) > 3)   continue;
		if (phohasPixelSeed[i] != 0)   continue;
		
		// * Iso selection
		if (abs(phoEta[i]) < 1)   etaInd = 0;
		else   etaInd = 1;
		
		phoCorPFChWorstIso = max (double(phoPFChWorstIso[i] - rho*effareaCH[etaInd]), 0.0);
		if (phoCorPFChWorstIso > 1.146)   continue;
		
		phoCorPFPhoIso = max (double(phoPFPhoIso[i] - rho*effareaPh[etaInd]), 0.0);
		if (phoCorPFPhoIso > (2.176 + 0.0043*phoCalibEt[i]))   continue;
		
		phoCorPFNeuIso = max (double(phoPFNeuIso[i] - rho*effareaNH[etaInd]), 0.0);
		if (phoCorPFNeuIso > (2.729 + 0.0112*phoCalibEt[i] + 0.000028*phoCalibEt[i]*phoCalibEt[i]))   continue;
		
		phoIDSel . push_back (i);
	}
	//printf ("fuck here\n");
	
	
	// + Sort the vector
	//------------------
	if (phoIDSel.size() > 0)
	{
		phoIDSort . push_back (phoIDSel[0]);
		
		for (unsigned int i=1; i<phoIDSel.size(); i++)
		{
			bool trigins = 1;
			
			for (it=phoIDSort.begin(); it<phoIDSort.end(); it++)
			{
				if (phoCalibEt[*it] < phoCalibEt[phoIDSel[i]])
				{
					phoIDSort . insert (it, phoIDSel[i]);
					trigins = 0;
					break;
				}
			}
			
			if (trigins == 1)
			{
				phoIDSort . push_back (phoIDSel[i]);
			}
		}
	}
}




// + Monophoton cut from G+Jets
void Select_Photon_GJets (TreeReader &file_input,   vector<Int_t> &phoIDSort)
{
	// + Prepare the vector
	//---------------------
	vector<Int_t>   phoIDSel;
	vector<Int_t>::iterator it;
	phoIDSel  . clear ();
	phoIDSort . clear ();
	
	
	// + Variables
	//------------
	// * - From input file
	Float_t   rho;
	Int_t     nPho;
	Float_t  *phoCalibEt, *phoEta, *phoPhi, *phoHoverE, *phoSigmaEtaEta, *phoSigmaPhiPhi, *phoPFChIso, *phoPFChWorstIso, *phoPFPhoIso, *phoPFNeuIso, *phoSeedTime;
	Int_t    *phohasPixelSeed;
	Int_t      nMC;
	Int_t     *mcPID;
	Float_t   *mcEta, *mcPhi;
	UShort_t  *mcStatusFlag;
	// * - for calculation
	Int_t    etaInd;
	bool     isBarrel;
	Float_t  phoCorPFChIso, phoCorPFPhoIso, phoCorPFNeuIso;
	
	
	// + Get the values
	//-----------------
	// * - From file
	rho             = file_input . GetFloat    ("rho");
	nPho            = file_input . GetInt      ("nPho");
	phoCalibEt      = file_input . GetPtrFloat ("phoCalibEt");
	phoEta          = file_input . GetPtrFloat ("phoEta");
	phoPhi          = file_input . GetPtrFloat ("phoPhi");
	phoHoverE       = file_input . GetPtrFloat ("phoHoverE");
	phoSigmaEtaEta  = file_input . GetPtrFloat ("phoSigmaEtaEta");
	phoPFChWorstIso = file_input . GetPtrFloat ("phoPFChWorstIso");
	phoPFChIso      = file_input . GetPtrFloat ("phoPFChIso");
	phoPFPhoIso     = file_input . GetPtrFloat ("phoPFPhoIso");
	if (file_input . HasMC())
	{
		nMC          =            file_input . GetInt      ("nMC");
		mcPID        =            file_input . GetPtrInt   ("mcPID");
		mcEta        =            file_input . GetPtrFloat ("mcEta");
		mcPhi        =            file_input . GetPtrFloat ("mcPhi");
		mcStatusFlag = (UShort_t*)file_input . GetPtrShort ("mcStatusFlag");
	}
	
	// * - Effective area from EGamma POG
	Float_t  effareaCH[2] = {0.0112, 0.0108};
	Float_t  effareaPh[2] = {0.1113, 0.0953};
	Float_t  effareaNH[2] = {0.0668, 0.1054};
	
	float  refHoverE[2]      = {0.050, 0.080};
	float  refSigmaEtaEta[2] = {0.045, 0.015};
	
	
	// + Select the photon
	//--------------------
	for (Int_t i=0; i<nPho; i++)
	{
		// * Normal selection
		if (phoCalibEt[i] < 200)   continue;
		if (abs(phoEta[i]) > 2.5)   continue;
		
		isBarrel = (abs(phoEta[i]) < 1.4442) ? 0 : 1;
		if (phoHoverE[i] > refHoverE[isBarrel])   continue;
		if (phoSigmaEtaEta[i] > refSigmaEtaEta[isBarrel])   continue;
		
		// * Iso selection
		etaInd   = (abs(phoEta[i]) < 1) ? 0 : 1;
		
		phoCorPFChIso = max (double(phoPFChIso[i] - rho*effareaCH[etaInd]), 0.0);
		//if (phoCorPFChIso > 15)   continue;
		if (phoPFChWorstIso[i] > 15)   continue;
		
		phoCorPFPhoIso = max (double(phoPFPhoIso[i] - rho*effareaPh[etaInd]), 0.0);
		if (phoCorPFPhoIso > 15)   continue;
		//if (phoPFPhoIso > 15)   continue;
		
		phoIDSel . push_back (i);
	}
	//printf ("fuck here\n");
	
	
	// + Sort the vector
	//------------------
	if (phoIDSel.size() > 0)
	{
		phoIDSort . push_back (phoIDSel[0]);
		
		for (unsigned int i=1; i<phoIDSel.size(); i++)
		{
			bool trigins = 1;
			
			for (it=phoIDSort.begin(); it<phoIDSort.end(); it++)
			{
				if (phoCalibEt[*it] < phoCalibEt[phoIDSel[i]])
				{
					phoIDSort . insert (it, phoIDSel[i]);
					trigins = 0;
					break;
				}
			}
			
			if (trigins == 1)
			{
				phoIDSort . push_back (phoIDSel[i]);
			}
		}
	}
}




// + Photon preselection step
//===========================
// + EGamma: Photon loose ID
//--------------------------
void Select_Photon_EGLooseID (TreeReader &file_input,   vector<Int_t> &phoIDSort)
{
	// + Prepare the vector
	//---------------------
	vector<Int_t>   phoIDSel;
	vector<Int_t>::iterator it;
	phoIDSel  . clear ();
	phoIDSort . clear ();
	
	
	// + Variables
	//------------
	// * - From input file
	Float_t   rho;
	Int_t     nPho;
	Float_t  *phoCalibEt, *phoEta, *phoPhi, *phoHoverE, *phoSigmaEtaEta, *phoSigmaPhiPhi, *phoPFChIso, *phoPFPhoIso, *phoPFNeuIso, *phoSeedTime;
	Int_t    *phohasPixelSeed;
	Int_t      nMC;
	Int_t     *mcPID;
	Float_t   *mcEta, *mcPhi;
	UShort_t  *mcStatusFlag;
	// * - for calculation
	Int_t    etaInd;
	Float_t  phoCorPFChIso, phoCorPFPhoIso, phoCorPFNeuIso;
	
	
	// + Get the values
	//-----------------
	// * - From file
	rho             = file_input . GetFloat    ("rho");
	nPho            = file_input . GetInt      ("nPho");
	phoCalibEt      = file_input . GetPtrFloat ("phoCalibEt");
	phoEta          = file_input . GetPtrFloat ("phoEta");
	phoPhi          = file_input . GetPtrFloat ("phoPhi");
	phoHoverE       = file_input . GetPtrFloat ("phoHoverE");
	phoSigmaEtaEta  = file_input . GetPtrFloat ("phoSigmaEtaEta");
	phoSigmaPhiPhi  = file_input . GetPtrFloat ("phoSigmaPhiPhi");
	phoPFChIso      = file_input . GetPtrFloat ("phoPFChIso");
	phoPFPhoIso     = file_input . GetPtrFloat ("phoPFPhoIso");
	phoPFNeuIso     = file_input . GetPtrFloat ("phoPFNeuIso");
	phoSeedTime     = file_input . GetPtrFloat ("phoSeedTime");
	phohasPixelSeed = file_input . GetPtrInt   ("phohasPixelSeed");
	if (file_input . HasMC())
	{
		nMC          =            file_input . GetInt      ("nMC");
		mcPID        =            file_input . GetPtrInt   ("mcPID");
		mcEta        =            file_input . GetPtrFloat ("mcEta");
		mcPhi        =            file_input . GetPtrFloat ("mcPhi");
		mcStatusFlag = (UShort_t*)file_input . GetPtrShort ("mcStatusFlag");
	}
	
	// * - Effective area from EGamma POG
	Float_t  effareaCH[2] = {0.0112, 0.0108};
	Float_t  effareaPh[2] = {0.1113, 0.0953};
	Float_t  effareaNH[2] = {0.0668, 0.1054};
	
	
	// + Select the photon
	//--------------------
	for (Int_t i=0; i<nPho; i++)
	{
		// * Normal selection
		if (phoCalibEt[i] < 210)   continue;
		if (abs(phoEta[i]) > 1.4442)   continue;
		if (phoHoverE[i] > 0.04596)   continue;
		if (phoSigmaEtaEta[i] > 0.0106)   continue;
		
		// * Iso selection
		etaInd = (abs(phoEta[i]) < 1) ? 0 : 1;
		
		phoCorPFChIso = max (double(phoPFChIso[i] - rho*effareaCH[etaInd]), 0.0);
		if (phoCorPFChIso > 1.694)   continue;
		
		phoCorPFPhoIso = max (double(phoPFPhoIso[i] - rho*effareaPh[etaInd]), 0.0);
		if (phoCorPFPhoIso > (2.876 + 0.004017*phoCalibEt[i]))   continue;
		
		phoCorPFNeuIso = max (double(phoPFNeuIso[i] - rho*effareaNH[etaInd]), 0.0);
		if (phoCorPFNeuIso > (24.032 + 0.01512*phoCalibEt[i] + 0.00002259*phoCalibEt[i]*phoCalibEt[i]))   continue;
		
		phoIDSel . push_back (i);
	}
	//printf ("fuck here\n");
	
	
	// + Sort the vector
	//------------------
	if (phoIDSel.size() > 0)
	{
		phoIDSort . push_back (phoIDSel[0]);
		
		for (unsigned int i=1; i<phoIDSel.size(); i++)
		{
			bool trigins = 1;
			
			for (it=phoIDSort.begin(); it<phoIDSort.end(); it++)
			{
				if (phoCalibEt[*it] < phoCalibEt[phoIDSel[i]])
				{
					phoIDSort . insert (it, phoIDSel[i]);
					trigins = 0;
					break;
				}
			}
			
			if (trigins == 1)
			{
				phoIDSort . push_back (phoIDSel[i]);
			}
		}
	}
}


#endif
