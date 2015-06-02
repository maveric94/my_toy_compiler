%{
#include <string>
#include <iostream>
#include "node.h"
#include "parser.hpp"


#define SAVE_TOKEN  yylval.string = new std::string(yytext, yyleng)
#define TOKEN(t)    (yylval.token = t)

int line = 1;
int current_indent = 0;

%}

%option noyywrap

%%
					       
"return"    			        return TOKEN(TRETURN);
"while"							return TOKEN(TWHILE);
"endwhile"						return TOKEN(TENDWHILE);
"for"							return TOKEN(TFOR);
"endfor"						return TOKEN(TENDFOR);

"if"							return TOKEN(TIF);
"else"							return TOKEN(TELSE);
"endif"							return TOKEN(TENDIF);
"blank"							return TOKEN(TBLANK);
"extern"						return TOKEN(TEXTERN);

"int"							SAVE_TOKEN; return TINT;
"double"						SAVE_TOKEN; return TDBL;
"char"							SAVE_TOKEN; return TCHAR;
"void"							SAVE_TOKEN; return TVOID;

["].*["]						{
									SAVE_TOKEN; 
									yylval.string->erase(yylval.string->begin());
									yylval.string->erase(yylval.string->end() - 1);		 
									return TSTR;
								}
								
[a-zA-Z_][a-zA-Z0-9_]*  		SAVE_TOKEN; return TIDENTIFIER;
[0-9]+					        SAVE_TOKEN; return TINTEGER;
[0-9]+\.[0-9]* 			    	SAVE_TOKEN; return TDOUBLE;
['].[']							{
									SAVE_TOKEN; 
									yylval.string->erase(yylval.string->begin());
									yylval.string->erase(yylval.string->end() - 1);		 
									return TCHARACTER;
								}

"="						        return TOKEN(TEQUAL);
"=="				          	return TOKEN(TCEQ);
"!="			          		return TOKEN(TCNE);
"<"				          		return TOKEN(TCLT);
"<="	          				return TOKEN(TCLE);
">"				          		return TOKEN(TCGT);
">="					        return TOKEN(TCGE);

"("	          					return TOKEN(TLPAREN);
")"					          	return TOKEN(TRPAREN);
"["								return TOKEN(TLBRACKET);
"]"								return TOKEN(TRBRACKET);
"{"								return TOKEN(TLBRACE);
"}"								return TOKEN(TRBRACE);
"#"								return TOKEN(TSHARP);
"~"								return TOKEN(TTILDE);

"."         					return TOKEN(TDOT);
","				          		return TOKEN(TCOMMA);

"+"				          		return TOKEN(TPLUS);
"-"		          				return TOKEN(TMINUS);
"*"		          				return TOKEN(TMUL);
"/"				          		return TOKEN(TDIV);
":"								return TOKEN(TCOLON);
";"								return TOKEN(TSEMICOLON);

[ ]*							;

[\n\t]*							{
									int i, found = 0;

									//std::cout << "yyleng " << yyleng << std::endl;

									for(i = 0; i < yyleng; i++)
									{
										if(yytext[i] == '\t')
											found++;
									}
									for(int j = 0; j < yyleng - found; j++, line++)
										;//std::cout << "LINE: " << line << std::endl;

									if(!found)
									{
										if(current_indent == 1)
										{
											current_indent--;

											//std::cout << "dec\n";
											return TOKEN(TDEC_INDENT);
										}
										else 
											;//return TOKEN(TLINE);

									} 
									else
									{
										if(current_indent == found + 1)
										{
											//std::cout << "dec\n";
											current_indent--;
											return TOKEN(TDEC_INDENT);
										}
										if(current_indent == found - 1)
										{
											current_indent++;

											//std::cout << "inc\n";
											return TOKEN(TINC_INDENT);
										}

										if(current_indent == found)
											;//return TOKEN(TLINE);
										else 
											return TOKEN(TINDENT_ERR); 
									}

								}

.                       		std::cout << "Unknown token! " << yytext << std::endl; yyterminate();

%%
