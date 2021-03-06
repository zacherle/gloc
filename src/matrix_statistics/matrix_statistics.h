#ifndef MATRIX_STATISTICS_H
#define MATRIX_STATISTICS_H

/***************************************************************************
 * matrix_statistics.h:
 *
 * TODO: add doc
 *
 * Written by Anthony Lomax
 *   ALomax Scientific www.alomax.net
 *
 * modified: 2010.12.16
 ***************************************************************************/


#include "../geometry/geometry.h"


#define CONFIDENCE_LEVEL 68.0   // 68% confidence level used throughout

// 2D ellipse

typedef struct {
    double az1, len1;   // semi-minor axis km
    double len2;   // semi-major axis km
} Ellipse2D;
#define DELTA_CHI_SQR_68_2 2.30    // value for 68% conf (see Num Rec, 2nd ed, sec 15.6, table)


// 3D ellipsoid

typedef struct {
    double az1, dip1, len1;   // semi-minor axis km
    double az2, dip2, len2;   // semi-intermediate axis km
    double len3;   // semi-major axis km
    double az3, dip3;   // 20150601 AJL - semi-major axis az and dip added to support conversion to QuakeML Tait-Bryan representation
} Ellipsoid3D;
#define DELTA_CHI_SQR_68_3 3.53    // value for 68% conf (see Num Rec, 2nd ed, sec 15.6, table)



char *get_matrix_statistics_error_mesage();
Vect3D CalcExpectationSamples(float*, int);
Mtrx3D CalcCovarianceSamplesRect(float* fdata, int nSamples, Vect3D* pexpect);
Mtrx3D CalcCovarianceSamplesGlobal(float* fdata, int nSamples, Vect3D* pexpect);
Ellipsoid3D CalcErrorEllipsoid(Mtrx3D *, double);
Ellipse2D CalcHorizontalErrorEllipse(Mtrx3D *pcov, double del_chi_2);
void ellipsiod2Axes(Ellipsoid3D *, Vect3D *, Vect3D *, Vect3D *);
int nllEllipsiod2QMLConfidenceEllipsoid(Ellipsoid3D *pellipsoid,
        double* psemiMajorAxisLength,
        double* psemiMinorAxisLength,
        double* psemiIntermediateAxisLength,
        double* pmajorAxisAzimuth,
        double* pmajorAxisPlunge,
        double* pmajorAxisRotation);


#ifdef NLL_DEAD_CODE
Mtrx3D CalcCovarianceSamplesGlobalWeighted(float* fdata, int nSamples, Vect3D* pexpect);
Vect3D CalcExpectationSamplesGlobal(float* fdata, int nSamples, double xReference);
Vect3D CalcExpectationSamplesGlobalWeighted(float* fdata, int nSamples, double xReference);
Vect3D CalcExpectationSamplesWeighted(float* fdata, int nSamples);
void nllEllipsiod2XMLConfidenceEllipsoid(Ellipsoid3D *pellipsoid,
        double* psemiMajorAxisLength, double* pmajorAxisPlunge, double* pmajorAxisAzimuth,
        double* psemiIntermediateAxisLength, double* pintermediateAxisPlunge, double* pintermediateAxisAzimuth,
        double* psemiMinorAxisLength);
#endif //NLL_DEAD_CODE

#endif //MATRIX_STATISTICS_H
