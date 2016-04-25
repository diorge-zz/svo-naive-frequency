#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <utility>


struct SvoRow {
   std::string s;
   std::string v;
   std::string o;
   int n;
};


struct hashPair {
   template <class T1, class T2>
   std::size_t operator () (const std::pair<T1, T2> &p) {
      auto h1 = std::hash<T1>{}(p.first);
      auto h2 = std::hash<T2>{}(p.second);
      return h1 ^ h2;
   }
};


int main(int argc, char** argv) {
   std::ifstream input("sample.svo");

   SvoRow row;
   std::unordered_map<std::pair<std::string, std::string>, int, hashPair> pairs;

   while (input >> row.s >> row.v >> row.o >> row.n) {
      pairs[std::make_pair(row.s, row.o)] += row.n;
   }
   for (const auto &data : pairs) {
      std::cout << "(" << data.first.first << ", " << data.first.second
                << ") = " << data.second << "\n";
   }
}
