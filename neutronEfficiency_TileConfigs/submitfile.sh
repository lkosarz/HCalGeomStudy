#!/bin/bash
#SBATCH --job-name=npsim_job
#SBATCH --account=PAS2524
#SBATCH --time=04:00:00
#SBATCH --array=16-20

# Set PROJECT_DIR to the directory where this script is located
PROJECT_DIR="/users/PAS2524/corey90/HCalGeomStudy/neutronEfficiency_TileConfigs"
export PROJECT_DIR

echo "$PROJECT_DIR/run_npsim.sh "$GEOMETRY" $ENERGY $SLURM_ARRAY_TASK_ID"
$PROJECT_DIR/run_npsim.sh "$GEOMETRY" $ENERGY $SLURM_ARRAY_TASK_ID
