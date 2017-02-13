#ifndef _AC_AUTOMATON_H_
#define _AC_AUTOMATON_H_

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <queue>

namespace tools
{
	struct Trie
	{
		int count; //标记是否为词结束节点
		int pattern_id; //如果该节点是模式的结束，记录匹配到的模式id
		std::map<char, Trie*> next; //下层节点
		Trie *fail;
		Trie()
		{
			next.clear();
			count = 0;
			pattern_id = -1;
			fail = NULL;
		}
	};


	class AC_automaton
	{
		public:

			/*构造函数
			 *初始化字典树根节点
			 */
			AC_automaton();


			/*析构函数
			 *释放字典树资源
			 */
			~AC_automaton();


			/*文档查询
			 *在构建好的自动机基础上查询文本
			 *arg1:text[string] 要查询的文本
			 *ret[map] 返回匹配到的模式id与模式串的映射
			 */
			std::vector< std::map<std::string, int> > query(std::string &text);


			/*构造自动机
			 *插入所有模式串构造自动机
			 *arg1:patterns[vector] 要插入的所有模式
			 */
			void build_automaton(std::set<std::string> &patterns);


			/*清除自动机
			 *清除所有已经存在的模式串
			 */
			void clear();
		private:

			/*构造自动机
			 *配置节点的失效函数
			 *arg1:root[Trie] 自动机根节点
			 */
			void _build(Trie *root);


			/*插入模式
			 *向自动机中插入模式串
			 *arg1:root[Trie] 自动机的根节点
			 *arg2:pattern[string] 要插入的模式
			 *arg3:id[int] 模式串id
			 */
			void _insert(Trie *root, std::string &pattern, int id);


			/*释放自动机内存
			 *递归释放自动机Trie树的内存
			 *arg1:root[Trie] 根节点
			 */
			void _destroy_tree(Trie *root);

			Trie *_root; //Trie树根节点
			std::map<int, int> _visit; //在查询是标记模式串是否已经被匹配
			std::map<int, std::string> _id_pattern_map; //模式id与模式串的映射
	};

}



#endif
