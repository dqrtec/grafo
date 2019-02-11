#include "vertex.h"

int Vertex::getId() {
    return this->id;
}

void Vertex::setId(int id) {
    this->id = id;
}

string Vertex::getLabel() {
    return label;
}

void Vertex::setLabel(string label) {
    this->label = label;
}