:/ 04Expr.csc

   Real expressions
/:
:A
	float: a, b, c, d;

	a := 5.0; b := 7.0; c := 8.0; d := 12.0;
	:O a, b, c, d;
	:N
	
	:O a - b + c * d;
	:N
	:O (a - b + c) * d;
	:N
	:O (a - (b + c)) * d;
	:N
	:O ((a - b) + c) * d;
	:N
	
	:O d / b - c * d;
	:N
	:O d / (b - c) * d;
	:N
	:O d / (b - c * d);
	:N
	:O (d / b - c) * d;
	:N
	
	:O b * 5.0 + d / 2.0 * a - c;
	:N
	:O b * ((5.0 + d / 2.0 * a) - c);
	:N
	:O b * (5.0 + d )/ (2.0 * a - c);
	:N
	:O (b * 5.0 + d) / ((2.0 * a) - c);
	:N
	
	:O 20.0 * 6.0 - 45.0 + 50.0 / 2.0;
	:N
	:O ((20.0 * 6.0) - (45.0 + 50.0)) / 2.0;
	:N

:Z
