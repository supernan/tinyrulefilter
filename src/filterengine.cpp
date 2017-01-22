#include "filterengine.h"

using namespace tinyrulefilter;


bool FilterEngine::__CheckRule(std::string &rule)
{
    int nCnt1 = 0;
    int nCnt2 = 0;
    for (int i = 0; i < rule.length(); i++)
    {
        if (nCnt1 < 0 || nCnt2 < 0)
            return false;
        if (rule[i] == '(')
            nCnt1++;
        else if (rule[i] == ')')
            nCnt1--;
        else if (rule[i] == '[')
            nCnt2++;
        else if (rule[i] == ']')
            nCnt2--;
        else
            continue;
    }
    if (nCnt1 != 0 || nCnt2 != 0)
        return false;
    else
        return true;
}


bool FilterEngine::__RuleFormat(std::string &src, std::string &dst,
                std::set<std::string> &wordsTable, std::string& sErrInfo)
{
    int nSize = src.length();
    if (nSize == 0)
    {
        sErrInfo = "Error in RuleFormat: source rule is empty";
        return false;
    }
    if (!__CheckRule(src))
    {
        sErrInfo = "Error in RuleFormat: source rule is invalid " + src;
        return false;
    }
    dst = "";
    int nPos = 0;
    while (nPos < nSize)
    {
        char val = src[nPos];
        if (val == '(' || val == ')' || val == '^' ||
            val == '|' || val == '~')
        {
            dst += val;
            nPos++;
        }
        else if (val == '[')
        {
            int nOffset = nPos;
            while (nOffset < nSize && src[nOffset] != ']')
                nOffset++;
            std::string word = src.substr(nPos+1, nOffset-nPos-1);
            if (wordsTable.find(word) != wordsTable.end())
                dst += '1';
            else
                dst += '0';
            nPos = nOffset + 1;
        }
        else
            nPos++;
    }
    return true;
}
