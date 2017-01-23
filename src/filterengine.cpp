#include "filterengine.h"

using namespace tinyrulefilter;

FilterEngine::FilterEngine()
{
    m_pAC = new AC_automaton();
}


FilterEngine::~FilterEngine()
{
    delete m_pAC;
}

bool FilterEngine::BuildFilter(std::vector<std::string> &rules)
{
    if (rules.empty())
    {
        LOG(ERROR) << "Error in BuildFilter: rules empty" << std::endl;
        return false;
    }
    m_vRules.clear();
    std::vector<std::string>().swap(m_vRules);
    m_vRules = rules;
    std::set<std::string> words;
    for (int i = 0; i < m_vRules.size(); i++)
    {
        if (!__GetWordsFromRule(m_vRules[i], words))
        {
            LOG(WARNING) << "Error in BuildFilter : __GetWordsFromRule Failed skip" << std::endl;
            continue;
        }
    }
    m_pAC->build_automaton(words);
    return true;
}

bool FilterEngine::__GetWordsFromRule(std::string &rule, std::set<std::string> &words)
{
    int nSize = rule.length();
    if (nSize == 0)
    {
        LOG(WARNING) << "Error in __GetWordsFromRule: rule is empty" << std::endl;
        return false;
    }
    if (!__CheckRule(rule))
    {
        LOG(WARNING) << "Error in __GetWordsFromRule: rule is invalid " << rule << std::endl;
        return false;
    }
    std::stack<char> charsStack;
    for (int i = nSize-1; i >= 0; i--)
    {
        char val = rule[i];
        charsStack.push(val);
        if (val == '[')
        {
            std::string word = "";
            charsStack.pop();
            while (!charsStack.empty())
            {
                char top = charsStack.top();
                charsStack.pop();
                if (top == ']')
                    break;
                word += top;
            }
            words.insert(word);
        }
    }
    return true;
}


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
                std::set<std::string> &wordsTable)
{
    int nSize = src.length();
    if (nSize == 0)
    {
        LOG(WARNING) << "Error in RuleFormat: source rule is empty" <<std::endl;
        return false;
    }
    if (!__CheckRule(src))
    {
        LOG(WARNING) << "Error in RuleFormat: source rule is invalid " << src << std::endl;
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


bool FilterEngine::__BuildDocStream(std::vector<std::string> &vDocs, std::string &sDocStream,
                                    std::vector<int> &vPos)
{
    if (vDocs.empty())
    {
        LOG(WARNING) << "Error in __BuildDocStream: Docs empty" << std::endl;
        return false;
    }
    vPos.clear();
    sDocStream = "";
    for (int i = 0; i < vDocs.size(); i++)
    {
        if (vDocs[i].length() == 0)
            continue;
        sDocStream += vDocs[i];
        sDocStream += "||";
        int nOffset = sDocStream.length();
        vPos.push_back(nOffset);
    }
    return true;
}


bool FilterEngine::__SearchDocIdx(std::vector<int> &vPos, int nOffset, int &nDocIdx)
{
    if (vPos.empty())
    {
        LOG(WARNING) << "Error in __SearchDocIdx: vPos empty" << std::endl;
        nDocIdx = -1;
        return false;
    }
    int nLeft = 0;
    int nRight = vPos.size() - 1;
    while (nLeft <= nRight)
    {
        int nMid = (nLeft + nRight) / 2;
        if (vPos[nMid] < nOffset)
            nLeft = nMid + 1;
        else
            nRight = nMid - 1;
    }
    if (nLeft < vPos.size())
    {
        nDocIdx = nLeft;
        return true;
    }
    else
    {
        LOG(WARNING) << "Error in __SearchDocIdx: Doc not found" << std::endl;
        nDocIdx = -1;
        return false;
    }
}
