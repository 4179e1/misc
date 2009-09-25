#include <iostream>

using namespace std;
template <typename elemtype> class BTnode;
template <typename elemtype> class BinaryTree;

template <typename elemtype>
class BTnode
{
	friend class BinaryTree<elemtype>;
	public:
		BTnode (const elemtype &);
	private:
		elemtype _val;
		int _cnt;
		BTnode *_lchild;
		BTnode *_rchild;
};

template <typename elemtype>
inline BTnode<elemtype>::BTnode (const elemtype &val)
	: _val(val)
{
	_cnt = 1;
	_lchild = _rchild = 0;
}

template <typename elemtype>
class BinaryTree
{
	public:
		BinaryTree();
		BinaryTree (const BinaryTree&);
		~BinaryTree();
		BinaryTree& operator=(const BinaryTree&);

		bool empty() {return _root == 0;}
		void clear();

		void insert(const elemtype &elem);
	private:
		BTnode<elemtype> *_root;
		void copy(BTnode<elemtype>*tar, BTnode<elemtype>*src);
};

template <typename elemtype>
inline BinaryTree<elemtype>::BinaryTree()
	: _root(0)
{}

template <typename elemtype>
inline BinaryTree<elemtype>::BinaryTree (const BinaryTree &rhs)
{
	copy (_root, rhs._root);
}

template <typename elemtype>
inline BinaryTree<elemtype>::~BinaryTree()
{
	clear();
}

template <typename elemtype>
inline BinaryTree<elemtype>& BinaryTree<elemtype>::operator=(const BinaryTree &rhs)
{
	if (this != &rhs)
	{
		clear();
		copy (_root, rhs._root);
	}

	return *this;
}

template <typename elemtype>
inline void BinaryTree<elemtype>::insert (const elemtype &elem)
{
	if (!_root)
	{
		_root = new BTnode<elemtype> (elem);
	}
	else
	{
		_root->insert_value(elem);
	}
}
