#!/bin/bash

# Get the absolute path of the directory where the script is located
script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Paths to the text files (relative to the script directory)
energy_file="$script_dir/energy_list.txt"
geom_file="$script_dir/geom_list.txt"

# Check if the files exist
if [[ ! -f "$energy_file" ]]; then
    echo "Error: Energy file not found at $energy_file"
    exit 1
fi

if [[ ! -f "$geom_file" ]]; then
    echo "Error: Geometry file not found at $geom_file"
    exit 1
fi

# Loop through each energy value
while IFS= read -r energy; do
    # Loop through each geometry file
    while IFS= read -r geom; do
        # Print or execute your desired command using $energy and $geom
        echo "Processing energy: $energy with geometry: $geom"

        sbatch --export=GEOMETRY=$geom,ENERGY=$energy $script_dir/submitfile.sh
    done < "$geom_file"
done < "$energy_file"
