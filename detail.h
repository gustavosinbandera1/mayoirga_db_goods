#pragma once
#include "setMember.h"
#include "order.h"
#include "product.h"
#include <string>
#include <sstream>


template <typename T>
std::string numberToString(T Number) {
	std::ostringstream ss;
	ss << Number;
	return ss.str();
}

class Detail : public SetMember {
protected:
	ref<Order> detail_owner_;
public:
	void print(void const *arg) const;
	void print_sku() const;
	nat4 getID() const { return this->_id; };
	ref<String> getSku() const { return this->_productSku; };
	Detail(char const* detailID, char const* productSku, 
		int quantity, double price);
	Detail(char const* detailID, char const* productSku,
		int quantity, double price, ref<Order> bill);
	void setOwner(ref<Order> order);
	ref<Order> getOwner() const { return detail_owner_; };


	/*static ref<Detail> create(int quantity, double price, 
		ref<Order> bill, char const* productSku);*/
	METACLASS_DECLARATIONS(Detail, SetMember);

private:
	nat4 _id;
	ref<String> _productSku;
	nat1 _quantity;
	real4 _price;
	real4 _total;
};

