#include <string>
#include <vector>
#include "iobuffer.h"
#include "symbols.h"
#include "abstract-syntax-tree.h"
#include <iostream>

// to shorten our code:
using namespace std ;
using namespace CS_IO_Buffers ;
using namespace CS_Symbol_Tables ;
using namespace Jack_Compiler ;

// ***** WHAT TO DO *****
//
// MODIFY the skeleton code below to parse a Jack class and construct the equivalent abstract syntax tree, ast.
//        The main function will print the ast formatted as XML
//
// NOTE: the correct segment and offset is recorded with every variable in the ast
//       so the code generator does not need to use any symbol tables
//
// NOTE: use the fatal_token_context() function to print fatal error messages with the current
//       input file position marked.
//
// The skeleton code has one function per non-terminal in the Jack grammar
//  - comments describing how to create relevant ast nodes prefix most functions
//  - ast nodes are immutable - you must create all the sub-trees before creating a new node
//
// The structure of the skeleton code is just a suggestion
//  - it matches the grammar but does not quite match the ast structure
//  - you will need to change the parameters / results / functions to suit your own logic
//  - you can change it as much as you like
//
// NOTE: the best place to start is to write code to parse the input without attempting to create
//       any ast nodes. If correct this parser will report errors when it finds syntax errors but
//       correct programs will fail because the tree printer will not be provided with a valid ast.
//       Once the parsing works modify your code to create the ast nodes.
//
// NOTE: the return create_empty() ; statements are only present so that this skeleton code will compile.
//       these statements need to be replaced by code that creates the correct ast nodes.
//

// The Jack grammar to be recognised:
// program          ::= One or more classes, each class in a separate file named <class_name>'.Jack'
// class            ::= 'class' identifier '{' class_var_decs subr_decs '}'
// class_var_decs   ::= (static_var_dec | field_var_dec)*
// static_var_dec   ::= 'static' type identifier (',' identifier)* ';'
// field_var_dec    ::= 'field' type identifier (',' identifier)* ';'
// type             ::= 'int' | 'char' | 'boolean' | identifier
// vtype            ::= 'void' | type
// subr_decs        ::= (constructor | function | method)*
// constructor      ::= 'constructor' identifier identifier '(' param_list ')' subr_body
// function         ::= 'function' vtype identifier '(' param_list ')' subr_body
// method           ::= 'method' vtype identifier '(' param_list ')' subr_body
// param_list       ::= ((type identifier) (',' type identifier)*)?
// subr_body        ::= '{' var_decs statements '}'
// var_decs         ::= var_dec*
// var_dec          ::= 'var' type identifier (',' identifier)* ';'

// statements       ::= statement*
// statement        ::= let | if | while | do | return
// let              ::= 'let' identifier index? '=' expr ';'
// if               ::= 'if' '(' expr ')' '{' statements '}' ('else' '{' statements '}')?
// while            ::= 'while' '(' expr ')' '{' statements '}'
// do               ::= 'do' identifier (id_call | call) ';'
// return           ::= 'return' expr? ';'

// expr             ::= term (infix_op term)*
// term             ::= integer_constant | string_constant | 'true' | 'false' | 'null' | 'this' | '(' expr ')' | unary_op term | var_term
// var_term         ::= identifier (index | id_call | call)?
// id_call          ::= '.' identifier call
// call             ::= '(' expr_list ')'
// expr_list        ::= (expr (',' expr)*)?
// infix_op         ::= '+' | '-' | '*' | '/' | '&' | '|' | '<' | '>' | '='
// unary_op         ::= '-' | '~'


// forward declarations of one function per non-terminal rule in the Jack grammar - except for program
// NOTE: parse_type(), parse_vtype(), parse_unary_op() all return a Token not an ast
//
ast parse_class() ;
ast parse_class_var_decs() ;
ast parse_static_var_dec() ;
ast parse_field_var_dec() ;
Token parse_type() ;
Token parse_vtype() ;
ast parse_subr_decs() ;
ast parse_constructor() ;
ast parse_function() ;
ast parse_method() ;
ast parse_param_list() ;
ast parse_subr_body() ;
ast parse_var_decs() ;
ast parse_var_dec() ;

ast parse_statements() ;
ast parse_statement() ;
ast parse_let() ;
ast parse_if() ;
ast parse_while() ;
ast parse_do() ;
ast parse_return() ;

ast parse_expr() ;
ast parse_term() ;
ast parse_var_term() ;
ast parse_index() ;
ast parse_id_call() ;
ast parse_call() ;
ast parse_expr_list() ;
ast parse_infix_op() ;
Token parse_unary_op() ;

int offset, class_offset, subr_offset, class_index;
int offset_static, offset_field;
string segment, class_name, first;

symbols class_symbols = create_ints();
symbols subr_symbols = create_ints();
symbols vars_sub = create_variables() ;

//symbols var_symbols = create_variables() ;
std::vector<symbols> vars_sub_symbols;
// std::vector<vector<symbols>> class_vars_sub_symbols;
std::vector<symbols> var_symbols;
// std::vector<vector<symbols>> class_var_symbols;
std::vector<ast> subr_ast;
std::vector<vector<ast>> class_subr_ast;



// ast condition = nullptr;
// ast body = nullptr;

    
// class ::= 'class' identifier '{' class_var_decs subr_decs '}'
// create_class(myclassname,class_var_decs,class_subrs)
ast parse_class()
{
    push_error_context("parse_class()") ;

    mustbe(tk_class);
    class_name = token_spelling(mustbe(tk_identifier));
    mustbe(tk_lcb);
    insert_ints(class_symbols,class_name, class_offset) ;
    var_symbols.push_back(create_variables());
    //class_subr_ast.push_back(vector<symbols> subr_symbols);
    ast class_var_decs = parse_class_var_decs();
    ast subr_decs = parse_subr_decs();

    // class_var_symbols.push_back(var_symbols);
    // class_subr_ast.push_back(subr_ast);
    // class_vars_sub_symbols.push_back(vars_sub_symbols);
    subr_symbols = create_ints();
    class_offset++;

    pop_error_context() ;
    //return create_empty() ;
    return create_class(class_name,class_var_decs,subr_decs) ;
}

// class_var_decs ::= (static_var_dec | field_var_dec)*
// returns ast_class_var_decs: create_class_var_decs(vector<ast> decs)
// create_class_var_decs must be passed a vector of ast_var_decs
//
ast parse_class_var_decs()
{
    push_error_context("parse_class_var_decs()") ;
    std::vector<ast> vars;
    segment = "local";
    // offset = 0;
    // while (have_next(tk_static))
    // {
    //     segment = "static";
    //     vars.push_back(parse_static_var_dec());
    // }
    // offset = 0;
    // while(have_next(tk_field))
    // {
    //     segment = "this";
    //     vars.push_back(parse_field_var_dec());
    // }
    offset = 0;
    while (have(tk_static)||have(tk_field))
    {
        offset = offset_static;
        while (have_next(tk_static))
        {
            segment = "static";
            vars.push_back(parse_static_var_dec());
            offset = offset_static;
        }
        offset = offset_field;
        while (have_next(tk_field))
        {
            segment = "this";
            vars.push_back(parse_field_var_dec());
            offset = offset_field;
        }
    }
    

    pop_error_context() ;
    return create_class_var_decs(vars) ;
}

// static_var_dec ::= 'static' type identifier (',' identifier)* ';'
// returns ast_var_decs: create_var_decs(vector<ast> decs)
// create_var_decs must be passed a vector of ast_var_dec
//
// ast_var_dec: create_var_dec(string name,string segment,int offset,string type)
// create_var_dec must be passed:
// . name: the variable's name
// . segment: the variable's segment
// . offset: the variable's position in it's segment
// . type: the variable's type
//
ast parse_static_var_dec()
{
    push_error_context("parse_class()") ;

    vector<ast> decs;

    while(have(tg_starts_type) || have(tk_identifier))
    {
        decs.push_back(parse_var_dec());
        offset_static++;
    }

    pop_error_context() ;
    return create_var_decs(decs) ;
}

// field_var_dec ::= 'field' type identifier (',' identifier)* ';'
// returns ast_var_decs: create_var_decs(vector<ast> decs)
// create_var_decs must be passed a vector of ast_var_dec
//
// ast_var_dec: create_var_dec(string name,string segment,int offset,string type)
// create_var_dec must be passed:
// . name: the variable's name
// . segment: the variable's segment
// . offset: the variable's position in it's segment
// . type: the variable's type
//
ast parse_field_var_dec()
{
    push_error_context("parse_class()") ;

    vector<ast> decs;

    while(have(tg_starts_type) || have(tk_identifier))
    {
        decs.push_back(parse_var_dec());
        offset_field++;
    }

    pop_error_context() ;
    return create_var_decs(decs) ;
}

// type ::= 'int' | 'char' | 'boolean' | identifier
// returns the Token for the type
Token parse_type()
{
    push_error_context("parse_type()") ;

    pop_error_context() ;
    return nullptr ;
}

// vtype ::= 'void' | type
// returns the Token for the type
Token parse_vtype()
{
    push_error_context("parse_vtype()") ;

    pop_error_context() ;
    return nullptr ;
}

// subr_decs ::= (constructor | function | method)*
// returns ast_subr_decs: create_subr_decs(vector<ast> subrs)
// create_subr_decs must be passed an vector of ast_subr
//
// ast_subr: create_
// create_subr must be passed one of: ast_constructor, ast_function or ast_method
//
ast parse_subr_decs()
{
    push_error_context("parse_subr_decs()") ;

    vector<ast> subrs;
    subr_offset=0;

    while(have(tg_starts_subroutine))
    {
        ast subr;
        if (have_next(tk_constructor))
        {
            subr=parse_constructor();
            subrs.push_back(create_subr(subr));
            subr_ast.push_back(subr);
        }
        else if (have_next(tk_function))
        {
            subr=parse_function();
            subrs.push_back(create_subr(subr));
            subr_ast.push_back(subr);
        }
        else if (have_next(tk_method))
        {
            subr=parse_method();
            subrs.push_back(create_subr(subr));
            subr_ast.push_back(subr);
        }
        subr_offset++;

        vars_sub_symbols.push_back(vars_sub);
        vars_sub = create_variables() ;

    }

    // cout<<"testing"<<endl;
    // ast_kind kind = ast_node_kind(class_subr_ast[class_offset][0]);
    // switch (kind)
    // {
    //     case ast_constructor:
    //         cout<<"ast_constructor"<<endl;
    //         break;
    //     case ast_function:
    //         cout<<"ast_function"<<endl;
    //         break;
    //     case ast_method:
    //         cout<<"ast_method"<<endl;
    //         break;
    //     default:
    //         break;
    // }


    pop_error_context() ;
    return create_subr_decs(subrs) ;
}

// constructor ::= 'constructor' identifier identifier '(' param_list ')' subr_body
// returns ast_constructor: create_constructor(string vtype,string name,ast params,ast body)
// . vtype: the constructor's return type, this must be it's class name
// . name: the constructor's name within its class
// . params: ast_param_list - the constructor's parameters
// . body: ast_subr_body - the constructor's body
//
ast parse_constructor()
{
    push_error_context("parse_constructor()") ;

    Token type = mustbe(tg_starts_vtype);
    string vtype = token_spelling(type);
    if (have(tg_starts_vtype))
    {
        parse_type();
    }
    else
    {
        parse_vtype();
    }
    string name = token_spelling(mustbe(tk_identifier));
    ast params = parse_param_list();
    ast body = parse_subr_body();

    insert_ints(subr_symbols, name, subr_offset);

    pop_error_context() ;
    return create_constructor(vtype, name, params, body) ;
}

// function ::= 'function' vtype identifier '(' param_list ')' subr_body
// returns ast_function: create_function(string vtype,string name,ast params,ast body)
// . vtype: the function's return type
// . name: the function's name within its class
// . params: ast_param_list - the function's parameters
// . body: ast_subr_body - the function's body
//
ast parse_function()
{
    push_error_context("parse_function()") ;

    Token type = mustbe(tg_starts_vtype);
    string vtype = token_spelling(type);
    if (have(tg_starts_vtype))
    {
        parse_type();
    }
    else
    {
        parse_vtype();
    }
    string name = token_spelling(mustbe(tk_identifier));
    //offset++;
    ast params = parse_param_list();
    ast body = parse_subr_body();

    insert_ints(subr_symbols, name, subr_offset);

    // cout<<"testing"<<endl;
    // ast temp = create_function(vtype, name, params, body);
    // subr_ast.push_back(temp);
    // cout<<subr_ast[subr_offset].get_function_vtype(temp)<<endl;;
    //subr_symbols.push_back

    pop_error_context() ;
    return create_function(vtype, name, params, body) ;
}

// method ::= 'method' vtype identifier '(' param_list ')' subr_body
// returns ast_method: create_method(string vtype,string name,ast params,ast body)
// . vtype: the method's return type
// . name: the method;s name within its class
// . params: ast_param_list - the method's explicit parameters
// . body: ast_subr_body - the method's body
//
ast parse_method()
{
    push_error_context("parse_method()") ;

    Token type = mustbe(tg_starts_vtype);
    string vtype = token_spelling(type);
    if (have(tg_starts_vtype))
    {
        parse_type();
    }
    else
    {
        parse_vtype();
    }
    string name = token_spelling(mustbe(tk_identifier));
    offset++;
    ast params = parse_param_list();
    ast body = parse_subr_body();

    insert_ints(subr_symbols, name, subr_offset);


    pop_error_context() ;
    //return create_empty() ;
    return create_method(vtype, name, params, body) ;
}

// param_list ::= ((type identifier) (',' type identifier)*)?
// returns ast_param_list: create_param_list(vector<ast> params)
// create_param_list must be passed a vector of ast_var_dec
//
// ast_var_dec: create_var_dec(string name,string segment,int offset,string type)
// create_var_dec must be passed:
// . name: the variable's name
// . segment: the variable's segment
// . offset: the variable's position in it's segment
// . type: the variable's type
//
ast parse_param_list()
{
    push_error_context("parse_param_list()") ;
    vector<ast> params;
    //ast param;
    segment="argument";
    string type;
    string name;

    mustbe(tk_lrb);
    if (have(tg_starts_type))
    {
        type = token_spelling(mustbe(tg_starts_type)) ;
        name = token_spelling(mustbe(tk_identifier)) ;
        params.push_back(create_var_dec(name,segment,offset, type));
        insert_variables(vars_sub, name, st_variable(name,type, segment,offset));
        //cout<<"testing "<<name<<type<<endl;
        offset++;
    }

    while(have_next(tk_comma))
    {
        type = token_spelling(mustbe(tg_starts_type)) ;
        name = token_spelling(mustbe(tk_identifier)) ;
        params.push_back(create_var_dec(name,segment,offset, type));
        insert_variables(vars_sub, name, st_variable(name,type, segment,offset));
        offset++;
    }
    offset=0;

    mustbe(tk_rrb);

    pop_error_context() ;
    return create_param_list(params) ;
}

// subr_body ::= '{' var_decs statements '}'
// returns ast_subr_body: create_subr_body(ast decs,ast body)
// create_subr_body must be passed:
// . decs: ast_var_decs - the subroutine's local variable declarations
// . body: ast_statements - the statements within the body of the subroutinue
//
ast parse_subr_body()
{
    push_error_context("parse_subr_body()") ;

    offset = 0;
    segment = "local";

    mustbe(tk_lcb);
    ast decs = parse_var_decs();
    ast body = parse_statements();
    mustbe(tk_rcb);

    pop_error_context() ;
    return create_subr_body(decs, body) ;
}

// var_decs ::= var_dec*
// returns ast_var_decs: create_var_decs(vector<ast> decs)
// create_var_decs must be passed a vector of ast_var_decs
//
ast parse_var_decs()
{
    push_error_context("parse_var_decs()") ;

    vector<ast> vars;

    while(have_next(tk_var))
    {
        vars.push_back(parse_var_dec());
    }
    offset = 0;

    pop_error_context() ;
    return create_var_decs(vars) ;
}

// var_dec ::= 'var' type identifier (',' identifier)* ';'
// returns ast_var_decs: create_var_decs(vector<ast> decs)
// create_var_decs must be passed a vector of ast_var_dec
//
// ast_var_dec: create_var_dec(string name,string segment,int offset,string type)
// create_var_dec must be passed:
// . name: the variable's name
// . segment: the variable's segment
// . offset: the variable's position in it's segment
// . type: the variable's type
//
ast parse_var_dec()
{
    vector<ast> decs ;
    push_error_context("parse_var_dec()") ;
    string type;

    if (have(tk_identifier))
    {
        type = token_spelling(current_token());
        next_token();
    }
    else
    {
        type = token_spelling(mustbe(tg_starts_type)) ;
    }
    string name = token_spelling(mustbe(tk_identifier)) ;
    decs.push_back(create_var_dec(name,segment,offset, type));


    if (segment=="local"||segment=="argument")
    {
        insert_variables(vars_sub, name, st_variable(name,type, segment,offset));
        //cout<<"testing "<<name<<endl;
    }
    else
    {
        insert_variables(var_symbols[class_offset], name, st_variable(name,type, segment,offset));
        //cout<<"testing "<<name<<" "<<type<<" "<<segment<<endl;
    }

    
    offset++;
    while(have_next(tk_comma))
    {
        name = token_spelling(mustbe(tk_identifier)) ;
        decs.push_back(create_var_dec(name,segment,offset, type));

        if (segment=="local"||segment=="argument")
        {
            insert_variables(vars_sub, name, st_variable(name,type, segment,offset));
            //cout<<"testing "<<name<<endl;
        }
        else
        {
            insert_variables(var_symbols[class_offset], name, st_variable(name,type, segment,offset));
            //cout<<"testing "<<name<<" "<<type<<" "<<segment<<endl;
        }
        offset++;
    }

    mustbe(tk_semi);

    pop_error_context() ;
    return create_var_decs(decs) ;
}

// statements ::= statement*
// create_statements(vector<ast> statements)
// create_statements must be passed a vector of ast_statement
//
ast parse_statements()
{
    push_error_context("parse_statements()") ;

    std::vector<ast> statements;

    while(have(tg_starts_statement))
    {
        statements.push_back(parse_statement());
    }

    pop_error_context() ;
    return create_statements(statements) ;
}

// statement ::= let | if | while | do | return
// create_statement(ast statement)
// create_statement initialiser must be one of: ast_let, ast_let_array, ast_if, ast_if_else, ast_while, ast_do, ast_return or ast_return_expr
//
ast parse_statement()
{
    push_error_context("parse_statement()") ;

    ast statement = nullptr;
    if (have_next(tk_let))
    {
        statement = parse_let();
        //cout<<"let"<<endl;
    }
    else if (have_next(tk_do))
    {
        statement = parse_do();
    }
    else if (have_next(tk_if))
    {
        statement = parse_if();
    }
    else if (have_next(tk_while))
    {
        statement = parse_while();
    }
    else if (have_next(tk_return))
    {
        statement = parse_return();
    }


    pop_error_context() ;
    return create_statement(statement) ;
}

// let ::= 'let' identifier index? '=' expr ';'
// return one of: ast_let or ast_let_array
//
// create_let(ast var,ast expr)
// . var: ast_var - the variable being assigned to
// . expr: ast_expr - the variable's new value
//
// create_let_array(ast var,ast index,ast expr)
// . var: ast_var - the variable for the array being assigned to
// . index: ast_expr - the array index
// . expr: ast_expr - the array element's new value
//
ast parse_let()
{
    push_error_context("parse_let()") ;

    string name = token_spelling(mustbe(tk_identifier));
    st_variable st_var = lookup_variables(var_symbols[class_offset], name);
    if (st_var.offset == -1)
    {
        st_var = lookup_variables(vars_sub, name);
    }
    ast var = create_var(st_var.name,st_var.segment,st_var.offset,st_var.type) ;
    
    parse_index();
    mustbe(tk_eq);
    ast expr = parse_expr();
    mustbe(tk_semi);
    //cout<<token_spelling()<<endl; 




    pop_error_context() ;
    return create_let(var,expr) ;
}

// if ::= 'if' '(' expr ')' '{' statements '}' ('else' '{' statements '}')?
// return one of: ast_if or ast_if_else
//
// create_if(ast condition,ast if_true)
// . condition: ast_expr - the if condition
// . if_true: ast_statements - the if true branch
//
// create_if_else(ast condition,ast if_true,ast if_false)
// . condition: ast_expr - the if condition
// . if_true: ast_statements - the if true branch
// . if_false: ast_statements - the if false branch
//
ast parse_if()
{
    push_error_context("parse_if()") ;

    mustbe(tk_lrb);
    ast condition = parse_expr();
    mustbe(tk_rrb);
    mustbe(tk_lcb);
    ast body = parse_statements();
    mustbe(tk_rcb);
    if (have_next(tk_else))
    {
        mustbe(tk_lcb);
        ast body_else = parse_statements();
        mustbe(tk_rcb);
        pop_error_context() ;
        return create_if_else(condition,body,body_else) ;
    }

    pop_error_context() ;
    return create_if(condition,body) ;
}


// while ::= 'while' '(' expr ')' '{' statements '}'
// returns ast_while: create_while(ast condition,ast body)
// . condition: ast_expr - the loop condition
// . body: ast_statements - the loop body
//
ast parse_while()
{
    push_error_context("parse_while()") ;


    mustbe(tk_lrb);
    ast condition = parse_expr();
    mustbe(tk_rrb);
    mustbe(tk_lcb);
    ast body = parse_statements();
    mustbe(tk_rcb);

    pop_error_context() ;
    return create_while(condition,body) ;
}

// do ::= 'do' identifier (call | id_call) ';'
// returns ast_do: create_do(ast call)
// create_do must be passed one of: ast_call_as_function or ast_call_as_method
//
// ast_call_as_function: create_call_as_function(string class_name,ast subr_call)
// create_ast_call_as_function must be passed:
// . class_name: name of the function's class
// . subr_call: ast_subr_call - the function's name within it's class and it's explicit arguments
//
// ast_call_as_method: create_call_as_method(string class_name,ast object,ast subr_call)
// create_ast_call_as_method must be passed:
// . class_name: name of the method's class
// . object: ast_expr - the object the method is applied to
// . subr_call: ast_subr_call - the method's name within it's class and it's explicit arguments
//
ast parse_do()
{
    push_error_context("parse_do()") ;

    mustbe(tk_identifier);

    ast call = parse_call();

    pop_error_context() ;
    return create_do(call) ;
}

// return ::= 'return' expr? ';'
// returns one of: ast_return or ast_return_expr
//
// ast_return: create_return()
//
// ast_return_expr: create_return_expr(ast expr)
// create_return_expr must be passed an ast_expr
//
ast parse_return()
{
    push_error_context("parse_return()") ;

    if (have(tg_starts_term))
    {
        //cout<<"testing "<<token_spelling(current_token())<< endl;
        ast expr = parse_expr();
        mustbe(tk_semi);
        pop_error_context() ;
        return create_return_expr(expr) ;
    }
    mustbe(tk_semi);
    pop_error_context() ;
    return create_return() ;
}

// expr ::= term (infix_op term)*
// returns ast_expr: create_expr(vector<ast> expr)
// the vector passed to create_expr:
// . must be an odd length of at least 1, ie 1, 3, 5, ...
// . must be  a vector alternating between ast_term and ast_infix_op nodes, ending with an ast_term
//
ast parse_expr()
{
    push_error_context("parse_expr()") ;

    vector<ast> expr;

    ast text;

    if (have(tg_starts_term))
    {
        text = parse_term();
        expr.push_back(text);
    }

    while(have(tg_infix_op))
    {
        expr.push_back(parse_infix_op());
        have_next(tg_infix_op);
        expr.push_back(parse_term());
    }
    


    pop_error_context() ;
    //return create_empty() ;
    return create_expr( expr) ;
}

// term ::= integer_constant | string_constant | 'true' | 'false' | 'null' | 'this' | '(' expr ')' | unary_op term | var_term
// returns ast_term: create_term(ast term)
// create_term must be passed one of: ast_int, ast_string, ast_bool, ast_null, ast_this, ast_expr,
//                                    ast_unary_op, ast_var, ast_array_index, ast_call_as_function, ast_call_as_method
//
// ast_int: create_int(int _constant)
// create_int must be passed an integer value in the range 0 to 32767
//
// ast_string: create_string(string _constant)
// create_string must be passed any legal Jack string literal
//
// ast_bool: create_bool(bool t_or_f)
// create_bool must be passed true or false
//
// ast_null: create_null()
//
// ast_this: create_this()
//
// ast_unary_op: create_unary_op(string op,ast term)
// create_unary_op must be passed:
// . op: the unary op
// . term: ast_term
//
ast parse_term()
{
    push_error_context("parse_term()") ;

    ast term;
    TokenKind kind = token_kind(current_token());
    // if(kind==tk_identifier)
    // {
    //     string name = token_spelling(current_token());
    //     st_variable st_var = lookup_variables(var_symbols[class_offset], name);
    //     if(st_var.offset != -1)
    //     {
    //         term = create_var(st_var.name,st_var.segment,st_var.offset,st_var.type) ;
    //         next_token() ;
    //         pop_error_context() ;
    //         return create_term(term) ;
    //     }
    //     else if((class_index = lookup_ints(class_symbols, name)) != -1)
    //     {
    //         term = create_var(st_var.name,st_var.segment,st_var.offset,st_var.type) ;
    //         next_token() ;
    //         // pop_error_context() ;
    //         // return create_term(term) ;
    //         pop_error_context() ;
    //         return create_empty() ;
    //     }
    // }

    switch(kind)
    {
        case tk_identifier:
            term = parse_var_term();
            next_token() ;
            break;
        case tk_integerConstant: 
            term = create_int(token_ivalue());
            next_token() ;
            //cout<<"testing"<<endl;
            break;
        case tk_stringConstant: 
            term = create_string(token_spelling());
            next_token() ;
            break;
        case tk_true: 
            term = create_bool(true);
            next_token() ;
            break;
        case tk_false: 
            term = create_bool(false);
            next_token() ;
            break;
        case tk_sub:
            next_token() ;
            term = create_unary_op("-", parse_term());
            break;
        case tk_not:
            next_token() ;
            term = create_unary_op("!", parse_term());
            break;
        case tk_null: 
            term = create_null();
            next_token() ;
            break;
        case tk_this:
            term = create_this();
            next_token() ;
            break;
        case tk_lrb: 
            term = parse_expr();

            mustbe(tk_rrb);
            break;
        // case tg_infix_op:

        default:
            pop_error_context() ;
            return create_empty() ;
    }
    // if (kind!=tk_identifier)
    // {
    //     next_token() ;
    // }
    //next_token() ;

    pop_error_context() ;
    return create_term(term) ;
}

// var_term ::= identifier (index | id_call | call)?
// returns one of: ast_var, ast_array_index, ast_call_as_function or ast_call_as_method
//
// ast_var: create_var(string name,string segment,int offset,string type)
// create_ast_var must be passed:
// . name: the variable's name
// . segment: the variable's segment
// . offset: the variable's position in it's segment
// . type: the variable's type
//
// ast_array_index: create_array_index(ast var,ast index)
// create_ast_array_index must be passed:
// . var: ast_var - the array variable
// . index: ast_expr - the index into the array
//
// ast_call_as_function: create_call_as_function(string class_name,ast subr_call)
// create_ast_call_as_function must be passed:
// . class_name: name of the function's class
// . subr_call: ast_subr_call - the function's name within it's class and it's explicit arguments
//
// ast_call_as_method: create_call_as_method(string class_name,ast object,ast subr_call)
// create_ast_call_as_method must be passed:
// . class_name: name of the method's class
// . object: ast_expr - the object the method is applied to
// . subr_call: ast_subr_call - the method's name within it's class and it's explicit arguments
//
ast parse_var_term()
{
    push_error_context("parse_var_term()") ;
    //return create_empty() ;

    ast term;

    string name = token_spelling(current_token());
    int subr_index = lookup_ints(subr_symbols,name);
    st_variable st_var = lookup_variables(vars_sub, name);
    if (st_var.offset == -1)
    {
        st_var = lookup_variables(var_symbols[class_offset], name);
    }
    if (st_var.offset != -1)
    {
        if (st_var.type == "int" || st_var.type ==  "char" || st_var.type ==  "boolean")
        {
            term = create_var(st_var.name,st_var.segment,st_var.offset,st_var.type) ;
            pop_error_context() ;
            return term ;
        }
        else
        {
            
            next_token();
            ast ast_var = create_var(st_var.name,st_var.segment,st_var.offset,st_var.type) ;
            term = parse_id_call();
            term = create_call_as_method(st_var.type, ast_var, term) ;
            pop_error_context() ;
            return term ;
        }
    }
    else
    {
        if(subr_index != -1)
        {
            ast ast_var = subr_ast[subr_index];
            next_token();
            ast expr_list=parse_call();
            ast subr_call = create_subr_call(name, expr_list) ;
            term = create_call_as_method(class_name,create_this(),subr_call) ;
            pop_error_context() ;
            return term ;
        }
        else
        {
            next_token();
            term = parse_id_call();
            term = create_call_as_function(name,term) ;

            // pop_error_context() ;
            // return create_term(term) ;
            pop_error_context() ;
            return term ;
        }
    }
    // else
    // {
    //     cout<<"couldn't found"<<endl;
    // }


    // ast_kind kind = ast_node_kind(class_subr_ast[class_offset][0]);
    // switch (kind)
    // {
    //     case ast_constructor:
    //         cout<<"ast_constructor"<<endl;
    //         break;
    //     case ast_function:
    //         cout<<"ast_function"<<endl;
    //         break;
    //     case ast_method:
    //         cout<<"ast_method"<<endl;
    //         break;
    //     default:
    //         break;
    // }

    pop_error_context() ;
    return create_empty() ;
}

// index ::= '[' expr ']'
// returns ast_expr
ast parse_index()
{
    push_error_context("parse_index()") ;

    if(have_next(tk_lsb))
    {
        ast ast_expr = parse_expr();
        mustbe(tk_rsb);
        pop_error_context() ;
        return ast_expr ;
    }


    pop_error_context() ;
    return create_empty() ;
}

// id_call ::= '.' identifier call
// returns ast_subr_call: create_subr_call(string subr_name,ast expr_list)
// create_subr_call must be passed:
// . subr_name: the constructor, function or method's name within its class
// . expr_list: ast_expr_list - the explicit arguments to the call
//
ast parse_id_call()
{
    push_error_context("parse_id_call()") ;
    string subr_name;
    ast expr_list;

    mustbe(tk_stop);
    subr_name=token_spelling(mustbe(tk_identifier));
    expr_list=parse_call();



    pop_error_context() ;
    return create_subr_call(subr_name, expr_list) ;
}

// call ::= '(' expr_list ')'
// returns ast_expr_list
//
ast parse_call()
{
    push_error_context("parse_call()") ;

    mustbe(tk_lrb);
    ast ast_expr_list = parse_expr_list();
    have(tk_rrb);
    //cout<<"testing"<<endl;

    pop_error_context() ;
    return ast_expr_list ;
}

// expr_list ::= (expr (',' expr)*)?
// returns ast_expr_list: create_expr_list(vector<ast> exprs)
// create_expr_list must be passed: a vector of ast_expr
//
ast parse_expr_list()
{
    push_error_context("parse_expr_list()") ;

    vector<ast> exprs;
    if (have(tg_starts_term))
    {
        exprs.push_back(parse_expr());
    }
    while(have_next(tk_comma))
    {
        exprs.push_back(parse_expr());
    }

    pop_error_context() ;
    return create_expr_list( exprs) ;
}

// infix_op ::= '+' | '-' | '*' | '/' | '&' | '|' | '<' | '>' | '='
// returns ast_op: create_infix_op(string infix_op)
// create_infix_op must be passed:
// infix_op: the infix op
//
ast parse_infix_op()
{
    push_error_context("parse_infix_op()") ;
    string spelling = token_spelling(current_token());

    pop_error_context() ;
    return create_infix_op(spelling) ;
}

// unary_op ::= '-' | '~'
// returns Token for the unary_op
//
Token parse_unary_op()
{
    push_error_context("parse_unary_op()") ;

    pop_error_context() ;
    return nullptr ;
}

ast jack_parser()
{
    // read the first token to get the tokeniser initialised
    next_token() ;

    // construct tree and return as result
    return parse_class() ;
}

// main program
int main(int argc,char **argv)
{
    // parse a Jack class and print the abstract syntax tree as XML
    ast_print_as_xml(jack_parser(),4) ;

    // flush the output and any errors
    print_output() ;
    print_errors() ;
}

