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


boolean Order::addDetail(ref<Detail> detail) {
	char* key = detail->getSku()->data();
	console::output("sku del item detail es %s", key);
	_set_order_details.insertUnique(key, detail);
	return boolean();
}

void Order::print(void const *) const {
	console::output("\nOrder Id: %d  is commited: %d", id, _commited);
	/*console::output("\nOwner Name: %s \nEmail: %s", _owner->getName()->data(), _owner->getEmail()->data());
	console::output("\nAddres... ");*/
	//_owner->getAddress()->print();
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