void Histogramas_DT_H_Detetor(TString root_file){ 

// Seleção dos ficheiro de dados
TFile *f = new TFile(root_file,"READ");

TString root_file_save = "Distribuicao_Temporal_Detetores"+root_file(15,16); // criação da string para criar ficheiros root para cada ficheiro AmberTarget

// ficheiro onde iremos gravar os histogramas
TFile *ficheiroGravar = new TFile(root_file_save,"RECREATE");

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
THStack *hs = new THStack("hs","Distribuicao temporal de Hits nos Detetores; Tempo (ns); Quantidade de Hits");
TCanvas *cs = new TCanvas("Distribuicao temporal de Hits nos Detetores","Distribuicao temporal de Hits nos Detetores",10,10,700,500);
TText T; T.SetTextFont(42); T.SetTextAlign(21);
auto legend = new TLegend(0.15,0.65,0.35,0.85);
// adição dos histogramas á stack
for (Int_t i = 0; i < nHistos;i++)
{
	histoDetetor[i]->SetFillColor(i+1);
	histoDetetor[i]->SetLineColor(i+1);
	hs->Add(histoDetetor[i]);
	legend->AddEntry(histoDetetor[i],"Detector " + TString::Itoa(i, 10),"l");
	histoDetetor[i]->Write(); // guardar os histogramas no ficheiro root
}
hs->Draw("noclear");
legend->Draw();
cs->SaveAs("/home/rosas/Desktop/TEC2_Trabalho/Graphs/Distribuicao_Temporal_Detetores"+root_file(15,16)+".png");

}
