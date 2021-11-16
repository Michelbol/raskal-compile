import os

def main():
    err = False
    os.system('ls tests/ > files.temp');
    file = open('files.temp')
    for line in file:
        print('======================================Inicio=========================================================')
        nameline = line.replace('\n', '')
        print('Arquivo: '+nameline)
        os.system('./compilador tests/'+nameline)        
        print('======================================Fim=========================================================')

main()