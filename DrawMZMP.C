void DrawMZMP(){
    TFile *ficheiro= new TFile("Momento.root","READ");

    TH1D *muoes=(TH1D*)ficheiro->Get("Histograma Do Momento na componente Z para Muoes");
    TH1D *pioes=(TH1D*)ficheiro->Get("Histograma Do Momento na componente Z para Pioes");

    
    THStack *hs = new THStack("hs","Histograma Do Momento na componente Z;Momento(Gev/C); log(Contagem(n))");
    hs->Add(pioes);
    hs->Add(muoes);
    hs->Draw("nostack");
    
    auto legend = new TLegend(0.5,0.5,0.8,0.8,NULL,"brNDC");
    TLegendEntry *ds=legend->AddEntry("muoes","Muoes","l");
    ds->SetLineColor(2);
    
    ds=legend->AddEntry("pioes","Pioes","l");
    ds->SetLineColor(3);
    
    legend-> Draw();
    

    gPad->SetLogy();

}
