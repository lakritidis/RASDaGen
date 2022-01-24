#include "Voter.h"

/// Constructor 1 : default
Voter::Voter() {
	this->name = NULL;
	this->weight = 0.0;
}

/// Constructor 2
Voter::Voter(char * n, double w) {
	this->name = new char[strlen(n) + 1];
	strcpy(this->name, n);

	this->weight = w;
}

/// Destructor
Voter::~Voter() {
	if (this->name) {
		delete [] this->name;
	}
}

void Voter::display() {
	printf("Voter Name: %s - Weight: %5.3f\n", this->name, this->weight);
}

/// Create the submission file for this voter
void Voter::create_submission_file(uint32_t K, uint32_t Q, class ElementsPool<Element> ** pools, char * path, char * ds, char * track) {
	uint32_t q = 0, k = 0;

	char buffer[1024];
	sprintf(buffer, "%s/%s/%s_%s_Input/%s_%s_%s.txt", path, ds, ds, track, ds, track, this->name);

	FILE * datafile = fopen(buffer, "w");
	if (datafile) {

		for (q = 0; q < Q; q++) {

			pools[q]->shuffle();

			for (k = 0; k < K; k++) {
				pools[q]->get_element(k)->setWeight(  pools[q]->get_element(k)->getWeight() + K - k);
//				printf("Item: %s ranking in list %d = %d. Current score = %5.2f\n",
//						pools[q]->get_element(k)->getId(), q, k, pools[q]->get_element(k)->getWeight());

				fprintf(datafile, "%d\tQ0\t%s\t%d\t%6.5f\t%s%s\n",
					q + 1, pools[q]->get_element(k)->getId(), k + 1, (weight_t)(K - k) / K, ds, track);
			}
		}

		fclose(datafile);

	} else {
		printf("Error creating dataset file\n");
	}
//	getchar();
}


/// Mutators
inline void Voter::set_name(char * v) {
	this->name = new char[strlen(v) + 1];
	strcpy(this->name, v);
}
inline void Voter::set_weight(double v) { this->weight = v; }

/// Accessors
inline char * Voter::get_name() { return this->name; }
inline double Voter::get_weight() { return this->weight; }
