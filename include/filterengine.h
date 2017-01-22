#ifndef _FILTER_ENGINE_H_
#define _FILTER_ENGINE_H_

#include <iostream>
#include <set>
#include <stack>
#include <vector>
#include "glog/logging.h"
#include "acautomaton.h"

using namespace tools;

namespace tinyrulefilter
{
    /*
     * \class > FilterEngine
     * \breif > filter engine core
     * \date > 2017/1
     * \author > zhounan(zhounan@software.ict.ac.cn)
     */
    class FilterEngine
    {
        public:
            /*
             * \fn > constructor and destructor
             *
             */
            FilterEngine();
            ~FilterEngine();

            bool BuildFilter(std::vector<std::string> &rules);

        private:


            /*
             * \fn > __GetWordsFromRule
             * \breif > resolve the rule and extract keywords
             * \param[in] rule > rule to resolve
             * \param[out] words > the set to store words
             * \ret bool > whether function is succeed
             * \date > 2017/1
             * \author > zhounan(zhounan@software.ict.ac.cn)
             */
            bool __GetWordsFromRule(std::string &rule, std::set<std::string> &words);


            /*
             * \fn > __CheckRule
             * \breif > check the rule
             * \param[in] rule > rule to check
             * \ret bool > whether rule is valid
             * \date > 2017/1
             * \author > zhounan(zhounan@software.ict.ac.cn)
             */
            bool __CheckRule(std::string &rule);


            /*
             * \fn > __RuleFormat
             * \breif > use match words to format rule
             * \param[in] src > source rule
             * \param[out] dst > destination rule
             * \param[in] wordsTable > words hit by doc
             * \param[out] sErrInfo > error info
             * \ret bool > whether rule is valid
             * \date > 2017/1
             * \author > zhounan(zhounan@software.ict.ac.cn)
             */
            bool __RuleFormat(std::string &src, std::string &dst,
                              std::set<std::string> &wordsTable, std::string& sErrInfo);

        private:
            // acautomaton ptr
            AC_automaton *m_pAC;

            // rules of engine
            std::vector<std::string> m_vRules;




    };
}

#endif

