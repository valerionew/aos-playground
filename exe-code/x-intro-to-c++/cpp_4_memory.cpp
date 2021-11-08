#include <memory>
#include "cpp_2_objects.cpp"

void test_function_2(std::shared_ptr<Sensor> sensor) {
	// DO something with sensor
}

void test_function() {
	//! SMART POINTERS
	//* a smart pointer cannot be destroyed until all the references to it are destroyed! This is powerful since it allows us to avoid referencing a pointer that is no longer valid.
	// the synthax is not beautiful but it's recommended to use smart pointers
	std::shared_ptr<Sensor> s = std::make_shared<Sensor>(123, "test");	// Dynamically allocated
	test_function_2(s);
	s->get_id();
}	// Destroyed here

//! UNIQUE POINTER
//* a unique pointer is a smart pointer that is guaranteed to be unique. This means that the pointer cannot be copied or assigned to another pointer.
// std::unique_ptr<>  

int main() {

	Sensor *test = new Sensor(123, "test");
	
	// ...
	

	delete test;

	test_function();

	return 0;
}
