void DrawEnergia(){
    TFile *ficheiro= new TFile("EnergiaFinal.root","READ");

    TH1D *pioes=(TH1D*)ficheiro->Get("Pioes");
    TH1D *muoes=(TH1D*)ficheiro->Get("Muoes");
    TH1D *outras=(TH1D*)ficheiro->Get("OutrasParticulas");
    
    THStack *hs = new THStack("hs","Energia depositada por particulas;Energia (keV); log(Tempo(ns))");
    hs->Add(pioes);
    hs->Add(muoes);
    hs->Add(outras);
    hs->Draw("nostack");

    gPad->SetLogy();



}
