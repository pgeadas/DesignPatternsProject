/* 
 * File:   Vector.cpp
 * Author: geadas
 * 
 * Created on October 10, 2011, 11:41 PM
 */
#pragma once 
#include<string.h> 
#include<cassert> 
#include<iostream> 

template<class T>
class Vector {
    template<class U>
    friend ostream& operator<<(ostream&, const Vector<U>&);
private:
    T* data;
    unsigned len;
public:
    Vector(unsigned x=20);
    Vector(const Vector<T>&);
    virtual ~Vector(void);
    Vector<T>& operator =(const Vector<T>&);
    bool operator==(const Vector<T>&);
    T& operator[](unsigned);
    unsigned length();
};


template <class T>
Vector<T>::~Vector(void) {
    delete [] data;
    len = 0;
}

template <class T>
Vector<T>::Vector(unsigned x) {
    data = new T[x];
    len = x;
}

template <class T>
Vector<T>::Vector(const Vector<T>& v) {
    len = v.len;
    data = new T[v.len];
    for (int i = 0; i < v.len; i++) {
        data[i] = v.data[i];
    }
}

template <class T>
unsigned Vector<T>::length(){
    return len;
}

template <class T>
T& Vector<T>::operator[] (unsigned i) {
    assert(i >= 0 && i < len);
    return data[i];
}

template <class T> bool Vector<T>::operator==(const Vector<T> &v) {
    for (int i = 0; i < v.len; i++) {
        if (data[i] != v.data[i]) {
            return false;
        }
    }
    return true;
}

template <class T>
Vector<T>& Vector<T>::operator =(const Vector<T>& v) {
    if (len != v.len) {
        delete [] data;
        data = new T[v.len];
        len = v.len;
    }

    for (int i = 0; i < v.len; i++) {
        data[i] = v.data[i];
    }

    return *this;
}

template <class U> ostream& operator<<(ostream& os, const Vector<U>& v) {
    cout << "[";
    for (int i = 0; i < v.len - 1; i++) {
        os << v.data[i] << ",";
    }
    os << v.data[v.len - 1] << "]";

    return os;
}
