::  013VarInit.csc
::
::  Tests variable initializations for simple variables (no arrays).

:A
	int: n, m, k;
	float: x, y, z, w;
	float p;
	int b1, b2, b3;

	n = 5; 
	m = 3; 
	k = 2 * (n + 2 * m);
	x = 4.0;
	y = 2.3;
	z = 0.5*(x + y);
	w = y - x;

	p = (w + 10) / k;
	b1 = 1; 
	b2 = 0;
	b3 = b1;

	:O "n = ", n;
	:O "\nm = ", m;
	:O "\nk = ", k;
	:O "\nx = ", x;
	:O "\ny = ", y;
	:O "\nz = ", z;
	:O "\nw = ", w;
	:O "\np = ", p;
	:O "\nb1 = ", b1;
	:O "\nb2 = ", b2;
	:O "\nb3 = ", b3;
	:N:N
:Z
