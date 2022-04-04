#include "pch.h"
#include "order.h"

REGISTER(Order, object, pessimistic_scheme);

field_descriptor& Order::describe_components()
{
	return FIELD(supplier), FIELD(item), FIELD(price), FIELD(delivery), FIELD(supplier_orders), FIELD(all_orders);
}