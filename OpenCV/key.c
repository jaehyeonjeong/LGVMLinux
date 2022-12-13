#include <stdio.h>

int main()
{
	int Key;
	Key=getc();

	if(Key==224)
		Key=getc();
	printf("%d", Key);

	return 0;
}
