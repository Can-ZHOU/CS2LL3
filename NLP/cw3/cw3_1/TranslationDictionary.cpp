/************* TranslationDictionary.cpp **********************/
#include <string>
#include <iostream>
#include <fstream>

#include "TranslationDictionary.h"

using namespace std;

/*************************************************************************/
/* builds dictionary from file with translation pairs source/translation */
/* on single lines                                                       */
/*************************************************************************/
Trans_Dict::Trans_Dict(string file_name)
{
  string line, translation, word;
  ifstream f;
  Transpair p;
  size_t trans_offset;

  f.open(file_name);
  if (f)
  {
    opened_ok = true;
  }
  else
  {
    opened_ok = false;
  }

  if (opened_ok)
  {

    while (f >> line)
    {
      trans_offset = line.find('/'); /* trans_offset is location of / */

      if (trans_offset == string::npos)
      {
        cout << "there was an entry with no /\n";
        continue;
      }
      else
      {
        word = line.substr(0, trans_offset);         // up to /
        translation = line.substr(trans_offset + 1); // after /
        // make transpair with word and translation
        p.french = word;
        p.english = translation;
        thewords.push_back(p); // add transpair to thewords
      }
    }
  }
}

/*****************************************************************/
/* looks up word in dictionary, returning true or false          */
/* setting 'trans' to contain the translation if found 
/*****************************************************************/
bool Trans_Dict::lookup(string word, string &trans)
{
  int i;
  for (i = 0; i < thewords.size(); i++)
  {
    if (thewords[i].french == word)
    {
      trans = thewords[i].english;
      return true;
    }
  }
  return false;
}

/*****************************************************************/
/* a function which takes an english word                        */
/* and tells the equivalent french word                          */
/*****************************************************************/
bool Trans_Dict::english_to_french(string word, string &trans)
{
  int i;
  for (i = 0; i < thewords.size(); i++)
  {
    if (thewords[i].english == word)
    {
      trans = thewords[i].french;
      return true;
    }
  }
  return false;
}

/*****************************************************************/
/* adds/updates the dictionary entry for                         */
/* the indicated french word french                              */
/*****************************************************************/
void Trans_Dict::update(string french, string english)
{
  bool exist_flag = false;
  int i;

  /* Go through thewords, check the exist of the matching word for french */
  for (i = 0; i < thewords.size(); i++)
  {
    // If exist, update the english
    if (thewords[i].french == french)
    {
      thewords[i].english = english;
      exist_flag = true;
    }
  }

  // If not exist, extend a new pair to thewords
  if (exist_flag == false)
  {
    Transpair new_pair;
    new_pair.french = french;
    new_pair.english = english;
    thewords.push_back(new_pair);
  }
}

/*****************************************************************/
/* create a file representing the contents of                    */
/* the dictionary's thewords vector                              */
/*****************************************************************/
void Trans_Dict::export_to_file(string filename)
{
  ofstream output_file(filename);
  for (int i = 0; i < thewords.size(); i++)
  {
    output_file << thewords[i].french << "/" << thewords[i].english << endl;
  }
}