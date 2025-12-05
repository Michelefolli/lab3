#include "/home/michele/root/include/TGraphErrors.h"
#include "/home/michele/root/include/TCanvas.h"
#include "/home/michele/root/include/TF1.h"
#include "/home/michele/root/include/TFile.h"
#include <iostream>
#include <cmath>
void cal(TFile* f)
{
    f->cd();
    TGraphErrors *Vcal = new TGraphErrors("caldata.txt", "%lg %lg %lg %lg");
    TF1 *Vline = new TF1("Vline", "[0]+[1]*x", 0., 1.);
    Vline->SetParameters(0., 1.);
    Vcal->Fit("Vline");

    TCanvas *Cal = new TCanvas("Canva", "Calibrazione del multimetro");
    Vcal->SetTitle("Calibrazione degli strumenti");
    Vcal->GetXaxis()->SetTitle("V mult(mV)");
    Vcal->GetYaxis()->SetTitle("V osc(mV)");
    Vcal->Draw("APE");
    Vline->Draw("SAME");
    Cal->Write();
    Cal->SaveAs("CalCanvas.pdf"); 
    std::cout << "Parametri di calibrazione: q: " << Vline->GetParameter(0) << " +/- " << Vline->GetParError(0)
              << " "<<std::endl<<" m:" << Vline->GetParameter(1) << " +/- " << Vline->GetParError(1);
}

void fitSi(TFile* f)
{
    f->cd();
    TGraphErrors *IVSi = new TGraphErrors("IVdataSi.txt", "%lg %lg %lg %lg");
    TF1 *fitSi = new TF1("fitSi", "[0]*(TMath::Exp(x/[1])-1)", 440, 600);
    

    fitSi->SetParameters(1E-6, 60);
    
    IVSi->Fit(fitSi,"R");
    fitSi->SetLineColor(kRed);
    
    TCanvas *SiChar = new TCanvas("CanvaSi", "Curve caratteristiche IV Silicio");
    IVSi->SetTitle("Caratteristica IV Silicio");
    IVSi->GetXaxis()->SetTitle("V(mV)");
    IVSi->GetYaxis()->SetTitle("I(mA)");
    IVSi->Draw("APE");
    fitSi->Draw("SAME");
    SiChar->Write();
     SiChar->SaveAs("SiCanvas.pdf");
}

void fitGe(TFile* f){

     f->cd();
 TGraphErrors *IVGe = new TGraphErrors("IVdataGe.txt", "%lg%lg%lg%lg");
 TF1 *fitGe = new TF1("fitGe", "[0]*(TMath::Exp(x/[1])-1)", 150, 240);
 fitGe->SetParameters(1E-3, 30);

 IVGe->Fit(fitGe, "R"); // specificare opzione Range
    fitGe->SetLineColor(kBlue);
 TCanvas *GeChar = new TCanvas("CanvaGe", "Curve caratteristiche IV Germanio");
    IVGe->SetTitle("Caratteristica IV Germanio");
    IVGe->GetXaxis()->SetTitle("V(mV)");
    IVGe->GetYaxis()->SetTitle("I(mA)");
    IVGe->Draw("APE");
    fitGe->Draw("SAME");
    GeChar->Write();
    GeChar->SaveAs("GeCanvas.pdf");
}

void analysis(){
    TFile *output = new TFile("output.root","RECREATE");
    cal(output);
    fitGe(output);
    fitSi(output);
    output->Write();
    output->Close();
}