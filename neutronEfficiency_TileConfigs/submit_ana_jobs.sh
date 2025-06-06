#!/bin/bash
# Directory containing the list files
LIST_DIR="/users/PAS2524/corey90/HCalGeomStudy/neutronEfficiency_TileConfigs/list_files"

# Directory to store the processed output files
OUTPUT_DIR="/users/PAS2524/corey90/HCalGeomStudy/neutronEfficiency_TileConfigs/processed_outputs"

# Ensure the output directory exists
mkdir -p "$OUTPUT_DIR"

# Loop through all .list files in the list directory
for LIST_FILE in "$LIST_DIR"/*.list; do
    # Extract the base name of the list file (e.g., "epic_backward_hcal_25layers_LFHCAL_neutron_2.4GeV")
    BASE_NAME=$(basename "$LIST_FILE" .list)

    # Define the output file path
    OUTPUT_FILE="$OUTPUT_DIR/$BASE_NAME.root"

    # Submit the job using sbatch
    sbatch --export=LIST_FILE="$LIST_FILE",OUTPUT_FILE="$OUTPUT_FILE",MAX_EVENTS=-1 /users/PAS2524/corey90/HCalGeomStudy/neutronEfficiency_TileConfigs/analysis_job.sh
done
