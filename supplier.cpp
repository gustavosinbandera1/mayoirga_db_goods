#include "pch.h"
#include "supplier.h"

REGISTER(Supplier, object, pessimistic_scheme);

field_descriptor& Supplier::describe_components()
{
	return FIELD(name), FIELD(addr), FIELD(rating), FIELD(key), FIELD(orders);
}