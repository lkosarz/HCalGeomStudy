/*
 * HistogramsSim.h
 *
 *  Created on: 23 mar 2023
 *      Author: Khaless
 */

#ifndef HISTOGRAMSSIM_H_
#define HISTOGRAMSSIM_H_

#include <TH1.h>
#include <TH1D.h>

#include <TH2.h>
#include <TH2D.h>

#include <TMath.h>

using namespace TMath;

void CreateHistogamsSim();

// Event
TH1D *h_Events;

TH1D *h_MCpart;

TH1D *h_MCpart_nPion_p;
TH1D *h_MCpart_nPion_n;
TH1D *h_MCpart_nKaon_p;
TH1D *h_MCpart_nKaon_n;
TH1D *h_MCpart_nProton_p;
TH1D *h_MCpart_nProton_n;
TH1D *h_MCpart_nElectron_p;
TH1D *h_MCpart_nElectron_n;

TH1D *h_MCpart_nNeutron;
TH1D *h_MCpart_nGamma;

TH1D *h_MCpart_nGen;
TH1D *h_MCpart_nSec;

// MC particles
TH1D *h_MCpart_mass;
TH1D *h_MCpart_charge;
TH1D *h_MCpart_E;
TH1D *h_MCpart_p;
TH1D *h_MCpart_pT;

TH1D *h_MCpart_mom_x;
TH1D *h_MCpart_mom_y;
TH1D *h_MCpart_mom_z;

TH1D *h_MCpart_eta;
TH2D *h_MCpart_etaphi;

TH2D *h_MCpart_xy;
TH2D *h_MCpart_zr;

TH1D *h_MCpart_end_p;
TH1D *h_MCpart_end_pT;

TH2D *h_MCpart_posEnd_xy;
TH2D *h_MCpart_posEnd_zr;

TH1D *h_MCpart_genStatus;

// nHCal acceptance
TH2D *h_MCpart_nHCal_etaphi;
TH2D *h_MCpart_nHCal_decayed_etaphi;

// momentum
TH1D *h_MCpart_Pion_p_p;
TH1D *h_MCpart_Pion_n_p;
TH1D *h_MCpart_Kaon_p_p;
TH1D *h_MCpart_Kaon_n_p;
TH1D *h_MCpart_Proton_p_p;
TH1D *h_MCpart_Proton_n_p;
TH1D *h_MCpart_Electron_p_p;
TH1D *h_MCpart_Electron_n_p;

TH1D *h_MCpart_Neutron_p;
TH1D *h_MCpart_Gamma_p;

// energy
TH1D *h_MCpart_Pion_p_E;
TH1D *h_MCpart_Pion_n_E;
TH1D *h_MCpart_Kaon_p_E;
TH1D *h_MCpart_Kaon_n_E;
TH1D *h_MCpart_Proton_p_E;
TH1D *h_MCpart_Proton_n_E;
TH1D *h_MCpart_Electron_p_E;
TH1D *h_MCpart_Electron_n_E;

TH1D *h_MCpart_Neutron_E;
TH1D *h_MCpart_Gamma_E;


// eta, momentum
TH2D *h_MCpart_pion_p_eta_p;
TH2D *h_MCpart_pion_n_eta_p;
TH2D *h_MCpart_Kaon_p_eta_p;
TH2D *h_MCpart_Kaon_n_eta_p;
TH2D *h_MCpart_proton_p_eta_p;
TH2D *h_MCpart_proton_n_eta_p;
TH2D *h_MCpart_Electron_p_eta_p;
TH2D *h_MCpart_Electron_n_eta_p;

TH2D *h_MCpart_Neutron_eta_p;
TH2D *h_MCpart_Gamma_eta_p;

// eta, energy
TH2D *h_MCpart_Pion_p_eta_E;
TH2D *h_MCpart_Pion_n_eta_E;
TH2D *h_MCpart_Kaon_p_eta_E;
TH2D *h_MCpart_Kaon_n_eta_E;
TH2D *h_MCpart_Proton_p_eta_E;
TH2D *h_MCpart_Proton_n_eta_E;
TH2D *h_MCpart_Electron_p_eta_E;
TH2D *h_MCpart_Electron_n_eta_E;

TH2D *h_MCpart_Neutron_eta_E;
TH2D *h_MCpart_Gamma_eta_E;

// pair projection distance
TH2D *h_MCpart_eta_deltaRxy;
TH2D *h_MCpart_Neutron_eta_deltaRxy;
TH1D *h_MCpart_eta_norm;
TH1D *h_MCpart_Neutron_eta_norm;


// Generated MC particles
TH1D *h_MCpart_gen_mass;
TH1D *h_MCpart_gen_charge;
TH1D *h_MCpart_gen_E;
TH1D *h_MCpart_gen_p;
TH1D *h_MCpart_gen_pT;

TH1D *h_MCpart_gen_eta;
TH2D *h_MCpart_gen_etaphi;

TH2D *h_MCpart_gen_xy;
TH2D *h_MCpart_gen_zr;

TH1D *h_MCpart_gen_end_p;
TH1D *h_MCpart_gen_end_pT;

TH2D *h_MCpart_gen_posEnd_xy;
TH2D *h_MCpart_gen_posEnd_zr;


// pair projection distance
TH2D *h_MCpart_gen_eta_deltaRxy;
TH2D *h_MCpart_gen_Neutron_eta_deltaRxy;
TH1D *h_MCpart_gen_eta_norm;
TH1D *h_MCpart_gen_Neutron_eta_norm;


// Secondary MC particles
TH1D *h_MCpart_sec_mass;
TH1D *h_MCpart_sec_charge;
TH1D *h_MCpart_sec_E;
TH1D *h_MCpart_sec_p;
TH1D *h_MCpart_sec_pT;

TH1D *h_MCpart_sec_eta;
TH2D *h_MCpart_sec_etaphi;

TH2D *h_MCpart_sec_xy;
TH2D *h_MCpart_sec_zr;

TH1D *h_MCpart_sec_end_p;
TH1D *h_MCpart_sec_end_pT;

TH2D *h_MCpart_sec_posEnd_xy;
TH2D *h_MCpart_sec_posEnd_zr;


// MC particles - 1st generation daughters
TH1D *h_MCpart_1stgen_daughter_mass;
TH1D *h_MCpart_1stgen_daughter_charge;
TH1D *h_MCpart_1stgen_daughter_E ;
TH1D *h_MCpart_1stgen_daughter_p;
TH1D *h_MCpart_1stgen_daughter_pT;

TH2D *h_MCpart_1stgen_daughter_etaphi;
TH1D *h_MCpart_1stgen_daughter_eta;

TH2D *h_MCpart_1stgen_daughter_xy;
TH2D *h_MCpart_1stgen_daughter_zr;

TH1D *h_MCpart_1stgen_daughter_end_p;
TH1D *h_MCpart_1stgen_daughter_end_pT;

TH2D *h_MCpart_1stgen_daughter_posEnd_xy;
TH2D *h_MCpart_1stgen_daughter_posEnd_zr;




// EcalEndcapNHit
TH1D *h_nECal_hit_E;
TH1D *h_nECal_hit_Esum;

TH1D *h_nECal_nhits;

// HcalEndcapNHit

TH1D *h_nHCal_hit_E;
TH1D *h_nHCal_hit_Ecorr;
TH1D *h_nHCal_hit_Esum;
TH1D *h_nHCal_hit_EsumCorr;
TH1D *h_nCal_hit_delE_perevent;

TH1D *h_nHCal_nhits;

TH1D *h_nHCal_hit_pos_x;
TH1D *h_nHCal_hit_pos_y;
TH1D *h_nHCal_hit_pos_z;
TH2D *h_nHCal_hit_pos_xy;

TH2D *h_nHCal_hit_pos_rE;

TH2D *h_nHCal_hit_etaphi;

TH3F *h_nHCal_hit_etaphi_Esum;
TH3F *h_nHCal_hit_Rphi_Esum;

// nCals
TH1D *h_nCal_hits_Esum;


void CreateHistogamsSim()
{

	// Event
	h_Events = new TH1D("h_Events", "Number of events; events; counts", 10, 0.0, 10.0);

	h_MCpart = new TH1D("h_MCpart", "Number of MC particles; N_{MC} [1]; counts", 2001, -0.5, 2000.5);

	h_MCpart_nPion_p = new TH1D("h_MCpart_nPion_p", "Number of MC particles #pi^{+}; N_{MC} [1]; counts", 2001, -0.5, 2000.5);
	h_MCpart_nPion_n = new TH1D("h_MCpart_nPion_n", "Number of MC particles #pi^{-}; N_{MC} [1]; counts", 2001, -0.5, 2000.5);
	h_MCpart_nKaon_p = new TH1D("h_MCpart_nKaon_p", "Number of MC particles K^{+}; N_{MC} [1]; counts", 2001, -0.5, 2000.5);
	h_MCpart_nKaon_n = new TH1D("h_MCpart_nKaon_n", "Number of MC particles K^{-}; N_{MC} [1]; counts", 2001, -0.5, 2000.5);
	h_MCpart_nProton_p = new TH1D("h_MCpart_nProton_p", "Number of MC particles p^{+}; N_{MC} [1]; counts", 2001, -0.5, 2000.5);
	h_MCpart_nProton_n = new TH1D("h_MCpart_nProton_n", "Number of MC particles p^{-}; N_{MC} [1]; counts", 2001, -0.5, 2000.5);
	h_MCpart_nElectron_p = new TH1D("h_MCpart_nElectron_p", "Number of MC particles e^{+}; N_{MC} [1]; counts", 2001, -0.5, 2000.5);
	h_MCpart_nElectron_n = new TH1D("h_MCpart_nElectron_n", "Number of MC particles e^{-}; N_{MC} [1]; counts", 2001, -0.5, 2000.5);

	h_MCpart_nNeutron = new TH1D("h_MCpart_nNeutron", "Number of MC particles n; N_{MC} [1]; counts", 2001, -0.5, 2000.5);
	h_MCpart_nGamma = new TH1D("h_MCpart_nGamma", "Number of MC particles #gamma; N_{MC} [1]; counts", 2001, -0.5, 2000.5);

	h_MCpart_nGen = new TH1D("h_MCpart_nGen", "Number of generated MC particles; N_{MC} [1]; counts", 2001, -0.5, 2000.5);
	h_MCpart_nSec = new TH1D("h_MCpart_nSec", "Number of secondary MC particles; N_{MC} [1]; counts", 2001, -0.5, 2000.5);


	// MC particles
	h_MCpart_mass = new TH1D("h_MCpart_mass", "MC particle mass; m [GeV/c^{2}]; counts", 2000, 0.0, 20.0);
    h_MCpart_charge = new TH1D("h_MCpart_charge", "MC particle charge; q [1]; counts", 101, -50.5, 50.5);
	h_MCpart_E = new TH1D("h_MCpart_E", "MC particle energy; E [GeV]; counts", 500, 0.0, 50.0);
	h_MCpart_p = new TH1D("h_MCpart_p", "MC particle momentum; p [GeV/c]; counts", 500, 0.0, 50.0);
	h_MCpart_pT = new TH1D("h_MCpart_pT", "MC particle transverse momentum; p_{T} [GeV/c]; counts", 500, 0.0, 50.0);

	h_MCpart_mom_x = new TH1D("h_MCpart_mom_x", "MC particle momentum x; p_{x} [GeV/c]; counts", 200, -50.0, 50.0);
	h_MCpart_mom_y = new TH1D("h_MCpart_mom_y", "MC particle momentum y; p_{y} [GeV/c]; counts", 200, -50.0, 50.0);
	h_MCpart_mom_z = new TH1D("h_MCpart_mom_z", "MC particle momentum z; p_{z} [GeV/c]; counts", 200, -50.0, 50.0);

	h_MCpart_eta = new TH1D("h_MCpart_eta", "MC particle #eta; #eta [1]; counts", 200, -10.0, 10.0);
	h_MCpart_etaphi = new TH2D("h_MCpart_etaphi", "MC particle #eta,#phi; #eta [1]; #phi [rad]; counts", 200, -10.0, 10.0, 314, -Pi(), Pi());

	h_MCpart_xy = new TH2D("h_MCpart_xy", "MC particle position x,y; x [mm]; y [mm]; counts", 1000, -5000.0, 5000.0, 1000, -5000.0, 5000.0);
    h_MCpart_zr = new TH2D("h_MCpart_zr", "MC particle position z,r; z [mm]; r [mm]; counts", 1000, -5000.0, 5000.0, 1000, -5000.0, 5000.0);

	h_MCpart_end_p = new TH1D("h_MCpart_end_p", "MC particle momentum at endpoint; p [GeV/c]; counts", 500, 0.0, 50.0);
	h_MCpart_end_pT = new TH1D("h_MCpart_end_pT", "MC particle transverse momentum at endpoint; p_{T} [GeV/c]; counts", 500, 0.0, 50.0);

	h_MCpart_posEnd_xy = new TH2D("h_MCpart_posEnd_xy", "MC particle endpoint position x,y; x [mm]; y [mm]; counts", 1000, -5000.0, 5000.0, 1000, -5000.0, 5000.0);
    h_MCpart_posEnd_zr = new TH2D("h_MCpart_posEnd_zr", "MC particle endpoint position z,r; z [mm]; r [mm]; counts", 1000, -5000.0, 5000.0, 1000, -5000.0, 5000.0);

	h_MCpart_genStatus = new TH1D("h_MCpart_genStatus", "MC particle generator status; generator status [1]; counts", 100001, -0.5, 100000.5);


	// nHCal acceptance

	h_MCpart_nHCal_etaphi = new TH2D("h_MCpart_nHCal_etaphi", "MC particle #eta,#phi with nHCal hits; #eta [1]; #phi [rad]; counts", 200, -5.0, 5.0, 314, -Pi(), Pi());
	h_MCpart_nHCal_decayed_etaphi = new TH2D("h_MCpart_nHCal_decayed_etaphi", "MC particle #eta,#phi interacted in nHCal; #eta [1]; #phi [rad]; counts", 200, -5.0, 5.0, 314, -Pi(), Pi());

    // momentum

	h_MCpart_Pion_p_p = new TH1D("h_MCpart_Pion_p_p", "MC particles #pi^{+} momentum; p_{MC} [GeV/c]; counts", 500, 0.0, 50.0);
	h_MCpart_Pion_n_p = new TH1D("h_MCpart_Pion_n_p", "MC particles #pi^{-} momentum; p_{MC} [GeV/c]; counts", 500, 0.0, 50.0);
	h_MCpart_Kaon_p_p = new TH1D("h_MCpart_Kaon_p_p", "MC particles K^{+} momentum; p_{MC} [GeV/c]; counts", 500, 0.0, 50.0);
	h_MCpart_Kaon_n_p = new TH1D("h_MCpart_Kaon_n_p", "MC particles K^{-} momentum; p_{MC} [GeV/c]; counts", 500, 0.0, 50.0);
	h_MCpart_Proton_p_p = new TH1D("h_MCpart_Proton_p_p", "MC particles p^{+} momentum; p_{MC} [GeV/c]; counts", 500, 0.0, 50.0);
	h_MCpart_Proton_n_p = new TH1D("h_MCpart_Proton_n_p", "MC particles p^{-} momentum; p_{MC} [GeV/c]; counts", 500, 0.0, 50.0);
	h_MCpart_Electron_p_p = new TH1D("h_MCpart_Electron_p_p", "MC particles e^{+} momentum; p_{MC} [GeV/c]; counts", 500, 0.0, 50.0);
	h_MCpart_Electron_n_p = new TH1D("h_MCpart_Electron_n_p", "MC particles e^{-} momentum; p_{MC} [GeV/c]; counts", 500, 0.0, 50.0);

	h_MCpart_Neutron_p = new TH1D("h_MCpart_Neutron_p", "MC particles n momentum; p_{MC} [GeV/c]; counts", 500, 0.0, 50.0);
	h_MCpart_Gamma_p = new TH1D("h_MCpart_Gamma_p", "MC particles #gamma momentum; p_{MC} [GeV/c]; counts", 500, 0.0, 50.0);


	// energy
	h_MCpart_Pion_p_E = new TH1D("h_MCpart_Pion_p_E", "MC particles #pi^{+} energy; E_{MC} [GeV]; counts", 500, 0.0, 50.0);
	h_MCpart_Pion_n_E = new TH1D("h_MCpart_Pion_n_E", "MC particles #pi^{-} energy; E_{MC} [GeV]; counts", 500, 0.0, 50.0);
	h_MCpart_Kaon_p_E = new TH1D("h_MCpart_Kaon_p_E", "MC particles K^{+} energy; E_{MC} [GeV]; counts", 500, 0.0, 50.0);
	h_MCpart_Kaon_n_E = new TH1D("h_MCpart_Kaon_n_E", "MC particles K^{-} energy; E_{MC} [GeV]; counts", 500, 0.0, 50.0);
	h_MCpart_Proton_p_E = new TH1D("h_MCpart_Proton_p_E", "MC particles p^{+} energy; E_{MC} [GeV]; counts", 500, 0.0, 50.0);
	h_MCpart_Proton_n_E = new TH1D("h_MCpart_Proton_n_E", "MC particles p^{-} energy; E_{MC} [GeV]; counts", 500, 0.0, 50.0);
	h_MCpart_Electron_p_E = new TH1D("h_MCpart_Electron_p_E", "MC particles e^{+} energy; E_{MC} [GeV]; counts", 500, 0.0, 50.0);
	h_MCpart_Electron_n_E = new TH1D("h_MCpart_Electron_n_E", "MC particles e^{-} energy; E_{MC} [GeV]; counts", 500, 0.0, 50.0);

	h_MCpart_Neutron_E = new TH1D("h_MCpart_Neutron_E", "MC particles n energy; E_{MC} [GeV]; counts", 500, 0.0, 50.0);
	h_MCpart_Gamma_E = new TH1D("h_MCpart_Gamma_E", "MC particles #gamma energy; E_{MC} [GeV]; counts", 500, 0.0, 50.0);


    // eta, momentum
	h_MCpart_pion_p_eta_p = new TH2D("h_MCpart_Pion_p_eta_p", "MC particles #pi^{+} #eta vs. momentum; #eta [1]; p_{MC} [GeV/c]; counts", 200, -10.0, 10.0, 500, 0.0, 50.0);
	h_MCpart_pion_n_eta_p = new TH2D("h_MCpart_Pion_n_eta_p", "MC particles #pi^{-} #eta vs. momentum; #eta [1]; p_{MC} [GeV/c]; counts", 200, -10.0, 10.0, 500, 0.0, 50.0);
	h_MCpart_Kaon_p_eta_p = new TH2D("h_MCpart_Kaon_p_eta_p", "MC particles K^{+} #eta vs. momentum; #eta [1]; p_{MC} [GeV/c]; counts", 200, -10.0, 10.0, 500, 0.0, 50.0);
	h_MCpart_Kaon_n_eta_p = new TH2D("h_MCpart_Kaon_n_eta_p", "MC particles K^{-} #eta vs. momentum; #eta [1]; p_{MC} [GeV/c]; counts", 200, -10.0, 10.0, 500, 0.0, 50.0);
	h_MCpart_proton_p_eta_p = new TH2D("h_MCpart_Proton_p_eta_p", "MC particles p^{+} #eta vs. momentum; #eta [1]; p_{MC} [GeV/c]; counts", 200, -10.0, 10.0, 500, 0.0, 50.0);
	h_MCpart_proton_n_eta_p = new TH2D("h_MCpart_Proton_n_eta_p", "MC particles p^{-} #eta vs. momentum; #eta [1]; p_{MC} [GeV/c]; counts", 200, -10.0, 10.0, 500, 0.0, 50.0);
	h_MCpart_Electron_p_eta_p = new TH2D("h_MCpart_Electron_p_eta_p", "MC particles e^{+} #eta vs. momentum; #eta [1]; p_{MC} [GeV/c]; counts", 200, -10.0, 10.0, 500, 0.0, 50.0);
	h_MCpart_Electron_n_eta_p = new TH2D("h_MCpart_Electron_n_eta_p", "MC particles e^{-} #eta vs. momentum; #eta [1]; p_{MC} [GeV/c]; counts", 200, -10.0, 10.0, 500, 0.0, 50.0);

	h_MCpart_Neutron_eta_p = new TH2D("h_MCpart_Neutron_eta_p", "MC particles n #eta vs. momentum; #eta [1]; p_{MC} [GeV/c]; counts", 200, -10.0, 10.0, 500, 0.0, 50.0);
	h_MCpart_Gamma_eta_p = new TH2D("h_MCpart_Gamma_eta_p", "MC particles #gamman #eta vs. momentum; #eta [1]; p_{MC} [GeV/c]; counts", 200, -10.0, 10.0, 500, 0.0, 50.0);



	// eta, energy
	h_MCpart_Pion_p_eta_E = new TH2D("h_MCpart_Pion_p_eta_E", "MC particles #pi^{+} #eta vs. energy; #eta [1]; E_{MC} [GeV]; counts", 200, -10.0, 10.0, 500, 0.0, 50.0);
	h_MCpart_Pion_n_eta_E = new TH2D("h_MCpart_Pion_n_eta_E", "MC particles #pi^{-} #eta vs. energy; #eta [1]; E_{MC} [GeV]; counts", 200, -10.0, 10.0, 500, 0.0, 50.0);
	h_MCpart_Kaon_p_eta_E = new TH2D("h_MCpart_Kaon_p_eta_E", "MC particles K^{+} #eta vs. energy; #eta [1]; E_{MC} [GeV]; counts", 200, -10.0, 10.0, 500, 0.0, 50.0);
	h_MCpart_Kaon_n_eta_E = new TH2D("h_MCpart_Kaon_n_eta_E", "MC particles K^{-} #eta vs. energy; #eta [1]; E_{MC} [GeV]; counts", 200, -10.0, 10.0, 500, 0.0, 50.0);
	h_MCpart_Proton_p_eta_E = new TH2D("h_MCpart_Proton_p_eta_E", "MC particles p^{+} #eta vs. energy; #eta [1]; E_{MC} [GeV]; counts", 200, -10.0, 10.0, 500, 0.0, 50.0);
	h_MCpart_Proton_n_eta_E = new TH2D("h_MCpart_Proton_n_eta_E", "MC particles p^{-} #eta vs. energy; #eta [1]; E_{MC} [GeV]; counts", 200, -10.0, 10.0, 500, 0.0, 50.0);
	h_MCpart_Electron_p_eta_E = new TH2D("h_MCpart_Electron_p_eta_E", "MC particles e^{+} #eta vs. energy; #eta [1]; E_{MC} [GeV]; counts", 200, -10.0, 10.0, 500, 0.0, 50.0);
	h_MCpart_Electron_n_eta_E = new TH2D("h_MCpart_Electron_n_eta_E", "MC particles e^{-} #eta vs. energy; #eta [1]; E_{MC} [GeV]; counts", 200, -10.0, 10.0, 500, 0.0, 50.0);

	h_MCpart_Neutron_eta_E = new TH2D("h_MCpart_Neutron_eta_E", "MC particles n #eta vs. energy; #eta [1]; E_{MC} [GeV]; counts", 200, -10.0, 10.0, 500, 0.0, 50.0);
	h_MCpart_Gamma_eta_E = new TH2D("h_MCpart_Gamma_eta_E", "MC particles #gamma #eta vs. energy; #eta [1]; E_{MC} [GeV]; counts", 200, -10.0, 10.0, 500, 0.0, 50.0);

	// pair projection distance
	h_MCpart_eta_deltaRxy = new TH2D("h_MCpart_eta_deltaRxy", "MC particles pair #eta vs. #DeltaR_{xy}; #eta [1]; #DeltaR_{xy} [cm]; counts", 200, -10.0, 10.0, 5000, 0.0, 500.0);
	h_MCpart_Neutron_eta_deltaRxy = new TH2D("h_MCpart_Neutron_eta_deltaRxy", "MC pair neutron+X #eta vs. #DeltaR_{xy}; #eta [1]; #DeltaR_{xy} [cm]; counts", 200, -10.0, 10.0, 5000, 0.0, 500.0);

	h_MCpart_eta_norm = new TH1D("h_MCpart_eta_norm", "MC particle #eta; #eta; counts", 200, -10.0, 10.0);
	h_MCpart_Neutron_eta_norm = new TH1D("h_MCpart_Neutron_eta_norm", "MC neutron #eta; #eta; counts", 200, -10.0, 10.0);

	// Generated MC particles
	h_MCpart_gen_mass = new TH1D("h_MCpart_gen_mass", "Generated MC particle mass; m [GeV/c^{2}]; counts", 500, 0.0, 50.0);
    h_MCpart_gen_charge = new TH1D("h_MCpart_gen_charge", "Generated MC particle charge; q; counts", 101, -50.5, 50.5);
	h_MCpart_gen_E = new TH1D("h_MCpart_gen_E", "Generated MC particle energy; E [GeV]; counts", 500, 0.0, 50.0);
	h_MCpart_gen_p = new TH1D("h_MCpart_gen_p", "Generated MC particle momentum; p [GeV/c]; counts", 500, 0.0, 50.0);
	h_MCpart_gen_pT = new TH1D("h_MCpart_gen_pT", "Generated MC particle transverse momentum; p_{T} [GeV/c]; counts", 500, 0.0, 50.0);

	h_MCpart_gen_eta = new TH1D("h_MCpart_gen_eta", "Generated MC particle #eta; #eta; counts", 200, -10.0, 10.0);
	h_MCpart_gen_etaphi = new TH2D("h_MCpart_gen_etaphi", "Generated MC particle #eta,#phi; #eta; #phi [rad]; counts", 200, -10.0, 10.0, 314, -Pi(), Pi());

	h_MCpart_gen_xy = new TH2D("h_MCpart_gen_xy", "Generated MC particle position x,y; x [mm]; y [mm]; counts", 1000, -5000.0, 5000.0, 1000, -5000.0, 5000.0);
	h_MCpart_gen_zr = new TH2D("h_MCpart_gen_zr", "Generated MC particle position z,r; z [mm]; r [mm]; counts", 1000, -5000.0, 5000.0, 1000, -5000.0, 5000.0);

	h_MCpart_gen_end_p = new TH1D("h_MCpart_gen_end_p", "Generated MC particle momentum at endpoint; p [GeV/c]; counts", 500, 0.0, 50.0);
	h_MCpart_gen_end_pT = new TH1D("h_MCpart_gen_end_pT", "Generated MC particle transverse momentum at endpoint; p [GeV/c]; counts", 500, 0.0, 50.0);

	h_MCpart_gen_posEnd_xy = new TH2D("h_MCpart_gen_posEnd_xy", "Generated MC particle endpoint position x,y; x [mm]; y [mm]; counts", 1000, -5000.0, 5000.0, 1000, -5000.0, 5000.0);
	h_MCpart_gen_posEnd_zr = new TH2D("h_MCpart_gen_posEnd_zr", "Generated MC particle endpoint position z,r; z [mm]; r [mm]; counts", 1000, -5000.0, 5000.0, 1000, -5000.0, 5000.0);


	// pair projection distance
	h_MCpart_gen_eta_deltaRxy = new TH2D("h_MCpart_gen_eta_deltaRxy", "Generated MC particles pair #eta vs. #DeltaR_{xy}; #eta [1]; #DeltaR_{xy} [cm]; counts", 200, -10.0, 10.0, 5000, 0.0, 500.0);
	h_MCpart_gen_Neutron_eta_deltaRxy = new TH2D("h_MCpart_gen_Neutron_eta_deltaRxy", "Generated MC pair neutron+X #eta vs. #DeltaR_{xy}; #eta [1]; #DeltaR_{xy} [cm]; counts", 200, -10.0, 10.0, 5000, 0.0, 500.0);

	h_MCpart_gen_eta_norm = new TH1D("h_MCpart_gen_eta_norm", "Generated MC particle #eta; #eta; counts", 200, -10.0, 10.0);
	h_MCpart_gen_Neutron_eta_norm = new TH1D("h_MCpart_gen_Neutron_eta_norm", "Generated MC neutron #eta; #eta; counts", 200, -10.0, 10.0);

	// Secondary MC particles
	h_MCpart_sec_mass = new TH1D("h_MCpart_sec_mass", "Secondary MC particle mass; m [GeV/c^{2}]; counts", 500, 0.0, 50.0);
    h_MCpart_sec_charge = new TH1D("h_MCpart_sec_charge", "Secondary MC particle charge; q [1]; counts", 101, -50.5, 50.5);
	h_MCpart_sec_E = new TH1D("h_MCpart_sec_E", "Secondary MC particle energy; E [GeV]; counts", 500, 0.0, 50.0);
	h_MCpart_sec_p = new TH1D("h_MCpart_sec_p", "Secondary MC particle momentum; p [GeV/c]; counts", 500, 0.0, 50.0);
	h_MCpart_sec_pT = new TH1D("h_MCpart_sec_pT", "Secondary MC particle transverse momentum; p_{T} [GeV/c]; counts", 500, 0.0, 50.0);

	h_MCpart_sec_eta = new TH1D("h_MCpart_sec_eta", "Secondary MC particle #eta; #eta; counts", 200, -10.0, 10.0);
	h_MCpart_sec_etaphi = new TH2D("h_MCpart_sec_etaphi", "Secondary MC particle #eta,#phi; #eta; #phi [rad]; counts", 200, -10.0, 10.0, 314, -Pi(), Pi());

	h_MCpart_sec_xy = new TH2D("h_MCpart_sec_xy", "Secondary MC particle position x,y; x [mm]; y [mm]; counts", 1000, -5000.0, 5000.0, 1000, -5000.0, 5000.0);
	h_MCpart_sec_zr = new TH2D("h_MCpart_sec_zr", "Secondary MC particle position z,r; z [mm]; r [mm]; counts", 1000, -5000.0, 5000.0, 1000, -5000.0, 5000.0);

	h_MCpart_sec_end_p = new TH1D("h_MCpart_sec_end_p", "Secondary MC particle momentum at endpoint; p [GeV/c]; counts", 500, 0.0, 50.0);
	h_MCpart_sec_end_pT = new TH1D("h_MCpart_sec_end_pT", "Secondary MC particle transverse momentum at endpoint; p [GeV/c]; counts", 500, 0.0, 50.0);

	h_MCpart_sec_posEnd_xy = new TH2D("h_MCpart_sec_posEnd_xy", "Secondary MC particle endpoint position x,y; x [mm]; y [mm]; counts", 1000, -5000.0, 5000.0, 1000, -5000.0, 5000.0);
	h_MCpart_sec_posEnd_zr = new TH2D("h_MCpart_sec_posEnd_zr", "Secondary MC particle endpoint position z,r; z [mm]; r [mm]; counts", 1000, -5000.0, 5000.0, 1000, -5000.0, 5000.0);


	// MC particles - 1st generation daughters
	h_MCpart_1stgen_daughter_mass = new TH1D("h_MCpart_1stgen_daughter_mass", "1stgen daughter MC mass; m [GeV/c^{2}]; counts", 500, 0.0, 50.0);
    h_MCpart_1stgen_daughter_charge = new TH1D("h_MCpart_1stgen_daughter_charge", "1stgen daughter MC charge; q [1]; counts", 101, -50.5, 50.5);
	h_MCpart_1stgen_daughter_E = new TH1D("h_MCpart_1stgen_daughter_E", "1stgen_daughtererated MC particle energy; E [GeV]; counts", 500, 0.0, 50.0);
	h_MCpart_1stgen_daughter_p = new TH1D("h_MCpart_1stgen_daughter_p", "1st gen daughter MC momentum; p [GeV/c]; counts", 500, 0.0, 50.0);
	h_MCpart_1stgen_daughter_pT = new TH1D("h_MCpart_1stgen_daughter_pT", "1st gen daughter MC transverse momentum; p_{T} [GeV/c]; counts", 500, 0.0, 50.0);

	h_MCpart_1stgen_daughter_etaphi = new TH2D("h_MCpart_1stgen_daughter_etaphi", "1st gen daughter MC #eta,#phi; #eta; #phi [rad]; counts", 200, -10.0, 10.0, 314, -Pi(), Pi());
	h_MCpart_1stgen_daughter_eta = new TH1D("h_MCpart_1stgen_daughter_eta", "1st gen daughter MC #eta; #eta; counts", 200, -10.0, 10.0);

	h_MCpart_1stgen_daughter_xy = new TH2D("h_MCpart_1stgen_daughter_xy", "1st gen daughter MC particle position x,y; x [mm]; y [mm]; counts", 1000, -5000.0, 5000.0, 1000, -5000.0, 5000.0);
	h_MCpart_1stgen_daughter_zr = new TH2D("h_MCpart_1stgen_daughter_zr", "1st gen daughter MC particle position z,r; z [mm]; r [mm]; counts", 1000, -5000.0, 5000.0, 1000, -5000.0, 5000.0);

	h_MCpart_1stgen_daughter_end_p = new TH1D("h_MCpart_1stgen_daughter_end_p", "1st gen daughter MC momentum at endpoint; p [GeV/c]; counts", 200, -50.0, 50.0);
	h_MCpart_1stgen_daughter_end_pT = new TH1D("h_MCpart_1stgen_daughter_end_pT", "1st gen daughter MC transverse momentum at endpoint; p [GeV/c]; counts", 200, -50.0, 50.0);

	h_MCpart_1stgen_daughter_posEnd_xy = new TH2D("h_MCpart_1stgen_daughter_posEnd_xy", "1st gen daughter MC endpoint position x,y; x [mm]; y [mm]; counts", 1000, -5000.0, 5000.0, 1000, -5000.0, 5000.0);
    h_MCpart_1stgen_daughter_posEnd_zr = new TH2D("h_MCpart_1stgen_daughter_posEnd_zr", "1st gen daughter MC endpoint position z,r; z [mm]; r [mm]; counts", 1000, -5000.0, 5000.0, 1000, -5000.0, 5000.0);



	// EcalEndcapNHit
	h_nECal_hit_E = new TH1D("h_nECal_hit_E", "nECal hits energy ; E [GeV]; counts", 200000, 0.0, 20.0);
	h_nECal_hit_Esum = new TH1D("h_nECal_hit_Esum", "nECal sum of hits energy; E_{sum} [GeV]; counts", 200000, 0.0, 20.0);

	h_nECal_nhits = new TH1D("h_nECal_nhits", "No. of nECal hits ; N_{hits}; counts", 501, -0.5, 500.5);

	// HcalEndcapNHit
	h_nHCal_hit_E = new TH1D("h_nHCal_hit_E", "nHCal hits energy ; E [GeV]; counts", 100000, 0.0, 10.0);
	h_nHCal_hit_Ecorr = new TH1D("h_nHCal_hit_Ecorr", "nHCal hits energy - sampling frac. corr. ; E [GeV]; counts", 100000, 0.0, 10.0);
	h_nHCal_hit_Esum = new TH1D("h_nHCal_hit_Esum", "nHCal sum of hits energy; E_{sum} [GeV]; counts", 200000, 0.0, 20.0);
	h_nHCal_hit_EsumCorr = new TH1D("h_nHCal_hit_EsumCorr", "nHCal sum of hits energy - sampling frac. corr. ; E_{sum} [GeV]; counts", 200000, 0.0, 20.0);

	h_nHCal_nhits = new TH1D("h_nHCal_nhits", "No. of nHCal hits ; N_{hits}; counts", 501, -0.5, 500.5);

	h_nHCal_hit_pos_x = new TH1D("h_nHCal_hit_pos_x", "nHCal hit position x; x [mm]; counts", 800, -4000.0, 4000.0);
	h_nHCal_hit_pos_y = new TH1D("h_nHCal_hit_pos_y", "nHCal hit position y; y [mm]; counts", 800, -4000.0, 4000.0);
	h_nHCal_hit_pos_z = new TH1D("h_nHCal_hit_pos_z", "nHCal hit position z; z [mm]; counts", 500, -5000.0, 0.0);
	h_nHCal_hit_pos_xy = new TH2D("h_nHCal_hit_pos_xy", "nHCal hit position xy; x [mm]; y [mm]; counts", 800, -4000.0, 4000.0, 800, -4000.0, 4000.0);

	h_nHCal_hit_pos_rE = new TH2D("h_NHcal_hit_pos_rE", "nHCal hit energy vs. radial position; r [mm]; E [GeV]; counts", 400, 0.0, 4000.0, 20000, 0.0, 20.0);

	h_nHCal_hit_etaphi = new TH2D("h_nHCal_hit_etaphi", "nHCal hit #eta,#phi; #eta [1]; #phi [rad]; counts", 200, -5.0, 5.0, 314, -Pi(), Pi());

	h_nHCal_hit_etaphi_Esum = new TH3F("h_nHCal_hit_etaphi_Esum", "nHCal hit E_{sum} vs. #eta,#phi; #eta [1]; #phi [rad]; E_{sum} [GeV]", 50, -5.0, 0.0, 100, -Pi(), Pi(), 10000, 0.0, 0.1);
	h_nHCal_hit_Rphi_Esum = new TH3F("h_nHCal_hit_Rphi_Esum", "nHCal hit E_{sum} vs. R,#phi; R [cm]; #phi [rad]; E_{sum} [GeV]", 100, 0.0, 400.0, 100, -Pi(), Pi(), 10000, 0.0, 0.1);


	// nCals
	h_nCal_hits_Esum = new TH1D("h_Ncal_hits_Esum", "Ncal-hit E sum; E [GeV]; counts", 200000, 0.0, 20.0);



	// MC particles
	h_MCpart_xy->GetYaxis()->SetNdivisions(5, 1, 0, kTRUE);
	h_MCpart_xy->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);
	h_MCpart_zr->GetYaxis()->SetNdivisions(5, 1, 0, kTRUE);
	h_MCpart_zr->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);

	h_MCpart_posEnd_xy->GetYaxis()->SetNdivisions(5, 1, 0, kTRUE);
	h_MCpart_posEnd_xy->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);
	h_MCpart_posEnd_zr->GetYaxis()->SetNdivisions(5, 1, 0, kTRUE);
	h_MCpart_posEnd_zr->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);


	// Generated MC particles
	h_MCpart_gen_xy->GetYaxis()->SetNdivisions(5, 1, 0, kTRUE);
	h_MCpart_gen_xy->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);
	h_MCpart_gen_zr->GetYaxis()->SetNdivisions(5, 1, 0, kTRUE);
	h_MCpart_gen_zr->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);

	h_MCpart_gen_posEnd_xy->GetYaxis()->SetNdivisions(5, 1, 0, kTRUE);
	h_MCpart_gen_posEnd_xy->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);
	h_MCpart_gen_posEnd_zr->GetYaxis()->SetNdivisions(5, 1, 0, kTRUE);
	h_MCpart_gen_posEnd_zr->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);


	// Secondary MC particles
	h_MCpart_sec_xy->GetYaxis()->SetNdivisions(5, 1, 0, kTRUE);
	h_MCpart_sec_xy->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);
	h_MCpart_sec_zr->GetYaxis()->SetNdivisions(5, 1, 0, kTRUE);
	h_MCpart_sec_zr->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);

	h_MCpart_sec_posEnd_xy->GetYaxis()->SetNdivisions(5, 1, 0, kTRUE);
	h_MCpart_sec_posEnd_xy->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);
	h_MCpart_sec_posEnd_zr->GetYaxis()->SetNdivisions(5, 1, 0, kTRUE);
	h_MCpart_sec_posEnd_zr->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);


	// MC particles - 1st generation daughters
	h_MCpart_1stgen_daughter_xy->GetYaxis()->SetNdivisions(5, 1, 0, kTRUE);
	h_MCpart_1stgen_daughter_xy->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);

	h_MCpart_1stgen_daughter_zr->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);

	h_MCpart_1stgen_daughter_posEnd_xy->GetYaxis()->SetNdivisions(5, 1, 0, kTRUE);
	h_MCpart_1stgen_daughter_posEnd_xy->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);

    h_MCpart_1stgen_daughter_posEnd_zr->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);

	// HcalEndcapNHit
	h_nHCal_hit_pos_x->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);
	h_nHCal_hit_pos_y->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);
	h_nHCal_hit_pos_z->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);

	h_nHCal_hit_pos_xy->GetYaxis()->SetNdivisions(5, 1, 0, kTRUE);
	h_nHCal_hit_pos_xy->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);

	h_nHCal_hit_pos_rE->GetXaxis()->SetNdivisions(5, 1, 0, kTRUE);

}


void DeleteHistogamsSim()
{

	// Event
	delete h_Events;

	delete h_MCpart;

	delete h_MCpart_nPion_p;
	delete h_MCpart_nPion_n;
	delete h_MCpart_nKaon_p;
	delete h_MCpart_nKaon_n;
	delete h_MCpart_nProton_p;
	delete h_MCpart_nProton_n;
	delete h_MCpart_nElectron_p;
	delete h_MCpart_nElectron_n;

	delete h_MCpart_nNeutron;
	delete h_MCpart_nGamma;

	delete h_MCpart_nGen;
	delete h_MCpart_nSec;

	// MC particles
	delete h_MCpart_mass;
	delete h_MCpart_charge;
	delete h_MCpart_E;
	delete h_MCpart_p;
	delete h_MCpart_pT;

	delete h_MCpart_mom_x;
	delete h_MCpart_mom_y;
	delete h_MCpart_mom_z;

	delete h_MCpart_eta;
	delete h_MCpart_etaphi;

	delete h_MCpart_xy;
	delete h_MCpart_zr;

	delete h_MCpart_end_p;
	delete h_MCpart_end_pT;

	delete h_MCpart_posEnd_xy;
	delete h_MCpart_posEnd_zr;

	delete h_MCpart_genStatus;

	// momentum
	delete h_MCpart_Pion_p_p;
	delete h_MCpart_Pion_n_p;
	delete h_MCpart_Kaon_p_p;
	delete h_MCpart_Kaon_n_p;
	delete h_MCpart_Proton_p_p;
	delete h_MCpart_Proton_n_p;
	delete h_MCpart_Electron_p_p;
	delete h_MCpart_Electron_n_p;

	delete h_MCpart_Neutron_p;
	delete h_MCpart_Gamma_p;

	// energy
	delete h_MCpart_Pion_p_E;
	delete h_MCpart_Pion_n_E;
	delete h_MCpart_Kaon_p_E;
	delete h_MCpart_Kaon_n_E;
	delete h_MCpart_Proton_p_E;
	delete h_MCpart_Proton_n_E;
	delete h_MCpart_Electron_p_E;
	delete h_MCpart_Electron_n_E;

	delete h_MCpart_Neutron_E;
	delete h_MCpart_Gamma_E;


	// eta, momentum
	delete h_MCpart_pion_p_eta_p;
	delete h_MCpart_pion_n_eta_p;
	delete h_MCpart_Kaon_p_eta_p;
	delete h_MCpart_Kaon_n_eta_p;
	delete h_MCpart_proton_p_eta_p;
	delete h_MCpart_proton_n_eta_p;
	delete h_MCpart_Electron_p_eta_p;
	delete h_MCpart_Electron_n_eta_p;

	delete h_MCpart_Neutron_eta_p;
	delete h_MCpart_Gamma_eta_p;

	// eta, energy
	delete h_MCpart_Pion_p_eta_E;
	delete h_MCpart_Pion_n_eta_E;
	delete h_MCpart_Kaon_p_eta_E;
	delete h_MCpart_Kaon_n_eta_E;
	delete h_MCpart_Proton_p_eta_E;
	delete h_MCpart_Proton_n_eta_E;
	delete h_MCpart_Electron_p_eta_E;
	delete h_MCpart_Electron_n_eta_E;

	delete h_MCpart_Neutron_eta_E;
	delete h_MCpart_Gamma_eta_E;

	// pair projection distance
	delete h_MCpart_eta_deltaRxy;
	delete h_MCpart_Neutron_eta_deltaRxy;
	delete h_MCpart_eta_norm;
	delete h_MCpart_Neutron_eta_norm;


	// Generated MC particles
	delete h_MCpart_gen_mass;
	delete h_MCpart_gen_charge;
	delete h_MCpart_gen_E;
	delete h_MCpart_gen_p;
	delete h_MCpart_gen_pT;

	delete h_MCpart_gen_eta;
	delete h_MCpart_gen_etaphi;

	delete h_MCpart_gen_xy;
	delete h_MCpart_gen_zr;

	delete h_MCpart_gen_end_p;
	delete h_MCpart_gen_end_pT;

	delete h_MCpart_gen_posEnd_xy;
	delete h_MCpart_gen_posEnd_zr;


	// pair projection distance
	delete h_MCpart_gen_eta_deltaRxy;
	delete h_MCpart_gen_Neutron_eta_deltaRxy;
	delete h_MCpart_gen_eta_norm;
	delete h_MCpart_gen_Neutron_eta_norm;


	// Secondary MC particles
	delete h_MCpart_sec_mass;
	delete h_MCpart_sec_charge;
	delete h_MCpart_sec_E;
	delete h_MCpart_sec_p;
	delete h_MCpart_sec_pT;

	delete h_MCpart_sec_eta;
	delete h_MCpart_sec_etaphi;

	delete h_MCpart_sec_xy;
	delete h_MCpart_sec_zr;

	delete h_MCpart_sec_end_p;
	delete h_MCpart_sec_end_pT;

	delete h_MCpart_sec_posEnd_xy;
	delete h_MCpart_sec_posEnd_zr;


	// MC particles - 1st generation daughters
	delete h_MCpart_1stgen_daughter_mass;
	delete h_MCpart_1stgen_daughter_charge;
	delete h_MCpart_1stgen_daughter_E ;
	delete h_MCpart_1stgen_daughter_p;
	delete h_MCpart_1stgen_daughter_pT;

	delete h_MCpart_1stgen_daughter_etaphi;
	delete h_MCpart_1stgen_daughter_eta;

	delete h_MCpart_1stgen_daughter_xy;
	delete h_MCpart_1stgen_daughter_zr;

	delete h_MCpart_1stgen_daughter_end_p;
	delete h_MCpart_1stgen_daughter_end_pT;

	delete h_MCpart_1stgen_daughter_posEnd_xy;
	delete h_MCpart_1stgen_daughter_posEnd_zr;




	// EcalEndcapNHit
	delete h_nECal_hit_E;
	delete h_nECal_hit_Esum;

	delete h_nECal_nhits;

	// HcalEndcapNHit

	delete h_nHCal_hit_E;
	delete h_nHCal_hit_Ecorr;
	delete h_nHCal_hit_Esum;
	delete h_nHCal_hit_EsumCorr;
	delete h_nCal_hit_delE_perevent;

	delete h_nHCal_nhits;

	delete h_nHCal_hit_pos_x;
	delete h_nHCal_hit_pos_y;
	delete h_nHCal_hit_pos_z;
	delete h_nHCal_hit_pos_xy;

	delete h_nHCal_hit_pos_rE;

	// nCals
	delete h_nCal_hits_Esum;

}

#endif /* HISTOGRAMSSIM_H_ */
