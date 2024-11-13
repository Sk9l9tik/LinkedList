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
		* @param[in] type type of Base Node
		* @return Base poiner
		*/
		static Base* create(NodeType type);
		/** 
		* @brief Setter by type field
		* @param Type of node
		*/
		void set_type(NodeType type) { type_ = type; }

		/// Fuction to input firlds in base node
		void input();
	public:
		/**
		* @brief Type getter
		* @return Type of node;
		*/
		NodeType type() { return type_; }
		/**
		* @brief Priority getter
		* @return Node priority;
		*/
		int priority() { return priority_; }

		/// Print node function
		void print() const;
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
		* @brief PID getter
		* @return Process pid;
		*/
		int pid() { return PID_; }

		/**
		* @brief Size getter
		* @return Size of process;
		*/
		int size() { return size_; }

		/// Print node function
		void print() const;

		/// Fuction to input firlds in base node
		void input();		
	};

	class Thread final : public Base {
		int parentPID_; ///< Parent PID of thgread

	public:
		Thread() : parentPID_(0) {};
		Thread(int parentPID) : parentPID_(parentPID) {};
	public:
		/**
		* @brief Parent PID getter
		* @return Parent PID of thread;
		*/
		int parentpid() { return parentPID_; }

		/// Print node function
		void print() const;
	public:
		/// Fuction to input firlds in base node
		void input();

		///@brief Fubction set parentpid
		void set_parentpid(int parentpid) { parentPID_ = parentpid; }
		
	};

	class SubjList final : public LinkedList::List {
	public:
		/// Print SubjList function
		void print();

		/**
		* @brief Find process in List by his PID
		* @param[in] Process PID
		* @return Pointer to Process Node
		*/
		Process* find_process_by_PID(int PID);
		
		/**
		* @brief Count child thread by parent PID
		* @param[in] Thread parent PID
		* @return Count of chield threads
		*/
		int count_child_threads(int parentPID);

		/**
		* @brief Count child thread by parent PID after node in list
		* @param[in] Base node pointer to node after his find count child threads
		* @param[in] Thread parent PID
		* @return Count of chield threads after node
		*/
		int count_child_threads_after_node(Base* node, int parentPID);
	
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
		* @brief Sort process in list by priority
		* @param[in] Poinert to unsorted node
		* @return Pointer to sorted process
		*/
		Base* sort_process(Base* node);
		
		/**
		* @brief Sort threads in list by priority
		* @param[in] Poinert to unsorted node
		* @param[in] Thread parent PID
		* @return Pointer to sorted thread
		*/
		Base* sort_threads(Base* node, int parentPID);

		/**
		* @brief Sort List by priority process and threads
		*/
		void sort_by_priority();

	};
}

#endif
