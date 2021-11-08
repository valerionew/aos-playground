#include <iostream>
#include <string>

//* example class
class Sensor {
//* public: everyone can access these methods (and variables but not recommended)
public:
	//* constructor
	Sensor(int id, const std::string &name) : id(id), name(name) {
		// ... Any code you need in the constructor goes here ...
		total_sensors++;
	}
	
	//* destructor
	virtual ~Sensor() {
		// Do something in the destructor...
		total_sensors--;
	}
	
	const std::string &get_name() {
		return this->name;	// or this->id
	}
	
	// we pass name by reference so that we don't make a copy 
	// and we also add the constant keyword to prevent modifications
	void set_name(const std::string &name) {
		// the keyword this is used here to clarify the ambiguity between the name varaible and the parameter
		this->name = name;
	}
	int get_id() const;

	static int get_nr_sensors() {
		return total_sensors;
	}
	
//	virtual void update() = 0;
	
	//! VIRTUAL
	//* virtual means that this method can be overwritten by the child
	// this returns a constant array of chars
	virtual const char * get_class_name() const {
		return "Sensor";
	}

//* protected: only derived classes can access these methods
protected:
	std::string name;

//* private: this are the encapsulated variables and methods
private:
	int id;
	static int total_sensors;
};

int Sensor::total_sensors = 0;

	//* const: this method cannot change the variables of the class
	// its a safety measure and a self-documenting way to code
	//* methods can be added also outside the class
int Sensor::get_id() const {
	return id;	// or this->id
}

//! Inheriting class
// inherits from Sensor
//* when inheriting, one can specify the visibility of the parent methods etc:  in particular, if it's kept public no changes are made. Instead, if it's kept private or protected, the inherited methods are hidden wrt the outside in the new class. What was private in the parent class stays private in the child class and what was protected stays protected in the child class.
class TemperatureSensor : public Sensor {
public:
	TemperatureSensor(int id, const std::string &name) : Sensor(id, name) {
		this->name = "[TEMP] " + this->name;
	}
	
/*	virtual void update() {
	  Read the temperature from the sensor and fill this->temperature...
		this->temperature = 20.5;
	}*/
	
	//! VIRTUAL is mandatory if we are over-writing a virtual method from the parent
	//* virtual means that this method can be overwritten by the child
	virtual const char * get_class_name() const {
		return "TemperatureSensor";
	}
	
	float get_temperature_C() const {
		return this->temperature;
	}

	float get_temperature_F() const {
		return (this->temperature * 9./5.) + 32.;
	}
	
private:
	float temperature;	// Saved in Celsius
};

class HumiditySensor : public Sensor {
public:
	HumiditySensor(int id, const std::string &name) : Sensor(id, name) {
		this->name = "[HUM] " + this->name;
	}

	virtual const char * get_class_name() const {
		return "HumiditySensor";
	}	

	float get_humidity() const {
		return humidity;
	}
private:
	float humidity;
};


int main() {

	// when a constructor is specified, the parameters must be passed
	Sensor s(123, "Generic");
	std::cout << "ID is: " << s.get_id() << "\tName is: " << s.get_name() << std::endl;

	Sensor            *s1 = new Sensor(123, "Generic"); // using new to allocate the memory
	TemperatureSensor *s2 = new TemperatureSensor(123, "Room");
	HumiditySensor    *s3 = new HumiditySensor(123, "Corridor");
	
	std::cout << s1->get_class_name() << "\t" << s2->get_class_name() << "\t" << s3->get_class_name() << std::endl;

	// I can access s2->get_temperature_C() and s3->get_humidity()
	std::cout << s2->get_temperature_C() << "\t" << s3->get_humidity() << std::endl;

 //! NOTICE: we are instantiating a children into a parent's type
 //* this can only be done with parent/children
 // but in this case the s4, s5, s6 will:
 // - use the children methods if virutal and already defined in the parent (but the children's version!! but only if VIRUTAL!)
 // - won't be able to use children methods that were not already defined in the parent!!
 //? puprose of this? seems pure madness
	Sensor *s4 = new Sensor(123, "Generic");
	Sensor *s5 = new TemperatureSensor(123, "Room");
	Sensor *s6 = new HumiditySensor(123, "Corridor");

	std::cout << s4->get_class_name() << "\t" << s5->get_class_name() << "\t" << s6->get_class_name() << std::endl;

	// I CANNOT access s5->get_temperature_C() or s6->get_humidity()
	//std::cout << s5->get_temperature_C() << "\t" << s6->get_humidity() << std::endl;


	std::cout << "Number of sensors: " << Sensor::get_nr_sensors() << std::endl;
	delete s1;
	delete s2;
	delete s3;
	delete s4;
	delete s5;
	delete s6;
	std::cout << "Number of sensors: " << Sensor::get_nr_sensors() << std::endl;

	return 0;
}

