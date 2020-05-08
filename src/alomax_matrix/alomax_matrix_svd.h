#ifndef ALOMAX_MATRIX_SVD_H
#define ALOMAX_MATRIX_SVD_H

/*
 * Written by Anthony Lomax <anthony@alomax.net, http://www.alomax.net>
 *
 */

#include "alomax_matrix.h"

void clean_SingularValueDecomposition();
void SingularValueDecomposition(MatrixDouble A_matrix, int nrows, int ncolumns);
double svd_cond();
MatrixDouble svd_getS();
VectorDouble svd_getSingularValues();
MatrixDouble svd_getU();
MatrixDouble svd_getV();
double svd_norm2();
int svd_rank();

void svd_helper(MatrixDouble A_matrix, int num_rows, int num_cols, VectorDouble S_vector, MatrixDouble V_matrix);

#endif //ALOMAX_MATRIX_SVD_H
