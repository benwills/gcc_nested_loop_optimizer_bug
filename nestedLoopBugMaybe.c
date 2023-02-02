#include <stdio.h>
#include <inttypes.h>

const char* tokens[] = {
	"aaa",
	"bbb",
	"ccc",
};
int main()
{
	const int iTokCnt = sizeof(tokens) / sizeof(*tokens);
	printf("iTokCnt: %d\n", iTokCnt);

	for (int iBeg = 0; iBeg <= iTokCnt; iBeg++)
	{
		printf("\n----------------------------------------------------------------\n");
		printf("iBeg: %d\n", iBeg);

		for (int iEnd = iTokCnt; iEnd >= iBeg; iEnd--)
		{
			printf("\n\t------------------------------------------------\n");
			printf("\tiBeg  : %d\n", iBeg);
			printf("\tiEnd  : %d\n", iEnd);

			// @BUG:
			// When compiling with -O2 or -O3, and there are _reads_ (no writes)
			// past the end of the tokens array, `i < iEnd` is never triggered,
			// and the program eventually segfaults.
			// Compiling without optimizations or with -O1 appears to compile
			// and execute correctly.
			//
			// @NOTE:
			// This line of code is _logically_ incorrect given the desired output.
			// To be logically correct, it should be `i < iEnd`.
			// So, this bug may not affect correctly written code.
			for (int i = iBeg; i <= iEnd; i++)
			{
				printf("\n\t\t--------------------------------\n");
				printf("\t\tiBeg: %d\n", iBeg);
				printf("\t\tiEnd: %d\n", iEnd);
				printf("\t\ti   : %d\n", i);
				printf("\t\t\t%s\n", tokens[i]);
				fflush(stdout);
			}
			printf("\n");
		}
	}

	return 0;
}
