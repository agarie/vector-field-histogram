/* Polar histogram. */
struct hist {
	int alpha;
	int sectors;
	double threshold;
	double damping_constant;
	double density_a;
	double density_b;
	int * densities;
};

typedef struct hist hist_t;

/* Polar Histogram. */

/* hist_init: Return a pointer to a new hist. NULL otherwise. */
hist_t * hist_init(int alpha, double threshold, double density_a,
	double density_b);

/* hist_update: Update hist with grid's information. */
void hist_update(hist_t * hist, grid_t * grid);
