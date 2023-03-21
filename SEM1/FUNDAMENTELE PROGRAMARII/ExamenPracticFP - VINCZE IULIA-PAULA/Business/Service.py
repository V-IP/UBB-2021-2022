from Domain.entitati import Carte
from Infrastructura.repozitorii import FileRepo

class Service(object):

    def __init__(self, repo):
        '''
        Initializeaza un obiect service carti
        :param repo: Repository
        '''
        self.__repo = repo

    def __len__(self):
        '''
        lungimea listei de carti
        '''
        return len(self.__repo)
    
    def get_all(self):
        '''
        Returneaza toate cartile din repo
        :return:
        '''
        return self.__repo.get_all()

    def adauga_carte(self,id,titlu,autor,anAparitie):
        '''
        Adauga o carte in repo
        :param id: id-ul cartii (int)
        :param titlu: titlul cartii (string)
        :param autor: autorul cartii (string)
        :param anAparitie: anul aparitiei cartii (int)
        :return:
        '''
        carte = Carte(id,titlu,autor,anAparitie)
        self.__repo.adauga_carte(carte)
        
    def sterge_carti(self,cifra):
        '''
        Sterge cartile care au in anul aparitiei cifra introdusa
        :param cifra: cifra care se cauta a fi in anul aparitiei (int)
        :return:
        '''
        self.__repo.sterge_carti(cifra)
    
    def filtrare_carti(self,titlu,anAparitie):
        '''
        Filtreaza cartile care au titlul introdus in titlu si care au anul aparitiei mai mic decat anul introdus
        :param titlu: titlul care se cauta a fi in titlul cartii (string)
        :param anAparitiei: anul aparitiei care se doreste a fi mai mare decat anul cartilor din lista (int)
        :return: o lista cu cartile care satisfac conditiile impuse
        '''
        return self.__repo.filtrare_carti(titlu,anAparitie)
    
    def undo(self,l):
        '''
        Reface ultima operatie de stergere
        :param l: lista memorata inainte de efectuarea stergerii (lista)
        :return:
        '''
        self.__repo.undo(l)