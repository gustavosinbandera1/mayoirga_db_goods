#include "pch.h"
#include "detail.h"
#include <string>


Detail::Detail(char const* detailId, char const* productSku, int quantity) 
	: SetMember(self_class) {
	this->_id = std::stod(detailId);
	this->_product_sku = String::create(productSku);
	this->_quantity = (nat1)quantity;
}

void Detail::setOwner(ref<Order> order) {
	detail_owner_ = order;
}

void Detail::print(void const* arg) const {
  console::output("Product sku: ");
  _product_sku->print();
  console::output("\n");
  console::output("Quantity: %d", _quantity);
  console::output("Price: %0.2lf", _product_price);
}

void Detail::print_sku() const { _product_sku->print(); }

field_descriptor& Detail::describe_components() {
  return FIELD(_id), FIELD(_product_sku), FIELD(_product_price), FIELD(_quantity);
}

REGISTER(Detail, SetMember, pessimistic_repeatable_read_scheme);
