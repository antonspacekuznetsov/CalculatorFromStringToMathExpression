#include <cstdlib>
#include <cstdio>
#include "parser.h"

using namespace std;

int main(int argc, char *argv[])
{
    Parser prs;
        if (strcmp(argv[1], "") != 0)
        {
            try
            {
                // evaluate the expression
                char* result;
                result = prs.parse(argv[1]);
                printf("%s\n", result);
            }
            catch (...)
            {
                printf("\tUnnown error occured!\n");
            }
        }

    return EXIT_SUCCESS;
}
