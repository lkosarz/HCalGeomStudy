#!/bin/bash
#SBATCH --job-name=npsim_ana_job
#SBATCH --account=PAS2524
#SBATCH --time=04:00:00

/users/PAS2524/corey90/eic-container/eic-shell << EOF
    /users/PAS2524/corey90/HCalGeomStudy/readFrameRootSimMain $LIST_FILE $OUTPUT_FILE $MAX_EVENTS
EOF
