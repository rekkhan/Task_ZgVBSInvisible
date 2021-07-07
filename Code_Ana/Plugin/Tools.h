#ifndef TOOL_H
#define TOOL_H




using namespace std;





// + define the value for Pi
//==========================
Double_t pival = 3.14159265358979323846;





// + Computation of delta Phi
//===========================
Double_t compute_DeltaPhi (Float_t phi1, Float_t phi2)
{
	Double_t subtraction = phi1 - phi2;
	Double_t delPhi;
	
	if (abs(subtraction) > pival)   delPhi = 2*pival - abs(subtraction);
	else   delPhi = abs(subtraction);
	
	return delPhi;
}





// + Computation of delta R (eta, phi)
//====================================
Double_t compute_DeltaR (Double_t eta1, Double_t eta2, Double_t phi1, Double_t phi2)
{
	// * Calculate deltaPhi
	Double_t subtraction = phi1 - phi2;
	Double_t delPhi;
	
	if (abs(subtraction) > pival)   delPhi = 2*pival - abs(subtraction);
	else   delPhi = abs(subtraction);
	
	
	// * Calculate delta eta
	Double_t delEta = eta1 - eta2;
	
	
	// * Calculate deltaR
	Double_t delR = sqrt (pow(delPhi,2) + pow(delEta,2));
	return delR;
}





// + Computation of delta R2 (theta, phi)
//=======================================
Double_t compute_DeltaR2 (Double_t theta1, Double_t theta2, Double_t phi1, Double_t phi2)
{
	// * Calculate deltaPhi
	Double_t dPhi = phi1 - phi2;
	Double_t delPhi = 0;
	
	if (abs(dPhi) > pival)   delPhi = 2*pival - abs(dPhi);
	else   delPhi = abs(dPhi);
	
	
	// * Calculate delta theta
	Double_t dTheta = theta1 - theta2;
	Double_t delTheta = 0;
	
	if (abs(dTheta) > pival)   delTheta = 2*pival - abs(dTheta);
	else   delTheta = abs(dTheta);
	
	
	// * Calculate deltaR2
	Double_t delR = sqrt (pow(delPhi,2) + pow(delTheta,2));
	return delR;
}




Double_t compute_DeltaRnorm (Double_t eta1, Double_t eta2, Double_t phi1, Double_t phi2)
{
	// * define the value for Pi
	Double_t pival = 3.14159265358979323846;
	
	
	// * Calculate deltaPhi
	Double_t subtraction = phi1 - phi2;
	Double_t delPhi;
	Double_t normfactor = (abs(eta1) > abs(eta2)) ? abs(eta1) : abs(eta2);
	
	if (abs(subtraction) > pival)   delPhi = 2*pival - abs(subtraction);
	else   delPhi = abs(subtraction);
	
	
	// * Calculate normalized delta eta
	Double_t delEta;
	if (normfactor == 0) delEta = abs(eta1 - eta2)/normfactor;
	else                 delEta = 0;
	
	
	// * Calculate deltaR
	Double_t delR = sqrt (pow(delPhi,2) + pow(delEta,2));
	return delR;
}



#endif
