
#include "/home/michele/root/include/TGraphErrors.h"
#include "/home/michele/root/include/TCanvas.h"
#include "/home/michele/root/include/TF1.h"
#include "/home/michele/root/include/TFile.h"
#include <iostream>
#include <cmath>
void analyze()
{
    TFile *output = new TFile("output.root", "RECREATE");

    TGraphErrors *IV1 = new TGraphErrors("IV1data.txt", "%lg %lg %lg %lg");
    TGraphErrors *IV2 = new TGraphErrors("IV2data.txt", "%lg %lg %lg %lg");
    int n_min=0;//inizio range attivo
    int n_max=8; //fine range
   
    //FIT BETA
    TGraphErrors* betaG= new TGraphErrors();
    for(int i=n_min; i<n_max; ++i){
        double V, Ic1, Ic2;
        IV1->GetPoint(i,V, Ic1);
        IV2->GetPoint(i,V, Ic2);
        double errIc1 = IV1->GetErrorY(i);
        double errIc2 = IV2->GetErrorY(i);
        double errbeta= sqrt(errIc1*errIc1+errIc2*errIc2)/fabs(Ic1-Ic2);
        double betai= (Ic1-Ic2)/50E-3; //il valore è in mA
        betaG->SetPoint(i, V, betai);
        betaG->SetPointError(i,0, errbeta);
    }
    TF1* betafit= new TF1("b","pol0",0,40);//specify range
    betaG->Fit(betafit, "R");
    std::cout << " BETA PARAMETER: "<< betafit->GetParameter(0) << "+/-" << betafit->GetParError(0) << std::endl;
    
    //DISEGNO
    TCanvas * IVchar = new TCanvas("Char","Curve di Caratteristica");
    IV1->GetXaxis()->SetTitle("-V_{CE}(V)");
    IV1->GetYaxis()->SetTitle("-I_{C}(mA)");
    IV1->GetYaxis()->SetLimits(0.,25.);
    IV1->SetLineColor(kRed);
    IV2->SetLineColor(kBlue);
    IV1->Draw("APE");
    IV2->Draw("SAME");
    IVchar->Write();
    
    TGraphErrors *VI1 = new TGraphErrors("VI1data.txt", "%lg %lg %lg %lg");
    TGraphErrors *VI2 = new TGraphErrors("VI2data.txt", "%lg %lg %lg %lg");
    
    TF1 *fit1 = new TF1("fit1", "[0]+[1]*x",18.65,22); // specificare range
    fit1->SetParameters(30,1);                     // parametri aspettati (il primo è tensione di early,
                                                // il secondo la resistività)
    VI1->Fit(fit1,"R");
    fit1->SetLineColor(kRed);
    TF1 *fit2 = new TF1("fit2", "[0]+[1]*x",9.62,11.); // specificare range
    fit2->SetParameters(30,0.5);                     // parametri aspettati (il primo è tensione di early,
                                                // il secondo la resistività)
    VI2->Fit(fit2,"R");
    fit2->SetLineColor(kGreen);
    std::cout << "Fit 1 (50uA): \n Early tension(V): " << -fit1->GetParameter(0)<< 
    "\n Conductivity (mA/V): " << 1/fit1->GetParameter(1)<< std::endl;
     std::cout << "Fit 2 (100uA): \n Early tension(V): " << -fit2->GetParameter(0)<< 
    "\n Conductivity (mA/V): " << 1/fit2->GetParameter(1)<< std::endl;

    output->Close();
    }