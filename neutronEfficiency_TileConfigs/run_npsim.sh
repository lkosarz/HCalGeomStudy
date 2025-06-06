#!/bin/bash

# Check if the user provided the correct number of arguments
if [ "$#" -ne 3 ]; then
    echo "Usage: $0 <path_to_file> <energy> <job_number>"
    exit 1
fi

# Get the file path and energy from the arguments
GEOM_FILE="$1"
ENERGY="$2"
JOB_NUMBER=$3

# Check if the provided file exists
if [ ! -f "$GEOM_FILE" ]; then
    echo "Error: File $GEOM_FILE not found."
    exit 1
fi

N_EVT=10000

echo "n events: $N_EVT"

# Get the directory of the script
SCRIPT_DIR="$(dirname "$(realpath "$0")")"

# Define the output file name based on the input file name and energy
OUT_DIR="${SCRIPT_DIR}/outputs/$(basename "${GEOM_FILE%.*}")_neutron_${ENERGY}GeV"
OUT_FILE="${OUT_DIR}/job_$JOB_NUMBER.root"

# Create the output directory if it doesn't exist
mkdir -p "$OUT_DIR"

echo "output file: $OUT_FILE"

# Define the container path
CONTAINER_PATH="/users/PAS2524/corey90/eic-container"

# Run the container and set up the environment
${CONTAINER_PATH}/eic-shell << EOF

    # Define and export the paths
    export EPIC_PATH="/users/PAS2524/corey90/epic"
    export NHCAL_GEOM_PATH="\${EPIC_PATH}/install/share/epic"
    export INPUT_FILE_PATH="$GEOM_FILE"

    echo "ePIC path: \$EPIC_PATH"
    echo "NHCAL geometry path: \$NHCAL_GEOM_PATH"
    echo "Input file path: \$INPUT_FILE_PATH"
    echo "Energy: $ENERGY"

    # Source the ePIC environment
    if [ -f "\${EPIC_PATH}/install/bin/thisepic.sh" ]; then
        source "\${EPIC_PATH}/install/bin/thisepic.sh"
        echo "ePIC environment sourced."
    else
        echo "Error: \${EPIC_PATH}/install/bin/thisepic.sh not found."
    fi

    # Print out energy and geometry file
    echo "Energy: $ENERGY GeV"
    echo "Geometry file: $GEOM_FILE"

    npsim --compactFile=$GEOM_FILE -N=$N_EVT --enableGun --gun.particle=\"neutron\" --gun.energy $ENERGY*GeV --gun.thetaMin 130*deg --gun.thetaMax 177*deg --gun.distribution uniform --outputFile $OUT_FILE

EOF
