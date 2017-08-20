//
// Created by znt on 17-8-19.
//

#include "String.h"

String::~String() {
    alloc.deallocate(firstElement,cap-firstElement);
    firstElement = nullptr;
    cap = nullptr;
    firstFree = nullptr;
}


String::String(const char *val) : firstElement(nullptr),cap(nullptr),firstFree(nullptr) {

    reallocate();

    while( *val != '\0'){

        chk_n_alloc();

        alloc.construct(firstFree++,*val++);

    }

}

String::String(const String &str) {

    auto newData = alloc.allocate(str.capacity());

    auto dest = newData;

    for (auto item = str.begin(); item != str.end();){
        alloc.construct(dest++,*item++);
    }
    firstFree = dest;
    firstElement = newData;
    cap = firstElement + str.capacity();

    std::cout << "copy-constructor" << std::endl;

}

String& String::operator=(const String &rhs) {
    char* tFirstElement = firstElement;
    char* tCap = cap;

    auto newData = alloc.allocate(rhs.capacity());

    auto dest = newData;

    for(auto item = rhs.begin(); item != rhs.end();){
        alloc.construct(dest++,*item++);
    }

    firstElement = newData;
    firstFree  = dest;
    cap = firstElement + rhs.capacity();

    alloc.deallocate(tFirstElement,tCap - tFirstElement);

    std::cout << "copy-assignment operator" << std::endl;

    return *this;
}

const std::size_t String::capacity() const {
    return cap - firstElement;
}

const std::size_t String::size() const{
    return firstFree - firstElement;
}

char* String::begin() const{
    return firstElement;
}

char* String::end() const {
    return firstFree;
}

void String::push_back(const char* val) {
    while (*val != '\0'){
        chk_n_alloc();
        alloc.construct(firstFree++,*val++);
    }
}

std::ostream& operator<<(std::ostream& os,const String& rhs){

    for(auto item = rhs.firstElement; item != rhs.firstFree; ++item){
        os << *item;
    }
    return os;
}

void String::reallocate() {

    std::size_t newCapacity = size() ? size()*2 : 1;

    auto newData = alloc.allocate(newCapacity);

    auto dest = newData;

    auto elem = firstElement;

    for (size_t i = 0; i != size() ; ++i) {
        alloc.construct(dest++,*elem++);
    }

    free();

    firstElement = newData;
    firstFree = dest;
    cap = firstElement + newCapacity;
}

void String::chk_n_alloc() {
    if(size() == capacity()) reallocate();
}

void String::free() {
    if (firstElement)
        alloc.deallocate(firstElement,cap - firstElement);
}