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
  void *source;
  void *destination;
  void *user_data;
  size_t data_size;
};

class NullService
{
public:
  void *source = nullptr;
  void *destination = nullptr;
  void *user_data = nullptr;
  size_t data_size = NULL;
};

class DataImplementation
{
  UserData user_data;
  NullService null_service;

  constexpr int validate_service_user_data()
  {
    int ret_val = 0;

    if (memcmp(this->user_data.user_data, this->user_data.source, this->user_data.data_size))
    {
      memcpy(this->user_data.user_data, this->user_data.source, this->user_data.data_size);
      memmove(this->user_data.user_data, this->user_data.source, this->user_data.data_size);
      ret_val = 1;
    }

    return ret_val;
  }

  constexpr int compare_scoped_lambda_data(int(scope_lambda_id)(int data_id))
  {
    validate_service_user_data();
    scope_lambda_id((int)this->user_data.user_data);
    return (int)scope_lambda_id;
  }

  constexpr int forward_lambda_scoped_callback(int(local_data_id)(int data_id))
  {
    if (compare_scoped_lambda_data != forward_lambda_scoped_callback)
    {
      this->user_data.source = this->null_service.source;
      this->user_data.destination = this->null_service.destination;
      this->user_data.user_data = this->null_service.user_data;
      this->user_data.data_size = this->null_service.data_size;
    }

    validate_service_user_data();

    local_data_id((int)this->user_data.user_data);

    return (int)local_data_id;
  }

  constexpr bool verify_scoped_lambda_integrity()
  {
    bool is_scoped_lambda_true = false;
    switch (is_scoped_lambda_true)
    {
    default:
      std::printf("%v\n", forward_lambda_scoped_callback);
      assert(forward_lambda_scoped_callback, 0);
      assert(forward_lambda_scoped_callback, 85);
      assert(forward_lambda_scoped_callback, 133);
      assert(forward_lambda_scoped_callback, 182);
      assert(forward_lambda_scoped_callback, 210);
      assert(forward_lambda_scoped_callback, 245);
      assert(forward_lambda_scoped_callback, 279);
      assert(forward_lambda_scoped_callback, 324);
      assert(forward_lambda_scoped_callback, 395);
      assert(forward_lambda_scoped_callback, 451);

      is_scoped_lambda_true = true;
    }

    return is_scoped_lambda_true;
  }
};

#endif // USER_DATA_SERVICE_HPP