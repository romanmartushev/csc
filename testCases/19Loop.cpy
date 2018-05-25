::  19Loop.csc
::
::  Simple loops.

:A
	int: n, k;
	:O "Enter a positive integer upper limit for counting: ";
	:I n;
	:N;
	k := 1;
	:O "Forward: ";
	:D
		:O k;
		:N;
		k:= k + 1;
	:U (k > n);
	:N; :N;

	k := n;
	:O "Backward: ";
	:D
		:O k;
		:N;
		k := k - 1;
	:U (k == 0);

	:N; :N;
:Z
