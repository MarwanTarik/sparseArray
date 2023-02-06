#ifndef SPARSE_ARRAY_ARRAYLINKEDLIST_H
#define SPARSE_ARRAY_ARRAYLINKEDLIST_H

#include <iostream>
using namespace std;

template<typename T>struct Node{
    Node *next;
    Node *previous;
    int index;
    T data;
    Node(T data,int index):data(data),index(index){}
};

template<class T>
class ArrayLinkedList{
private:
    Node<T> *head{};
    Node<T> *tail{};
    int length{};

public:
    ArrayLinkedList(int length):length(length){}

    void insert(T value,int index){
        if(index==length || index<0)
            throw out_of_range(" index out of range");

        Node<T> *node = new Node(value,index);

        if(!head) {
            head = tail = node;
            return;
        }

        bool is_back = true;
        for(Node<T> *cur = head; cur; cur = cur->next){
             if(cur->index>index){
                 if(cur==head)
                     head = node;
                link(cur->previous, node);
                link(node,cur);
                is_back = false;
                break;
            }

             else if(cur->data == index){
                cur->data = value;
                is_back = false;
                break;
            }
        }

        if(is_back) {
            link(tail,node);
            tail = node;
        }
    }

    void print_array_nonzero(){
        for(Node<T> *cur = head; cur; cur=cur->next){
            cout<<cur->data<<" ";
        }
    }

    void print_array(){
        Node<T> *cur = head;
        int idx = 0;
        while(idx<length){
            if(cur && cur->index==idx) {
                cout << cur->data << " ";
                cur = cur->next;
                idx++;
            }

            else{
                cout<<0<<" ";
                idx++;
            }
        }
    }

    void add_arrays(ArrayLinkedList& other){
        if(other.length>length)
            throw out_of_range("index out of range");

        Node<T>* second = other.head;
        Node<T>* first;

        while(second){
            first = get_node(second->index);
            if(first)
                first->data+=second->data;

            else
                insert(second->data,second->index);

            second = second->next;
        }
        
    }

    Node<T>*get_node(int index){
        if(index==length || index<0)
            throw out_of_range("index out of range");

        for(Node<T> *cur = head; cur; cur = cur->next){
            if(cur->index==index)
                return cur;
        }
        return nullptr;
    }

private:
    void link(Node<T> *first, Node<T> *second){
        if(first)
            first->next = second;

        if(second)
            second->previous = first;
    }
};
#endif //SPARSE_ARRAY_ARRAYLINKEDLIST_H
