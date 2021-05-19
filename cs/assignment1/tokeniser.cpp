// a skeleton implementation of a tokeniser

#include "tokeniser-extras.h"
#include <string>
#include <cstring>

// to shorten the code
using namespace std ;

/////////////////////////////////////////////////////////////////////////

namespace Assignment_Tokeniser
{

    static void parse_identifier();
    static TokenKind new_token_kind ;
    static string spelling="";

    int get_line();
    int get_column();
    string get_spelling();
    void set_spelling(string str);


    //parse other kind
    static void parse_extra(TokenKind kind)
    {
        new_token_kind = kind ;
        nextch() ;
    }

    //parse wspace
    static void parse_wspace(TokenKind kind)
    {
        parse_extra(kind) ;
    }

    //parse double
    static void parse_double(TokenKind kind)
    {
        new_token_kind = kind ;
        do 
        {
            nextch() ; 
        }while ( c_have(cg_digit) ) ;
    }

    //parse integer
    static void parse_integer(TokenKind kind)
    {

        new_token_kind = kind ;

        do 
        {
            nextch() ; 
            if (ch=='.')
            {
                do
                {
                	nextch() ; 
                }while ( c_have(cg_digit));
                c_did_not_find(cg_start_of_exponent);
            }
            
        }while ( c_have(cg_digit19)) ;
    }

    //parse symbol
    static void parse_symbol(TokenKind kind)
    {
        new_token_kind = kind ;
        nextch();
    }

    //parse eol_comment
    static void parse_eol_comment(TokenKind kind)
    {
        new_token_kind = kind ;
        nextch();
        while(c_have(cg_eol_comment_char))
        {
            nextch();
        }    
        
        nextch();
        spelling=get_spelling();
        set_spelling(spelling.substr(2,spelling.size() - 3));
        
        
    }

    //parse tadhoc_comment
    static void parse_tadhoc_comment(TokenKind kind)
    {
        new_token_kind = kind ;
        nextch();
        
        bool star=false;
        while(c_have(cg_adhoc_comment_char) && !(ch=='/' && star==true))
        {
            if (ch=='*')
            {
                star=true;
            }
            else
            {
                star=false;
            }
            nextch();
        }

        nextch();
        spelling=get_spelling();
        set_spelling(spelling.substr(2,spelling.size() - 4));

    }

    //parse oprators
    static void parse_op(TokenKind kind)
    {
        new_token_kind = kind ;
        switch(ch)
        {
            case '+':
                nextch();
                if(ch=='=')
                {
                    parse_symbol(tk_add_assign);
                }
                else
                {
                    c_did_not_find('=') ;
                }
                break;
            case '-':
                nextch();
                if(ch=='=')
                {
                    parse_symbol(tk_sub_assign);
                }
                else
                {
                    c_did_not_find('=') ;
                }
                break;
            case '*':
                nextch();
                if(ch=='=')
                {
                    parse_symbol(tk_mult_assign);
                }
                else
                {
                    c_did_not_find('=') ;
                }
                break;
            case '/':
                nextch();
                // /=
                if(ch=='=')
                {
                    parse_symbol(tk_div_assign);
                }
                else if(ch=='/')
                {
                    parse_eol_comment(tk_eol_comment);
                }
                else if (ch=='*')
                {
                    parse_tadhoc_comment(tk_adhoc_comment);
                }
                else
                {
                    c_did_not_find('=') ;
                }
                
                break;
            case '!':
                nextch();
                if(ch=='=')
                {
                    parse_symbol(tk_not_eq);
                }
                else
                {
                    c_did_not_find('=') ;
                }
                break;
            case '=':
                nextch();
                if(ch=='=')
                {
                    parse_symbol(tk_not_eq);
                }
                else
                {
                    c_did_not_find('=') ;
                }
                break;
        }
    }

    //parse 
    static void parse_symbol_lshift(TokenKind kind)
    {
        new_token_kind = kind ;
        nextch();
        nextch();
        if (ch=='<')
        {
            new_token_kind = tk_lshift_l;
            nextch();
        }
    }

    //parse rshift
    static void parse_symbol_rshift(TokenKind kind)
    {
        new_token_kind = kind ;
        nextch();
        nextch();
        if (ch=='>')
        {
            new_token_kind = tk_rshift_l;
            nextch();
        }
    }


    // return the next Token object by reading more of the input
    // you must read input using the nextch() function
    // the last character read is in the static variable ch
    // always read one character past the end of the token being returned
    Token next_token()
    {
        switch(ch)      // ch is always the next char to read
        {
        case 'a'...'z':         // identifier tokens
        case 'A'...'Z':
        case '$':
            spelling="";
            parse_identifier();
            break;
        case ' ':               // white space tokens
            parse_wspace(tk_space) ;
            break ;
        case '\n':
            parse_wspace(tk_newline) ;
            break ;
        case '0'...'9':
            parse_integer(tk_integer);
            break;
        case '@':
            parse_symbol(tk_at);
            break;
        case '.':
            parse_symbol(tk_stop);
            break;
        case '{':
            parse_symbol(tk_lcb);
            break;
        case '}':
            parse_symbol(tk_rcb);
            break;
        case '(':
            parse_symbol(tk_lrb);
            break;
        case ')':
            parse_symbol(tk_rrb);
            break;
        case '[':
            parse_symbol(tk_lsb);
            break;
        case ']':
            parse_symbol(tk_rsb);
            break;
        case '+':               // op tokens
            parse_op(tg_symbol) ;
            break ;
        case '-':               // op tokens
            parse_op(tg_symbol) ;
            break ;
        case '*':               // op tokens
            parse_op(tg_symbol) ;
            break ;
        case '/':               // op tokens
            parse_op(tg_symbol) ;
            break ;
        case '!':               // op tokens
            parse_op(tg_symbol) ;
            break ;
        case '=':               // op tokens
            parse_op(tg_symbol) ;
            break ;
        case '<':               // op tokens
            parse_symbol_lshift(tk_lshift) ;
            break ;
        case '>':               // op tokens
            parse_symbol_rshift(tk_rshift) ;
            break ;
        

        


                       // this should follow the style used in the workshops ...
                        // but remember that the token grammar is different in this assignment
                        //
                        // add additional case labels here for characters that can start tokens
                        // call a parse_*() function to parse the token
                        //

                        // End of Inptut
        case EOF:
            new_token_kind = tk_eoi ;
            break ;
        default:
            c_did_not_find(cg_start_of_token) ;
        }
        Token token = new_token(new_token_kind) ;


                        // before returning a token check if the kind or spelling needs updating
                        // ...

        return token ;
    }

    void parse_identifier()
    {
        new_token_kind = tk_identifier;
        spelling+=ch;
        nextch();
        switch(ch)
        {
        	//these cases are still in identifer
            case 'a'...'z':
            case 'A'...'Z':
            case '0'...'9':
            case '-':
            case '$':
            case '.':
            parse_identifier() ;
            break ;
            default:
            //identify keywords
            if (spelling=="this")
            {
                new_token_kind=tk_this;
            }
            else if (spelling=="while")
            {
            	new_token_kind=tk_while;
            }
            else if (spelling=="if-goto")
            {
            	new_token_kind=tk_if_goto;
            }
            else if (spelling=="procedure")
            {
            	new_token_kind=tk_procedure;
            }
            else if (spelling=="done")
            {
            	new_token_kind=tk_done;
            }
            break;
        }
        //c_did_not_find(cg_start_of_identifier) ;
    }
}


