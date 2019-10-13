typedef struct {
	int n;		// pattern dimension
	int N;		// number of patterns
	double *x;	// Data patterns (1D array ; dimension N * n * sizeof(double)
	// Pattern i: x[ i*n ] ... x[ i*n + n - 1 ]
	int *t;		// Target values (0 or 1)
} Data;

int input_adult( char *, Data * );
int input_iris( char *, Data *, int );
int input_wdbc( char *, Data * );
int input_car( char *, Data *, int );