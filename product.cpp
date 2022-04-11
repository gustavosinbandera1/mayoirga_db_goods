#include "pch.h"
#include "product.h"

Product::Product(char const *sku, char const *description, double price,
                 double weight)
    : SetMember(self_class) {

  sSku = String::create(sku);
  sDescription = String::create(description);
  nPrice = (real4)price;
  nWeight = (real4)weight;
}

void Product::print(void const *arg) const {
	console::output("sku: ");
	sSku->print();
	console::output("\nDescription: ");
	sDescription->print();
	console::output("\nPrice: %0.2lf", nPrice);
	console::output("\nWeight: %0.2lf", nWeight);
}

field_descriptor &Product::describe_components() {
  return FIELD(sSku), FIELD(sDescription), FIELD(nPrice), FIELD(nWeight);
}

REGISTER(Product, SetMember, pessimistic_scheme);
