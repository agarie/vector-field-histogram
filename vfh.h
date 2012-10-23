/* histogramGrid: Stores a histogram (certainty) grid. */
struct histogramGrid {
	short cells;
	float resolution;
	short *grid;
};

typedef struct histogramGrid histogramGrid_t;

/* histogramGridInit: Initialize hg to a full grid with all cells equal to 0. */
void histogramGridInit(histogramGrid_t * hg, short cells, float resolution);

/* polarHistogram: Stores a polar histogram. */
struct polarHistogram {
	short alpha;
	short sectors;
	int * obstacleDensities;
};

typedef struct polarHistogram polarHistogram_t;

/* polarHistogramInit: Update ph with hg's information. */
void polarHistogramInit(polarHistogram_t * ph, histogramGrid_t * hg, short alpha);

void polarHistogramUpdate(polarHistogram_t * ph, histogramGrid_t * hg);