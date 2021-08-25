#pragma once

namespace my_stack {
	//struct decl
	struct stack_node;
	//class decl
	class stack;
}; //end of namespace my_stack

//structure of stack node
struct my_stack::stack_node {
	int data;
	struct stack_node* next;
};

class my_stack::stack {
public:
	bool is_empty(struct stack_node*);
	bool is_full();
	void push(struct stack_node**, int item);
	int pop(struct stack_node**);
	int peek(struct stack_node* root);
	void display_stack(struct stack_node* first);
	//newly added function
	int return_max_balanced_sub_array(int input[], int no_of_entries);
};