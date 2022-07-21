void DrawTH2D6(){
    TFile *ficheiro= new TFile("DetParticula.root","READ");

    TH2D *umN=(TH2D*)ficheiro->Get("HistogramaNeutras1");
    TH2D *doisN=(TH2D*)ficheiro->Get("HistogramaNeutras2");
    TH2D *tresN=(TH2D*)ficheiro->Get("HistogramaNeutras3");
    TH2D *quatroN=(TH2D*)ficheiro->Get("HistogramaNeutras4");
  
    
   TCanvas *canvasN= new TCanvas();
   canvasN->Divide(2,2);
   canvasN->cd(1);
   umN->Draw("COLZ");
   
   canvasN->cd(2);
   doisN->Draw("COLZ");
   
   canvasN->cd(3);
   tresN->Draw("COLZ");
   
   canvasN->cd(4);
   quatroN->Draw("COLZ");


    TH2D *umC=(TH2D*)ficheiro->Get("HistogramaCarregadas1");
    TH2D *doisC=(TH2D*)ficheiro->Get("HistogramaCarregadas2");
    TH2D *tresC=(TH2D*)ficheiro->Get("HistogramaCarregadas3");
    TH2D *quatroC=(TH2D*)ficheiro->Get("HistogramaCarregadas4");
  
    
   TCanvas *canvasC= new TCanvas();
   canvasC->Divide(2,2);
   canvasC->cd(1);
   umC->Draw("COLZ");
   
   canvasC->cd(2);
   doisC->Draw("COLZ");
   
   canvasC->cd(3);
   tresC->Draw("COLZ");
   
   canvasC->cd(4);
   quatroC->Draw("COLZ");




}
