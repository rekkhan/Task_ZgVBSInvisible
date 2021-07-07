#include <stdio.h>
#include "CodeAna_Yield.C"

void run_Yield (int year,   bool doLoop,   int tightness=0,   int corMETVer=0,   int cutScenario=0)
{
	TString strBool[4] = {"loose", "medium", "tight", "lead2jets"};
	
	if (doLoop)
	{
		printf (" [#] [doLoop] mode is activated, now going through all argument ...\n");
		
		int  countLoop = 0;
		
		for (tightness=0; tightness<4; tightness++)
		{
			for (corMETVer=1; corMETVer<3; corMETVer++)
			{
				for (cutScenario=0; cutScenario<2; cutScenario++)
				{
					for (int isCollective=0; isCollective<2; isCollective++)
					{
						countLoop ++;
						
						printf ("| + Now starting loop number %02d ...\n", countLoop);
						printf ("|====================================\n");
						printf ("    Arguments being used:\n");
						printf ("    ||-- Use tight selection     = %s\n",   strBool[tightness].Data());
						printf ("    ||-- MET correction version  = %d\n",   corMETVer);
						printf ("    ||-- Selection scenario      = %d\n",   cutScenario);
						printf ("    ||-- Print collective yield  = %s\n\n", strBool[isCollective].Data());
						
						CodeAna_Yield (year, isCollective, tightness, corMETVer, cutScenario);
						
						printf ("| + Loop number %02d is done\n\n\n\n\n", countLoop);
					}
				}
			}
		}
	}
	else
	{
		printf (" [#] [doLoop] mode is deactivated, now using provided argument ...\n");
		int  countLoop = 0;
		
		for (int isCollective=0; isCollective<2; isCollective++)
		{
			countLoop ++;
			
			printf ("| + Now starting loop number %02d ...\n", countLoop);
			printf ("|====================================\n");
			printf ("    Arguments set:\n");
			printf ("    ||-- Use tight selection     = %s\n",   strBool[tightness].Data());
			printf ("    ||-- MET correction version  = %d\n",   corMETVer);
			printf ("    ||-- Selection scenario      = %d\n",   cutScenario);
			printf ("    ||-- Use logarithm scale     = %s\n\n\n\n\n", strBool[isCollective].Data());
			CodeAna_Yield (year, isCollective, tightness, corMETVer, cutScenario);
		}
	}
}
