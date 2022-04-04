#pragma once
#include "pch.h"

struct Address {
	wstring_t street;
	wstring_t city;
	wstring_t state;
	int4      zipcode;

	field_descriptor& describe_components() {
		return FIELD(street), FIELD(city), FIELD(state), FIELD(zipcode);
	}

	friend field_descriptor& describe_field(Address& s) {
		return s.describe_components();
	}
};