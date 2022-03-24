#pragma once
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <csv.h>
#include <stdbool.h>
#include <string>
#include <vector>
#include <unordered_map>

typedef void (*row_parser_callback)(std::vector<std::string>* row_items);

class CSVParser {
private:
  struct csv_parser* parser;
  long unsigned fields;
  long unsigned rows;
  int is_first_item = true;
  int is_first_line = true;
  int is_comment = false;
  std::vector<std::string>* row_items;
  row_parser_callback row_parser;
  
public:
  unsigned char options = 0;

  CSVParser();
  ~CSVParser();

  void readFile(const std::string filename, std::vector<std::string> *expectedColumns, row_parser_callback row_parser);
  void setOptions(unsigned char options);

  // you shouldn't be calling these, but they need to be public
  // for the callback the way I wrote it. Better than exposing
  // the member variables at least.
  // These do have side effects, so don't go calling them
  inline void callback_item(void *string_pointer, size_t len);
  inline void callback_assemble_row(int c);
};
