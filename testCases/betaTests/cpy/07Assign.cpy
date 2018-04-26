:: 07Assign.mnc
::
:: Variable initialization and assignments.

:A
   int: n, m, k, x;
   float: a, b, c, d;

   n := 5; m := 7; k := 4;
   a := 2.5; b := 3.1; c := 4.0;

   x := k * (n + m);
   :O x;
   :N
   x := 4 * (n + m);
   :O x;
   :N
   :O (n + m) * k;
   :N
   d := c * (a - b);
   :O d;
   :N
   :O 400.0e-2 ;
   :N
   d := 0.4e+1 * (a - b);
   :O d;
   :N
:Z
