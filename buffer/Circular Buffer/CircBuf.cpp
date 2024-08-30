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
        if (buffer_size == buffer_capacity - 1) {
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
        if (head == buffer_capacity - 1) {
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
        if (head == buffer_capacity - 1) {
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
        if (tail == buffer_capacity - 1) {
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

string CircBuf::get(size_t j){
    string s = "";
    for (size_t i = 0; i < j; i++) {
        if (buffer_size == 0) {
            return s;
        }
        else {
            s.push_back(buffer[tail]);
            if (tail == buffer_capacity - 1) {
                tail = 0;
                buffer_size--;
            }
            else {
                tail++;
                buffer_size--;
            }
        }
    }
    return s;
}

string CircBuf::flush(){
    string s = get(buffer_size);
    return s;
}

string CircBuf::examine(){
    string s;
    s.push_back('[');
    size_t end_digits = buffer_capacity - tail;
    size_t start_digits;
    size_t mid_digits;
    if (end_digits > buffer_size) {
        if (tail > 0) {
            start_digits = buffer_capacity - end_digits;
            mid_digits = buffer_size;
            end_digits = end_digits - mid_digits;
            size_t i;
            for (i = 0; i < start_digits; i++) {
                s.push_back('-');
            }
            for (size_t j = 0; j < mid_digits; j++) {
                s.push_back(buffer[i]);
                i++;
            }
            for (size_t j = 0; j < end_digits; j++) {
                s.push_back('-');
                i++;
            }
        }
        else {
            start_digits = buffer_size;
            end_digits = buffer_capacity - buffer_size;
            size_t i;
            for (i = 0; i < start_digits; i++) {
                s.push_back(buffer[i]);
            }
            for (size_t j = 0; j < end_digits; j++) {
                s.push_back('-');
                i++;
            }
        }
    }
    else {
        start_digits = buffer_size - end_digits;
        mid_digits = buffer_capacity - buffer_size;
        size_t i;
        for (i = 0; i < start_digits; i++) {
            s.push_back(buffer[i]);
        }
        for (size_t j = 0; j < mid_digits; j++) {
            s.push_back('-');
            i++;
        }
        for (size_t j = 0; j < end_digits; j++) {
            s.push_back(buffer[i]);
            i++;
        }
    }
    s.push_back(']');
    return s;
}
void CircBuf::shrink() {
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
    buffer_capacity = 0;
    while (buffer_capacity < buffer_size) {
        buffer_capacity += CHUNK;
    }
}   // Reduces the unused space in the buffer.

void CircBuf::expand() {
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
    buffer_capacity += CHUNK;
}
