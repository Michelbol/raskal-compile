CFLAGS = -g

compilador: compilador.c sintatico.tab.c lexico.yy.c ast.c tab.c analisador.c mepa.c util.c

sintatico.tab.c sintatico.tab.h: sintatico.y
	bison -Werror -tvd -r all sintatico.y

lexico.yy.c: lexico.l sintatico.tab.h
	flex -o lexico.yy.c lexico.l

clean:
	@$(RM) compilador sintatico.tab.c sintatico.tab.h sintatico.output lexico.yy.c files.temp

test:
	python validateSamples.py 