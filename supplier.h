#pragma once
#include "common.h"

class Supplier : public object {
public:
  wstring_t name;
  Address addr;
  float rating;
  ref<set_member> key;
  ref<set_owner> orders;

  Supplier(wstring_t const &sName, Address const &sAddr, float sRating)
      : object(self_class), name(sName), addr(sAddr), rating(sRating) {
    char *supplierName = name.getChars();
    key = set_member::create(this, supplierName);
    delete[] supplierName;
    orders = B_tree::create(this);
  }

  METACLASS_DECLARATIONS(Supplier, object);
};
