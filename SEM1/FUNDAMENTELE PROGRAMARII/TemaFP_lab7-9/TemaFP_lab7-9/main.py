from prezentare.user import consola
from business.servicii import ServiciiFilme,ServiciiClienti,ServiciiInchirieri
from infrastructura.repozitorii import RepoFilme,RepoClienti,RepoInchirieri,FileRepoFilme,FileRepoClienti,FileRepoInchirieri
from validare.validatoare import ValidareFilme,ValidareClienti,ValidareInchirieri
from testare.teste import Teste

if __name__ == '__main__':

    valid_filme = ValidareFilme()
    valid_clienti = ValidareClienti()
    valid_inchirieri = ValidareInchirieri()

    repo_filme = FileRepoFilme("filme.txt")
    repo_clienti = FileRepoClienti("clienti.txt")
    repo_inchirieri = FileRepoInchirieri("inchirieri.txt")
    
    srv_filme = ServiciiFilme(valid_filme,repo_filme)
    srv_clienti = ServiciiClienti(valid_clienti,repo_clienti)
    srv_inchirieri = ServiciiInchirieri(valid_inchirieri,repo_inchirieri,repo_filme,repo_clienti)
    
    ui = consola(srv_filme,srv_clienti,srv_inchirieri)

    #teste = Teste()
    #teste.ruleaza_teste()

    ui.run()