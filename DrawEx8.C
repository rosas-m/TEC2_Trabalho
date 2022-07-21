void DrawEx8(){
    TFile *ficheiro= new TFile("Momento.root","READ");

    TH1D *pioes=(TH1D*)ficheiro->Get("Histo_PMZ");
    TH1D *muoes=(TH1D*)ficheiro->Get("Histo_MMZ");
    
    THStack *hs = new THStack("hs","Histograma Do Momento na componente Z;log(Contagem(n)); Momento(Nm)");
    hs->Add(pioes);
    hs->Add(muoes);
    hs->Draw("nostack");

    gPad->SetLogy();



}
