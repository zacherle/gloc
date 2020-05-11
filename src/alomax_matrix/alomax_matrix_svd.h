#ifndef ALOMAX_MATRIX_SVD_H
#define ALOMAX_MATRIX_SVD_H

/*
 * Written by Anthony Lomax <anthony@alomax.net, http://www.alomax.net>
 *
 */

#include "alomax_matrix.h"

void clean_SingularValueDecomposition();
void SingularValueDecomposition(MatrixDouble A_matrix, int nrows, int ncolumns);
VectorDouble svd_getSingularValues();
MatrixDouble svd_getV();

#ifdef NLL_DEAD_CODE
double svd_cond();
MatrixDouble svd_getS();
MatrixDouble svd_getU();
double svd_norm2();
int svd_rank();
#endif //NLL_DEAD_CODE

void svd_helper(MatrixDouble A_matrix, int num_rows, int num_cols, VectorDouble S_vector, MatrixDouble V_matrix);

#endif //ALOMAX_MATRIX_SVD_H
