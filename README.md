# NonLinLoc redux

NonLinLoc is a software package popular with seismologists, developed by A. Lomax.
NonLinLoc is a set of programs for locating earthquakes in 3D structures and for visualizing location results.

This repository was initialized based on the source code from the last published distribution
[NLLbeta_src.tgz](http://alomax.free.fr/nlloc/softbeta/tar/NLLbeta_src.tgz) of 2018-12-06.
Only core programs (Vel2Grid, Grid2Time, Time2Angles, NLLoc, LocSum, Grid2GMT, Time2EQ ) from this distribution
are of interest. Most utilities and marginal programs have been deleted.

## Intentions
The program will be tested on earthquakes in the NE Czech Republic published in
[IPE-MONET earthquake catalog](https://www.researchgate.net/publication/323906777_IPE-MONET_EARTHQUAKE_CATALOG)

To test it the program needs to be adapted.   
In particular, adaptation is needed for
 - map coordinates (Křovák EPSG:5514 )
 - newer GMT version
 - data format of seismic phases identical to [hypo3d](https://github.com/firbas/hypo3d)

## Documentation
Documentation of the original program is available on the
[A. Lomax website](http://alomax.free.fr/nlloc/)
