#include <iostream>
#include <vector>
#include <stdarg.h>

using namespace std;

class Queue {
private:
	vector <int> body;
public:
	void push(int element);
	int pop();
	Queue(int num, ...) {
        va_list args;
        va_start(args, num);
        while (num--) {
            body.push_back(va_arg(args, int));
        }
        va_end(args);
	}

};

void Queue::push(int element) {
    body.insert(body.begin(), element);
}

int Queue::pop() {
    if (!body.empty()) {
        int temp = body.back();
        body.pop_back();
        return temp;
    }
    cout << "The queue is empty";
    return -1;
}

int main() {
    Queue sany{2, 1, 145};
    cout << sany.pop() << sany.pop();
	return 0;
}
