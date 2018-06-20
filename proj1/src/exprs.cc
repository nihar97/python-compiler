/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* exprs.cc: AST subclasses related to expressions. */

/* Authors:  YOUR NAMES HERE */

// The default AST printing method defined in ast.cc suffices for
// almost all ASTs.  There are a few exceptions, shown here.
// Strictly speaking, it is not necessary to define AST subclasses for
// the different kinds of AST, but you may want to anyway just to get
// a leg up on projects 2 and 3, where you will want to override
// methods to define node-specific behaviors.  The Println_AST class
// in stmts.cc is an example of a minimal AST subclass definition that
// simply inherits print and other methods unchnaged.


#include <iostream>
#include <iomanip>
#include "apyc.h"
#include "ast.h"

using namespace std;

                     /*** PRIMARY EXPRESSIONS ***/

/** Represents an integer literal. */
class Int_Literal_AST : public AST_Leaf {
private:

    void print (ostream& out, int indent) {
        out << "(int_literal " << location () << " " << value << ")";
    }

    /** Augment setText to initialize value from the text of the lexeme,
     *  checking that the literal is in range. */
    void setText (const string& text) {
        AST_Leaf::setText(text);
        value = stol (this->text (), NULL, 0);
        // FIXME: incomplete.
    }

    long value;

    FACTORY(Int_Literal_AST);

};

EXEMPLAR(Int_Literal_AST, INT_LITERAL_AST);

    
/** A string literal. In Python, a string may be denoted by a number of
 *  string and raw string tokens concatentated together.  For example:
 *       message = 'He said, "Don"' "'t do that!" 
 *  A String_Literal_AST contains a sequence of string tokens and,
 *  when printing an AST, concatenates them together. **/
class String_Literal_AST : public AST_Leaf {
public:
    
    string denotedText () const {
        return literalText;
    }

    void setText (const string& text) {
        literalText.clear ();
        AST_Leaf::setText ("");
        appendText(text);
    }        

    void appendText(const string& s0) {
        if (s0.empty ()) {
            return;
        }
        
        string s (s0);

        if (!text ().empty ()) {
            AST_Leaf::appendText (" ");
        }
        AST_Leaf::appendText (s);

        for (size_t p = s.find ("\r\n"); p != string::npos;
             p = s.find ("\r\n", p + 2)) {
            s.replace(p, 2, "\n");
        }
        for (size_t p = s.find ('\r'); p != string::npos;
             p = s.find ('\r', p + 1)) {
            s[p] = '\n';
        }

        if (s[0] == 'r') {
            if (s.compare (0, 4, "r'''") == 0
                || s.compare (0, 4, "r\"\"\"") == 0
                || s.compare (0, 4, "R'''") == 0
                || s.compare (0, 4, "R\"\"\"") == 0) {
                literalText += s.substr (4, s.size () - 7);
            } else {
                literalText += s.substr (2, s.size () - 3);
            }
        } else {
            int v;
            size_t i;

            if (s.compare (0, 3, "'''") == 0
                || s.compare (0, 3, "\"\"\"") == 0) {
                s = s.substr (3, s.size () - 6);
            } else {
                s = s.substr (1, s.size () - 2);
            }

            i = 0;
            while (i < s.size ()) {
                i += 1;
                if (s[i-1] == '\\') {
                    i += 1;
                    switch (s[i-1]) {
                    default: literalText += '\\'; v = s[i-1]; break;
                    case '\r':
                    {
                        if (s[i] == '\n') {
                            i += 1;
                            continue;
                        } else {
                            error (location(), "stray carriage return");
                        }
                        break;
                    }
                    case '\n': continue;
                    case 'a': v = '\007'; break;
                    case 'b': v = '\b'; break;
                    case 'f': v = '\f'; break;
                    case 'n': v = '\n'; break;
                    case 'r': v = '\r'; break;
                    case 't': v = '\t'; break;
                    case 'v': v = '\v'; break;
                    case '\'': v = '\''; break;
                    case '"': case '\\': v = s[i-1]; break;
                    case '0': case '1': case '2': case '3': case '4':
                    case '5': case '6': case '7': 
                    { 
                        v = s[i-1] - '0';
                        for (int j = 0; j < 2; j += 1) {
                            if ('0' > s[i] || s[i] > '7')
                                break;
                            v = v*8 + (s[i] - '0');
                            i += 1;
                        }
                        break;
                    }
                    case 'x': {
                        if (i+2 > s.size () || 
                            !isxdigit (s[i]) || !isxdigit (s[i+1])) {
                            error (location (),
                                   "bad hexadecimal escape sequence");
                            break;
                        }
                        sscanf (s.c_str ()+i, "%2x", &v);
                        i += 2;
                        break;
                    }
                    }
                } else
                    v = s[i-1];
                literalText += (char) v;        
            }
        }
    }

    void print (ostream& out, int indent) {
        out << "(string_literal " << location () << " \"";
        for (size_t i = 0; i < literalText.size (); i += 1) {
            char c = literalText[i];
            if (c < 32 || c == '\\' || c == '"') {
                out << "\\" << oct << setw (3) << setfill('0') << (int) c
                    << setfill (' ') << dec;
            } else
                out << c;
        }
        out << "\")";
    }

private:
    FACTORY(String_Literal_AST);

    string literalText;
};

EXEMPLAR(String_Literal_AST, STRING_LITERAL_AST);
