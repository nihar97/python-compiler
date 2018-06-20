/* -*- mode: fundamental; c-file-style: "stroustrup"; indent-tabs-mode: nil -*- */

/* apyc-lexer.l: Flex Lexer */

/* Authors: YOUR NAMES HERE */

  #define YY_DECL int yylex_raw() 

%option yylineno noyywrap

%%

  /* The following are incomplete.  Complete them appropriately.  */

  /* Normally, throw away whitespace other than newline. */
[ \t\r]+          {     }
"#".*             {     }
"\n"              { return NEWLINE; }

[1-9][0-9]*       {  /* FIXME */
          yylval.str = new string (yytext);
          return INT;
    }

  /* Keywords */

print             { return PRINT; }
and               {return AND;}
break             {return BREAK;}
class             {return CLASS;}
continue          {return CONTINUE;}
def               {return DEF;}
elif              {return ELIF;}
else              {return ELSE;}
for               {return FOR;}
if                {return IF;}
in                {return IN;}
is                {return IS;}
not               {return NOT;}
or                {return OR;}
pass              {return PASS;}
return            {return RETURN;}
while             {return WHILE;}
  /* Punctuation */
  /* By convention, for one-character tokens written in the grammar as
   * character constants (such as ','), Bison uses the character value itself
   * (as an integer). */
\*\*                   { return EXP;}
[\+\-\*/,;:()\[\]{}]           { return yytext[0]; }


  /* Strings */
\"\"              { return STRING; /* FIXME */ }

r\"\"             { return STRING; /* FIXME */ }

%%

static vector<string> sourceFileNames;
static vector<int> firstLines;

bool
initLexer (const string& fileName)
{
    FILE* input = fopen (fileName.c_str (), "r");
    if (input == NULL) {
        return false;
    }

    firstLines.push_back (yylineno);
    sourceFileNames.push_back (fileName);
    yyin = input;
    // FIXME: Other stuff here?
    return true;
}

int
yylex ()
{
    int result = yylex_raw();
    yylloc = yylineno;
    return result;
}

string
currentFileName ()
{
    return sourceFileNames.back ();
}

Location
currentLocation ()
{
    return yylineno;
}

string
locationFileName (Location loc)
{
    if (loc == 0) {
        return "?";
    } else {
        for (size_t i = 1; i < sourceFileNames.size(); i += 1) {
             if (firstLines[i] > loc) {
                 return sourceFileNames[i - 1];
             }
         }
         return sourceFileNames.back ();
    }
}

Location
locationLine (Location loc)
{
    if (loc == 0) {
        return 0;
    } else {
        for (size_t i = 1; i < sourceFileNames.size(); i += 1) {
             if (firstLines[i] > loc) {
                 return loc - firstLines[i - 1] + 1;
             }
         }
         return loc - firstLines.back () + 1;
    }
}
