#include <iostream>
#include <string>


void pass_by_copy_function(std::string str) {
	str = str + " world!";	// This is a copy, doesn't have any effect
}

void pass_by_pointer_function(std::string *str) {
	*str = *str + " world!";
}

void pass_by_reference_function(std::string &str) {
	str = str + " world!";
}

// one can define namespaces in order to create a separate environmnet for names
// for example
namespace mynamespace {
	void myfunction(){
		return;
	}

}

int main() {

	std::cout << "Hello world!" << std::endl;
		
	// one here could call
	mynamespace::myfunction();
	// or just use `using namespace mynamespace`

	// using namespace std;	// Not the best practice
	// it's not best practice because it looses the advantages of namespaces
	// such as separation etc
	// cout << "Hello world v2" << endl;


	// In C++ we have:
	// - pass-by-value (copy)
	// - pass-by-pointer (C-style)
	// - pass-by-reference (new in C++)
	//
	//? needs string inlcude?
	std::string my_str = "Hello";	// This is a new object
	
	pass_by_copy_function(my_str);
	std::cout << my_str << std::endl;
	
	my_str = "Hello";
	
	pass_by_pointer_function(&my_str);
	std::cout << my_str << std::endl;

	my_str = "Hello";

	//* this is new to c++
	// it is safe, because it's not a pointer, so you cannot pass something 
	// that is invalid.
	pass_by_reference_function(my_str);
	std::cout << my_str << std::endl;

	// Pass-by-reference is always preferred instead of pass-by-pointer:
	// - Safe
	// - Compiler optimizations (avoid pointer aliasing)
	
	// ---------------------------------------------------------------------
	
	// Dynamic memory allocation in C++
	//* malloc/free becomes new/delete
	int *my_int = new int; // new + type is the way of allocating memory
	*my_int = 10;
	std::cout << "My integer is: " << *my_int << std::endl;
	delete my_int;
	
	int N;
	std::cin >> N;
	
	int *my_vector = new int[N]; // this is how you allocate an array
	// Do something...
	delete [] my_vector; // this is how you deallocate an array (thanks copilot)

	//! NEVER mix malloc/free with new/delete
	// Usually, you have no reasons to use the old malloc/free in C++
	
	// ... and, usually, you have no reasons to use new/delete in C++11 (see later)
	
	return 0;
}
