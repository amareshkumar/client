#include "my_project_app.h"
/***********************************
Linked list implentation of Stack
***********************************/

#include "MyStack.h"
#define Max_Stack_Size = 10;
	
void my_stack::stack::push(struct stack_node** first, int item){

	stack_node* stackNode = (stack_node*)malloc(sizeof(stackNode));
	stackNode->data = item;

	if (*first == NULL){
		cout << "empty stack\nadding items...\n\n";
	}

	stackNode->next = *first;
	*first = stackNode;

	cout << "Item added:\t\"" << item << "\"" << endl;
}

void my_stack::stack::display_stack(struct stack_node* first){
	if (first == NULL) {
		cout << "No items\n";
		return;
	}

	while (first != NULL){
		std::cout << first->data << " ";
		first = first->next;
	}
}

int my_stack::stack::pop(stack_node** first){
	stack_node* temp = *first;

	if (temp == NULL){
		cout << "stack underflow\n";
		return 0;
	}
	if (temp->next == NULL){
		cout << "\npopped item:\t" << temp->data << endl;
		cout << "this was the last item in the stack";
	}

	(*first) = temp->next;
	cout << "\npopped item:\t" << temp->data << endl;
	return temp->data;

}

int my_stack::stack::peek(struct stack_node* root)
{
	if (is_empty(root))
		return INT_MIN;
	return root->data;

	printf("Top element is %d\n", peek(root));
}

bool my_stack::stack::is_empty(stack_node* first){
	return false;
}

bool my_stack::stack::is_full(){
	return false;
}

/* Task: find out the length of the longest subarray that is balanced
//Client code to call following function
//client code starts
int no_of_entries = 0;
int input[sizeof(no_of_entries)];
cin >> no_of_entries;
int i = 0;
int value = 0;
while (i < no_of_entries){
cin >> value;
input[i++] = value;
}
//create an array if signed int
cout << "desired lenght: " << return_max_balanced_sub_array(input, no_of_entries) << endl;
//client code ends
*/
int my_stack::stack::return_max_balanced_sub_array(int input[], int no_of_entries) {
	struct stack_node* first = NULL;
	my_stack::stack mystack;

	mystack.push(&first, input[0]);
	static int max_bal_array = 1;

	for (int i = 1; i < no_of_entries; i++) {
		if (input[i] + mystack.peek(first) == 0) {
			max_bal_array++;
		}
		else {
			mystack.push(&first, input[i]);
		}
		if (i == no_of_entries && mystack.is_empty(first)) { return max_bal_array; }
		else { continue; }
	}
	return max_bal_array;
}


/*
//sample code to use for stacks operations and testing of mystack class
struct stack_node* first = NULL;
my_stack::stack mystack;
mystack.push(&first, 11);
mystack.push(&first, 21);
mystack.push(&first, 31);
mystack.push(&first, 41);
mystack.push(&first, 51);

mystack.display_stack(first);
std::cout << "Popping:\n";
mystack.pop(&first);
mystack.display_stack(first);
mystack.pop(&first);
mystack.display_stack(first);
mystack.pop(&first);
mystack.display_stack(first);
mystack.pop(&first);
mystack.display_stack(first);
mystack.pop(&first);
mystack.display_stack(first);

//underflow check
mystack.pop(&first);
*/