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

    
    auto legend = new TLegend(0.5,0.5,0.8,0.8,NULL,"brNDC");
    TLegendEntry *ds=legend->AddEntry("muoes","Muoes","l");
    ds->SetLineColor(2);
    
    ds=legend->AddEntry("pioes","Pioes","l");
    ds->SetLineColor(1);
    
    ds=legend->AddEntry("outras","Outras","l");
    ds->SetLineColor(3);
    
    legend-> Draw();
    

    gPad->SetLogy();



}
