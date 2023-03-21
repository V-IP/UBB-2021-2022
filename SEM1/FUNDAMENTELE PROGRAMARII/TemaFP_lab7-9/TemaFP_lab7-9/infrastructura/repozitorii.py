from domain.entitati import Film,Client,Inchiriere
from domain.dto import InchiriereDTO
from erori.exceptii import RepoError
from datetime import datetime,timedelta

class RepoFilme(object):
    
    def __init__(self):
        self._filme = []

    def __len__(self):
        return len(self._filme)

    def adauga_film(self,film):
        for _film in self._filme:
            if _film == film:
                raise RepoError("Id existent!\n")
        self._filme.append(film)

    def adaugaFilm_rec(self,film,i):
        if i == len(self._filme):
            self._filme.append(film)
            return
        elif self._filme[i] == film:
            raise RepoError("Id existent!\n")
        self.adaugaFilm_rec(film,i+1)

    def cauta_film_id(self,id_film):
        '''
        Complexitate: O(n)
        Pentru functia de cauta film dupa id:
        Caz favorabil: Primul film este cel care trebuie: T(n) = 1 => O(1)
        Caz defavorabil: Nu s-a gasit filmul care trebuie: T(n) = n => O(n)
        Caz mediu: se afla media tuturor posibilitatilor: (1+2+..+n)/n = n(n+1)/(2n) = (n+1)/2 => T(n) = n => O(n)
        '''
        for _ in self._filme:
            if _.get_id_film() == id_film:
                return _
        raise RepoError("Id inexistent!\n")

    def cauta_film_id_rec(self,id,i):
        if i == len(self._filme):
            raise RepoError("Id inexistent!\n")
        elif self._filme[i].get_id_film() == id:
            return self._filme[i]
        return self.cauta_film_id_rec(id,i+1)

    def cauta_film_titlu(self,titlu):
        for _ in self._filme:
            if _.get_titlu() == titlu:
                return _
        raise RepoError("Titlu inexistent!\n")

    def sterge_film(self,film):
        self._filme.remove(film)

    def modifica_film(self,film,descriere):
        film.set_descriere(descriere)

    def get_all(self):
        return self._filme

class RepoClienti(object):
    
    def __init__(self):
        self._clienti = []

    def __len__(self):
        return len(self._clienti)

    def adauga_client(self,client):
        for _ in self._clienti:
            if _ == client:
                raise RepoError("Id existent!\n")
        self._clienti.append(client)

    def cauta_client_id(self,id_client):
        for _client in self._clienti:
            if _client.get_id_client() == id_client:
                return _client
        raise RepoError("Id inexistent!\n")

    def cauta_client_nume(self,nume):
        for _client in self.__clienti:
            if _client.get_nume() == nume:
                return _client
        raise RepoError("Nume inexistent!\n")

    def cauta_client_cnp(self,cnp):
        for _client in self.__clienti:
            if _client.get_cnp() == cnp:
                return _client
        raise RepoError("CNP inexistent!\n")

    def sterge_client(self,client):
        self._clienti.remove(client)

    def modifica_client(self,client,nume):
        client.set_nume(nume)

    def get_all(self):
        return self._clienti

class RepoInchirieri(object):
    
    def __init__(self):
        self._inchirieri = []

    def __len__(self):
        return len(self._inchirieri)

    def adauga_inchiriere(self,inchiriere):
        for _ in self._inchirieri:
            if _ == inchiriere:
                raise RepoError("Id existent!\n")
        self._inchirieri.append(inchiriere)

    def get_all(self):
        return self._inchirieri

    def cauta_inchiriere_id(self,film,client,data_inchiriere):
        for _ in self._inchirieri:
            if _.get_film() == film and _.get_client() == client and _.get_data_inchiriere() == data_inchiriere:
                return _
        raise RepoError("Id inexistent!\n")

    def sterge_inchiriere(self,inchiriere):
        self._inchirieri.remove(inchiriere)

    def modifica_inchiriere(self,inchiriere,data_returnare):
        inchiriere.set_data_returnare(data_returnare)


class FileRepoFilme(RepoFilme):

    def __init__(self, filename):
        RepoFilme.__init__(self)
        self.__filename = filename


    def __citeste_fisier(self):
        with open(self.__filename, "r") as f:
            self._filme = []
            linii = f.readlines()
            for linie in linii:
                linie = linie.strip()
                if len(linie) > 0:
                    parti = linie.split(",")
                    id_film = int(parti[0])
                    titlu = parti[1]
                    descriere = parti[2]
                    gen = parti[3]
                    film = Film(id_film,titlu,descriere,gen)
                    self._filme.append(film)

    def __adauga_fisier(self, film):
        with open(self.__filename, "a") as f:
            string = str(film.get_id_film())
            string += "," + film.get_titlu()
            string += "," + film.get_descriere()
            string += "," + film.get_gen()  + "\n"
            f.write(string)

    def adauga_film(self, film):
        self.__citeste_fisier()
        RepoFilme.adauga_film(self,film)
        self.__adauga_fisier(film)
    def adauga_film_rec(self, film):
        self.__citeste_fisier()
        RepoFilme.adaugaFilm_rec(self,film,0)
        self.__adauga_fisier(film)

    def __len__(self):
        self.__citeste_fisier()
        return RepoFilme.__len__(self)

    def get_all(self):
         self.__citeste_fisier()
         return RepoFilme.get_all(self)
    
    def cauta_dupa_id(self, id_film):
        self.__citeste_fisier()
        return RepoFilme.cauta_film_id(self,id_film)
    def cauta_dupa_id_rec(self, id_film):
        self.__citeste_fisier()
        return RepoFilme.cauta_film_id_rec(self,id_film,0)


class FileRepoClienti(RepoClienti):

    def __init__(self, filename):
        RepoClienti.__init__(self)
        self.__filename = filename


    def __citeste_fisier(self):
        with open(self.__filename, "r") as f:
            self._clienti = []
            linii = f.readlines()
            for linie in linii:
                linie = linie.strip()
                if len(linie) > 0:
                    parti = linie.split(",")
                    id_client = int(parti[0])
                    nume = parti[1]
                    cnp = int(parti[2])
                    client = Client(id_client,nume,cnp)
                    self._clienti.append(client)

    def __adauga_fisier(self, client):
        with open(self.__filename, "a") as f:
            string = str(client.get_id_client())
            string += "," + client.get_nume()
            string += "," + str(client.get_cnp()) + "\n"
            f.write(string)

    def adauga_client(self, client):
        self.__citeste_fisier()
        RepoClienti.adauga_client(self,client)
        self.__adauga_fisier(client)

    def __len__(self):
        self.__citeste_fisier()
        return RepoClienti.__len__(self)

    def get_all(self):
         self.__citeste_fisier()
         return RepoClienti.get_all(self)
    
    def cauta_dupa_id(self, id_client):
        self.__citeste_fisier()
        return RepoClienti.cauta_client_id(self,id_client)

class FileRepoInchirieri(RepoInchirieri):

    def __init__(self,filename):
        RepoInchirieri.__init__(self)
        self.__filename = filename

    def __len__(self):
        self.__citeste_fisier()
        return RepoInchirieri.__len__(self)

    def __citeste_fisier(self):
        with open(self.__filename, "r") as f:
            self._inchirieri = []
            linii = f.readlines()
            for linie in linii:
                linie = linie.strip()
                if len(linie) > 0:
                    id, id_film, id_client, data_inchiriere = [token.strip() for token in linie.split(",")]
                    data_inchiriere = datetime.strptime(data_inchiriere, '%Y.%m.%d').date()
                    data_returnare = data_inchiriere + timedelta(days=14)
                    inchiriere = InchiriereDTO(int(id),int(id_client),int(id_film),data_inchiriere,data_returnare)
                    self._inchirieri.append(inchiriere)

    def get_all(self):
        self.__citeste_fisier()
        return RepoInchirieri.get_all(self)