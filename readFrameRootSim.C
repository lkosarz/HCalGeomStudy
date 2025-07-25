#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>

#ifdef __CINT__
R__LOAD_LIBRARY(libfmt.so)
#endif
#include "fmt/core.h"

#include "ROOT/RDataFrame.hxx"
#include <TH1D.h>
#include <TH2D.h>
#include <TRandom3.h>
#include <TFile.h>
#include <TChain.h>
#include <TTree.h>
#include <TMath.h>
#include <TVector3.h>

#include "TROOT.h"
#include "TRandom.h"
#include "TH3.h"


#include "DD4hep/Detector.h"
#include "DDRec/CellIDPositionConverter.h"

#include <podio/Frame.h>
#include <podio/CollectionBase.h>
#include "podio/ROOTReader.h"
#include "podio/CollectionIDTable.h"
#include "podio/ObjectID.h"


#include "edm4hep/utils/kinematics.h"

#include "edm4hep/MCParticleCollection.h"
#include "edm4hep/MCParticleCollectionData.h"
#include "edm4hep/MCParticle.h"
#include "edm4hep/MCParticleData.h"

#include "edm4hep/SimCalorimeterHitCollectionData.h"
#include "edm4hep/SimCalorimeterHitCollection.h"
#include "edm4hep/SimCalorimeterHitData.h"
#include "edm4hep/SimCalorimeterHit.h"

#include "edm4hep/CalorimeterHit.h"
#include "edm4hep/CalorimeterHitCollectionData.h"
#include "edm4hep/CalorimeterHitCollection.h"
#include "edm4hep/CalorimeterHitData.h"
#include "edm4hep/CalorimeterHit.h"
#include "edm4hep/CalorimeterHitObj.h"

//dd4hep::sim::Geant4Calorimeter::Hit

#include "edm4eic/ClusterCollection.h"
#include "edm4eic/Cluster.h"
#include "edm4eic/ClusterData.h"

#include "edm4eic/CalorimeterHit.h"
#include "edm4eic/CalorimeterHitCollectionData.h"
#include "edm4eic/CalorimeterHitCollection.h"
#include "edm4eic/CalorimeterHitData.h"
#include "edm4eic/CalorimeterHit.h"
#include "edm4eic/CalorimeterHitObj.h"


#include <edm4eic/vector_utils_legacy.h>
#include <edm4hep/Vector3f.h>


#include "FileList.h"
#include "HistogramsSim.h"
#include "HistogramsDepthCheck.h"
#include "EICutil.h"
#include "BasicUtil.h"


using namespace std;
using namespace ROOT;
using namespace TMath;
//using namespace eicd;
//using namespace edm4eic;
using namespace edm4hep;

int readFrameRootSim(TString list = "data/test.list", TString ofname = "output/output_test.root", long nevents = -1);
int MakeEvent(podio::ROOTReader *reader, unsigned ev);


bool printEvNum = true;
bool debug = false;
dd4hep::Detector* det = NULL;

int readFrameRootSim(TString list, TString ofname, long nevents)
{
    std::cout << "Input list: " << list << std::endl;
    std::cout << "Output file: " << ofname << std::endl;
    std::cout << "Number of events: " << nevents << std::endl;

	// open file w/ frame reader
	podio::ROOTReader *reader = new podio::ROOTReader();

	std::vector<std::string> filenames = openList(list);
	if(filenames.size() != 0) reader->openFiles(filenames);
	else {
		cout<<"Can't open file list! Exiting."<<endl;
		return 0;
	}

	std::vector<std::string_view> categories = reader->getAvailableCategories();

	cout<<"Available categories:"<<endl;
	PrintStringVector(categories);
	cout<<endl;


	unsigned nEvents = reader->getEntries(podio::Category::Event);
	cout<<"Number of events = "<<nEvents<<endl;

	if(nevents>0) nEvents = nevents;



	TFile *output = new TFile(ofname, "recreate");
	output->cd();

	CreateHistogamsSim();
	CreateHistogamsDepthCheck();


	if(nevents>0) nEvents = nevents;

	for(unsigned ev=0; ev<nEvents; ++ev) {

		if(printEvNum) std::cout<<"reading event "<<ev<<std::endl;

		MakeEvent(reader, ev); // execute for each event

		if(debug) std::cout<<"End of event"<<std::endl;

	} // event loop

	std::cout<<"Writing output"<<std::endl;

	output->Write();

	DeleteHistogamsSim();
	DeleteHistogamsDepthCheck();

	output->Close();

	std::cout<<"Finished!"<<std::endl;

	delete output;

	return 1;

}



int MakeEvent(podio::ROOTReader *reader, unsigned ev)
{

	// Get frame
    auto frame = podio::Frame(reader->readNextEntry(podio::Category::Event));

    std::vector<std::string> collections_names = frame.getAvailableCollections();

	if (ev==0) PrintStringVector(collections_names);

	//reader->goToEvent(ev);
	//reader->readEvent();
	//if(printEvNum) std::cout<<"reading event "<<ev<<std::endl;

	//store->endOfEvent();


	// Get collections
	auto& nHCal_hitscoll = frame.get<edm4hep::SimCalorimeterHitCollection>("HcalEndcapNHits");
	auto& MCParticles_coll  = frame.get<edm4hep::MCParticleCollection>("MCParticles");


	double nHCal_samp_frac = 0.0095;
	double projLayerZ = -3950.0; // [mm]
	//double projLayerZ = 3600.0; // [mm]
	double cutLayerZ = -3000.0; // [mm]

	TVector3 mcMom_single;
	TVector3 mcPosProj_single;

	int nPion_p = 0;
	int nPion_n = 0;
	int nKaon_p = 0;
	int nKaon_n = 0;
	int nProton_p = 0;
	int nProton_n = 0;
	int nElectron_p = 0;
	int nElectron_n = 0;

	int nNeutron = 0;
	int nGamma = 0;

	int nMCpart = 0;
	int nMCpart_gen = 0;
	int nMCpart_sec = 0;

	double hit_nHCal_Esum = 0.0;
	double hit_nHCal_scint_Esum = 0.0;

	double singlePart_E = 0.0;
	double singlePart_Ekin = 0.0;


	h_Events->Fill(1.0);

	vector<edm4hep::MCParticleData> *MCParticles_fromContrib_data = new vector<edm4hep::MCParticleData>;
	vector<unsigned> *MCParticlesID_fromContrib_data = new vector<unsigned>;
	map<int, vector<int>> *MCParticle_to_hitContrib_map = new map<int, vector<int>>;


	if(!MCParticles_coll.isValid())
		cout<<"MCParticle collection does not exist!"<<endl;

	if(debug) cout<<"MCParticles collection size = "<<MCParticles_coll.size()<<endl;


	if(!nHCal_hitscoll.isValid())
		cout<<"HcalEndcapNHits collection does not exist!"<<endl;

	if(debug) cout<<"HcalEndcapNHits collection size = "<<nHCal_hitscoll.size()<<endl;


//	Geometry
//------------------

	if(ev == 0)
	{
		TString compact_file = "epic/install/share/epic/epic_backward_hcal_only_sampF.xml";
		//compact_file = "epic/install/share/epic/epic_lfhcal_only.xml";
		//compact_file = "epic/install/share/epic/epic_backward_hcal_only.xml";

		det = &(dd4hep::Detector::getInstance());
		det->fromCompact(compact_file.Data());
		det->volumeManager();
		det->apply("DD4hepVolumeManager", 0, 0);
	}

	dd4hep::rec::CellIDPositionConverter cellid_converter(*det);

	// Get our readout ID spec for HcalEndcapNHits
	auto idSpecBarrel = det->readout("HcalEndcapNHits").idSpec();

	// Get our cell ID decoder
	auto decoder = idSpecBarrel.decoder();
	const int slice_index = decoder->index("slice");


//---------------------------------

	bool *isInNHcal = new bool[MCParticles_coll.size()]{};

	//isInNHcal = {false};

//---------------------------------

		for (unsigned hit_iter = 0; hit_iter < nHCal_hitscoll.size(); ++hit_iter) {

			//CalorimeterHit hit_nHCal =  nHCal_hits_frame[hit_iter];
			SimCalorimeterHit hit_nHCal = nHCal_hitscoll.at(hit_iter);


			if(!hit_nHCal.isAvailable())
				cout<<"CalorimeterHit does not exist! index = "<<hit_nHCal<<endl;

			auto contrib_data = hit_nHCal.getContributions();

			if(debug) cout<<"hit contributions = "<<contrib_data.size()<<endl;

			for (unsigned c = 0; c < contrib_data.size(); ++c) {

				CaloHitContribution contrib = contrib_data.at(c);

				int MCparentID = contrib.getParticle().id().index;
				int contribID = contrib.id().index;

				isInNHcal[MCparentID] = true;

				map<int, vector<int>>::iterator it;
				it = MCParticle_to_hitContrib_map->find(MCparentID);

				if (it != MCParticle_to_hitContrib_map->end())
					{
						it->second.push_back(contribID);
						if(debug) cout<<"contribID added for MCparticle = "<<MCparentID<<","<<contribID<<endl;

					}
				else{

					vector<int> vec = {contribID};

					MCParticle_to_hitContrib_map->insert(it, pair<int, vector<int>>(MCparentID, vec));
					if(debug) cout<<"contribID inserted for MCparticle = "<<MCparentID<<","<<contribID<<endl;
					}
			}


		} // HcalEndcapNHits loop

		if(debug){
			//cout<<"MCParticles_fromContrib_data size = "<<MCParticles_fromContrib_data->size()<<endl;
			cout<<"MCParticle_to_hitContrib_map size = "<<MCParticle_to_hitContrib_map->size()<<endl;
		}

		if(debug)
		{
			for (map<int, vector<int>>::iterator it = MCParticle_to_hitContrib_map->begin(); it != MCParticle_to_hitContrib_map->end(); ++it) {

				cout<<"size[id="<<it->first<<"] ="<<it->second.size()<<endl;
				for (int i = 0; i < it->second.size(); ++i) {

					cout<<it->second[i]<<", ";
				}
				cout<<endl;
			}
		}



	// MC particle loop

	for (unsigned mc_iter = 0; mc_iter < MCParticles_coll.size(); ++mc_iter) {

		edm4hep::MCParticle mcpart =  MCParticles_coll.at(mc_iter);

		//if(!MCParticle_to_hitContrib_map->find(mc_iter)->second.size())	continue;
		if(MCParticle_to_hitContrib_map->find(mc_iter)->second.size()==0 || MCParticle_to_hitContrib_map->find(mc_iter) == MCParticle_to_hitContrib_map->end() || !MCParticle_to_hitContrib_map->size())
		{
			if(debug) cout<<"Excluded mc_iter = "<<mc_iter<<"\t size = "<<MCParticle_to_hitContrib_map->find(mc_iter)->second.size()<<endl;

			continue;
		}
		bool has_nHcalHit = false;

		for (int i = 0; i < MCParticlesID_fromContrib_data->size(); ++i) {

			if(MCParticlesID_fromContrib_data->at(i) ==  mc_iter) has_nHcalHit = true;
		}

		// Select only particles with nHCal hits
		//if(!has_nHcalHit) continue;

		if(debug) cout<<"Included mc_iter = "<<mc_iter<<"\t size = "<<MCParticle_to_hitContrib_map->find(mc_iter)->second.size()<<endl;


		//if (MCParticle_to_hitContrib_map->find(mc_iter) == MCParticle_to_hitContrib_map->end()) continue;

		if(debug)
		{
			cout<<endl;
			cout<<"MCParticle generator status = "<<mcpart.getGeneratorStatus()<<endl;
			cout<<"MCParticle simulator status = "<<mcpart.getSimulatorStatus()<<endl;
			cout<<"MCParticle isCreatedInSimulation = "<<mcpart.isCreatedInSimulation()<<endl;
		}

		TVector3 mcMom(mcpart.getMomentum().x, mcpart.getMomentum().y, mcpart.getMomentum().z);
		TVector3 mcMomEnd(mcpart.getMomentumAtEndpoint ().x, mcpart.getMomentumAtEndpoint ().y, mcpart.getMomentumAtEndpoint ().z);
		TVector3 mcStart(mcpart.getVertex().x, mcpart.getVertex().y, mcpart.getVertex().z);
		TVector3 mcEnd(mcpart.getEndpoint().x, mcpart.getEndpoint().y, mcpart.getEndpoint().z);

		TVector3 mcProjPos = projTrackZ(mcMom.Eta(), mcMom.Phi(), projLayerZ, mcStart);

		if(mcpart.id().index == 0)
			{
				mcMom_single = mcMom;
				mcPosProj_single = mcProjPos;
			}

		//vector<edm4hep::MCParticleData> *parents_check = new vector<edm4hep::MCParticleData>;

		auto parents_check = mcpart.getParents();

		if(debug)
		{
			cout<<"MCParticle parents size = "<<parents_check.size()<<endl;
		}

		//if(mcpart.isCreatedInSimulation()) continue; // select primaries, reject secondaries
		//if(!mcpart.isCreatedInSimulation()) continue; // select secondaries, reject primaries
		//if(mcpart.getGeneratorStatus()!=1) continue; // select primaries, reject secondaries
		//if(mcpart.getGeneratorStatus()==1) continue; // select secondaries, reject primaries

		//	Correct!
		//if(mcpart.getGeneratorStatus()!=1) continue; // select primaries, reject secondaries
		//if(mcpart.getGeneratorStatus()!=0) continue; // select secondaries, reject primaries

		//if(mcMom.Eta()>-4.0)	continue;
		//if(mcMom.Eta()<-4.0 ||  mcMom.Eta()>-1.0)	continue;
		//if(mcEnd.z()>-3250)	continue;
		//if(mcStart.z()<cutLayerZ)	continue;
		//if(mcpart.getPDG() == 22)	continue;
		//if(mcpart.getPDG() == 11)	continue;
		//if(mcpart.getPDG() == -11)	continue;
		//if(mcpart.getPDG() == 111)	continue;
		//if(mcpart.getPDG() == 221)	continue;

		//if(mcMom.Mag()<1)	continue; // >1 GeV/c^{2}
		//if(mcpart.getEnergy()<1)	continue; // >1 GeV/c^{2}

		nMCpart++;

		if(debug)
		{
			cout<<"MCParticle index = "<<mcpart.id().index<<"\titer = "<<mc_iter<<endl;
			cout<<"MCParticle px = "<<mcMom.x()<<endl;
			cout<<"MCParticle py = "<<mcMom.y()<<endl;
			cout<<"MCParticle pz = "<<mcMom.z()<<endl;
		}

		if(mc_iter == 0)
		{
			singlePart_E = mcpart.getEnergy();
			singlePart_Ekin = mcpart.getEnergy()-mcpart.getMass();
		}

		h_MCpart_mass->Fill(mcpart.getMass());
		h_MCpart_charge->Fill(mcpart.getCharge());
		h_MCpart_E->Fill(mcpart.getEnergy());
		h_MCpart_p->Fill(mcMom.Mag());
		h_MCpart_pT->Fill(mcMom.Pt());

		h_MCpart_mom_x->Fill(mcMom.x());
		h_MCpart_mom_y->Fill(mcMom.y());
		h_MCpart_mom_z->Fill(mcMom.z());

		h_MCpart_eta->Fill(mcMom.Eta());
		h_MCpart_etaphi->Fill(mcMom.Eta(), mcMom.Phi());

		h_MCpart_xy->Fill(mcStart.x(), mcStart.y());
		h_MCpart_zr->Fill(mcStart.z(), mcStart.Pt());

		h_MCpart_end_p->Fill(mcMomEnd.Mag());
		h_MCpart_end_pT->Fill(mcMomEnd.Pt());

		h_MCpart_posEnd_xy->Fill(mcEnd.x(), mcEnd.y());
		h_MCpart_posEnd_zr->Fill(mcEnd.z(), mcEnd.Pt());

		h_MCpart_genStatus->Fill(mcpart.getGeneratorStatus());

		if(mcpart.getPDG() == 211) nPion_p++;
		if(mcpart.getPDG() == -211) nPion_n++;
		if(mcpart.getPDG() == 321) nKaon_p++;
		if(mcpart.getPDG() == -321) nKaon_n++;
		if(mcpart.getPDG() == 2212) nProton_p++;
		if(mcpart.getPDG() == -2212) nProton_n++;
		if(mcpart.getPDG() == -11) nElectron_p++;
		if(mcpart.getPDG() == 11) nElectron_n++;

		if(mcpart.getPDG() == 2112) nNeutron++;
		if(mcpart.getPDG() == 22) nGamma++;


		// momentum
		if(mcpart.getPDG() == 211) h_MCpart_Pion_p_p->Fill(mcMom.Mag());
		if(mcpart.getPDG() == -211) h_MCpart_Pion_n_p->Fill(mcMom.Mag());
		if(mcpart.getPDG() == 321) h_MCpart_Kaon_p_p->Fill(mcMom.Mag());
		if(mcpart.getPDG() == -321) h_MCpart_Kaon_n_p->Fill(mcMom.Mag());
		if(mcpart.getPDG() == 2212) h_MCpart_Proton_p_p->Fill(mcMom.Mag());
		if(mcpart.getPDG() == -2212) h_MCpart_Proton_n_p->Fill(mcMom.Mag());
		if(mcpart.getPDG() == -11) h_MCpart_Electron_p_p->Fill(mcMom.Mag());
		if(mcpart.getPDG() == 11) h_MCpart_Electron_n_p->Fill(mcMom.Mag());

		if(mcpart.getPDG() == 2112) h_MCpart_Neutron_p->Fill(mcMom.Mag());
		if(mcpart.getPDG() == 22) h_MCpart_Gamma_p->Fill(mcMom.Mag());

		// energy
		if(mcpart.getPDG() == 211) h_MCpart_Pion_p_E->Fill(mcpart.getEnergy());
		if(mcpart.getPDG() == -211) h_MCpart_Pion_n_E->Fill(mcpart.getEnergy());
		if(mcpart.getPDG() == 321) h_MCpart_Kaon_p_E->Fill(mcpart.getEnergy());
		if(mcpart.getPDG() == -321) h_MCpart_Kaon_n_E->Fill(mcpart.getEnergy());
		if(mcpart.getPDG() == 2212) h_MCpart_Proton_p_E->Fill(mcpart.getEnergy());
		if(mcpart.getPDG() == -2212) h_MCpart_Proton_n_E->Fill(mcpart.getEnergy());
		if(mcpart.getPDG() == -11) h_MCpart_Electron_p_E->Fill(mcpart.getEnergy());
		if(mcpart.getPDG() == 11) h_MCpart_Electron_n_E->Fill(mcpart.getEnergy());

		if(mcpart.getPDG() == 2112) h_MCpart_Neutron_E->Fill(mcpart.getEnergy());
		if(mcpart.getPDG() == 22) h_MCpart_Gamma_E->Fill(mcpart.getEnergy());


		// eta, momentum
		if(mcpart.getPDG() == 211) h_MCpart_pion_p_eta_p->Fill(mcMom.Eta(), mcMom.Mag());
		if(mcpart.getPDG() == -211) h_MCpart_pion_n_eta_p->Fill(mcMom.Eta(), mcMom.Mag());
		if(mcpart.getPDG() == 321) h_MCpart_Kaon_p_eta_p->Fill(mcMom.Eta(), mcMom.Mag());
		if(mcpart.getPDG() == -321) h_MCpart_Kaon_n_eta_p->Fill(mcMom.Eta(), mcMom.Mag());
		if(mcpart.getPDG() == 2212) h_MCpart_proton_p_eta_p->Fill(mcMom.Eta(), mcMom.Mag());
		if(mcpart.getPDG() == -2212) h_MCpart_proton_n_eta_p->Fill(mcMom.Eta(), mcMom.Mag());
		if(mcpart.getPDG() == -11) h_MCpart_Electron_p_eta_p->Fill(mcMom.Eta(), mcMom.Mag());
		if(mcpart.getPDG() == 11) h_MCpart_Electron_n_eta_p->Fill(mcMom.Eta(), mcMom.Mag());

		if(mcpart.getPDG() == 2112) h_MCpart_Neutron_eta_p->Fill(mcMom.Eta(), mcMom.Mag());
		if(mcpart.getPDG() == 22) h_MCpart_Gamma_eta_p->Fill(mcMom.Eta(), mcMom.Mag());

		// eta, energy
		if(mcpart.getPDG() == 211) h_MCpart_Pion_p_eta_E->Fill(mcMom.Eta(), mcpart.getEnergy());
		if(mcpart.getPDG() == -211) h_MCpart_Pion_n_eta_E->Fill(mcMom.Eta(), mcpart.getEnergy());
		if(mcpart.getPDG() == 321) h_MCpart_Kaon_p_eta_E->Fill(mcMom.Eta(), mcpart.getEnergy());
		if(mcpart.getPDG() == -321) h_MCpart_Kaon_n_eta_E->Fill(mcMom.Eta(), mcpart.getEnergy());
		if(mcpart.getPDG() == 2212) h_MCpart_Proton_p_eta_E->Fill(mcMom.Eta(), mcpart.getEnergy());
		if(mcpart.getPDG() == -2212) h_MCpart_Proton_n_eta_E->Fill(mcMom.Eta(), mcpart.getEnergy());
		if(mcpart.getPDG() == -11) h_MCpart_Electron_p_eta_E->Fill(mcMom.Eta(), mcpart.getEnergy());
		if(mcpart.getPDG() == 11) h_MCpart_Electron_n_eta_E->Fill(mcMom.Eta(), mcpart.getEnergy());

		if(mcpart.getPDG() == 2112) h_MCpart_Neutron_eta_E->Fill(mcMom.Eta(), mcpart.getEnergy());
		if(mcpart.getPDG() == 22) h_MCpart_Gamma_eta_E->Fill(mcMom.Eta(), mcpart.getEnergy());


		// Generated MC particles
		if(mcpart.getGeneratorStatus()==1)
		{
			h_MCpart_gen_mass->Fill(mcpart.getMass());
			h_MCpart_gen_charge->Fill(mcpart.getCharge());
			h_MCpart_gen_E->Fill(mcpart.getEnergy());
			h_MCpart_gen_p->Fill(mcMom.Mag());
			h_MCpart_gen_pT->Fill(mcMom.Pt());

			h_MCpart_gen_eta->Fill(mcMom.Eta());
			h_MCpart_gen_etaphi->Fill(mcMom.Eta(), mcMom.Phi());

			h_MCpart_gen_xy->Fill(mcStart.x(), mcStart.y());
			h_MCpart_gen_zr->Fill(mcStart.z(), mcStart.Pt());

			h_MCpart_gen_end_p->Fill(mcMomEnd.Mag());
			h_MCpart_gen_end_pT->Fill(mcMomEnd.Pt());

			h_MCpart_gen_posEnd_xy->Fill(mcEnd.x(), mcEnd.y());
			h_MCpart_gen_posEnd_zr->Fill(mcEnd.z(), mcEnd.Pt());

			nMCpart_gen++;
		}


		// Secondary MC particles
		if(mcpart.getGeneratorStatus()==0)
		{
			h_MCpart_sec_mass->Fill(mcpart.getMass());
			h_MCpart_sec_charge->Fill(mcpart.getCharge());
			h_MCpart_sec_E->Fill(mcpart.getEnergy());
			h_MCpart_sec_p->Fill(mcMom.Mag());
			h_MCpart_sec_pT->Fill(mcMom.Pt());

			h_MCpart_sec_eta->Fill(mcMom.Eta());
			h_MCpart_sec_etaphi->Fill(mcMom.Eta(), mcMom.Phi());

			h_MCpart_sec_xy->Fill(mcStart.x(), mcStart.y());
			h_MCpart_sec_zr->Fill(mcStart.z(), mcStart.Pt());

			h_MCpart_sec_end_p->Fill(mcMomEnd.Mag());
			h_MCpart_sec_end_pT->Fill(mcMomEnd.Pt());

			h_MCpart_sec_posEnd_xy->Fill(mcEnd.x(), mcEnd.y());
			h_MCpart_sec_posEnd_zr->Fill(mcEnd.z(), mcEnd.Pt());

			nMCpart_sec++;

			bool parentIsPrimary = false;

			//podio::RelationRange<edm4hep::MCParticle> MCparents = mcpart.getParents();

			//vector<edm4hep::MCParticleData> *parents_data = new vector<edm4hep::MCParticleData>;
			//vector<edm4hep::MCParticleData> *daughters_data = new vector<edm4hep::MCParticleData>;


			auto MCparents_data = mcpart.getParents();
			auto MCdaughters_data = mcpart.getDaughters();

			for (int parentIter = 0; parentIter < MCparents_data.size(); ++parentIter) {

				edm4hep::MCParticle mcpart_parent = MCparents_data.at(parentIter);

				if(mcpart.getGeneratorStatus()==1)	parentIsPrimary = true;
			}

			//for (int parentIter = 0; parentIter < MCparents.size(); ++parentIter) {
/*			for (int parentIter = mcpart_data.parents_begin; parentIter < mcpart_data.parents_end; ++parentIter) {

				//if(!MCParticles_data->at(parentIter).isCreatedInSimulation)	parentIsPrimary = true;

	        	unsigned parentID = MCparents_data->at(parentIter).index;

				edm4hep::MCParticleData mcpart_data_parent = MCParticles_data->at(parentID);
				edm4hep::MCParticle mcpart_parent(mcpart_data_parent.PDG, mcpart_data_parent.generatorStatus, mcpart_data_parent.simulatorStatus, mcpart_data_parent.charge, mcpart_data_parent.time, mcpart_data_parent.mass, mcpart_data_parent.vertex, mcpart_data_parent.endpoint, mcpart_data_parent.momentum, mcpart_data_parent.momentumAtEndpoint, mcpart_data_parent.spin, mcpart_data_parent.colorFlow);

				if(!mcpart_parent.isCreatedInSimulation())	parentIsPrimary = true;
			}*/

			// MC particles - 1st generation daughters
			if(parentIsPrimary)
			{
				h_MCpart_1stgen_daughter_mass->Fill(mcpart.getMass());
				h_MCpart_1stgen_daughter_charge->Fill(mcpart.getCharge());
				h_MCpart_1stgen_daughter_E->Fill(mcpart.getEnergy());
				h_MCpart_1stgen_daughter_p->Fill(mcMom.Mag());
				h_MCpart_1stgen_daughter_pT->Fill(mcMom.Pt());

				h_MCpart_1stgen_daughter_eta->Fill(mcMom.Eta());
				h_MCpart_1stgen_daughter_etaphi->Fill(mcMom.Eta(), mcMom.Phi());

				h_MCpart_1stgen_daughter_xy->Fill(mcStart.x(), mcStart.y());
				h_MCpart_1stgen_daughter_zr->Fill(mcStart.z(), mcStart.Pt());

				h_MCpart_1stgen_daughter_end_p->Fill(mcMomEnd.Mag());
				h_MCpart_1stgen_daughter_end_pT->Fill(mcMomEnd.Pt());

				h_MCpart_1stgen_daughter_posEnd_xy->Fill(mcEnd.x(), mcEnd.y());
				h_MCpart_1stgen_daughter_posEnd_zr->Fill(mcEnd.z(), mcEnd.Pt());
			}


		}	// Secondary MC particles

		// Make MC particle pairs

		for (unsigned mc_iter2 = 0; mc_iter2 < MCParticles_coll.size(); ++mc_iter2) {

			edm4hep::MCParticle mcpart2 =  MCParticles_coll.at(mc_iter2);


			TVector3 mcMom2(mcpart2.getMomentum().x, mcpart2.getMomentum().y, mcpart2.getMomentum().z);
			TVector3 mcMomEnd2(mcpart2.getMomentumAtEndpoint ().x, mcpart2.getMomentumAtEndpoint ().y, mcpart2.getMomentumAtEndpoint ().z);
			TVector3 mcStart2(mcpart2.getVertex().x, mcpart2.getVertex().y, mcpart2.getVertex().z);
			TVector3 mcEnd2(mcpart2.getEndpoint().x, mcpart2.getEndpoint().y, mcpart2.getEndpoint().z);

			//if(mcMom2.Eta()<-4.0 ||  mcMom2.Eta()>-1.0)	continue;
			if(mcStart2.z()<cutLayerZ)	continue;
			if(mcpart2.getPDG() == 22)	continue;
			if(mcpart2.getPDG() == 11)	continue;
			if(mcpart2.getPDG() == -11)	continue;
			if(mcpart2.getPDG() == 111)	continue;
			if(mcpart2.getPDG() == 221)	continue;

			//if(mcMom2.Mag()<1)	continue; // >1 GeV/c^{2}
			//if(mcpart2.getEnergy()<1)	continue; // >1 GeV/c^{2}

			if(mc_iter==mc_iter2)	continue;

			TVector3 mcProjPos2 = projTrackZ(mcMom2.Eta(), mcMom2.Phi(), projLayerZ, mcStart2);

			TVector3 diffVect = mcProjPos-mcProjPos2;
			diffVect.SetMag(diffVect.Mag()/10.0); // convert [mm]->[cm]
/*
			cout<<"proj x = "<<mcProjPos.x()<<"\ty = "<<mcProjPos.y()<<"\tz = "<<mcProjPos.z()<<endl;
			cout<<"proj2 x = "<<mcProjPos2.x()<<"\ty = "<<mcProjPos2.y()<<"\tz = "<<mcProjPos2.z()<<endl;
			cout<<"delta x = "<<diffVect.x()<<"\ty = "<<diffVect.y()<<"\tz = "<<diffVect.z()<<endl;
*/
			h_MCpart_eta_deltaRxy->Fill(mcMom.Eta(), diffVect.Pt());
			if(mcpart.getPDG() == 2112)	h_MCpart_Neutron_eta_deltaRxy->Fill(mcMom.Eta(), diffVect.Pt());

			if(mcpart.getGeneratorStatus()==1 && mcpart2.getGeneratorStatus()==1)
			{
				h_MCpart_gen_eta_deltaRxy->Fill(mcMom.Eta(), diffVect.Pt());
				if(mcpart.getPDG() == 2112)	h_MCpart_gen_Neutron_eta_deltaRxy->Fill(mcMom.Eta(), diffVect.Pt());
			}

		} // MCParticles loop 2

		h_MCpart_eta_norm->Fill(mcMom.Eta());
		if(mcpart.getPDG() == 2112) h_MCpart_Neutron_eta_norm->Fill(mcMom.Eta());

		if(mcpart.getGeneratorStatus()==1)
		{
			h_MCpart_gen_eta_norm->Fill(mcMom.Eta());
			if(mcpart.getPDG() == 2112) h_MCpart_gen_Neutron_eta_norm->Fill(mcMom.Eta());
		}

		//delete parents_check;


		// nHCal acceptance

		if(mcpart.isDecayedInCalorimeter())
		{
			h_MCpart_nHCal_decayed_etaphi->Fill(mcMom.Eta(), mcMom.Phi());
		}
		if(isInNHcal[mc_iter])
		{
			h_MCpart_nHCal_etaphi->Fill(mcMom.Eta(), mcMom.Phi());
		}

	} // MCParticles loop


	//h_MCpart->Fill(MCParticles_frame.size());
	//h_MCpart->Fill(MCParticles_data->size());
	h_MCpart->Fill(nMCpart);

	h_MCpart_nPion_p->Fill(nPion_p);
	h_MCpart_nPion_n->Fill(nPion_n);
	h_MCpart_nKaon_p->Fill(nKaon_p);
	h_MCpart_nKaon_n->Fill(nKaon_n);
	h_MCpart_nProton_p->Fill(nProton_p);
	h_MCpart_nProton_n->Fill(nProton_n);
	h_MCpart_nElectron_p->Fill(nElectron_p);
	h_MCpart_nElectron_n->Fill(nElectron_n);

	h_MCpart_nNeutron->Fill(nNeutron);
	h_MCpart_nGamma->Fill(nGamma);

	h_MCpart_nGen->Fill(nMCpart_gen);
	h_MCpart_nSec->Fill(nMCpart_sec);


	h_temp_depth_nHCal_z->Reset();
	h_temp_depth_nHCal_hit_Esum_z->Reset();


	if(!nHCal_hitscoll.isValid())
		cout<<"HcalEndcapNHits collection does not exist!"<<endl;

	if(debug) cout<<"HcalEndcapNHits size = "<<nHCal_hitscoll.size()<<endl;

	h_nHCal_nhits->Fill(nHCal_hitscoll.size());


		for (unsigned hit_iter = 0; hit_iter < nHCal_hitscoll.size(); ++hit_iter) {

			SimCalorimeterHit hit_nHCal = nHCal_hitscoll.at(hit_iter);


			if(!hit_nHCal.isAvailable())
				cout<<"CalorimeterHit does not exist! index = "<<hit_nHCal<<endl;

			const int hit_slice = decoder->get(hit_nHCal.getCellID(), slice_index);

			hit_nHCal_Esum += hit_nHCal.getEnergy();
			if(hit_slice == 3) hit_nHCal_scint_Esum += hit_nHCal.getEnergy();


			//cout<<"hit_slice = "<<hit_slice<<endl;
			//cout<<"Escint = "<<hit_nHCal_scint_Esum<<endl;
			//cout<<"Esum = "<<hit_nHCal_Esum<<endl;

			h_nHCal_hit_E->Fill(hit_nHCal.getEnergy());
			h_nHCal_hit_Ecorr->Fill(hit_nHCal.getEnergy()/nHCal_samp_frac);

			h_nHCal_hit_pos_x->Fill(hit_nHCal.getPosition().x);
			h_nHCal_hit_pos_y->Fill(hit_nHCal.getPosition().y);
			h_nHCal_hit_pos_z->Fill(hit_nHCal.getPosition().z);
			h_nHCal_hit_pos_xy->Fill(hit_nHCal.getPosition().x, hit_nHCal.getPosition().y);

			TVector3 nHCal_pos(hit_nHCal.getPosition().x, hit_nHCal.getPosition().y, hit_nHCal.getPosition().z);

			h_nHCal_hit_pos_rE->Fill(nHCal_pos.Perp(), hit_nHCal.getEnergy());

			h_nHCal_hit_etaphi->Fill(nHCal_pos.Eta(), nHCal_pos.Phi());


			// depth study
			h_temp_depth_nHCal_z->Fill(hit_nHCal.getPosition().z/10);
			h_temp_depth_nHCal_hit_Esum_z->Fill(hit_nHCal.getPosition().z/10, hit_nHCal.getEnergy());

			h_depth_nHCal_hit_E_z->Fill(hit_nHCal.getPosition().z/10, hit_nHCal.getEnergy());

			//h_depth_nHCal_nhits_z->Fill(hit_nHCal.getPosition().z, nHCal_data->size());


			auto contributions = hit_nHCal.getContributions();

			for (unsigned c = 0; c < contributions.size(); ++c) {

				//if(contributions[c]==NULL)
				//if(!contributions->at(c).isAvailable())
				//	cout<<"Contribution does not exist! index = "<<c<<endl;

				CaloHitContribution contrib = contributions.at(c);

				if(debug) cout<<"hit time = "<<contrib.getTime()<<endl;


				edm4hep::MCParticle MCpart_in_nHCal = contrib.getParticle();

				// nHCal acceptance check
/*
				if(MCpart_in_nHCal)
					{
					h_MCpart_nHCal_etaphi->Fill(mcMom.Eta(), mcMom.Phi());
					}*/

			}

		} // HcalEndcapNHits loop



		// Sampling fraction
		h_nHCal_sampling_fraction_vs_E->Fill(singlePart_Ekin, hit_nHCal_scint_Esum/hit_nHCal_Esum);
		prof_nHCal_sampling_fraction_vs_E->Fill(singlePart_Ekin, hit_nHCal_scint_Esum/hit_nHCal_Esum);

		//cout<<"Ekin = "<<singlePart_Ekin<<"\tsampF = "<<hit_nHCal_scint_Esum/hit_nHCal_Esum<<" = "<<hit_nHCal_scint_Esum<<"/"<<hit_nHCal_Esum<<endl;


		for (int lbin = 1; lbin <= h_temp_depth_nHCal_z->GetXaxis()->GetNbins(); ++lbin) {

			h_depth_nHCal_nhits_z->Fill(h_temp_depth_nHCal_z->GetBinCenter(lbin), h_temp_depth_nHCal_z->GetBinContent(lbin));
		}

		//TH1D* h_temp_depth_nHCal_hit_Esum_z_proj = (TH1D *)h_temp_depth_nHCal_hit_Esum_z->ProjectionX("proj", 0, -1, "w");

		for (int lbin = 1; lbin <= h_temp_depth_nHCal_hit_Esum_z->GetXaxis()->GetNbins(); ++lbin) {

			h_depth_nHCal_hit_Esum_z->Fill(h_temp_depth_nHCal_hit_Esum_z->GetBinCenter(lbin), h_temp_depth_nHCal_hit_Esum_z->GetBinContent(lbin));
		}

		//delete h_temp_depth_nHCal_hit_Esum_z_proj;

		h_nHCal_hit_Esum->Fill(hit_nHCal_Esum);
		h_nHCal_hit_EsumCorr->Fill(hit_nHCal_Esum/nHCal_samp_frac);

		h_nHCal_hit_etaphi_Esum->Fill(mcMom_single.Eta(), mcMom_single.Phi(), hit_nHCal_Esum);
		h_nHCal_hit_Rphi_Esum->Fill(mcPosProj_single.Perp()/10, mcPosProj_single.Phi(), hit_nHCal_Esum); // R [cm]


		delete MCParticles_fromContrib_data;
		delete MCParticlesID_fromContrib_data;
		delete MCParticle_to_hitContrib_map;

	return 1;
}
