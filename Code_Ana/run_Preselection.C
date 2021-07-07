#include <stdio.h>
#include <iostream>


#include "CodeAna_Preselection.C"

void run_Preselection (int year,   bool isMC,   int file_1st,   int file_2nd)
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
	
	
	
	// + NOTE input directories (root)
	//--------------------------------
	// * 2016 directories
	TString name_inputpathDT2016[7] =
	{
		"/home/hoa/Task_ZgVBS/Output/Tree_miniDT/tree2016_SinglePhoB.root",
		"/home/hoa/Task_ZgVBS/Output/Tree_miniDT/tree2016_SinglePhoC.root",
		"/home/hoa/Task_ZgVBS/Output/Tree_miniDT/tree2016_SinglePhoD.root",
		"/home/hoa/Task_ZgVBS/Output/Tree_miniDT/tree2016_SinglePhoE.root",
		"/home/hoa/Task_ZgVBS/Output/Tree_miniDT/tree2016_SinglePhoF.root",
		"/home/hoa/Task_ZgVBS/Output/Tree_miniDT/tree2016_SinglePhoG.root",
		"/home/hoa/Task_ZgVBS/Output/Tree_miniDT/tree2016_SinglePhoH.root"
	};
	TString name_inputpathMC2016[48] =
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
		/*48*/"/home/hoa/Task_ZgVBS/Input_Tmp/Sample_MC/tree2017_Z2nuGammaEWK.root"
	};
	
	
	// * 2017 directories
	TString name_inputpathDT2017[5] =
	{
		"/home/hoa/Task_ZgVBS/Output/Tree_miniDT/tree2017_SinglePhoB.root",
		"/home/hoa/Task_ZgVBS/Output/Tree_miniDT/tree2017_SinglePhoC.root",
		"/home/hoa/Task_ZgVBS/Output/Tree_miniDT/tree2017_SinglePhoD.root",
		"/home/hoa/Task_ZgVBS/Output/Tree_miniDT/tree2017_SinglePhoE.root",
		"/home/hoa/Task_ZgVBS/Output/Tree_miniDT/tree2017_SinglePhoF.root"
	};
	TString name_inputpathMC2017[48] =
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
		/*48*/"/home/hoa/Task_ZgVBS/Input_Tmp/Sample_MC/tree2017_Z2nuGammaEWK.root"
	};
	
	
	// * 2018 directories
	TString name_inputpathDT2018[4] =
	{
		"/home/hoa/Task_ZgVBS/Output/Tree_miniDT/tree2018_EGammaA.root",
		"/home/hoa/Task_ZgVBS/Output/Tree_miniDT/tree2018_EGammaB.root",
		"/home/hoa/Task_ZgVBS/Output/Tree_miniDT/tree2018_EGammaC.root",
		"/home/hoa/Task_ZgVBS/Output/Tree_miniDT/tree2018_EGammaD.root"
	};
	TString name_inputpathMC2018[48] =
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
		/*48*/"/home/hoa/Task_ZgVBS/Input_Tmp/Sample_MC/tree2017_Z2nuGammaEWK.root"
	};
	
	
	
	
	
	// + NOTE Output directories (root)
	//---------------------------------
	// * 2016 directories
	TString name_outputpathDT2016[7] =
	{
		"/home/hoa/Task_ZgVBS/Output/Tree_preselDT/tree16_SinglePhoB.root",
		"/home/hoa/Task_ZgVBS/Output/Tree_preselDT/tree16_SinglePhoC.root",
		"/home/hoa/Task_ZgVBS/Output/Tree_preselDT/tree16_SinglePhoD.root",
		"/home/hoa/Task_ZgVBS/Output/Tree_preselDT/tree16_SinglePhoE.root",
		"/home/hoa/Task_ZgVBS/Output/Tree_preselDT/tree16_SinglePhoF.root",
		"/home/hoa/Task_ZgVBS/Output/Tree_preselDT/tree16_SinglePhoG.root",
		"/home/hoa/Task_ZgVBS/Output/Tree_preselDT/tree16_SinglePhoH.root"
	};
	TString name_outputpathMC2016[48] =
	{
		//  Drell-Yan (Visible)
		/*01*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_DYJets_HT0100to0200.root",
		/*02*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_DYJets_HT0200to0400.root",
		/*03*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_DYJets_HT0400to0600.root",
		/*04*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_DYJets_HT0600to0800.root",
		/*05*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_DYJets_HT0800to1200.root",
		/*06*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_DYJets_HT1200to2500.root",
		/*07*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_DYJets_HT2500toInfi.root",
		// * Drell-Yan (Invisible)
		/*08*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_DYJetsInv_HT0100to0200.root",
		/*09*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_DYJetsInv_HT0200to0400.root",
		/*10*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_DYJetsInv_HT0400to0600.root",
		/*11*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_DYJetsInv_HT0600to0800.root",
		/*12*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_DYJetsInv_HT0800to1200.root",
		/*13*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_DYJetsInv_HT1200to2500.root",
		/*14*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_DYJetsInv_HT2500toInfi.root",
		//  Mono-boson EWK
		/*15*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_WmEWK.root",
		/*16*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_WpEWK.root",
		/*17*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_Z2lepEWK.root",
		/*18*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_Z2nuEWK.root",
		// * Gamma + Jets
		/*19*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_GJets_HT0100to0200.root",
		/*20*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_GJets_HT0200to0400.root",
		/*21*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_GJets_HT0400to0600.root",
		/*22*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_GJets_HT0600toInfi.root",
		// * QCD multiple jets
		/*23*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_QCD_HT0100to0200.root",
		/*24*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_QCD_HT0200to0300.root",
		/*25*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_QCD_HT0300to0500.root",
		/*26*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_QCD_HT0500to0700.root",
		/*27*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_QCD_HT0700to1000.root",
		/*28*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_QCD_HT1000to1500.root",
		/*29*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_QCD_HT1500to2000.root",
		/*30*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_QCD_HT2000toInfi.root",
		//  Tops & gamma
		/*31*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_TGJets.root",
		/*32*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_TTGJets.root",
		//  W + Jets (+ gamma)
		/*33*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_WJetsToLNu_HT0100to0200.root",
		/*34*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_WJetsToLNu_HT0200to0400.root",
		/*35*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_WJetsToLNu_HT0400to0600.root",
		/*36*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_WJetsToLNu_HT0600to0800.root",
		/*37*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_WJetsToLNu_HT0800to1200.root",
		/*38*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_WJetsToLNu_HT1200to2500.root",
		/*39*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_WJetsToLNu_HT2500toInfi.root",
		//  Multiple boson QCD
		/*40*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_WGJets.root",
		/*41*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_WW.root",
		/*42*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_WZ.root",
		/*43*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_ZZ.root",
		/*44*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_WWG.root",
		/*45*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_WZG.root",
		/*46*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_Z2lepG.root",
		/*47*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_Z2nuG.root",
		//  Signal
		/*48*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree16_Z2nuGEWK.root"
	};
	
	
	// * 2017 directories
	TString name_outputpathDT2017[5] =
	{
		"/home/hoa/Task_ZgVBS/Output/Tree_preselDT/tree17_SinglePhoB.root",
		"/home/hoa/Task_ZgVBS/Output/Tree_preselDT/tree17_SinglePhoC.root",
		"/home/hoa/Task_ZgVBS/Output/Tree_preselDT/tree17_SinglePhoD.root",
		"/home/hoa/Task_ZgVBS/Output/Tree_preselDT/tree17_SinglePhoE.root",
		"/home/hoa/Task_ZgVBS/Output/Tree_preselDT/tree17_SinglePhoF.root"
	};
	TString name_outputpathMC2017[48] =
	{
		//  Drell-Yan (Visible)
		/*01*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_DYJets_HT0100to0200.root",
		/*02*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_DYJets_HT0200to0400.root",
		/*03*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_DYJets_HT0400to0600.root",
		/*04*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_DYJets_HT0600to0800.root",
		/*05*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_DYJets_HT0800to1200.root",
		/*06*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_DYJets_HT1200to2500.root",
		/*07*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_DYJets_HT2500toInfi.root",
		// * Drell-Yan (Invisible)
		/*08*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_DYJetsInv_HT0100to0200.root",
		/*09*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_DYJetsInv_HT0200to0400.root",
		/*10*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_DYJetsInv_HT0400to0600.root",
		/*11*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_DYJetsInv_HT0600to0800.root",
		/*12*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_DYJetsInv_HT0800to1200.root",
		/*13*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_DYJetsInv_HT1200to2500.root",
		/*14*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_DYJetsInv_HT2500toInfi.root",
		//  Mono-boson EWK
		/*15*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_WmEWK.root",
		/*16*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_WpEWK.root",
		/*17*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_Z2lepEWK.root",
		/*18*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_Z2nuEWK.root",
		// * Gamma + Jets
		/*19*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_GJets_HT0100to0200.root",
		/*20*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_GJets_HT0200to0400.root",
		/*21*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_GJets_HT0400to0600.root",
		/*22*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_GJets_HT0600toInfi.root",
		// * QCD multiple jets
		/*23*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_QCD_HT0100to0200.root",
		/*24*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_QCD_HT0200to0300.root",
		/*25*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_QCD_HT0300to0500.root",
		/*26*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_QCD_HT0500to0700.root",
		/*27*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_QCD_HT0700to1000.root",
		/*28*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_QCD_HT1000to1500.root",
		/*29*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_QCD_HT1500to2000.root",
		/*30*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_QCD_HT2000toInfi.root",
		//  Tops & gamma
		/*31*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_TGJets.root",
		/*32*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_TTGJets.root",
		//  W + Jets (+ gamma)
		/*33*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_WJetsToLNu_HT0100to0200.root",
		/*34*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_WJetsToLNu_HT0200to0400.root",
		/*35*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_WJetsToLNu_HT0400to0600.root",
		/*36*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_WJetsToLNu_HT0600to0800.root",
		/*37*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_WJetsToLNu_HT0800to1200.root",
		/*38*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_WJetsToLNu_HT1200to2500.root",
		/*39*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_WJetsToLNu_HT2500toInfi.root",
		//  Multiple boson QCD
		/*40*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_WGJets.root",
		/*41*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_WW.root",
		/*42*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_WZ.root",
		/*43*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_ZZ.root",
		/*44*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_WWG.root",
		/*45*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_WZG.root",
		/*46*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_Z2lepG.root",
		/*47*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_Z2nuG.root",
		//  Signal
		/*48*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree17_Z2nuGEWK.root"
		
	};
	
	
	// * 2018 directories
	TString name_outputpathDT2018[4] =
	{
		"/home/hoa/Task_ZgVBS/Output/Tree_preselDT/tree18_EGammaA.root",
		"/home/hoa/Task_ZgVBS/Output/Tree_preselDT/tree18_EGammaB.root",
		"/home/hoa/Task_ZgVBS/Output/Tree_preselDT/tree18_EGammaC.root",
		"/home/hoa/Task_ZgVBS/Output/Tree_preselDT/tree18_EGammaD.root"
	};
	TString name_outputpathMC2018[48] =
	{
		//  Drell-Yan (Visible)
		/*01*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_DYJets_HT0100to0200.root",
		/*02*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_DYJets_HT0200to0400.root",
		/*03*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_DYJets_HT0400to0600.root",
		/*04*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_DYJets_HT0600to0800.root",
		/*05*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_DYJets_HT0800to1200.root",
		/*06*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_DYJets_HT1200to2500.root",
		/*07*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_DYJets_HT2500toInfi.root",
		// * Drell-Yan (Invisible)
		/*08*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_DYJetsInv_HT0100to0200.root",
		/*09*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_DYJetsInv_HT0200to0400.root",
		/*10*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_DYJetsInv_HT0400to0600.root",
		/*11*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_DYJetsInv_HT0600to0800.root",
		/*12*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_DYJetsInv_HT0800to1200.root",
		/*13*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_DYJetsInv_HT1200to2500.root",
		/*14*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_DYJetsInv_HT2500toInfi.root",
		//  Mono-boson EWK
		/*15*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_WmEWK.root",
		/*16*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_WpEWK.root",
		/*17*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_Z2lepEWK.root",
		/*18*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_Z2nuEWK.root",
		// * Gamma + Jets
		/*19*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_GJets_HT0100to0200.root",
		/*20*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_GJets_HT0200to0400.root",
		/*21*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_GJets_HT0400to0600.root",
		/*22*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_GJets_HT0600toInfi.root",
		// * QCD multiple jets
		/*23*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_QCD_HT0100to0200.root",
		/*24*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_QCD_HT0200to0300.root",
		/*25*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_QCD_HT0300to0500.root",
		/*26*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_QCD_HT0500to0700.root",
		/*27*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_QCD_HT0700to1000.root",
		/*28*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_QCD_HT1000to1500.root",
		/*29*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_QCD_HT1500to2000.root",
		/*30*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_QCD_HT2000toInfi.root",
		//  Tops & gamma
		/*31*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_TGJets.root",
		/*32*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_TTGJets.root",
		//  W + Jets (+ gamma)
		/*33*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_WJetsToLNu_HT0100to0200.root",
		/*34*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_WJetsToLNu_HT0200to0400.root",
		/*35*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_WJetsToLNu_HT0400to0600.root",
		/*36*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_WJetsToLNu_HT0600to0800.root",
		/*37*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_WJetsToLNu_HT0800to1200.root",
		/*38*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_WJetsToLNu_HT1200to2500.root",
		/*39*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_WJetsToLNu_HT2500toInfi.root",
		//  Multiple boson QCD
		/*40*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_WGJets.root",
		/*41*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_WW.root",
		/*42*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_WZ.root",
		/*43*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_ZZ.root",
		/*44*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_WWG.root",
		/*45*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_WZG.root",
		/*46*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_Z2lepG.root",
		/*47*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_Z2nuG.root",
		//  Signal
		/*48*/"/home/hoa/Task_ZgVBS/Output/Tree_preselMC/tree18_Z2nuGEWK.root"
	};
	
	
	
	
	
	
	
	//printf("*** The value arrays has no problem.\n");
	
	// NOTE Run multiple files
	if (isMC==0)
	{
		for (int ifile=file_1st-1; ifile<file_2nd; ifile++)
		{
			printf("Processing file [ # %d ]\n", ifile);
			
			if (year == 2016)
			{
				CodeAna_Preselection (year, 0, name_inputpathDT2016[ifile], name_outputpathDT2016[ifile]);
			}
			else
			{
				if (year == 2017)
				{
					CodeAna_Preselection (year, 0, name_inputpathDT2017[ifile], name_outputpathDT2017[ifile]);
				}
				else
				{
					CodeAna_Preselection (year, 0, name_inputpathDT2018[ifile], name_outputpathDT2018[ifile]);
				}
			}
		}
	}
	else
	{
		for (int ifile=file_1st-1; ifile<file_2nd; ifile++)
		{
			printf("Processing file [ # %d ]\n", ifile);
			
			if (year == 2016)
			{
				CodeAna_Preselection (year, 1, name_inputpathMC2016[ifile], name_outputpathMC2016[ifile]);
			}
			else
			{
				if (year == 2017)
				{
					CodeAna_Preselection (year, 1, name_inputpathMC2017[ifile], name_outputpathMC2017[ifile]);
				}
				else
				{
					CodeAna_Preselection (year, 1, name_inputpathMC2018[ifile], name_outputpathMC2018[ifile]);
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
