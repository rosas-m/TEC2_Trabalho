void Histogramas_DT_H_Detetor(){ 

// Seleção dos ficheiro de dados
TFile *f = new TFile("AmberTarget_Run_1.root","READ");


// Seleção da árvore onde estão os hits temporais
TTree *dados = (TTree*)f->Get("Hits");

Int_t nHistos = 4;
TH1F *histoDetetor [nHistos];

Int_t nBins=500;
Double_t minBin=0;
Double_t maxBin=10;
Double_t particleTime;
Int_t detetorID;

// iremos "desativar" as branches, para mais tarde selecionar apenas as que precisamos por questões de otimização
dados->SetBranchStatus("*",0);
Long64_t Nentries = dados->GetEntries();


// criação dos histogramas que irão guardas os hits de cada detetor
TString detetorTitle;
detetorTitle="Detector 0";
histoDetetor[0] = new TH1F(detetorTitle,detetorTitle,nBins,minBin,maxBin);
detetorTitle="Detector 1";
histoDetetor[1] = new TH1F(detetorTitle,detetorTitle,nBins,minBin,maxBin);
detetorTitle="Detector 2";
histoDetetor[2] = new TH1F(detetorTitle,detetorTitle,nBins,minBin,maxBin);
detetorTitle="Detector 3";
histoDetetor[3] = new TH1F(detetorTitle,detetorTitle,nBins,minBin,maxBin);


// seleção das branches de dados
dados->SetBranchStatus("detectorID",1);
dados->SetBranchStatus("particleHitTime_ns",1);
dados->SetBranchAddress("detectorID",&detetorID);
dados->SetBranchAddress("particleHitTime_ns",&particleTime);

// itereção pelas entradas das branches
for (Int_t i = 0; i < Nentries; i++)
{
	dados->GetEntry(i);
	histoDetetor[detetorID]->Fill(particleTime); // com o detetorID obtemos o ID de detetor e adicionamos o tempo da particula
}
// criação da stack de histogramas para agrupar os histogramas dos detetores no mesmo grafico
THStack *hs = new THStack("hs","Hits por tempo nos Detetores; tempo (ns); Quantidade de Hits");
TCanvas *cs = new TCanvas("Hits por tempo dos detetores","Hits por tempo dos detetores",10,10,700,500);
TText T; T.SetTextFont(42); T.SetTextAlign(21);

// adição dos histogramas á stack
for (Int_t i = 0; i < nHistos;i++)
{
	histoDetetor[i]->SetFillColor(i+1);
	histoDetetor[i]->SetLineColor(i+1);
	hs->Add(histoDetetor[i]);
}
hs->Draw("noclear");
cs->BuildLegend();

}
