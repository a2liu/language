#include "lexer.h"
#include "parser.h"
#include "pools.h"
#include <iostream>

int main() {
  std::string s = R"(

def hi():
    return 1 + 12.12
    def hi():
      pass

  )";

  Program program;
  BucketArray buckets;
  Lexer *l = new (buckets.add<Parser>()) Lexer(s);
  Parser *p = new (buckets.add<Parser>()) Parser(*l);

  bool a = p->try_parse_program(program);

  if (!a)
    std::cout << "failed" << std::endl;
  std::cout << program << std::endl;
}
