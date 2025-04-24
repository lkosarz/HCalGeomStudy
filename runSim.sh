#!/bin/bash


EICSHELL=./eic-shell


#CONDOR_DIR=condorSim
OUT_DIR=data

#mkdir ${CONDOR_DIR}
mkdir "${OUT_DIR}"

## Pass commands to eic-shell
#${EICSHELL} <<EOF

#cd epic
#rm -rf build
#cmake -B build -S . -DCMAKE_INSTALL_PREFIX=install
#cmake --build build -j8 -- install
#cd ../

## Set environment
#source epic/install/bin/thisepic.sh
source /opt/detector/epic-main/bin/thisepic.sh
#source /opt/detector/setup.sh
#source epic/install/setup.sh

#export LOCAL_PREFIX=/gpfs02/eic/lkosarzew/Calorimetry/nHcalDev
#source ${LOCAL_PREFIX}/install/bin/thisepic.sh
#source ${LOCAL_PREFIX}/epic/install/setup.sh
#export DETECTOR_PATH=/gpfs02/eic/lkosarzew/Calorimetry/nHcalDev/epic/install/share/epic

## Export detector libraries
#export LD_LIBRARY_PATH=${LOCAL_PREFIX}/epic/install/lib:$LD_LIBRARY_PATH

## Set geometry and events to simulate
DETECTOR_CONFIG=epic_backward_hcal_only
N_EVENTS=100

ene=1

# Set seed based on date
SEED=$(date +%N)
#echo $SEED

OPTIONS="--compactFile ${DETECTOR_PATH}/${DETECTOR_CONFIG}.xml --numberOfEvents ${N_EVENTS} --random.seed ${SEED} --enableGun \
	--gun.particle pi- --gun.thetaMin 120*degree --gun.thetaMax 180*degree --gun.distribution uniform \
	--gun.energy ${ene}*GeV --outputFile ${OUT_DIR}/output_E${ene}GeV_hist.edm4hep.root"

echo $OPTIONS
npsim $OPTIONS
	
exit

#EOF
