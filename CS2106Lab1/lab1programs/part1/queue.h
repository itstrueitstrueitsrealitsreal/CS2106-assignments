
// Maximum number of elements in a queue
//
#define MAX_Q_SIZE	10

// declare prototypes below
void enq(double data);
double deq();
double sum(double x, double y);
double prod(double x, double y);
void clear_sum(double *acc);
void clear_prod(double *acc);
double reduce();
double flex_reduce(void (*clear)(double *), double (*op)(double, double));


