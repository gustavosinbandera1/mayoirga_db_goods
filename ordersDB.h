#pragma once
#include "small_set.h"
#include "person.h"
#include "product.h"
#include "order.h"
#include "detail.h"

#define DB_VERSION 1

class OrdersDB : public object {
protected:
	large_set<Person> _set_all_people;
	large_set<Product> _set_all_products;
	large_set<Order> _set_all_orders;

public:
  int version;
  //------------------- person list stuff -------------//
  ref<Person> findPerson(char const* email) const;
  boolean removePerson(char const* email) const;
  boolean addPerson(char const* name, char const* email, char const* password);
  boolean addPerson(char const* email, ref<Person> p);
  size_t personListSize(void) const;
  void printPerson(char const* email) const;
  void printAllPersons(void) const;
  int4 getLastPersonIndex()  const;

  //------------------ Product list stuff ------------//
  ref<Product> findProduct(char const* sku) const;
  boolean removeProduct(char const* sku) const;
  boolean addProduct(const char* sku, const char* description,
						double price, double weight);
  boolean addProduct(char const* sku, ref<Product> p);
  size_t productListSize(void) const;
  void printProduct(char const* sku) const;
  void printAllProducts(void) const;
  int4 getLastProductIndex() const;

  //----------------- Orders  list stuff ---------------//
  ref<Order> findOrder(char const* orderID) const;
  boolean removeOrder(char const* orderID) const;
  boolean addOrder(char const* orderID);
  boolean addOrder(char const* orderID, ref<Order> o);
  size_t orderListSize(void) const;
  void printOrder(char const* orderID) const;
  void printAllOrders(void) const;
  int4 getLastOrderIndex() const;

  //------------------- User Address list stuff -------------//
  ref<Address> findAddress(char const* owner_address_email, char const* s_type, AddressType e_type) const;
  boolean removeAddress(char const* owner_address_email, char const* s_type, AddressType e_type);
  boolean addAddress(char const* city, char const* state,
	  char const* country, char const* street, char const* s_type, AddressType e_type);
  boolean addAddress(char const* email, ref<Address> address);
  size_t addressListSize(void) const;
  void printUserAddress(char const* email, char const* s_type, AddressType e_type) const;
  void printAllUserAddress(void) const;


  OrdersDB(int vers);

  METACLASS_DECLARATIONS(OrdersDB, object);
};
