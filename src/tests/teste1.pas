program procPassRef; 

procedure p(n: integer);
begin
  if (n >= 2) then
    begin
      n := n - 1;
      p(n);
    end;
  write(n);
end;

begin
  p(3);
end. 
