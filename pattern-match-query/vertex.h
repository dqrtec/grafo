#ifndef VERTEX_H
#define VERTEX_H

#include <string>
#include "common.h"

using namespace std;

class Vertex {
private:
    int id;
    string label;
public:
    int getId();
    void setId(int id);
    string getLabel();
    void setLabel(string label);
};

#endif