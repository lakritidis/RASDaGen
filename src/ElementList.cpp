#include "ElementList.h"

ElementList::ElementList(uint32_t K) {
	this->cur_elems = 0;
	this->num_elems = K;
	this->elems = new Element * [K];
}

ElementList::~ElementList() {
	delete [] this->elems;
}

void ElementList::insert_element(class Element * elem) {
	this->elems[this->cur_elems++] = elem;
}
