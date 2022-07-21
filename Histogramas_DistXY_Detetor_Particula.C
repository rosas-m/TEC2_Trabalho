void Histogramas_DistXY_Detetor_Particula(TString ficheiroLido){

//Seleção de ficheiros a ler assim como escrever
TFile *ficheiro = new TFile("AmberTarget_Run_0.root","READ");
	
TString novoFicheiro=ficheiroLido;
novoFicheiro.ReplaceAll("AmberTarget_Run_","Analise_Histogramas_DistXY_Detetor_Particula_");
	
TFile *ficheiroGravar = new TFile(novoFicheiro,"RECREATE");
TTree *dados = (TTree*) ficheiro->Get("Hits");/*Seleção da árvore Hits em que iremos buscar a posição dos hits nos eixos X e Y, o ID de detetor e particleCharge que irá nos permitir selecionar as particulas carregadas das neutras*/
	   

Int_t nBins = 100;
//Como vai até 40 deu-se um intervalo de 5 para se ver o final
Double_t minBin = -45.0;
Double_t maxBin = 45.0;

Int_t nHistos = 4;

//NEUTRAS
TH2D* histoN[nHistos];
TCanvas *canvasN = new TCanvas("canvasN",novoFicheiro,3000,700);
gStyle->SetOptStat(0);
canvasN->Divide(4,0,0,0);

TString branchXN;
TString branchYN; 
	
/*Neste for iremos selecionar as particulas neutras, a cada iteração iremos fazer um histograma para um detetor, para isto temos de selecionar as branchs hitPosX_cm e hiyPosY_cm, a branch detectorID que será utilizada para localizar o detetor dos hits e a branch particleCharge irá definir a carga da particula em que se for igual a 0 é neutra */
for(Int_t i = 0; i < nHistos; i++){
	
	TString HistNome = "HistogramaNeutras" + TString::Itoa(i+1, 10);
	histoN[i] = new TH2D(HistNome, HistNome, nBins, minBin, maxBin, nBins, minBin, maxBin);
	branchXN = "hitPosX_cm";
    branchYN = "hitPosY_cm";
    canvasN->cd(i+1);
	dados->Draw(branchXN +":" + branchYN + ">>" + HistNome, "detectorID=="+ TString::Itoa(i, 10) + " && particleCharge == 0","colz"); //Selecção das branches assim como as condições de pertencer ao detetor e ser uma particula neutra 
    histoN[i]->SetTitle(HistNome);
    histoN[i]->GetXaxis()->SetTitle("X");
    histoN[i]->GetYaxis()->SetTitle("Y");
    ficheiroGravar->cd();
    histoN[i]->Write();

	}




//CARREGADAS
TH2D* histoC[nHistos];
TCanvas *canvasC = new TCanvas("canvasC",novoFicheiro,3000,700);
gStyle->SetOptStat(0);
canvasC->Divide(4,0,0,0);

TString branchXC;
TString branchYC; 
	
/*Neste for iremos selecionar as particulas carregadas, a cada iteração iremos fazer um histograma para um detetor, para isto temos de selecionar as branchs hitPosX_cm e hitPosY_cm, a branch detectorID que será utilizada para localizar o detetor dos hits e a branch particleCharge irá definir a carga da particula em que se for diferente a 0 é neutra, ou seja é carregada */
for(Int_t i = 0; i < nHistos; i++){
	
	TString HistNome = "HistogramaCarregadas" + TString::Itoa(i+1, 10);
	histoC[i] = new TH2D(HistNome, HistNome, nBins, minBin, maxBin, nBins, minBin, maxBin);
	branchXC = "hitPosX_cm";
    branchYC = "hitPosY_cm";
    canvasC->cd(i+1);
	dados->Draw(branchXC +":" + branchYC + ">>" + HistNome, "detectorID=="+ TString::Itoa(i, 10) + " && particleCharge != 0","colz"); //Selecção das branches assim como as condições de pertencer ao detetor e ser uma particula carregada 
    histoC[i]->SetTitle(HistNome);
    histoC[i]->GetXaxis()->SetTitle("X");
    histoC[i]->GetYaxis()->SetTitle("Y");
    ficheiroGravar->cd();
    histoC[i]->Write();

	}

ficheiro->Close();
ficheiroGravar->Close();
    	
}
