This repository is missing the .root files for the analysis macro "analyzeTrees.cpp".

For the following code to run correctly, there need to be EICrecon files saved in the `input/`	directory. The code is written for 5 files with the energies of 1, 3, 5, 10 GeV and 300 MeV. The filenames were:

```bash
neutron_1gev.edm4eic.root
neutron_3gev.edm4eic.root
neutron_5gev.edm4eic.root
neutron_10gev.edm4eic.root
neutron_300mev.edm4eic.root
```

After these files are added, then the `run.sh` script can be run (in eic-shell), which produces a `.root` file for each provided EICrecon file with the needed histograms. Then it will run all the macros.

`plotHists.cpp` macro produces the `plots.pdf` file, which includes the phi and theta resolutions for all the GeV energies.

`plotAll.cpp` macro produces the `plots_all.pdf` file, which is the same as the `plots.pdf`, plus the energy depositions for all the GeV energies.

`plot5Gev.cpp` macro produces the `plots_5gev.pdf` file, which compares the phi and theta resolutions for 5 GeV.

`plotEfficiency.cpp` macro produces the `efficiency.pdf` file, which plots the efficiency (#reconstructed events/#simulated events) for all the files in one graph.
