#include TGraph
#include TCanvas
#include TF1
#include <iostream>

void cal(){

    TGraphErrors *Vcal = new TGraphErrors("caldata.txt", "%lg%lg%lg%lg"); 
    TF1 *Vline = new TF1("Vline", "[0]+[1]*x", 0., 1.);
    Vline->SetParameters(0.,1.);
    Vcal->Fit("Vline");

    Canva *TCanvas = new TCanvas("Canva", "Calibrazione del multimetro", 600, 400);
    Vcal->Draw("APE");
    Vline->Draw("SAME");

    std::cout<<"Parametri di calibrazione: q: "<<Vline->GetParameter(0)<<" +/- "<<Vline->GetParError(0)
    <<" \n m:"<< Vline->GetParameter(1)<<" +/- "<<Vline->GetParError(1);

}

void fit(){

    TGraphErrors *IVSi = new TGraphErrors("IVdataSi.txt", "%lg%lg%lg%lg"); 
    TGraphErrors *IVGe = new TGraphErrors("IVdataGe.txt", "%lg%lg%lg%lg");

    TF1 *fitSi = new TF1("fitSi", "[0]*(exp(x/[1])-1)", 0., 1.);
    TF1 *fitGe = new TF1("fitGe", "[0]*(exp(x/[1])-1)", 0., 1.);

    fitSi->SetParameters(1E-6, 3.6);
    fitGe->SetParameters(1E-3, 1.8);

    IVSi->Fit(fitSi);
        IVSi->SetLineColor(kRed);
    IVGe->Fit(fitGe); // specificare opzione Range
        IVGe->SetLineColor(kBlue);

    Canva *TCanvas = new TCanvas("Canva", "Curve caratteristiche IV", 600, 400);

    IVSi->Draw("APE");
    IVGe->Draw("SAME");
    fitSi->Draw("SAME");
    fitGe->Draw("SAME");

std::cout<<"Parametri del fit caratteristica IV: \n
Silicio: \n
I0: "<<fitSi->GetParameter(0)<<" +/- "<<fitSi->GetParError(0)<<"
\n
EtaVT: "<<fitSi->GetParameter(1)<<" +/- "<<fitSi->GetParError(1)<<
"\n
Germanio: \n
I0: "<<fitGe->GetParameter(0)<<" +/- "<<fitGe->GetParError(0)<<"
\n
EtaVT: "<<fitGe->GetParameter(1)<<" +/- "<<fitGe->GetParError(1)<<"\n";
std::cout<<"Chi quadro fit silicio: " << fitSi->GetChiSquare()/fitSi->GetNdF() << "\n
Chi quadro fit germanio: " <<fitGe->GetChiSquare()/fitGe->GetNdF();


}
