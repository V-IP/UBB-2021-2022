from Prezentare.user import consola
from Business.Service import Service
from Infrastructura.repozitorii import FileRepo
from Testare.teste import Teste

if __name__ == '__main__':

    repo = FileRepo("carti.txt")
    
    srv = Service(repo)
    
    ui = consola(srv)

    teste = Teste()
    teste.ruleaza_teste()

    ui.run()
    
    