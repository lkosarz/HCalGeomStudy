/*
 * HistogramsSim.h
 *
 *  Created on: 23 mar 2023
 *      Author: Khaless
 */

#ifndef HISTOGRAMSDEPTHCHECK_H_
#define HISTOGRAMSDEPTHCHECK_H_

#include <TH1.h>
#include <TH1D.h>

#include <TH2.h>
#include <TH2D.h>

#include <TMath.h>

using namespace TMath;

void CreateHistogamsDepthCheck();

// HcalEndcapNHit

TH1D *h_temp_depth_nHCal_z;
TH1D *h_temp_depth_nHCal_hit_Esum_z;

TH2D *h_depth_nHCal_hit_E_z;
TH2D *h_depth_nHCal_hit_Esum_z;
TH2D *h_depth_nHCal_nhits_z;


void CreateHistogamsDepthCheck()
{

	// HcalEndcapNHit
	h_temp_depth_nHCal_z = new TH1D("h_temp_depth_nHCal_z", "TEMP nHCal hits vs. z; z [cm] ; counts", 20, -459.0, -379.0);

	h_temp_depth_nHCal_hit_Esum_z = new TH1D("h_temp_depth_nHCal_hit_Esum_z", "TEMP nHCal hits energy vs. z; z [cm] ; E [GeV]; counts", 20, -459.0, -379.0);

	h_depth_nHCal_hit_E_z = new TH2D("h_depth_nHCal_hit_E_z", "nHCal hits energy vs. z; z [cm] ; E [GeV]; counts", 20, -459.0, -379.0, 100000, 0.0, 10.0);
	h_depth_nHCal_hit_Esum_z = new TH2D("h_depth_nHCal_hit_Esum_z", "nHCal hits energy sum vs. z; z [cm] ; E [GeV]; counts", 20, -459.0, -379.0, 100000, 0.0, 10.0);

	h_depth_nHCal_nhits_z = new TH2D("h_depth_nHCal_nhits_z", "No. of nHCal hits vs. z; z [cm] ; N_{hits}; counts", 20, -459.0, -379.0, 501, -0.5, 500.5);

}

void DeleteHistogamsDepthCheck()
{

	delete h_temp_depth_nHCal_z;
	delete h_temp_depth_nHCal_hit_Esum_z;

	delete h_depth_nHCal_hit_E_z;
	delete h_depth_nHCal_hit_Esum_z;
	delete h_depth_nHCal_nhits_z;

}


#endif /* HISTOGRAMSDEPTHCHECK_H_ */
