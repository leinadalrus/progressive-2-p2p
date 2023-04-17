#include "../inc/user_entity_table.hpp" // Enumerated Chord DHT controller
#include <memory>
#include <cstdio>
#include <cstdlib>
#include <cstring>

int read_file_throughput(void *table_data, char *data_input, char *data_size,
                         char *data_output) {
  table_data = malloc(sizeof(data_size));
  char table_data_ptr_t = static_cast<char>(reinterpret_cast<char16_t>(table_data));
  memcpy(data_input, data_output, table_data_ptr_t);
  free(table_data);

  return 0;
}

int reading_author_callback(int(function)(char *, char *, char *, char *)) {
  void *reader = malloc(sizeof function); // this is a non-heap object.
  memmove(function, reader, sizeof *function);

  int retval = 0;
  if (!reader) {
    retval = 1;
  }

  return retval; // return false as a boolean check codition.
}
