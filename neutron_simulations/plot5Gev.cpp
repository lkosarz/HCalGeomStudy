#include "TFile.h"
#include "TString.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLatex.h"


void plot5Gev() {
  TFile *inputfile = new TFile("hists/processed_neutron_5gev.edm4eic.root", "READ");

  TH1D *phiResolution;
  TH1D *thetaResolution;

  phiResolution = (TH1D*)inputfile->Get("HCal_Reco/hPhiResolution_HCal_Reco");
  if (!phiResolution) std::cerr << "phiResolution is null" << std::endl;
  thetaResolution = (TH1D*)inputfile->Get("HCal_Reco/hThetaResolution_HCal_Reco");
  if (!thetaResolution) std::cerr << "theta is null" << std::endl;

  TCanvas *can = new TCanvas("can", "can", 1200, 600);
  can->SetLeftMargin(0.16);
  can->SetBottomMargin(0.15);
  can->Divide(2,1,0.,0.);

  TString outPdf = "pdfs/plots_5Gev.pdf";
  can->SaveAs(outPdf + "[");

  TLatex *text_phi = new TLatex();
  TLatex *text_theta = new TLatex();

  can->cd(1);
  phiResolution->Draw();
  phiResolution->Rebin(2);

  phiResolution->SetTitle("");
  phiResolution->GetXaxis()->SetTitle("#Delta#phi [#circ]");
  phiResolution->GetYaxis()->SetTitle("Counts");

  phiResolution->GetXaxis()->SetTitleSize(0.06);
  phiResolution->GetXaxis()->SetTitleOffset(1);
  phiResolution->GetXaxis()->CenterTitle(true);
  phiResolution->GetXaxis()->SetLabelSize(0.06);
  phiResolution->GetXaxis()->SetRangeUser(-5.9, 5.9);

  phiResolution->GetYaxis()->SetTitleSize(0.06);
  phiResolution->GetYaxis()->SetTitleOffset(1.5);
  phiResolution->GetYaxis()->SetLabelSize(0.06);
  phiResolution->GetYaxis()->SetRangeUser(0., 3100.);

  phiResolution->SetLineColor(kGreen+2);
  phiResolution->SetLineWidth(2);
  phiResolution->SetStats(0);
  phiResolution->Draw();

  text_phi->SetNDC();
  text_phi->SetTextSize(0.07);
  text_phi->SetTextFont(42);
  text_phi->DrawLatex(0.7, 0.85, "#splitline{5 GeV}{#phi resolution}");
  text_phi->Draw();

  can->cd(2);
  thetaResolution->Draw("Y+");
  thetaResolution->Rebin(2);
  thetaResolution->SetTitle("");

  thetaResolution->GetXaxis()->SetTitle("#Delta#theta [#circ]");
  thetaResolution->GetXaxis()->SetTitleSize(0.06);
  thetaResolution->GetXaxis()->SetTitleOffset(1);
  thetaResolution->GetXaxis()->CenterTitle(true);
  thetaResolution->GetXaxis()->SetLabelSize(0.06);
  phiResolution->GetXaxis()->SetRangeUser(-5.9, 5.9);

  thetaResolution->GetYaxis()->SetTitle("Counts");
  thetaResolution->GetYaxis()->SetTitleSize(0.06);
  thetaResolution->GetYaxis()->SetTitleOffset(1);
  thetaResolution->GetYaxis()->SetLabelSize(0.06);
  thetaResolution->GetYaxis()->SetRangeUser(0., 3100.);

  thetaResolution->SetLineColor(kBlue);
  thetaResolution->SetLineWidth(2);
  thetaResolution->SetStats(0);
  thetaResolution->Draw();

  text_theta->SetNDC();
  text_theta->SetTextSize(0.07);
  text_theta->SetTextFont(42);
  text_theta->DrawLatex(0.6, 0.85, "#splitline{5 GeV}{#theta resolution}");
  text_theta->Draw();

  can->Update();
  can->Modified();
  can->SaveAs(outPdf);
  can->SaveAs(outPdf + "]");
}
