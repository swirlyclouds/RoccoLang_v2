#pragma once
template <class T>
class Iterator
{
	std::vector<T> objects;
	void fill() {
		if (ptr > (objects.size() - 1)) {
			next = NULL;
		}
		else next = &objects[ptr];
		if (ptr >= (objects.size() - 1)) {
			end = true;
			++ptr;
			return;
		}
		++ptr;
	}

public:
	unsigned int ptr;
	bool end = false;
	T* next;
	Iterator(std::vector<T> objs) : objects(objs) {
		ptr = 0;
		fill();
	}
	T* move_next() {
		T* retval = next;
		fill();
		return retval;
	}
};

class StringIter {
public:
	std::string str;
	char next;
	unsigned int ptr;
	bool end = false;	
	StringIter(std::string str) : str(str) {
		ptr = 0;
		fill();
	}
	void fill() {
		next = str[ptr];
		if (ptr >= str.size()) {
			end = true;
			return;
		}
		++ptr;
	}
	char move_next() {
		char retval = next;
		fill();
		return retval;
	}
};