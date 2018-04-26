:/ 08Assign.csc
  Various arithmetic expressions.
/:

:A
   int: num1, num2, num3, num4;
   int: result;

   :O "Enter 4 integers: ";
   :I num1, num2, num3, num4;
   result := ((num1 - 3) * (num2 + num3))/ num4;
   :O "\n((num1 - 3) * (num2 + num3))/ num4 = ", result;
   :N;
   result := (num2 + num4 * num1 / 3) - num3;
   :O "\n(num2 + num4 * num1 / 3) - num3 = ", result;
   :N;

:Z
