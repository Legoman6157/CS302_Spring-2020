#include <iostream>
#include <string>

#include "link_list.cpp"

int main() {
	LinkedList<int> ll1,
						 ll2,
						 ll3;

	LinkedList<int>::Node *it1,
								 *it2,
								 *it3;

	std::string num1,
					num2;

	int carry = 0;

	while (std::cin >> num1 >> num2) {
		for (int i = 0; i < num1.size(); i++)
			ll1.push_front(num1[i]-'0');

		for (int j = 0; j < num2.size(); j++)
			ll2.push_front(num2[j]-'0');

		it1 = ll1.head;
		it2 = ll2.head;

		while ((it1 != NULL) || (it2 != NULL)) {
			if (it1 && it2)
				ll3.push_back(it1->data + it2->data + carry);
			else if (it1)
				ll3.push_back(it1->data + carry);
			else
				ll3.push_back(it2->data + carry);

			if (ll3.tail->data >= 10) {
				ll3.tail->data %= 10;
				carry = 1;
			} else
				carry = 0;

			if (it1)
				it1 = it1->next;
			if (it2)
				it2 = it2->next;
		}//while ((it1 != NULL) || (it2 != NULL))

		if (carry == 1) {
			ll3.push_back(1);
			carry = 0;
		}

		it3 = ll3.tail;
		for (; it3 != NULL; it3 = it3->last)
			std::cout << it3->data;

		std::cout << std::endl;

		ll1.clear();
		ll2.clear();
		ll3.clear();
	}
}//main
