compilador: compilador.c sintatico.tab.c lexico.yy.c ast.c util.c

sintatico.tab.c sintatico.tab.hh: sintatico.yy
	bison -Werror -tvd -r all sintatico.yy

lexico.yy.c: lexico.l sintatico.tab.hh
	flex -o lexico.yy.c lexico.l

clean:
	@$(RM) compilador sintatico.tab.c sintatico.tab.hh sintatico.output lexico.yy.c