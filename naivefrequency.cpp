/**

The MIT License (MIT)

Copyright (c) 2016 Diorge Brognara

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
**/

#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <sstream>
#include <vector>


typedef std::pair<std::string, std::string> TKey;
typedef std::pair<TKey, int> TPair;


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


bool compareTuples(TPair a, TPair b) {
   return a.second > b.second;
}


int main(int argc, char** argv) {
   if (argc < 2) {
      std::cout << "Unspecified N value" << std::endl;
      return -1;
   }


   std::unordered_map<TKey, int, hashPair> pairs;

   while (std::cin.peek() != std::char_traits<char>::eof()) {
      SvoRow row;
      std::getline(std::cin, row.s, '\t');
      std::getline(std::cin, row.v, '\t');
      std::getline(std::cin, row.o, '\t');
      std::string tempString;
      std::getline(std::cin, tempString);
      row.n = std::stoi(tempString);
      pairs[std::make_pair(row.s, row.o)] += row.n;
   }

   int n = std::stoi(argv[1]);
   n = std::min(n, (int)pairs.size());
   std::vector<TPair> ordered;
   ordered.resize(n);

   std::partial_sort_copy(pairs.begin(), pairs.end(),
                     ordered.begin(), ordered.end(), compareTuples);

   for (auto &elem : ordered) {
      std::cout << "(" << elem.first.first << ", " << elem.first.second
                  << ") = " << elem.second << "\n";
   }
}
