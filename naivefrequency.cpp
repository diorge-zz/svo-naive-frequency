/*!
 * \brief       Program for frequency count of SVO{N} files.
 * \author      Diorge Brognara
 * \date        2016
 * \copyright   Copyright (C) Diorge Brognara 2016. All rights MIT Licensed.
*/

#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <sstream>
#include <vector>


/*! \var    typedef std::pair<std::string, std::string> TKey
 *  \brief  (S, O) key used in the mapping
*/
typedef std::pair<std::string, std::string> TKey;

/*! \var    typedef std::pair<TKey, int> TPair
    \brief  type_value used in the mapping
*/
typedef std::pair<TKey, int> TPair;

//! Data in each row in the SVO{N} file
struct SvoRow {
   std::string s;
   std::string v;
   std::string o;
   int n;
};


//! Definition of custom hash for std::pair<T1, T2>
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


//! Compares two TPair by greater integer value
bool compareTuples(TPair a, TPair b) {
   return a.second > b.second;
}


//! SVO{N} frequency counter program
/*! 
 * \param argc Must be at least 2
 * \param argv Second element (first argument) must be a positive integer, other elements are discarded
 SVO input is expected on stdin. Output is on stdout.
*/
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
