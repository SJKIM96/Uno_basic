#pragma once

class IsLess {
public:
	template<class T>
	static bool compare(const T& a, const T& b) { return a < b; }
};

class IsGreater {
public:
	template<class T>
	static bool compare(const T& a, const T& b) { return a > b; }
};

class IsLessDeref {
public:
	template<class T>
	static bool compare(const T& a, const T& b) {
		if (a == NULL) return false; // CONVENTION: NULL pointer is "greater" than other pointers 
		else if (b == NULL) return true; // NOTE: returns false is both pointers are NULL
		else return *a < *b; // for non NULL pointers we compare objects they point at
	}
};

class IsGreaterDeref {
public:
	template<class T>
	static bool compare(const T& a, const T& b) {
		if (b == NULL) return false; // CONVENTION: NULL pointer is "greater" than other pointers
		else if (a == NULL) return true;  // NOTE: returns false is both pointers are NULL
		else return *a > *b; // for non NULL pointers we compare objects they point at
	}
};

class IsEqual {
public:
	template<class T>
	static bool compare(const T& a, const T& b) { return a == b; }
};

class IsEqualDeref {
public:
	template<class T>
	static bool compare(const T& a, const T& b) {
		if (a == NULL || b == NULL) return false;  // CONVENTION: if at least one of the pointers is NULL
		// then the "objects" they point at are not equal
		else return (*a) == (*b); // for non NULL pointers we compare objects they point at
	}
};

