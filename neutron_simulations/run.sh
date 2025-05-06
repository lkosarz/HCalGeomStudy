#!/bin/bash

# run the analyzeTrees.cpp macro for all EICrecon files in input/
for file in input/*.root; do
    echo "Processing $file"
    root -l -n -b -q "analyzeTrees.cpp(\"$file\")"
done

# run all other macros and produce outputs to pdfs/
root -l -n -b -q plotHists.cpp
root -l -n -b -q plotAll.cpp
root -l -n -b -q plot5Gev.cpp
root -l -n -b -q plotEfficiency.cpp

# a macro, which was used to compare the reconstructed energies for two different sampling fractions
#root -l -n -b -q energyComparison.cpp