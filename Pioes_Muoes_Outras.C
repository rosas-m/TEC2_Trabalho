void Pioes_Muoes_Outras(){
//seleção ficheiro de dados
TFile *f = new TFile("AmberTarget_Run_1.root","READ");

// seleção da arvore dos dados
TTree *dados = (TTree*)f->Get("tracksData");

// nHistos representa o histograma dos pioes, muoes e outras particulas, que são 3.
Int_t nHistos = 3;
// temos quatro detetores
Int_t nDetetores = 4;

Int_t nBins=500;
Double_t minBin=0;
Double_t maxBin=240000;

// O Canvas vai ser dividido em 4, uma vez que temos quatro detetores 
TCanvas *cs = new TCanvas("Energia depositada de particulas nos detetores","Energia depositada de particulas nos detetores");
TText T; T.SetTextFont(42); T.SetTextAlign(21);
cs->Divide(2,2);

// o histoDetetor é uma matriz em que cada linha contém histogramas dos pioes, muoes e outras particulas de um detetor
TH1F *histoDetetor [nDetetores][nHistos];
// a stack vai servir para analisar a quantidade de particulas e a energia depositada entre muoes, pioes e outras particulas no mesmo detetor 
THStack *hs [nDetetores];


//o ciclo for vai percorrer os detetores
for (Int_t i = 0; i < nDetetores; i++){
	cs->cd(i+1);
	TString graphName = "Detector " + TString::Itoa(i, 10); // construção da string para o titulo da stack
	TString branchName = "EdepDet" + TString::Itoa(i, 10) + "_keV"; // contrução da string para a branch, que neste caso é o detetor
	hs[i] = new THStack("hs",graphName+";log(Tempo (ns));log(Energia (keV))");
	// construção das strings para os titulos dos histogramas dos pioes, muoes e outras particulas
	TString pioes = "Pioes " + TString::Itoa(i, 10);
	TString muoes = "Muoes " + TString::Itoa(i, 10);
	TString outras = "Outras " + TString::Itoa(i, 10);
	// obtenção dos dados para o detetor i, e a seleção dos pioes entre as restantes particulas utilizando a branch particlePDG
	histoDetetor[i][0] = new TH1F(pioes,pioes,nBins,minBin,maxBin);
	dados->Draw(branchName + ">>" + pioes,"particlePDG==211 || particlePDG==-211 && "+branchName+">10");
	histoDetetor[i][0]->SetLineWidth(2);
	histoDetetor[i][0]->SetLineColor(1);
	// obtenção dos dados para o detetor i, e a seleção dos muoes entre as restantes particulas utilizando a branch particlePDG
	histoDetetor[i][1] = new TH1F(muoes,muoes,nBins,minBin,maxBin);
	dados->Draw(branchName + ">>" + muoes,"particlePDG==13 || particlePDG==-13 && "+branchName+">10");
	histoDetetor[i][1]->SetLineWidth(2);
	histoDetetor[i][1]->SetLineColor(2);
	// obtenção dos dados para o detetor i, e a seleção das particulas que não são muoes nem pioes utilizando a branch particlePDG
	histoDetetor[i][2] = new TH1F(outras,outras,nBins,minBin,maxBin);
	dados->Draw(branchName + ">>" + outras,"particlePDG!=13 || particlePDG!=-13 || particlePDG!=211 || particlePDG!=-211 && "+branchName+">10");
	histoDetetor[i][2]->SetLineWidth(2);
	histoDetetor[i][2]->SetLineColor(3);
	// adicionamos os histogramas á stack
	hs[i]->Add(histoDetetor[i][2]);
	hs[i]->Add(histoDetetor[i][0]);
	hs[i]->Add(histoDetetor[i][1]);
	// legenda da stack
   	auto legend = new TLegend(0.1,0.7,0.48,0.9);
   	legend->AddEntry(histoDetetor[i][0],"Pioes","l");
   	legend->AddEntry(histoDetetor[i][1],"Muoes","l");
   	legend->AddEntry(histoDetetor[i][2],"Outras","l");
	hs[i]->Draw("nostack");
	gPad->SetLogy(); // colocar o eixo y na escala logaritmica
	gPad->SetLogx(); // colocar o eixo x na escala logaritmica
	legend->Draw();
	
}
}
