#include "ruleanalysis.h"

using namespace tinyrulefilter;



void RuleAnalyzer::DebugPrint(std::stack<char> numsStack, std::stack<char> optsStack)
{
    std::string out = "";
    while (!numsStack.empty())
    {
        char val = numsStack.top();
        numsStack.pop();
        out += val;
        out += " ";
    }
    std::cout<<"debug "<<out<<std::endl;
}


bool RuleAnalyzer::GetOperationRes(char opt, char c1, char c2,
                                   bool &res)
{
    bool n1 = false;
    bool n2 = false;
    if (!Char2Boolean(c1, n1))
        return false;
    if (!Char2Boolean(c2, n2))
        return false;

    res = false;
    bool ret = true;
    switch (opt)
    {
        case '|':
            res = n1 || n2;
            break;
        case '^':
            res = n1 & n2;
            break;
        default:
            res = false;
            ret = false;
            LOG(WARNING) << "Error in GetOperationRes: opt is illegal " << opt << std::endl;
            break;
    }
    return ret;
}


bool RuleAnalyzer::Char2Boolean(char ch, bool &bRes)
{
    if (ch == '1')
    {
        bRes = true;
        return true;
    }
    else if (ch == '0')
    {
        bRes = false;
        return true;
    }
    else
    {
        bRes = false;
        LOG(WARNING) << "Error in Char2Boolean: char value is illegal " << ch << std::endl;
        return false;
    }
}


bool RuleAnalyzer::ComputeExp(std::stack<char> &numsStack, std::stack<char> &optsStack)
{
    DebugPrint(numsStack, optsStack);
    if (numsStack.empty())
    {
        LOG(WARNING) << "Error in ComputeExp: numsStack is empty" << std::endl;
        return false;
    }
    while (!numsStack.empty())
    {
        char elem = numsStack.top();
        numsStack.pop();
        if (elem == '(')
            continue;
        if (elem == ')')
            break;
        if (numsStack.empty())
        {
            LOG(WARNING) << "Error in ComputeExp: numsStack is empty before end" << std::endl;
            return false;
        }
        char next = numsStack.top();
        numsStack.pop();
        if (next == ')')
        {
            numsStack.push(elem);
            break;
        }
        if (optsStack.empty())
        {
            LOG(WARNING) << "Error in ComputeExp: optsStack is empty before end" << std::endl;
            return false;
        }
        char opt = optsStack.top();
        optsStack.pop();
        bool res;
        if (!GetOperationRes(opt, elem, next, res))
        {
            return false;
        }
        if (res)
            numsStack.push('1');
        else
            numsStack.push('0');
    }
    return true;
}


bool RuleAnalyzer::RuleAnalysis(std::string rule, bool &bRes)
{
    int nSize = rule.length();
    if (nSize == 0)
    {
        LOG(WARNING) << "Error in RuleAnalysis: rule string is empty" << std::endl;
        return false;
    }
    if (rule == "1")
    {
        bRes = true;
        return true;
    }
    if (rule == "0")
    {
        bRes = false;
        return true;
    }
    std::stack<char> numsStack;
    std::stack<char> optsStack;
    int nPos = nSize - 1;
    while (nPos >= 0)
    {
        char elem = rule[nPos];
        if (elem == '|' || elem == '^')
            optsStack.push(elem);
        else if (elem == '~')
        {
            if (numsStack.empty())
            {
                LOG(WARNING) << "Error in RuleAnalysis: numsStack is empty before negation " << rule << std::endl;
                return false;
            }
            else
            {
                char num = numsStack.top();
                if (num != '0' && num != '1')
                {
                    LOG(WARNING) << "Error in RuleAnalysis: number is invalid when negation " << num << std::endl;
                    return false;
                }
                else
                {
                    numsStack.pop();
                    if (num == '1')
                        numsStack.push('0');
                    else
                        numsStack.push('1');
                }
            }
        }
        else if (elem == '(' || elem == ')' || elem == '0'
                 || elem == '1')
        {
            numsStack.push(elem);
        }
        if (elem == '(')
        {
            if (!ComputeExp(numsStack, optsStack))
                return false;
        }
        nPos--;
    }

    if (numsStack.empty())
    {
        LOG(WARNING) << "Error in RuleAnalysis: numsStack is empty before get final res " << rule << std::endl;
        return false;
    }
    char finalElem = numsStack.top();
    if (finalElem == '1')
    {
        bRes = true;
        return true;
    }
    else if (finalElem == '0')
    {
        bRes = false;
        return true;
    }
    else
    {
        LOG(WARNING) << "Error in RuleAnalysis: the final value in stack is invalid " << finalElem << std::endl;
        return false;
    }
}
