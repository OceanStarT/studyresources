//https://leetcode-cn.com/problems/implement-queue-using-stacks/
class MyQueue {
public:
    /** Initialize your data structure here. */
    queue<int> q;
    MyQueue() {
        q = queue<int>();
    }
    
    /** Push element x to the back of queue. */
    void push(int x) {
        q.push(x);
    }
    
    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        int k = q.front();
        q.pop();
        return k;
    }
    
    /** Get the front element. */
    int peek() {
        return q.front();
    }
    
    /** Returns whether the queue is empty. */
    bool empty() {
        if(q.size()==0) return true;
        return false;
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */