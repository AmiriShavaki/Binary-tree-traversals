#include <iostream>
#include <utility> //Using pair
#include <cstring> //Using memset

using namespace std;

class Node {
	private:
		int* value;
		Node* next;
		
	public:
		Node(int& value, Node* next);
		int* getValue() { return value; }
		Node* getNext() { return next; }
};

Node::Node(int& value, Node* next) {
	this -> value = new int;
	*(this -> value) = value;
	this -> next = next;
}

class Stack {
	private:
		int size;
		int filled;
		Node* top;
		
	public:
		Stack(int size) { this -> size = size; filled = 0; top = NULL; }
		bool push(int value);
		int pop();
		int peek() { return (is_empty() ? 0 : *(top -> getValue())); }
		bool is_empty() { return filled == 0; }
		bool is_full() { return size == filled; }
		int getSize() { return filled; }
		bool clear() { top = NULL; filled = 0; return true; }
};

bool Stack::push(int value) {
	if (is_full()) {
		return false;
	} 
	Node* newElem = new Node(value, top);
	top = newElem;
	filled++;
	return true;
}

int Stack::pop() {
	//cout << "filled:" << filled << "   is_empty:" << is_empty() << endl;
	if (is_empty()) {
		return 0;
	} 
	int res = *(top -> getValue());
	top = top -> getNext();
	filled--;
	return res;
}

const int N = 100005;

string val[N];
pair < int, int > G[N];
bool mark[N];

int main() {
	int i = 0;
	while (cin >> val[i]) {
		int l, r;
		cin >> l >> r;
		G[i].first = l;
		G[i].second = r;
		i++;
	}
	
	Stack s(N);
	
	//In order
	s.push(0);
	while (!s.is_empty()) {
		int top = s.pop();
		if (mark[top]) {
			cout << val[top] << " ";
			continue;
		}
		mark[top] = true;
		if (G[top].second != -1) {
			s.push(G[top].second);
		}
		s.push(top);
		if (G[top].first != -1) {
			s.push(G[top].first);
		}
	}
	
	//Pre order
	cout << endl;
	s.push(0);
	while (!s.is_empty()) {
		int top = s.pop();
		cout << val[top] << " ";
		if (G[top].second != -1) {
			s.push(G[top].second);
		}
		if (G[top].first != -1) {
			s.push(G[top].first);
		}
	}
	
	//Post order
	memset(mark, false, sizeof(mark));
	cout << endl;
	s.push(0);
	while (!s.is_empty()) {
		int top = s.pop();
		if (mark[top]) {
			cout << val[top] << " ";
			continue;
		}
		mark[top] = true;
		s.push(top);
		if (G[top].second != -1) {
			s.push(G[top].second);
		}
		if (G[top].first != -1) {
			s.push(G[top].first);
		}
	}
}
