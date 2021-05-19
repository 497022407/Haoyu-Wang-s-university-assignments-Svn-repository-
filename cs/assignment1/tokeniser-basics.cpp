// a skeleton implementation of a tokeniser

#include "tokeniser-extras.h"
#include <vector>
#include <queue>
// to shorten the code
using namespace std ;



/////////////////////////////////////////////////////////////////////////

namespace Assignment_Tokeniser
{

    // the current input character
    // the eof marker can be confused with a legal character but not one accepted by our tokeniser
    char ch ;

    // to create a new token we need the characters read since the last token was created
    // the tokeniser always reads one character past a token so ch is never part of a new token
    // when nextch() is called the old ch value must be part of the token currently being parsed
    // this minimal implementation just remembers the spelling of the current token
    static string spelling ;
    static char repeat = EOF;
    static int line, column;
    static int line_temp, column_temp;

    std::vector<Token> v;

    // create a new token using characters remembered since the last token was created
    // in the final submission tests new_token() will require the correct line and column numbers
    // this will require keeping an entire history of the input, not just the latest spelling
    // NOTE: the first character in the input is in column 1 of line 1
    Token new_token(TokenKind kind)
    {
        Token token;
        
        // create a new token object and reset spelling
        token = new_token(kind,spelling,line_temp,column_temp) ;
        
        // store the begining line and column numbers of token
        line_temp=line;
        column_temp=column;

        // store token to vector
        v.push_back(token);

        if (ch=='\n')
        {
            line++;
            column=0;
        }

        // reset the spelling
        spelling = "" ;

        return token ;
    }

    // generate a context string for the given token
    // all lines are shown after the preprocssing of special characters
    // it shows the line before the token, with a '$' marking the end of line,
    // the line containing the token up to the end of the token, and
    // a line of spaces ending with a ^ under the token's first character to mark its position
    // the lines are prefixed by line numbers, right justified in four spaces, followed by ": ", eg "  45: "
    // NOTE: if a token includes newline character(s), only display the token before the first newline followed by a '$'
    // NOTE: this function is not required for the milestone submission
    // NOTE: it is a good idea to build a data structure to remember where each line starts
    string token_context(Token token)
    {
        string str="";

        //print context if the token is in first line
        if (token_line(token)==1)
        {
            str += "   1: ";
            for (int i = 0; i < v.size() && token_column(v[i]) <= token_column(token) ; ++i)
            {
                if (token_kind(v[i])==tk_newline)
                {
                    str+="$";
                }
                else
                {
                    str+=token_spelling(v[i]);
                }
            }
        }
        //print context if the token is not in first line
        else
        {
            int p=0;

            // set "\n" to "$"
            for (int i = 0; i < v.size(); ++i)
            {
                if (token_kind(v[i])==tk_newline)
                {
                    set_token_spelling(v[i],"$");
                }
            }

            // set p
            for (; p < v.size() && token_line(v[p]) < token_line(token)-1; ++p){}
            
            // 1st line
            str += "   " + std::to_string(token_line(token)-1) + ": ";
            for (; token_line(v[p]) < token_line(token) ; ++p)
            {
                str+=token_spelling(v[p]);
            }

            //2nd line
            str+='\n';
            str += "   " + std::to_string(token_line(token)) + ": ";

            for (; p < v.size() && token_column(v[p]) <= token_column(token); ++p)
            {
                    str+=token_spelling(v[p]);
                    if (token_spelling(v[p])=="$")
                    {
                        break;
                    }
            }

            // reset "$" to "\n"
            for (int i = 0; i < v.size(); ++i)
            {
                if (token_spelling(v[i])=="$")
                {
                    set_token_spelling(v[i],"\n");
                }
            }

        }
        
        // use '^' to locate the position
        str+="\n      ";
        for (int i = 1; i < token_column(token); ++i)
        {
            str+=" ";
        }
        str+="^\n";

        return str ;
        
    }

    // read next character if not at the end of input and update the line and column numbers
    // additional code will be required here to handle preprocessing of '\t' and '\r'
    // in some cases you may wish to remember a character to use next time instead of calling read_char()
    void nextch()
    {
        if ( ch == EOF ) return ;           // stop reading once we have read EOF

        spelling += ch ;                    // remember the old ch, it is part of the current token being parsed

        if ( repeat != EOF ) 
        { 
            ch = repeat ;
            repeat = EOF ; 
        } 
        else ch = read_char() ;                  // read the next character

        //evety read next char, column ++
        column++;

        //handle '\t'
        if ( ch == '\t' ) 
        { 
            if ( column % 4 != 0 ) repeat = '\t' ; 
            ch = ' ' ; 
        } 
        else if ( ch == '\r' ) 
        { 
            ch = read_char() ; 
            if ( ch != '\n' ) repeat = ch ; 
            ch = '\n' ; 
        }


    }

    // initialise the tokeniser
    void initialise_tokeniser()
    {
                                            // add any other initialisation code you need here
                                            // ...
        ch = '\n' ;                         // initialise ch to avoid accidents
        nextch() ;                          // make first call to nextch to initialise ch using the input
        spelling = "" ;                     // discard the initial '\n', it is not part of the input
        line=1;
        column=1;/* code */
        line_temp=1;
        column_temp=1;

    }

    int get_line()
    {
        return line;
    }

    int get_column()
    {
        return column;
    }

    string get_spelling()
    {
        return spelling;
    }

    void set_spelling(string str)
    {
        spelling=str;
    }
}
