program progCount;

var qtdAlunos, nota1, nota2, nota3, media: integer;

begin
  read(qtdAlunos);
  while (qtdAlunos > 0) do
  begin
    read(nota1);
    read(nota2);
    read(nota3);
    media := (nota1 + nota2 + nota3) div 3;
    if(media >= 6) then
      write(true)
    else
      write(false);
    qtdAlunos := qtdAlunos - 1;
  end;
end.