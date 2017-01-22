#ifndef _FILTER_ENGINE_H_
#define _FILTER_ENGINE_H_

#include <iostream>
#include <set>

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
            FilterEngine();
            ~FilterEngine();
        private:
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


    };
}

#endif

