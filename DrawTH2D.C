void DrawTH2D(){
    TFile *ficheiro= new TFile("allData.root","READ");

    TH2D *um=(TH2D*)ficheiro->Get("Histograma 1");
    TH2D *dois=(TH2D*)ficheiro->Get("Histograma 2");
    TH2D *tres=(TH2D*)ficheiro->Get("Histograma 3");
    TH2D *quatro=(TH2D*)ficheiro->Get("Histograma 4");
  
    
   TCanvas *canvas= new TCanvas();
   canvas->Divide(2,2);
   canvas->cd(1);
   um->Draw("COLZ");
   
   canvas->cd(2);
   dois->Draw("COLZ");
   
   canvas->cd(3);
   tres->Draw("COLZ");
   
   canvas->cd(4);
   quatro->Draw("COLZ");


}
