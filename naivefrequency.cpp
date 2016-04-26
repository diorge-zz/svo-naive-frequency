#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <sstream>
#include <vector>


struct SvoRow {
   std::string s;
   std::string v;
   std::string o;
   int n;
};


struct hashPair {
   template <class T1, class T2>
   std::size_t operator () (const std::pair<T1, T2> &p) const {
      auto value = 0x345678;
      auto h1 = std::hash<T1>{}(p.first);
      auto h2 = std::hash<T2>{}(p.second);
      value = (100003 * value) ^ h1;
      value = (100003 * value) ^ h2;
      return value;
   }
};


bool compareTuples(std::tuple<std::string, std::string, int> a,
                     std::tuple<std::string, std::string, int> b) {
   return std::get<2>(a) > std::get<2>(b);
}


std::vector<std::string> &split(const std::string &s, char delim,
                                 std::vector<std::string> &elems) {
   std::stringstream ss(s);
   std::string item;
   while (std::getline(ss, item, delim)) {
      elems.push_back(item);
   }
   return elems;
}


SvoRow rowFromSplit(std::vector<std::string> vec) {
   SvoRow row;
   row.s = vec[0];
   row.v = vec[1];
   row.o = vec[2];
   row.n = std::stoi(vec[3]);
   return row;
}

std::vector<std::string> split(const std::string &s, char delim) {
   std::vector<std::string> elems;
   split(s, delim, elems);
   return elems;
}


int main(int argc, char** argv) {
   if (argc < 2) {
      std::cout << "Unspecified N value" << std::endl;
      return -1;
   }


   int n = std::stoi(argv[1]);
   SvoRow row;
   std::unordered_map<std::pair<std::string, std::string>, int, hashPair> pairs;
   std::vector<std::tuple<std::string, std::string, int> > ordered;
   std::string tempString;

   while (std::cin.good()) {
      std::getline(std::cin, row.s, '\t');
      std::getline(std::cin, row.v, '\t');
      std::getline(std::cin, row.o, '\t');
      std::getline(std::cin, tempString);
      row.n = std::stoi(tempString);
      pairs[std::make_pair(row.s, row.o)] += row.n;
      std::cin.peek();
   }

   for (const auto &data : pairs) {
      ordered.push_back(std::make_tuple(data.first.first,
                                          data.first.second, data.second));
   }

   n = std::min(n, (int)ordered.size());

   std::partial_sort(ordered.begin(), ordered.begin() + n,
                     ordered.end(), compareTuples);

   for (auto it = ordered.begin(); it != ordered.begin() + n; ++it) {
      std::cout << "(" << std::get<0>(*it) << ", " << std::get<1>(*it)
                  << ") = " << std::get<2>(*it) << "\n";
   }
}
