//
// Created by bhuwan sapkota on 4/2/16.
//


#include "Exceptions.h"
using namespace Gaming;

void GamingException::setName(std::string name) {
    __name = name;          //setting the name up.
}

// polymorphic operator overloading
// print__arg decide what to do based on what kind of GaminExceptions is passed.
std::ostream &Gaming::operator<<(std::ostream &os, const GamingException &ex){
    ex.__print_args(os);
    return os;
}

// constructor

DimensionEx::DimensionEx(unsigned expWidth, unsigned expHeight, unsigned width, unsigned height) {
    __exp_width = expWidth;
    __exp_height = expHeight;
    __width = width;
    __height = height;
}

// getters.
unsigned DimensionEx::getExpWidth() const {
    return __exp_width;
}

unsigned DimensionEx::getExpHeight() const {
    return __exp_height;
}

unsigned DimensionEx::getWidth() const {
    return __width;
}

unsigned DimensionEx::getHeight() const {
    return __height;
}

// passing this to extraction operator.
void InsufficientDimensionsEx::__print_args(std::ostream &os) const {
    os << __name << std::endl;
}

// constructor
InsufficientDimensionsEx::InsufficientDimensionsEx(unsigned minWidth, unsigned minHeight, unsigned width,
                                                   unsigned height):DimensionEx(minWidth,minHeight,width,height) {
    setName("InsufficientDimensionsEx");

}

// passing this to extraction operator.
void OutOfBoundsEx::__print_args(std::ostream &os) const {
    os << "Name: "<< __name << std::endl;
    os << "Game grid "<<__exp_width <<'x' << __exp_height << std::endl;
    os << "co-ordinate (" << __width <<","<< __height << ")" << std::endl;

}

// constructor
OutOfBoundsEx::OutOfBoundsEx(unsigned maxWidth, unsigned maxHeight, unsigned width, unsigned height):
        DimensionEx(maxWidth,maxHeight,width,height) {
    setName("OutOfBoundsEx");
}

// passing this to extraction operator.
void PositionEx::__print_args(std::ostream &os) const {
    os << "Name: "<< __name << std::endl;
    os << "co_ordinate "<< '(' <<__x <<","<<__y << ')' << std::endl;
}
//constructor
PositionEx::PositionEx(unsigned x, unsigned y) {
    __x = x;
    __y = y;
}

//constructor
PositionNonemptyEx::PositionNonemptyEx(unsigned x, unsigned y):PositionEx(x,y) {
    setName("PositionNonemptyEx");
}

//constructor
PositionEmptyEx::PositionEmptyEx(unsigned x, unsigned y):PositionEx(x,y) {
    setName("PositionEmptyEx");
}

// passing this to extraction operator.
void PosVectorEmptyEx::__print_args(std::ostream &os) const {
    os << "Name: "<< __name << std::endl;
}
//constructor
PosVectorEmptyEx::PosVectorEmptyEx() {
    setName("PosVectorEmptyEx");
}



