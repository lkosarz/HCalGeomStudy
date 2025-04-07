# ePICRecoDataAnalysis
Analysis of ePIC simulated data. The code is written so that it can be easily converted between 3 different data reading modes:
- ROOT trees
- `podio::ROOTReader`
- `podio::ROOTFrameReader` (to be deprecated in podio v1.0)
- `podio::EventStore` (abandoned)

### To run interactively:

```Sh
root -l -b -q readFrameRootSim.C+ | tee run.log
```

Old:

```Sh
root -l -b -q readTreeSim.C+ | tee run.log
```

### To compile executable:

```Sh
make
```

and Run:

```Sh
./readFrameRootSimMain | tee run.log
```

### Batch scripts to use condor on RCF

```Sh
submitSimEne.job
runSimBatchEne.sh
```
Submit with:

```Sh
condor_submit submitSimEne.job
```

### Python version

You can use `ipython3` to have interactive `python` and autocomplete feauture

```Sh
python readEvents.py
```


### How To contribute

Integrate your codes by adding a header file with histograms. Add implementation in the analysis macro (preferably in a separate method within the code). Test the code!


### TO DO
1. Add more histograms and functionality
2. Add macros for drawing histograms