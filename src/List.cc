#include "inc/List.h"


namespace LinkedList {
	
	List::~List() {
		this->clear();
	}

	Node* List::get_node(int index) {
		int i = 0;
		if (index < 0 || !head_) return nullptr;

		Node* t = head_;
		while (i < index && t) {
			t = &t->next();
			i++;
		}
		return t;
	}
	
	int List::get_index(Node* node) {
		if (!node) return -1;

		int i = 0;
		Node* t = head_;
		while (t && t != node) {
			i++;
			t = t->pnext();
		}
		return i;
	}

	int List::size() const {
		Node* t = head_;
		int size = 0;
		while (t) {
			size++;
			t = t->pnext();
		}
		return size;
	}

	void List::print() {
		Node* t = head_;
		std::cout << "List:" << this << "\t head:" << head_ << "\ttail:" << tail_ << "\n";
		std::cout << "#\tNode\t\t prev\t\t next\n";
		int i = 0;
		while (t) {
			std::cout << i << "\t";
			t->print();
			i++;
			t = &(t->next());
		}
	}

	bool List::empty() const {
		if (!head_ && !tail_)
			return false;
		else
			return true;
	}

	Node* List::create() {
		Node* new_node = new Node;
		//Calb`s line
		return new_node;
	}

	
	Node* List::add(Node* node) {

		if (!node) return nullptr;

		if (!head_ && !tail_) {
			head_ = node;
			tail_ = node;
			node->set_parent(this);
			return node;
		}
		else {
			node->set_prev(tail_);
			node->set_next_null();
			tail_->set_next(node);
			tail_ = node;
			node->set_parent(this);
			return node;
		}

	}

	Node* List::insert(Node* node, int index) {
		insert_after(node, index - 1);
		return node;
	}

	Node* List::insert_after(Node* node, int index){
		Node* tmp_node = get_node(index);

		if (!node) return nullptr;

		if (!head_ && !tail_ || index > size()) {
			add(node);
		}

		else if (!tmp_node) {
			node->set_prev_null();
			node->set_next(head_);
			head_->set_prev(node);
			head_= node;
		}

		else if (tmp_node->pnext()) {
			node->set_prev(tmp_node);
			node->set_next(tmp_node->pnext());
			tmp_node->pnext()->set_prev(node);
			tmp_node->set_next(node);
		}

		else if (!tmp_node->pnext()) {
			add(node);
		}
		return node;
	}

	Node* List::remove(int index) {

		Node* node = get_node(index);

		if (!node) {
			return nullptr;
		}

		else if (!node->pnext() && node->pprev()) {
			tail_ = node->pprev();
			node->set_prev_null();
			tail_->set_next_null();
		}
		else if (!node->pprev() && node->pnext()) {
			head_ = node->pnext();
			head_->set_prev_null();
			node->set_next_null();
		}
		else if (!node->pnext() && !node->pprev()) {
			node->set_next_null();
			node->set_prev_null();
			head_ = nullptr;
			tail_ = nullptr;
		}
		else {
			node->prev().set_next(node->pnext());
			node->next().set_prev(node->pprev());
			node->set_next_null();
			node->set_next_null();
		}
		return node;
	}


	void List::delete_node(int index) {
		delete remove(index);
	}


	void List::clear() {
		while (head_)
			delete_node(0);
	}

	void List::swap(List& other) {

		Node* t_head = head_, * t_tail = tail_;
		//line
		head_ = other.phead();
		tail_ = other.ptail();
		other.set_head(t_head);
		other.set_tail(t_tail);
	}

	void List::swap_node(Node* lhs, Node* rhs) {
		if (!lhs || !rhs || lhs == rhs)
			return;

		Node* lhs_prev = lhs->pprev();
		Node* lhs_next = lhs->pnext();

		Node* rhs_prev = rhs->pprev();
		Node* rhs_next = rhs->pnext();

		if (lhs_prev != 0) {
			lhs_prev->set_next(rhs);
		}
		else {
			head_ = rhs;
		}

		if (lhs_next != 0) {
			lhs_next->set_prev(rhs);
		}
		else {
			tail_ = rhs;
		}

		if (rhs_prev != 0) {
			rhs_prev->set_next(lhs);
		}
		else {
			head_ = lhs;
		}

		if (rhs_next != 0) {
			rhs_next->set_prev(lhs);
		}
		else {
			tail_ = lhs;
		}

		lhs->set_prev(lhs == rhs_prev ? rhs : rhs_prev);
		lhs->set_next(lhs == rhs_next ? rhs : rhs_next);

		rhs->set_prev(rhs == lhs_prev ? lhs : lhs_prev);
		rhs->set_next(rhs == lhs_next ? lhs : lhs_next);
	}
}