::  11floatArray.csc

::  Tests floatArray indexing in expressions and assignment statements.

:A
	floatarray[6]: x := [3.2, 72.5, 1.9e+3, 2.8e-2, 4.5E+4, 0.0];
	float: k;

	:O "x[0] = ", x[0];
	:O "x[1] = ", x[1];
	:O "x[2] = ", x[2];
	:O "x[3] = ", x[3];
	:O "x[4] = ", x[4];
	:O "x[5] = ", x[5];

	:O "k = ";
	:I k;
	x[0] := 2.0*k + 0.5; :O "x[0] = ", x[0];
	x[1] := x[0] + 1.2; :O "x[1] = ", x[1];
	x[2] := x[1] + x[0]; :O "x[2] = ", x[2];
	x[3] := x[2] + x[1]; :O "x[3] = ", x[3];
	x[4] := x[3] + x[2]; :O "x[4] = ", x[4];
	x[5] := x[4] + x[3]; :O "x[5] = ", x[5];

:Z
