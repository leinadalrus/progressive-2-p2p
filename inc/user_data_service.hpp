#ifndef USER_DATA_SERVICE_HPP
#define USER_DATA_SERVICE_HPP

#include <assert.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <memory>

class UserData
{
public:
  void *predecessor;
  void *successor;
  void *user_data;
  size_t data_size;
};

class NullService
{
public:
  void *predecessor = nullptr;
  void *successor = nullptr;
  void *user_data = nullptr;
  size_t data_size = NULL;
};

class DataImplementation
{
public:
  UserData user_data;
  NullService null_service;

   int validate_service_user_data()
  {
    int ret_val = 0;

    if (memcmp(this->user_data.user_data, this->user_data.predecessor, this->user_data.data_size))
    {
      memcpy(this->user_data.user_data, this->user_data.predecessor, this->user_data.data_size);
      memmove(this->user_data.user_data, this->user_data.predecessor, this->user_data.data_size);
      ret_val = 1;
    }

    return ret_val;
  }

   int compare_scoped_lambda_data(int scope_lambda_id, int current_node)
  {
    validate_service_user_data();
    int (scope_lambda_id)((int)this->user_data.user_data == current_node);
    return (int)scope_lambda_id;
  }

   int forward_lambda_scoped_callback(int(local_data_id)(int data_id))
  {
    if (!validate_service_user_data())
    {
      this->user_data.predecessor = this->null_service.predecessor;
      this->user_data.successor = this->null_service.successor;
      this->user_data.user_data = this->null_service.user_data;
      this->user_data.data_size = this->null_service.data_size;
    }

    validate_service_user_data();

    local_data_id((int)this->user_data.user_data);

    return (int)local_data_id;
  }

  constexpr bool verify_scoped_lambda_integrity(int scoped_lambda)
  {
    switch (scoped_lambda)
    {
    case 0:
      scoped_lambda = compare_scoped_lambda_data(scoped_lambda, 0);
    case 85:
      scoped_lambda = compare_scoped_lambda_data(scoped_lambda, 85);
    case 133:
      scoped_lambda = compare_scoped_lambda_data(scoped_lambda, 133);
    case 182:
      scoped_lambda = compare_scoped_lambda_data(scoped_lambda, 182);
    case 210:
      scoped_lambda = compare_scoped_lambda_data(scoped_lambda, 210);
    case 245:
      scoped_lambda = compare_scoped_lambda_data(scoped_lambda, 245);
    case 279:
      scoped_lambda = compare_scoped_lambda_data(scoped_lambda, 279);
    case 324:
      scoped_lambda = compare_scoped_lambda_data(scoped_lambda, 324);
    case 395:
      scoped_lambda = compare_scoped_lambda_data(scoped_lambda, 395);
    case 451:
      scoped_lambda = compare_scoped_lambda_data(scoped_lambda, 451);

    default:
      std::printf("%v\n", forward_lambda_scoped_callback);
      scoped_lambda = true;
    }

    return scoped_lambda;
  }
};

#endif // USER_DATA_SERVICE_HPP