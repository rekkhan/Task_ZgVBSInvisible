#ifndef   TOOL_UTILITIES_H
#define   TOOL_UTILITIES_H






TString Lookup_Variable (TString aString)
{
	TString var;
	
	if (aString=="Pho")   var="#gamma";
	else if (aString=="Phoboost")   var="#gamma_{boost}";
	else if (aString=="All")   var="All";
	else if (aString.Contains("Invis"))   var="#slash{E_{T}}";
	else if (aString.BeginsWith("Jet1"))   var="j_{1}";
	else if (aString.BeginsWith("Jet2"))   var="j_{2}";
	else if (aString.BeginsWith("Jet"))   var="j";
	else if (aString.Contains("Dijet"))   var="jj";
	else if (aString.Contains("ZPho"))   var="Z#gamma";
	else if (aString.Contains("ETPho"))   var="E^{#gamma}_{T}";
	else if (aString.Contains("pTJet1"))   var="p^{j1}_{T}";
	else if (aString.Contains("pTJet2"))   var="p^{j2}_{T}";
	else if (aString.Contains("EtaJet1"))   var="j^{1}_{#eta}";
	else if (aString.Contains("EtaJet2"))   var="j^{2}_{#eta}";
	else if (aString.Contains("EtaJet"))   var="j_{#eta}";
	else if (aString.Contains("Vtx"))   var="Vertices";
	else if (aString.Contains("VtxWei"))   var="Wt.Vertices";
	else if (aString.Contains("PUtrue"))
	{
		aString . ReplaceAll ("PUtrue", "");
		var=Form("true PU %s", aString.Data());
	}
	else if (aString.Contains("Signal"))   var="Z#gammajj";
	else if (aString=="EToET")   var="E_{T} over E_{T}";
	else if (aString=="PToPT")   var="p_{T} over p_{T}";
	else var=aString;
	
	return var;
}






//==================================
// * Utilities - Get info from files
//==================================
unsigned int  GetInfo_Histograms (TFile *file,   vector<TString> &vec_nameHist,   vector<TString> &vec_nameFileout,   vector<TString> &vec_nameXaxis)
{
	// + Variables for computation
	//----------------------------
	// * Number of variables to return
	unsigned int nVar = 0;
	
	// * The iterator
	TIter next(file->GetListOfKeys());
	
	// * The keys
	TKey *key;
	
	
	
	// + Main loop
	//------------
	while ((key = (TKey*)next()))
	{
		// + Get the name of the class
		//----------------------------
		TString name_class  = key -> GetClassName();
		
		// * Reject non-1D-histogram objects
		if (!name_class.Contains("TH1F"))   continue;
		
		// * Add up the number of variables
		nVar ++;
		
		// + Read and store the name of the histogram
		//-------------------------------------------
		TH1F *hist = (TH1F*)key -> ReadObj();
		TString name_hist = hist -> GetName();
		delete hist;
		
		vec_nameHist . push_back (name_hist);
		
		
		// + Store the name of the output plot
		//------------------------------------
		TString name_fileout = name_hist;
		name_fileout . ReplaceAll ("hist_", "");
		name_fileout . ReplaceAll (".root", "");
		
		vec_nameFileout . push_back (name_fileout);
		//printf ("Stripped file name: %s\n", name_fileout.Data());
		
		
		// + Get axis name
		//----------------
		// * Split histogram's name into part
		TObjArray *arr_splitStr = name_fileout . Tokenize ("_");
		
		vector<TString>  vec_splitStr;
		vec_splitStr . clear();
		
		for (unsigned int i=0; i<arr_splitStr->GetLast()+1; i++)
		{
			TString str_split = ((TObjString*)(arr_splitStr->At(i)))->String();
			vec_splitStr . push_back (str_split);
		}
		
		// * Generate axis title
		TString name_func = "";
		TString name_var1 = "";
		TString name_var2 = "";
		TString name_unit = "";
		TString name_Xaxis = "";
		
		if (vec_splitStr[0]=="ET" || vec_splitStr[0]=="pT")
		{
			name_func = Form ("%c_{%c}", vec_splitStr[0][0], vec_splitStr[0][1]);
			name_unit = " [GeV]";
		}
		else if (vec_splitStr[0]=="eta" || vec_splitStr[0]=="Phi")
		{
			name_func = Form ("#%s", vec_splitStr[0].Data());
			name_unit = " [rad]";
		}
		else if (vec_splitStr[0]=="Mass")
		{
			name_func = "Inv.Mass";
			name_unit = " [GeV]";
		}
		else if (vec_splitStr[0].Contains("deta") || vec_splitStr[0].Contains("dPhi"))
		{
			name_func = vec_splitStr[0];
			name_func . ReplaceAll ("d", "#Delta#");
			name_unit = " [rad]";
		}
		else if (vec_splitStr[0]=="dR")
		{
			name_func = vec_splitStr[0];
			name_func . ReplaceAll ("d", "#Delta");
			name_unit = " [rad]";
		}
		else
		{
			name_func = vec_splitStr[0];
		}
		
		if (name_func.Contains("Sum"))   name_func . ReplaceAll ("Sum", "#sum");
		
		if (vec_splitStr.size()>2)
		{
			name_var1 = Lookup_Variable (vec_splitStr[1]);
			name_var2 = Lookup_Variable (vec_splitStr[2]);
			
			name_Xaxis = Form ("%s(%s,%s)%s", name_func.Data(), name_var1.Data(), name_var2.Data(), name_unit.Data());
		}
		else
		{
			name_var1 = Lookup_Variable (vec_splitStr[1]);
			
			if (vec_splitStr[1]=="Invis" && name_func=="ET")
			{
				name_Xaxis = Form ("%s%s", name_var1.Data(), name_unit.Data());
			}
			else
			{
				name_Xaxis = Form ("%s(%s)%s", name_func.Data(), name_var1.Data(), name_unit.Data());
			}
		}
		
		// * Add title to vector
		vec_nameXaxis . push_back (name_Xaxis);
	}
	
	
	return nVar;
}





#endif
