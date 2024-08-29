#include "CircBuf.h"

CircBuf::CircBuf(size_t reserve) { // Number of elements you want it to be able to hold to start with.
    buffer_capacity = 0;
    while (buffer_capacity < reserve) {
        buffer_capacity += CHUNK;
    }
    buffer = new char[buffer_capacity];
    buffer_size = 0;
    head = 0;
    tail = 0;
}
CircBuf::~CircBuf() {
    delete[] buffer;
}
size_t CircBuf::size(){
    return buffer_size;
}
size_t CircBuf::capacity(){
    return buffer_capacity;
}

void CircBuf::insert(char c){
    if (head == buffer_capacity) {
        if (buffer_size == buffer_capacity) {
            expand();
            buffer[head] = c;
            head++;
            buffer_size++;
        }
        else {
            buffer[head] = c;
            head = 0;
            buffer_size++;
        }
    }
    else {
        if (buffer_size == buffer_capacity and head == tail) {
            expand();
        }
        buffer[head] = c;
        head++;
        buffer_size++;
    }
}

void CircBuf::insert(const char* c, size_t sz) {
    size_t temp_counter = 0;
    while (temp_counter < sz) {
        if (head == buffer_capacity) {
            if (buffer_size == buffer_capacity) {
                expand();
                buffer[head] = c[temp_counter];
                head++;
                buffer_size++;
            }
            else {
                buffer[head] = c[temp_counter];
                head = 0;
                buffer_size++;
            }
        }
        else {
            if (buffer_size == buffer_capacity and head == tail) {
                expand();
            }
            buffer[head] = c[temp_counter];
            head++;
            buffer_size++;
        }
        temp_counter += 1;
    }
}
void CircBuf::insert(const string& str){
    for(const char c : str) {
        if (head == buffer_capacity) {
            if (buffer_size == buffer_capacity) {
                expand();
                buffer[head] = c;
                head++;
                buffer_size++;
            }
            else {
                buffer[head] = c;
                head = 0;
                buffer_size++;
            }
        }
        else {
            if (buffer_size == buffer_capacity and head == tail) {
                expand();
            }
            buffer[head] = c;
            head++;
            buffer_size++;
        }
    }
}

char CircBuf::get(){
    char c = '\0';
    if (buffer_size == 0) {
        return c;
    }
    else {
        c = buffer[tail];
        if (tail == buffer_capacity) {
            tail = 0;
            buffer_size--;
        }
        else {
            tail++;
            buffer_size--;
        }
    }
    return c;
}

string CircBuf::get(size_t i){
    return "";
}

string CircBuf::flush(){
    buffer_size = 0;
    return "";
}

string CircBuf::examine(){
    return "";
}
void CircBuf::shrink() {
    
}   // Reduces the unused space in the buffer.

void CircBuf::expand() {
    buffer_capacity += CHUNK;
    char* temp = new char[buffer_capacity];
    size_t temp_counter = tail;
    size_t i;
    for (i = 0; i < buffer_size; i++) {
        temp[i] = buffer[temp_counter];
        if (temp_counter < buffer_capacity - 1){
            temp_counter++;
        }
        else {
            temp_counter = 0;
        }
    }
    head = i;
    tail = 0;
    delete[] buffer;
    buffer = temp;
}
