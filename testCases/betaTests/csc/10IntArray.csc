::  10intArray.csc

::  Tests intArray indexing in expressions and assignment statements.

:A
	intArray[6]: x :=[3, 72, 13, 22, 44, 0] ;
	int: k;

	:O "x[0] = ", x[0];
	:O "x[1] = ", x[1];
	:O "x[2] = ", x[2];
	:O "x[3] = ", x[3];
	:O "x[4] = ", x[4];
	:O "x[5] = ", x[5];

	:O "k = ";
	:I k;
	x[0] = 2 * k - 1; :O "x[0] = ", x[0], "\n";
	x[1] = x[0] + 10; :O "x[1] = ", x[1], "\n";
	x[2] = x[1] + x[0]; :O "x[2] = ", x[2], "\n";
	x[3] = x[2] + x[1]; :O "x[3] = ", x[3], "\n";
	x[4] = x[3] + x[2]; :O "x[4] = ", x[4], "\n";
	x[5] = x[4] + x[3]; :O "x[5] = ", x[5], "\n";
	:O "\n";
:Z
