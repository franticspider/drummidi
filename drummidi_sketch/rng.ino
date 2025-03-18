
/* original from https://github.com/edrosten/8bit_rng/blob/master/rng-4261412736.c
unsigned char x, y, z, a;

	x=0;
	y=0;
	z=0;
	a=1;

	for(unsigned long i=0;;i++)
	{
		unsigned char t = x ^ (x << 4);
		x=y;
		y=z;
		z=a;
		a = z ^ t ^ ( z >> 1) ^ (t << 1);

		printf("%i\n", a);

	}
*/

unsigned char x=0,y=0,z=0,a=1,t;

unsigned char rng_next(){
	t = x ^ (x << 4);
	x=y;
	y=z;
	z=a;
	a = z ^ t ^ ( z >> 1) ^ (t << 1);
	return a;
}

