void Histogramas_VH_PS_EmZ(TString ficheiroLido){

//Seleção de ficheiros a ler assim como escrever
TFile *ficheiro = new TFile("AmberTarget_Run_0.root","READ");
	
TString novoFicheiro = ficheiroLido;
novoFicheiro.ReplaceAll("AmberTarget_Run_","Analise_Histogramas_VH_PS_EmZ_");
	
TFile *ficheiroGravar = new TFile(novoFicheiro,"RECREATE");
TTree *dados = (TTree*) ficheiro->Get("hadronicVertex");/*Selecionamos a árvore hadronicVertex em que iremos utilizar as branches vertexPoxZ_com para obter a posição do vertex no eixo Z, e a branch IsPrimary para diferenciar os vertex hadrónico primários dos secundários*/

	
Int_t nBins = 1100; 
Double_t minBin = -550;
Double_t maxBin = 550; 

Int_t nHistos = 2;
TH1D* Histogramas[nHistos]; //criação do array que irá guardar os histogramas do vertex hadrónico primários e secundários
TCanvas *canvas = new TCanvas("canvas",novoFicheiro,1800,700);
gStyle->SetOptStat(0);
canvas->Divide(2,1,0,0);
TString branchName;
TString canvasName;

//percorrer os histogramas, em que para i==0 desenhamos o histograma do vertex hadrónico primario e i==1 o do vertex hadrónico secundário
for(Int_t i = 0; i<nHistos;i++){

   	if(i==0){
   		TString HistoNome = "Vertex Primario";
   		Histogramas[i] = new TH1D(HistoNome,HistoNome,nBins,minBin,maxBin);
  		branchName = "vertexPosZ_cm";
   		canvas->cd(i+1);
   		dados->Draw(branchName + ">>" + HistoNome, "IsPrimary==1"); //selecionamos a branch vertexPosZ_com e filtramos os vertex hadrónico primários com a condição IsPrimary == 1
   		Histogramas[i]->Write();
   		gPad->SetLogy();
       	}
   	
   	else{
   		TString HistoNome = "Vertex Secundario";
   		Histogramas[i] = new TH1D(HistoNome,HistoNome,nBins,minBin,maxBin);
  		branchName = "vertexPosZ_cm";
   		canvas->cd(i+1);
   		dados->Draw(branchName + ">>" + HistoNome); //selecionamos a branch vertexPosZ_com
   		Histogramas[i]->Write();
   		gPad->SetLogy();

      	}

    }


}
