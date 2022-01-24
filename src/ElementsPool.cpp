#include "ElementsPool.h"

template<class T> ElementsPool<T>::ElementsPool(uint32_t n, uint32_t q) {
	this->query = q;
	this->num_elements = n;
	this->elements = new T * [n];
//	char tmp[1024];

	for (uint32_t i = 0; i < this->num_elements; i++) {
//		sprintf(tmp, "Q%d-E%d", q + 1, i + 1);
		this->elements[i] = new T();
	}
}

template<class T> ElementsPool<T>::~ElementsPool() {
	for (uint32_t i = 0; i < this->num_elements; i++) {
		delete this->elements[i];
	}
	delete [] this->elements;
}

template<class T> void ElementsPool<T>::create_dummy() {
	char buffer[1024];

	for (uint32_t i = 0; i < this->num_elements; i++) {
		sprintf(buffer, "Q%d-E%d", this->query + 1, i + 1);
		this->elements[i]->setId(buffer);
		this->elements[i]->setWeight(0.0);
	}
}

template<class T> void ElementsPool<T>::shuffle() {
	uint32_t currentIndex = this->num_elements;
	uint32_t randomIndex = 0;
	T * tmp = 0;

	while (currentIndex != 0) {
		/// Pick a remaining element...
		randomIndex = floor(rand() % currentIndex);
//		printf("Random Index: %d\n", randomIndex);
		currentIndex--;

		/// And swap it with the current element.
		tmp = this->elements[currentIndex];
		this->elements[currentIndex] = this->elements[randomIndex];
		this->elements[randomIndex] = tmp;
	}
}

template<class T> void ElementsPool<T>::compute_element_scores
	(uint32_t M, uint32_t K, weight_t bias, weight_t threshold, FILE * eval_file) {

		weight_t score = 0.0;
		uint32_t rel = 0;
		uint32_t prob1 = 10 - ceil(bias), prob2 = floor(bias);

		for (uint32_t i = 0; i < this->num_elements; i++) {
			score = rand() % prob1 + (prob2 * this->elements[i]->getWeight()) / (double)(M * K);
	//		score = rand() % 10;

			this->elements[i]->setWeight( score );

			if (score > threshold) {
				rel = 1;
			} else {
				rel = 0;
			}
			fprintf(eval_file, "%d\t0\t%s\t%d\n", this->query + 1, this->elements[i]->getId(), rel);
		}
//getchar();
}

template<class T> void ElementsPool<T>::display() {
	printf("Displaying pool for Query %d...\n", this->query);
	for (uint32_t i = 0; i < this->num_elements; i++) {
		this->elements[i]->display();
	}
	printf("\n\n");
}

template<class T> T * ElementsPool<T>::get_element(uint32_t i) {
	return this->elements[i];
}
