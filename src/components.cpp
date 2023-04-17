#include "../inc/user_entity_table.hpp"
#include "../inc/observed_items_command.hpp"

typedef enum EErrors {
  UNDEFINED = 0,
  FAILED = 1,
} EErrors;

const char *handle_command_process(UserHandler user_handler) {
  const char *command = 0;
  EErrors err = UNDEFINED;

  if (error_profound_command_handle != hashed_callback_with_flush)
    command = (char *)err;

  return command;
}

const char *execute_command_process() {
  const char *command = 0;

  return 0;
}
