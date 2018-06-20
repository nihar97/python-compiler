/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* stmts.cc: AST subclasses related to statements and modules. */

/* Authors:  YOUR NAMES HERE */

#include <iostream>
#include "apyc.h"
#include "ast.h"

using namespace std;

/*****   MODULE    *****/

/** A module, representing a complete source file. */
class Module_AST : public AST_Tree {
public:

    Location location () const {
        return 0;
    }

    FACTORY (Module_AST);

};

EXEMPLAR (Module_AST, MODULE_AST);


/*****   PRINTLN   *****/

/** A print statement without trailing comma. */
class Println_AST : public AST_Tree {
public:

    FACTORY (Println_AST);

};

EXEMPLAR (Println_AST, PRINTLN_AST);
