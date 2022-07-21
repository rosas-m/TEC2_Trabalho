void DrawVertex(){
    TFile *ficheiro= new TFile("VertexFinal.root","READ");

    TH1D *vPrimario=(TH1D*)ficheiro->Get("VertexPrimario");
    TH1D *vSecundario=(TH1D*)ficheiro->Get("VertexSecundario");
    
    THStack *hs = new THStack("hs","Hadronic vertex;Posicao de Z (cm); log(Tempo (ns))");
    hs->Add(vPrimario);
    hs->Add(vSecundario);

    hs->Draw("nostack");

    gPad->SetLogy();



}
