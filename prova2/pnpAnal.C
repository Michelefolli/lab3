
#include "/home/michele/root/include/TGraphErrors.h"
#include "/home/michele/root/include/TCanvas.h"
#include "/home/michele/root/include/TF1.h"
#include "/home/michele/root/include/TFile.h"
#include <iostream>
#include <cmath>
TGraphErrors* Betacalc(TGraphErrors* Graph1, TGraphErrors* Graph2, int n_min, int nmax ){
    TGraphErrors  gBeta = new
};
void analyze()
{
    TFile *output = new TFile("output.root", "RECREATE");

    TGraphErrors *IV1 = new TGraphErrors("IV1data.txt", "%lg %lg %lg %lg");
    TF1 *fit1 = new TF1("fit1", "[0]+[1]*x"); // specificare range
    fit1->SetParameters();                     // parametri aspettati (il primo è tensione di early,
                                                // il secondo la resistività)
    IV1->Fit(fit1,"R");
    fit1->SetLineColor(kRed);


    TGraphErrors *IV2 = new TGraphErrors("IV2data.txt", "%lg %lg %lg %lg");
    TF1 *fit2 = new TF1("fit2", "[0]+[1]*x"); // specificare range
    fit2->SetParameters();                     // parametri aspettati (il primo è tensione di early,
                                                // il secondo la resistività)
    IV2->Fit(fit2,"R");
    fit2->SetLineColor(kGreen);
    

    TCanvas * IVchar = new TCanvas("Char","Curve di Caratteristica");
    IV1->GetXaxis()->SetTitle("-V(V)");
    IV1->GetYaxis()->SetTitle("-I(mA)");
    IV1->Draw("APE");
    fit1->Draw("SAME");
    IV2->Draw("SAME");
    fit2->Draw("SAME");
    IVchar->Write(output);

    //BETA
    int n_min=0;//inizio range attivo
    int n_max=100; //fine range
    double betasum;
    double count;
    for(int i=n_min; i<n_max; ++i){
        double Ic1 = IV1->GetY(i, Ic1);
        double Ic2= IV2->GetY(i,Ic2);
        double errIc1 = IV1->GetErrorY(i);
        double errIc2 = IV2->GetErrorY(i);
        
        double dIc= Ic1-Ic2;
        double beta = dIc/50E-3; // se sono in mA
        betasum+= beta;
        count++;
    }
    double betamean = betasum/count;
    std::cout << " BETA PARAMETER: "<<betamean;

    }