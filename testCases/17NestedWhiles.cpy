:/  17NestedWhiles.csc

    While loops nested four levels deep.
/:
:A
	int: i, j, k,  m;

	i := 7;
	:W (i <= 9)
		j := 1;
		:W (j <= 10 - i)
			k := 1;
			:W (k <= 5)
				m := 1;
				:W (m <= 9)
					:O 1000*i + 100*j + 10*k + m;
					m := m + 1;
				:.
				:N;
				k := k + 1;
			:.
			:N;
			j := j + 1;
		:.
		i := i + 1;
	:.
:Z
