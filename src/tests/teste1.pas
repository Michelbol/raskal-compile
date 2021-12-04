program funcaoSimples;
  var x, y, z: integer;

function f(a, b: integer): integer;
  var m: integer;
begin
  m := a * b;
  if a > b then
    f := m div (a - b)
  else
    f := b - a;
  x := a + b;
end;

begin
  x := 5;
  y := 3;
  write(z);
end.