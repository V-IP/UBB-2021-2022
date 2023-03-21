from domain.entitati import Film,Client,Inchiriere
from domain.dto import InchiriereDTO,FilmDTO,ClientDTO
from erori.exceptii import ValidatorError,RepoError
import random,string

class ServiciiFilme(object):
    
    def __init__(self,valid_filme,repo_filme):
        self.__valid_filme = valid_filme
        self.__repo_filme = repo_filme
    
    def nr_filme(self):
        return len(self.__repo_filme)

    def get_all_filme(self):
        return self.__repo_filme.get_all()

    def adauga_film(self,id_film,titlu,descriere,gen):
        film = Film(id_film,titlu,descriere,gen)
        self.__valid_filme.valideaza(film)
        self.__repo_filme.adauga_film_rec(film)

    def sterge_film(self,id_film):
        film = self.__repo_filme.cauta_film_id(id_film)
        self.__repo_filme.sterge_film(film)

    def cauta_film_id(self,id_film):
        film = self.__repo_filme.cauta_dupa_id(id_film)
        film_rec = self.__repo_filme.cauta_dupa_id_rec(id_film)
        return film_rec

    def cauta_film_titlu(self,titlu):
        film = self.__repo_filme.cauta_film_titlu(titlu)
        return film

    def modifica_film(self,id_film,descriere):
        film = self.__repo_filme.cauta_film_id(id_film)
        self.__repo_filme.modifica_film(film,descriere)

    def random_filme(self):
        try:
            id_film = random.randrange(100)
            titlu = ""
            descriere = ""
            gen = ""
            for nr in range(random.randrange(50)):
                titlu += random.choice(string.ascii_letters)
                descriere += random.choice(string.ascii_letters)
                gen = random.choice(string.ascii_letters)
            film = Film(id_film,titlu,descriere,gen)
            self.__repo_filme.adauga_film(film)
        except RepoError as re:
            pass

    def bubble_sort_filme(self, l, key, reverse, cmp):
        if reverse is False:
            for j in range(0, len(l)-1):
                for i in range(len(l)-1-j):
                    if cmp(key(l[i]), key(l[i+1])):
                        l[i], l[i+1] = l[i+1], l[i]
        else:
            for j in range(0, len(l)-1):
                for i in range(len(l)-1-j):
                    if cmp(key(l[i+1]), key(l[i])):
                        l[i], l[i+1] = l[i+1], l[i]
        return l

    def shell_sort_filme(self, l, key , reverse, cmp):
        if reverse is False:
            aux = len(l) // 2
            while aux >= 1:
                i = 0
                while i < aux:
                    j = i + aux
                    while j < len(l):
                        if cmp(key(l[j]) , key(l[j-aux])):
                            l[j], l[j-aux] = l[j-aux], l[j]
                        j = j + aux
                    i = i + 1
            aux = aux // 2
        else:
            aux = len(l) // 2
            while aux >= 1:
                i = 0
                while i < aux:
                    j = i + aux
                    while j < len(l):
                        if cmp(key(l[j-aux]) , key(l[j])):
                            l[j], l[j-aux] = l[j-aux], l[j]
                        j = j + aux
                    i = i + 1
                aux = aux // 2
        return l

class ServiciiClienti(object):
    
    def __init__(self,valid_clienti,repo_clienti):
        self.__valid_clienti = valid_clienti
        self.__repo_clienti = repo_clienti

    def nr_clienti(self):
        return len(self.__repo_clienti)

    def get_all_clienti(self):
        return self.__repo_clienti.get_all()

    def adauga_client(self,id_client,nume,cnp):
        client = Client(id_client,nume,cnp)
        self.__valid_clienti.valideaza(client)
        self.__repo_clienti.adauga_client(client)

    def sterge_client(self,id_client):
        client = self.__repo_clienti.cauta_client_id(id_client)
        self.__repo_clienti.sterge_client(client)

    def modifica_client(self,id_client,nume):
        client = self.__repo_clienti.cauta_client_id(id_client)
        self.__repo_clienti.modifica_client(client,nume)

    def cauta_client_id(self,id_client):
        client = self.__repo_clienti.cauta_client_id(id_client)
        return client

    def cauta_client_nume(self,nume):
        client = self.__repo_clienti.cauta_client_nume(nume)
        return client

    def cauta_client_cnp(self,cnp):
        client = self.__repo_clienti.cauta_client_cnp(cnp)
        return client

class ServiciiInchirieri(object):

    def __init__(self,valid_inchirieri,repo_inchirieri,repo_filme,repo_clienti):
        self.__valid_inchirieri = valid_inchirieri
        self.__repo_inchirieri = repo_inchirieri
        self.__repo_filme = repo_filme
        self.__repo_clienti = repo_clienti

    def adauga_inchiriere(self,id_film,id_client,data_inchiriere,data_returnare):
        film = self.__repo_filme.cauta_film_id(id_film)
        client = self.__repo_clienti.cauta_client_id(id_client)
        inchiriere = Inchiriere(1,film,client,data_inchiriere,data_returnare)
        self.__valid_inchirieri.valideaza(inchiriere)
        self.__repo_inchirieri.adauga_inchiriere(inchiriere)

    def nr_inchirieri(self):
        return len(self.__repo_inchirieri)

    def get_all_inchirieri(self):
        return self.__repo_inchirieri.get_all()

    def top_inchiriate(self):
        inchirieri = self.__repo_inchirieri.get_all()
        data_filme = {}
        for inchiriere in inchirieri:
            film = self.__repo_filme.cauta_dupa_id(inchiriere.get_id_film())
            client = self.__repo_clienti.cauta_dupa_id(inchiriere.get_id_client())
            data_inchiriere = inchiriere.get_data_inchiriere()
            data_returnare = inchiriere.get_data_returnare()
            Ninchiriere = Inchiriere(inchiriere.get_id_inc(),film,client,data_inchiriere,data_returnare)
            if inchiriere.get_id_film() not in data_filme:
                data_filme[inchiriere.get_id_film()] = []
            data_filme[inchiriere.get_id_film()].append(Ninchiriere)
        rez = []
        for date_film in data_filme:
            titlu = data_filme[date_film][0].get_film().get_titlu()
            filmDTO = FilmDTO(titlu)
            for inchiriere in data_filme[date_film]:
                filmDTO.adauga_client(inchiriere.get_client())
            rez.append(filmDTO)
        rez.sort(key=lambda x: len(x), reverse = True)
        return rez[:3]

    def get_all_dto(self):
        inchirieri = self.__repo_inchirieri.get_all()
        data_clienti = {}
        for inchiriere in inchirieri:
            film = self.__repo_filme.cauta_dupa_id(inchiriere.get_id_film())
            client = self.__repo_clienti.cauta_dupa_id(inchiriere.get_id_client())
            data_inchiriere = inchiriere.get_data_inchiriere()
            data_returnare = inchiriere.get_data_returnare()
            Ninchiriere = Inchiriere(inchiriere.get_id_inc(),film,client,data_inchiriere,data_returnare)
            if inchiriere.get_id_client() not in data_clienti: # list(), set()
                data_clienti[inchiriere.get_id_client()] = []
            data_clienti[inchiriere.get_id_client()].append(Ninchiriere)
        rez = []
        for data_client in data_clienti:
            nume = data_clienti[data_client][0].get_client().get_nume()
            clientDTO = ClientDTO(nume)
            for inchiriere in data_clienti[data_client]:
                clientDTO.adauga_inchiriere(inchiriere)
            rez.append(clientDTO)
        return rez

    def ordonare_nume_numar(self,rez):
        rez.sort(key=lambda x:(x.get_nume(), len(x)))
        return rez

    def raport30(self,rez):
        rez.sort(key=lambda x: len(x), reverse = True)
        procent = int(0.3*len(rez))
        return rez[:procent]

    def sterge_inchiriere(self,id_film,id_client,data_inchiriere):
        film = self.__repo_filme.cauta_film_id(id_film)
        client = self.__repo_clienti.cauta_client_id(id_client)
        inchiriere = self.__repo_inchirieri.cauta_inchiriere_id(film,client,data_inchiriere)
        self.__repo_inchirieri.sterge_inchiriere(inchiriere)

    def modifica_inchiriere(self,id_film,id_client,data_inchiriere,data_returnare):
        film = self.__repo_filme.cauta_film_id(id_film)
        client = self.__repo_clienti.cauta_client_id(id_client)
        inchiriere = self.__repo_inchirieri.cauta_inchiriere_id(film,client,data_inchiriere)
        self.__repo_inchirieri.modifica_inchiriere(inchiriere,data_returnare)

    def cauta_inchiriere_id(self,id_film,id_client,data_inchiriere):
        film = self.__repo_filme.cauta_film_id(id_film)
        client = self.__repo_clienti.cauta_client_id(id_client)
        inchiriere = self.__repo_inchirieri.cauta_inchiriere_id(film,client,data_inchiriere)
        return inchiriere