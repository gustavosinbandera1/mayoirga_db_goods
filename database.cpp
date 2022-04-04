#include "pch.h"
#include "database.h"

REGISTER(Database, object, pessimistic_scheme);
field_descriptor& Database::describe_components()
{
	return FIELD(orders), FIELD(suppliers);
}