void Histogramas_Dep_Per_Event(TString root_file){

// ficheiro de dados
TFile *f = new TFile(root_file,"READ");

TString root_file_save = "Edep_per_event"+root_file(15,16)+".root"; // criação da string para criar ficheiros root para cada ficheiro AmberTarget

// ficheiro onde iremos gravar os histogramas
TFile *ficheiroGravar = new TFile(root_file_save,"RECREATE");

// seleção da arvore dos dados
TTree *dados = (TTree*)f->Get("edep_Per_Event");

// array dos histogramas, um histograma para cada detetor
Int_t nHistos = 4;
TH1F *histoDetetor [nHistos];

Int_t nBins=300;
Double_t minBin=0;
Double_t maxBin=400000;

// criação da stack, onde iremos agrupar os histogramas
THStack *hs = new THStack("hs","Energia depositada por evento;Energia (keV); log(ID do evento)");
TCanvas *cs = new TCanvas("Energia depositada por evento","Energia depositada por evento",10,10,700,500);
TText T; T.SetTextFont(42); T.SetTextAlign(21);

for (Int_t i = 0; i < nHistos; i++)
{
	TString graphName = "Detector " + TString::Itoa(i, 10); // construção da string para o titulo do histograma
	TString branchName = "detector" + TString::Itoa(i, 10); // contrução da string para a branch, neste caso é o detetor
	// criação do histograma, e adição deste à stack
	histoDetetor[i] = new TH1F(graphName,graphName,nBins,minBin,maxBin);
	dados->Draw(branchName + ">>" + graphName);
	histoDetetor[i]->SetLineColor(i+1);
	histoDetetor[i]->SetLineWidth(2);
	hs->Add(histoDetetor[i]);
	histoDetetor[i]->Write(); // guardar o histograma num ficheiro root
}

hs->Draw("nostack");
gPad->SetLogy();
cs->BuildLegend();

//salvar imagens dos histogramas obtidos
//cs->SaveAs("/home/marta/Desktop/TEC2_Trabalho/Graficos/alinea1/Histograma da Energia depositada por evento"+root_file(15,16)+".png");

}

