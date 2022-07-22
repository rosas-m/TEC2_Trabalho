void Histogramas_MZ_MP(TString ficheiroLido){

//Seleção de ficheiros a ler assim como escrever
TFile *ficheiro = new TFile("AmberTarget_Run_0.root","READ");
TString novoFicheiro=ficheiroLido;
novoFicheiro.ReplaceAll("AmberTarget_Run_","Analise_Histogramas_MZ_MP_");
    
TFile *ficheiroGravar = new TFile(novoFicheiro,"RECREATE");
TTree *dados = (TTree*) ficheiro->Get("tracksData"); /*Seleção da árvore tracksData em que iremos buscar a branche pZ_GeV que contém a energia do momento no eixo Z, também usamos particlePDG que irá ser útil para verificar se a particula é um muão ou um pião*/

Int_t nBinM = 60;
Double_t minBinM = -5;
Double_t maxBinM=30;
Int_t nBinP = 215; 
Double_t minBinP = -5;
Double_t maxBinP = 220;

Int_t nHistos = 2;
TCanvas *canvas = new TCanvas("canvas",novoFicheiro,900,700);
gStyle->SetOptStat(0);
canvas->Divide(2,1,0,0);

//MUÕES
TString HistoNome_MMZ = "Histograma Do Momento na componente Z para Muoes";
TH1D* Histo_MMZ = new TH1D(HistoNome_MMZ, HistoNome_MMZ,nBinM,minBinM,maxBinM);
canvas->cd(1);
dados->Draw("pZ_GeV>>"+HistoNome_MMZ,"particlePDG==13 || particlePDG==-13");//Seleção da energia do momento dos puões, utilizando a condição particlePDG == -13 (para os positivos) ou particlePDG == 13 (para os negativos)
Histo_MMZ->SetLineColor(2);
//Histo MMZ->GetXaxis()->SetTitle("Momento(Nm)");
//Histo MMZ->GetYaxis()->SetTitle("log(Contagem(n))");
Histo_MMZ->Write();
gPad->SetLogy();//Selecionar escala logaritmica

  

//PIÕES
TString HistoNome_PMZ = "Histograma Do Momento na componente Z para Pioes";
TH1D* Histo_PMZ = new TH1D(HistoNome_PMZ,HistoNome_PMZ,nBinP,minBinP,maxBinP);
canvas->cd(2);
dados->Draw("pZ_GeV>>"+HistoNome_PMZ,"particlePDG==211 || particlePDG==-211");//Seleção da energia do momento dos piões, utilizando a condição particlePDG == 211 (para os positivos) ou particlePDG == -211 (para os negativos)
Histo_PMZ->SetLineColor(3);
//Histo PMZ->GetXaxis()->SetTitle("Momento(Nm)");
//Histo PMZ->GetYaxis()->SetTitle("log(Contagem(n))");
Histo_PMZ->Write();
gPad->SetLogy();//Selecionar escala logaritmica


ficheiro->Close();
ficheiroGravar->Close();
		
}
