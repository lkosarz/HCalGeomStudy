#!/bin/bash

# Loop through all the files in the current directory
for file in *.root; do
    # Extract the configuration part of the filename
    # This assumes the configuration ends before "_neutron"
    config=$(echo "$file" | sed -E 's/_neutron.*//')

    # Create a directory for the configuration if it doesn't exist
    if [ ! -d "$config" ]; then
        mkdir "$config"
    fi

    # Move the file into the corresponding directory
    mv "$file" "$config/"
done

echo "Files have been organized into folders by configuration."
