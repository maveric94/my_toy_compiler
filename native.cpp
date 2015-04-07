#include <cstdio>

extern "C"
{
	void printi(long long val)
	{
    	printf("%lld\n", val);
    }
	void printd(double val)
	{
		printf("%f\n", val);
	}
	void putch(char val)
	{
		putchar(val);
	}
	void printstr(char *val)
	{
		printf("%s\n", val);
	}
};

