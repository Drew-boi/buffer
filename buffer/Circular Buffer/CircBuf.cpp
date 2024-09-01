#include "CircBuf.h"
///This program was an absolute nightmare for me.  I first had to figure out how to use a pointer and
/// a dynamically allocated array to create different sized array. I then spent quite a lot of time thinking
/// through my insert functions, which I was eventually able to figure out. The main issues here were
/// out  the proper indexing of the array. I also had to figure out when I would need to expand the array.
/// I then spent awhile on my examine function, as it was hard to figure out all of the cases I would need
/// in order to get it to properly insert the dashes. My final problem was that I forgot to expand the size
/// of my temporary array while expanding the array, so I was writing out of bounds.

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
    if (head == buffer_capacity) { // Check if head is at the end of the array
        if (buffer_size == buffer_capacity - 1) { // Check if  you need to expand the array or loop around the back
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
        if (buffer_size == buffer_capacity) { // Check if the array is full, expand if so.
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
        if (head == buffer_capacity - 1) { // Check if head is at the end of the buffer
            if (buffer_size == buffer_capacity) {  // Check if  you need to expand the buffer or loop around the back
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
            if (buffer_size == buffer_capacity) { // Check if the buffer is full, expand if so.
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
        if (head == buffer_capacity - 1) { // Check if head is at the end of the buffer
            if (buffer_size == buffer_capacity) { // Check if  you need to expand the buffer or loop around the back
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
            if (buffer_size == buffer_capacity) { // Check if the buffer is full, expand if so.
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
    if (buffer_size == 0) { // Return empty char if buffer is empty
        return c;
    }
    else {
        c = buffer[tail];
        if (tail == buffer_capacity - 1) { // Loop around the back if the tail is at the end of buffer
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
    for (size_t i = 0; i < j; i++) { // Return empty string if buffer is empty
        if (buffer_size == 0) {
            return s;
        }
        else {
            s.push_back(buffer[tail]);
            if (tail == buffer_capacity - 1) { // Loop around the back if the tail is at the end of buffer
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
    string s = get(buffer_size); // Clear the entire buffer and return it
    return s;
}

string CircBuf::examine(){
    string s;
    s.push_back('[');
    size_t end_digits = buffer_capacity - tail; // Check how many digits are after the tail
    size_t start_digits;
    size_t mid_digits;
    if (end_digits > buffer_size) { // Check if the amount of characters after the tail is more than the size of the buffer
        if (tail > 0) {
            start_digits = buffer_capacity - end_digits;
            mid_digits = buffer_size;
            end_digits = end_digits - mid_digits;
            size_t i;
            for (i = 0; i < start_digits; i++) {
                s.push_back('-');
            }
            for (size_t j = 0; j < mid_digits; j++) { // We know there are only characters in the middle of the buffer
                s.push_back(buffer[i]);
                i++;
            }
            for (size_t j = 0; j < end_digits; j++) {
                s.push_back('-');
                i++;
            }
        }
        else { // There are only characters at the start of the buffer
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
    else { // We know there are more characters at the end than there are spots in the buffer
        start_digits = buffer_size - end_digits;
        mid_digits = buffer_capacity - buffer_size;
        size_t i;
        for (i = 0; i < start_digits; i++) {
            s.push_back(buffer[i]);
        }
        for (size_t j = 0; j < mid_digits; j++) { // The characters are at the start and end of the buffer, not the middle.
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
    buffer_capacity = 0;
    while (buffer_capacity < buffer_size) { // Shrink the buffer size
        buffer_capacity += CHUNK;
    }
    char* temp = new char[buffer_capacity];
    size_t temp_counter = tail; // This counter tells you where to start in the current buffer
    size_t i;
    for (i = 0; i < buffer_size; i++) { // Copy over only elements in the buffer
        temp[i] = buffer[temp_counter];
        if (temp_counter < buffer_capacity - 1){
            temp_counter++;
        }
        else { // Rotate counter to the back once you hit the end of the buffer
            temp_counter = 0;
        }
    }
    head = i;
    tail = 0;
    delete[] buffer;
    buffer = temp;
}   // Reduces the unused space in the buffer.

void CircBuf::expand() {
    size_t temp_cap = buffer_capacity + CHUNK; // Expand the buffer size
    char* temp = new char[temp_cap];
    size_t temp_counter = tail; // This counter tells you where to start in the current buffer
    size_t i;
    for (i = 0; i < buffer_size; i++) { // Copy over only elements in the buffer
        temp[i] = buffer[temp_counter];
        if (temp_counter < buffer_capacity - 1){
            temp_counter++;
        }
        else { // Rotate counter to the back once you hit the end of the buffer
            temp_counter = 0;
        }
    }
    head = i;
    tail = 0;
    delete[] buffer;
    buffer = temp;
    buffer_capacity += CHUNK;
}
