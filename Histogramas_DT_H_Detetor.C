void Histogramas_DT_H_Detetor(TString ficheiroLido){ 


//Seleção de ficheiros a ler assim como escrever
TFile *ficheiro = new TFile("AmberTarget_Run_0.root","READ");
	
TString novoFicheiro=ficheiroLido;
novoFicheiro.ReplaceAll("AmberTarget_Run_","Analise_Histogramas_DT_H_Detetor_");
	
TFile *ficheiroGravar = new TFile(novoFicheiro,"RECREATE");
TTree *dados = (TTree*) ficheiro->Get("Hits");/*Seleção da árvore Hits em que iremos buscar a branch particleHitTime, para obter o tempo que as particulas demoraram para chegar ao detetor e selecionamos também a branch detectorID para filtrar as o tempo de choque das particulas para os respetivos detetores*/
	 
Int_t nBins = 50;
Double_t minBin = 0.0;
Double_t maxBin = 400;
	
Int_t nHistos = 4;
TH1D* histo[nHistos];
TString branchName;


TCanvas *canvas = new TCanvas("canvas", novoFicheiro, 900, 700);
gStyle->SetOptStat(0);
canvas->Divide(2,2,0,0);

	
/*A cada iteração iremos desenhar um histograma para um dado detetor, para isto iremos filtrar os dados de particleHitTime usando o detectorID que igual ao foi selecionado durante a iteração*/
for(Int_t i = 0 ;i < nHistos; i++){

	TString HistoNome = "Histograma " + TString::Itoa(i+1, 10);
	histo[i] = new TH1D(HistoNome, HistoNome, nBins, minBin, maxBin);
	branchName = "particleHitTime_ns";
   	canvas->cd(i+1);
	dados->Draw(branchName + ">>" + HistoNome, "detectorID=="+ TString::Itoa(i, 10) );//Seleção dos dados e a condição de o detectorID ser o que foi selecionado neesta iteração
	gPad->SetLogy(); //selecionar escala logaritmica
	histo[i]->SetFillColor(i+1);
   	histo[i]->SetTitle(HistoNome);
	histo[i]->Write();

	}

}
