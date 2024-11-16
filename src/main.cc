/**
* @brief main file
* 
* @author Belosheev A.D.
*/

#include "inc/Subj.hpp"
#include <cstdlib>

using namespace LinkedList;
using namespace SubJList;


void menu() {
	SubjList* temp_list = new SubjList;
	Base* new_node = nullptr;

	Thread* t_thread = 0;

	int ii = 1, jj = 1;

	while (ii) {
		printf("-------\n"\
			"1. Insert element in list\n"\
			"2. Insert element in end of list\n" \
			"3. Sort list\n"\
			"4. Print list \n" \
			"5. Delete Node from list\n" \
			"6. Delete List \n"\
			"0. Exit\n-------\n");

		int number;
		std::cin >> number;
		switch (number) {

		case(1):
			system("cls");

			while (jj) {
				std::cout << "1. Create process.\n2. Create thread.\n";
				int numb = 0;
				std::cin >> numb;

				if (numb == 1) {
					new_node = temp_list->create(NodeType::process);

					system("cls");
					break;
				}
				else if (numb == 2) {
					new_node = Base::create(NodeType::thread);
					system("cls");
					break;
				}
			}
			std::cout << "Enter index node before which insert new: ";
			int i;
			std::cin >> i;
			temp_list->insert(new_node, i);
			system("cls");
			std::cout << "Success insert node in position:" << i << "\n";

			break;

		case(2):
			while (jj) {
				std::cout << "1. Create process.\n2. Create thread.\n";
				int numb = 0;
				std::cin >> numb;

				if (numb == 1) {
					new_node = temp_list->create(NodeType::process);

					system("cls");
					break;
				}
				else if (numb == 2) {
					new_node = temp_list->create(NodeType::thread);

					system("cls");
					break;
				}
			}
			temp_list->add(new_node);
			system("cls");
			std::cout << "Success add node end of list\n";
			break;

		case(3):
			temp_list->sort_by_priority();
			system("cls");
			printf("List Sorted\n");
			break;

		case(4):
			system("cls");
			temp_list->print();
			
			break;

		case(5):
			std::cout << "Enter index node which need to delete: ";
			std::cin >> i;
			temp_list->delete_node(i);
			system("cls");
			std::cout << "Success delete node in position:" <<  i << "\n";
			break;

		case(6):
			temp_list->clear();
			system("cls");
			std::cout << "List successfully deleted\n";
			break;

		case(0):
			ii = 0;
			temp_list->clear();
			delete temp_list;
			break;
		}
	}
}

int main(){
	
	menu();
	return 0;
}

