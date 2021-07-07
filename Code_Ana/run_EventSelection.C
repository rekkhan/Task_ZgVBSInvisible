#include "CodeAna_EventSelection.C"

void run_EventSelection (int year,   bool isMC,   int file_1st,   int file_2nd)
{
	// + Some basic info
	//------------------
	TString strDTorMC[2] = {"DT", "MC"};
	printf ("\n------------------------------------------------------------------------------\n");
	printf ("| Program starts, working on [ %d %s ], from file [ # %02d ] to file [ # %02d ] |\n", year, strDTorMC[isMC].Data(), file_1st, file_2nd);
	printf ("------------------------------------------------------------------------------\n\n");
	
	
	
	// + Start time
	//-------------
	time_t time1 = time(0);
	
	
	
	// NOTE Run multiple files
	for (int ifile=file_1st-1; ifile<file_2nd; ifile++)
	{
		for (int itight=0; itight<4; itight++)
		{
			for (int icor=1; icor<3; icor++)
			{
				for (int iscen=0; iscen<2; iscen++)
				{
					printf (" [+] File [ #%d ]  --  tightness: [ %d ]  --  METCor version: [ %d ]  --  Cut scenario: [ %d ]\n", ifile+1, itight, icor, iscen);
					CodeAna_EventSelection (year, isMC, ifile+1, itight, icor, iscen);
					printf ("\n");
				}
			}
		}
	}
	
	
	
	// + End time
	//-----------
	time_t time2 = time(0);
	float  deltime = float(time2 - time1) / 3600.0;
	
	printf ("--------------------------------------\n");
	printf ("| Program ends after [ %5.2f hours ] |\n", deltime);
	printf ("--------------------------------------\n");
}
