#include "pch.h"
#include "detail.h"
#include "order.h"
#include <string>

Order::Order(char const* id, class_descriptor &desc) : SetMember(desc) {
	_set_order_details.initialize(this);
	this->id = std::stod(id);
	this->_first_line_description = String::create(" ");
	this->_second_line_description = String::create(" ");
	console::output("\nOrderId: %ld", this->id);
}


boolean Order::addDetail(char const* key, ref<Detail> detail) {
	//char* key = detail->getSku()->data();
	console::output("sku item detail: %s", key);
	_set_order_details.insertUnique(key, detail);
	//delete key;
	return boolean();
}

void Order::print(void const *) const {
	/*I am not sure about if thememory will need to be released 
	when I did it I got an issue relate with using delete operator
	*/
	char* name = _owner->getName()->data();
	char* email = _owner->getEmail()->data();
	console::output("\nOrder Id: %d  is commited: %d", id, _commited);
	console::output("\nOwner Name: %s \nEmail: %s",name, email);
	console::output("\nAddres... ");
	_owner->getAddress()->print();
	//delete email;
	//delete name;
}

void Order::printBrief() const {

}

void Order::printDetails() const {

}

boolean Order::select(void const* pattern) const {
	return True;
}

//ref<Order> Order::create(long int id) {
//	return new (self_class,0) Order(id);
//}

field_descriptor& Order::describe_components() {
	return FIELD(id), FIELD(_set_order_details), 
		FIELD(_owner), FIELD(_commited),
		FIELD(_shipping_address), FIELD(_billing_address), FIELD(_first_line_description),
		FIELD(_second_line_description) ;
}

REGISTER(Order, SetMember, pessimistic_repeatable_read_scheme);