/*
This was an interview assignment
Problem description:


*/
#include <iostream>
#include <string.h>
#include <stdint.h>

class MyString {
private:
	class Node {
	public:
		Node() : m_val(0), m_next(NULL) {}
		Node(char val, Node* next) : m_val(val), m_next(next) {}
		void set_char(char val) { m_val = val; }
		void set_next(Node* next) { m_next = next; }
		char get_char() const { return m_val; }
		Node* get_next() const { return m_next; }
		bool has_next() const { return (get_next() != NULL); }
	private:
		char m_val;
		Node* m_next;
	};
public:
	MyString() : m_head(NULL) {}
	~MyString() {
		Node* curNode = m_head;
		while (curNode != NULL) {
			Node* tmp = curNode;
			curNode = curNode->get_next();
			delete tmp;
		}
	}

	bool scan(const char* str);
	char* format() const;

	bool match_and_delete(const char* pattern);

private:
	Node * push_back(char val);

	Node* get_last_node() const;

private:
	Node * m_head;
};

bool MyString::scan(const char* str) {
	if (str == NULL)
		return false;

	while (*str != 0) {
		push_back(*str);
		str++;
	}
	return true;
}

char* MyString::format() const {
	static const uint32_t BUF_CNT = 6;
	static const uint32_t MAX_STREAM_LEN = 1024;
	static char buffers[BUF_CNT][MAX_STREAM_LEN];
	static uint32_t  turn = 0;

	turn = (turn + 1) % BUF_CNT;
	char* buffer = buffers[turn];

	Node* curNode = m_head;
	uint32_t len = 0;
	while (curNode != NULL && (len < MAX_STREAM_LEN - 1)) {
		*buffer = curNode->get_char();
		buffer++;
		len++;
		curNode = curNode->get_next();
	}
	*buffer = 0;
	return buffers[turn];
}

MyString::Node* MyString::push_back(char val) {
	if (m_head == NULL) {
		m_head = new Node(val, NULL);
		return m_head;
	}
	else {
		Node* lastNode = get_last_node();
		Node* newNode = new Node(val, NULL);
		lastNode->set_next(newNode);
		return newNode;
	}
}

MyString::Node* MyString::get_last_node() const {
	if (m_head == NULL)
		return m_head;
	else {
		Node* curNode = m_head;
		while (curNode->has_next()) {
			curNode = curNode->get_next();
		}
		return curNode;
	}
}

bool MyString::match_and_delete(const char* pattern) {
	//get node of current string

	Node* currentnode = m_head;
	Node* tempnode = nullptr;
	bool char_match = false;
	bool occured = false;
	const char* temp = pattern;

	if (temp) { //if pattern is not NULL
		tempnode = currentnode;
		while (tempnode->has_next()) { //one big iteration thorugh the list
			do {
				if (*temp == tempnode->get_char()) {
					char_match = true;
					tempnode = tempnode->get_next();
					temp++;
				}
				else { //didnt match patterns first char to the string's one, try next and dont forget to reset temp to pattern
					tempnode = tempnode->get_next();
					temp = pattern;
				}
			} while (char_match && (*temp != '\0'));

			occured = true;
			if (tempnode == nullptr) {
				currentnode->set_next(nullptr);
				break;
			}
			currentnode = tempnode;

			//reset the pattern pointer to start of it
			temp = pattern;
			continue;
		} //end of while loop
		return occured;
	}

	return false;
}

void unittest_1() {
	static const char* TEST_STR = "11011";
	MyString l;
	l.scan(TEST_STR);
	char* buf = l.format();
	if (strcmp(TEST_STR, buf) == 0) {
		std::cout << "Test Case 1 successful \n";
	}
	else {
		std::cout << "Test Case 1 failed \n";
	}
}

void unittest_2() {
	static const char* TEST_STR = "11011";
	static const char* PATTERN = "11";
	static const char* RESULT = "0";
	MyString l;
	l.scan(TEST_STR);
	bool ret = l.match_and_delete(PATTERN);
	char* buf = l.format();
	if ((strcmp(RESULT, buf) == 0) && ret) {
		std::cout << "Test Case 2 successful \n";
	}
	else {
		std::cout << "Test Case 2 failed \n";
	}
}

void unittest_3() {
	static const char* TEST_STR = "111101111";
	static const char* PATTERN = "101";
	static const char* RESULT = "111111";
	MyString l;
	l.scan(TEST_STR);
	bool ret = l.match_and_delete(PATTERN);
	char* buf = l.format();
	if ((strcmp(RESULT, buf) == 0) && ret) {
		std::cout << "Test Case 3 successful \n";
	}
	else {
		std::cout << "Test Case 3 failed \n";
	}
}

void unittest_4() {
	static const char* TEST_STR = "000010000";
	static const char* PATTERN = "00";
	static const char* RESULT = "1";
	MyString l;
	l.scan(TEST_STR);
	bool ret = l.match_and_delete(PATTERN);
	char* buf = l.format();
	if ((strcmp(RESULT, buf) == 0) && ret) {
		std::cout << "Test Case 4 successful \n";
	}
	else {
		std::cout << "Test Case 4 failed \n";
	}
}

void unittest_5() {
	static const char* TEST_STR = "111111111";
	static const char* PATTERN = "111111111";
	static const char* RESULT = "";
	MyString l;
	l.scan(TEST_STR);
	bool ret = l.match_and_delete(PATTERN);
	char* buf = l.format();
	if ((strcmp(RESULT, buf) == 0) && ret) {
		std::cout << "Test Case 5 successful \n";
	}
	else {
		std::cout << "Test Case 5 failed \n";
	}
}

void unittest_6() {
	static const char* TEST_STR = "111111111";
	static const char* PATTERN = "0";
	static const char* RESULT = "111111111";
	MyString l;
	l.scan(TEST_STR);
	bool ret = l.match_and_delete(PATTERN);
	char* buf = l.format();
	if ((strcmp(RESULT, buf) == 0) && !ret) {
		std::cout << "Test Case 6 successful \n";
	}
	else {
		std::cout << "Test Case 6 failed \n";
	}
}

int main() {
	unittest_1();
	unittest_2();
	unittest_3();
	unittest_4();
	unittest_5();
	unittest_6();
	return 0;
}
