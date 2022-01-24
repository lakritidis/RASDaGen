#include "Element.h"

Element::Element() {

}

Element::Element(char * x, weight_t w) {
	this->setId(x);
	this->weight = w;
}

Element::~Element() {
	delete [] this->id;
}

void Element::display() {
	printf("%s, ", this->id);
}

void Element::setId(char * v) {
	this->id = new char [strlen(v) + 1];
	strcpy(this->id, v);
}

void Element::setWeight(weight_t v) {
	this->weight = v;
}

char * Element::getId() { return this->id; }
weight_t Element::getWeight() { return this->weight; }
