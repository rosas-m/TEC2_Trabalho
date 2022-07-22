void Histogramas_MZ_P_PS(TString ficheiroLido){

//Seleção de ficheiros a ler assim como escrever
TFile *ficheiro = new TFile("AmberTarget_Run_0.root","READ");
TString novoFicheiro=ficheiroLido;
novoFicheiro.ReplaceAll("AmberTarget_Run_","Analise_Histogramas_MZ_P_PS_");
    
TFile *ficheiroGravar = new TFile(novoFicheiro,"RECREATE");
TTree *dados = (TTree*) ficheiro->Get("tracksData");/*Seleção da árvore tracksData em que iremos buscar a branche pZ_GeV que contém a energia do momento no eixo Z, também usamos particlePDG que irá ser útil para verificar se a particula é um pião e para verificar, por fim utilizamos a branch IsPrimary para verificar se o pião é primário*/

Int_t nBinP = 215; 
Double_t minBinP = -5;
Double_t maxBinP = 220;

    
Int_t nHistos = 2;

TH1D* Histo_Pioes[nHistos]; //Array com os histogramas para o momento de Z no caso de piões primários e secundários
TCanvas *canvas = new TCanvas("canvas",novoFicheiro,900,700);
gStyle->SetOptStat(0);
canvas->Divide(2,1,0,0);

//Percorre os histogramas, o primeiro é para os piões primários, o segundo para os secundários
for(Int_t i=0; i<nHistos; i++){


	if(i==0){
   		TString HistoNome = "Pioes Primarios";
   		Histo_Pioes[i] = new TH1D(HistoNome,HistoNome,nBinP,minBinP,maxBinP); 		
   		canvas->cd(i+1);
   		dados->Draw("pZ_GeV>>" + HistoNome ,"particlePDG==211 || particlePDG==-211 && IsPrimary==1"); //Selecionamos a branch pZ_GeV que é a branch que contém a energia do momento, verificamos se a particula é um pião com a condição particlePDG == 211 ou particlePDG == -211, por fim verificamos se é primário com a condição IsPrimary == 1
   		Histo_Pioes[i]->SetLineColor(2);
   		Histo_Pioes[i]->Write();
   		gPad->SetLogy();//Selecionar a escala logaritmica

       	}
   	
   	else{
   		TString HistoNome = "Pioes Secundarios";
   		Histo_Pioes[i] = new TH1D(HistoNome,HistoNome,nBinP,minBinP,maxBinP);
   		canvas->cd(i+1);
   		dados->Draw("pZ_GeV>>" + HistoNome ,"particlePDG==211 || particlePDG==-211 && IsPrimary==0");//Selecionamos a branch pZ_GeV que é a branch que contém a energia do momento, verificamos se a particula é um pião com a condição particlePDG == 211 ou particlePDG == -211, por fim verificamos se é secundário com a condição IsPrimary == 0
   		Histo_Pioes[i]->SetLineColor(3);
   		Histo_Pioes[i]->Write();
   		gPad->SetLogy();//Selecionar a escala logaritmica


      	}
    }
		
}
