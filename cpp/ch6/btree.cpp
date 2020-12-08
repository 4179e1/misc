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
		void insert_value (const elemtype &);
		static void lchild_leaf (BTnode *leaf, BTnode *subtree);
		void remove_value (const elemtype &val, BTnode *& prev);
		void display_val (BTnode *pt, ostream &os) const;
		void preorder (BTnode *pt, ostream &os) const;
		void inorder (BTnode *pt, ostream &os) const;
		void postorder (BTnode *pt, ostream &os) const;
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
void BTnode<elemtype>::insert_value (const elemtype &val)
{
	if (val == _val)
	{
		_cnt++;
		return;
	}

	if (val < _val)
	{
		if (!_lchild)
		{
			_lchild = new BTnode (val);
		}
		else
		{
			_lchild->insert_value (val);
		}
	}
	else
	{
		if (!_rchild)
		{
			_rchild = new BTnode (val);
		}
		else
		{
			_rchild->insert_value (val);
		}
	}
}

template <typename elemtype>
void BTnode<elemtype>::lchild_leaf (BTnode *leaf, BTnode *subtree)
{
	while (subtree->_lchild) 
	{
		subtree = subtree->_lchild;
	}
	
	subtree->_lchild = leaf;
}

template <typename elemtype>
void BTnode<elemtype>::remove_value (const elemtype &val, BTnode *& prev)
{
	if (val < _val)
	{
		if (!_lchild)
		{
			return;
		}
		else 
		{
			_lchild->remove_value (val, _lchild);
		}
	}
	else if (val > _val)
	{
		if (!_rchild)
		{
			return;
		}
		else
		{
			_rchild->remove_value (val, _rchild);
		}
	}
	else
	{
		if (_rchild)
		{
			prev = _rchild;
			if (_lchild)
			{
				if (!prev->_lchild)
				{
					prev->_lchild = _lchild;
				}
				else
				{
					BTnode<elemtype>::lchild_leaf (_lchild, prev->_lchild);
				}
			}
		}
		else
		{
			prev = _lchild;
		}

		delete this;
	}
}

template <typename elemtype>
inline void BTnode<elemtype>::display_val (BTnode *pt, ostream &os) const
{
	os << pt->_val;
	if (pt->_cnt > 1)
	{
		os << "( " << pt->_cnt << " ) ";
	}
	else
	{
		os << ' ';
	}
}

template <typename elemtype>
void BTnode<elemtype>::preorder (BTnode *pt, ostream &os) const
{
	if (pt)
	{
		display_val (pt, os);
		if (pt->_lchild)
		{
			preorder (pt->_lchild, os);
		}
		if (pt->_rchild)
		{
			preorder (pt->_rchild, os);
		}
	}
}

template <typename elemtype>
void BTnode<elemtype>::inorder (BTnode *pt, ostream &os) const
{
	if (pt)
	{
		if (pt->_lchild)
		{
			inorder (pt->_lchild, os);
		}

		display_val (pt, os);

		if (pt->_rchild)
		{
			inorder (pt->_rchild, os);
		}
	}
}

template <typename elemtype>
void BTnode<elemtype>::postorder (BTnode *pt, ostream &os) const
{
	if (pt)
	{
		if (pt->_lchild)
		{
			postorder (pt->_lchild, os);
		}
		if (pt->_rchild)
		{
			postorder (pt->_rchild, os);
		}

		display_val (pt, os);
	}
}

template <typename elemtype>
inline ostream& operator<<(ostream &os, const BinaryTree<elemtype> &bt)
{
	os << "Tree: " <<endl;
	bt.inorder(os);
	return os;
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
		void clear() { if (_root) { clear (_root); } _root = 0; }

		void inorder (ostream &os = cout) const {_root->inorder (_root, os);}
		void postorder (ostream &os = cout) const {_root->postorder (_root, os);}
		void preorder (ostream &os = cout) const {_root->preorder (_root, os);}

		void insert(const elemtype &elem);
		void remove (const elemtype &elem);
	private:
		void clear (BTnode<elemtype>*);
		void remove_root();
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

template <typename elemtype>
inline void BinaryTree<elemtype>::remove (const elemtype &elem)
{
	if (_root)
	{
		if (_root->_val == elem)
		{
			remove_root();
		}
		else
		{
			_root->remove_value (elem, _root);
		}
	}
}

template <typename elemtype>
void BinaryTree<elemtype>::remove_root()
{
	if (!_root)
	{
		return;
	}

	BTnode<elemtype> *tmp = _root;

	if (_root->_rchild)
	{
		_root = _root->_rchild;

		if (tmp->_lchild)
		{
			BTnode<elemtype> *lc = tmp->_lchild;
			BTnode<elemtype> *newlc = _root->_lchild;

			if (!newlc)
			{
				_root->_lchild = lc;
			}
			else
			{
				BTnode<elemtype>::lchild_leaf (lc, newlc);
			}
		}
	}
	else
	{
		_root = _root->_lchild;
	}

	delete tmp;
}

template <typename elemtype>
void BinaryTree<elemtype>::clear (BTnode<elemtype> *pt)
{
	if (pt)
	{
		clear (pt->_lchild);
		clear (pt->_rchild);
		delete pt;
	}
}

#include <string>

int main()
{
	BinaryTree<string> bt;

	bt.insert ("Piglet");
	bt.insert ("Eeyore");
	bt.insert ("Roo");
	bt.insert ("Tigger");
	bt.insert ("Chris");
	bt.insert ("Pooh");
	bt.insert ("Kanga");

	cout << "Preorder traversal: \n";
	bt.preorder();

	bt.remove ("Piglet");
	cout << "\n\nPreorder traversal after Piglet removal: \n";
	bt.preorder();

	bt.remove ("Eeyore");
	cout << "\n\nPreorder traversal after Eeyore removal: \n";
	bt.preorder();
	
	cout << bt << endl;

	bt.clear();

	return 0;
}
