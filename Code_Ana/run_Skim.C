#include <stdio.h>
#include <iostream>

#include "CodeAna_Skim.C"


using namespace std;





//================
// + Main function
//================
void run_Skim (int year,   bool isMC,   int file_1st,   int file_2nd)
{
	// + Some basic info
	//------------------
	TString strDTorMC[2] = {"DT", "MC"};
	printf ("\n--------------------------------------------------------------------------\n");
	printf ("Program starts, working on [ %d %s ], from file [ # %02d ] to file [ # %02d ]\n", year, strDTorMC[isMC].Data(), file_1st, file_2nd);
	printf ("--------------------------------------------------------------------------\n\n");
	
	
	
	// + Start time
	//-------------
	time_t time1 = time(0);
	
	
	// * Create neccesary derectories
	//===============================
	system ("mkdir -p /home/hoa/Task_ZgVBS/Output/Tree_miniMC/");
	system ("mkdir -p /home/hoa/Task_ZgVBS/Output/Tree_miniDT/");
	
	
	
	
	
	// + NOTE input directories
	//-------------------------
	// * Directories for 2016
	TString name_inputpathDT2016[7] =
	{
		"/data1/ggNtuples/V10_02_10_07/job_SinglePho_Run2016B_Legacy/",
		"/data1/ggNtuples/V10_02_10_07/job_SinglePho_Run2016C_Legacy/",
		"/data1/ggNtuples/V10_02_10_07/job_SinglePho_Run2016D_Legacy/",
		"/data1/ggNtuples/V10_02_10_07/job_SinglePho_Run2016E_Legacy/",
		"/data1/ggNtuples/V10_02_10_07/job_SinglePho_Run2016F_Legacy/",
		"/data1/ggNtuples/V10_02_10_07/job_SinglePho_Run2016G_Legacy/",
		"/data1/ggNtuples/V10_02_10_07/job_SinglePho_Run2016H_Legacy/"
	};
	TString name_inputpathMC2016[48] =
	{
		// * Drell-Yan (Visible)
		/*01*/"/data6/ggNtuples/V10_02_10_07/job_summer16_DYJetsToLL_m50_MG_HT100to200*/",
		/*02*/"/data6/ggNtuples/V10_02_10_07/job_summer16_DYJetsToLL_m50_MG_HT200to400*/",
		/*03*/"/data6/ggNtuples/V10_02_10_07/job_summer16_DYJetsToLL_m50_MG_HT400to600*/",
		/*04*/"/data6/ggNtuples/V10_02_10_07/job_summer16_DYJetsToLL_m50_MG_HT600to800/",
		/*05*/"/data6/ggNtuples/V10_02_10_07/job_summer16_DYJetsToLL_m50_MG_HT800to1200/",
		/*06*/"/data6/ggNtuples/V10_02_10_07/job_summer16_DYJetsToLL_m50_MG_HT1200to2500/",
		/*07*/"/data6/ggNtuples/V10_02_10_07/job_summer16_DYJetsToLL_m50_MG_HT2500toInf/",
		// * Drell-Yan (Invisible)
		/*08*/"/data6/ggNtuples/V10_02_10_07/job_summer16_ZvvJets_HT100to200*/",
		/*09*/"/data6/ggNtuples/V10_02_10_07/job_summer16_ZvvJets_HT200to400*/",
		/*10*/"/data6/ggNtuples/V10_02_10_07/job_summer16_ZvvJets_HT400to600*/",
		/*11*/"/data6/ggNtuples/V10_02_10_07/job_summer16_ZvvJets_HT600to800/",
		/*12*/"/data6/ggNtuples/V10_02_10_07/job_summer16_ZvvJets_HT800to1200/",
		/*13*/"/data6/ggNtuples/V10_02_10_07/job_summer16_ZvvJets_HT1200to2500*/",
		/*14*/"/data6/ggNtuples/V10_02_10_07/job_summer16_ZvvJets_HT2500toInf/",
		// * Mono-boson EWK
		/*15*/"/data6/ggNtuples/V10_02_10_07/job_summer16_EWK_Wminus*/",
		/*16*/"/data6/ggNtuples/V10_02_10_07/job_summer16_EWK_Wplus*/",
		/*17*/"/data6/ggNtuples/V10_02_10_07/job_summer16_EWK_Zll*/",
		/*18*/"/data6/ggNtuples/V10_02_10_07/job_summer16_EWK_Zvv*/",
		// * Gamma + Jets
		/*19*/"/data6/ggNtuples/V10_02_10_07/job_summer16_GJets_MG_HT100to200/",
		/*20*/"/data6/ggNtuples/V10_02_10_07/job_summer16_GJets_MG_HT200to400/",
		/*21*/"/data6/ggNtuples/V10_02_10_07/job_summer16_GJets_MG_HT400to600/",
		/*22*/"/data6/ggNtuples/V10_02_10_07/job_summer16_GJets_MG_HT600toInf/",
		// * QCD multiple jets
		/*23*/"/data6/ggNtuples/V10_02_10_07/job_summer16_QCD_HT100to200/",
		/*24*/"/data6/ggNtuples/V10_02_10_07/job_summer16_QCD_HT200to300*/",
		/*25*/"/data6/ggNtuples/V10_02_10_07/job_summer16_QCD_HT300to500*/",
		/*26*/"/data6/ggNtuples/V10_02_10_07/job_summer16_QCD_HT500to700*/",
		/*27*/"/data6/ggNtuples/V10_02_10_07/job_summer16_QCD_HT700to1000*/",
		/*28*/"/data6/ggNtuples/V10_02_10_07/job_summer16_QCD_HT1000to1500*/",
		/*29*/"/data6/ggNtuples/V10_02_10_07/job_summer16_QCD_HT1500to2000*/",
		/*30*/"/data6/ggNtuples/V10_02_10_07/job_summer16_QCD_HT2000toInf*/",
		// * Tops & gamma
		/*31*/"/data6/ggNtuples/V10_02_10_07/job_summer16_TGJets*/",
		/*32*/"/data6/ggNtuples/V10_02_10_07/job_summer16_TTGJets*/",
		// * W + Jets (+ gamma)
		/*33*/"/data6/ggNtuples/V10_02_10_07/job_summer16_WJetsToLNu_MG_HT100to200*/",
		/*34*/"/data6/ggNtuples/V10_02_10_07/job_summer16_WJetsToLNu_MG_HT200to400*/",
		/*35*/"/data6/ggNtuples/V10_02_10_07/job_summer16_WJetsToLNu_MG_HT400to600*/",
		/*36*/"/data6/ggNtuples/V10_02_10_07/job_summer16_WJetsToLNu_MG_HT600to800*/",
		/*37*/"/data6/ggNtuples/V10_02_10_07/job_summer16_WJetsToLNu_MG_HT800to1200*/",
		/*38*/"/data6/ggNtuples/V10_02_10_07/job_summer16_WJetsToLNu_MG_HT1200to2500*/",
		/*39*/"/data6/ggNtuples/V10_02_10_07/job_summer16_WJetsToLNu_MG_HT2500toInf*/",
		/*40*/"/data6/ggNtuples/V10_02_10_07/job_summer16_Wg_aMCatNLO*/",
		// * Multiple boson QCD
		/*41*/"/data6/ggNtuples/V10_02_10_07/job_summer16_WW*/",
		/*42*/"/data6/ggNtuples/V10_02_10_07/job_summer16_WZ*/",
		/*43*/"/data6/ggNtuples/V10_02_10_07/job_summer16_ZZ*/",
		/*44*/"/data6/ggNtuples/V10_02_10_07/job_summer16_WWG*/",
		/*45*/"/data6/ggNtuples/V10_02_10_07/job_summer16_WZG*/",
		// * Z + Gamma QCD
		/*46*/"/data6/ggNtuples/V10_02_10_07/job_summer16_Zg_aMCatNLO/",
		/*47*/"/data6/ggNtuples/V10_02_10_07/job_summer16_Znunug_pt130/",
		// * Signal
		/*48*/"/data6/ggNtuples/V10_02_10_07/job_summer16_WZG*/"
	};
	
	
	// * Directories for 2017
	TString name_inputpathDT2017[5] =
	{
		"/data1/ggNtuples/V10_02_10_07/job_SinglePho_Run2017B_MarReminiAOD/",
		"/data1/ggNtuples/V10_02_10_07/job_SinglePho_Run2017C_MarReminiAOD/",
		"/data1/ggNtuples/V10_02_10_07/job_SinglePho_Run2017D_MarReminiAOD/",
		"/data1/ggNtuples/V10_02_10_07/job_SinglePho_Run2017E_MarReminiAOD/",
		"/data1/ggNtuples/V10_02_10_07/job_SinglePho_Run2017F_MarReminiAOD/"
	};
	TString name_inputpathMC2017[48] =
	{
		// * Drell-Yan (Visible)
		/*01*/"/data6/ggNtuples/V10_02_10_07/job_fall17_DYJetsToLL_m50_MG_HT100to200*/",
		/*02*/"/data6/ggNtuples/V10_02_10_07/job_fall17_DYJetsToLL_m50_MG_HT200to400*/",
		/*03*/"/data6/ggNtuples/V10_02_10_07/job_fall17_DYJetsToLL_m50_MG_HT400to600*/",
		/*04*/"/data6/ggNtuples/V10_02_10_07/job_fall17_DYJetsToLL_m50_MG_HT600to800/",
		/*05*/"/data6/ggNtuples/V10_02_10_07/job_fall17_DYJetsToLL_m50_MG_HT800to1200/",
		/*06*/"/data6/ggNtuples/V10_02_10_07/job_fall17_DYJetsToLL_m50_MG_HT1200to2500/",
		/*07*/"/data6/ggNtuples/V10_02_10_07/job_fall17_DYJetsToLL_m50_MG_HT2500toInf/",
		// * Drell-Yan (Invisible)
		/*08*/"/data6/ggNtuples/V10_02_10_07/job_fall17_ZvvJets_HT100to200/",
		/*09*/"/data6/ggNtuples/V10_02_10_07/job_fall17_ZvvJets_HT200to400/",
		/*10*/"/data6/ggNtuples/V10_02_10_07/job_fall17_ZvvJets_HT400to600/",
		/*11*/"/data6/ggNtuples/V10_02_10_07/job_fall17_ZvvJets_HT600to800/",
		/*12*/"/data6/ggNtuples/V10_02_10_07/job_fall17_ZvvJets_HT800to1200/",
		/*13*/"/data6/ggNtuples/V10_02_10_07/job_fall17_ZvvJets_HT1200to2500*/",
		/*14*/"/data6/ggNtuples/V10_02_10_07/job_fall17_ZvvJets_HT2500toInf/",
		// * Mono-boson EWK
		/*15*/"/data6/ggNtuples/V10_02_10_07/job_fall17_newPU_EWK_Wminus/",
		/*16*/"/data6/ggNtuples/V10_02_10_07/job_fall17_newPU_EWK_Wplus/",
		/*17*/"/data6/ggNtuples/V10_02_10_07/job_fall17_newPU_EWK_Zll/",
		/*18*/"/data6/ggNtuples/V10_02_10_07/job_fall17_newPU_EWK_Zvv/",
		// * Gamma + Jets
		/*19*/"/data6/ggNtuples/V10_02_10_07/job_fall17_GJets_MG_HT100to200/",
		/*20*/"/data6/ggNtuples/V10_02_10_07/job_fall17_GJets_MG_HT200to400/",
		/*21*/"/data6/ggNtuples/V10_02_10_07/job_fall17_GJets_MG_HT400to600/",
		/*22*/"/data6/ggNtuples/V10_02_10_07/job_fall17_GJets_MG_HT600toInf/",
		// * QCD multiple jets
		/*23*/"/data6/ggNtuples/V10_02_10_07/job_fall17_QCD_HT100to200*/",
		/*24*/"/data6/ggNtuples/V10_02_10_07/job_fall17_QCD_HT200to300/",
		/*25*/"/data6/ggNtuples/V10_02_10_07/job_fall17_QCD_HT300to500/",
		/*26*/"/data6/ggNtuples/V10_02_10_07/job_fall17_QCD_HT500to700/",
		/*27*/"/data6/ggNtuples/V10_02_10_07/job_fall17_QCD_HT700to1000/",
		/*28*/"/data6/ggNtuples/V10_02_10_07/job_fall17_QCD_HT1000to1500/",
		/*29*/"/data6/ggNtuples/V10_02_10_07/job_fall17_QCD_HT1500to2000/",
		/*30*/"/data6/ggNtuples/V10_02_10_07/job_fall17_QCD_HT2000toInf/",
		// * Tops & gamma
		/*31*/"/data6/ggNtuples/V10_02_10_07/job_fall17_TGjets/",
		/*32*/"/data6/ggNtuples/V10_02_10_07/job_fall17_newPU_TTGjets/",
		// * W + Jets (+ gamma)
		/*33*/"/data6/ggNtuples/V10_02_10_07/job_fall17_WJetsToLNu_MG_HT100to200/",
		/*34*/"/data6/ggNtuples/V10_02_10_07/job_fall17_WJetsToLNu_MG_HT200to400/",
		/*35*/"/data6/ggNtuples/V10_02_10_07/job_fall17_WJetsToLNu_MG_HT400to600/",
		/*36*/"/data6/ggNtuples/V10_02_10_07/job_fall17_WJetsToLNu_MG_HT600to800/",
		/*37*/"/data6/ggNtuples/V10_02_10_07/job_fall17_WJetsToLNu_MG_HT800to1200/",
		/*38*/"/data6/ggNtuples/V10_02_10_07/job_fall17_WJetsToLNu_MG_HT1200to2500/",
		/*39*/"/data6/ggNtuples/V10_02_10_07/job_fall17_WJetsToLNu_MG_HT2500toInf/",
		/*40*/"/data6/ggNtuples/V10_02_10_07/job_fall17_Wg_aMCatNLO*/",
		// * Multiple boson QCD
		/*41*/"/data6/ggNtuples/V10_02_10_07/job_fall17_WW/",
		/*42*/"/data6/ggNtuples/V10_02_10_07/job_fall17_WZ/",
		/*43*/"/data6/ggNtuples/V10_02_10_07/job_fall17_newPU_ZZ/",
		/*44*/"/data6/ggNtuples/V10_02_10_07/job_fall17_WWG/",
		/*45*/"/data6/ggNtuples/V10_02_10_07/job_fall17_WZG/",
		// * Z + Gamma QCD
		/*46*/"/data6/ggNtuples/V10_02_10_07/job_fall17_Zg_aMCatNLO",
		/*47*/"/data6/ggNtuples/V10_02_10_07/job_fall17_Znunug_pt130",
		// * Signal
		/*48*/"/data6/ggNtuples/V10_02_10_07/job_summer16_WZG*/"
	};
	
	// * Directories for 2018
	TString name_inputpathDT2018[4] =
	{
		"/data3/ggNtuples/V10_02_10_04/job_EGamma_Run2018A_EarlyRereco/*.root",
		"/data3/ggNtuples/V10_02_10_04/job_EGamma_Run2018B_EarlyRereco/*.root",
		"/data3/ggNtuples/V10_02_10_04/job_EGamma_Run2018C_EarlyRereco/*.root",
		"/data3/ggNtuples/V10_02_10_04/job_EGamma_Run2018D_22Jan2019/*.root"
	};
	TString name_inputpathMC2018[48] =
	{
		// * Drell-Yan (Visible)
		/*01*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_DYJetsToLL_m50_MG_HT100to200/",
		/*02*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_DYJetsToLL_m50_MG_HT200to400/",
		/*03*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_DYJetsToLL_m50_MG_HT400to600*/",
		/*04*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_DYJetsToLL_m50_MG_HT600to800/",
		/*05*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_DYJetsToLL_m50_MG_HT800to1200/",
		/*06*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_DYJetsToLL_m50_MG_HT1200to2500/",
		/*07*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_DYJetsToLL_m50_MG_HT2500toInf/",
		// * Drell-Yan (Invisible)
		/*08*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_ZvvJets_HT100to200/",
		/*09*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_ZvvJets_HT200to400/",
		/*10*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_ZvvJets_HT400to600/",
		/*11*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_ZvvJets_HT600to800/",
		/*12*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_ZvvJets_HT800to1200/",
		/*13*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_ZvvJets_HT1200to2500/",
		/*14*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_ZvvJets_HT2500toInf/",
		// * Mono-boson EWK
		/*15*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_EWK_Wminus/",
		/*16*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_EWK_Wplus/",
		/*17*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_EWK_Zll/",
		/*18*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_EWK_Zvv/",
		// * Gamma + Jets
		/*19*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_GJets_MG_HT100to200/",
		/*20*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_GJets_MG_HT200to400/",
		/*21*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_GJets_MG_HT400to600/",
		/*22*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_GJets_MG_HT600toInf/",
		// * QCD multiple jets
		/*23*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_QCD_HT100to200/",
		/*24*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_QCD_HT200to300/",
		/*25*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_QCD_HT300to500/",
		/*26*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_QCD_HT500to700/",
		/*27*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_QCD_HT700to1000/",
		/*28*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_QCD_HT1000to1500/",
		/*29*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_QCD_HT1500to2000/",
		/*30*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_QCD_HT2000toInf/",
		// * Tops & gamma
		/*31*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_TGjets/",
		/*32*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_TTGjets/",
		// * W + Jets (+ gamma)
		/*33*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_WJetsToLNu_MG_HT100to200/",
		/*34*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_WJetsToLNu_MG_HT200to400/",
		/*35*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_WJetsToLNu_MG_HT400to600/",
		/*36*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_WJetsToLNu_MG_HT600to800/",
		/*37*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_WJetsToLNu_MG_HT800to1200/",
		/*38*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_WJetsToLNu_MG_HT1200to2500/",
		/*39*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_WJetsToLNu_MG_HT2500toInf/",
		/*40*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_Wg_aMCatNLO*/",
		// * Multiple boson QCD
		/*41*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_WW/",
		/*42*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_WZ/",
		/*43*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_ZZ/",
		/*44*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_WWG/",
		/*45*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_WZG/",
		// * Z + Gamma QCD
		/*46*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_Zg_aMCatNLO/",
		/*47*/"/data6/ggNtuples/V10_02_10_07/job_autumn18_Znunug_pt130/",
		// * Signal
		/*48*/"/data6/ggNtuples/V10_02_10_07/job_summer16_WZG*/"
	};
	
	
	
	
	
	
	
	
	
	// + NOTE Output directories
	//--------------------------
	
	// * Directories for 2016
	TString name_outputpathDT2016[7] =
	{
		"/home/hoa/Task_ZgVBS/Output/Tree_miniDT/tree2016_SinglePhoB.root",
		"/home/hoa/Task_ZgVBS/Output/Tree_miniDT/tree2016_SinglePhoC.root",
		"/home/hoa/Task_ZgVBS/Output/Tree_miniDT/tree2016_SinglePhoD.root",
		"/home/hoa/Task_ZgVBS/Output/Tree_miniDT/tree2016_SinglePhoE.root",
		"/home/hoa/Task_ZgVBS/Output/Tree_miniDT/tree2016_SinglePhoF.root",
		"/home/hoa/Task_ZgVBS/Output/Tree_miniDT/tree2016_SinglePhoG.root",
		"/home/hoa/Task_ZgVBS/Output/Tree_miniDT/tree2016_SinglePhoH.root"
	};
	TString name_outputpathMC2016[48] =
	{
		//  Drell-Yan (Visible)
		/*01*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_DYJets_HT0100to0200.root",
		/*02*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_DYJets_HT0200to0400.root",
		/*03*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_DYJets_HT0400to0600.root",
		/*04*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_DYJets_HT0600to0800.root",
		/*05*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_DYJets_HT0800to1200.root",
		/*06*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_DYJets_HT1200to2500.root",
		/*07*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_DYJets_HT2500toInfi.root",
		// * Drell-Yan (Invisible)
		/*08*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_ZvvJets_HT0100to0200.root",
		/*09*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_ZvvJets_HT0200to0400.root",
		/*10*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_ZvvJets_HT0400to0600.root",
		/*11*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_ZvvJets_HT0600to0800.root",
		/*12*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_ZvvJets_HT0800to1200.root",
		/*13*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_ZvvJets_HT1200to2500.root",
		/*14*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_ZvvJets_HT2500toInfi.root",
		//  Mono-boson EWK
		/*15*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_EWK_Wminus.root",
		/*16*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_EWK_Wplus.root",
		/*17*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_EWK_Zll.root",
		/*18*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_EWK_Zvv.root",
		// * Gamma + Jets
		/*19*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_GJets_HT0100to0200.root",
		/*20*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_GJets_HT0200to0400.root",
		/*21*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_GJets_HT0400to0600.root",
		/*22*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_GJets_HT0600toInfi.root",
		// * QCD multiple jets
		/*23*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_QCD_HT0100to0200.root",
		/*24*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_QCD_HT0200to0300.root",
		/*25*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_QCD_HT0300to0500.root",
		/*26*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_QCD_HT0500to0700.root",
		/*27*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_QCD_HT0700to1000.root",
		/*28*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_QCD_HT1000to1500.root",
		/*29*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_QCD_HT1500to2000.root",
		/*30*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_QCD_HT2000toInfi.root",
		//  Tops & gamma
		/*31*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_TGJets.root",
		/*32*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_TTGJets.root",
		//  W + Jets (+ gamma)
		/*33*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_WJetsToLNu_HT0100to0200.root",
		/*34*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_WJetsToLNu_HT0200to0400.root",
		/*35*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_WJetsToLNu_HT0400to0600.root",
		/*36*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_WJetsToLNu_HT0600to0800.root",
		/*37*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_WJetsToLNu_HT0800to1200.root",
		/*38*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_WJetsToLNu_HT1200to2500.root",
		/*39*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_WJetsToLNu_HT2500toInf.root",
		/*40*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_Wg.root",
		//  Multiple boson QCD
		/*41*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_WW.root",
		/*42*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_WZ.root",
		/*43*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_ZZ.root",
		/*44*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_WWG.root",
		/*45*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_WZG.root",
		//  Z + Gamma QCD
		/*46*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_Zg.root",
		/*47*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_Znunug_pt130.root",
		//  Signal
		/*48*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree16_EWKZG.root"
	};
	
	// * Directories for 2017
	TString name_outputpathDT2017[5] =
	{
		"/home/hoa/Task_ZgVBS/Output/Tree_miniDT/tree2017_SinglePhoB.root",
		"/home/hoa/Task_ZgVBS/Output/Tree_miniDT/tree2017_SinglePhoC.root",
		"/home/hoa/Task_ZgVBS/Output/Tree_miniDT/tree2017_SinglePhoD.root",
		"/home/hoa/Task_ZgVBS/Output/Tree_miniDT/tree2017_SinglePhoE.root",
		"/home/hoa/Task_ZgVBS/Output/Tree_miniDT/tree2017_SinglePhoF.root"
	};
	TString name_outputpathMC2017[48] =
	{
		//  Drell-Yan (Visible)
		/*01*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_DYJets_HT0100to0200.root",
		/*02*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_DYJets_HT0200to0400.root",
		/*03*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_DYJets_HT0400to0600.root",
		/*04*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_DYJets_HT0600to0800.root",
		/*05*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_DYJets_HT0800to1200.root",
		/*06*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_DYJets_HT1200to2500.root",
		/*07*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_DYJets_HT2500toInfi.root",
		// * Drell-Yan (Invisible)
		/*08*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_ZvvJets_HT0100to0200.root",
		/*09*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_ZvvJets_HT0200to0400.root",
		/*10*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_ZvvJets_HT0400to0600.root",
		/*11*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_ZvvJets_HT0600to0800.root",
		/*12*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_ZvvJets_HT0800to1200.root",
		/*13*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_ZvvJets_HT1200to2500.root",
		/*14*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_ZvvJets_HT2500toInfi.root",
		//  Mono-boson EWK
		/*15*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_EWK_Wminus.root",
		/*16*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_EWK_Wplus.root",
		/*17*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_EWK_Zll.root",
		/*18*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_EWK_Zvv.root",
		// * Gamma + Jets
		/*19*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_GJets_HT0100to0200.root",
		/*20*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_GJets_HT0200to0400.root",
		/*21*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_GJets_HT0400to0600.root",
		/*22*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_GJets_HT0600toInfi.root",
		// * QCD multiple jets
		/*23*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_QCD_HT0100to0200.root",
		/*24*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_QCD_HT0200to0300.root",
		/*25*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_QCD_HT0300to0500.root",
		/*26*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_QCD_HT0500to0700.root",
		/*27*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_QCD_HT0700to1000.root",
		/*28*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_QCD_HT1000to1500.root",
		/*29*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_QCD_HT1500to2000.root",
		/*30*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_QCD_HT2000toInfi.root",
		//  Tops & gamma
		/*31*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_TGJets.root",
		/*32*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_TTGJets.root",
		//  W + Jets (+ gamma)
		/*33*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_WJetsToLNu_HT0100to0200.root",
		/*34*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_WJetsToLNu_HT0200to0400.root",
		/*35*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_WJetsToLNu_HT0400to0600.root",
		/*36*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_WJetsToLNu_HT0600to0800.root",
		/*37*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_WJetsToLNu_HT0800to1200.root",
		/*38*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_WJetsToLNu_HT1200to2500.root",
		/*39*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_WJetsToLNu_HT2500toInf.root",
		/*40*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_Wg.root",
		//  Multiple boson QCD
		/*41*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_WW.root",
		/*42*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_WZ.root",
		/*43*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_ZZ.root",
		/*44*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_WWG.root",
		/*45*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_WZG.root",
		//  Z + Gamma QCD
		/*46*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_Zg.root",
		/*47*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_Znunug_pt130.root",
		//  Signal
		/*48*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree17_EWKZG.root"
	};
	
	// * Directories for 2018
	TString name_outputpathDT2018[4] =
	{
		"/home/hoa/Task_ZgVBS/Output/Tree_miniDT/tree2018_EGammaA.root",
		"/home/hoa/Task_ZgVBS/Output/Tree_miniDT/tree2018_EGammaB.root",
		"/home/hoa/Task_ZgVBS/Output/Tree_miniDT/tree2018_EGammaC.root",
		"/home/hoa/Task_ZgVBS/Output/Tree_miniDT/tree2018_EGammaD.root"
	};
	TString name_outputpathMC2018[48] =
	{
		//  Drell-Yan (Visible)
		/*01*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_DYJets_HT0100to0200.root",
		/*02*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_DYJets_HT0200to0400.root",
		/*03*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_DYJets_HT0400to0600.root",
		/*04*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_DYJets_HT0600to0800.root",
		/*05*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_DYJets_HT0800to1200.root",
		/*06*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_DYJets_HT1200to2500.root",
		/*07*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_DYJets_HT2500toInfi.root",
		// * Drell-Yan (Invisible)
		/*08*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_ZvvJets_HT0100to0200.root",
		/*09*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_ZvvJets_HT0200to0400.root",
		/*10*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_ZvvJets_HT0400to0600.root",
		/*11*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_ZvvJets_HT0600to0800.root",
		/*12*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_ZvvJets_HT0800to1200.root",
		/*13*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_ZvvJets_HT1200to2500.root",
		/*14*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_ZvvJets_HT2500toInfi.root",
		//  Mono-boson EWK
		/*15*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_EWK_Wminus.root",
		/*16*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_EWK_Wplus.root",
		/*17*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_EWK_Zll.root",
		/*18*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_EWK_Zvv.root",
		// * Gamma + Jets
		/*19*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_GJets_HT0100to0200.root",
		/*20*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_GJets_HT0200to0400.root",
		/*21*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_GJets_HT0400to0600.root",
		/*22*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_GJets_HT0600toInfi.root",
		// * QCD multiple jets
		/*23*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_QCD_HT0100to0200.root",
		/*24*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_QCD_HT0200to0300.root",
		/*25*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_QCD_HT0300to0500.root",
		/*26*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_QCD_HT0500to0700.root",
		/*27*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_QCD_HT0700to1000.root",
		/*28*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_QCD_HT1000to1500.root",
		/*29*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_QCD_HT1500to2000.root",
		/*30*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_QCD_HT2000toInfi.root",
		//  Tops & gamma
		/*31*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_TGJets.root",
		/*32*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_TTGJets.root",
		//  W + Jets (+ gamma)
		/*33*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_WJetsToLNu_HT0100to0200.root",
		/*34*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_WJetsToLNu_HT0200to0400.root",
		/*35*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_WJetsToLNu_HT0400to0600.root",
		/*36*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_WJetsToLNu_HT0600to0800.root",
		/*37*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_WJetsToLNu_HT0800to1200.root",
		/*38*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_WJetsToLNu_HT1200to2500.root",
		/*39*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_WJetsToLNu_HT2500toInf.root",
		/*40*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_Wg.root",
		//  Multiple boson QCD
		/*41*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_WW.root",
		/*42*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_WZ.root",
		/*43*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_ZZ.root",
		/*44*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_WWG.root",
		/*45*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_WZG.root",
		//  Z + Gamma QCD
		/*46*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_Zg.root",
		/*47*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_Znunug_pt130.root",
		//  Signal
		/*48*/"/home/hoa/Task_ZgVBS/Output/Tree_miniMC/tree18_EWKZG.root"
	};
	
	
	
	// + Photon removal
	Float_t  crossSection[48] =
	{
		// * Drell-Yan (Visible)
		/*01*/147.4,
		/*02*/40.99,
		/*03*/5.678,
		/*04*/1.367,
		/*05*/0.6304,
		/*06*/0.1514,
		/*07*/0.003565,
		// * Drell-Yan (Invisible)
		/*08*/280.5,
		/*09*/77.7,
		/*10*/10.71,
		/*11*/2.562,
		/*12*/1.183,
		/*13*/0.286,
		/*14*/0.006945,
		// * Mono-boson EWK
		/*15*/20.35,
		/*16*/25.81,
		/*17*/3.99,
		/*18*/10.04,
		// * Gamma + Jets
		/*19*/5382,
		/*20*/1177,
		/*21*/132.8,
		/*22*/44.25,
		// * QCD multiple jets
		/*23*/27990000,
		/*24*/1735000,
		/*25*/366800,
		/*26*/29370,
		/*27*/6524,
		/*28*/1064,
		/*29*/121.5,
		/*30*/25.42,
		// * Tops & gamma
		/*31*/2.967,
		/*32*/3.785,
		// * W + Jets (+ gamma)
		/*33*/1343,
		/*34*/359.6,
		/*35*/48.85,
		/*36*/12.05,
		/*37*/5.501,
		/*38*/1.329,
		/*39*/0.03216,
		/*40*/179.2,
		// * Multiple boson QCD
		/*41*/118.7,
		/*42*/47.13,
		/*43*/16.523,
		/*44*/0.2147,
		/*45*/1,
		// * Z + Gamma QCD
		/*46*/117.864,
		/*47*/0.190,
		// * Signal
		/*48*/0.0037
	};
	
	
	
	// + Photon removal
	Bool_t  photonRemoval[48] =
	{
		// * Drell-Yan (Visible)
		/*01*/1,
		/*02*/1,
		/*03*/1,
		/*04*/1,
		/*05*/1,
		/*06*/1,
		/*07*/1,
		// * Drell-Yan (Invisible)
		/*08*/0,
		/*09*/0,
		/*10*/0,
		/*11*/0,
		/*12*/0,
		/*13*/0,
		/*14*/0,
		// * Mono-boson EWK
		/*15*/0,
		/*16*/0,
		/*17*/0,
		/*18*/0,
		// * Gamma + Jets
		/*19*/0,
		/*20*/0,
		/*21*/0,
		/*22*/0,
		// * QCD multiple jets
		/*23*/0,
		/*24*/0,
		/*25*/0,
		/*26*/0,
		/*27*/0,
		/*28*/0,
		/*29*/0,
		/*30*/0,
		// * Tops & gamma
		/*31*/0,
		/*32*/0,
		// * W + Jets (+ gamma)
		/*33*/0,
		/*34*/0,
		/*35*/0,
		/*36*/0,
		/*37*/0,
		/*38*/0,
		/*39*/0,
		/*40*/0,
		// * Multiple boson QCD
		/*41*/0,
		/*42*/0,
		/*43*/0,
		/*44*/0,
		/*45*/0,
		// * Z + Gamma QCD
		/*46*/0,
		/*47*/0,
		// * Signal
		/*48*/0
	};
	
	//printf("*** The value arrays has no problem.\n");
	
	// NOTE Run multiple files
	bool runJob;
	
	if (isMC==0)
	{
		for (int ifile=file_1st; ifile<file_2nd+1; ifile++)
		{
			printf("Processing file [ # %d ]\n", ifile);
			
			if (year == 2016)
			{
				runJob = CodeAna_Skim (year, isMC, name_inputpathDT2016[ifile-1], name_outputpathDT2016[ifile-1], 0, 1);
			}
			else
			{
				if (year == 2017)
				{
					runJob = CodeAna_Skim (year, isMC, name_inputpathDT2017[ifile-1], name_outputpathDT2017[ifile-1], 0, 1);
				}
				else
				{
					runJob = CodeAna_Skim (year, isMC, name_inputpathDT2018[ifile-1], name_outputpathDT2018[ifile-1], 0, 1);
				}
			}
		}
	}
	else
	{
		for (int ifile=file_1st; ifile<file_2nd+1; ifile++)
		{
			printf("Processing file [ # %d ]\n", ifile);
			if (year == 2016)
			{
				runJob = CodeAna_Skim (year, isMC, name_inputpathMC2016[ifile-1], name_outputpathMC2016[ifile-1], photonRemoval[ifile-1], crossSection[ifile-1]);
			}
			else
			{
				if (year == 2017)
				{
					runJob = CodeAna_Skim (year, isMC, name_inputpathMC2017[ifile-1], name_outputpathMC2017[ifile-1], photonRemoval[ifile-1], crossSection[ifile-1]);
				}
				else
				{
					runJob = CodeAna_Skim (year, isMC, name_inputpathMC2018[ifile-1], name_outputpathMC2018[ifile-1], photonRemoval[ifile-1], crossSection[ifile-1]);
				}
			}
		}
	}
	
	
	
	// + End time
	//-----------
	time_t time2 = time(0);
	float  deltime = float(time2 - time1) / 3600.0;
	
	printf ("----------------------------------\n");
	printf ("Program ends after [ %5.2f hours ]\n", deltime);
	printf ("----------------------------------\n");
}
