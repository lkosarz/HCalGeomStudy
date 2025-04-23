#include <TFile.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TSystem.h>
#include "style.C"

/// Macro for calculating Sampling fraction and e & h response
/// for different particles with different momentum in the HCal
/// this file is taken from https://github.com/OSUNuclearPhysics/ePIC_preTDR_nHCal_eh-ratio/blob/main/ebyh_ana.C
/// Please see the README file for more detaiiled information



double Energy(double momentum, TString filename) {
  double mass = 0.000511; // GeV
  if (filename.Contains("#pi^{-}")) {
    mass = 0.139570; // GeV
  }
  if (filename.Contains("neutron")) {
    mass = 0.939565; // GeV
  }
  ////cout << "mass = " << mass << endl;
  double energy = sqrt(pow(momentum, 2) + pow(mass, 2));
  ////cout << "energy = " << energy << endl;
  return energy;
}

void ebyh_ana(TString particlename, TString dir_path) {
  // Open the directory containing the root files
  ////TString dir_path = "Hcal_only";
  ////TString dir_path = "Whole_Geometry";
  style();
  TSystemDirectory dir("dir", dir_path);
  
  TList *files = dir.GetListOfFiles();
  files->Sort();

  // Create a canvas to plot the TH1Ds
  TCanvas *c_hitsumdist = new TCanvas("c_hitsumdist", "c_hitsumdist", 800, 600);
  ///c->Divide(2, 2);
  
  double x1 = 0.7;
  double y1 = 0.7;
  double x2 = 0.9;
  double y2 = 0.9;

  TLegend *legend = new TLegend(x1, y1, x2, y2);
  //legend->SetTextSize(2.0);
  
  TGraphErrors *MeanEvsp = new TGraphErrors();
  MeanEvsp->SetName("MeanEvsp");
  TGraphErrors *SampFvsp = new TGraphErrors();
  SampFvsp->SetName("SampFvsp");

  TH1D *h = new TH1D(); 

  
  
   
  // Loop over all files in the directory
  for (int i = 0; i < files->GetEntries(); i++) {
    TString filename = files->At(i)->GetName();
    if (!filename.EndsWith(".root")) continue;

    /// change the names of the files in alphabetic order with the particle name
    /// increasing momentum (aoutput_e-_1GeV_hcal_only.root, boutput_e-_2GeV_hcal_only.root, 
    /// aoutput_pi-_1GeV_hcal_only.root, boutput_pi-_2GeV_hcal_only.root, etc.)

    if (!filename.Contains(particlename)) continue;

    cout << "Processing " << filename << "   " << i << endl;

    // Open the root file
    TFile *file = TFile::Open(dir_path + "/" + filename);

    // Get the TH1D with the desired name
    h = (TH1D*)file->Get("h_nHCal_hit_Esum");
    h->Scale(1.0/(h->GetEntries()));
    
    /////h->GetYaxis()->SetRangeUser(0, 0.009);
    h->GetYaxis()->SetTitle("Probability Density");
    h->GetYaxis()->SetMaxDigits(3);
    
    
    filename.Remove(0, 8);

    
    filename.ReplaceAll("_hcal_only.root", "");
    /////filename.ReplaceAll(".root", "");
    filename.ReplaceAll("pi-_", "#pi^{-} ");
    filename.ReplaceAll("e-_", "e^{-} ");
    filename.ReplaceAll("neutron_", "neutron ");

    cout << filename << endl;
    legend->AddEntry(h, filename, "l");
    ////h->SetTitle(filename);
    h->Rebin(1);
    if (particlename == "neutron") h->Rebin(4);
    // Plot the TH1D on the canvas
    c_hitsumdist->cd();
    h->SetLineColor(i);
    h->GetXaxis()->SetRangeUser(0.00, 0.35);
    h->GetYaxis()->SetRangeUser(0.00, 9.0e-3);
    if (particlename == "neutron") h->GetYaxis()->SetRangeUser(0.00, 60.0e-3);

    h->SetStats(0);

    
    Int_t bin1 = h->FindFirstBinAbove(h->GetMaximum()/2, 1, h->FindBin(0.005), -1);
    Int_t bin2 = h->FindLastBinAbove(h->GetMaximum()/2, 1, h->FindBin(0.005), -1);

    
        // Find the bin with the highest bin content
    /*int maxBin = h->GetMaximumBin();
    double maxBinCenter = h->GetBinCenter(maxBin);
    cout << "Bin center of the bin with the highest bin content: " << maxBinCenter << endl;
    */
    cout << h->GetMaximum() << endl;
    cout << h->GetBinCenter(h->GetMaximumBin()) << endl;
    cout << "bin1center = " << h->GetBinCenter(bin1) << endl;
    cout << "bin2center = " << h->GetBinCenter(bin2) << endl;

    ////h->Fit("gaus", "MR", "", ((h->GetBinCenter(bin1))-0.), ((h->GetBinCenter(bin2))+0.));
    ///h->Fit("gaus");
    if (i == 10) h->SetLineColor(kBlack);
    if (i == 0) h->Draw("hist");

    else h->Draw("same");
    
    h->Fit("gaus", "", "", 0.0015, 1.0);

    
    

    TF1 *fitFunc = h->GetFunction("gaus");
    fitFunc->SetNpx(1000);
    if (fitFunc) {
        fitFunc->SetLineColor(kYellow+1);
        if (filename.Contains("#pi^{-}")) fitFunc->SetLineColor(kRed);///fitFunc->SetLineStyle(10);
        fitFunc->SetLineWidth(4); // Change the line color to red
    }
    
    if (filename.Contains("{-} 1GeV")) {
      MeanEvsp->SetPoint(i, 1, fitFunc->GetParameter(1));
      MeanEvsp->SetPointError(i, 0, fitFunc->GetParameter(2));
      SampFvsp->SetPoint(i, 1, fitFunc->GetParameter(1)/Energy(1.0, filename));
      SampFvsp->SetPointError(i, 0, fitFunc->GetParameter(2)/Energy(1.0, filename));
    cout << "*********************************************************" << endl;
    cout << "particle = " << filename << endl;
    /////cout << "Energy = " << Energy(1.0, filename) << " GeV" << endl;
    cout << "Sampling fraction = " << (fitFunc->GetParameter(1)/Energy(1.0, filename))*100  << " %" << endl;
    cout << "error = " << (fitFunc->GetParameter(2)/Energy(1.0, filename))*100  << " %" << endl;
    cout << "*********************************************************" << endl;
    }

    if (filename.Contains("{-} 2GeV")) {
      MeanEvsp->SetPoint(i, 2, fitFunc->GetParameter(1));
      MeanEvsp->SetPointError(i, 0, fitFunc->GetParameter(2));
      SampFvsp->SetPoint(i, 2, fitFunc->GetParameter(1)/Energy(2.0, filename));
      SampFvsp->SetPointError(i, 0, fitFunc->GetParameter(2)/Energy(2.0, filename));
    cout << "*********************************************************" << endl;
    cout << "particle = " << filename << endl;
    //////cout << "Energy = " << Energy(2.0, filename) << " GeV" << endl;
    cout << "Sampling fraction = " << (fitFunc->GetParameter(1)/Energy(2.0, filename))*100  << " %" << endl;
    cout << "error = " << (fitFunc->GetParameter(2)/Energy(2.0, filename))*100  << " %" << endl;
    cout << "*********************************************************" << endl;
    }

    if (filename.Contains("{-} 5GeV")) {
      MeanEvsp->SetPoint(i, 5, fitFunc->GetParameter(1));
      MeanEvsp->SetPointError(i, 0, fitFunc->GetParameter(2));
      SampFvsp->SetPoint(i, 5, fitFunc->GetParameter(1)/Energy(5.0, filename));
      SampFvsp->SetPointError(i, 0, fitFunc->GetParameter(2)/Energy(5.0, filename));
    cout << "*********************************************************" << endl;
    cout << "particle = " << filename << endl;
    //////cout << "Energy = " << Energy(5.0, filename) << " GeV" << endl;
    cout << "Sampling fraction = " << (fitFunc->GetParameter(1)/Energy(5.0, filename))*100  << " %" << endl;
    cout << "error = " << (fitFunc->GetParameter(2)/Energy(5.0, filename))*100  << " %" << endl;
    cout << "*********************************************************" << endl;

    }

    if (filename.Contains("{-} 10GeV")) {
      MeanEvsp->SetPoint(i, 10, fitFunc->GetParameter(1));
      MeanEvsp->SetPointError(i, 0, fitFunc->GetParameter(2));
      SampFvsp->SetPoint(i, 10, fitFunc->GetParameter(1)/Energy(10.0, filename));
      SampFvsp->SetPointError(i, 0, fitFunc->GetParameter(2)/Energy(10.0, filename));
    cout << "*********************************************************" << endl;
    cout << "particle = " << filename << endl;
    /////cout << "Energy = " << Energy(10.0, filename) << " GeV" << endl;
    cout << "Sampling fraction = " << (fitFunc->GetParameter(1)/Energy(10.0, filename))*100  << " %" << endl;
    cout << "error = " << (fitFunc->GetParameter(2)/Energy(10.0, filename))*100  << " %" << endl;
    cout << "*********************************************************" << endl;
    }

    if (filename.Contains("{-} 20GeV")) {
      MeanEvsp->SetPoint(i, 20, fitFunc->GetParameter(1));
      MeanEvsp->SetPointError(i, 0, fitFunc->GetParameter(2));
      SampFvsp->SetPoint(i, 20, fitFunc->GetParameter(1)/Energy(20.0, filename));
      SampFvsp->SetPointError(i, 0, fitFunc->GetParameter(2)/Energy(20.0, filename));
    cout << "*********************************************************" << endl;
    cout << "particle = " << filename << endl;
    ////cout << "Energy = " << Energy(20.0, filename) << " GeV" << endl;
    cout << "Sampling fraction = " << (fitFunc->GetParameter(1)/Energy(20.0, filename))*100  << " %" << endl;
    cout << "error = " << (fitFunc->GetParameter(2)/Energy(20.0, filename))*100  << " %" << endl;
    cout << "*********************************************************" << endl;
    }

    if (filename.Contains("{-} 0.1GeV")) {
      MeanEvsp->SetPoint(i, 0.1, fitFunc->GetParameter(1));
      MeanEvsp->SetPointError(i, 0, fitFunc->GetParameter(2));
      SampFvsp->SetPoint(i, 0.1, fitFunc->GetParameter(1)/Energy(0.1, filename));
      SampFvsp->SetPointError(i, 0, fitFunc->GetParameter(2)/Energy(0.1, filename));
    }

    if (filename.Contains("{-} 0.2GeV")) {
      MeanEvsp->SetPoint(i, 0.2, fitFunc->GetParameter(1));
      MeanEvsp->SetPointError(i, 0, fitFunc->GetParameter(2));
      SampFvsp->SetPoint(i, 0.2, fitFunc->GetParameter(1)/Energy(0.2, filename));
      SampFvsp->SetPointError(i, 0, fitFunc->GetParameter(2)/Energy(0.2, filename));
    }

    if (filename.Contains("{-} 0.5GeV")) {
      MeanEvsp->SetPoint(i, 0.5, fitFunc->GetParameter(1));
      MeanEvsp->SetPointError(i, 0, fitFunc->GetParameter(2));
      SampFvsp->SetPoint(i, 0.5, fitFunc->GetParameter(1)/Energy(0.5, filename));
      SampFvsp->SetPointError(i, 0, fitFunc->GetParameter(2)/Energy(0.5, filename));

    }

    if (filename.Contains("neutron 1GeV")) {
      MeanEvsp->SetPoint(i, 1, fitFunc->GetParameter(1));
      MeanEvsp->SetPointError(i, 0, fitFunc->GetParameter(2));
      SampFvsp->SetPoint(i, 1, fitFunc->GetParameter(1)/Energy(1.0, filename));
      SampFvsp->SetPointError(i, 0, fitFunc->GetParameter(2)/Energy(1.0, filename));
      cout << "*********************************************************" << endl;
    cout << "particle = " << filename << endl;
    ////cout << "Energy = " << Energy(1.0, filename) << " GeV" << endl;
    cout << "Sampling fraction = " << (fitFunc->GetParameter(1)/Energy(1.0, filename))*100  << " %" << endl;
    cout << "error = " << (fitFunc->GetParameter(2)/Energy(1.0, filename))*100  << " %" << endl;
    cout << "*********************************************************" << endl;
    }

    if (filename.Contains("neutron 2GeV")) {
      MeanEvsp->SetPoint(i, 2, fitFunc->GetParameter(1));
      MeanEvsp->SetPointError(i, 0, fitFunc->GetParameter(2));
      SampFvsp->SetPoint(i, 2, fitFunc->GetParameter(1)/Energy(2.0, filename));
      SampFvsp->SetPointError(i, 0, fitFunc->GetParameter(2)/Energy(2.0, filename));
      cout << "*********************************************************" << endl;
    cout << "particle = " << filename << endl;
    ////cout << "Energy = " << Energy(2.0, filename) << " GeV" << endl;
    cout << "Sampling fraction = " << (fitFunc->GetParameter(1)/Energy(2.0, filename))*100  << " %" << endl;
    cout << "error = " << (fitFunc->GetParameter(2)/Energy(2.0, filename))*100  << " %" << endl;
    cout << "*********************************************************" << endl;
    }

    if (filename.Contains("neutron 5GeV")) {
      MeanEvsp->SetPoint(i, 5, fitFunc->GetParameter(1));
      MeanEvsp->SetPointError(i, 0, fitFunc->GetParameter(2));
      SampFvsp->SetPoint(i, 5, fitFunc->GetParameter(1)/Energy(5.0, filename));
      SampFvsp->SetPointError(i, 0, fitFunc->GetParameter(2)/Energy(5.0, filename));
      cout << "*********************************************************" << endl;
    cout << "particle = " << filename << endl;
    //////cout << "Energy = " << Energy(5.0, filename) << " GeV" << endl;
    cout << "Sampling fraction = " << (fitFunc->GetParameter(1)/Energy(5.0, filename))*100  << " %" << endl;
        cout << "error = " << (fitFunc->GetParameter(2)/Energy(5.0, filename))*100  << " %" << endl;
    cout << "*********************************************************" << endl; 

    }

    if (filename.Contains("neutron 10GeV")) {
      MeanEvsp->SetPoint(i, 10, fitFunc->GetParameter(1));
      MeanEvsp->SetPointError(i, 0, fitFunc->GetParameter(2));
      SampFvsp->SetPoint(i, 10, fitFunc->GetParameter(1)/Energy(10.0, filename));
      SampFvsp->SetPointError(i, 0, fitFunc->GetParameter(2)/Energy(10.0, filename));
      cout << "*********************************************************" << endl;
    cout << "particle = " << filename << endl;
    /////cout << "Energy = " << Energy(10.0, filename) << " GeV" << endl;
    cout << "Sampling fraction = " << (fitFunc->GetParameter(1)/Energy(10.0, filename))*100  << " %" << endl;
    cout << "error = " << (fitFunc->GetParameter(2)/Energy(10.0, filename))*100  << " %" << endl;
    cout << "*********************************************************" << endl;
    }

    if (filename.Contains("neutron 20GeV")) {
      MeanEvsp->SetPoint(i, 20, fitFunc->GetParameter(1));
      MeanEvsp->SetPointError(i, 0, fitFunc->GetParameter(2));
      SampFvsp->SetPoint(i, 20, fitFunc->GetParameter(1)/Energy(20.0, filename));
      SampFvsp->SetPointError(i, 0, fitFunc->GetParameter(2)/Energy(20.0, filename));
      cout << "*********************************************************" << endl;
    cout << "particle = " << filename << endl;
    ////cout << "Energy = " << Energy(20.0, filename) << " GeV" << endl;
    cout << "Sampling fraction = " << (fitFunc->GetParameter(1)/Energy(20.0, filename))*100  << " %" << endl;
    cout << "error = " << (fitFunc->GetParameter(2)/Energy(20.0, filename))*100  << " %" << endl;
    cout << "*********************************************************" << endl;
    }
    /*
    MeanEvsp->SetPointError(0, 0, y_error);*/

    fitFunc->Draw("same");

    

    
    
    
    

    // Close the root file
    ///file->Close();
  }
  legend->Draw();


  TCanvas *c_MeanEvsp = new TCanvas("c_MeanEvsp", "c_MeanEvsp", 800, 600);
  c_MeanEvsp->cd();
  MeanEvsp->SetMarkerStyle(20);
  MeanEvsp->SetMarkerSize(1.5);
  MeanEvsp->SetMarkerColor(kRed);
  MeanEvsp->SetLineColor(kRed);
  MeanEvsp->GetXaxis()->SetTitle("p [GeV/c]");
  MeanEvsp->GetXaxis()->SetRangeUser(0.05, 25);
  MeanEvsp->GetYaxis()->SetRangeUser(0.001, 0.8); //will comeback here
  MeanEvsp->GetYaxis()->SetTitleOffset(1.2);
  MeanEvsp->GetYaxis()->SetTitle("#Sigma E_{hit} [GeV]");
  MeanEvsp->GetYaxis()->SetMaxDigits(3);

  MeanEvsp->Draw("AP");

  TCanvas *c_SampFvsp = new TCanvas("c_SampFvsp", "c_SampFvsp", 800, 600);
  c_SampFvsp->cd();
  SampFvsp->SetMarkerStyle(20);
  SampFvsp->SetMarkerSize(1.5);
  SampFvsp->SetMarkerColor(kRed);
  SampFvsp->SetLineColor(kRed);
  SampFvsp->GetXaxis()->SetTitle("p [GeV/c]");
  SampFvsp->GetXaxis()->SetRangeUser(0.05, 25);
  SampFvsp->GetYaxis()->SetRangeUser(0.001, 0.06);
  SampFvsp->GetYaxis()->SetTitleOffset(1.2);
  SampFvsp->GetYaxis()->SetTitle("Sampling Fraction (#Sigma E_{hit}/E_{gun})");
  SampFvsp->GetYaxis()->SetMaxDigits(3);

  SampFvsp->Draw("AP");

  TFile *outputFile = new TFile((particlename+dir_path+".root"), "RECREATE");
  
  c_hitsumdist->Write();
  MeanEvsp->Write();
  SampFvsp->Write();
  outputFile->Close();
  

  




}
