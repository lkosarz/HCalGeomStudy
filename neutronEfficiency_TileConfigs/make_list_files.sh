#!/bin/bash

# Define the outputs directory (relative to the script's location)
outputs_dir="$(dirname "$0")/outputs"

# Get the absolute path of the outputs directory
outputs_dir=$(realpath "$outputs_dir")

# Check if the outputs directory exists
if [[ ! -d "$outputs_dir" ]]; then
    echo "Error: Outputs directory '$outputs_dir' does not exist."
    exit 1
fi

# Loop through each subdirectory in the outputs directory
for subdir in "$outputs_dir"/*/; do
    # Remove the trailing slash and get the subdirectory name
    subdir_name=$(basename "$subdir")

    # Create the .list file in the outputs directory
    list_file="${outputs_dir}/../list_files/${subdir_name}.list"

    # Find all files in the subdirectory and write their absolute paths to the .list file
    find "$subdir" -type f > "$list_file"

    echo "Created list file: $list_file"
done
