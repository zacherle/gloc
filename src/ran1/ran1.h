
//depend: no




double get_rand_double(const double xmin, const double xmax);
int get_rand_int(const int imin, const int imax);
void test_rand_int();

#define SRAND_FUNC(x) rinit((int) x)

double uni(void);
void rstart(int i, int j, int k, int l);
void rinit(int ijkl);
