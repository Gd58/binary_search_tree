#ifndef  _BINARY_SEARCH_TREE_
#define _BINARY_SEARCH_TREE_
#ifndef __MALLOC_ALLOC_TEMPLATE__
#include "__malloc_alloc_template.h"
#endif
#ifndef __ALLOCATOR__
#include "allocator.h"
#endif
#ifndef __G_FUN__
#include "g_func.h"
#endif
template<class T>
struct bst_node{
	bst_node<T> *lChild;
	bst_node<T> *rChild;
	bst_node<T> *parent;
	T data;
};
template<class T, class Alloc = default_alloc>
class binary_search_tree{
public:
	typedef T value_type;
	typedef T& reference;
	typedef T* pointer;
	typedef ptrdiff_t different_type;
	typedef size_t size_type;
	typedef typename bst_node<T> node;
	typedef typename __allocator<node, Alloc> allocator_t;
public:
	binary_search_tree() :root(nullptr){}
	node* search_node(value_type lhs){
		node *_tmp = nullptr;
		node *_bst = root;
		
		while(_bst){
		if(_bst->data == lhs||!_bst) break;
		else if(_bst->data > lhs)
		_bst = _bst->lChild;
		else
		_bst = _bst->rChild;
		}
		return _bst;
		/*
		here two way to do it
		while (_bst && lhs != _bst->data){
			if (_bst->data >= lhs)
				_bst = _bst->lChild;
			else
				_bst = _bst->rChild;
		}
		return _bst;
		*/
	}
	node* create_node(value_type lhs){
		node* tmp =(node*) allocator_t::allocate();
		construct(&tmp->data, lhs);
		tmp->lChild = nullptr;
		tmp->rChild = nullptr;
		tmp->parent = nullptr;
		return tmp;
	}
	void insert_node(value_type lhs){
		node* _tmp = root;
		node* _cur_bst = nullptr;
		node* result = create_node(lhs);
		if (!_tmp) {
			root = result;
			return;
		}
		while (_tmp){
			_cur_bst = _tmp;
			if (_tmp->data > lhs)
				_tmp = _tmp->lChild;
			else
				_tmp = _tmp->rChild;
		}
		result->parent = _cur_bst;
		if (_cur_bst == nullptr){
			root = result;
		}
		else if (_cur_bst->data > lhs){
			_cur_bst->lChild = result;
		}
		else{
			_cur_bst->rChild = result;
		}
		
	}
	void __destory(node *lhs){
		//static_assert(lhs != nullptr);
		destory(&lhs->data);
		allocator_t::deallocate(lhs);
	}

	void delete_node(value_type lhs){
		node *tar_node = search_node(lhs);
		if (tar_node->lChild == nullptr && tar_node->rChild != nullptr)
			node_translant(tar_node, tar_node->rChild);
		else if (tar_node->lChild != nullptr && tar_node->rChild == nullptr)
			node_translant(tar_node, tar_node->lChild);
		else
		{
			node* tmp = min_node(tar_node->rChild);

			if (tmp->parent != tar_node)
			{
				node_translant(tmp, tmp->rChild);
				tmp->rChild = tar_node->rChild;
				tmp->rChild->parent = tmp;
				//tmp->rChild = tar_node->lChild;
			}
				node_translant(tar_node, tmp);
				tmp->lChild = tar_node->lChild;
				tmp->lChild->parent = tmp;
		}

		__destory(tar_node);
	}
	node *min_node(node* lhs){
		node* _bst = lhs;
		node* result = nullptr;
		while (_bst){
			result = _bst;
			_bst = _bst->lChild;
		}
		return result;
	}
	node *max_node(node * lhs){
		node* _bst = lhs;
		node* result = nullptr;
		while (_bst)
		{
			result = _bst;
			_bst = _bst->rChild;
		}
		return result;
	}
	void node_translant(node* lhs, node* rhs)
	{
		if (lhs->parent==nullptr)
			rhs = lhs;
		else if (lhs->parent->lChild == lhs)
			lhs->parent->lChild = rhs;
		else
			lhs->parent->rChild = rhs;

		if (rhs)
		rhs->parent = lhs->parent;
	}

		/*
		node* l_child = lhs->lChild;
		node* r_child = lhs->rChild;
		// here exchange the lhs's parent's child
		if (lhs->parent->lChild == lhs)
		lhs->parent->lChild = rhs;
		else
		lhs->parent->rChild = rhs;
		//here exchange the rhs' parent's child
		if (rhs->parent->lChild == rhs)
		rhs->parent->lChild = lhs;
		else
		rhs->parent->rChild = lhs;
		//here exchange the rhs's and lhs's parent
		node* tmp = rhs->parent;
		rhs->parent = lhs->parent;
		lhs->parent = tmp;

		//here exchange the rhs's and lhs's parent
		lhs->lChild = rhs->lChild;
		lhs->rChild = rhs->lChild;
		rhs->lChild = l_Child;
		rhs->rChild = r_Child;
		*/
		


	
	void print(node* lhs){
		if (lhs==nullptr) return;
		print(lhs->lChild);
		std::cout << lhs->data << std::endl;
		print(lhs->rChild);
	}
	node* get_root(){ return root; }
private:
	node* root;
};
#endif