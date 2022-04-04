#pragma once
#include "common.h"
//#include "supplier.h"
#include "order.h"


const int nOrders = 10;
const int nSuppliers = 100;
const int nStreets = 100;

const int queryBufSize = 64 * 1024;

class Database : public object {
public:
	ref<B_tree> suppliers;
	ref<B_tree> orders;

	void initialize() const {
		if (is_abstract_root()) {
			ref<Database> root = this;
			modify(root)->become(NEW Database());
		}
	}

	void populate() const
	{
		char buf[256];
		time_t delivery = time(NULL);
		int orderId = 1000;
		Address addr;
		addr.city = "Boston";
		addr.state = "MT";
		for (int i = 1; i <= nSuppliers; i++) {
			sprintf(buf, "%d-th avenu", i % nStreets);
			addr.street = buf;
			addr.zipcode = i % nStreets;
			sprintf(buf, "X%d", i);
			ref<Supplier> supplier = NEW Supplier(buf, addr, i % 3);
			modify(suppliers)->insert(supplier->key);

			for (int j = 1; j <= nOrders; j++) {
				sprintf(buf, "#%d", orderId++);
				ref<Order> order = NEW Order(supplier, buf, 999 + (j & 1), delivery++);
				modify(orders)->insert(order->all_orders);
				modify(supplier->orders)->insert(order->supplier_orders);
			}
		}
	}

	Database() : object(self_class) {
		orders = B_tree::create(this);
		suppliers = B_tree::create(this);
	}


	METACLASS_DECLARATIONS(Database, object);
};

