#pragma once
#include "supplier.h"

class Order :public object {
public:
	ref<Supplier> supplier;
	wstring_t item;
	nat8 price;
	nat8 delivery;
	ref<set_member> supplier_orders;
	ref<set_member> all_orders;

	Order(ref<Supplier> oSupplier, wstring_t oItem, nat8 oPrice, nat8 oDelivery)
		: object(self_class), supplier(oSupplier), item(oItem), price(oPrice), delivery(oDelivery)
	{
		char* itemName = item.getChars();
		all_orders = set_member::create(this, itemName);
		supplier_orders = set_member::create(this, itemName);
		delete[] itemName;
	}

	METACLASS_DECLARATIONS(Order, object);
};

