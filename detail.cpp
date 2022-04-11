#include "pch.h"
#include "detail.h"
#include <string>

Detail::Detail(char const *detailID, char const *productSku, int quantity,
               double price )
    : SetMember(self_class) {

  this->_id = std::stod(detailID);
  this->_productSku = String::create(productSku);
  this->_quantity = (nat1)quantity;
  this->_price = (real4)price;
}

Detail::Detail(char const * detailID, char const * productSku, int quantity, 
	double price, ref<Order> order) : SetMember(self_class) {
	this->_id = std::stod(detailID);
	this->_productSku = String::create(productSku);
	this->_quantity = (nat1)quantity;
	this->_price = (real4)price;
	this->detail_owner_ = order;
}

void Detail::setOwner(ref<Order> order) {
	detail_owner_ = order;
}

void Detail::print(void const* arg) const {
  console::output("Product sku: ");
  _productSku->print();
  console::output("\n");
  console::output("Quantity: %d", _quantity);
  console::output("Price: %0.2lf", _price);
}

void Detail::print_sku() const { _productSku->print(); }

field_descriptor& Detail::describe_components() {
  return FIELD(_id), FIELD(_productSku), FIELD(_price), FIELD(_total), FIELD(_quantity);
}

REGISTER(Detail, SetMember, pessimistic_repeatable_read_scheme);
