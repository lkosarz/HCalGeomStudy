#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TGraph.h"
#include "TGraphErrors.h"

double E_MIP = 0.00075;

double energyThreshold = 0.25*E_MIP; // GeV
double timeMax = 100; // ns

// Function to process a single configuration directory
void processConfiguration(const std::string& directory,
                          std::vector<double>& efficiencies,
                          std::vector<double>& efficiency_errs,
                          std::vector<double>& energies) {
    // Iterate over all files in the directory
    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        std::string file_path = entry.path().string();
        std::string file_name = entry.path().filename().string(); // Get the file name only

        // Extract the energy from the file name
        size_t last_underscore = file_name.find_last_of('_');
        size_t dot_root = file_name.find(".root");
        if (last_underscore != std::string::npos && dot_root != std::string::npos) {
            std::string energy_str = file_name.substr(last_underscore + 1, dot_root - last_underscore - 1);
            double energy = std::stod(energy_str); // Convert to double
            energies.push_back(energy); // Add to energies vector
        } else {
            std::cerr << "Error: Could not extract energy from file name " << file_name << std::endl;
            continue;
        }

        // Open the ROOT file
        TFile* test = new TFile(file_path.c_str(), "READ");
        if (!test || test->IsZombie()) {
            std::cerr << "Error: Could not open file " << file_path << std::endl;
            continue;
        }

        // Retrieve histograms
        TH2F* hitcont_energy_vs_telap = (TH2F*)test->Get("h_nHCal_hit_contrib_energy_vs_telap");
        TH2F* hitcont_energy_vs_ttotal = (TH2F*)test->Get("h_nHCal_hit_contrib_energy_vs_time_total");

        if (!hitcont_energy_vs_telap || !hitcont_energy_vs_ttotal) {
            std::cerr << "Error: Could not retrieve histograms from file " << file_path << std::endl;
            test->Close();
            continue;
        }

        // Calculate npass and ntotal
        double npass = hitcont_energy_vs_telap->GetBinContent(hitcont_energy_vs_telap->FindBin(energyThreshold, timeMax));
        double npass_err = hitcont_energy_vs_telap->GetBinError(hitcont_energy_vs_telap->FindBin(energyThreshold, timeMax));

        double ntotal = hitcont_energy_vs_ttotal->GetBinContent(hitcont_energy_vs_ttotal->FindBin(energyThreshold, timeMax));
        double ntotal_err = hitcont_energy_vs_ttotal->GetBinError(hitcont_energy_vs_ttotal->FindBin(energyThreshold, timeMax));

        // Calculate efficiency and its error
        double efficiency = (ntotal > 0) ? npass / ntotal : 0.0;
        double efficiency_err = (npass > 0 && ntotal > 0) ? efficiency * sqrt(pow(npass_err / npass, 2) + pow(ntotal_err / ntotal, 2)) : 0.0;

        // Store results in vectors
        efficiencies.push_back(efficiency);
        efficiency_errs.push_back(efficiency_err);

        // Close the file
        test->Close();
    }
}

void SubtractTGraphErrors(TGraphErrors* graph, TGraphErrors* reference) {
    if (graph->GetN() != reference->GetN()) {
        std::cerr << "Error: Graphs have different number of points." << std::endl;
        return;
    }

    for (int i = 0; i < graph->GetN(); ++i) {
        double x, y, ex, ey;
        graph->GetPoint(i, x, y);
        ex = graph->GetErrorX(i);
        ey = graph->GetErrorY(i);

        double ref_y = reference->Eval(x);
        double ref_ey = reference->GetErrorY(i);

        graph->SetPoint(i, x, y - ref_y);
        graph->SetPointError(i, ex, sqrt(ey * ey + ref_ey * ref_ey));
    }
}

void plotResults() {
    // Directory containing all configurations
    std::string base_directory = "processed_outputs";

    std::vector<std::string> directories = {
        "processed_outputs/epic_backward_hcal_12layers",
        "processed_outputs/epic_backward_hcal_12layers_tile5x5cm",
        "processed_outputs/epic_backward_hcal_15layers",
        "processed_outputs/epic_backward_hcal_15layers_tile5x5cm",
        "processed_outputs/epic_backward_hcal_20layers_abs2cm_sci4mm",
        "processed_outputs/epic_backward_hcal_20layers_abs2cm_sci4mm_tile5x5cm",
        "processed_outputs/epic_backward_hcal_20layers_abs4cm_sci8mm",
        "processed_outputs/epic_backward_hcal_20layers_abs4cm_sci8mm_tile5x5cm",
        "processed_outputs/epic_backward_hcal_25layers_LFHCAL",
        "processed_outputs/epic_backward_hcal_25layers_LFHCAL_tile5x5cm",
        "processed_outputs/epic_backward_hcal_only",
        "processed_outputs/epic_backward_hcal_tile5x5cm",
    };

    std::vector<std::string> labels = {
        "12 layers",
        "12 layers, 5x5 cm tiles",
        "15 layers",
        "15 layers, 5x5 cm tiles",
        "20 layers, 2 cm absorber, 4 mm scintillator",
        "20 layers, 2 cm absorber, 4 mm scintillator, 5x5 cm tiles",
        "20 layers, 4 cm absorber, 8 mm scintillator",
        "20 layers, 4 cm absorber, 8 mm scintillator, 5x5 cm tiles",
        "25 layers, LFHCAL",
        "25 layers, LFHCAL, 5x5 cm tiles",
        "default",
        "default, 5x5 cm tiles",
    };

    std::map<std::string, std::vector<double>> efficiencies_map;
    std::map<std::string, std::vector<double>> efficiency_errs_map;
    std::map<std::string, std::vector<double>> energies_map;

    // Process each directory
    for (size_t i = 0; i < directories.size(); ++i) {
        const std::string& directory = directories[i];
        const std::string& label = labels[i];

        // Vectors to store results for this directory
        std::vector<double> efficiencies;
        std::vector<double> efficiency_errs;
        std::vector<double> energies;

        // Process the directory
        processConfiguration(directory, efficiencies, efficiency_errs, energies);

        // Store results in the map
        efficiencies_map[label] = efficiencies;
        efficiency_errs_map[label] = efficiency_errs;
        energies_map[label] = energies;
    }

    // now, make a bunch of TGraphErrors
    TGraphErrors* epic_backward_hcal_12layers = new TGraphErrors(energies_map["12 layers"].size(),&energies_map["12 layers"][0],&efficiencies_map["12 layers"][0],nullptr,&efficiency_errs_map["12 layers"][0]);
    TGraphErrors* epic_backward_hcal_12layers_tile5x5cm = new TGraphErrors(energies_map["12 layers, 5x5 cm tiles"].size(),&energies_map["12 layers, 5x5 cm tiles"][0],&efficiencies_map["12 layers, 5x5 cm tiles"][0],nullptr,&efficiency_errs_map["12 layers, 5x5 cm tiles"][0]);
    TGraphErrors* epic_backward_hcal_15layers = new TGraphErrors(energies_map["15 layers"].size(),&energies_map["15 layers"][0],&efficiencies_map["15 layers"][0],nullptr,&efficiency_errs_map["15 layers"][0]);
    TGraphErrors* epic_backward_hcal_15layers_tile5x5cm = new TGraphErrors(energies_map["15 layers, 5x5 cm tiles"].size(),&energies_map["15 layers, 5x5 cm tiles"][0],&efficiencies_map["15 layers, 5x5 cm tiles"][0],nullptr,&efficiency_errs_map["15 layers, 5x5 cm tiles"][0]);
    TGraphErrors* epic_backward_hcal_20layers_abs2cm_sci4mm = new TGraphErrors(energies_map["20 layers, 2 cm absorber, 4 mm scintillator"].size(),&energies_map["20 layers, 2 cm absorber, 4 mm scintillator"][0],&efficiencies_map["20 layers, 2 cm absorber, 4 mm scintillator"][0],nullptr,&efficiency_errs_map["20 layers, 2 cm absorber, 4 mm scintillator"][0]);
    TGraphErrors* epic_backward_hcal_20layers_abs2cm_sci4mm_tile5x5cm = new TGraphErrors(energies_map["20 layers, 2 cm absorber, 4 mm scintillator, 5x5 cm tiles"].size(),&energies_map["20 layers, 2 cm absorber, 4 mm scintillator, 5x5 cm tiles"][0],&efficiencies_map["20 layers, 2 cm absorber, 4 mm scintillator, 5x5 cm tiles"][0],nullptr,&efficiency_errs_map["20 layers, 2 cm absorber, 4 mm scintillator, 5x5 cm tiles"][0]);
    TGraphErrors* epic_backward_hcal_20layers_abs4cm_sci8mm = new TGraphErrors(energies_map["20 layers, 4 cm absorber, 8 mm scintillator"].size(),&energies_map["20 layers, 4 cm absorber, 8 mm scintillator"][0],&efficiencies_map["20 layers, 4 cm absorber, 8 mm scintillator"][0],nullptr,&efficiency_errs_map["20 layers, 4 cm absorber, 8 mm scintillator"][0]);
    TGraphErrors* epic_backward_hcal_20layers_abs4cm_sci8mm_tile5x5cm = new TGraphErrors(energies_map["20 layers, 4 cm absorber, 8 mm scintillator, 5x5 cm tiles"].size(),&energies_map["20 layers, 4 cm absorber, 8 mm scintillator, 5x5 cm tiles"][0],&efficiencies_map["20 layers, 4 cm absorber, 8 mm scintillator, 5x5 cm tiles"][0],nullptr,&efficiency_errs_map["20 layers, 4 cm absorber, 8 mm scintillator, 5x5 cm tiles"][0]);
    TGraphErrors* epic_backward_hcal_25layers_LFHCAL = new TGraphErrors(energies_map["25 layers, LFHCAL"].size(),&energies_map["25 layers, LFHCAL"][0],&efficiencies_map["25 layers, LFHCAL"][0],nullptr,&efficiency_errs_map["25 layers, LFHCAL"][0]);
    TGraphErrors* epic_backward_hcal_25layers_LFHCAL_tile5x5cm = new TGraphErrors(energies_map["25 layers, LFHCAL, 5x5 cm tiles"].size(),&energies_map["25 layers, LFHCAL, 5x5 cm tiles"][0],&efficiencies_map["25 layers, LFHCAL, 5x5 cm tiles"][0],nullptr,&efficiency_errs_map["25 layers, LFHCAL, 5x5 cm tiles"][0]);
    TGraphErrors* epic_backward_hcal_only = new TGraphErrors(energies_map["default"].size(),&energies_map["default"][0],&efficiencies_map["default"][0],nullptr,&efficiency_errs_map["default"][0]);
    TGraphErrors* epic_backward_hcal_tile5x5cm = new TGraphErrors(energies_map["default, 5x5 cm tiles"].size(),&energies_map["default, 5x5 cm tiles"][0],&efficiencies_map["default, 5x5 cm tiles"][0],nullptr,&efficiency_errs_map["default, 5x5 cm tiles"][0]);

    // set colors and styles
    std::vector<int> plotColors = {
        kPink-3, kAzure-7, kOrange+7, kGreen+1, kBlue+2, kViolet, kGray+3, kAzure+7, kYellow-4, kCyan-3, kMagenta-9, kRed, kTeal-8, kOrange+10, kRed-6, kPink+1, kGreen-6, kViolet-6, kAzure-6, kOrange-6, kRed-6
    };

    std::vector<int> markerStyles = {20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};

    epic_backward_hcal_12layers->SetMarkerColor(plotColors[0]);
    epic_backward_hcal_12layers->SetLineColor(plotColors[0]);
    epic_backward_hcal_12layers->SetMarkerStyle(markerStyles[0]);

    epic_backward_hcal_12layers_tile5x5cm->SetMarkerColor(plotColors[1]);
    epic_backward_hcal_12layers_tile5x5cm->SetLineColor(plotColors[1]);
    epic_backward_hcal_12layers_tile5x5cm->SetMarkerStyle(markerStyles[1]);

    epic_backward_hcal_15layers->SetMarkerColor(plotColors[2]);
    epic_backward_hcal_15layers->SetLineColor(plotColors[2]);
    epic_backward_hcal_15layers->SetMarkerStyle(markerStyles[2]);

    epic_backward_hcal_15layers_tile5x5cm->SetMarkerColor(plotColors[3]);
    epic_backward_hcal_15layers_tile5x5cm->SetLineColor(plotColors[3]);
    epic_backward_hcal_15layers_tile5x5cm->SetMarkerStyle(markerStyles[3]);

    epic_backward_hcal_20layers_abs2cm_sci4mm->SetMarkerColor(plotColors[4]);
    epic_backward_hcal_20layers_abs2cm_sci4mm->SetLineColor(plotColors[4]);
    epic_backward_hcal_20layers_abs2cm_sci4mm->SetMarkerStyle(markerStyles[4]);

    epic_backward_hcal_20layers_abs2cm_sci4mm_tile5x5cm->SetMarkerColor(plotColors[5]);
    epic_backward_hcal_20layers_abs2cm_sci4mm_tile5x5cm->SetLineColor(plotColors[5]);
    epic_backward_hcal_20layers_abs2cm_sci4mm_tile5x5cm->SetMarkerStyle(markerStyles[5]);

    epic_backward_hcal_20layers_abs4cm_sci8mm->SetMarkerColor(plotColors[6]);
    epic_backward_hcal_20layers_abs4cm_sci8mm->SetLineColor(plotColors[6]);
    epic_backward_hcal_20layers_abs4cm_sci8mm->SetMarkerStyle(markerStyles[6]);

    epic_backward_hcal_20layers_abs4cm_sci8mm_tile5x5cm->SetMarkerColor(plotColors[7]);
    epic_backward_hcal_20layers_abs4cm_sci8mm_tile5x5cm->SetLineColor(plotColors[7]);
    epic_backward_hcal_20layers_abs4cm_sci8mm_tile5x5cm->SetMarkerStyle(markerStyles[7]);

    epic_backward_hcal_25layers_LFHCAL->SetMarkerColor(plotColors[8]);
    epic_backward_hcal_25layers_LFHCAL->SetLineColor(plotColors[8]);
    epic_backward_hcal_25layers_LFHCAL->SetMarkerStyle(markerStyles[8]);

    epic_backward_hcal_25layers_LFHCAL_tile5x5cm->SetMarkerColor(plotColors[9]);
    epic_backward_hcal_25layers_LFHCAL_tile5x5cm->SetLineColor(plotColors[9]);
    epic_backward_hcal_25layers_LFHCAL_tile5x5cm->SetMarkerStyle(markerStyles[9]);

    epic_backward_hcal_only->SetMarkerColor(plotColors[10]);
    epic_backward_hcal_only->SetLineColor(plotColors[10]);
    epic_backward_hcal_only->SetMarkerStyle(markerStyles[10]);
    epic_backward_hcal_tile5x5cm->SetMarkerColor(plotColors[11]);

    epic_backward_hcal_tile5x5cm->SetLineColor(plotColors[11]);
    epic_backward_hcal_tile5x5cm->SetMarkerStyle(20);
    epic_backward_hcal_tile5x5cm->SetMarkerStyle(markerStyles[11]);

    // make the plot
    TCanvas* c1 = new TCanvas("c1", "Efficiency vs Energy", 1200, 600);

    // Manually create two pads with custom widths
    TPad* leftPad = new TPad("leftPad", "Plot", 0.0, 0.0, 0.55, 1.0);  // Left pad: 70% of the width
    TPad* rightPad = new TPad("rightPad", "Legend", 0.55, 0.0, 1.0, 1.0); // Right pad: 30% of the width

    leftPad->SetRightMargin(0.01);
    rightPad->SetLeftMargin(0.01);

    // Add the pads to the canvas
    leftPad->Draw();
    rightPad->Draw();

    // Draw the plot on the left pad
    leftPad->cd();
    // leftPad->SetLogx();
    epic_backward_hcal_12layers->SetTitle(";Energy (GeV);Efficiency");
    epic_backward_hcal_12layers->GetXaxis()->SetRangeUser(0.1, 5.5);
    epic_backward_hcal_12layers->GetYaxis()->SetRangeUser(0.0, 1.1);
    epic_backward_hcal_only->SetTitle(";Energy (GeV);Efficiency");
    epic_backward_hcal_only->GetXaxis()->SetRangeUser(0.1, 5.5);
    epic_backward_hcal_only->GetYaxis()->SetRangeUser(0.0, 1.1);
    epic_backward_hcal_20layers_abs2cm_sci4mm->SetTitle(";Energy (GeV);Efficiency");
    epic_backward_hcal_20layers_abs2cm_sci4mm->GetXaxis()->SetRangeUser(0.1, 5.5);
    epic_backward_hcal_20layers_abs2cm_sci4mm->GetYaxis()->SetRangeUser(0.0, 1.1);

    epic_backward_hcal_12layers->Draw("AP");
    epic_backward_hcal_12layers_tile5x5cm->Draw("P");
    epic_backward_hcal_15layers->Draw("P");
    epic_backward_hcal_15layers_tile5x5cm->Draw("P");
    epic_backward_hcal_20layers_abs2cm_sci4mm->Draw("P");
    epic_backward_hcal_20layers_abs2cm_sci4mm_tile5x5cm->Draw("P");
    epic_backward_hcal_20layers_abs4cm_sci8mm->Draw("P");
    epic_backward_hcal_20layers_abs4cm_sci8mm_tile5x5cm->Draw("P");
    epic_backward_hcal_25layers_LFHCAL->Draw("P");
    epic_backward_hcal_25layers_LFHCAL_tile5x5cm->Draw("P");
    epic_backward_hcal_only->Draw("P");
    epic_backward_hcal_tile5x5cm->Draw("P");

    // Draw the legend on the right pad
    rightPad->cd();
    TLegend* legend = new TLegend(0.0, 0.1, 0.9, 0.9);
    legend->SetTextSize(0.04);
    legend->SetMargin(0.1);
    legend->AddEntry(epic_backward_hcal_only, "10 layers, 4 cm abs., 4 mm sci., 10x10 cm tiles", "p");
    legend->AddEntry(epic_backward_hcal_tile5x5cm, "10 layers, 4 cm abs., 4 mm sci., 5x5 cm tiles", "p");
    legend->AddEntry(epic_backward_hcal_12layers, "12 layers, 4 cm abs., 4 mm sci., 10x10 cm tiles", "p");
    legend->AddEntry(epic_backward_hcal_12layers_tile5x5cm, "12 layers, 4 cm abs., 4 mm sci., 5x5 cm tiles", "p");
    legend->AddEntry(epic_backward_hcal_15layers, "15 layers, 4 cm abs., 4 mm sci., 10x10 cm tiles", "p");
    legend->AddEntry(epic_backward_hcal_15layers_tile5x5cm, "15 layers, 4 cm abs., 4 mm sci., 5x5 cm tiles", "p");
    legend->AddEntry(epic_backward_hcal_20layers_abs2cm_sci4mm, "20 layers, 2 cm abs., 4 mm sci., 10x10 cm tiles", "p");
    legend->AddEntry(epic_backward_hcal_20layers_abs2cm_sci4mm_tile5x5cm, "20 layers, 2 cm abs., 4 mm sci., 5x5 cm tiles", "p");
    legend->AddEntry(epic_backward_hcal_20layers_abs4cm_sci8mm, "20 layers, 2 cm abs., 8 mm sci., 10x10 cm tiles", "p");
    legend->AddEntry(epic_backward_hcal_20layers_abs4cm_sci8mm_tile5x5cm, "20 layers, 2 cm abs., 8 mm sci., 5x5 cm tiles", "p");
    legend->AddEntry(epic_backward_hcal_25layers_LFHCAL, "25 layers, 1.52 cm abs., 4 mm sci., 10x10 cm tiles", "p");
    legend->AddEntry(epic_backward_hcal_25layers_LFHCAL_tile5x5cm, "25 layers,  1.52 cm abs., 4 mm sci., 5x5 cm tiles", "p");
    legend->SetBorderSize(0);
    legend->SetFillStyle(0);
    legend->Draw();

    // Save the canvas to a file
    c1->SaveAs("efficiency_vs_energy.png");
    c1->SaveAs("efficiency_vs_energy.pdf");
    c1->SaveAs("efficiency_vs_energy.svg");

    leftPad->cd();
    gPad->SetLogx();

    c1->SaveAs("efficiency_vs_energy_logx.png");
    c1->SaveAs("efficiency_vs_energy_logx.pdf");
    c1->SaveAs("efficiency_vs_energy_logx.svg");

    TGraphErrors* pull_12layers = (TGraphErrors*)epic_backward_hcal_12layers->Clone("pull_12layers");
    TGraphErrors* pull_12layers_tile5x5cm = (TGraphErrors*)epic_backward_hcal_12layers_tile5x5cm->Clone("pull_12layers_tile5x5cm");
    TGraphErrors* pull_15layers = (TGraphErrors*)epic_backward_hcal_15layers->Clone("pull_15layers");
    TGraphErrors* pull_15layers_tile5x5cm = (TGraphErrors*)epic_backward_hcal_15layers_tile5x5cm->Clone("pull_15layers_tile5x5cm");
    TGraphErrors* pull_20layers_abs2cm_sci4mm = (TGraphErrors*)epic_backward_hcal_20layers_abs2cm_sci4mm->Clone("pull_20layers_abs2cm_sci4mm");
    TGraphErrors* pull_20layers_abs2cm_sci4mm_tile5x5cm = (TGraphErrors*)epic_backward_hcal_20layers_abs2cm_sci4mm_tile5x5cm->Clone("pull_20layers_abs2cm_sci4mm_tile5x5cm");
    TGraphErrors* pull_20layers_abs4cm_sci8mm = (TGraphErrors*)epic_backward_hcal_20layers_abs4cm_sci8mm->Clone("pull_20layers_abs4cm_sci8mm");
    TGraphErrors* pull_20layers_abs4cm_sci8mm_tile5x5cm = (TGraphErrors*)epic_backward_hcal_20layers_abs4cm_sci8mm_tile5x5cm->Clone("pull_20layers_abs4cm_sci8mm_tile5x5cm");
    TGraphErrors* pull_25layers_LFHCAL = (TGraphErrors*)epic_backward_hcal_25layers_LFHCAL->Clone("pull_25layers_LFHCAL");
    TGraphErrors* pull_25layers_LFHCAL_tile5x5cm = (TGraphErrors*)epic_backward_hcal_25layers_LFHCAL_tile5x5cm->Clone("pull_25layers_LFHCAL_tile5x5cm");
    TGraphErrors* pull_hcal_only = (TGraphErrors*)epic_backward_hcal_only->Clone("pull_hcal_only");
    TGraphErrors* pull_hcal_tile5x5cm = (TGraphErrors*)epic_backward_hcal_tile5x5cm->Clone("pull_hcal_tile5x5cm");

    SubtractTGraphErrors(pull_12layers, epic_backward_hcal_only);
    SubtractTGraphErrors(pull_12layers_tile5x5cm, epic_backward_hcal_tile5x5cm);
    SubtractTGraphErrors(pull_15layers, epic_backward_hcal_only);
    SubtractTGraphErrors(pull_15layers_tile5x5cm, epic_backward_hcal_tile5x5cm);
    SubtractTGraphErrors(pull_20layers_abs2cm_sci4mm, epic_backward_hcal_only);
    SubtractTGraphErrors(pull_20layers_abs2cm_sci4mm_tile5x5cm, epic_backward_hcal_tile5x5cm);
    SubtractTGraphErrors(pull_20layers_abs4cm_sci8mm, epic_backward_hcal_only);
    SubtractTGraphErrors(pull_20layers_abs4cm_sci8mm_tile5x5cm, epic_backward_hcal_tile5x5cm);
    SubtractTGraphErrors(pull_25layers_LFHCAL, epic_backward_hcal_only);
    SubtractTGraphErrors(pull_25layers_LFHCAL_tile5x5cm, epic_backward_hcal_only);
    SubtractTGraphErrors(pull_hcal_only, epic_backward_hcal_only);
    SubtractTGraphErrors(pull_hcal_tile5x5cm, epic_backward_hcal_only);

    auto* l = new TLine(0.1, 0, 5.5, 0);
    l->SetLineColor(kBlack);
    l->SetLineStyle(kDashed);
    l->SetLineWidth(2);

    TCanvas* c2 = new TCanvas("c2", "Pulls", 1200, 600);

    // Manually create two pads with custom widths
    leftPad = new TPad("leftPad", "Plot", 0.0, 0.0, 0.55, 1.0);  // Left pad: 70% of the width
    rightPad = new TPad("rightPad", "Legend", 0.55, 0.0, 1.0, 1.0); // Right pad: 30% of the width

    leftPad->SetRightMargin(0.01);
    leftPad->SetLeftMargin(0.15);
    rightPad->SetLeftMargin(0.01);

    // Add the pads to the canvas
    leftPad->Draw();
    rightPad->Draw();

    leftPad->cd();
    gPad->SetLogx();

    pull_12layers->SetLineColor(plotColors[0]);
    pull_12layers_tile5x5cm->SetLineColor(plotColors[1]);
    pull_15layers->SetLineColor(plotColors[2]);
    pull_15layers_tile5x5cm->SetLineColor(plotColors[3]);
    pull_20layers_abs2cm_sci4mm->SetLineColor(plotColors[4]);
    pull_20layers_abs2cm_sci4mm_tile5x5cm->SetLineColor(plotColors[5]);
    pull_20layers_abs4cm_sci8mm->SetLineColor(plotColors[6]);
    pull_20layers_abs4cm_sci8mm_tile5x5cm->SetLineColor(plotColors[7]);
    pull_25layers_LFHCAL->SetLineColor(plotColors[8]);
    pull_25layers_LFHCAL_tile5x5cm->SetLineColor(plotColors[9]);
    pull_hcal_only->SetLineColor(plotColors[10]);
    pull_hcal_tile5x5cm->SetLineColor(plotColors[11]);

    pull_12layers->SetTitle("Difference from Default Configuration;Energy (GeV); #varepsilon - #varepsilon_{default}");
    pull_12layers->GetXaxis()->SetRangeUser(0.1, 5.5);
    pull_12layers->GetYaxis()->SetRangeUser(-0.05, 0.1);
    pull_hcal_tile5x5cm->SetTitle("Difference from Default Configuration;Energy (GeV); #varepsilon - #varepsilon_{default}");
    pull_hcal_tile5x5cm->GetXaxis()->SetRangeUser(0.1, 5.5);
    pull_hcal_tile5x5cm->GetYaxis()->SetRangeUser(-0.05, 0.05);
    pull_20layers_abs2cm_sci4mm->SetTitle("Difference from Default Configuration;Energy (GeV); #varepsilon - #varepsilon_{default}");
    pull_20layers_abs2cm_sci4mm->GetXaxis()->SetRangeUser(0.1, 5.5);
    pull_20layers_abs2cm_sci4mm->GetYaxis()->SetRangeUser(-0.05, 0.45);

    // pull_12layers->Draw("AP");
    // pull_12layers_tile5x5cm->Draw("P");
    // pull_15layers->Draw("P");
    // pull_15layers_tile5x5cm->Draw("P");
    pull_20layers_abs2cm_sci4mm->Draw("AP");
    // pull_20layers_abs2cm_sci4mm_tile5x5cm->Draw("P");
    pull_20layers_abs4cm_sci8mm->Draw("P");
    // pull_20layers_abs4cm_sci8mm_tile5x5cm->Draw("P");
    // pull_25layers_LFHCAL->Draw("P");
    // pull_25layers_LFHCAL_tile5x5cm->Draw("P");
    // pull_hcal_only->Draw("AP");
    // pull_hcal_tile5x5cm->Draw("P");

    l->Draw("same");

    // Draw the legend on the right pad
    rightPad->cd();

    TLegend* pull_legend = new TLegend(0.0, 0.1, 0.9, 0.9);
    pull_legend->SetTextSize(0.04);
    pull_legend->SetMargin(0.1);
    // pull_legend->AddEntry(pull_hcal_only, "10 layers, 4 cm abs., 4 mm sci., 10x10 cm tiles", "p");
    // pull_legend->AddEntry(pull_hcal_tile5x5cm, "10 layers, 4 cm abs., 4 mm sci., 5x5 cm tiles", "p");
    // pull_legend->AddEntry(pull_12layers, "12 layers, 4 cm abs., 4 mm sci., 10x10 cm tiles", "p");
    // pull_legend->AddEntry(pull_12layers_tile5x5cm, "12 layers, 4 cm abs., 4 mm sci., 5x5 cm tiles", "p");
    // pull_legend->AddEntry(pull_15layers, "15 layers, 4 cm abs., 4 mm sci., 10x10 cm tiles", "p");
    // pull_legend->AddEntry(pull_15layers_tile5x5cm, "15 layers, 4 cm abs., 4 mm sci., 5x5 cm tiles", "p");
    pull_legend->AddEntry(pull_20layers_abs2cm_sci4mm, "20 layers, 2 cm abs., 4 mm sci., 10x10 cm tiles", "p");
    // pull_legend->AddEntry(pull_20layers_abs2cm_sci4mm_tile5x5cm, "20 layers, 2 cm abs., 4 mm sci., 5x5 cm tiles", "p");
    pull_legend->AddEntry(pull_20layers_abs4cm_sci8mm, "20 layers, 2 cm abs., 8 mm sci., 10x10 cm tiles", "p");
    // pull_legend->AddEntry(pull_20layers_abs4cm_sci8mm_tile5x5cm, "20 layers, 2 cm abs., 8 mm sci., 5x5 cm tiles", "p");
    // pull_legend->AddEntry(pull_25layers_LFHCAL, "25 layers, 1.52 cm abs., 4 mm sci., 10x10 cm tiles", "p");
    // pull_legend->AddEntry(pull_25layers_LFHCAL_tile5x5cm, "25 layers,  1.52 cm abs., 4 mm sci., 5x5 cm tiles", "p");
    pull_legend->SetBorderSize(0);
    pull_legend->SetFillStyle(0);
    pull_legend->Draw();

    // Save the canvas to a file
    c2->SaveAs("pulls_vs_energy.png");
    c2->SaveAs("pulls_vs_energy.pdf");
    c2->SaveAs("pulls_vs_energy.svg");
}
