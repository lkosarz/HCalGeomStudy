/*
 * LinkDef.h
 *
 *  Created on: 1 lut 2024
 *      Author: kosarzewski.1
 */

#ifndef LINKDEF_H_
#define LINKDEF_H_


#ifdef __CINT__

/*
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclasses;
*/

#pragma link C++ class vector<edm4hep::MCParticleData>+;
#pragma link C++ class vector<eicd::ClusterData>+;
#pragma link C++ class vector<podio::ObjectID>+;
#pragma link C++ class vector<edm4hep::SimCalorimeterHitData>+;
#pragma link C++ class vector<edm4eic::CalorimeterHitData>+;
#pragma link C++ class vector<edm4hep::CaloHitContributionData>+;

#endif


#endif /* LINKDEF_H_ */
