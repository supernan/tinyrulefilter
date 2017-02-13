#ifndef _FILTER_ENGINE_H_
#define _FILTER_ENGINE_H_

#include <iostream>
#include <set>
#include <stack>
#include <vector>
#include "glog/logging.h"
#include "acautomaton.h"
#include "ruleanalysis.h"

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

            /*
             * \fn > BuildFilter
             * \breif > build filter engine
             * \param[in] rules > rules to build filter
             * \ret bool > whether function is succeed
             * \date > 2017/1
             * \author > zhounan(zhounan@software.ict.ac.cn)
             */
            bool BuildFilter(std::vector<std::string> &rules);


            /*
             * \fn > FilterDocs
             * \breif > filter docs
             * \param[in] vDocs > docs to filter
             * \param[out] mRule2Doc > rule_id -> {d1, d2, ...}
             * \ret bool > whether function is succeed
             * \date > 2017/1
             * \author > zhounan(zhounan@software.ict.ac.cn)
             */
            bool FilterDocs(std::vector<std::string> &vDocs, std::map<int, std::vector<int> > &mRule2Doc);

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
             * \ret bool > whether rule is valid
             * \date > 2017/1
             * \author > zhounan(zhounan@software.ict.ac.cn)
             */
            bool __RuleFormat(std::string &src, std::string &dst,
                              std::set<std::string> &wordsTable);


            /*
             * \fn > __BuildDocStream
             * \breif > change doc vector to docstream before filter
             * \param[in] vDocs > docs
             * \param[out] sDocStream > string of docstream
             * \param[out] vPos > vector to store positions of each doc
             * \ret bool > whether function succeed
             * \date > 2017/1
             * \author > zhounan(zhounan@software.ict.ac.cn)
             */
            bool __BuildDocStream(std::vector<std::string> &vDocs, std::string &sDocStream,
                                  std::vector<int> &vPos);


            /*
             * \fn > __SearchDocIdx
             * \breif > search doc idx with doc offset
             * \param[in] vPos > doc offset vector
             * \param[in] nOffset > the position of matched keyword
             * \param[out] nDocIdx > doc idx of matched doc
             * \ret bool > whether function succeed
             * \date > 2017/1
             * \author > zhounan(zhounan@software.ict.ac.cn)
             */
            bool __SearchDocIdx(std::vector<int> &vPos, int nOffset, int &nDocIdx);


            /*
             * \fn > __GetHitDocs
             * \breif > get hit docs after query
             * \param[in] mMatchRes > query result
             * \param[in] vPos > position of docs
             * \param[out] mDoc2Words > docid -> {w1, w2, w3...}
             * \ret bool > whether function succeed
             * \date > 2017/1
             * \author > zhounan(zhounan@software.ict.ac.cn)
             */
            bool __GetHitDocs(std::vector< std::map<std::string, int> > &mMatchRes, std::vector<int> &vPos,
                              std::map<int, std::set<std::string> > &mDoc2Words);


            /*
             * \fn > __FilterByRule
             * \breif > filter doc by rule after  query
             * \param[in] mDoc2Words > query result
             * \param[out] mRule2Doc > rule_id -> {d1, d2, ..}
             * \ret bool > whether function succeed
             * \date > 2017/1
             * \author > zhounan(zhounan@software.ict.ac.cn)
             */
            bool __FilterByRule(std::map<int, std::set<std::string> > &mDoc2Words,
                                std::map<int, std::vector<int> > &mRule2Doc);

        private:
            // acautomaton ptr
            AC_automaton *m_pAC;

            // rules of engine
            std::vector<std::string> m_vRules;




    };
}

#endif

