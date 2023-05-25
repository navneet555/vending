#include "Node.h"

Node::Node(){
    this->data = nullptr;
    this->next = nullptr;
};
Node::~Node(){
      delete this->data;  
};