program meu_programa;
var a, b, c, n, i: integer;
    x, y: integer;
    z: boolean;
    f1, f2, f3: integer;
    
    procedure p();
        var a, b: integer;
    begin
        a := 2 * x;
        b := a + 1;
        y := b + y;
    end;
begin
    //y := 2*3+2-2+2+2-4; // 6
    //y := 10 div 2; // 5
    //y := 10 div 1+1; // 11
    //y := 5+4 div 2;  // 7
    //y := (5+5) <= (9+1); //true
    // y := (5+5) > (9+2); // false
    // y := (5+5) > (5+5); // false
    // y := (5+5) >= (5+5); // true
    y := 5;
    x := 6;
    c := 99;
    b := 88;
    // if (false) then
    //     write(y)
    // else
    //     write(x);
    // if (true) then
    //     begin
    //         write(c);
    //         write(b);
    //     end
    // else
    //     begin
    //         write(y);
    //         write(x);
    //     end;
    read(n);
    f1 := 0; 
    f2 := 1; 
    i := 1;
    while (i <= n) do  
    begin
        f3 := f2 + f1;
        f1 := f2;
        f2 := f3;
        i := i + 1;
    end;
    write(n,i);
end.