program cmdWhile;

  var n, i: integer; 
      f1, f2, f3: integer;

begin
  read(n);
  f1 := 0; f2 := 1; i := 1;
  while (i <= n) do  
  begin
    f3 := f2 + f1;
    f1 := f2;
    f2 := f3;
    i := i + 1;
  end;
  write(n,i);
end.
