#include <iostream>
#include <string>

#include "link_list.cpp"

int main() {
	std::string num1,
					num2;
	
	int carry = 0;

	while (std::cin >> num1 >> num2) {	
		std::cout << "Given numbers: " << num1 << ' ' << num2 << std::endl;
		LinkedList<int> ll1;
		for (int i = 0; i < num1.size(); i++)
			ll1.push_front(num1[i]-'0');
		
		LinkedList<int> ll2;
		for (int i = 0; i < num2.size(); i++)
			ll2.push_front(num2[i]-'0');

		LinkedList<int>::Node* temp1 = ll1.head;
		LinkedList<int>::Node* temp2 = ll2.head;
		for (; (temp1 != NULL && temp2 != NULL); temp1 = temp1->next, temp2 = temp2->next) {
			temp1->data = (temp1->data + temp2->data) + carry;
			if (temp1->data >= 10) {
				temp1->data %= 10;
				if (temp1->next == NULL)
					ll1.push_back(1);
				else
					carry = 1;
			} else
				carry = 0;
		}

		temp1 = ll1.tail;
		while (temp1 != NULL) {
			std::cout << temp1->data;
			temp1 = temp1->last;
		}
		std::cout << std::endl;
	}
}//main
