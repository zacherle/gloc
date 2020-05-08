#ifndef RAN1_H
#define RAN1_H

double get_rand_double(const double xmin, const double xmax);
int get_rand_int(const int imin, const int imax);
void test_rand_int();

#define SRAND_FUNC(x) rinit((int) x)

void rinit(int ijkl);

#endif //RAN1_H
