#ifndef TOOL_PLOTTINGSTYLE_H
#define TOOL_PLOTTINGSTYLE_H










//====================================
// + Histogram for analysis setting up
//====================================
// + Histogram for observables
//----------------------------
void Characterize_Dist1D (TH1 *hist,  float ratio,  bool hasRatio,   int colour_fill,  int style_fill,  int colour_mark,  int style_mark,  int line_width,  TString name_Xaxis,  bool setLogY)
{
	float scaleXtext = 0.0;
	
	if (!hasRatio)
	{
		ratio = 0.5;
		scaleXtext = 0.5;
	}
	// * Check whether the histogram need to be scaled by bin-width
	int   nBin = hist -> GetNbinsX ();
	float widthBin = hist -> GetBinWidth (1);
	//printf (" + - Width of bin %d in %s is: %.2f\n", 1, name_Xaxis.Data(), widthBin);
	
	int nDiff = 0;
	
	for (int i=2; i<=nBin; i++)
	{
		if (hist->GetBinWidth(i)<widthBin*0.99 || hist->GetBinWidth(i)>widthBin*1.01)
		{
			nDiff++;
			//printf ("   - Width of bin %d in %s is: %.5f\n", i, name_Xaxis.Data(), hist->GetBinWidth(i));
		}
	}
	
	TString name_Yaxis;
	if (nDiff > 0)
	{
		hist -> Scale (1, "width");
		name_Yaxis = "Events/GeV";
	}
	else
	{
		name_Yaxis = "Events";
	}
	
	if (setLogY == false)   hist -> SetMinimum (0);
	
	hist -> SetTitle       ("");
	hist -> SetFillColor   (colour_fill);
	hist -> SetFillStyle   (style_fill);
	hist -> SetMarkerColor (colour_mark);
	hist -> SetMarkerStyle (style_mark);
	hist -> SetLineColor   (colour_mark);
	hist -> SetLineWidth   (line_width);
	hist -> SetMarkerSize  (1.5);
	hist -> SetMinimum     (0.01);
	
	hist -> GetXaxis() -> SetTitle       (name_Xaxis.Data());
	hist -> GetXaxis() -> SetTitleSize   (0.047*scaleXtext);
	hist -> GetXaxis() -> SetTitleOffset (0.840*scaleXtext);
	hist -> GetXaxis() -> SetLabelSize   (0.040*scaleXtext);
	hist -> GetXaxis() -> SetLabelOffset (0.006*scaleXtext);
	
	hist -> GetYaxis() -> SetTitle          (name_Yaxis.Data());
	hist -> GetYaxis() -> SetMaxDigits      (4);
	hist -> GetYaxis() -> SetTitleSize      (0.047);
	hist -> GetYaxis() -> SetTitleOffset    (0.350*ratio);
	hist -> GetYaxis() -> SetLabelSize      (0.040);
	hist -> GetYaxis() -> SetLabelOffset    (0.006);
	
	TGaxis :: SetMaxDigits (4);
	TGaxis :: SetExponentOffset (-0.10, 0.02, "y");
}





// + Histogram for ratio
//----------------------
void Characterize_Rate1D (TH1 *hist,  int colour,  int style_mark,  TString name_Xaxis)
{
	float ratio = 7.5/2.5;
	hist -> SetTitle       ("");
	hist -> SetLineColor   (colour);
	hist -> SetMarkerColor (colour);
	hist -> SetMarkerStyle (style_mark);
	hist -> SetMarkerSize  (1.5);
	hist -> SetFillColor   (colour);
	
	hist -> GetXaxis() -> SetTitle       (name_Xaxis.Data());
	hist -> GetXaxis() -> SetTitleSize   (0.047*ratio);
	hist -> GetXaxis() -> SetTitleOffset (0.940);
	hist -> GetXaxis() -> SetLabelSize   (0.040*ratio);
	hist -> GetXaxis() -> SetLabelOffset (0.004*ratio);
	
	hist -> GetYaxis() -> SetTitle       ("Data/MC");
	hist -> GetYaxis() -> SetTitleSize   (0.047*ratio);
	hist -> GetYaxis() -> SetTitleOffset (0.350);
	hist -> GetYaxis() -> SetLabelSize   (0.040*ratio);
	hist -> GetYaxis() -> SetLabelOffset (0.006);
	hist -> GetYaxis() -> SetRangeUser   (-0.2, 3.2);
	hist -> GetYaxis() -> SetNdivisions  (505);
}










//=============
// * Pad set up
//=============
void Characterize_Pad (TPad *pad, float left, float right, float top, float bottom, int logY)
{
	pad -> SetGrid (1, 1);
	pad -> SetLeftMargin   (left);
	pad -> SetRightMargin  (right);
	pad -> SetTopMargin    (top);
	pad -> SetBottomMargin (bottom);
	pad -> SetLogy (logY);
}










//===============
// * Latex set up
//===============
void Characterize_Latex (TLatex *tex, int texfont, float texsize)
{
	tex -> SetNDC ();
	tex -> SetTextFont (texfont);
	tex -> SetTextSize (texsize);
}










#endif
