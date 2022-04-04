#include "pch.h"
#include "database-guard.h"
#include "application.h"

#include "database.h"
#include "order.h"

#define QUERY_CONFIG                                                           \
  "C:\\Users\\gusta\\Documents\\server-config-dbs\\test-query-1.cfg"

int Application::main() {
  task::initialize(task::normal_stack);
  if (database_guard _{this->db, QUERY_CONFIG}) {
    console::output("Session is open\n");

    if (this->db.open(QUERY_CONFIG)) {
      ref<Database> root;
      this->db.get_root(root);
      root->initialize();
		if (root->orders->empty()) {
			time_t start = time(NULL);
			root->populate();
			printf("Elapsed time for populating database: %d seconds\n",
				   (int)(time(NULL) - start));
		}
      {
        time_t start = time(NULL);
        result_set_cursor cursor;
        try {
			/*this commented query doesn't work*/
			// root->orders->filter(cursor, "price > 990 and supplier.rating >= 0 and supplier.addr.city='Boston'",
          root->orders->filter(cursor, "price > 990" 
									   "and supplier.rating = 2",
                               queryBufSize);
        } catch (QueryException const &err) {
          fprintf(stderr, "Query failed: %s\n", err.msg);
          this->db.close();
          return EXIT_FAILURE;
        }
        ref<Order> order;
        int n_orders;
        for (n_orders = 0; (order = cursor.next()) != NULL; n_orders++) {
          assert(order->price >= 990 /*&&
                 order->supplier->addr.city == "Boston" &&
                 order->supplier->rating >= 0*/);
		  printf("supplier city : [%d, %s]\n",n_orders,order->supplier->addr.city.getChars());
        }
        printf("Elapsed time for filtering %d orders: %d seconds\n", n_orders,
               (int)(time(NULL) - start));

        try {
			// and item like '#%'
          root->suppliers->filter(cursor,
			  /*this query doesn't work */
			  /* "addr.city='Boston' and orders contains "*/
                                  "orders contains "
                                  "(price >= 990 )",
                                  queryBufSize);
        } catch (QueryException const &x) {
          fprintf(stderr, "Query failed: %s\n", x.msg);
          db.close();
          return EXIT_FAILURE;
        }
        ref<Supplier> supplier;
        int n_suppliers;
        for (n_suppliers = 0; (supplier = cursor.next()) != NULL;
             n_suppliers++) {
          assert(supplier->addr.city == "Boston");
        }
        printf("Elapsed time for filtering %d suppliers: %d seconds\n",
               n_suppliers, (int)(time(NULL) - start));
      }
      db.close();
      return EXIT_SUCCESS;
    } else {
      fprintf(stderr, "Failed to open detabase\n");
      return EXIT_FAILURE;
    }

    db.close();
    console::output("Session is closed\n");
    return EXIT_SUCCESS;
  } else {
    console::output("Failed to open database\n");
    return EXIT_FAILURE;
  }
}
