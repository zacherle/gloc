# GLoc
**an adaptation of NonLinLoc**

NonLinLoc is a software package popular with seismologists, developed by A. Lomax.
It is a set of programs for locating earthquakes in 3D structures and for visualizing location results.

This repository is based on the source code of the last published distribution
[NLLbeta_src.tgz](http://alomax.free.fr/nlloc/softbeta/tar/NLLbeta_src.tgz) dated 2018-12-06.

The aim is to test the program and adapt it so that it can be used for earthquakes in the Czech Republic.
In particular, adaptation is needed for
 - map coordinates (Křovák EPSG:5514 )
 - newer GMT version
 - data format of seismic phases [hypo3d](https://github.com/firbas/hypo3d)

## Major program changes
Backward compatibility may be lost during editing.

### Code organization
1. Marginal programs deleted.   
   Only core programs from this distribution 
   (Vel2Grid, Grid2Time, Time2Angles, NLLoc, LocSum, Grid2GMT, Time2EQ 
   and their modules) are of interest.
   Most utilities and marginal programs with little chance of use have been deleted.
2. Declaration and definition of variables separated.   
   Programs use many global variables defined in header files.
   In order to find out which variables require an external link,
   the variables are defined in the code and declared in the header file
   (modules GridLib, GridMemLib, velmod, util, NLLocLib, GridGraphLib).
3. Header files enclosed by #include guards.
4. The dead code identified and enclosed in the #ifdef directive.

### Program functions
1. Grid2GMT5 works with GMT 5 version. 
   The new MAPLINE GMT_YX_K option is for Krovak map coordinates. 

## Documentation
Documentation of the original program is available on the
[A. Lomax website](http://alomax.free.fr/nlloc/)

Notes on using the programs can be found at [wiki pages](https://github.com/zacherle/gloc/wiki).
Comments on the procedures used are on the [web pages](https://zacherle.github.io/gloc).

