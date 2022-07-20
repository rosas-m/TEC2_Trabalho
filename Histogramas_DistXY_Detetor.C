void Histogramas_DistXY_Detetor(TString ficheiroLido){

//Seleção de ficheiros a ler assim como escrever
TFile *ficheiro = new TFile("AmberTarget_Run_0.root","READ");

TString novoFicheiro=ficheiroLido;
novoFicheiro.ReplaceAll("AmberTarget_Run_","Analise_Histogramas_DistXY_Detetor_");
	
TFile *ficheiroGravar = new TFile(novoFicheiro,"RECREATE");
TTree *dados = (TTree*) ficheiro->Get("Hits"); /*Seleção da árvore Hits em que iremos buscar a posição dos hits nos eixos X e Y assim como o o ID de detetor*/
	   

Int_t nBins = 100;
//Como vai até 40 deu-se um intervalo de 5 para se ver o final
Double_t minBin = -45.0;
Double_t maxBin = 45.0;

Int_t nHistos = 4;


TH2D* histo[nHistos];
TCanvas *canvas = new TCanvas("canvas",novoFicheiro,3000,1000);
gStyle->SetOptStat(0);
canvas->Divide(2,2);

TString branchX;
TString branchY; 


	
/*A cada iteração iremos produzir um histograma para um detetor, selecionando as branchs hitPosX_cm e hitPosY_cm e a branch detectorID que será utilizada para localizar o detetor dos hits*/
for(Int_t i = 0; i < nHistos; i++){
	
	TString HistNome = "Histograma " + TString::Itoa(i+1, 10);

	histo[i] = new TH2D(HistNome, HistNome, nBins, minBin, maxBin, nBins, minBin, maxBin);//Criar o histograma
	branchX = "hitPosX_cm";
    branchY = "hitPosY_cm";
    canvas->cd(i+1);
	dados->Draw(branchX +":" + branchY + ">>" + HistNome, "detectorID=="+ TString::Itoa(i, 10),"colz");//Seleção dos hits pertencentes ao detetor usando a condição "detectorID=="
    histo[i]->SetTitle(HistNome);
    histo[i]->GetXaxis()->SetTitle("X");
    histo[i]->GetYaxis()->SetTitle("Y");
    ficheiroGravar->cd();
    histo[i]->Write();
    
	}

ficheiro->Close();
ficheiroGravar->Close();


}
