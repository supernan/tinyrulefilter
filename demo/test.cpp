#include <set>
#include <iostream>
#include "acautomaton.h"
#include "ruleanalysis.h"
#include "filterengine.h"

using namespace std;
using namespace tools;
using namespace tinyrulefilter;


int main()
{
    set<string> words;
    string s = "([b]|(~([aa]^([ab]|[bc]))^[aa]))";
    FilterEngine f;
    /*f.__GetWordsFromRule(s, words);
    set<string>::iterator it;
    for (it = words.begin(); it != words.end(); ++it)
        cout<<*it<<endl;*/

    /*words.insert("abc");
    words.insert("efg");
	AC_automation ac;
    ac.build_automation(words);
    map<int, string> ret;
    string s = "abcxxxefgxxxabcxxxefgyy";
    ret = ac.query(s);
    map<int, string>::iterator it;
    for (it = ret.begin(); it != ret.end(); ++it)
        cout<<it->first<<" "<<it->second<<endl;*/

    /*std::set<std::string> words;
    words.insert("a");
    string s = "([b]|(~([aa]^([ab]|[bc]))^[aa]))";
    string d = "";
    string err = "";
    if (!RuleFormat(s, d, words, err))
    {
        cout<<err<<endl;
    }
    else
        cout<<d<<endl;*/
    return 0;
}
