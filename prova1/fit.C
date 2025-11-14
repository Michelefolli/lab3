#include "/home/michele/root/include/TGraphErrors.h"
#include "/home/michele/root/include/TCanvas.h"
#include "/home/michele/root/include/TF1.h"
#include <iostream>
#include <cmath>
void cal()
{

    TGraphErrors *Vcal = new TGraphErrors("caldata.txt", "%lg%lg%lg%lg");
    TF1 *Vline = new TF1("Vline", "[0]+[1]*x", 0., 1.);
    Vline->SetParameters(0., 1.);
    Vcal->Fit("Vline");

    TCanvas *Canva = new TCanvas("Canva", "Calibrazione del multimetro", 600, 400);
    Vcal->SetTitle("Calibrazione degli strumenti");
    Vcal->GetXaxis()->SetTitle("V osc(mV)");
    Vcal->GetYaxis()->SetTitle("V mult(mV)");
    Vcal->Draw("APE");
    Vline->Draw("SAME");

    std::cout << "Parametri di calibrazione: q: " << Vline->GetParameter(0) << " +/- " << Vline->GetParError(0)
              << " "<<std::endl<<" m:" << Vline->GetParameter(1) << " +/- " << Vline->GetParError(1);
}

void fitSi()
{

    TGraphErrors *IVSi = new TGraphErrors("IVdataSi.txt", "%lg%lg%lg%lg");
    

    TF1 *fitSi = new TF1("fitSi", "[0]*(TMath::Exp(x/[1])-1)", 0, 1000);
    

    fitSi->SetParameters(1E-6, 60);
    
    IVSi->Fit(fitSi,"R");
    fitSi->SetLineColor(kRed);
    
    TCanvas *Canva2 = new TCanvas("CanvaSi", "Curve caratteristiche IV Silicio", 600, 400);
    IVSi->GetXaxis()->SetTitle("V(mV)");
    IVSi->GetYaxis()->SetTitle("I(mA)");
    IVSi->Draw("APE");
    fitSi->Draw("SAME")
}
void fitGe(){
 TGraphErrors *IVGe = new TGraphErrors("IVdataGe.txt", "%lg%lg%lg%lg");
 TF1 *fitGe = new TF1("fitGe", "[0]*(TMath::Exp(x/[1])-1)", 0, 1000);
 fitGe->SetParameters(1E-3, 30);

 IVGe->Fit(fitGe, "R"); // specificare opzione Range
    fitGe->SetLineColor(kBlue);
 TCanvas *Canva3 = new TCanvas("CanvaGe", "Curve caratteristiche IV Germanio", 600, 400);
    IVGe->GetXaxis()->SetTitle("V(mV)");
    IVGe->GetYaxis()->SetTitle("I(mA)");
    IVGe->Draw("APE");
    fitGe->Draw("SAME");

}