/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* code.h: Definitions related to code generation. */

/* Authors: */

#ifndef _CODE_H
#define _CODE_H_

#include "apyc.h"

/** A repository for information needed to generate from an AST
 *  node, and other code utilities.  */
class Code_Context {
public:
     Code_Context ();

     /* Support for emitting code.  Behaves essentially as does an
      * an ostream, but with additions. */

     /** Output CODE to code output file. */
     Code_Context& operator<< (const std::string& code);


     /* Support for manipulators. */
     Code_Context& operator<< (std::ostream& (*manip) (std::ostream&));
     Code_Context& operator<< (std::ios& (*pf)(std::ios&));
     Code_Context& operator<< (std::ios_base& (*pf)(std::ios_base&));

     /** Indent subsequent code by INDENTING levels.  
      *  Indents next line after an endl manipulator. */
     void indent (int indent = 1);

     Decl* getContext() const { return _context; }

     void setContext(Decl* c) { _context = c; }

     void setTupleAssignScratchPos(unsigned long l) { _tupleAssignScratchPos = l; }
     unsigned long advanceTupleAssignScratchPos() { return _tupleAssignScratchPos++; }
     unsigned long getTupleAssignScratchPos() const { return _tupleAssignScratchPos; }

     void setLeftCompareScratchPos(unsigned long l) { _leftCompareScratchPos = l; }
     unsigned long advanceLeftCompareScratchPos() { return _leftCompareScratchPos++; }
     unsigned long getLeftCompareScratchPos() const { return _leftCompareScratchPos; }

     void setAndOrScratchPos(unsigned long l) { _andOrScratchPos = l; }
     unsigned long advanceAndOrScratchPos() { return _andOrScratchPos++; }
     unsigned long getAndOrScratchPos() const { return _andOrScratchPos; }

private:

     /** Current output indentation level. */
     int _indentation;
     /** True at beginnings of emitted lines. */
     bool _bol;

     Decl* _context = nullptr;

     unsigned long _tupleAssignScratchPos = 0;
     unsigned long _leftCompareScratchPos = 0;
     unsigned long _andOrScratchPos = 0;
};

#endif
