#include "TCanvas.h"
#include "TGraph.h"
#include "TAxis.h"
#include "TLine.h"

void plotEfficiency() {
  TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);
  c1->SetGrid(0,1);

  const Int_t totalSimulated = 100000;
  const Int_t numberOfEnergies = 5;

  const char* filenames[numberOfEnergies] = {
    "hists/processed_neutron_300mev.edm4eic.root",
    "hists/processed_neutron_1gev.edm4eic.root",
    "hists/processed_neutron_3gev.edm4eic.root",
    "hists/processed_neutron_5gev.edm4eic.root",
    "hists/processed_neutron_10gev.edm4eic.root"
  };

  Int_t entries[numberOfEnergies] = {};
  for (Int_t i = 0; i < numberOfEnergies; ++i) {
    TFile *file = TFile::Open(filenames[i]);
    if (!file || file->IsZombie()) {
      entries[i] = 0;
      continue;
    }

    TH1D* histogram = (TH1D*)(file->Get("HCal_Reco/hEnergy_HCal_Reco"));
    entries[i] = (histogram ? histogram->GetEntries() : 0);
    file->Close();
    delete file;
  }

  Double_t x[numberOfEnergies] = {0.3, 1, 3, 5, 10};
  Double_t y[numberOfEnergies] = {};

  for (Int_t i = 0; i < numberOfEnergies; i++) {
    y[i] = (entries[i]*1.0 / totalSimulated) * 100;
  }

  TGraph *gr = new TGraph(numberOfEnergies, x, y);
  TAxis *axis = gr->GetXaxis();
  TLine *l1 = new TLine(0, 100, 10.5, 100);
  TLine *l2 = new TLine(0., 14.5, 0., 100.5);

  gr->SetTitle(";E [GeV];Efficiency [%]");
  gr->SetMarkerColor(kBlue);
  gr->SetMarkerStyle(70);
  gr->SetMarkerSize(3.5);

  gr->GetXaxis()->SetTitleSize(0.06);
  gr->GetXaxis()->SetLabelSize(0.06);
  gr->GetYaxis()->SetLabelSize(0.06);
  gr->GetYaxis()->SetTitleSize(0.06);

  gPad->SetLeftMargin(0.13);
  gPad->SetBottomMargin(0.13);
  gPad->SetRightMargin(0.02);
  gPad->SetTopMargin(0.02);

  l1->SetLineColor(kGreen+2);
  l1->SetLineStyle(2);
  l1->SetLineWidth(2);

  l2->SetLineColor(kBlack);
  l2->SetLineStyle(2);
  l2->SetLineWidth(2);

  gr->GetYaxis()->SetTitleOffset(1.);
  gr->GetYaxis()->CenterTitle(true);
  gr->GetXaxis()->CenterTitle(true);

  gr->Draw("AP");
  l1->Draw("same");
  l2->Draw("same");

  axis->SetLimits(-0.5, 10.5);

  c1->SaveAs("pdfs/efficiency.pdf");

  delete c1;
  delete gr;
  delete l1;
  delete l2;
}
