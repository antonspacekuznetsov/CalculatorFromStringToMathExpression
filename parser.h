#ifndef PARSER_H
#define PARSER_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>

#include "constants.h"
#include "error.h"

using namespace std;

class Parser
{

    public:
        Parser();
        char* parse(const char expr[]);


    private:

        enum TOKENTYPE {NOTHING = -1, DELIMETER, NUMBER, UNKNOWN};

        enum OPERATOR_ID {PLUS, MINUS,MULTIPLY, DIVIDE};


    private:
        char expr[EXPR_LEN_MAX+1];
        char* e;
        int Counter;

        char token[NAME_LEN_MAX+1];
        TOKENTYPE token_type;

        double ans;
        char ans_str[255];

    private:
        void getToken();

        double parse_PLUS_MINUS();
        double parse_MUL_DIV();
        double parse_MinusSign();
        double parse_CheckParenthesis();
        double parse_number();

        int get_operator_id(const char op_name[]);
        double eval_operator(const int op_id, const double &lhs, const double &rhs);

};

#endif
