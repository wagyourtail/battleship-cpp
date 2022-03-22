//
// Created by william on 3/9/22.
//

#include "GLBuilder.h"

bool GLBuilder::GLBuilder::state = false;

GLBuilder& GLBuilder::getImmediate() {
    return ImmediateBuilder::getInstance();
}