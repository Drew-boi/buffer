#include "CircBuf.h"

CircBuf::CircBuf(size_t reserve) { // Number of elements you want it to be able to hold to start with.
    while (buffer_capacity < reserve) {
        buffer_capacity += CHUNK;
    }
    buffer = new char[buffer_capacity];
    buffer_size = 0;
    front_index = 0;
    back_index = 0;
    behind = false;
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
    if (front_index == buffer_capacity - 1) {
        if (buffer_size == buffer_capacity) {
            expand();
            buffer[front_index] = c;
        }
        else {
            buffer[front_index] = c;
            front_index = 0;
        }
    }
    else {
        if (buffer_size == buffer_capacity and front_index == back_index) {
            expand();
        }
        buffer[front_index] = c;
        front_index++;
        buffer_size++;
    }
}

void CircBuf::insert(const char* c, size_t sz) {
    size_t temp_counter = 0;
    while (temp_counter < sz) {
        if (front_index == buffer_capacity - 1) {
            if (buffer_size == buffer_capacity) {
                expand();
                buffer[front_index] = c[temp_counter];
            }
            else {
                buffer[front_index] = c[temp_counter];
                front_index = 0;
            }
        }
        else {
            if (buffer_size == buffer_capacity and front_index == back_index) {
                expand();
            }
            buffer[front_index] = c[temp_counter];
            front_index++;
            buffer_size++;
        }
        temp_counter += 1;
    }
}
void CircBuf::insert(const string& str){
    for(const char& c : str) {
        if (front_index == buffer_capacity - 1) {
            if (buffer_size == buffer_capacity) {
                expand();
                buffer[front_index] = c;
            }
            else {
                buffer[front_index] = c;
                front_index = 0;
            }
        }
        else {
            if (buffer_size == buffer_capacity and front_index == back_index) {
                expand();
            }
            buffer[front_index] = c;
            front_index++;
            buffer_size++;
        }
    }
}
char CircBuf::get(){
    return ' ';
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
    size_t temp_counter = back_index;
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
    front_index = i;
    back_index = 0;
    delete[] buffer;
    buffer = temp;
}
