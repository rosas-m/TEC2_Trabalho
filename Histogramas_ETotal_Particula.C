void Histogramas_ETotal_Particula(TString root_file){

//Seleção de ficheiros a ler assim como escrever
TFile *ficheiro = new TFile("AmberTarget_Run_0.root","READ");

TString root_file_save = "Energia_Total_particula"+root_file(15,16)+".root"; // criação da string para criar ficheiros root para cada ficheiro AmberTarget

// ficheiro onde iremos gravar os histogramas
TFile *ficheiroGravar = new TFile(root_file_save,"RECREATE");

TTree *dados = (TTree*) ficheiro->Get("tracksData");/*Seleção da árvore tracksData em que iremos buscar as branches EdepDet[0:4]_keV, que contém as energias depositadas dos detetores, também usamos particlePDG que irá ser útil para verificar se a particula é um muão, pião ou outra particula*/

Int_t particlePDG;
Double_t EdepDet0_keV;
Double_t EdepDet1_keV;
Double_t EdepDet2_keV;
Double_t EdepDet3_keV;
Double_t soma;
Int_t particlePDGNew;	


dados->SetBranchStatus("*", 0); // Desativar as branches

// Ativar só as necessárias
dados->SetBranchStatus("particlePDG", 1);
dados->SetBranchStatus("EdepDet0_keV", 1);
dados->SetBranchStatus("EdepDet1_keV", 1);
dados->SetBranchStatus("EdepDet2_keV", 1);
dados->SetBranchStatus("EdepDet3_keV", 1);

	
Int_t nBins = 500; 
Double_t minBin = 0.0;
Double_t maxBinP = 100000;
Double_t maxBinM = 52000;
Double_t maxBinO = 230000;

/*Iremos adicionar atribuir endereços de variaveis as entradas das branches*/
dados->SetBranchAddress("EdepDet0_keV", &EdepDet0_keV); //energia depositada no detetor 1
dados->SetBranchAddress("EdepDet1_keV", &EdepDet1_keV); //energia depositada no detetor 2
dados->SetBranchAddress("EdepDet2_keV", &EdepDet2_keV); //energia depositada no detetor 3
dados->SetBranchAddress("EdepDet3_keV", &EdepDet3_keV); //energia depositada no detetor 4
dados->SetBranchAddress("particlePDG", &particlePDG); //ID da particula
	
TTree *newTree = new TTree("Resultados", "Resultado da soma de energias por partícula"); 
newTree->Branch("soma", &soma, "soma/D"); 
newTree->Branch("particlePDGNew", &particlePDGNew, "particlePDGNew/I");
	
	
Long64_t Nentries = dados->GetEntries(); //Obter o numero de entradas na arvore tracksData

/*Vamos percorrer as entradas*/
for(Int_t i = 0; i < Nentries; i++)
{		
	dados->GetEntry(i);
	soma = EdepDet0_keV + EdepDet1_keV + EdepDet2_keV + EdepDet3_keV; //Faz a soma das energias dos detetores
	particlePDGNew =  particlePDG;//Seleciona o ID da particula
	newTree->Fill(); //Guardamos os valores numa arvore			
}	
newTree->Write();

	
TCanvas *cs = new TCanvas("Energia total depositada", "Energia total depositada");
// A THStack irá servir para agregar os histogramas dos pioes, muoes e outras particulas no mesmo grafico
THStack *hs = new THStack("hs","Energia depositada por particulas;log(tempo(ns)); log(Energia (keV)");

//PIÕES
TH1D* histo_Pioes = new TH1D("Pioes", "Pioes", nBins, minBin, maxBinP);
newTree->Draw("soma>>Pioes", "particlePDGNew==211 || particlePDGNew==-211"); //Seleção da energia total dos piões, utilizando a condição particlePDGNew == 211 ou particlePDGNew == -211
histo_Pioes->SetLineColor(1);
hs->Add(histo_Pioes);

//MUÕES
TH1D* histo_Muoes = new TH1D("Muoes", "Muoes", nBins, minBin, maxBinM);
newTree->Draw("soma>>Muoes", "particlePDGNew==13 || particlePDGNew==-13"); //Seleção da energia total dos muões, utilizando a condição particlePDGNew == -13 ou particlePDGNew == 13
histo_Muoes->SetLineColor(2);
hs->Add(histo_Muoes);
	
//OUTRAS PARTICULAS
TH1D* histo_Outras = new TH1D("Outras Particulas", "Outras Particulas", nBins, minBin, maxBinO);
newTree->Draw("soma>>Outras Particulas", "particlePDGNew != 13 || particlePDGNew !=-13 || particlePDGNew !=211 || particlePDGNew !=-211");//Seleção da energia total das restantes particulas, utilizando as condições particlePDGNew != -13 ou particlePDGNew != 13 ou particlePDGNew != 211 ou particlePDGNew != -211, que são todas as particulas que não são muões ou piões
histo_Outras->SetLineColor(3);
hs->Add(histo_Outras);

hs->Draw("nostack");
gPad->SetLogy();
gPad->SetLogx();
cs->BuildLegend();

// Salvar os histogramas num ficheiro root
histo_Pioes->Write();
histo_Muoes->Write();
histo_Outras->Write();


}
