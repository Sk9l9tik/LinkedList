#ifndef SUBJ_H
#define SUBJ_H

#include "List.h"


namespace SubJList {

	/**
	* @brief Enum class with node types
	*/
	enum class NodeType {
		unknown, // 0
		process, // 1
		thread	 // 2
	};

	class Base : public LinkedList::Node{
	protected:
		NodeType type_ = NodeType::unknown; ///< Type of node
		time_t creation_time_ = 0;
		int priority_ = 0;

	public:
		Base() : priority_(0) {}
		Base(int priority) : priority_(priority) {}
		virtual ~Base() = default;
	public:
		/**
		* @brief Memory allocator by type.
		* @param[in] type type of Base Node.
		* @return Base poiner
		*/
		static Base* create(NodeType type);
		/** 
		* @brief Setter by type field.
		* @param Type of node.
		*/
		void set_type(NodeType type) { type_ = type; }

		/// Fuction to input firlds in base node.
		virtual void input() = 0;
	public:
		/**
		* @brief Type getter.
		* @return Type of node.
		*/
		virtual NodeType type() const = 0;
		/**
		* @brief Priority getter.
		* @return Node priority.
		*/
		int priority() const { return priority_; }

		/// Print node function.
		virtual void print() const = 0;
	public:
		
		/**
		* @brief Overloaded operator >. This copmares priority fields of 2 nodes.
		* @param[in] rhs Reference to Base type Node.
		* @return bool value.
		*/
		bool operator>(Base& rhs);
		
		/**
		* @brief Overloaded operator >. This copmares priority node and param rhs value.
		* @param[in] rhs Reference to int value of priority.
		* @return bool value.
		*/
		bool operator>(int& rhs);
	};

	class Process final: public Base {
		int PID_; /// Process PID
		int size_ = 1;
	public:
		Process() : PID_(0) {}
		Process(int PID) : PID_(PID) {}
		Process(int PID, int size) : PID_(PID), size_(size) {}
	public:
		/**
		* @brief PID getter.
		* @return Process pid;
		*/
		int pid() const { return PID_; }

		/**
		* @brief Size getter.
		* @return Size of process.
		*/
		int size() const { return size_; }

		/// Print node function
		void print() const override;

		/// Fuction to input firlds in base node.
		void input() override;	

		/// Fucntion returned type of Node. @return NodeType::process.
		NodeType type() const override { return NodeType::process; }
	};

	class Thread final : public Base {
		int parentPID_; ///< Parent PID of thgread

	public:
		Thread() : parentPID_(0) {};
		Thread(int parentPID) : parentPID_(parentPID) {};
	public:
		/**
		* @brief Parent PID getter.
		* @return Parent PID of thread.
		*/
		int parentpid() const { return parentPID_; }

		/// Fucntion returned type of Node.  @return NodeType::thread.
		NodeType type() const override { return NodeType::thread; }
		
		/// Print node function.
		void print() const override;
	public:
		/// Fuction to input fields in base node.
		void input() override;

		/**
		* @brief Function set parent pid.
		* @param[in] parentpid Parent pid of Thread.
		*/
		void set_parentpid(int parentpid) { parentPID_ = parentpid; }
	public:

	};

	class SubjList final : public LinkedList::List {
	public:
		/// Print SubjList function.
		void print() const override;

		/**
		* @brief Find process in List by his PID.
		* @param[in] Process PID.
		* @return Pointer to Process Node.
		*/
		Process* find_process_by_PID(int PID) const;
		
		/**
		* @brief Count child thread by parent PID.
		* @param[in] Thread parent PID.
		* @return Count of chield threads.
		*/
		int count_child_threads(int parentPID) const;

		/**
		* @brief Count child thread by parent PID after node in list.
		* @param[in] Base node pointer to node after his find count child threads.
		* @param[in] Thread parent PID.
		* @return Count of chield threads after node.
		*/
		int count_child_threads_after_node(Base* node, int parentPID) const;
	
	public:


		/**
		* @brief Memory allocator by type.
		* @param[in] type Type of Base Node.
		* @return Base poiner.
		*/
		Base* create(NodeType type);

		/**
		* @brief Delte node by index (Not eq List function)
		* @param[in] Deleted node index
		*/
		void delete_node(int index);

		/**
		* @brief Sort process in list by priority.
		* @param[in] Poinert to unsorted node.
		* @return Pointer to sorted process.
		*/
		Base* sort_process(Base* node);
		
		/**
		* @brief Sort threads in list by priority.
		* @param[in] Poinert to unsorted node.
		* @param[in] Thread parent PID.
		* @return Pointer to sorted thread.
		*/
		Base* sort_threads(Base* node, int parentPID);

		/**
		* @brief Sort List by priority process and threads.
		*/
		void sort_by_priority();
	public:
		/**
		* @brief Overload operator [].
		* @param[in] index Index of node in list.
		* @return Reference to Node in index position on list.
		* @warning If index goes beyond of list throw the std::out_of_range exception
		*/
		Base& operator[](int index) const ;
	};
}

#endif
