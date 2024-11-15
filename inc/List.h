#ifndef LIST_H
#define LIST_H

#include <iostream>

namespace LinkedList {

	class Node;
	
	/**
	* @brief The struct model of a double linked list.
	*/
	class List {
	protected:
		Node* head_;	///< Poiter to the first Node in list.
		Node* tail_;	///< Poiter to the last Node in list.

	public:
		List() : head_(nullptr), tail_(nullptr) {}

		List(Node* head, Node* tail) : head_(head), tail_(tail) {}
		
		virtual ~List();

	public:
		/**
		* @brief Returns a reference to the first element in list.
		* 
		* @param (none)
		* @return Reference(pointer) the first element.
		* @addtogroup head
		* @{
		*/
		Node& head() { return *head_; }
		Node* phead() { return head_; }
		const Node& head() const { return *head_; }
		/**}@*/

		/**
		* @brief Returns a reference to the last element in list.
		*
		* @param (none)
		* @return Reference(pointer) the last element.
		* @addtogroup tail
		* @{
		*/
		Node& tail() { return *tail_; }
		Node* ptail() { return tail_; }
		const Node& tail() const { return *tail_; }
		/**}@*/

		/**
		* @brief Get node pointer by index.
		* @param index Index of node. If index > size list return nullptr.
		* @return Pointer to Node
		*/
		Node* get_node(int index);

		/**
		* @brief Get index of node by pointer.
		* @param node Pointer to node.
		* @return Index of node.
		*/
		int get_index(Node* node) ;

		/**
		* @brief Get size of list.
		* @param (none)
		* @return Count of nodes.
		*/
		int size() const;

		/**
		* @brief Print list (#i node ...)
		* @param (none)
		*/
		virtual void print() const;

		/**
		* @brief Check list for emptiness.
		* @param (none)
		* @return Bool value: list empty or not.
		*/
		bool empty() const;

	public:


		/**
		* @brief Setters. Set fields head and tail new value.
		* @parem head/tail New pointers.
		* @addtogroup set_head_tail_value
		* @{
		*/
		Node* set_head(Node* head) { head_ = head; return head; }
		Node* set_tail(Node* tail) { tail_ = tail; return tail; }
		/**}@*/

		/**
		* @brief Allocate memory for nodem.
		* @param (none)
		* @return Pointer to allocated memory.
		*/
		static Node* create();

		/**
		* @brief Push back a new node in list.
		* @param node Pointer to created node.
		* @return Pointer to new inserted node.
		*/
		Node* add(Node* node);

		/**
		* @brief Insert a new node in list before node in "index" position.
		* @param node Pointer to created node.
		* @param index Position node before which need insert a new node.
		* @return Pointer to new inserted node.
		*/
		Node* insert(Node* node, int index);

		/**
		* @brief Function insert a Node after an element by index.
		* @param[in] node The pointer to the item is inserted into the ListNode.
		* @param[in] index Number of the item after which you need insert Node.
		* @return Poinert to new inserted node.
		*/
		Node* insert_after(Node* node, int index);

		/**
		* @brief Remove node from list.
		*
		* @param index Position node which need to be removed.
		* @return Pointer removed node.
		*/
		Node* remove(int index);

		/**
		* @brief Delete node.
		*
		* @param index Position node which need to be deleted.
		*/
		void delete_node(int index);

		/**
		* @brief Delete list method.
		* @param (none)
		*/
		void clear();

		/**
		* @brief swap lists.
		* param othrer swaped list.
		*/
		void swap(List& other);

		/**
		* @brief						The fucnvion swap 2 nodes in list.
		* @param[in]		list		The pointer to ListNode.
		* @param[in|out]	node		First swaped node.
		* @param[in|out]	node		Second swaped node.
		* @waning						The first pointer to the node should go to the left node.
		*/
		void swap_node(Node* left, Node* right);
	};

	/**
	* @brief The class node model of a double linked list.
	*/
	class Node {
		Node* next_;	///< Pointer no the next node.
		Node* prev_;	///< Pointer no the previous node.
		List* parent_;	///< Pointer to the list.

	public:
		Node() : next_(nullptr), prev_(nullptr), parent_(nullptr) {}

		Node(Node* prev, Node* next) : prev_(prev), next_(next), parent_(nullptr) {
			if (prev != nullptr) prev->next_ = this;
			if (next != nullptr) next->prev_ = this;
		}

		Node(const Node& other) = delete;

		Node& operator=(const Node& other) = delete;

		virtual ~Node() { if (parent_ != nullptr) parent_->delete_node(parent_->get_index(this)); }

	public:
		/**
		* @brief Returns the reference to the next node.
		*
		* @param (none)
		* @return Reference to the next element.
		* @addtogroup next
		* @{
		*/
		Node& next() { return *next_; }
		Node* pnext() { return next_; }
		const Node& next() const { return *next_; }
		/**}@*/

		/**
		* @brief Returns the reference to the previous node.
		*
		* @param (none)
		* @return Reference to the previous element.
		* @addtogroup prev
		* @{
		*/
		Node& prev() { return *prev_; }
		Node* pprev() { return prev_; }
		const Node& prev() const { return *prev_; }
		/**}@*/

		inline void print() { std::cout << this << " " << prev_ << " " << next_ << "\n"; }

	public:
		/**
		* @brief Setters. Set fields next and prev new value.
		* @parem next/prev New pointers.
		* @addtogroup set_next_prev_value
		* @{
		*/
		Node* set_next(Node* next) { next_ = next; return next; }
		Node* set_prev(Node* prev) { prev_ = prev; return prev; }
		/**}@*/

		/**
		* @brief Setters. Set fields next and prev to nullptr.
		* @parem (none)
		* @addtogroup set_next_prev_nullptr
		* @{
		*/
		void set_next_null() { next_ = nullptr; }
		void set_prev_null() { prev_ = nullptr; }
		/**}@*/


		/**
		* @brief Set parent.
		* @param list Pointer to the parent list.
		*/
		void set_parent(List* list) { parent_ = list; }
	};
}

#endif
