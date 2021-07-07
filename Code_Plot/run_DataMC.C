#include <stdio.h>
#include "CodePlot_DataMC.C"

void run_DataMC (int year,   int corMETVer)
{
	// + Some basic info
	//------------------
	TString strDTorMC[2] = {"DT", "MC"};
	printf ("\n---------------------------------------------------------------------------\n");
	printf ("| Program starts, working on [ %d ] data/mc, MET corection version: [ %d ] |\n", year, corMETVer);
	printf ("-----------------------------------------------------------------------------\n\n\n\n");
	
	
	
	// + Start time
	//-------------
	time_t time1 = time(0);
	
	
	
	TString strBool[4] = {"loose", "medium", "tight", "lead2jets"};
	
	int  countLoop = 0;
	
	for (int itight=0; itight<4; itight++)
	{
		for (int cutScenario=0; cutScenario<2; cutScenario++)
		{
			for (int logY=0; logY<2; logY++)
			{
				countLoop ++;
				
				printf ("| + Now starting loop number %02d ...\n", countLoop);
				printf ("|====================================\n");
				printf ("    Arguments being used:\n");
				printf ("    ||-- Use tight selection     = %s\n",   strBool[itight].Data());
				printf ("    ||-- MET correction version  = %d\n",   corMETVer);
				printf ("    ||-- Selection scenario      = %d\n",   cutScenario);
				printf ("    ||-- Use logarithm scale     = %s\n\n", strBool[logY].Data());
				
				CodePlot_DataMC (year, logY, itight, corMETVer, cutScenario);
				
				printf ("| + Loop number %02d is done\n\n\n", countLoop);
			}
		}
	}
	
	
	
	// + End time
	//-----------
	time_t time2 = time(0);
	float  deltime = float(time2 - time1) / 3600.0;
	
	printf ("-------------------------------------\n");
	printf ("| Program ends after [ %2.0f minutes ] |\n", deltime);
	printf ("-------------------------------------\n");
}
