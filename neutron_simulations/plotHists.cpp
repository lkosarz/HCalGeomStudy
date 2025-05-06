#include <iostream>
#include <fstream>
#include <set>
#include <vector>

#include "TFile.h"
#include "TString.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TMath.h"
#include "TLatex.h"
#include "TLine.h"
#include "TLegend.h"
#include "TGaxis.h"
#include "TF1.h"

void plotHists() {
  std::vector<Float_t> energyValues = {1, 3, 5, 10};
  std::vector<TString> energyTitles = {"1", "3", "5", "10"};

  std::vector<TFile *> inputFiles;

  for (auto &energy : energyTitles) {
    TFile *inputfile = new TFile("hists/processed_neutron_" + energy + "gev.edm4eic.root", "READ");
    inputFiles.push_back(inputfile);
  }
  std::cout << std::endl;

  std::vector<TH1D *> phiResolution;
  std::vector<TH1D *> thetaResolution;

  for (auto &input : inputFiles) {
    phiResolution.push_back((TH1D *)input->Get("HCal_Reco/hPhiResolution_HCal_Reco"));
    if (!phiResolution.back()) std::cerr << "phiResolution is null" << std::endl;
    thetaResolution.push_back((TH1D *)input->Get("HCal_Reco/hThetaResolution_HCal_Reco"));
    if (!thetaResolution.back()) std::cerr << "theta is null" << std::endl;
  }

  std::vector<std::vector<TH1D *> > hists;

  hists.push_back(phiResolution);
  hists.push_back(thetaResolution);

  std::vector<TString> histsTitles = {"#phi resolution", "#theta resolution"};
  std::vector<TString> Xlabels = {"#Delta#phi [#circ]", "#Delta#theta [#circ]"};

  TCanvas *can = new TCanvas("can", "can", 1200, 600);

  can->cd();
  can->Divide(2, 2, 0., 0.);

  TString outPdf = "pdfs/plots.pdf";
  can->SaveAs(outPdf + "[");

  TLatex *text = new TLatex();
  text->SetNDC();
  text->SetTextSize(0.09);
  text->SetTextFont(42);

  for (unsigned int i = 0; i < hists.size(); i++)
  {
    for (unsigned int j = 0; j < hists[i].size(); j++)
    {
      hists[i][j]->GetXaxis()->CenterTitle(true);
      hists[i][j]->GetYaxis()->CenterTitle(true);
    }
  }


///////////////////////////////////// PHI RESOLUTION ///////////////////////////////////////
  for (unsigned int j = 0; j < hists[0].size(); j++) {
    can->cd(j+1);

    if (j==0 || j==1) gPad->SetTopMargin(0.05);
    if (j==2 || j==3) gPad->SetBottomMargin(0.16);
    if (j==0 || j==2) gPad->SetLeftMargin(0.13);
    if (j==1 || j==3) gPad->SetRightMargin(0.01);

    hists[0][j]->Draw();
    hists[0][j]->SetTitle("");

    if (j==2 || j==3) hists[0][j]->GetXaxis()->SetTitle(Xlabels[0]);
    if (j==0 || j==2) hists[0][j]->GetYaxis()->SetTitle("Counts");

    hists[0][j]->GetXaxis()->SetTitleOffset(0.9);
    hists[0][j]->GetYaxis()->SetTitleOffset(0.95);

    if (j==0) hists[0][j]->GetYaxis()->SetTitleOffset(0.82);
    hists[0][j]->Rebin(2);

    if (j==0 || j==1) hists[0][j]->GetYaxis()->SetRangeUser(0.1, 3100.);
    if (j==2 || j==3) hists[0][j]->GetYaxis()->SetRangeUser(-0.1, 3100.);

    if (j==0) hists[0][j]->SetLineColor(kRed+2);
    if (j==1) hists[0][j]->SetLineColor(kBlack);
    if (j==2) hists[0][j]->SetLineColor(kGreen+2);
    if (j==3) hists[0][j]->SetLineColor(kBlue+1);

    hists[0][j]->SetLineWidth(2);
    hists[0][j]->SetStats(0);

    hists[0][j]->SetAxisRange(-9.9, 9.9,"X");
    hists[0][j]->GetXaxis()->CenterTitle(true);
    hists[0][j]->GetXaxis()->SetTitleSize(0.078);
    hists[0][j]->GetYaxis()->SetTitleSize(0.07);
    hists[0][j]->GetXaxis()->SetLabelSize(0.07);
    hists[0][j]->GetYaxis()->SetLabelSize(0.07);
    
    if (j==0) hists[0][j]->GetYaxis()->SetTitleSize(0.08);
    if (j==0) hists[0][j]->GetYaxis()->SetLabelSize(0.08);

    if (j==0 || j==1) text->SetTextSize(0.1);
    if (j==2 || j==3) text->SetTextSize(0.09);
    if (j==0) text->DrawLatex(0.75, 0.75, Form("#splitline{%s}{%s GeV}", histsTitles[0].Data(), energyTitles[j].Data()));
    if (j==1) text->DrawLatex(0.72, 0.75, Form("#splitline{%s}{%s GeV}", histsTitles[0].Data(), energyTitles[j].Data()));
    if (j==2) text->DrawLatex(0.75, 0.8, Form("#splitline{%s}{%s GeV}", histsTitles[0].Data(), energyTitles[j].Data()));
    if (j==3) text->DrawLatex(0.72, 0.8, Form("#splitline{%s}{%s GeV}", histsTitles[0].Data(), energyTitles[j].Data()));

    text->Draw();
  }
  
  can->Update();
  can->Modified();
  can->SaveAs(outPdf);

///////////////////////////////////// THETA RESOLUTION ///////////////////////////////////////
  for (unsigned int j = 0; j < hists[1].size(); j++) {
    can->cd(j+1);

    if (j==0 || j==1) gPad->SetTopMargin(0.05);
    if (j==2 || j==3) gPad->SetBottomMargin(0.16);
    if (j==0 || j==2) gPad->SetLeftMargin(0.13);
    if (j==1 || j==3) gPad->SetRightMargin(0.01);

    hists[1][j]->Draw();
    hists[1][j]->SetTitle("");

    if (j==2 || j==3) hists[1][j]->GetXaxis()->SetTitle(Xlabels[1]);
    if (j==0 || j==2) hists[1][j]->GetYaxis()->SetTitle("Counts");

    hists[1][j]->GetXaxis()->SetTitleOffset(0.9);
    hists[1][j]->GetYaxis()->SetTitleOffset(0.95);

    if (j==0) hists[1][j]->GetYaxis()->SetTitleOffset(0.82);
    hists[1][j]->Rebin(2);

    if (j==0 || j==1) hists[1][j]->GetYaxis()->SetRangeUser(0.1, 3100.);
    if (j==2 || j==3) hists[1][j]->GetYaxis()->SetRangeUser(-0.1, 3100.);

    if (j==0) hists[1][j]->SetLineColor(kRed+2);
    if (j==1) hists[1][j]->SetLineColor(kBlack);
    if (j==2) hists[1][j]->SetLineColor(kGreen+2);
    if (j==3) hists[1][j]->SetLineColor(kBlue+1);

    hists[1][j]->SetLineWidth(2);
    hists[1][j]->SetStats(0);

    hists[1][j]->SetAxisRange(-5.5, 5.5,"X");
    hists[1][j]->GetXaxis()->CenterTitle(true);
    hists[1][j]->GetXaxis()->SetTitleSize(0.078);
    hists[1][j]->GetYaxis()->SetTitleSize(0.07);
    hists[1][j]->GetXaxis()->SetLabelSize(0.07);
    hists[1][j]->GetYaxis()->SetLabelSize(0.07);

    if (j==0) hists[1][j]->GetYaxis()->SetTitleSize(0.08);
    if (j==0) hists[1][j]->GetYaxis()->SetLabelSize(0.08);

    if (j==0 || j==1) text->SetTextSize(0.1);
    if (j==2 || j==3) text->SetTextSize(0.09);
    if (j==0) text->DrawLatex(0.75, 0.75, Form("#splitline{%s}{%s GeV}", histsTitles[1].Data(), energyTitles[j].Data()));
    if (j==1) text->DrawLatex(0.72, 0.75, Form("#splitline{%s}{%s GeV}", histsTitles[1].Data(), energyTitles[j].Data()));
    if (j==2) text->DrawLatex(0.75, 0.8, Form("#splitline{%s}{%s GeV}", histsTitles[1].Data(), energyTitles[j].Data()));
    if (j==3) text->DrawLatex(0.72, 0.8, Form("#splitline{%s}{%s GeV}", histsTitles[1].Data(), energyTitles[j].Data()));

    text->Draw();
  }

  can->Update();
  can->Modified();
  can->SaveAs(outPdf);
  can->SaveAs(outPdf + "]");

  //        j==0    j==1    j==2    j==3
  // i==0   phi1    phi3    phi5    phi10

  // i==1   theta1  theta3  theta5  theta10
}
