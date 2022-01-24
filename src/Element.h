#ifndef ELEMENT_H
#define ELEMENT_H

class Element {
	protected:
		char * id;
		weight_t weight;

	public:
		Element();
		Element(char *, weight_t);
		~Element();

		void display();

		char * getId();
		weight_t getWeight();

		void setId(char *);
		void setWeight(weight_t);
};

#endif // ELEMENT_H
