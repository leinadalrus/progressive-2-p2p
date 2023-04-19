#ifndef USER_DATA_SERVICE_HPP
#define USER_DATA_SERVICE_HPP

#include <assert.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>

class UserData {
public:
  int predecessor;
  int successor;
  int node;
  size_t size;
};

class DataImplementation {
public:
  UserData data;

  int compare_scoped_lambda_data(int scoped_lambda_id, int current_node) {
    scoped_lambda_id = (this->data.node == current_node);
    return scoped_lambda_id;
  }
};

#endif // USER_DATA_SERVICE_HPP
