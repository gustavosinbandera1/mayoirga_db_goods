#pragma once
#include "setMember.h"

class Product : public SetMember {
public:
  inline nat8 getPrice(void) { return nPrice; };
  inline nat8 getWeight(void) { return nWeight; };
  inline ref<String> getDescription(void) { return sDescription; };
  inline ref<String> getSku() { return sSku; }
  inline void setPrice(double  price) { nPrice = price; }
  inline void setWeight(double weight) { nWeight = weight; }
  
  struct selectPattern {
    char const *sSku;
  };

  void print(void const* arg = NULL) const override;

  METACLASS_DECLARATIONS(Product, SetMember);

  Product(char const *sku, char const *description, double price,
          double weight);

private:
  ref<String> sSku;
  ref<String> sDescription;
  real4 nPrice;
  real4 nWeight;
};
