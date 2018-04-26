:: 03Expr.csc
::
:: Integer expressions

:A
	int: a, b, c, d;
	
	a := 5; b := 7; c := 8; d := 12;
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
	
	:O d // b - c * d;
	:N
	:O d // (b - c) * d;
	:N
	:O d // (b - c * d);
	:N
	:O (d // b - c) * d;
	:N

	:O b * 5 + d / 2 * a - c;
	:N
	:O b * ((5 + d / 2 * a) - c);
	:N
	:O b * (5 + d )/ (2 * a - c);
	:N
	:O (b * 5 + d) / ((2 * a) - c);
	:N
	
	:O 20 * 6 - 45 + 50 / 2;
	:N
	:O ((20 * 6) - (45 + 50)) / 2;
	:N

	:O 20 * 6 - 45 + 50 // 2;
	:N
	:O ((20 * 6) - (45 + 50)) // 2;
	:N

:Z
