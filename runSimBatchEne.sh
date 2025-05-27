#!/bin/bash


EICSHELL=./eic-shell


CONDOR_DIR=condorSim
OUT_DIR=output

mkdir ${CONDOR_DIR}
mkdir "${CONDOR_DIR}/${OUT_DIR}"

## Pass commands to eic-shell
#${EICSHELL} <<EOF

# set energy values to simulate
ENERGY_TAB=(0.2 0.3 0.4 0.5 0.7 1.0 2.0 5.0 10.0)
PART_TAB=(pi- neutron)

cd epic
rm -rf build
cmake -B build -S . -DCMAKE_INSTALL_PREFIX=install
cmake --build build -j8 -- install
cd ../

## Set environment
#source /opt/detector/epic-main/bin/thisepic.sh
source epic/install/bin/thisepic.sh
#source /opt/detector/setup.sh
#source epic/install/setup.sh

#export LOCAL_PREFIX=/gpfs02/eic/lkosarzew/Calorimetry/nHcalDev
#source ${LOCAL_PREFIX}/install/bin/thisepic.sh
#source ${LOCAL_PREFIX}/epic/install/setup.sh
#export DETECTOR_PATH=/gpfs02/eic/lkosarzew/Calorimetry/nHcalDev/epic/install/share/epic

## Export detector libraries
#export LD_LIBRARY_PATH=${LOCAL_PREFIX}/epic/install/lib:$LD_LIBRARY_PATH

## Set geometry and events to simulate
DETECTOR_CONFIG=epic_backward_hcal_only_sampF
N_EVENTS=500


for ene in "${ENERGY_TAB[@]}"
do  
  
	for part in "${PART_TAB[@]}"
	do  

# Set seed based on date
SEED=$(date +%N)
#echo $SEED

OPTIONS="--compactFile ${DETECTOR_PATH}/${DETECTOR_CONFIG}.xml --numberOfEvents ${N_EVENTS} --random.seed ${SEED} --enableGun \
	--gun.particle pi- --gun.thetaMin 170*degree --gun.thetaMax 180*degree --gun.distribution uniform \
	--gun.energy ${ene}*GeV --outputFile ${CONDOR_DIR}/${OUT_DIR}/output_${part}_E${ene}GeV_${1}"

echo $OPTIONS
npsim $OPTIONS

	done
done
	
exit

#EOF
