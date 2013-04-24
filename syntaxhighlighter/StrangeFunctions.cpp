#include <sstream>
std::string inttostring(int a){
  std::stringstream b;
  b<<a;
  std::string help;
  b>>help;
  b.clear();
  return help;
}
