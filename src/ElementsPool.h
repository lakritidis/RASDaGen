#ifndef ELEMENTSPOOL_H
#define ELEMENTSPOOL_H


template<class T> class ElementsPool {
	private:
		uint32_t query;
		uint32_t num_elements;
		T ** elements;

	public:
		ElementsPool(uint32_t, uint32_t);
		~ElementsPool();

		void create_dummy();
		void compute_element_scores(uint32_t, uint32_t, weight_t, weight_t, FILE *);

		void shuffle();
		void display();
		void create_evaluation_file();

		T * get_element(uint32_t);
};

#endif // ELEMENTSPOOL_H
