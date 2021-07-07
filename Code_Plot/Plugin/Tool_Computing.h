#ifndef TOOL_COMPUTING_H
#define TOOL_COMPUTING_H





//============================
// * Compute - Rounding number
//============================
int  Calc_Rounding (int number)
{
	int outNum = number*10;
	int chkNum = number;
	
	int countTen = 0;
	
	while (chkNum/10 > 0)
	{
		countTen ++;
		outNum /= 10;
		chkNum /= 10;
	}
	
	for (int i=0; i<countTen; i++)
	{
		chkNum *= 10;
		outNum *= 10;
	}
	
	outNum /= 10;
	
	return outNum;
}





//===========================
// * Compute - Exponent value
//===========================
int  Calc_valExponent (int number)
{
	int chkNum = number;
	int countTen = 0;
	
	while (chkNum/10.0 > 0)
	{
		chkNum /= 10.0;
		countTen ++;
	}
	
	
	return countTen;
}





//=======================
// * Compute - Base value
//=======================
float  Calc_valBase (float number)
{
	float outNum = number;
	
	while (outNum/10 >= 1)
	{
		outNum /= 10;
	}
	
	
	return outNum;
}




#endif
