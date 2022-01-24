#ifndef ELEMENTLIST_H
#define ELEMENTLIST_H


class ElementList {
	private:
		uint32_t num_elems;
		uint32_t cur_elems;
		class Element ** elems;

	public:
		ElementList(uint32_t);
		~ElementList();

		void insert_element(class Element *);
		void eval_elems();
};

#endif // ELEMENTLIST_H
