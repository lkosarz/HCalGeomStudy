#!/bin/bash

# Set environment variables
export EPIC_PATH="/users/PAS2524/corey90/epic"
export NHCAL_GEOM_PATH="${EPIC_PATH}/install/share/epic"

# Get the directory of the script
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Find files and exclude epic_backward_hcal_only.xml, then save to geom_list.txt
find "$NHCAL_GEOM_PATH" -name "epic_backward*.xml" -not -name "epic_backward_hcal_only.xml" > "$SCRIPT_DIR/geom_list.txt"
