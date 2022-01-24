#include "stdio.h"
#include "stdlib.h"
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <dirent.h>
#include <assert.h>
#include <string>
#include <vector>

typedef double weight_t;

#include "src/Element.cpp"
#include "src/ElementsPool.cpp"
#include "src/Voter.cpp"


int main(int argc, char** argv) {
	uint32_t q = 0, m = 0;

	char BASE_PATH[] = "/media/leo/B65266EC5266B1331/phd_Research/08 - Datasets/TREC";
	char DATASET_NAME[] = "Synthetic";

	char buffer [1024];
	uint32_t Q = 20;		/// Number of queries

	/// FESO dataset; FEw ShOrt Lists
/*
	char DATASET_TRACK[] = "FESO";

	uint32_t M = 10;		/// Number of lists (voters) to create
	uint32_t K = 30;		/// The length of the voter lists (top-k lists)
	uint32_t N = 30;		/// The size of the pool of elements
	weight_t bias = 3.0;
	weight_t threshold = 7.0;
*/
	/// FELO dataset; FEw LOng Lists

	char DATASET_TRACK[] = "MASO";
	uint32_t M = 1000;		/// Number of lists (voters) to create
	uint32_t K = 30;		/// The length of the voter lists (top-k lists)
	uint32_t N = 30;		/// The size of the pool of elements
	weight_t bias = 3.0;
	weight_t threshold = 5.0;


	class ElementsPool<Element> ** POOLS = new ElementsPool<Element> * [Q];
	for (q = 0; q < Q; q++) {
		POOLS[q] = new ElementsPool<Element>(N, q);
		POOLS[q]->create_dummy();
	}

/*
	for (q = 0; q < Q; q++) {
		POOLS[q]->display();

		printf("\nShuffled list:\n");
		POOLS[q]->shuffle();
		POOLS[q]->display();
	}
*/

	class Voter ** VOTERS = new Voter * [M];
	for (m = 0; m < M; m++) {
		sprintf(buffer, "V-%d", m);
		VOTERS[m] = new Voter(buffer, 1.0);
		VOTERS[m]->create_submission_file(K, Q, POOLS, BASE_PATH, DATASET_NAME, DATASET_TRACK);
	}

	sprintf(buffer, "%s/%s/%s_%s_prels", BASE_PATH, DATASET_NAME, DATASET_NAME, DATASET_TRACK);
	FILE * eval_file = fopen(buffer, "w");

	if(!eval_file) {
		printf("Error creating evaluation file");
		return -1;
	}

	for (q = 0; q < Q; q++) {
		POOLS[q]->compute_element_scores(M, K, bias, threshold, eval_file);
	}

	fclose(eval_file);


	for (q = 0; q < Q; q++) {
		delete POOLS[q];
	}
	delete [] POOLS;

	for (m = 0; m < M; m++) {
		delete VOTERS[m];
	}
	delete [] VOTERS;

	return 1;
}
