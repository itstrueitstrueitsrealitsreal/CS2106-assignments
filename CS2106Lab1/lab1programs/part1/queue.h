
// Maximum number of elements in a queue
//
#define MAX_Q_SIZE	10

// declare prototypes below

void enq(double);

double deq();

double sum(double, double);

double prod(double, double);

void clear_sum(double*);

void clear_prod(double*);

double reduce();

double flex_reduce(void (*)(double *), double (*)(double, double));