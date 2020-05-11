#ifndef NLLOCLIB_H
#define NLLOCLIB_H

/*
 * Copyright (C) 1999-2010 Anthony Lomax <anthony@alomax.net, http://www.alomax.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser Public License for more details.

 * You should have received a copy of the GNU Lesser Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.

 */


/*-----------------------------------------------------------------------
Anthony Lomax
Anthony Lomax Scientific Software
161 All?e du Micocoulier, 06370 Mouans-Sartoux, France
tel: +33(0)493752502  e-mail: anthony@alomax.net  web: http://www.alomax.net
-------------------------------------------------------------------------*/


/*  NLLocLib.h

        include file for program NLLoc, NLDiffLoc

 */


//#include "GridLib.h"
#include "velmod.h"
#include "loclist.h"
#include "otime_limit.h"
#include "alomax_matrix/alomax_matrix.h"




/*------------------------------------------------------------*/
/* structures */

/* gaussian errors location parameters */

/*	see (TV82, eq. 10-14; MEN92, eq. 22) */
typedef struct {
    double SigmaT; /* theoretical error coeff for travel times */
    double CorrLen; /* model corellation length */
    MatrixDouble EDTMtrx; /* EDT covariance (row=col) or correlation (row!=col) matrix */
    MatrixDouble WtMtrx; /* weight matrix */
    double WtMtrxSum; /* sum of elements of weight matrix */
    long double meanObs; /* weighted mean of obs arrival times */
    double meanPred; /* weighted mean of predicted travel times */
    double arrivalWeightMax; /* maximum station (row) weight */
}
GaussLocParams;

/* gaussian error travel time parameters */
typedef struct {
    double SigmaTfraction; /* fraction of travel times to use as travel times error */
    double SigmaTmin; /* minimum travel times error */
    double SigmaTmax; /* maximum travel times error */
}
Gauss2LocParams;

/* scatter paramters */
typedef struct {
    int npts; /* number of scatter points */
}
ScatterParams;

/* station/inst/component parameters */
typedef struct {
    char label[ARRIVAL_LABEL_LEN]; /* label (i.e. station name) */
    char inst[INST_LABEL_LEN]; /* instrument */
    char comp[COMP_LABEL_LEN]; /* component */
    double amp_fact_ml_hb; /* amplitude scale factor */
    double sta_corr_ml_hb; /* station correction */
    double sta_corr_md_fmag; /* station correction MD_FMAG */
}
CompDesc;

/* station label alias */
typedef struct {
    char name[ARRIVAL_LABEL_LEN]; /* original label (i.e. station name) */
    char alias[ARRIVAL_LABEL_LEN]; /* alias, i.e. new label */
    int byr, bmo, bday; /* begin year, month, day of validity */
    int eyr, emo, eday; /* end year, month, day of validity */
}
AliasDesc;

/* excluded phase desc */
typedef struct {
    char label[ARRIVAL_LABEL_LEN]; /* label (i.e. station name) */
    char phase[ARRIVAL_LABEL_LEN]; /* phase */
}
ExcludeDesc;

/* time delays */
typedef struct {
    char label[ARRIVAL_LABEL_LEN];
    char phase[ARRIVAL_LABEL_LEN];
    int n_residuals;
    double delay; /* time delay (sec) */
    double std_dev; /* std dev of time delay (sec) */
}
TimeDelayDesc;



/* Event time information extracted from filename or hypocenter line in obs file */

/*  SH 03/05/2004  added event number ev_nr which is used by SED_LOC format */
typedef struct {
    int ev_nr;
    int year, month, day;
    int hour, min;
    double sec;
}
EventTimeExtract;



/* Octtree */

#define OCTREE_UNDEF_VALUE -VERY_SMALL_DOUBLE

typedef struct {
    int init_num_cells_x, init_num_cells_y, init_num_cells_z;
    // num nodes for each side of initial Tree3D
    double min_node_size; // size of smallest side of smallest allowed node
    int max_num_nodes; // maximum number of nodes to evaluate
    int num_scatter; // number of scatter points to output
    int use_stations_density; // if 1, weight oct node order in result tree by station density in node
    int stop_on_min_node_size; // if 1, stop search when first min_node_size reached, if 0 stop subdividing a given cell when min_node_size reached
    double mean_cell_velocity; // mean cell velocity (>0 = Increases misfit sigma in proportion to travel time across diagonal of cell.
}
OcttreeParams;

/* Metropolis */
typedef struct {
    double x, y, z;
    long double dt;
    double dx;
    double likelihood;
    double velocity;
    double initial_temperature;
}
WalkParams;

/* Magnitude */
typedef struct {
    int type; /* magnitude calculation method */

    /* ML - Hutton & Boore, BSSA, v77, n6, Dec 1987 */
    double amp_fact_ml_hb; /* amplitude scale factor */
    double hb_n; /* "n" in H&B eq. (2) */
    double hb_K; /* "K" in H&B eq. (2) */
    double hb_Ro; /* reference distance "100" in H&B eq. (2) */
    double hb_Mo; /* reference magnitude "3.0" in H&B eq. (2) */

    /* coda duration (FMAG) - HYPOELLIPSE users manual chap 4;
            Lee et al., 1972; Lahr et al., 1975; Bakun and Lindh, 1977 */
    double fmag_c1, fmag_c2, fmag_c3, fmag_c4, fmag_c5;
}
MagDesc;



/*------------------------------------------------------------*/
/* globals  */

/* output file path  */
extern char f_outpath[FILENAME_MAX];

/* Gaussian error parameters */
extern GaussLocParams Gauss;
extern Gauss2LocParams Gauss2;
extern int iUseGauss2;

/* Scatter parameters */
extern ScatterParams Scatter;


/* events */
extern int NumEvents;
extern int NumEventsLocated;
extern int NumLocationsCompleted;

#define MAX_NUM_OBS_FILES 10000
extern int NumObsFiles;

/* number of arrivals read from obs file */
extern int NumArrivalsRead;

/* number of arrivals used for location */
extern int NumArrivalsLocation;

/* observations filenames */
extern char fn_loc_obs[MAX_NUM_OBS_FILES][FILENAME_MAX];
/* filetype */
extern char ftype_obs[MAXLINE];

/* filenames */
extern char fn_loc_grids[FILENAME_MAX], fn_path_output[FILENAME_MAX];
extern int iSwapBytesOnInput;

// model files
extern FILE *fp_model_grid_P;
extern FILE *fp_model_hdr_P;
extern GridDesc model_grid_P;
extern FILE *fp_model_grid_S;
extern FILE *fp_model_hdr_S;
extern GridDesc model_grid_S;

/* location search type (grid, simulated annealing, Metropolis, etc) */
#define SEARCH_GRID  	0
#define SEARCH_MET  	1
#define SEARCH_OCTTREE  2
extern int SearchType;

/* location method (misfit, etc) */
#define METH_UNDEF  		0
#define METH_GAU_ANALYTIC  	1
#define METH_GAU_TEST  		2
#define METH_EDT  		3
#define METH_EDT_BOX  		4
#define METH_ML_OT  		5
#define METH_OT_STACK  		6
#define METH_L1_NORM  		7         // 20140515 AJL - added for NLDiffLoc
extern int LocMethod;
extern int EDT_use_otime_weight;
extern int EDT_otime_weight_active;
extern double DistStaGridMin;
extern double DistStaGridMax;
extern int MinNumArrLoc;
extern int MaxNumArrLoc;
extern int MinNumSArrLoc;
extern double VpVsRatio;

/* location signature */
extern char LocSignature[MAXLINE_LONG];

/* location grids */
#define MAX_NUM_LOCATION_GRIDS 10
extern GridDesc LocGrid[MAX_NUM_LOCATION_GRIDS];
extern int NumLocGrids;
extern int LocGridSave[MAX_NUM_LOCATION_GRIDS]; /* !should be in GridDesc */
//extern int Num3DGridReadToMemory, MaxNum3DGridMemory;

/* related flags */
extern int iWriteHypHeader[MAX_NUM_LOCATION_GRIDS];

/* format specific event data */
extern char HypoInverseArchiveSumHdr[MAXLINE_LONG];

/* hypocenter filetype saving flags */
/* SH 02/26/2004  added iSaveSnapSum for output to be read
    by SNAP */
extern int iSaveNLLocEvent, iSaveNLLocSum, iSaveNLLocOctree,
iSaveHypo71Event, iSaveHypo71Sum,
iSaveHypoEllEvent, iSaveHypoEllSum,
iSaveHypoInvSum, iSaveHypoInvY2KArc, iSaveAlberto4Sum, iSaveFmamp,
iSaveSnapSum, iCalcSedOrigin, iSaveDecSec, iSaveNone;
// 20170811 AJL - added to allow saving of expectation hypocenter results instead of maximum likelihood
extern int iSaveNLLocExpectation;


// Arrival prior weighting flag (NLL_FORMAT_VER_2)
extern int iUseArrivalPriorWeights;

/* station distance weighting flag. */
extern int iSetStationDistributionWeights;
extern double stationDistributionWeightCutoff;

/* station density weghting */
extern double AveInterStationDistance;
extern int NumForceOctTreeStaDenWt;

extern int iRejectDuplicateArrivals;

/* Event Information extracted from phase file */
extern EventTimeExtract EventTime;
extern long int EventID;

/* magnitude calculation */
#define MAG_UNDEF  	0
#define MAG_ML_HB  	1
#define MAG_MD_FMAG  	2
extern int NumMagnitudeMethods;
#define MAX_NUM_MAG_METHODS  	2
extern MagDesc Magnitude[MAX_NUM_MAG_METHODS];

/* station/inst/component parameters */
#define MAX_NUM_COMP_DESC 1000
extern CompDesc Component[MAX_NUM_COMP_DESC];
extern int NumCompDesc;

/* arrival label alias */
#define MAX_NUM_LOC_ALIAS 1000
#define MAX_NUM_LOC_ALIAS_CHECKS 2*MAX_NUM_LOC_ALIAS
extern AliasDesc LocAlias[MAX_NUM_LOC_ALIAS];
extern int NumLocAlias;

/* exclude arrivals */
#define MAX_NUM_LOC_EXCLUDE 1000
extern ExcludeDesc LocExclude[MAX_NUM_LOC_EXCLUDE];
extern int NumLocExclude;

/* station delays */
#define WRITE_RESIDUALS 0
#define WRITE_RES_DELAYS 1
#define WRITE_PDF_RESIDUALS 2
#define WRITE_PDF_DELAYS 3
#define MAX_NUM_STA_DELAYS 10000
extern TimeDelayDesc TimeDelay[MAX_NUM_STA_DELAYS];
extern int NumTimeDelays;

extern char TimeDelaySurfacePhase[MAX_SURFACES][PHASE_LABEL_LEN];
extern double TimeDelaySurfaceMultiplier[MAX_SURFACES];
extern int NumTimeDelaySurface;

/* crustal and elev corrections */
extern int ApplyElevCorrFlag;
extern double ElevCorrVelP;
extern double ElevCorrVelS;
extern int ApplyCrustElevCorrFlag;
extern double MinDistCrustElevCorr;

/* topo surface */
extern struct surface *topo_surface;
extern int topo_surface_index; // topo surface index is velmod.h.MAX_SURFACES-1 so as not to interferce with any TimeDelaySurfaces read in

/* station list */
extern int NumStations;
extern SourceDesc StationList[X_MAX_NUM_ARRIVALS];

/* fixed origin time parameters */
extern int FixOriginTimeFlag;

/* Metropolis */
extern WalkParams Metrop; /* walk parameters */
extern int MetNumSamples; /* number of samples to evaluate */
extern int MetLearn; /* learning length in number of samples for
					calculation of sample statistics */
extern int MetEquil; /* number of samples to equil before using */
extern int MetStartSave; /* number of sample to begin saving */
extern int MetSkip; /* number of samples to wait between saves */
extern double MetStepInit; /* initial step size (km) (< 0.0 for auto) */
extern double MetStepMin; /* minimum step size (km) */
extern double MetStepMax; /* maximum step size (km) (NLDiffLoc) */
extern double MetStepFact; /* step size factor */
extern double MetProbMin; /* minimum likelihood necessary after learn */
extern double MetVelocity; /* velocity for conversion of distance to time */
extern double MetInititalTemperature; /* initial temperature */
extern int MetUse; /* number of samples to use
					= MetNumSamples - MetEquil */


/* Octtree */
extern OcttreeParams octtreeParams; /* Octtree parameters */
extern Tree3D* octTree; /* Octtree */
extern ResultTreeNode* resultTreeRoot; /* Octtree likelihood*volume results tree root node */
//extern ResultTreeNode* resultTreeLikelihoodRoot;	/* Octtree likelihood results tree root node */


/* take-off angles */
extern int angleMode; /* angle mode - ANGLE_MODE_NO, ANGLE_MODE_YES */
extern int iAngleQualityMin; /* minimum quality for angles to be used */
#define ANGLE_MODE_NO     0
#define ANGLE_MODE_YES    1
#define ANGLE_MODE_UNDEF -1


/* otime list */
extern OtimeLimit** OtimeLimitList;
extern int NumOtimeLimit;

/* maxumum residual values to include in statistics */
extern int NRdgs_Min;
extern double RMS_Max, Gap_Max;
extern double P_ResidualMax;
extern double S_ResidualMax;
extern double Ell_Len3_Max;
extern double Hypo_Depth_Min;
extern double Hypo_Depth_Max;
extern double Hypo_Dist_Max;


/*------------------------------------------------------------*/
/* hashtable function declarations */
int FreeStaStatTable(int ntable);
int WriteStaStatTable(int, FILE *, double, int, double,
        double, double, double, double, double, double, int);

/*------------------------------------------------------------*/
/* function declarations */

int NLLoc(char *pid_main, char *fn_control_main, char **param_line_array, int n_param_lines, char **obs_line_array, int n_obs_lines,
        int return_locations, int return_oct_tree_grid, int return_scatter_sample, LocNode **ploc_list_head);

int Locate(int ngrid, char* fn_loc_obs, char* fn_root_out, int numArrivalsReject, int return_locations, int return_oct_tree_grid, int return_scatter_sample, LocNode **ploc_list_head);

int checkObs(ArrivalDesc *arrival, int nobs);
int ExtractFilenameInfo(char*, char*);
int ReadNLLoc_Input(FILE* fp_input, char **param_line_array, int n_param_lines);
int GetNLLoc_Grid(char*);
int GetNLLoc_HypOutTypes(char*);
int GetPhaseID(char*);
int GetStaWeight(char* line1);
int GetNLLoc_Gaussian(char*);
int GetNLLoc_Gaussian2(char*);
int GetNLLoc_PhaseStats(char*);
int GetNLLoc_Angles(char*);
int GetNLLoc_Magnitude(char*);
int GetNLLoc_Files(char*);
int GetNLLoc_Method(char*);
int GetNLLoc_SearchType(char*);
int GetNLLoc_FixOriginTime(char*);
int GetObservations(FILE*, char*, char*, ArrivalDesc*, int*, int*, int*, int, HypoDesc*, int*, int*, int);
int GetNextObs(HypoDesc* phypo, FILE*, ArrivalDesc *, char*, int);
int IsGoodDate(int, int, int);
int ReadArrivalSheets(int, ArrivalDesc*, double);
int IsSameArrival(ArrivalDesc *, int, int, char *);
int IsDuplicateArrival(ArrivalDesc *, int, int, int);
int FindDuplicateTimeGrid(ArrivalDesc *arrival, int num_arrivals, int ntest);

int WriteHypo71(FILE *, HypoDesc* , ArrivalDesc* , int , char* , int , int );
int WriteHypoEll(FILE *, HypoDesc* , ArrivalDesc* , int , char* , int , int );
int WriteHypoInverseArchive(FILE *fpio, HypoDesc *phypo, ArrivalDesc *parrivals, int narrivals,
        char *filename, int writeY2000, int write_arrivals, double arrivalWeightMax);
int WriteHypoAlberto4(FILE *, HypoDesc* , ArrivalDesc* , int , char* );
int WriteHypoFmamp(FILE *fpio, HypoDesc* phypo, ArrivalDesc* parrivals, int narrivals, char* filename, int write_header);
int OpenSummaryFiles(char *, char *);
int CloseSummaryFiles();

int GetCompDesc(char*);
int GetLocAlias(char*);
int GetLocExclude(char* line1);
int GetTimeDelays(char*);
int GetTimeDelaySurface(char*);

int GetTopoSurface(char*);

int LocGridSearch(int, int, int, ArrivalDesc*, GridDesc*,
        GaussLocParams*, HypoDesc*);
int LocMetropolis(int, int, int, ArrivalDesc *,
        GridDesc*, GaussLocParams*, HypoDesc*, WalkParams*, float*);
int SaveBestLocation(OctNode* poct_node, int num_arr_total, int num_arr_loc, ArrivalDesc *arrival,
        GridDesc* ptgrid, GaussLocParams* gauss_par, HypoDesc* phypo,
        double misfit_max, int iGridType, int ignore_pred_travel_time_best,
        double cell_diagonal_time_var_best, double cell_diagonal_best, double cell_volume_best);
int ConstWeightMatrix(int, ArrivalDesc*, GaussLocParams*);
int CleanWeightMatrix();
void CalcCenteredTimesObs(int, ArrivalDesc*, GaussLocParams*, HypoDesc*);
void CalcCenteredTimesPred(int, ArrivalDesc*, GaussLocParams*);
double CalcSolutionQuality(OctNode* poct_node, int num_arrivals, ArrivalDesc *arrival, GaussLocParams* gauss_par, int itype,
        double* pmisfit, double* potime, double* potime_var, double cell_diagonal_time_var, double cell_diagonal, double cell_volume, double* effective_cell_size, double *pot_variance_factor);
double CalcSolutionQuality_GAU_ANALYTIC(int, ArrivalDesc*, GaussLocParams*, int, double*, double*);
double CalcSolutionQuality_GAU_TEST(int, ArrivalDesc*, GaussLocParams*, int, double*, double*);
double CalcSolutionQuality_L1_NORM(int num_arrivals, ArrivalDesc *arrival,
        GaussLocParams* gauss_par, int itype, double* pmisfit, double* potime);
double CalcSolutionQuality_EDT(int num_arrivals, ArrivalDesc *arrival, GaussLocParams* gauss_par, int itype, double* pmisfit, double* potime, double* potime_var, double cell_diagonal_time_var, int method_box);
double CalcSolutionQuality_OT_STACK(OctNode* poct_node, int num_arrivals, ArrivalDesc *arrival,
        GaussLocParams* gauss_par, int itype, double* pmisfit, double* potime, double* potime_var,
        double cell_half_diagonal_time_range, double cell_diagonal, double cell_volume, double* effective_cell_size, double *pot_variance_factor);
double CalcSolutionQuality_ML_OT(int num_arrivals, ArrivalDesc *arrival, GaussLocParams* gauss_par, int itype, double* pmisfit, double* potime, double* potime_var, double cell_diagonal_time_var, int method_box);
double calc_maximum_likelihood_ot_sort(
        OctNode* poct_node, int num_arrivals, ArrivalDesc *arrival,
        double cell_half_diagonal_time_range, double cell_diagonal, double cell_volume, double *pot_var, int icalc_otime,
        double *plog_prob_max, double *pot_stack_weight, double* effective_cell_size, double *pot_variance_factor);
double calc_maximum_likelihood_ot(double *ot_ml_arrival, double *ot_ml_arrival_edt_sum, int num_arrivals, ArrivalDesc *arrival, MatrixDouble edtmtx, double *pot_ml_var, int iwrite_errors,
        double *pprob_max);
double calc_likelihood_ot(double *ot_ml_arrival, double *ot_ml_arrival_edt_sum, int num_arrivals, ArrivalDesc *arrival, MatrixDouble edtmtx, double time);
double calc_variance_ot(double *ot_ml_arrival, double *ot_ml_arrival_edt_sum, int num_arrivals, ArrivalDesc *arrival, MatrixDouble edtmtx, double expectation_time);
long double CalcMaxLikeOriginTime(int, ArrivalDesc*, GaussLocParams*);
int NormalizeWeights(int num_arrivals, ArrivalDesc *arrival);
void UpdateProbabilisticResiduals(int, ArrivalDesc *, double);
int CalcConfidenceIntrvl(GridDesc*, HypoDesc*, char*);
int HomogDateTime(ArrivalDesc*, int, HypoDesc*);
int CheckAbsoluteTiming(ArrivalDesc *arrival, int num_arrivals);
int hypotime2hrminsec(long double phypo_time, int *phypo_hour, int *phypo_min, double *phypo_sec);
int StdDateTime(ArrivalDesc*, int, HypoDesc*);
int SetOutName(ArrivalDesc *arrival, char* out_file_root, char* out_file, char lastfile[FILENAME_MAX], int isec, int *pncount);
int SaveLocation(HypoDesc* hypo, int ngrid, char* fnobs, char *fnout, int numArrivalsReject,
        char* typename, int isave_phases, GaussLocParams* gauss_par);
int GenEventScatterGrid(GridDesc*, HypoDesc*, ScatterParams*, char*);
void InitializeArrivalFields(ArrivalDesc *);
int isExcluded(char *label, char *phase);
int EvaluateArrivalAlias(ArrivalDesc *);
int ApplyTimeDelays(ArrivalDesc *);
double ApplySurfaceTimeDelay(int nsurface, ArrivalDesc *arrival);
double CalcSimpleElevCorr(ArrivalDesc *arrival, int narr, double pvel, double svel);

double CalcAzimuthGap(ArrivalDesc *arrival, int num_arrivals, double *pgap_secondary);
double CalcArrivalDistances(ArrivalDesc *arrival, int num_arrivals, double *pmaximumDistance, double *pmedianDistance, int usedStationCount);
int CalcArrivalCounts(ArrivalDesc *arrival, int num_arrivals, int num_arrivals_read, int* passociatedPhaseCount, int* passociatedStationCount, int* pusedStationCount, int* pdepthPhaseCount);
void InitializeMetropolisWalk(GridDesc*, ArrivalDesc*, int,
        WalkParams*, int, double);
int GetNextMetropolisSample(WalkParams*, double, double,
        double, double, double, double, double*, double*, double*);
int MetropolisTest(double, double);

double CalculateVpVsEstimate(HypoDesc* phypo, ArrivalDesc* parrivals, int narrivals);

int CalculateMagnitude(HypoDesc*, ArrivalDesc*, int, CompDesc*, int, MagDesc*);
int findStaInstComp(ArrivalDesc* parr, CompDesc* pcomp, int nCompDesc);
double Calc_ML_HuttonBoore(double amplitude, double dist, double depth, double sta_corr,
        double hb_n, double hb_K, double hb_Ro, double hb_Mo);
double Calc_MD_FMAG(double coda_dur, double dist, double depth, double sta_corr,
        double fmag_c1, double fmag_c2, double fmag_c3, double fmag_c4, double fmag_c5);

int addToStationList(SourceDesc *stations, int numStations, ArrivalDesc *arrival, int nArrivals);
int WriteStationList(FILE*, SourceDesc*, int);
int setStationDistributionWeights(SourceDesc *stations, int numStations, ArrivalDesc *arrival, int nArrivals);

int getTravelTimes(ArrivalDesc *arrival, int num_arr_loc, double xval, double yval, double zval);
double applyCrustElevCorrection(ArrivalDesc* parrival, double xval, double yval, double zval);
int isAboveTopo(double xval, double yval, double zval);

Tree3D* InitializeOcttree(GridDesc* ptgrid, OcttreeParams* pParams);
int LocOctree(int ngrid, int num_arr_total, int num_arr_loc,
        ArrivalDesc *arrival,
        GridDesc* ptgrid, GaussLocParams* gauss_par, HypoDesc* phypo,
        OcttreeParams* pParams, Tree3D* pOctTree, float* fdata,
        double *poct_node_value_max, double *poct_tree_integral);
long double LocOctree_core(int ngrid, double xval, double yval, double zval,
        int num_arr_loc, ArrivalDesc *arrival,
        OctNode* poct_node,
        int icalc_cell_diagonal_time_var, double *volume_min,
        double *diagonal, double *cell_diagonal_time_var,
        OcttreeParams* pParams, GaussLocParams* gauss_par, int iGridType,
        double *misfit, double logWtMtrxSum);
double getOctTreeStationDensityWeight(OctNode* poct_node, SourceDesc *stations, int numStations, GridDesc *pgrid, int iOctLevelMax);
int GenEventScatterOcttree(OcttreeParams* pParams, double oct_node_value_max, float* fscatterdata, double integral, HypoDesc* Hypocenter);

int GetElevCorr(char* line1);

/*------------------------------------------------------------*/

#endif //NLLOCLIB_H
