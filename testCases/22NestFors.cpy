:/  22NestedFors.csc
  
    For loops nested four levels deep.
/:
:A
	int: i, j, k,  m;

	:F (i := 7; i <= 9; i := i + 1)
		:F (j := 1; j <= 10 - i; j := j + 1)
			:F (k := 1;k <= 5; k := k + 1)
				:F (m := 1; m <= 9; m := m + 1)
					:O 1000*i + 100*j + 10*k + m;
				:.
				:N;
			:.
			:N ;
		:.
	:.
:Z
