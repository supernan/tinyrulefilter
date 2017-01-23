#ifndef _RULE_ANALYZER_H_
#define _RULE_ANALYZER_H_

#include <iostream>
#include <stack>
#include "glog/logging.h"


namespace tinyrulefilter
{
    /*
     * \class > RuleAnalyzer
     * \breif > rule analysis class
     * \date > 2017/1
     * \author > zhounan(zhounan@software.ict.ac.cn)
     */
    class RuleAnalyzer
    {
        public:
            /*
             * \fn > RuleAnaysis
             * \breif > resolve rule and get result
             * \param[in] rule > rule string
             * \param[out] bRes > boolean result
             * \ret bool > whether function succeed
             * \date > 2017/1
             * \author > zhounan(zhounan@software.ict.ac.cn)
             */
            static bool RuleAnalysis(std::string rule, bool &bRes);

        private:
            /*
             * \fn > Char2Boolean
             * \breif > convert char value to boolean
             * \param[in] ch > char value
             * \param[out] bRes > boolean result
             * \ret bool > whether function succeed
             * \date > 2017/1
             * \author > zhounan(zhounan@software.ict.ac.cn)
             */
            static bool Char2Boolean(char ch, bool &bRes);


            /*
             * \fn > GetOperationRes
             * \breif > get operation result
             * \param[in] opt > opr value
             * \param[in] c1 > char value
             * \param[in] c2 > char value
             * \param[out] bRes > boolean result
             * \ret bool > whether function succeed
             * \date > 2017/1
             * \author > zhounan(zhounan@software.ict.ac.cn)
             */
            static bool GetOperationRes(char opt, char c1, char c2,
                                        bool &bRes);


            /*
             * \fn > ComputeExp
             * \breif > compute bool expression
             * \param[in] numsStack > number stack
             * \param[in] optsStack > operation stack
             * \ret bool > whether function succeed
             * \date > 2017/1
             * \author > zhounan(zhounan@software.ict.ac.cn)
             */
            static bool ComputeExp(std::stack<char> &numsStack, std::stack<char> &optsStack);


            /*
             * \fn > DebugPrint
             * \breif > debug function
             * \param[in] numsStack > number stack
             * \param[in] optsStack > operation stack
             * \ret void
             * \date > 2017/1
             * \author > zhounan(zhounan@software.ict.ac.cn)
             */
            static void DebugPrint(std::stack<char> numsStack, std::stack<char> optsStack);

    };
}
#endif
