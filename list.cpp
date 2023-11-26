#include <iostream>

template <typename T>
class List
{
private:
    struct Node
    {
        T data;
        Node* next;
        Node* prev;
        Node(const T& d = T{}, Node* n = nullptr, Node* p = nullptr)
            : data{ d }, next{ n }, prev{ p } {}
    };
    Node* head;
    Node* tail;
    int size;
public:
    List() : head{ nullptr }, tail{ nullptr }, size{ 0 } {}
    List(const List& rhs) : head{ nullptr }, tail{ nullptr }, size{ 0 }
    {
        Node* p = rhs.head;
        while (p != nullptr)
        {
            push_back(p->data);
            p = p->next;
        }
    }
    List& operator=(const List& rhs)
    {
        if (this != &rhs)
        {
            clear();
            Node* p = rhs.head;
            while (p != nullptr)
            {
                push_back(p->data);
                p = p->next;
            }
        }
        return *this;
    }
    ~List() { clear(); }
    void clear()
    {
        while (!empty())
        {
            pop_front();
        }
    }
    bool empty() const { return size == 0; }
    int getSize() const { return size; }
    void push_back(const T& val)
    {
        if (empty())
        {
            head = tail = new Node(val);
        }
        else {
            tail->next = new Node(val, nullptr, tail);
            tail = tail->next;
        }
        ++size;
    }
    void push_front(const T& val)
    {
        if (empty()) {
            head = tail = new Node(val);
        }
        else {
            head->prev = new Node(val, head, nullptr);
            head = head->prev;
        }
        ++size;
    }
    void pop_back()
    {
        if (!empty())
        {
            Node* temp = tail;
            tail = tail->prev;
            if (tail != nullptr)
            {
                tail->next = nullptr;
            }
            else {
                head = nullptr;
            }
            delete temp;
            --size;
        }
    }
    void pop_front()
    {
        if (!empty())
        {
            Node* temp = head;
            head = head->next;
            if (head != nullptr)
            {
                head->prev = nullptr;
            }
            else {
                tail = nullptr;
            }
            delete temp;
            --size;
        }
    }
    T& front() const { return head->data; }
    T& back() const { return tail->data; }
};

int main() {
    List<int> myList;
    myList.push_back(1);
    myList.push_back(2);
    myList.push_back(3);
    myList.push_front(0);

    std::cout << "Size: " << myList.getSize() << std::endl;
    std::cout << "Front: " << myList.front() << std::endl;
    std::cout << "Back: " << myList.back() << std::endl;

    myList.pop_back();
    myList.pop_front();

    std::cout << "Size: " << myList.getSize() << std::endl;
    std::cout << "Front: " << myList.front() << std::endl;
    std::cout << "Back: " << myList.back() << std::endl;

    List<int> copyList(myList);
    std::cout << "Copy size: " << copyList.getSize() << std::endl;

    copyList.clear();
    std::cout << "Copy size after clear: " << copyList.getSize() << std::endl;
    return 0;
}