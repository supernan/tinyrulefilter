#include "acautomaton.h"

tools::AC_automaton::AC_automaton()
{
	_root = new Trie();
}


void tools::AC_automaton::_destroy_tree(Trie *root)
{
	if (root == NULL) //空指针 判断
		return;
	std::map<char, Trie*>::iterator iter;
	for (iter = root->next.begin(); iter != root->next.end(); ++iter)
	{
		_destroy_tree(iter->second);
	}
	delete root;
}


tools::AC_automaton::~AC_automaton()
{
	_destroy_tree(_root);
}


void tools::AC_automaton::_insert(Trie *root, std::string &pattern, int id)
{
	Trie *cur = root;
	for (unsigned int i = 0; i < pattern.length(); ++i)
	{
		if (cur->next.find(pattern[i]) == cur->next.end())
			cur->next[pattern[i]] = new Trie();
		cur = cur->next[pattern[i]];
	}
	++cur->count;
	cur->pattern_id = id;
}


void tools::AC_automaton::_build(Trie *root)
{
	std::queue<Trie*> trie_queue;
	while (!trie_queue.empty())
		trie_queue.pop();
	trie_queue.push(root);
	while (!trie_queue.empty())
	{
		Trie *cur = trie_queue.front();
		trie_queue.pop();
		std::map<char, Trie*>::iterator iter;
		for (iter = cur->next.begin(); iter != cur->next.end(); ++iter)
		{
			if (cur == root)
				cur->next[iter->first]->fail = root;
			else
			{
				Trie *tmp = cur->fail;
				while (tmp)
				{
					if (tmp->next[iter->first])
					{
						cur->next[iter->first]->fail = tmp->next[iter->first];
						break;
					}
					tmp = tmp->fail;
				}
				if (tmp == NULL)
					cur->next[iter->first]->fail = root;
			}
			trie_queue.push(cur->next[iter->first]);
		}
	}
}


void tools::AC_automaton::build_automaton(std::set<std::string> &patterns)
{
    std::set<std::string>::iterator it;
    int count = 0;
	for (it = patterns.begin(); it != patterns.end(); ++it)
	{
		//_visit[i] = 0;
        std::string pattern = *it;
		_insert(_root, pattern, count);
		_id_pattern_map[count] = *it;
        count++;
	}
	_build(_root);
}


std::map<int, std::string> tools::AC_automaton::query(std::string &text)
{
	//_visit.clear(); //TODO(zhounan) 全赋值为0 or 清空
	int ret = 0;
	std::map<int, std::string> match_patterns;
	Trie *cur = _root;
	for (unsigned int i = 0; i < text.length(); ++i)
	{
		while (cur->next[text[i]] == NULL && cur != _root)
			cur = cur->fail;
		cur = cur->next[text[i]];
		if (cur == NULL)
			cur = _root;
		Trie *tmp = cur;
		while (tmp != _root && tmp)
		{
			if (tmp->pattern_id != -1 /*&&_visit[tmp->pattern_id] == 0*/)
			{
				ret += tmp->count;
				//_visit[tmp->pattern_id] = 1;
				//match_patterns[tmp->pattern_id] = _id_pattern_map[tmp->pattern_id];
				match_patterns[i] = _id_pattern_map[tmp->pattern_id];
			}
			tmp = tmp->fail;
		}
	}
	return match_patterns;
}


void tools::AC_automaton::clear()
{
	_destroy_tree(_root);
	_root = new Trie();
	_id_pattern_map.clear();
	//_visit.clear();
}
