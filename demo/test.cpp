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
    string s1 = "~([中国]^[美国])";
    string s2 = "~([美国]|[中国])";
    string s = "([b]|(~([aa]^([ab]|[bc]))^[aa]))";
    FilterEngine f;
    vector<string> rules;
    rules.push_back(s1);
    rules.push_back(s2);
    f.BuildFilter(rules);

    vector<string> docs;
    string d1 = "中国居民赴美国旅游需要申请B2旅游签证，此签证也包括观光、探亲访友及医疗治病等";
    string d2 = "中国政府网由国务院办公厅主办，中国政府网运行中心负责运行维护";
    docs.push_back(d1);
    docs.push_back(d2);
    map<int, vector<int> > ret;
    if (!f.FilterDocs(docs, ret))
    {
        cout<<"error "<< endl;
    }
    else
    {
        map<int, vector<int> >::iterator it;
        for (it = ret.begin(); it != ret.end(); it++)
        {
            int ruleId = it->first;
            cout<<"rule: "<<ruleId<<" "<<rules[ruleId]<<endl;
            vector<int> matches = it->second;
            for (int j = 0; j < matches.size(); j++)
                cout<<"doc: "<<matches[j]<<endl;
        }
    }
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
