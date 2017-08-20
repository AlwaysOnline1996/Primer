//
// Created by znt on 17-8-19.
//

#ifndef C_PRIMER_STRING_H
#define C_PRIMER_STRING_H

#include <iterator>
#include <utility>
#include <iostream>


class String {


public:
    explicit String(const char* val = "");
    String(const String&);
    String& operator=(const String&);
    ~String();
    const std::size_t capacity() const;
    const std::size_t size() const;
    char* begin() const;
    char* end() const;
    void push_back(const char*);

    friend std::ostream&operator<<(std::ostream& os,const String&) ;


private:
    std::allocator<char> alloc;
    char* firstElement;
    char* cap;
    char* firstFree;
    void reallocate();
    void chk_n_alloc();
    void free();
};

std::ostream&operator<<(std::ostream& os,const String&) ;

#endif //C_PRIMER_STRING_H
