#include "pch.h"
#include "database-guard.h"
#include "application.h"

#define QUERY_CONFIG  \
  "C:\\Users\\gusta\\Documents\\server-config-dbs\\orders-config.cfg"

char buf[6][256];

static void input(const char *prompt, char *buf, size_t buf_size) {
  char *p;
  do {
    console::output("\n		");
    console::output(prompt);
    *buf = '\0';
    console::input(buf, buf_size);
    p = buf + strlen(buf);
  } while (p <= buf + 1);

  if (*(p - 1) == '\n') {
    *--p = '\0';
  }
}

Application::Application() {
  actions.emplace("A", [this](void) { this->addPerson(); });
  actions.emplace("B", [this](void) { this->printAllPerson(); });
  actions.emplace("C", [this](void) { this->deletePerson(); });
  actions.emplace("D", [this](void) { this->addProduct(); });
  actions.emplace("E", [this](void) { this->printAllProduct(); });
  actions.emplace("F", [this](void) { this->deleteProduct(); });
  actions.emplace("G", [this](void) { this->addOrder(); });
  actions.emplace("H", [this](void) { this->deleteOrder(); });
  actions.emplace("I", [this](void) { this->printOrder(); });
  actions.emplace("J", [this](void) { this->printAllOrders(); });
  actions.emplace("N", [this](void) { this->addDetail(); });
  actions.emplace("Q", [this](void) { this->quit(); });
  actions.emplace("Z", [this](void) { this->populateData(); });
}

void Application::addDemoPeople() {
  strcpy(buf[0], "gustavo");
  strcpy(buf[1], "gustavo@gmail.com");
  strcpy(buf[2], "1234");
  ref<Person> p1 = NEW Person(buf[0], buf[1], buf[2]);
  modify(p1)->setAddress("Armenia-1", "Quindio-1", "Colombia-1",
                         "universal calle 24-1", "MAIN_ADDRESS");
  modify(p1)->setAddress("Armenia-2", "Quindio-2", "Colombia-2",
                         "universal calle 24-2", "SHIPPING_ADDRESS");
  modify(p1)->setAddress("Armenia-3", "Quindio-3", "Colombia-3",
                         "universal calle 24-3", "BILLING_ADDRESS");
  modify(root)->addPerson(buf[1], p1);

  strcpy(buf[0], "nicolas");
  strcpy(buf[1], "nico@gmail.com");
  strcpy(buf[2], "abcd");
  ref<Person> p2 = NEW Person(buf[0], buf[1], buf[2]);
  modify(p2)->setAddress("Pereira", "Risaralda", "Colombia",
                         "Laureles calle 25", "BILLING_ADDRESS");
  modify(p2)->setAddress("Armenia-2", "Quindio-2", "Colombia-2",
                         "universal calle 24-2", "SHIPPING_ADDRESS");
  modify(p2)->setAddress("Armenia-3", "Quindio-3", "Colombia-3",
                         "universal calle 24-3", "BILLING_ADDRESS");
  modify(root)->addPerson(buf[1], p2);

  strcpy(buf[0], "pedro");
  strcpy(buf[1], "pedro@gmail.com");
  strcpy(buf[2], "4321");
  ref<Person> p3 = NEW Person(buf[0], buf[1], buf[2]);
  modify(p3)->setAddress("Florencia", "Caqueta", "Colombia", "Centro calle 26",
                         "SHIPPING_ADDRESS");
  modify(p3)->setAddress("Armenia-2", "Quindio-2", "Colombia-2",
                         "universal calle 24-2", "SHIPPING_ADDRESS");
  modify(p3)->setAddress("Armenia-3", "Quindio-3", "Colombia-3",
                         "universal calle 24-3", "BILLING_ADDRESS");
  modify(root)->addPerson(buf[1], p3);

  strcpy(buf[0], "juan");
  strcpy(buf[1], "juan@gmail.com");
  strcpy(buf[2], "4321");
  ref<Person> p4 = NEW Person(buf[0], buf[1], buf[2]);
  modify(p4)->setAddress("Florencia", "Caqueta", "Colombia", "Centro calle 26",
                         "SHIPPING_ADDRESS");
  modify(p4)->setAddress("Armenia-2", "Quindio-2", "Colombia-2",
                         "universal calle 24-2", "SHIPPING_ADDRESS");
  modify(p4)->setAddress("Armenia-3", "Quindio-3", "Colombia-3",
                         "universal calle 24-3", "BILLING_ADDRESS");
  modify(root)->addPerson(buf[1], p4);
}

void Application::addDemoProducts(void) {
  strcpy(buf[0], "1");      // sku
  strcpy(buf[1], "Modem");  // description
  strcpy(buf[2], "1235.4"); // price
  strcpy(buf[3], "32.1");   // weight
  modify(root)->addProduct(buf[0], buf[1], std::stod(buf[2]),
                           std::stod(buf[3]));

  strcpy(buf[0], "2");        // sku
  strcpy(buf[1], "Pc");       // description
  strcpy(buf[2], "12435.23"); // price
  strcpy(buf[3], "12.18");    // weight
  modify(root)->addProduct(buf[0], buf[1], std::stod(buf[2]),
                           std::stod(buf[3]));

  strcpy(buf[0], "3");        // sku
  strcpy(buf[1], "TV");       // description
  strcpy(buf[2], "43267.22"); // price
  strcpy(buf[3], "4.32");     // weight
  modify(root)->addProduct(buf[0], buf[1], std::stod(buf[2]),
                           std::stod(buf[3]));

  strcpy(buf[0], "4");       // sku
  strcpy(buf[1], "Desktop"); // description
  strcpy(buf[2], "2345.6");  // price
  strcpy(buf[3], "2.32");    // weight
  modify(root)->addProduct(buf[0], buf[1], std::stod(buf[2]),
                           std::stod(buf[3]));
}

void Application::addDemoOrders() {
  strcpy(buf[0], "1");
  strcpy(buf[1], "2");
  strcpy(buf[2], "3");
  strcpy(buf[3], "4");

  modify(root)->addOrder(buf[0]);
  modify(root)->addOrder(buf[1]);
  modify(root)->addOrder(buf[2]);
  modify(root)->addOrder(buf[3]);

  //----------------- Adding Order's details to Order "1" and using User Gustavo
  //as bill owner ----------------------//
  ref<Order> order;
  order = ordersDb->findOrder("1");
  if (order != NULL) {
    console::output("we get the order object .........");
    ref<Detail> detail1 =
        NEW Detail("1", "4", std::stod("3"), std::stod("765.09"));
    ref<Detail> detail2 =
        NEW Detail("2", "5", std::stod("3"), std::stod("546.6"));
    ref<Detail> detail3 =
        NEW Detail("3", "6", std::stod("3"), std::stod("321.32"));
    modify(detail1)->setOwner(order);
    modify(detail2)->setOwner(order);
    modify(detail3)->setOwner(order);

    modify(order)->addDetail(detail1);
    modify(order)->addDetail(detail2);
    modify(order)->addDetail(detail3);

    ref<Person> p = ordersDb->findPerson("gustavo@gmail.com");
    if (p != NULL) {
      console::output("\nAdding adrdesses to the bill order ....");
      modify(order)->setOwner(p);
      modify(order)->setBillingAddress(p->getAddress("BILLING_ADDRESS"));
      modify(order)->setShippingAddress(p->getAddress("SHIPPING_ADDRESS"));
    } else {
      console::output("\nUser doesn't exist");
    }
  }

  //----------------- Adding Order's details to Order "2" and using User Nicolas
  //as bill owner ----------------------//
  order = ordersDb->findOrder("2");
  if (order != NULL) {
    console::output("we get the order object .........");
    ref<Detail> detail1 =
        NEW Detail("1", "4", std::stod("3"), std::stod("765.09"));
    ref<Detail> detail2 =
        NEW Detail("2", "5", std::stod("3"), std::stod("546.6"));
    ref<Detail> detail3 =
        NEW Detail("3", "6", std::stod("3"), std::stod("321.32"));
    modify(detail1)->setOwner(order);
    modify(detail2)->setOwner(order);
    modify(detail3)->setOwner(order);

    modify(order)->addDetail(detail1);
    modify(order)->addDetail(detail2);
    modify(order)->addDetail(detail3);
    ref<Person> p = ordersDb->findPerson("nico@gmail.com");
    if (p != NULL) {
      console::output("\nAdding adrdesses to the bill order ....");
      modify(order)->setOwner(p);
      modify(order)->setBillingAddress(p->getAddress("BILLING_ADDRESS"));
      modify(order)->setShippingAddress(p->getAddress("SHIPPING_ADDRESS"));
    } else {
      console::output("\nUser doesn't exist");
    }
  }

  //----------------- Adding Order's details to Order "3" and using User Pedro
  //as bill owner ----------------------//
  order = ordersDb->findOrder("3");
  if (order != NULL) {
    console::output("we get the order object .........");
    ref<Detail> detail1 =
        NEW Detail("1", "4", std::stod("3"), std::stod("765.09"));
    ref<Detail> detail2 =
        NEW Detail("2", "5", std::stod("3"), std::stod("546.6"));
    ref<Detail> detail3 =
        NEW Detail("3", "6", std::stod("3"), std::stod("321.32"));
    modify(detail1)->setOwner(order);
    modify(detail2)->setOwner(order);
    modify(detail3)->setOwner(order);

    modify(order)->addDetail(detail1);
    modify(order)->addDetail(detail2);
    modify(order)->addDetail(detail3);
    ref<Person> p = ordersDb->findPerson("pedro@gmail.com");
    if (p != NULL) {
      console::output("\nAdding adrdesses to the bill order ....");
      modify(order)->setOwner(p);
      modify(order)->setBillingAddress(p->getAddress("BILLING_ADDRESS"));
      modify(order)->setShippingAddress(p->getAddress("SHIPPING_ADDRESS"));
    } else {
      console::output("\nUser doesn't exist");
    }
  }

  //----------------- Adding Order's details to Order "3" and using User Pedro
  //as bill owner ----------------------//
  order = ordersDb->findOrder("4");
  if (order != NULL) {
    console::output("we get the order object .........");
    ref<Detail> detail1 =
        NEW Detail("1", "4", std::stod("3"), std::stod("765.09"));
    ref<Detail> detail2 =
        NEW Detail("2", "5", std::stod("3"), std::stod("546.6"));
    ref<Detail> detail3 =
        NEW Detail("3", "6", std::stod("3"), std::stod("321.32"));
    modify(detail1)->setOwner(order);
    modify(detail2)->setOwner(order);
    modify(detail3)->setOwner(order);

    modify(order)->addDetail(detail1);
    modify(order)->addDetail(detail2);
    modify(order)->addDetail(detail3);
    ref<Person> p = ordersDb->findPerson("juan@gmail.com");
    if (p != NULL) {
      console::output("\nAdding adrdesses to the bill order ....");
      modify(order)->setOwner(p);
      modify(order)->setBillingAddress(p->getAddress("BILLING_ADDRESS"));
      modify(order)->setShippingAddress(p->getAddress("SHIPPING_ADDRESS"));
    } else {
      console::output("\nUser doesn't exist");
    }
  }
}

void Application::addPerson() {
  input("Name: ", buf[0], sizeof buf[0]);
  input("Email: ", buf[1], sizeof buf[1]);
  input("Password: ", buf[2], sizeof buf[2]);
  modify(root)->addPerson(buf[0], buf[1], buf[2]);
}

void Application::printAllPerson() const { ordersDb->printAllPersons(); }

void Application::deletePerson() {
  input("Name: ", buf[0], sizeof buf[0]);
  modify(root)->removePerson(buf[0]);
}

void Application::addProduct() {
  input("New product sku: ", buf[0], sizeof buf[0]);
  input("Description: ", buf[1], sizeof buf[1]);
  input("Price: ", buf[2], sizeof buf[2]);
  input("Weight: ", buf[3], sizeof buf[3]);
  console::output("int output: %0.2lf", std::stod(buf[2]));
  modify(root)->addProduct(buf[0], buf[1], std::stod(buf[2]),
                           std::stod(buf[3]));
}

void Application::printAllProduct() { ordersDb->printAllProducts(); }

void Application::deleteProduct() {
  input("Sku: ", buf[0], sizeof buf[0]);
  modify(root)->removeProduct(buf[0]);
}

void Application::addOrder() {
  input("OrderId: ", buf[0],
        sizeof buf[0]); // then create order id object and insert details items
  modify(root)->addOrder(buf[0]);
}

void Application::addDetail() {
  input("detail ID: ", buf[0], sizeof buf[0]);
  input("Product sku: ", buf[1], sizeof buf[1]);
  input("Quantity: ", buf[2], sizeof buf[2]);
  input("Price: ", buf[3], sizeof buf[3]);
  input("Order ID: ", buf[4], sizeof buf[4]);
  ref<Detail> detail =
      NEW Detail(buf[0], buf[1], std::stod(buf[2]), std::stod(buf[3]));
  insertDetail(buf[4], detail);
}

void Application::printAllOrders() { ordersDb->printAllOrders(); }

void Application::printOrderDetail() {}

void Application::deleteOrderDetail() {}

void Application::quit() {
  session_opened = false;
  cs.leave();
}

void Application::printOrder() {
  input("Order ID: ", buf[0], sizeof buf[0]);
  root->printOrder(buf[0]);
}

void Application::deleteOrder() {}

void Application::populateData() {
  /* sample data */
  //--------------------- Adding Person objects -----------------------//
  addDemoPeople();
  //-----------------Adding Product
  //objects-------------------------------------//
  addDemoProducts();
  //-----------------------Adding Order objects-------------------------
  addDemoOrders();
}

boolean Application::insertDetail(char const *orderID, ref<Detail> detail) {
  ref<Order> order = ordersDb->findOrder(orderID);
  if (order != NULL) {
    modify(order)->addDetail(detail);
    return True;
  }
  console::output("Order no found");
  return False;
}

void Application::printMenu() {

  console::output("Number of persons are %d\n", ordersDb->personListSize());
  console::output("Menu:\n\
	|(a)| Add new Person \n\
	|(b)| Print all persons \n\
	|(c)| Delete Person \n\
	|(d)| Add new Product \n\
	|(e)| Print all products \n\
	|(f)| Delete Product \n\
	|(g)| add order \n\
	|(h)| delete order \n\
	|(i)| print order \n\
	|(j)| print all Orders \n\
	|(k)| Set Order shipping address \n\
	|(l)| Set order billing address \n\
	|(m)| Set Order Owner \n\
	|(n)| Set Order Detail \n\
	|(q)| Quit \n");
}

void task_proc Application::start_update_process(void *arg) {
  ((Application *)arg)->update();
}

void Application::dialogue() {
  task::create(start_update_process, this);

  while (session_opened) {
    printMenu();
    input(">> ", buf[0], sizeof buf[0]);

    char ch = toupper(*buf[0]);
    std::string option(1, ch);
    cs.enter();
    executeAction(option);
    cs.leave();
    console::output("\n<<< Press ENTER to  continue >>>");
    /*wait for key input to continue */
    console::input(buf[0], sizeof buf[0]);
  }
}

void Application::update() {
  // thread for sending signals about  updates to others clients 
  while (session_opened) {
  }
}

int Application::main() {
  task::initialize(task::huge_stack);

  if (database_guard _{this->db, QUERY_CONFIG}) {
    session_opened = True;
    console::output("Session is opened\n");
    this->db.get_root(root);
    this->root->initialize();

    this->ordersDb = root->db;
    dialogue();
    
	console::output("Session is closed\n");
    return EXIT_SUCCESS;
  } else {
    console::output("Failed to open database\n");
    return EXIT_FAILURE;
  }
}

boolean Application::executeAction(std::string action) {
  auto it = actions.find(action);
  if (it != actions.end()) {
    it->second();
    return true;
  }
  return false;
}
