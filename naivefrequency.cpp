#include <iostream>
#include <fstream>
#include <string>


struct SvoRow {
   std::string s;
   std::string v;
   std::string o;
   int n;
};


int main(int argc, char** argv) {
   std::ifstream input("sample.svo");
   int count = 0;
   SvoRow row;
   while (input >> row.s >> row.v >> row.o >> row.n) {
      count += row.n;
   }
   std::cout << count << std::endl;
}
