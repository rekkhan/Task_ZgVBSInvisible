#include <stdio.h>
#include <iostream>

using namespace std;



#ifndef FILEBROWSER_H
#define FILEBROWSER_H



bool Check_IsDir (string path_toCheck="");
bool Check_IsNumber (string str_toCheck="");
bool Check_StrBeginwith (string str_toCheck="",   string str_toFind="");
bool Check_StrEndwith (string str_toCheck="",   string str_toFind="");
bool Check_StrInStr (string str_toFind="",   string str_toCheck="");

int Count_StrInStr (string str_toCount="",   string str_toCheck="");

vector<string>    Get_formula (string str_formula);
pair<string,bool> Get_cmdlineOutput (string str_cmdLine);
vector<string>    Get_splittedString (string str_origin,   string delimiter,   bool rejectnull=true);

string  Replace_StrByStr (string str_orgin,   string str_replaced,   string str_replacing,   bool printChar=false);

vector<string>  Search_StringsFromTemplate (string template_toSearch);





//==========================================
// + Function: Check if string A ends with B
//==========================================
bool Check_IsDir (string path_toCheck)
{
	// + List of variables
	//--------------------
	// * For output
	bool  result = true;
	
	// * For collecting infos
	char char_fromPipe[2];
	string str_cmdOutput;
	string tmp_cmdLine;
	FILE *file_pipe;
	
	
	
	// + Check if there is any error listing the contents
	//---------------------------------------------------
	// * Temporary command line
	tmp_cmdLine = "ls ";
	tmp_cmdLine += path_toCheck;
	tmp_cmdLine += "  2> /dev/null";
	
	// * Make sure the string is empty
	str_cmdOutput = "";
	
	// * Execute the command line
	file_pipe = popen (tmp_cmdLine.data(), "r");
	
	// * Return error if the pipe cannot be opened
	if (!file_pipe)
	{
		str_cmdOutput = "Unknown error, failed to do popen\n";
		
		result = false;
		return  result;
	}
	
	// * Check the output of the command line
	while (!feof(file_pipe))
	{
		fgets (char_fromPipe, 2, file_pipe);
		
		if (feof(file_pipe))   break;
		
		str_cmdOutput += char_fromPipe;
	}
	
	pclose (file_pipe);
	
	if (str_cmdOutput == "")
	{
		result = false;
	}
	
	return result;
}





//==========================================
// + Function: Check if string A ends with B
//==========================================
bool Check_IsNumber (string str_toCheck)
{
	for (unsigned int i=0; i<str_toCheck.length(); i++)
	{
		char mychar = str_toCheck[i];
		if (!isdigit(mychar))   return false;
	}
	
	return true;
}





//==========================================
// + Function: Check if string A ends with B
//==========================================
bool Check_StrBeginwith (string str_toCheck,   string str_toFind)
{
	// + List of variables
	//--------------------
	// * Return value
	bool result = false;
	
	if (str_toCheck==""  ||  str_toFind=="")
	{
		return result;
	}
	
	// * Size of the string
	unsigned int size_toCheck = str_toCheck . length();
	unsigned int size_toFind  = str_toFind  . length();
	
	if (size_toCheck < size_toFind)   return false;
	
	
	
	// + Search for string B in string A
	//----------------------------------
	// * Number of match characters
	int nMatch = 0;
	
	for (unsigned int i=0; i<size_toFind; i++)
	{
		if (str_toCheck[i]==str_toFind[i])
		{
			nMatch ++;
		}
	}
	
	if (nMatch==size_toFind)
	{
		result = true;
	}
	else
	{
		result = false;
	}
	return result;
}





//==========================================
// + Function: Check if string A ends with B
//==========================================
bool Check_StrEndwith (string str_toCheck,   string str_toFind)
{
	// + List of variables
	//--------------------
	// * Return value
	bool result = false;
	
	if (str_toCheck==""  ||  str_toFind=="")
	{
		return result;
	}
	
	// * Size of the string
	unsigned int size_toCheck = str_toCheck . length();
	unsigned int size_toFind  = str_toFind  . length();
	
	if (size_toCheck < size_toFind)   return false;
	
	
	
	// + Search for string B in string A
	//----------------------------------
	// * Number of match characters
	int nMatch = 0;
	
	for (unsigned int i=0; i<size_toFind; i++)
	{
		int j = i + size_toCheck - size_toFind;
		
		if (str_toCheck[j]==str_toFind[i])
		{
			nMatch ++;
		}
	}
	
	if (nMatch==size_toFind)
	{
		result = true;
	}
	else
	{
		result = false;
	}
	return result;
}





//================================================
// + Function: Check if string A contains string B
//================================================
bool Check_StrInStr (string str_toFind,   string str_toCheck)
{
	// + List of variables
	//--------------------
	// * Return value
	bool result = false;
	
	if (str_toCheck==""  ||  str_toFind=="")
	{
		return result;
	}
	
	// * Size of the string
	unsigned int size_toCheck = str_toCheck . length();
	unsigned int size_toFind  = str_toFind  . length();
	
	if (size_toCheck < size_toFind)   return false;
	
	
	
	// + Search for string B in string A
	//----------------------------------
	for (unsigned int i=0; i<size_toCheck-size_toFind+1; i++)
	{
		// * Number of match characters
		int nMatch = 0;
		
		for (unsigned int j=0; j<size_toFind; j++)
		{
			if (str_toCheck[i+j] == str_toFind[j])
			{
				//printf ("Matched\n");
				nMatch ++;
				continue;
			}
		}
		
		// * It #matched characters equal
		if (nMatch == size_toFind)
		{
			result = true;
			break;
		}
	}
	
	return result;
}





//===================================================
// + Function: Count the repetition of str B in str A
//===================================================
int Count_StrInStr (string str_toCount,   string str_toCheck)
{
	// + List of variables
	//--------------------
	// * Return value
	int result = 0;
	
	if (str_toCount == ""  ||  str_toCheck == "")
	{
		return result = -1;
	}
	
	// * Size of the string
	unsigned int size_toCheck = str_toCheck . length();
	unsigned int size_toCount = str_toCount  . length();
	
	if (size_toCheck < size_toCount)   return false;
	
	
	
	// + Search for string B in string A
	//----------------------------------
	for (unsigned int i=0; i<size_toCheck-size_toCount; i++)
	{
		// * Number of match characters
		int nMatch = 0;
		
		for (unsigned int j=0; j<size_toCount; j++)
		{
			if (str_toCheck[i+j] == str_toCount[j])
			{
				nMatch ++;
				continue;
			}
		}
		
		// * It #matched characters equal
		if (nMatch == size_toCount)
		{
			result ++;
		}
	}
	
	return result;
}





//=========================================
// + Function: Get output from command line
//=========================================
vector<string> Get_formula (string str_formula)
{
	// + Return value
	//---------------
	vector<string> form_return;
	form_return . clear();
	
	
	
	// + Get the formula
	vector<string> form_pre = Get_splittedString (str_formula, ",", false);
	
	for (unsigned int i=0; i<form_pre.size(); i++)
	{
		string form_indv = form_pre[i];
		
		// * Check whether we have iter structure
		bool isIter = Check_StrInStr ("..", form_indv);
		printf ("  The splitted form is: [ %s ] ;   is Iter: %d\n", form_indv.data(), isIter);
		
		
		
		// + Get value from iteration
		//---------------------------
		if (isIter)
		{
			// * Get the start/end point of iter, and may be the step
			vector<string>  iter_info = Get_splittedString(form_indv, "..");
			
			bool is_0char = iter_info[0].length()==1;
			bool is_1char = iter_info[1].length()==1;
			bool is_0int  = Check_IsNumber(iter_info[0]);
			bool is_1int  = Check_IsNumber(iter_info[1]);
			
			bool isChar = is_0char && is_1char;
			bool isInt  = is_0int && is_1int;
			
			bool isValid = isChar || isInt;
			
			if (!isValid)
			{
				form_return . push_back(form_indv);
				continue;
			}
			
			
			bool is_2int = true;
			bool hasStep = false;
			
			if (iter_info.size()==3)
			{
				hasStep = true;
				is_2int = Check_IsNumber(iter_info[2]);
			}
			
			int stepsize = (hasStep==false  ||  (is_2int && hasStep)) ? 1 : atoi(iter_info[2].data());
			if (stepsize==0)   stepsize = 1;
			
			if (isInt)
			{
				int num0 = atoi (iter_info[0].data());
				int num1 = atoi (iter_info[1].data());
				
				int minInt = min (num0, num1);
				int maxInt = max (num0, num1);
				
				for (int j=minInt; j<maxInt+1; j+=stepsize)
				{
					string tmpVal = to_string (j);
					form_return . push_back(tmpVal);
				}
				
				continue;
			}
			
			char char0 = iter_info[0][0];
			char char1 = iter_info[1][0];
			
			char minChar = min (char0, char1);
			char maxChar = max (char0, char1);
			
			for (char j=minChar; j<maxChar+1; j+=stepsize)
			{
				string tmpVal = "";
				tmpVal += j;
				form_return . push_back(tmpVal);
			}
			
			continue;
		}
		
		// * Fill the vector if no iteration available
		form_return . push_back (form_indv);
	}
	
	return form_return;
}





//=========================================
// + Function: Get output from command line
//=========================================
pair<string,bool> Get_cmdlineOutput (string str_cmdLine)
{
	// + List of variables
	//--------------------
	// * For output
	pair<string,bool>  result;
	
	// * For collecting infos
	char char_fromPipe[2];
	string str_cmdOutput;
	string tmp_cmdLine;
	FILE *file_pipe;
	bool isErrorFree = true;
	
	
	
	// + Check if there is any error listing the contents
	//---------------------------------------------------
	// * Temporary command line
	tmp_cmdLine = str_cmdLine;
	tmp_cmdLine += "  2> /dev/null";
	
	// * Make sure the string is empty
	str_cmdOutput = "";
	
	// * Execute the command line
	file_pipe = popen (tmp_cmdLine.data(), "r");
	
	// * Return error if the pipe cannot be opened
	if (!file_pipe)
	{
		str_cmdOutput = "Unknown error, failed to do popen\n";
		isErrorFree = false;
		
		result . first  = str_cmdOutput;
		result . second = isErrorFree;
		return  result;
	}
	
	// * Check the output of the command line
	while (!feof(file_pipe))
	{
		fgets (char_fromPipe, 2, file_pipe);
		
		if (feof(file_pipe))   break;
		
		str_cmdOutput += char_fromPipe;
	}
	
	pclose(file_pipe);
	
	// * If the output is not empty, return the output
	if (str_cmdOutput!="")
	{
		result . first  = str_cmdOutput;
		result . second = isErrorFree;
		return  result;
	}
	
	
	
	// + Execute the command line again to get the error
	//--------------------------------------------------
	// * Temporary command line
	tmp_cmdLine = str_cmdLine;
	tmp_cmdLine += "  2>&1";
	
	isErrorFree = false;
	
	// * Make sure the string is empty
	str_cmdOutput = "";
	
	// * Execute the command line
	file_pipe = popen (tmp_cmdLine.data(), "r");
	
	// * Return error if the pipe cannot be opened
	if (!file_pipe)
	{
		str_cmdOutput = "Unknown error, failed to do popen\n";
		isErrorFree = false;
		
		result . first  = str_cmdOutput;
		result . second = isErrorFree;
		return  result;
	}
	
	// * Check the output of the command line
	while (!feof(file_pipe))
	{
		fgets (char_fromPipe, 2, file_pipe);
		
		if (feof(file_pipe))   break;
		
		str_cmdOutput += char_fromPipe;
	}
	
	pclose(file_pipe);
	
	result . first  = str_cmdOutput;
	result . second = isErrorFree;
	return  result;
}





//==========================================================
// + Function: Split the line into sub-string for converting
//==========================================================
vector<string>   Get_splittedString (string str_origin,  string delimiter,  bool rejectnull)
{
	vector<string>   list_strSplitted;
	list_strSplitted . clear();
	
	string str_block;
	str_block . clear();
	
	string str_tmp;
	str_tmp . clear();
	
	
	unsigned int size_str = str_origin  . size();
	unsigned int size_del = delimiter . size();
	
	bool doFillBlock = true;
	bool doFillList  = false;
	
	for (unsigned int i=0; i<size_str; i++)
	{
		// * If the character is one of the delimiter, prevent the program from appending the substring
		for (unsigned int j=0; j<size_del; j++)
		{
			if (str_origin[i] == delimiter[j])
			{
				doFillBlock = false;
				break;
			}
			else
			{
				doFillBlock = true;
			}
		}
		
		// * Append the substring if permitted
		if (doFillBlock)
		{
			str_block . append (str_origin, i, 1);
		}
		
		// * If the substring is not empty and we encounter a delimiter, it's time to add the substring to the list
		//   (Remember to clear substring afterward and allow the program to append letter again)
		unsigned int size_block = str_block . size();
		bool isValid = (!rejectnull) || (size_block>0);
		
		
		if (isValid>0 && doFillBlock==false)
		{
			list_strSplitted . push_back (str_block);
			str_block . clear();
			doFillBlock = true;
		}
	}
	
	// * The last substring will be ignore as the program escape the loop before filling it
	//   Fill the substring "manually" here
	bool endwith_Delimiter = false;
	for (unsigned int i=0; i<size_del; i++)
	{
		string deli = "";
		deli += delimiter[i];
		
		if (Check_StrEndwith(str_origin, deli))
		{
			endwith_Delimiter = true;
			break;
		}
	}
	
	bool isValid = ((!rejectnull)  &&  endwith_Delimiter)  || (str_block.size()>0);
	
	if (isValid > 0)
	{
		list_strSplitted . push_back (str_block);
		str_block . clear();
	}
	
	return list_strSplitted;
}





//===========================================
// + Function: Replace substring by substring
//===========================================
string  Replace_StrByStr (string str_orgin,  string str_replaced,   string str_replacing,   bool printChar)
{
	string result = "";
	
	unsigned int size_origin    = str_orgin     . length();
	unsigned int size_replaced  = str_replaced  . length();
	unsigned int size_replacing = str_replacing . length();
	
	if (printChar)  printf ("     char is:  ");
	
	for (unsigned int i=0; i<size_origin; i++)
	{
		char mychar = str_orgin[i];
		if (printChar)  printf (" [ %c ]", mychar);
		
		
		if (i>size_origin-size_replaced)
		{
			result . append (1, mychar);
			if (printChar)  printf (" [ %c ]", mychar);
			continue;
		}
		
		// * Number of match characters
		int nMatch = 0;
		
		for (unsigned int j=0; j<size_replaced; j++)
		{
			if (str_orgin[i+j] == str_replaced[j])
			{
				nMatch ++;
				continue;
			}
		}
		
		//printf ("  |-- |-- |-- nMatch: [ %d ] vs size_replaced: [ %d ]\n", nMatch, size_replaced);
		if (nMatch == size_replaced)
		{
			//printf ("  |-- |-- |-- appending: [ %s ]\n", str_replacing.data());
			result . append (str_replacing);
			i += size_replaced-1;
			continue;
		}
		else
		{
			result . append (1, mychar);
			continue;
		}
	}
	if (printChar)  printf ("\n");
	
	return result;
}





//=================================
// + Search for paths from template
//=================================
vector<string>  Search_StringsFromTemplate (string template_toSearch)
{
	// + Split the template to get the formula
	//----------------------------------------
	// * Get the splitted strings
	vector<string> template_split = Get_splittedString (template_toSearch, "{}", false);
	
	// * Loop through the splitted component to get the formats
	//   The formats are the strings inside the curly bracket
	bool start_byBra = Check_StrBeginwith (template_toSearch, "{");
	unsigned int idx_begin = (start_byBra) ? 0 : 1;
	
	// * Vector to store the formula
	vector<vector<string>>  dirPart_formula;
	dirPart_formula . clear();
	
	// * Vector to store the common part
	vector<string>  dirPart_common;
	dirPart_common . clear();
	
	for (unsigned int i=0; i<template_split.size(); i++)
	{
		// * Get the common string
		unsigned int idx = i + idx_begin;
		if (idx%2 != 0)
		{
			dirPart_common . push_back (template_split[i]);
			continue;
		}
		
		// * Get the format
		vector<string> formula = Get_formula (template_split[i]);
		dirPart_formula . push_back (formula);
	}
	
	for (int i=0; i<dirPart_formula.size(); i++)
	{
		printf ("Formula %d:   ", i);
		for (int j=0; j<dirPart_formula[i].size(); j++)
		{
			printf ("   [ %s ]", dirPart_formula[i][j].data());
		}
		printf ("\n");
	}
	
	
	
	
	
	// + The return value
	//-------------------
	vector<string> list_pathFound;
	list_pathFound . clear();
	
	// * Size of the common part and the formula part
	unsigned int size_common  = dirPart_common . size();
	unsigned int size_formula = dirPart_formula . size();
	
	// * Return empty vector in case of error
	if (size_common < size_formula)
	{
		list_pathFound . push_back (template_toSearch);
		return list_pathFound;
	}
	
	if (size_common > size_formula+1)
	{
		list_pathFound . push_back (template_toSearch);
		return list_pathFound;
	}
	
	
	
	// + Create the actual paths
	//--------------------------
	// * Get the 1D list of formula
	vector<vector<string>>  list_form1;
	vector<vector<string>>  list_form2;
	list_form1 . clear();
	list_form2 . clear();
	
	vector<string>  formslot;
	formslot . clear();
	
	unsigned int size_partFormula = dirPart_formula.size();
	if (size_partFormula < 1)
	{
		list_pathFound . push_back (template_toSearch);
		return list_pathFound;
	}
	
	list_form1 . push_back (dirPart_formula[0]);
	
	if (size_partFormula < 2)
	{
		list_form2 . clear();
		
		for (unsigned int i=0; i<list_form1[0].size(); i++)
		{
			formslot . clear();
			formslot . push_back (list_form1[0][i]);
			list_form2 . push_back (formslot);
		}
		
		list_form1 = list_form2;
	}
	else
	{
		for (unsigned int i=1; i<dirPart_formula.size(); i++)
		{
			list_form2 . clear();
			for (unsigned int j=0; j<dirPart_formula[i].size(); j++)
			{
				for (unsigned int k=0; k<list_form1[0].size(); k++)
				{
					formslot . clear();
					printf ("  Adding (%d): %s,", k, list_form1[0][k].data());
					formslot . push_back (list_form1[0][k]);
					printf (" (%d-%d): %s\n", i, j, dirPart_formula[i][j].data());
					formslot . push_back (dirPart_formula[i][j]);
					list_form2 . push_back (formslot);
				}
			}
			
			list_form1 = list_form2;
		}
	}
	
	for (int i=0; i<list_form1.size(); i++)
	{
		printf ("Line %d:   ", i);
		for (int j=0; j<list_form1[i].size(); j++)
		{
			printf ("   [ %s ]", list_form1[i][j].data());
		}
		printf ("\n");
	}
	
	// * Combine the formula with the common strings
	for (unsigned int i=0; i<list_form1.size(); i++)
	{
		string  path_extract = "";
		
		for (unsigned int j=0; j<size_formula; j++)
		{
			path_extract += (start_byBra) ? list_form1[i][j] + dirPart_common[j] : dirPart_common[j] + list_form1[i][j];
		}
		
		if (size_common > size_formula)
		{
			path_extract += dirPart_common[size_common-1];
		}
		
		printf ("     Loop #%d:  < %s >\n", i, path_extract.data());
		
		list_pathFound . push_back (path_extract);
	}
	
	for (int i=0; i<list_pathFound.size(); i++)
	{
		printf ("   [ %s ]\n", list_pathFound[i].data());
	}
	
	return list_pathFound;
}





//============================
// + The core of files browser
//============================
// * This browser use (string, string) arguments
//----------------------------------------------
vector<string>  fileBrowserCore (string dirTmpl_toBrowse, string filetype)
{
	// + Get the actual paths from the template
	//-----------------------------------------
	vector<string>  list_pathFromTemplate = Search_StringsFromTemplate (dirTmpl_toBrowse);
	
	
	
	// + Browse files and check their size
	//------------------------------------
	// * Vector to store the file
	vector<string>  list_pathFile;
	list_pathFile . clear();
	int  nError;
	bool is_errorFree;
	
	for (unsigned int i=0; i<list_pathFromTemplate.size(); i++)
	{
		string dir_toBrowse = list_pathFromTemplate[i];
		
		// * Correct the file path
		if (Check_StrEndwith(dir_toBrowse,"/"))
		{
			dir_toBrowse += "*";
		}
		else
		{
			string dirtmp_toBrowse = dir_toBrowse + "/*";
			
			if (Check_IsDir(dirtmp_toBrowse))
			{
				dir_toBrowse = dirtmp_toBrowse;
			}
		}
		
		// * Skip non-exist path
		bool isDir = Check_IsDir (dir_toBrowse);
		
		if (!isDir)
		{
			printf ("Skip: %s\n", dir_toBrowse.data());
			nError ++;
			continue;
		}
		
		// * Command line to get the paths to files
		string str_cmdLine = "ls -1  ";
		str_cmdLine += dir_toBrowse.data();
		
		// * Get the output from the command line
		pair<string,bool> cmd_output = Get_cmdlineOutput (str_cmdLine);
		string cmd_strOutput = cmd_output . first;
		is_errorFree  = cmd_output . second;
		
		// * Get the lines from the output
		vector<string> lines_fromCmdOut = Get_splittedString (cmd_strOutput, "\n");
		
		// * Loop over the lines
		int nLine = int(lines_fromCmdOut . size());
		
		for (int j=0; j<nLine; j++)
		{
			// * Skip the lines that are not pointing to files
			bool is_rootFile = Check_StrInStr (filetype, lines_fromCmdOut[j]);
			if (!is_rootFile && is_errorFree)   continue;
			
			// * Extract the components in each output line
			vector<string> lineSplt = Get_splittedString (lines_fromCmdOut[j], " ");
			
			// * Get the last component, which is  the full path
			string path_file = (is_errorFree) ? lineSplt[lineSplt.size()-1] : lines_fromCmdOut[j];
			list_pathFile . push_back (path_file);
		}
	}
	
	if (list_pathFile.size() == 0)
	{
		list_pathFile . push_back ("No file found!");
		is_errorFree = false;
	}
	
	pair<vector<string>,bool>  result;
	
	result . first  = list_pathFile;
	result . second = is_errorFree;
	
	
	//return result;
	return list_pathFile;
}





//==========================================
// + The files browser with TString template
//==========================================
vector<string>  fileBrowser (TString dirTmpl_toBrowse,  string filetype="root")
{
	string  str_dirTemplate = dirTmpl_toBrowse.Data();
	
	return fileBrowserCore (str_dirTemplate,  filetype);
}





//===========================================
// + The files browser with TString arguments
//===========================================
vector<string>  fileBrowser (string dirTmpl_toBrowse,  string filetype="root")
{
	return fileBrowserCore (dirTmpl_toBrowse,  filetype);
}





#endif
