void Histogramas_VH_PS_EmZ(){

//Seleção de ficheiros a ler assim como escrever
TFile *ficheiro = new TFile("AmberTarget_Run_0.root","READ");

	
TFile *ficheiroGravar = new TFile("Vertex.root","RECREATE");
TTree *dados = (TTree*) ficheiro->Get("hadronicVertex");/*Selecionamos a árvore hadronicVertex em que iremos utilizar as branches vertexPoxZ_com para obter a posição do vertex no eixo Z, e a branch IsPrimary para diferenciar os vertex hadrónico primários dos secundários*/

	
Int_t nBins = 1100; 
Double_t minBin = -550;
Double_t maxBin = 550; 

TCanvas *cs = new TCanvas("canvas","Vertex");
Int_t nHistos = 2;
TH1D* histogramas[nHistos]; //criação do array que irá guardar os histogramas do vertex hadrónico primários e secundários


// criação dos histogramas para os vertexes primarios e secundarios
histogramas[0] = new TH1D("Vertex Primario","Vertex Primario",nBins,minBin,maxBin);
histogramas[0]->SetLineColor(1);
histogramas[1] = new TH1D("Vertex Secundario","Vertex Secundario",nBins,minBin,maxBin);
histogramas[1]->SetLineColor(2);

Double_t pos_Z;
Int_t isPrimary;
Long64_t Nentries = dados->GetEntries();
dados->SetBranchStatus("*",0);

dados->SetBranchStatus("vertexPosZ_cm",1);
dados->SetBranchStatus("IsPrimary",1);
dados->SetBranchAddress("vertexPosZ_cm",&pos_Z);
dados->SetBranchAddress("IsPrimary",&isPrimary);


// iteração pelas entradas na arvore hadronicVertex
for (Int_t i = 0; i < Nentries; i++)
{
	dados->GetEntry(i);
	if (isPrimary == 1) // se o vertex for primario adiciono-o ao histograma dos vertex primarios
	{
		histogramas[0]->Fill(pos_Z);
	}
	else //  se o vertex for secundario adiciono-o ao histograma dos vertex secundarios
	{
		histogramas[1]->Fill(pos_Z);
	}
}

// agregação dos histogramas no mesmo grafico utilizando uma THStack
THStack* hs = new THStack("hs","Hadronic Vertex;Posicao de Z (cm); Quantidade");
hs->Add(histogramas[0]);
hs->Add(histogramas[1]);

hs->Draw("nostack");
cs->BuildLegend();
}
