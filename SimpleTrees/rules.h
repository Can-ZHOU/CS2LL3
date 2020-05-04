#if !defined RULES
#define RULES


#include <string>
#include <vector>

using namespace std;

/*! \file
 * the context free grammar classes
 */



//! represents a category in a syntax rule
class Category {
 public:
  string cat; //!< the name of the category
  bool terminal;  //!< indicates whether a terminal category
  Category(string c); //!< constructs from a string
  Category(void); //!< void constructor does nothing
  ~Category(void); //!< destructor does nothing present only for debugging reasons
  void print(void); //!< prints the category
  bool operator==(const Category&);
};

//! represents a syntax rule
class Rule {
 public:
  Category mother; //!< the mother of the rule
  vector<Category> dtrs; //!< the daughters of the rule
  Rule(string r); //!< constructs from a string
  Rule(void); //!< void constructor does nothing
  ~Rule(void); //!< destructor does nothing present only for debugging reasons
  void print(void); //!< prints the rule
};


#endif
