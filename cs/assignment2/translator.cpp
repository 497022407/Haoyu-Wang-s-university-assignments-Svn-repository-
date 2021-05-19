// Assiegment2 of computer systems
// Student ID: a1785394
// Student name: Haoyu Wang

// convert Hack VM Code into Hack Assembler

#include <string>
#include "iobuffer.h"
#include "tokeniser.h"
#include "assembler-internal.h"

// to make out programs a bit neater
using namespace std ;

using namespace CS_IO_Buffers ;
using namespace Hack_Virtual_Machine ;

////////////////////////////////////////////////////////////////
/************     MODIFY CODE BETWEEN HERE     **************/

static string current_label;
static string current_class;
static string current_function;

static int count_call = 0;
static int count_op = 0;
static int count = 0;
static int count_jump = 0;

//  output "@" + number
void at(int number)
{
	output_assembler("@" + std::to_string(number));
}

//  output "@" + lable
void at(string symbol)
{
	output_assembler("@" + symbol);
}

// change the value of D
void change_D(int n)
{
	at(n);
	output_assembler("D=A");
}

// change the value of D
void change_D(string s)
{
	at(s);
	output_assembler("D=A");
}

// translate segment to RAM symbol
string to_symbol(TokenKind segment, int offset = 0)
{
	switch (segment)
	{
		case tk_argument:            // 'argument'
			return "ARG";
        case tk_local:               // 'local'
        	return "LCL";
        	break;
        case tk_pointer:             // 'pointer'
        case tk_this:                // 'this'
        	return "THIS";
        case tk_that:                // 'that'
        	return "THAT";
        case tk_temp:                // 'temp'
        	return "R" + to_string(offset+5);
        case tk_static:                // 'static'
        	return current_class+"."+to_string(offset);
        default:
        	return "LCL";
        	break;
	}
}

// push D to the top of stack
void push()
{
	at("SP");
	output_assembler("AM=M+1");
	output_assembler("A=A-1");
	output_assembler("M=D");
}

// push the value in given RAM to the top of stack
void push(TokenKind segment, int offset = 0)
{
	change_D(offset);
	at(to_symbol(segment, offset));

	switch (segment)
	{
		case tk_pointer:
			if (offset==1)
			{
				at("THAT");
			}
		case tk_temp:
		case tk_static:
			output_assembler("D=M");
		case tk_constant:
			break;
		default:
			output_assembler("A=D+M");
			output_assembler("D=M");
	}
	push();
}

// pop the top of stack to D
void pop()
{
	at("SP");
	output_assembler("AM=M-1");
	output_assembler("D=M");
}

// pop to given RAM
void pop(TokenKind segment, int offset = 0)
{
	change_D(offset);
	string s = to_symbol(segment, offset);

	if(segment == tk_temp || segment == tk_static)
	{
		pop();
		at(s);
	}
	else if (segment == tk_pointer)
	{
		pop();
		if (offset == 0)
		{
			at("THIS");
		}
		else
		{
			at("THAT");
		}
	}
	else
	{
		at(s);
		output_assembler("D=D+M");
		at("R13");
		output_assembler("M=D");
		pop();
		at("R13");
		output_assembler("A=M");
	}
	output_assembler("M=D");
}

// translate vm operator command into assembly language
static void translate_vm_operator(TokenKind the_op)
{
    start_of_vm_operator_command(the_op) ;

	// ... your code goes here ...
    switch (the_op)
    {
    	case tk_add:
	    	pop();
	   		output_assembler("A=A-1");
    		output_assembler("M=D+M");
    		break;
        case tk_and: 
        	pop();
	   		output_assembler("A=A-1");
    		output_assembler("M=D&M");
    		break;
        case tk_eq:
        	pop();
	   		at("SP");
	   		output_assembler("AM=M-1");
    		output_assembler("D=D-M");
    		at(current_label + "$jump_ture" + to_string(count_op));
    		output_assembler("D;JEQ");
    		output_assembler("D=0");
    		push();
    		at(current_label + "$jump_false" + to_string(count_op));
    		output_assembler("0;JMP");
    		output_assembler("(" + current_label+ "$jump_ture" + to_string(count_op) + ")");
    		output_assembler("D=-1");
    		push();
    		output_assembler("(" + current_label+ "$jump_false" + to_string(count_op) + ")");
    		count_op++;
    		break;
        case tk_gt: 
        	pop();
			at("R14");
			output_assembler("M=D");
			pop();
			at("R13");
			output_assembler("M=D");
			at( current_label + "$jump_neg" + to_string(count_op));
			output_assembler("D;JLT");
			at("R14");
			output_assembler("D=M");
			at(current_label + "$same" + to_string(count_op));
			output_assembler("D;JGE");
			at(0);
    		output_assembler("D=!A");
    		push();
			at(current_label + "$jump_false" + to_string(count_op));
    		output_assembler("0;JMP");
			output_assembler("(" + current_label + "$jump_neg" + to_string(count_op) + ")");
			at("R14");
			output_assembler("D=M");
			at(current_label + "$same" + to_string(count_op));
			output_assembler("D;JLT");
			output_assembler("D=0");
    		push();
			at(current_label + "$jump_false" + to_string(count_op));
    		output_assembler("0;JMP");
			output_assembler("(" + current_label + "$same" + to_string(count_op) + ")");
			at("R14");
			output_assembler("D=M");
			at("R13");
    		output_assembler("D=M-D");
    		at(current_label + "$jump_ture" + to_string(count_op));
    		output_assembler("D;JGT");
    		output_assembler("D=0");
    		push();
    		at(current_label + "$jump_false" + to_string(count_op));
    		output_assembler("0;JMP");
    		output_assembler("(" + current_label + "$jump_ture" + to_string(count_op) + ")");
    		at(0);
    		output_assembler("D=!A");
    		push();
    		output_assembler("(" + current_label + "$jump_false" + to_string(count_op) + ")");
    		count_op++;
    		break;
        case tk_lt:
        	pop();
			at("R14");
			output_assembler("M=D");
			pop();
			at("R13");
			output_assembler("M=D");
			at( current_label + "$jump_neg" + to_string(count_op));
			output_assembler("D;JLT");
			at("R14");
			output_assembler("D=M");
			at(current_label + "$same" + to_string(count_op));
			output_assembler("D;JGE");
    		output_assembler("D=0");
    		push();
			at(current_label + "$jump_false" + to_string(count_op));
    		output_assembler("0;JMP");
			output_assembler("(" + current_label+ "$jump_neg" + to_string(count_op) + ")");
			at("R14");
			output_assembler("D=M");
			at(current_label + "$same" + to_string(count_op));
			output_assembler("D;JLT");
			at(0);
    		output_assembler("D=!A");
    		push();
			at(current_label + "$jump_false" + to_string(count_op));
    		output_assembler("0;JMP");
			output_assembler("(" + current_label + "$same" + to_string(count_op) + ")");
			at("R14");
			output_assembler("D=M");
			at("R13");
    		output_assembler("D=M-D");
    		at(current_label + "$jump_ture" + to_string(count_op));
    		output_assembler("D;JLT");
    		output_assembler("D=0");
    		push();
    		at(current_label + "$jump_false" + to_string(count_op));
    		output_assembler("0;JMP");
    		output_assembler("(" + current_label + "$jump_ture" + to_string(count_op) + ")");
    		at(0);
    		output_assembler("D=!A");
    		push();
    		output_assembler("(" + current_label + "$jump_false" + to_string(count_op) + ")");
    		count_op++;
    		break;
        case tk_neg:
        	at("SP");
        	output_assembler("A=M-1");
        	output_assembler("M=-M");
        	break;
        case tk_not:
        	at("SP");
        	output_assembler("A=M-1");
        	output_assembler("M=!M");
        	break;
        case tk_or:
        	pop();
	   		output_assembler("A=A-1");
    		output_assembler("M=D|M");
    		break;
        case tk_sub:
        	pop();
	   		output_assembler("A=A-1");
        	output_assembler("M=M-D");
        	break;
        case tk_return:
			 at("LCL");
			 output_assembler("D=M");
			 at("R13");
			 output_assembler("M=D");
			 at(5);
			 output_assembler("D=D-A");
			 output_assembler("A=D");
			 output_assembler("D=M");
			 at("R14");
			 output_assembler("M=D");
			pop();
			 at("ARG");
			 output_assembler("A=M");
			 output_assembler("M=D");
			 at("ARG");
			 output_assembler("D=M+1");
			 at("SP");
			 output_assembler("M=D");
			 at("R13");
			 output_assembler("AM=M-1");
			 output_assembler("D=M");
			 at("THAT");
			 output_assembler("M=D");
			at("R13");
			 output_assembler("AM=M-1");
			 output_assembler("D=M");
			 at("THIS");
			 output_assembler("M=D");
			at("R13");
			 output_assembler("AM=M-1");
			 output_assembler("D=M");
			 at("ARG");
			 output_assembler("M=D");
			at("R13");
			 output_assembler("AM=M-1");
			 output_assembler("D=M");
			 at("LCL");
			 output_assembler("M=D");
			at("R14");
			output_assembler("A=M");
			output_assembler("0;JMP");
        default:
        	break;
    }

    end_of_vm_command() ;
}

// translate vm jump command into assembly language
static void translate_vm_jump(TokenKind jump, string label)
{
    start_of_vm_jump_command(jump,label) ;

    // ... your code goes here ...
	switch (jump)
	{
		case  tk_if_goto:
			pop();
			at(current_label+"$"+label );
			output_assembler("D;JNE");
			break;
		case tk_goto:
			at(current_label+"$"+label );
			output_assembler("0;JMP");
			break;
		case tk_label:
			output_assembler("(" + current_label+"$"+ label +  ")");
		default:
			break;
	}

    end_of_vm_command() ;
}

// translate vm call or function command into assembly language
static void translate_vm_function(TokenKind func, string label, int n)
{
    start_of_vm_func_command(func,label,n) ;

	// ... your code goes here ...
    switch (func)
	{
    	case tk_function:
    		current_label=label;
    		int p;
    		p = current_label.find('.');
    		current_class = current_label.substr(0,p);
    		current_function = current_label.substr(p+1);
    		output_assembler("(" + label + ")");
	    	
			//set n local variable to n.
	    	for (int i = 0; i < n; ++i)
	    	{
	    		at("SP");
	    		output_assembler("A=M");
	    		output_assembler("M=0");
	    		at("SP");
	    		output_assembler("M=M+1");
	    	}
	    	break;
    	case tk_call:
    		change_D(current_label +"$"+ label + to_string(count_call));
    		push();
    		at("LCL");
    		output_assembler("D=M");
    		push();
    		at("ARG");
    		output_assembler("D=M");
    		push();
    		at("THIS");
    		output_assembler("D=M");
    		push();
    		at("THAT");
    		output_assembler("D=M");
    		push();
    		change_D(n+5);
    		at("SP");
    		output_assembler("D=M-D");
    		at("ARG");
    		output_assembler("AM=D");
    		at("SP");
    		output_assembler("D=M");
    		at("LCL");
    		output_assembler("AM=D");
    		at(label);
    		output_assembler("0;JMP");
    		output_assembler("(" + current_label +"$"+ label + to_string(count_call) + ")");
    		count_call++;
    		break;
    	default:
    		break;
    }

    end_of_vm_command() ;
}

// translate vm push or pop command into assembly language
static void translate_vm_stack(TokenKind stack,TokenKind segment,int offset)
{
    start_of_vm_stack_command(stack,segment,offset) ;

	// ... your code goes here ...
	if (stack == tk_push)
	{
    	push(segment,offset);
    }
    else
    {
    	pop(segment,offset);
    }

    end_of_vm_command() ;
}

/************            AND HERE              **************/
///////////////////////////////////////////////////////////////

// grammar to be parsed:
// vm_class ::= command* eoi
// command ::= vm_operator | vm_jump | vm_func | vm_stack
// vm_operator ::= 'add' | 'and' | 'eq' | 'gt' | 'lt' | 'neg' | 'not' | 'or' | 'sub' | 'return'
// vm_jump ::= jump label
// vm_func ::= func label number
// vm_stack ::= stack segment number

// forward declare parsing functions - one per rule
static void parse_class() ;
static void parse_command() ;
static void parse_op() ;
static void parse_jump() ;
static void parse_func() ;
static void parse_stack() ;

// Note: always read one token after the one recognised

// vm_class ::= command* eoi
static void parse_class()
{
    // tell the output system we are starting to translate VM commands for a Jack class
    start_of_vm_class() ;

    while ( have(tk_vm_command) ) parse_command() ;
    mustbe(tk_eoi) ;

    // tell the output system we have just finished translating VM commands for a Jack class
    end_of_vm_class() ;
}

// command ::= vm_operator | vm_jump | vm_func | vm_stack
static void parse_command()
{
    if ( have(tk_vm_operator) ) parse_op() ; else
    if ( have(tk_vm_jump) )     parse_jump() ; else
    if ( have(tk_vm_func) )     parse_func() ; else
    if ( have(tk_vm_stack) )    parse_stack() ; else
    mustbe(tk_vm_command) ;
}

// vm_operator ::= 'add' | 'and' | 'eq' | 'gt' | 'lt' | 'neg' | 'not' | 'or' | 'sub' | 'return'
static void parse_op()
{
    TokenKind the_op = token_kind(mustbe(tk_vm_operator)) ;

    translate_vm_operator(the_op) ;
}

// vm_jump ::= jump label
// jump command - label, goto label or if-goto label
static void parse_jump()
{
    TokenKind command = token_kind(mustbe(tk_vm_jump)) ;
    string label = token_spelling(mustbe(tk_a_label)) ;

    translate_vm_jump(command,label) ;
}

// vm_func ::= func label number
// call function-name #args or function function-name #locals
static void parse_func()
{
    TokenKind command = token_kind(mustbe(tk_vm_func)) ;
    string label = token_spelling(mustbe(tk_a_label)) ;
    int number = token_ivalue(mustbe(tk_a_number)) ;

    translate_vm_function(command,label,number) ;
}

// vm_stack ::= stack segment number
// push segment offset or pop segment offset
static void parse_stack()
{
    TokenKind stack = token_kind(mustbe(tk_vm_stack)) ;
    TokenKind segment = token_kind(mustbe(tk_vm_segment)) ;
    int number = token_ivalue(mustbe(tk_a_number)) ;

    translate_vm_stack(stack,segment,number) ;
}

// main program
int main(int argc,char **argv)
{
    // initialise the tokeniser by reading the first token
    next_token() ;

    // parse a class and output VM code
    parse_class() ;

    // flush the output and any errors
    print_output() ;
    print_errors() ;
}

