void DrawVertex(){
    TFile *ficheiro= new TFile("VertexFinal.root","READ");

    TH1D *vPrimario=(TH1D*)ficheiro->Get("VertexPrimario");
    TH1D *vSecundario=(TH1D*)ficheiro->Get("VertexSecundario");
    
    THStack *hs = new THStack("hs","Hadronic vertex;Posicao de Z (cm); log(Tempo (ns))");
    hs->Add(vPrimario);
    hs->Add(vSecundario);

    hs->Draw("nostack");
    
    auto legend = new TLegend(0.5,0.5,0.8,0.8,NULL,"brNDC");
    TLegendEntry *ds=legend->AddEntry("vPrimario","Vertex Primario","l");
    ds->SetLineColor(1);
    
    ds=legend->AddEntry("vSecundario","Vertex Secundario","l");
    ds->SetLineColor(2);
    
    
    legend-> Draw();
    

    gPad->SetLogy();



}
