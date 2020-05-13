# GLoc
**an adaptation of NonLinLoc**

NonLinLoc is a software package popular with seismologists, developed by A. Lomax.
It is a set of programs for locating earthquakes in 3D structures and for visualizing location results.

This repository is based on the source code of the last published distribution
[NLLbeta_src.tgz](http://alomax.free.fr/nlloc/softbeta/tar/NLLbeta_src.tgz) dated 2018-12-06.

The aim is to understand this software and adapt it to work with local seismic data.  
In particular, adaptations are needed for
 - map coordinates (Křovák EPSG:5514 )
 - newer GMT version
 - phase-file data format [hypo3d](https://github.com/firbas/hypo3d)
We focus on the typical features of this software (location in the 3D model
in Cartesian coordinates and error characteristics). Features added for program complexity
(GLOBAL mode, number of I / O formats and map projections) can be suppressed when adapting the program.

## Major program changes
Backward compatibility may be lost during editing.

### Code reduction

The complexity of the program has been reduced for better clarity.

1. Marginal programs deleted.   
   Only core programs from this distribution 
   (Vel2Grid, Grid2Time, Time2Angles, NLLoc, LocSum, Grid2GMT, Time2EQ 
   and their modules) are of interest.
   Most utilities and marginal programs with little chance of use have been deleted.
   (v-0.2)
2. The dead code identified and deletod or enclosed in the #ifdef directive.
   (v0.3, v-0.8)
3. Input / output seismic formats.   
   There were a lot of input/output seismic formats that I never want to know.
   All you need is the native NLLOC_OBS format for input and NLL_FORMAT for output.
   (v-0.9)
<!--
4. Map projections
5. Processing methods
   2-D slices
  -->

### Code organization
1. Declaration and definition of variables separated.   
   Programs use many global variables defined in header files.
   In order to find out which variables require an external link,
   the variables are defined in the code and declared in the header file
   (modules GridLib, GridMemLib, velmod, util, NLLocLib, GridGraphLib).
   (v-0.4)
2. Header files enclosed by #include guards.
   (v-0.7)

### New functions
1. Grid2GMT5 works with GMT 5 version. 
   The new MAPLINE GMT_YX_K option is for Krovak map coordinates.
   (v-0.1)
2. NLLoc reads the [hypo3d] phase file format (LOCFILES HYPO3D option).
   

## Documentation
Documentation of the original program is available on the
[A. Lomax website](http://alomax.free.fr/nlloc/)

Notes on using the programs can be found at [wiki pages](https://github.com/zacherle/gloc/wiki).
Comments on the procedures used are on the [web pages](https://zacherle.github.io/gloc).

[hypo3d]: https://github.com/firbas/hypo3d
