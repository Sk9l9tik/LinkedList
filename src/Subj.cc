﻿#include "inc/Subj.hpp"

namespace SubJList {
	using namespace LinkedList;
	//Base
	Base* Base::create(NodeType type) {
		Base* node = nullptr;
		if (type == NodeType::process) {
			node = (Base*) new Process;
			node->set_next_null();
			node->set_prev_null();
			node->set_type(NodeType::process);
			node->input();
		}
		else if (type == NodeType::thread) {
			node = (Base*) new Thread;
			node->set_next_null();
			node->set_prev_null();
			node->set_type(NodeType::thread);
			node->input();
		}
		return node;
	}

	bool Base::operator>(Base& rhs) {
		return priority_ > rhs.priority();
	}

	bool Base::operator>(int& rhs) {
		return priority_ > rhs;
	}

	//Process
	void Process::print() const {
		std::cout << "---\nProcess:\n";
		std::cout << "Priority: " << priority_ << "\nPID: " << PID_ << "\nSize : " << size_ << " \nCreation time : " << creation_time_ << "\n";
	}

	void Process::input() {
		std::cout << "Enter pritority:";
		std::cin >> priority_;
		static int PID_count = 0;
		PID_ = PID_count++;
	}

	//Thread
	void Thread::print() const {
		std::cout << "---\nThread:\n";
		std::cout << "Priority: " << priority_ << "\nParent PID : " << parentPID_ << "\nCreation time : " << creation_time_ << "\n---\n";
	}

	void Thread::input() {
		std::cout << "Enter pritority:";
		std::cin >> priority_;
		std::cout << "Enter parent PID : ";
		std::cin >> parentPID_;
	}


	//SubjList
	void SubjList::print() const {
		Base* node = (Base*)head_;

		if (!node)
			std::cout << "List is empty!!!\n";

		for (int i = 0, end = size(); i < end; i++) {
			(*this)[i].print();
		}
	}

	Process* SubjList::find_process_by_PID(int PID) const{
		if (!head_) {
			return nullptr;
		}

		Process* tmp_process = (Process*)head_;
		while (tmp_process->pid() != PID) {
			tmp_process = (Process*)tmp_process->pnext();
		}
		return tmp_process;
	}

	int SubjList::count_child_threads(int parentPID) const{
		int count = 0;

		Base* tmp_thread = (Base*)head_;

		while (tmp_thread) {
			if (tmp_thread->type() == NodeType::thread)
				if (tmp_thread->type() == NodeType::thread && ((Thread*)tmp_thread)->parentpid() == parentPID)
					count++;
			tmp_thread = (Base*)tmp_thread->pnext();
		}
		return count;
	}

	int SubjList::count_child_threads_after_node(Base* node, int parentPID) const{
		int count = 0;
		Base* t = node;
		while (t) {
			if (t->type() == NodeType::thread) {
				Thread* tmp_thread = (Thread*)t;
				if (tmp_thread->parentpid() == parentPID)
					count++;
			}
			t = (Base*)t->pnext();
		}
		return count;
	}

	Base* SubjList::create(NodeType type) {
		Base* created = Base::create(type);
		if (created->type() == NodeType::process) {
			Base* t_thread = new Thread(((Process*)created)->pid());
			t_thread->set_type(NodeType::thread);
			((Thread*)t_thread)->print();
			this->insert(t_thread, 0);
		}
		return created;
	}

	void SubjList::delete_node(int index) {
		Base* tmp_base = (Base*)remove(index);

		if (!tmp_base) {
			return;
		}

		if (tmp_base->type() == NodeType::thread) {
			Thread* tmp_thread = (Thread*)tmp_base;
			if (count_child_threads(tmp_thread->parentpid()) == 1) {
				delete_node(get_index((Node*)find_process_by_PID(tmp_thread->parentpid())));
				delete tmp_base;
			}
		}
		else {
			Process* tmp_process = (Process*)tmp_base;

			Base* tmp_base_2 = (Base*)head_;

			int tmp_index = 0, tmp_pid = tmp_process->pid();
			while (tmp_base_2) {
				if (tmp_base_2->type() == NodeType::thread && ((Thread*)tmp_base_2)->parentpid() == tmp_pid) {
					tmp_base_2 = (Base*)tmp_base_2->pnext();
					delete_node(tmp_index);
				}
				else {
					tmp_index++;
					tmp_base_2 = (Base*)tmp_base_2->pnext();
				}
			}
			delete tmp_base;
		}

	}

	Base* SubjList::sort_process(Base* node) {

		Base* t = node;
		int max_process_priority = -21;
		Base* temp_max_process = NULL;

		/// find max priority proicess
		while (t) {
			Base* tmp = t;
			if (tmp->type() == NodeType::process) {
				if (*tmp > max_process_priority) {
					max_process_priority = tmp->priority();
					temp_max_process = tmp;
				}
			}
			t = (Base*)t->pnext();
		}

		swap_node((Node*)node, (Node*)temp_max_process);

		return temp_max_process;

	}

	Base* SubjList::sort_threads(Base* node, int parentPID) {
		Base* t = node;
		Base* tmp_max_thread = NULL;
		int max_thread_priority = -21;
		/// find max priority thread with PID
		while (t) {
			Base* tmp = t;
			if (tmp->type() == NodeType::thread && ((Thread*)tmp)->parentpid() == parentPID) {
				if (*tmp > max_thread_priority) {
					max_thread_priority = tmp->priority();
					tmp_max_thread = tmp;
				}
			}
			t = (Base*)t->pnext();
		}

		swap_node(((Node*)node), (Node*)tmp_max_thread);
		return tmp_max_thread;
	}

	void SubjList::sort_by_priority() {
		Node* t = head_;
		/// main cycle in which sorting list
		while (t && t->pnext()) {
			Node* temp_max_process = sort_process((Base*)t);
			Node* temp_last_thread = temp_max_process->pnext(); ///< pnext() node after sorted process
			/// in this cycle sotring all threads owned by temp_max_process, this cycle work while list has more 0 this process child thread or temp_last_thread is last in list
			while (temp_last_thread && temp_last_thread->pnext() && count_child_threads_after_node((Base*)temp_last_thread, ((Process*)temp_max_process)->pid()) > 0) {

				/// this fuction find pnext() thread with ParentPID = PID and swap it with the pnext() unsorted element
				Node* temp_max_thread = sort_threads((Base*)temp_last_thread, ((Process*)temp_max_process)->pid());

				temp_last_thread = temp_max_thread->pnext();
			}
			t = temp_last_thread;
		}
	}

	Base& SubjList::operator[](int index) const {
		if (index < 0 || index >= size()) throw std::out_of_range("List index out of range!!!!");
		return *(Base*)get_node(index);
	}
}	