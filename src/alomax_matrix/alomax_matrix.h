#ifndef ALOMAX_MATRIX_H
#define ALOMAX_MATRIX_H

/*
 * Written by Anthony Lomax <anthony@alomax.net, http://www.alomax.net>
 *
 * Released into the Public Domain
 *
 */


typedef double**  MatrixDouble;
typedef double*  VectorDouble;


MatrixDouble matrix_double(int nrow, int ncol);
void free_matrix_double(MatrixDouble mtx, int nrow, int ncol);

VectorDouble vector_double(int nsize);
void free_vector_double(VectorDouble vect);
void display_matrix_double(char* name, MatrixDouble matrix, int num_rows, int num_cols);
int gauss_jordan(MatrixDouble matrix_double, int num_rows, int num_cols);
int matrix_double_inverse(MatrixDouble dmtx, int num_rows, int num_cols);

#ifdef NLL_DEAD_CODE
void display_vector_double(char* name, VectorDouble vect, int nsize);
int matrix_double_check_diagonal_non_zero_inverse(MatrixDouble mtx_original, int i_original_size, int verify_inverse, int verbose);
char *get_matrix_error_mesage();

int square_inverse_not_ok(MatrixDouble inverse_mtrx, MatrixDouble original_mtx, int nsize, int verbose);

int real_symmetric_eigen_helper(MatrixDouble A_matrix, int isize, VectorDouble S_vector, MatrixDouble V_matrix);
#endif //NLL_DEAD_CODE

#endif //ALOMAX_MATRIX_H
