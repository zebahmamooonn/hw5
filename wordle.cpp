#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
//#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;

size_t countDashes(const std::string& s){
  int count = 0;
  for(char c : s){
    if(c == '-') count ++; 
  }
  return count; 
}

// Add prototypes of helper functions here
void buildWords(std::string current, std::string floating, 
  const std::set<std::string>& dict, 
  std::set<std::string>& results, size_t index )
  {
    
    if(index == current.size()){
      if(floating.empty() && dict.find(current) != dict.end()){
        results.insert(current); 
      }
      return; 
    }

    if (current[index] != '-'){
      buildWords(current, floating, dict, results, index + 1);
      return; 
    }

    for(char c = 'a'; c <= 'z'; c++){
      current[index] = c; 

      std::string newFloating = floating;
      size_t pos = newFloating.find(c);
      if(pos != string::npos){
        newFloating.erase(pos, 1);
        buildWords(current, newFloating, dict, results, index +1); 
      }
      else{
        if(newFloating.size() <= countDashes(current)){
          buildWords(current, newFloating, dict, results, index + 1); 
        }
    }
  }
}
  
  
  // Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
  std::set<std::string> results;
  buildWords(in, floating, dict, results, 0);
  return results; 
}

// Define any helper functions here
