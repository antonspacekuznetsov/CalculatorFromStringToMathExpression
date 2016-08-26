#include "parser.h"

using namespace std;

Parser::Parser()
{
    expr[0] = '\0';
    e = NULL;

    token[0] = '\0';
    token_type = NOTHING;
}


char* Parser::parse(const char new_expr[])
{
    try
    {
        if ((int)strlen(new_expr) > EXPR_LEN_MAX)
        {
            throw Error(200);
        }

        strncpy(expr, new_expr, EXPR_LEN_MAX - 1);
        e = expr;
        ans = 0;
        Counter=0;


        while(expr[Counter]!='\0')
        {
            if(expr[Counter]==',')
                expr[Counter]='.';

            Counter++;
        }
        getToken();
        if (token_type == DELIMETER && *token == '\0')
        {
            throw Error(4);
        }

        ans = parse_PLUS_MINUS();


        if (token_type != DELIMETER || *token != '\0')
        {
            if (token_type == DELIMETER)
            {
                throw Error(101, token);
            }
            else
            {
                throw Error(5, token);
            }
        }
        snprintf(ans_str, sizeof(ans_str), "Ans = %.2f", ans);

    }
    catch (Error err)
    {
        snprintf(ans_str, sizeof(ans_str), "Error: %s", err.get_msg());
    }

    return ans_str;
}

bool isMinus(const char c)
{
    if (c == 0) return 0;
    return c == '-';
}

bool isWhiteSpace(const char c)
{
    if (c == 0) return 0;
    return c == 32 || c == 9;
}

bool isDelimeter(const char c)
{
    if (c == 0) return 0;
    return strchr("&|<>=+/*%^!", c) != 0;
}

bool isDigitDot(const char c)
{
    if (c == 0) return 0;
    return strchr("0123456789.", c) != 0;
}


bool isDigit(const char c)
{
    if (c == 0) return 0;
    return strchr("0123456789", c) != 0;
}


void Parser::getToken()
{
    token_type = NOTHING;
    char* t;
    t = token;
    *t = '\0';

    while (*e == ' ' || *e == '\t')
    {
        e++;
    }


    if (*e == '\0')
    {
        token_type = DELIMETER;
        return;
    }

    if (*e == '-')
    {
        token_type = DELIMETER;
        *t = *e;
        e++;
        t++;
        *t = '\0';
        return;
    }

    if (*e == '(' || *e == ')')
    {
        token_type = DELIMETER;
        *t = *e;
        e++;
        t++;
        *t = '\0';
        return;
    }

    if (isDelimeter(*e))
    {
        token_type = DELIMETER;
        while (isDelimeter(*e))
        {
            *t = *e;
            e++;
            t++;
        }
        *t = '\0';
        return;
    }

    if (isDigitDot(*e))
    {
        token_type = NUMBER;
        while (isDigitDot(*e))
        {
            *t = *e;
            e++;
            t++;
        }

        *t = '\0';
        return;
    }

    token_type = UNKNOWN;
    while (*e != '\0')
    {
        *t = *e;
        e++;
        t++;
    }
    *t = '\0';
    throw Error(1, token);

    return;
}

double Parser::parse_PLUS_MINUS()
{
        int op_id;
    double ans;
    ans = parse_MUL_DIV();

    op_id = get_operator_id(token);
    while (op_id == PLUS || op_id == MINUS)
    {
        getToken();
        ans = eval_operator(op_id, ans, parse_MUL_DIV());
        op_id = get_operator_id(token);
    }

    return ans;

}

double Parser::parse_MUL_DIV()
{
       int op_id;
    double ans;
    ans = parse_MinusSign();

    op_id = get_operator_id(token);
    while (op_id == MULTIPLY || op_id == DIVIDE)
    {
        getToken();
        ans = eval_operator(op_id, ans, parse_MinusSign());
        op_id = get_operator_id(token);
    }

    return ans;
}

double Parser::parse_MinusSign()
{
    double ans;

    int op_id = get_operator_id(token);
    if (op_id == MINUS)
    {
        getToken();
        ans = parse_CheckParenthesis();
        ans = -ans;
    }
    else
    {
        ans = parse_CheckParenthesis();
    }

    return ans;
}

double Parser::parse_CheckParenthesis()
{
    if (token_type == DELIMETER)
    {
        if (token[0] == '(' && token[1] == '\0')
        {
            getToken();
            double ans = parse_PLUS_MINUS();
            if (token_type != DELIMETER || token[0] != ')' || token[1] || '\0')
            {
                throw Error(3);
            }
            getToken();
            return ans;
        }
    }
    return parse_number();
}


double Parser::parse_number()
{
double ans = 0;


        if(token_type==NUMBER)
        {
            ans = strtod(token, NULL);
            getToken();
         }

        else
        {
            if (token[0] == '\0')
            {
                throw Error(6);
            }
            else
            {
                throw Error(7);
            }
        }

    return ans;
}

int Parser::get_operator_id(const char op_name[])
{
    if (!strcmp(op_name, "+")) {return PLUS;}
    if (!strcmp(op_name, "-")) {return MINUS;}
    if (!strcmp(op_name, "*")) {return MULTIPLY;}
    if (!strcmp(op_name, "/")) {return DIVIDE;}
    return -1;
}

double Parser::eval_operator(const int op_id, const double &lhs, const double &rhs)
{
    switch (op_id)
    {
        case PLUS:      return lhs + rhs;
        case MINUS:     return lhs - rhs;
        case MULTIPLY:  return lhs * rhs;
        case DIVIDE:    return lhs / rhs;
    }

    throw Error(104, op_id);
    return 0;
}


