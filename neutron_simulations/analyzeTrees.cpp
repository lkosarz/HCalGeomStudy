#include "TGraphErrors.h"
#include "TF1.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TMath.h"
#include "TStyle.h"
#include "TFile.h"
#include "TTree.h"
#include "TTreeReader.h"
#include "TTreeReaderArray.h"
#include "TTreeReaderValue.h"
#include <iostream>
#include <fstream>
#include <string>
#include <regex>

#include "TH1D.h"
#include "TH2D.h"
#include "TLatex.h"

Double_t zGlobal = 395.;

Int_t getMaximumEnergyIndex(TTreeReaderArray<Float_t> &energyVector) {
  Int_t maxIndex = -1;
  Float_t maxEnergy = 0.;

  for (unsigned int i = 0; i < energyVector.GetSize(); ++i) {
    if (energyVector[i] > maxEnergy) {
      maxEnergy = energyVector[i];
      maxIndex = i;
    }
  }
  return maxIndex;
}

struct Cluster {
  Cluster(TString _type) : theta(0), phi(0), eta(0), energy(0), x(0), y(0), phiResolution(0), thetaResolution(0) { type = _type; }; //++
  Cluster() : theta(0), phi(0), eta(0), energy(0), x(0), y(0), phiResolution(0), thetaResolution(0), type("None"){}; //++

  Cluster &operator-(const Cluster &mc_position) {
    thetaResolution = (theta - mc_position.theta);
    phiResolution = (phi - mc_position.phi);

    x = zGlobal * TMath::Tan(theta) * TMath::Cos(phi);
    y = zGlobal * TMath::Tan(theta) * TMath::Sin(phi);

    Double_t xResolution = (x - mc_position.x);
    Double_t yResolution = (y - mc_position.y);

    rResolution = TMath::Sqrt(xResolution * xResolution + yResolution * yResolution);

    return *this;
  }

  void normalize() {
    if (phi > TMath::Pi())
        phi -= 2 * TMath::Pi();
    if (phi < -TMath::Pi())
        phi += 2 * TMath::Pi();

    x = zGlobal * TMath::Tan(theta) * TMath::Cos(phi);
    y = zGlobal * TMath::Tan(theta) * TMath::Sin(phi);
  }

  Double_t theta;
  Double_t phi;
  Double_t eta;
  Double_t energy;
  Double_t x;
  Double_t y;

  Double_t xVertex;
  Double_t yVertex;

  Double_t phiResolution;
  Double_t thetaResolution;
  Double_t rResolution;

  TString type;
};

Double_t getMaximum(TH1D *h1, TH1D *h2, TH1D *h3) {
  Double_t max = h1->GetMaximum();

  if (h2->GetMaximum() > max) {
    max = h2->GetMaximum();
  }
  if (h3->GetMaximum() > max) {
    max = h3->GetMaximum();
  }
  return max;
}

struct ClusterHists {
  const Double_t xrange = 10.;
  
  ClusterHists(TString _name) {
    name = _name;
    hTheta = new TH1D("hTheta_" + _name, _name + " Cluster #theta_{cluster}; #theta_{cluster} [rad]; Entries", 1000, 0., 5.);
    hPhi = new TH1D("hPhi_" + _name, _name + " Cluster #phi_{cluster}; #phi_{cluster} [rad]; Entries", 1000, -TMath::Pi(), TMath::Pi());
    hThetaResol = new TH1D("hThetaResolution_" + _name, _name + " Cluster #theta Resolution ; #Delta#theta; Entries", 1000, -xrange, xrange);
    hPhiResol = new TH1D("hPhiResolution_" + _name, _name + " Cluster #phi Resolution; #Delta#phi; Entries", 1000, -xrange, xrange);
    hRxyResol = new TH1D("hRxyResolution_" + _name, _name + " Cluster R_{XY} Resolution; #Delta R_{XY}[cm]; Entries", 1000, 0., 200.);
    hEnergy = new TH1D("hEnergy_" + _name, _name + " Cluster energy; E [GeV]; Entries", 1000, 0, 25);
    hPos = new TH2D("hPosition_" + _name, _name + " Cluster position x,y; x [mm]; y [mm]; Entries", 5000, -3000., 3000., 500, -3000., 3000.);
    hPhiEnergy = new TH2D("hPhiEnergy_" + _name, _name + " Cluster #phi vs Energy; #phi; Energy", 1000, -TMath::Pi(), TMath::Pi(), 100, 0., 10.);
    hPhiTheta = new TH2D("hPhiTheta_" + _name, _name + " Cluster #phi vs. #theta; #phi; #theta", 1000, 0., 180., 1000, 140., 180.);
    hPhiEta = new TH2D("hPhiEta_" + _name, _name + " Cluster #phi vs. #eta; #eta; #phi", 1000, -2., 0.5, 1000, 30., 60.);
  }

  void Fill(const Cluster &cluster) {
    hTheta->Fill(cluster.theta*(180./TMath::Pi()));
    hPhi->Fill(cluster.phi*(180./TMath::Pi()));
    hEnergy->Fill(cluster.energy);
    hPos->Fill(cluster.xVertex, cluster.yVertex);
    hThetaResol->Fill(cluster.thetaResolution*(180./TMath::Pi()));
    hPhiResol->Fill(cluster.phiResolution*(180./TMath::Pi()));
    hRxyResol->Fill(cluster.rResolution);
    hPhiTheta->Fill(cluster.phi*(180./TMath::Pi()), cluster.theta*(180./TMath::Pi()));
    hPhiEta->Fill(cluster.eta, cluster.phi*(180./TMath::Pi()));
  }

  void Draw(TCanvas *can, TString outPdf) {
    can->cd();
    hTheta->Draw("hist");
    can->SaveAs(outPdf);
    hPhi->Draw("hist");
    can->SaveAs(outPdf);
    hEnergy->Draw("hist");
    can->SaveAs(outPdf);
    hPos->Draw("colz");
    can->SaveAs(outPdf);
    hPhiTheta->Draw("colz");
    can->SaveAs(outPdf);
    hPhiEta->Draw("colz");
    can->SaveAs(outPdf);
  }

  void Write(TDirectory *output) {
    std::cout << "Writing histograms" << name << std::endl;

    output->cd();
    TDirectory *dir = output->mkdir(name);
    dir->cd();
    
    hTheta->Write();
    hPhi->Write();
    hThetaResol->Write();
    hPhiResol->Write();
    hRxyResol->Write();
    hEnergy->Write();
    hPos->Write();
    hPhiTheta->Write();
    hPhiEta->Write(); 
  }

  TString name;
  TH1D *hTheta;
  TH1D *hPhi;
  TH1D *hThetaResol;
  TH1D *hPhiResol;
  TH1D *hRxyResol;
  TH1D *hEnergy;
  TH2D *hPos;
  TH2D *hPhiEnergy;
  TH2D *hPhiTheta;
  TH2D *hPhiEta;
};

void analyzeTrees(TString inFileName, TString outFileName="") {
  
  if (outFileName == "") {
    TString base = inFileName;
    if (base.BeginsWith("input/")) {
      base.Remove(0, 6);
    }
    outFileName = "hists/processed_" + base;
  }

  gStyle->SetPalette(1);
  gStyle->SetOptTitle(1);
  gStyle->SetTitleOffset(.85, "X");
  gStyle->SetTitleOffset(.85, "Y");
  gStyle->SetTitleSize(.04, "X");
  gStyle->SetTitleSize(.04, "Y");
  gStyle->SetLabelSize(.04, "X");
  gStyle->SetLabelSize(.04, "Y");
  gStyle->SetHistLineWidth(2);
  gStyle->SetOptFit(1);
  gStyle->SetOptStat(0);

  TFile *file = new TFile(inFileName);             
  TTreeReader myReader("events", file);

  TTreeReaderArray<Float_t> charge(myReader, "MCParticles.charge");
  TTreeReaderArray<Double_t> vx_mc(myReader, "MCParticles.vertex.x");
  TTreeReaderArray<Double_t> vy_mc(myReader, "MCParticles.vertex.y");
  TTreeReaderArray<Double_t> vz_mc(myReader, "MCParticles.vertex.z");
  TTreeReaderArray<Float_t> px_mc(myReader, "MCParticles.momentum.x");
  TTreeReaderArray<Float_t> py_mc(myReader, "MCParticles.momentum.y");
  TTreeReaderArray<Float_t> pz_mc(myReader, "MCParticles.momentum.z");
  TTreeReaderArray<Int_t> status(myReader, "MCParticles.generatorStatus");
  TTreeReaderArray<Int_t> pdg(myReader, "MCParticles.PDG");

  TTreeReaderArray<Float_t> hcal_truth_E(myReader, "HcalEndcapNTruthClusters.energy");
  TTreeReaderArray<Float_t> hcal_truth_theta(myReader, "HcalEndcapNTruthClusters.intrinsicTheta");
  TTreeReaderArray<Float_t> hcal_truth_phi(myReader, "HcalEndcapNTruthClusters.intrinsicPhi");
  TTreeReaderArray<Float_t> hcal_truth_x(myReader, "HcalEndcapNTruthClusters.position.x");
  TTreeReaderArray<Float_t> hcal_truth_y(myReader, "HcalEndcapNTruthClusters.position.y");

  TTreeReaderArray<Float_t> hcal_reco_E(myReader, "HcalEndcapNClusters.energy");
  TTreeReaderArray<Float_t> hcal_reco_theta(myReader, "HcalEndcapNClusters.intrinsicTheta");
  TTreeReaderArray<Float_t> hcal_reco_phi(myReader, "HcalEndcapNClusters.intrinsicPhi");
  TTreeReaderArray<Float_t> hcal_reco_x(myReader, "HcalEndcapNClusters.position.x");
  TTreeReaderArray<Float_t> hcal_reco_y(myReader, "HcalEndcapNClusters.position.y");

  TCanvas *can = new TCanvas("can", "can", 1200, 1000);
  can->SetMargin(0.09, 0.1, 0.1, 0.06);

  TFile *output = new TFile(outFileName, "recreate");

  ClusterHists hcalRecoHist("HCal_Reco");
  ClusterHists hcalTruthHist("HCal_Truth");

  Int_t nEvents = myReader.GetEntries();
  std::cout << "Total Events: " << nEvents << std::endl;

  for (Int_t iEvent = 0; iEvent < nEvents; ++iEvent) {
    myReader.SetEntry(iEvent);
    if (iEvent % 10000 == 0) {
        std::cout << "Event No: " << iEvent << std::endl;
    }

    // MC Particle
    Cluster mc("mc");
    for (uint64_t iParticle = 0; iParticle < charge.GetSize(); ++iParticle) {
      if (status[iParticle] == 1) {
        Double_t p_mc = sqrt(px_mc[iParticle] * px_mc[iParticle] + py_mc[iParticle] * py_mc[iParticle] + pz_mc[iParticle] * pz_mc[iParticle]);
        Double_t pt_mc = sqrt(px_mc[iParticle] * px_mc[iParticle] + py_mc[iParticle] * py_mc[iParticle]);
        Double_t eta_mc = -1.0 * TMath::Log(TMath::Tan((TMath::ACos(pz_mc[iParticle] / p_mc)) / 2));
        Double_t theta_mc = TMath::ACos(pz_mc[iParticle] / p_mc);
        Double_t phi_mc = TMath::ATan(py_mc[iParticle] / px_mc[iParticle]);
        
        mc.eta = eta_mc;
        mc.theta = theta_mc;
        mc.phi = phi_mc;
        mc.energy = p_mc;
        mc.xVertex = vx_mc[iParticle];
        mc.yVertex = vy_mc[iParticle];

        mc.normalize();
      }
    }

    Int_t indexHClusterTruth = getMaximumEnergyIndex(hcal_truth_E);
    Int_t indexHClusterReco = getMaximumEnergyIndex(hcal_reco_E);

    Cluster hcalReco("hcalReco");
    if (indexHClusterReco >= 0) {
      hcalReco.energy = hcal_reco_E[indexHClusterReco];
      hcalReco.theta = hcal_reco_theta[indexHClusterReco];
      hcalReco.phi = hcal_reco_phi[indexHClusterReco];
      hcalReco.eta = -TMath::Log(TMath::Tan(hcal_reco_theta[indexHClusterReco]/2));
      hcalReco.xVertex = hcal_reco_x[indexHClusterReco];
      hcalReco.yVertex = hcal_reco_y[indexHClusterReco];

      hcalReco = hcalReco - mc;
      hcalReco.normalize();

      hcalRecoHist.Fill(hcalReco);
    }

    Cluster hcalTruth("hcalTruth");
    if (indexHClusterTruth >= 0) {
      hcalTruth.energy = hcal_truth_E[indexHClusterTruth];
      hcalTruth.theta = hcal_truth_theta[indexHClusterTruth];
      hcalTruth.phi = hcal_truth_phi[indexHClusterTruth];
      hcalTruth.xVertex = hcal_truth_x[indexHClusterTruth];
      hcalTruth.yVertex = hcal_truth_y[indexHClusterTruth];
      
      hcalTruth = hcalTruth - mc;
      hcalTruth.normalize();

      hcalTruthHist.Fill(hcalTruth);
    }
  }

  output->cd();
  hcalRecoHist.Write(output);
  hcalTruthHist.Write(output);
  output->Save();
  output->Close();

  delete can;
  delete file;
  delete output;
}