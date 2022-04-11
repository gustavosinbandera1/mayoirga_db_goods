#include "ordersDB.h"

class RootObject : public object {
public:
	ref<OrdersDB> db;
	void initialize() const;

	RootObject(int version) : object(self_class) {
		db = NEW OrdersDB(version);
	}

	boolean addPerson(const char* name,const char* email, const char* password);
	boolean addPerson(const char *name, ref<Person> person);
	boolean removePerson(char const* name) const;

	boolean addOrder(char const* order_id);
	boolean removeOrder(char const* order_id);
	void printOrder(char const* id) const ;


	boolean addProduct(const char* sku, const char* description, 
		double price, double weight);
	boolean addProduct(char const* sku, ref<Product> p);
	boolean removeProduct(char const* sku) const;

	METACLASS_DECLARATIONS(RootObject, object);
};

