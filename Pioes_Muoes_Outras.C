void Pioes_Muoes_Outras(TString ficheiroLido){


//Seleção de ficheiros a ler assim como escrever
TFile *ficheiro = new TFile("AmberTarget_Run_0.root","READ");
TString novoFicheiro = ficheiroLido;
novoFicheiro.ReplaceAll("AmberTarget_Run_","Analise_Pioes_Muoes_Outras_");
	
TFile *ficheiroGravar = new TFile(novoFicheiro,"RECREATE");
TTree *dados = (TTree*) ficheiro->Get("tracksData");/*Seleção da árvore tracksData em que iremos buscar a branche EdepDet[0:4]_keV que contém as energias depositadas dos detetores, também usamos particlePDG que irá ser útil para verificar se a particula é um muão ou um pião, ou nenhum destes*/


    
Int_t nBins = 100; 
Double_t minBin = 0.0;
Double_t maxBinP = 80000;
Double_t maxBinM = 18000;
Double_t maxBinO=90000;
 
        
Int_t nHistos = 4;

//PIÕES
TCanvas *canvasPioes = new TCanvas("canvasPioes", novoFicheiro, 900, 700);;
TH1D* histo_Pioes[nHistos];
gStyle->SetOptStat(0);
canvasPioes->Divide(2,2,0,0);

TString canvasNamePioes;
TString folhaNamePioes;


//Percorremos os histogramas em que cada histograma é de um determinado detetor, depois selecionamos o detetor, construindo a string da branch, e selecionamos os piões usando dados da particlePDG
for(Int_t i = 0; i < nHistos; i++){
	TString HistoNome = "HistoDetector" + TString::Itoa(i, 10);
	histo_Pioes[i] = new TH1D(HistoNome, HistoNome, nBins, minBin, maxBinP);
	folhaNamePioes = "EdepDet" + TString::Itoa(i, 10) + "_keV"; //Construção da string da branch da energia depositada do respetivo detetor
	canvasNamePioes = "canvasPioes_Detetor_" + TString::Itoa(i, 10);
	canvasPioes->cd(i+1);
	
	dados->Draw(folhaNamePioes + ">>" + HistoNome, "particlePDG==211 || particlePDG==-211 && " + folhaNamePioes + ">10"); // Filtramos os piões da EdepDet com as condições particlePDG == 211 ou particlePDG == -211
	histo_Pioes[i]->SetFillColor(i+1);
       	histo_Pioes[i]->Write();
        histo_Pioes[i]->SetTitle("Pioes -> Detector" + TString::Itoa(i, 10) + "; log(EdepDet0_keV)");
        gPad->SetLogy();//Escala logaritmica
        TF1 *landouFitPioes = new TF1 ("landouFitPioes", "landau", 0, 30000);
        histo_Pioes[i]->Fit("landouFitPioes");
	
	}


        
//MUÕES	
TCanvas *canvasMuoes = new TCanvas("canvasMuoes", novoFicheiro, 900, 700);
TH1D* histo_Muoes[nHistos];
gStyle->SetOptStat(0);
canvasMuoes->Divide(2,2,0,0);

TString canvasNameMuoes;
TString folhaNameMuoes;
	
	
for(Int_t i = 0; i < nHistos; i++){
	
	TString HistoNome = "HistoDetector" + TString::Itoa(i, 10);
	histo_Muoes[i] = new TH1D(HistoNome, HistoNome, nBins, minBin, maxBinM);
	folhaNameMuoes = "EdepDet" + TString::Itoa(i, 10) + "_keV";//Construção da string da branch da energia depositada do respetivo detetor
	canvasNameMuoes = "canvasMuoes_Detetor_" + TString::Itoa(i, 10);
	canvasMuoes->cd(i+1);
	
	dados->Draw(folhaNameMuoes + ">>" + HistoNome, "particlePDG==13 || particlePDG==-13 && "+folhaNameMuoes+">10");// Filtramos os muões da EdepDet com as condições particlePDG == 13 ou particlePDG == -13
	histo_Muoes[i]->SetFillColor(i+1);
    	histo_Muoes[i]->Write();
    	histo_Muoes[i]->SetTitle("Muoes -> Detetor" + TString::Itoa(i, 10) + "; log(EdepDet0_keV)");
    	gPad->SetLogy();//Escala logaritmica
        TF1 *landouFitMuoes = new TF1 ("landouFitMuoes", "landau", 0, 30000);
       	histo_Muoes[i]->Fit("landouFitMuoes");
	}



//OUTRAS PARTICULAS  
TCanvas *canvasOutras = new TCanvas("canvasOutras", novoFicheiro, 900, 700); 
TH1D* histo_Outras[nHistos];
gStyle->SetOptStat(0);
canvasOutras->Divide(2,2,0,0);

TString canvasNameOutras;
TString folhaNameOutras;



for(Int_t i = 0; i < nHistos; i++){
	
	TString HistoNome = "HistoDetector" + TString::Itoa(i, 10);
	histo_Outras[i] = new TH1D(HistoNome, HistoNome, nBins, minBin, maxBinO);
	folhaNameOutras= "EdepDet" + TString::Itoa(i, 10) + "_keV";//Construção da string da branch da energia depositada do respetivo detetor
	canvasNameOutras = "canvasOutras_Detetor_" + TString::Itoa(i, 10);
	canvasOutras->cd(i+1);
	
	dados->Draw(folhaNameOutras + ">>" + HistoNome, "particlePDG!=13 || particlePDG!=-13 || particlePDG!=211 || particlePDG!=-211");// Filtramos as restantes particulas da EdepDet com as condições de não serem nem muões nem piões
	histo_Outras[i]->SetFillColor(i+1);
       	histo_Outras[i]->Write();
        histo_Outras[i]->SetTitle("Outras -> Detetor" + TString::Itoa(i, 10) + "; log(EdepDet0_keV)");
        gPad->SetLogy();//Escala logaritmica
        //TF1 *landouFiOutras = new TF1 ("landouFitOutras", "landau", 0, 30000);
       	//histo_Outras[i]->Fit("landouFitOutras");
	
	
	}

		
}



