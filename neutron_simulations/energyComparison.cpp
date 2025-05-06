#include <iostream>
#include <vector>

#include "TFile.h"
#include "TString.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TLine.h"


void energyComparison() {
	std::vector<Float_t> energyValues = {1, 3, 5, 10};
	std::vector<TString> energyTitles = {"1", "3", "5", "10"};
	std::vector<TFile *> inputFiles;


	TFile *inputfile1 = new TFile("original/processed_original_5gev.root", "READ");
	TFile *inputfile2 = new TFile("hists/processed_neutron_5gev.edm4eic.root", "READ");
	inputFiles.push_back(inputfile1);
	inputFiles.push_back(inputfile2);

	std::cout << std::endl;

	std::vector<TH1D *> energyDeposition;

	for (auto &input : inputFiles) {
		energyDeposition.push_back((TH1D *)input->Get("HCal_Reco/hEnergy_HCal_Reco"));
    if (!energyDeposition.back()) {
      std::cout << "energyDeposition is null" << std::endl << std::endl;
    }
	}

	std::vector<TString> histsTitles = {"Deposited energy"};
	std::vector<TString> Xlabels = {"E [GeV]"};

	TCanvas *can = new TCanvas("can", "can", 1000, 600);
	
	can->SetLeftMargin(0.16);
	can->SetBottomMargin(0.15);
	can->Divide(1,2,0,0);
	
	TString outPdf = "pdfs/energy_comparison.pdf";
	can->SaveAs(outPdf + "[");

	TLatex *text_a = new TLatex();
	TLatex *text_b = new TLatex();

	TLine *l1 = new TLine(5.0,0.0,5.0,1300);
	TLine *l2 = new TLine(5.0,0.5,5.0,897);

	l1->SetLineColor(kGreen+2);
	l1->SetLineStyle(2);
	l1->SetLineWidth(2);

	l2->SetLineColor(kGreen+2);
	l2->SetLineStyle(2);
	l2->SetLineWidth(2);

///////////////original energy////////////////////////

	can->cd(1);
	energyDeposition[0]->Draw();
	energyDeposition[0]->Rebin(2);
	// energyDeposition[0]->SetTitle(histsTitles[0]+" "+energyTitles[j]+" GeV");
	energyDeposition[0]->SetTitle("");
	energyDeposition[0]->GetXaxis()->SetTitle(Xlabels[0]);
	energyDeposition[0]->GetYaxis()->SetTitle("Counts");

	energyDeposition[0]->GetXaxis()->SetTitleSize(0.08);
	energyDeposition[0]->GetYaxis()->SetTitleSize(0.08);
	energyDeposition[0]->GetXaxis()->CenterTitle(true);
	energyDeposition[0]->GetYaxis()->CenterTitle(true);

	energyDeposition[0]->GetXaxis()->SetLabelSize(0.08);
	energyDeposition[0]->GetYaxis()->SetLabelSize(0.08);

	energyDeposition[0]->GetYaxis()->SetTitleOffset(0.5);
	energyDeposition[0]->GetXaxis()->SetTitleOffset(1);
	energyDeposition[0]->GetYaxis()->SetRangeUser(0.1, 1300.);
	energyDeposition[0]->SetAxisRange(0.0, 14.3,"X");
	energyDeposition[0]->SetLineColor(kBlue);
	energyDeposition[0]->SetLineWidth(2);
	energyDeposition[0]->SetStats(0);
	text_a->SetNDC();
	text_a->SetTextSize(0.092);
	text_a->SetTextFont(42);
	text_a->DrawLatex(0.7, 0.85, "#splitline{5 GeV}{Original sampling fraction}");
	text_a->Draw();
	l1->Draw();

///////////////modified energy////////////////////////

	can->cd(2);
	energyDeposition[1]->Draw();
	energyDeposition[1]->Rebin(2);
	energyDeposition[1]->SetTitle("");

	energyDeposition[1]->GetXaxis()->SetTitle(Xlabels[0]);
	energyDeposition[1]->GetXaxis()->SetLabelSize(0.07);
	energyDeposition[1]->GetXaxis()->SetTitleSize(0.07);
	energyDeposition[1]->GetXaxis()->CenterTitle(true);
  energyDeposition[1]->GetXaxis()->SetTitleOffset(1);

  energyDeposition[1]->GetYaxis()->SetTitle("Counts");
	energyDeposition[1]->GetYaxis()->SetLabelSize(0.07);
	energyDeposition[1]->GetYaxis()->SetTitleSize(0.07);
  energyDeposition[1]->GetYaxis()->CenterTitle(true);
	energyDeposition[1]->GetYaxis()->SetTitleOffset(0.57);
  energyDeposition[1]->GetYaxis()->SetRangeUser(0., 899.);

	energyDeposition[1]->SetAxisRange(0.0, 14.3,"X");
	energyDeposition[1]->SetLineColor(kRed+2);
	energyDeposition[1]->SetLineWidth(2);
	energyDeposition[1]->SetStats(0);

	text_b->SetNDC();
	text_b->SetTextSize(0.08);
	text_b->SetTextFont(42);
	text_b->DrawLatex(0.7, 0.85, "#splitline{5 GeV}{Modified sampling fraction}");
	text_b->Draw();
	l2->Draw();

	can->Update();
	can->Modified();
  can->SaveAs(outPdf);
	can->SaveAs(outPdf + "]");
}
