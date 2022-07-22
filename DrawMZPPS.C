void DrawMZPPS(){
    TFile *ficheiro= new TFile("Momento2.root","READ");

    TH1D *primarios=(TH1D*)ficheiro->Get("Pioes Primarios");
    TH1D *secundarios=(TH1D*)ficheiro->Get("Pioes Secundarios");

    
    THStack *hs = new THStack("hs","Histograma Do Momento na componente Z;Momento(Gev/C); log(Contagem(n))");
    hs->Add(primarios);
    hs->Add(secundarios);
    hs->Draw("nostack");
    
    auto legend = new TLegend(0.5,0.5,0.8,0.8,NULL,"brNDC");
    TLegendEntry *ds=legend->AddEntry("primarios","Pioes Primarios","l");
    ds->SetLineColor(2);
    
    ds=legend->AddEntry("secundarios","Pioes Secundarios","l");
    ds->SetLineColor(3);
    
    legend-> Draw();
    

    gPad->SetLogy();

}
