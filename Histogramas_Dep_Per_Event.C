void Histogramas_Dep_Per_Event(TString ficheiroLido){

//Seleção de ficheiros a ler assim como escrever*
TFile *ficheiro = new TFile("AmberTarget_Run_0.root","READ");
	
TString novoFicheiro = ficheiroLido;
novoFicheiro.ReplaceAll("AmberTarget_Run_","Analise_Histogramas_Dep_Per_Event_");


TFile *ficheiroGravar = new TFile(novoFicheiro, "RECREATE");



TTree *dados = (TTree*)ficheiro->Get("edep_Per_Event"); /*Seleção da árvore edep_per_event em que iremos buscar os dados de energia depositada por evento*/


Int_t nBins=500;
Double_t minBin=0.0;
Double_t maxBin=400000;

Int_t nHistos=4;
TH1D* histoDetetor[nHistos]; //array com os histogramas


TCanvas *canvas = new TCanvas("canvas", novoFicheiro, 900, 700);
	gStyle->SetOptStat(0);
	canvas->Divide(2,2,0,0);
TString branchName;


/*Para fazer o histograma para cada detetor, a cada iteração iremos selecionar a branch do respetivo detetor, e obter os eventos do mesmo
depois desenhamos o histograma que está num array com dimensão igual ao nº de detetores*/
for (Int_t i=0;i<nHistos;i++){
	TString histoName="Histogramas_Dep_Per_Event Detector"+TString::Itoa(i,10); 
	histoDetetor[i]=new TH1D (histoName,histoName,nBins,minBin,maxBin); /*Criar histograma*/
	branchName="detector"+TString::Itoa(i,10); //Definir o nome a branch
	canvas->cd(i+1);
	dados->Draw(branchName+">>"+histoName,branchName+">0");
	histoDetetor[i]->SetTitle(histoName);
	histoDetetor[i]->SetLineColor(i+1);
	histoDetetor[i]->Write();

	}
}
