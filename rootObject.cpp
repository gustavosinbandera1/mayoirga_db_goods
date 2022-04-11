#include "pch.h"
#include "rootObject.h"


//----------------------------------------------------------
void RootObject::initialize() const {
  if (is_abstract_root()) {
    ref<RootObject> root = this;
    modify(root)->become(NEW RootObject(DB_VERSION));
  }
}
//----------------------------------------------------------
boolean RootObject::removePerson(char const *email) const {
	return modify(db)->removePerson(email);
}
//----------------------------------------------------------
boolean RootObject::addPerson(const char *name, const char *email,
                            const char *password) {
	return modify(db)->addPerson(name, email, password);
}
//----------------------------------------------------------
boolean RootObject::addPerson(const char *email, ref<Person> person) {
	return modify(db)->addPerson(email, person);
}
//----------------------------------------------------------
boolean RootObject::addProduct(const char* sku, const char* description,
	double price, double weight) {
	return modify(db)->addProduct(sku, description, price, weight);
}
boolean RootObject::addProduct(char const * sku, ref<Product> p) {
	return modify(db)->addProduct(sku, p);
}
//----------------------------------------------------------
boolean RootObject::removeProduct(char const* sku) const {
	return modify(db)->removeProduct(sku);
}
//----------------------------------------------------------
boolean RootObject::addOrder(char const* order_id) {
	return modify(db)->addOrder(order_id);
}
//----------------------------------------------------------
boolean RootObject::removeOrder(char const* order_id) {
	return modify(db)->removeOrder(order_id);
}

void RootObject::printOrder(char const * id) const {
	db->findOrder(id)->print();
}

//----------------------------------------------------------
field_descriptor &RootObject::describe_components() {
  return FIELD(db);
}
//----------------------------------------------------------
REGISTER(RootObject, object, pessimistic_exclusive_scheme);
