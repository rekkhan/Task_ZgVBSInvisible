#include <stdio.h>
#include <iostream>
#include "Plugin/fileBrowser.h"

#include "Plugin/untuplizer_work.h"





//===================
// + Global variables
//===================
// + Weight type
//--------------
TString name_Weight [4] =
{
	"",
	"Neg",
	"PU",
	"Norm"
};





//========================
// + Get yield information
//========================
vector<double>   Get_YieldInfo (TString pathIn,   int iwgt)
{
	//printf (" * - - Now reading %s\n", pathIn.Data());
	vector<double> vec_result;
	vec_result . clear();
	
	
	vector<TString> name_Yield;
	name_Yield . clear();
	name_Yield . push_back ("");
	name_Yield . push_back ("HLT");
	name_Yield . push_back ("PVGood");
	name_Yield . push_back ("SkimPho");
	name_Yield . push_back ("SkimJet");
	name_Yield . push_back ("SkimMET");
	name_Yield . push_back ("LepVeto");
	name_Yield . push_back ("PassPho");
	name_Yield . push_back ("PassJet");
	name_Yield . push_back ("PassMET");
	if (iwgt==0)
	{
		name_Yield . push_back ("PhoMET");
		name_Yield . push_back ("JetMET");
		name_Yield . push_back ("PhoJet");
		name_Yield . push_back ("JetJet");
	}
	name_Yield . push_back ("VBS");
	
	// * Open tree & hHistogram
	TreeReader reader (pathIn, "tree_Global");
	reader . GetEntry (0);
	
	TFile *file_input = new TFile (pathIn.Data(), "read");
	TH1F *hist = (TH1F*)file_input -> Get ("hist_no_Vtx");
	
	// * Read the tree
	double crossSection = reader . GetFloat ("crossSection");
	vec_result . push_back (crossSection);
	
	double luminosity = reader . GetFloat ("luminosity");
	vec_result . push_back (luminosity);
	
	double normFactor = reader . GetDouble ("normFactor");
	vec_result . push_back (normFactor);
	
	double nVtx_mean = hist -> GetMean();
	vec_result . push_back (nVtx_mean);
	
	for (unsigned int i=0; i<name_Yield.size(); i++)
	{
		double yield;
		if (name_Weight[iwgt]=="" || name_Weight[iwgt]=="Neg")
		{
			yield = reader . GetLong64 (Form("nEvent%s%s", name_Weight[iwgt].Data(), name_Yield[i].Data()));
		}
		else
		{
			yield = reader . GetDouble (Form("nEvent%s%s", name_Weight[iwgt].Data(), name_Yield[i].Data()));
		}
		vec_result . push_back (yield);
	}
	
	file_input -> Close();
	delete file_input;
	
	//for (unsigned int i=0; i<vec_result.size(); i++)
	//{
	//	printf ("        *** vec[%d] = %.2f\n", i, vec_result[i]);
	//}
	
	// * Return the result vector
	return  vec_result;
}





//================
// + Main function
//================
void CodeAna_Yield (int year = 2016,   bool isCollective = 1,   int tightness = 0,   int corMETVer = 0,   char cutScenario = 0)
{
	// + List of scenario
	//-------------------
	TString prefixTightness[4] = {"Loose", "Medium", "Tight", "Lead2jets"};
	TString prefixUseCorMET[3] = {"Org", "Mix", "Cor"};
	
	TString strAdvancedCut[2] =
	{
		Form ("VBS_%s_%sMET_Default",   prefixTightness[tightness].Data(), prefixUseCorMET[corMETVer].Data()),
		Form ("VBS_%s_%sMET_CutAllBtB", prefixTightness[tightness].Data(), prefixUseCorMET[corMETVer].Data())
	};
	
	TString name_dirOut = Form ("/home/hoa/Task_ZgVBS/Output/Yield_DataMC/%s/", strAdvancedCut[cutScenario].Data());
	printf ("    Creating output directory: %s ...\n", name_dirOut.Data());
	system (Form("mkdir -p  %s", name_dirOut.Data()));
	
	
	
	
	
	// + Get list of files from data
	//------------------------------
	// * Vector to store the list of input
	vector<TString>  vec_nameFileinDT;
	vec_nameFileinDT . clear();
	
	// * Vector for the list of runs
	vector<TString>  vec_nameRunDT;
	vec_nameRunDT . clear();
	
	// * Define the input dir(s)
	printf ("    Getting input for data from: %s ...\n", Form("/home/hoa/Task_ZgVBS/Output/Hist_selDT/%s/", strAdvancedCut[cutScenario].Data()));
	TString strDirInputDT  = Form("/home/hoa/Task_ZgVBS/Output/Hist_selDT/%s/", strAdvancedCut[cutScenario].Data());
	string dir_inputDT = strDirInputDT.Data();
	
	vector<string>  list_fileDT = fileBrowser (dir_inputDT, string("root"));
	
	for (unsigned int i=0; i<list_fileDT.size(); i++)
	{
		// * Reject inconsistent files
		TString name_file = list_fileDT[i];
		
		if (!name_file . Contains (Form("hist%d",year-2000)))   continue;
		
		// * Store the full paths
		TString namePathIn  = name_file;
		vec_nameFileinDT . push_back (namePathIn);
		
		// * Store the runs
		TString name_run = name_file . ReplaceAll (strDirInputDT, "");
		name_run . ReplaceAll (Form("hist%d_",year-2000), "");
		name_run . ReplaceAll (".root", "");
		vec_nameRunDT . push_back (name_run);
	}
	
	// * Print result list
	printf ("    [*] List of %zu data input:\n", vec_nameFileinDT.size());
	for (int i=0; i<vec_nameFileinDT.size(); i++)
		printf ("    ||-->-- %s\n", vec_nameFileinDT[i].Data());
	printf ("\n");
	
	
	
	
	
	// + Get list of files from MC
	//----------------------------
	// * Define vector to store the input information
	printf ("    Getting input for MC from: %s ...\n", Form("/home/hoa/Task_ZgVBS/Output/Hist_selMC/%s/", strAdvancedCut[cutScenario].Data()));
	vector<TString>  vec_nameProcess;  // Name of physical interaction
	vec_nameProcess . clear();
	vector<TString>  vec_tmpProcess;  // Name of physical interaction
	vec_tmpProcess . clear();
	vector<TString>  vec_nameDataset;  // Name of sub process (define by some phase space cuts)
	vec_nameDataset . clear();
	vector<TString>  vec_nameIndir;    // Name of all input files
	vec_nameIndir . clear();
	
	vector<vector<TString>>  vec_nameFileinMC; // Name of input files categorized by process
	vec_nameFileinMC . clear();
	
	TString strDirInputMC  = Form("/home/hoa/Task_ZgVBS/Output/Hist_selMC/%s/", strAdvancedCut[cutScenario].Data());
	string dir_inputMC = strDirInputMC.Data();
	
	vector<string>  list_fileMC = fileBrowser (dir_inputMC, string("root"));
	
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
		name_file . ReplaceAll (Form("hist%d_",year-2000), "");
		name_file . ReplaceAll (".root", "");
		
		vec_nameDataset . push_back (name_file);
		vec_tmpProcess . push_back (name_file);
	}
	
	// * Get list of interactions
	vector<TString>::iterator itmc;
	
	for (itmc=vec_tmpProcess.begin(); itmc!=vec_tmpProcess.end(); itmc++)
	{
		int countDiff = 0;
		
		TString textTmp = *itmc;
		TObjArray *arr_splitStr = textTmp . Tokenize ("_");
		
		TString str_split = ((TObjString*)(arr_splitStr->At(0)))->String();
		
		for (int i=0; i<vec_nameProcess.size(); i++)
		{
			if (str_split==vec_nameProcess[i])
			{
				vec_tmpProcess . erase (itmc);
				itmc --;
			}
			else
			{
				countDiff ++;
			}
		}
		
		if (countDiff==vec_nameProcess.size())
		{
			vec_nameProcess . push_back (str_split);
			vec_tmpProcess . erase (itmc);
			itmc --;
		}
	}
	
	// * Get list of full path for each interaction
	for (int i=0; i<vec_nameProcess.size(); i++)
	{
		vector<TString>  vec_tmp;
		vec_tmp . clear();
		
		for (itmc=vec_nameIndir.begin(); itmc!=vec_nameIndir.end(); itmc++)
		{
			TString name_tmp = Form("%s", itmc->Data());
			TObjArray *name_split = name_tmp . Tokenize("_.");
			TString name_sample = ((TObjString*)(name_split->At(1)))->String();
			
			if (name_sample == vec_nameProcess[i])
			{
				TString path_full = Form ("%s%s", strDirInputMC.Data(), itmc->Data());
				vec_tmp . push_back (path_full);
				
				vec_nameIndir . erase (itmc);
				itmc --;
			}
		}
		
		vec_nameFileinMC . push_back (vec_tmp);
	}
	
	printf ("    [*] List of %zu MC sample input:\n", vec_nameFileinMC.size());
	for (int i=0; i<vec_nameFileinMC.size(); i++)
	{
		printf ("    ||-- Sample %s has:\n", vec_nameProcess[i].Data());
		for (int j=0; j<vec_nameFileinMC[i].size(); j++)
		{
			printf ("    ||-->-- %s\n", vec_nameFileinMC[i][j].Data());
		}
	}
	printf ("\n");
	
	
	
	
	
	// + Read and store yield to text file
	//------------------------------------
	// * Level 1 - Loop over all type of yield
	TString text_Weight [4] =
	{
		"Absolute",
		"GENweight",
		"PUweight",
		"Normalize"
	};
	
	
	
	TString name_doCollect[2] = {"MCSep", "MCCom"};
	
	for (int i=0; i<4; i++)
	{
		printf (" * Processing %s weight yield\n", text_Weight[i].Data());
		// + Open a file to store the result
		//----------------------------------
		TString name_fileOutTXT = Form ("%syield%d_%s_%s.txt", name_dirOut.Data(), year, name_doCollect[isCollective].Data(), text_Weight[i].Data());
		FILE *file_yieldTXT = fopen (name_fileOutTXT.Data(), "w");
		
		TString name_fileOutCSV = Form ("%syield%d_%s_%s.csv", name_dirOut.Data(), year, name_doCollect[isCollective].Data(), text_Weight[i].Data());
		FILE *file_yieldCSV = fopen (name_fileOutCSV.Data(), "w");
		
		printf (" * - File %s created\n", name_fileOutTXT.Data());
		printf (" * - File %s created\n", name_fileOutCSV.Data());
		
		fprintf (file_yieldTXT, "Weight type %s:\n\n", text_Weight[i].Data());
		fprintf (file_yieldCSV, "Weight type %s:\n\n", text_Weight[i].Data());
		
		
		
		// + Create name of the yield at each step
		//----------------------------------------
		vector<TString> name_Yield;
		name_Yield . clear();
		name_Yield . push_back ("");
		name_Yield . push_back ("HLT");
		name_Yield . push_back ("PVGood");
		name_Yield . push_back ("SkimPho");
		name_Yield . push_back ("SkimJet");
		name_Yield . push_back ("SkimMET");
		name_Yield . push_back ("LepVeto");
		name_Yield . push_back ("PassPho");
		name_Yield . push_back ("PassJet");
		name_Yield . push_back ("PassMET");
		if (i==0)
		{
			name_Yield . push_back ("PhoMET");
			name_Yield . push_back ("JetMET");
			name_Yield . push_back ("PhoJet");
			name_Yield . push_back ("JetJet");
		}
		name_Yield . push_back ("VBS");
		
		
		
		
		// + Level 2 - Loop over all MC file
		//----------------------------------
		// * Vector of DT total yield
		printf (" * - Processing MC\n");
		
		vector<double>   vec_yieldSumMC;
		vec_yieldSumMC . clear();
		
		
		fprintf (file_yieldTXT, "MC %d yield:\n", year);
		fprintf (file_yieldTXT, "===============\n");
		fprintf (file_yieldCSV, "MC %d yield:\n", year);
		fprintf (file_yieldCSV, "===============\n");
		
		// * Write the variable name
		fprintf (file_yieldTXT, "%25s", "Run / Process / Dataset");
		fprintf (file_yieldTXT, "%14s", "X.Sect.");
		fprintf (file_yieldTXT, "%14s", "Lumi.");
		fprintf (file_yieldTXT, "%14s", "N.Factor");
		fprintf (file_yieldTXT, "%14s", "no.Vtx");
		
		fprintf (file_yieldCSV, "%s,", "Run / Process / Dataset");
		fprintf (file_yieldCSV, "%s,", "X.Sect.");
		fprintf (file_yieldCSV, "%s,", "Lumi.");
		fprintf (file_yieldCSV, "%s,", "N.Factor");
		fprintf (file_yieldCSV, "%s,", "no.Vtx");
		
		for (unsigned int j=0; j<name_Yield.size(); j++)
		{
			TString name_variable = Form ("nEvent%s", name_Yield[j].Data());
			fprintf (file_yieldTXT, "%15s", name_variable.Data());
			fprintf (file_yieldCSV, "%s,", name_variable.Data());
		}
		fprintf (file_yieldTXT, "\n");
		fprintf (file_yieldCSV, "\n");
		
		// * Read and write the yield of individual dataset/process
		int idxFile = 0;
		int idxLast = vec_nameFileinMC.size()-1;
		double  sumEventVBS;
		double  procEventVBS;
		
		if (idxLast > -1)
		{
			for (unsigned int j=0; j<vec_nameFileinMC.size(); j++)
			{
				// * Vector of yield by process
				vector<double>   vec_yieldProc;
				vec_yieldProc . clear();
				
				// * Scan through each data set
				for (unsigned int k=0; k<vec_nameFileinMC[j].size(); k++)
				{
					vector<double>   vec_yield;
					vec_yield . clear();
					
					vec_yield = Get_YieldInfo (vec_nameFileinMC[j][k], i);
					
					if (j==0)
					{
						sumEventVBS = vec_yield[14];
						vec_yieldSumMC = vec_yield;
						vec_yieldSumMC[3] = vec_yield[3]*vec_yield[14];
					}
					else
					{
						sumEventVBS += vec_yield[14];
						for (unsigned int l=0; l<vec_yield.size(); l++)
						{
							if (l!=3)   vec_yieldSumMC[l] += vec_yield[l];
							else        vec_yieldSumMC[l] += vec_yield[l]*vec_yield[14];
						}
					}
					
					if (k==0)
					{
						procEventVBS = vec_yield[14];
						vec_yieldProc  = vec_yield;
						vec_yieldProc[3]  = vec_yield[3]*vec_yield[14];
					}
					else
					{
						procEventVBS += vec_yield[14];
						for (unsigned int l=0; l<vec_yield.size(); l++)
						{
							if (l!=3)  vec_yieldProc[l] += vec_yield[l];
							else       vec_yieldProc[l] += vec_yield[l]*vec_yield[14];
						}
					}
					
					// * Skip printing the yield of each data set if required
					if (isCollective)   continue;
					
					TString name_dataset = vec_nameFileinMC[j][k];
					name_dataset . ReplaceAll (strDirInputMC.Data(), "");
					name_dataset . ReplaceAll (Form("hist%d_",year-2000), "");
					name_dataset . ReplaceAll (".root", "");
					
					fprintf (file_yieldTXT, "%25s", name_dataset.Data());
					fprintf (file_yieldCSV, "%s,", name_dataset.Data());
					for (unsigned int l=0; l<vec_yield.size(); l++)
					{
						if (l<4)
						{
							fprintf (file_yieldTXT, "%+14.4E", vec_yield[l]);
							fprintf (file_yieldCSV, "%+.4E,", vec_yield[l]);
						}
						else
						{
							fprintf (file_yieldTXT, "%15.0f", vec_yield[l]);
							fprintf (file_yieldCSV, "%.0f,", vec_yield[l]);
						}
					}
					fprintf (file_yieldTXT, "\n");
					fprintf (file_yieldCSV, "\n");
				}
				
				// * Skip printing the yield of each process if not required
				if (!isCollective)   continue;
				
				vec_yieldProc[3] /= procEventVBS;
				
				fprintf (file_yieldTXT, "%25s", vec_nameProcess [j].Data());
				fprintf (file_yieldCSV, "%s,", vec_nameProcess [j].Data());
				for (unsigned int k=0; k<vec_yieldProc.size(); k++)
				{
					if (k<4)
					{
						fprintf (file_yieldTXT, "%+14.4E", vec_yieldProc[k]);
						fprintf (file_yieldCSV, "%+.4E,", vec_yieldProc[k]);
					}
					else
					{
						fprintf (file_yieldTXT, "%15.0f", vec_yieldProc[k]);
						fprintf (file_yieldCSV, "%.0f,", vec_yieldProc[k]);
					}
				}
				fprintf (file_yieldTXT, "\n");
				fprintf (file_yieldCSV, "\n");
			}
			
			// * Write the total yield of the year
			vec_yieldSumMC[3] /= sumEventVBS;
			
			fprintf (file_yieldTXT, "%25s", "Total MC yield");
			fprintf (file_yieldCSV, "%s,", "Total MC yield");
			for (unsigned int j=0; j<vec_yieldSumMC.size(); j++)
			{
				if (j<4)
				{
					fprintf (file_yieldTXT, "%+14.4E", vec_yieldSumMC[j]);
					fprintf (file_yieldCSV, "%+.4E,", vec_yieldSumMC[j]);
				}
				else
				{
					fprintf (file_yieldTXT, "%15.1f", vec_yieldSumMC[j]);
					fprintf (file_yieldCSV, "%.1f,", vec_yieldSumMC[j]);
				}
			}
			fprintf (file_yieldTXT, "\n");
			fprintf (file_yieldCSV, "\n");
		}
		
		
		
		
		// + Level 2 - Loop over all DT file
		//----------------------------------
		// * Vector of DT total yield
		printf (" * - Processing Data\n");
		
		vector<double>   vec_yieldSumDT;
		vec_yieldSumDT . clear();
		
		fprintf (file_yieldTXT, "Data %d yield:\n", year);
		fprintf (file_yieldTXT, "=================\n");
		
		fprintf (file_yieldCSV, "Data %d yield:\n", year);
		fprintf (file_yieldCSV, "=================\n");
		
		// * Write the variable name
		fprintf (file_yieldTXT, "%25s", "Run / Process / Dataset");
		fprintf (file_yieldTXT, "%14s", "X.Sect.");
		fprintf (file_yieldTXT, "%14s", "Lumi.");
		fprintf (file_yieldTXT, "%14s", "N.Factor");
		fprintf (file_yieldTXT, "%14s", "no.Vtx");
		
		fprintf (file_yieldCSV, "%s,", "Run / Process / Dataset");
		fprintf (file_yieldCSV, "%s,", "X.Sect.");
		fprintf (file_yieldCSV, "%s,", "Lumi.");
		fprintf (file_yieldCSV, "%s,", "N.Factor");
		fprintf (file_yieldCSV, "%s,", "no.Vtx");
		
		for (unsigned int j=0; j<name_Yield.size(); j++)
		{
			TString name_variable = Form ("nEvent%s", name_Yield[j].Data());
			fprintf (file_yieldTXT, "%15s", name_variable.Data());
			fprintf (file_yieldCSV, "%s,", name_variable.Data());
		}
		fprintf (file_yieldTXT, "\n");
		fprintf (file_yieldCSV, "\n");
		
		// * Read and write the yield of individual runs
		idxLast = vec_nameFileinDT.size()-1;
		
		if (idxLast > -1)
		{
			for (unsigned int j=0; j<vec_nameFileinDT.size(); j++)
			{
				vector<double>   vec_yield;
				vec_yield . clear();
				
				vec_yield = Get_YieldInfo (vec_nameFileinDT[j], i);
				if (j==0)
				{
					sumEventVBS = vec_yield[14];
					vec_yieldSumDT = vec_yield;
					vec_yieldSumDT[3] = vec_yield[3]*vec_yield[14];
				}
				else
				{
					sumEventVBS += vec_yield[14];
					for (unsigned int k=0; k<vec_yield.size(); k++)
					{
						if (k!=3)  vec_yieldSumDT[k] += vec_yield[k];
						else       vec_yieldSumDT[k] += vec_yield[k]*vec_yield[14];
					}
				}
				
				fprintf (file_yieldTXT, "%25s", vec_nameRunDT[j].Data());
				fprintf (file_yieldCSV, "%s,", vec_nameRunDT[j].Data());
				for (unsigned int k=0; k<vec_yield.size(); k++)
				{
					if (k<4)
					{
						fprintf (file_yieldTXT, "%+14.4E", vec_yield[k]);
						fprintf (file_yieldCSV, "%+.4E,", vec_yield[k]);
					}
					else
					{
						fprintf (file_yieldTXT, "%15.0f", vec_yield[k]);
						fprintf (file_yieldCSV, "%.0f,", vec_yield[k]);
					}
				}
				fprintf (file_yieldTXT, "\n");
				fprintf (file_yieldCSV, "\n");
			}
			
			// * Write the total DT yield of the year
			vec_yieldSumDT[3] /= sumEventVBS;
			
			fprintf (file_yieldTXT, "%25s", "Total DT yield");
			fprintf (file_yieldCSV, "%s,", "Total DT yield");
			for (unsigned int j=0; j<vec_yieldSumDT.size(); j++)
			{
				if (j<4)
				{
					fprintf (file_yieldTXT, "%+14.4E", vec_yieldSumDT[j]);
					fprintf (file_yieldCSV, "%+.4E,", vec_yieldSumDT[j]);
				}
				else
				{
					fprintf (file_yieldTXT, "%15.0f", vec_yieldSumDT[j]);
					fprintf (file_yieldCSV, "%.0f,", vec_yieldSumDT[j]);
				}
			}
			fprintf (file_yieldTXT, "\n\n");
			fprintf (file_yieldCSV, "\n\n");
		}
			
			
			
		// + Close file
		//-------------
		fclose (file_yieldTXT);
		fclose (file_yieldCSV);
		printf (" * - file closed\n\n");
	}
	
	
	printf ("\n\nJob's done\n");
}
