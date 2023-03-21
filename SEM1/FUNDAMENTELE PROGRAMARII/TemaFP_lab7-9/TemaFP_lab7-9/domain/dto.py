class ClientDTO(object):

    def __init__(self,nume):
        self.__nume = nume
        self.__lista_inchirieri = []

    def get_nume(self):
        return self.__nume

    def __len__(self):
        return len(self.__lista_inchirieri)

    def adauga_inchiriere(self, inchiriere):
        self.__lista_inchirieri.append(inchiriere)

    def __str__(self):
        string = self.__nume + ":\n"
        for inchiriere in self.__lista_inchirieri:
            string += "\t" + str(inchiriere)
        return string


class FilmDTO(object):

    def __init__(self,titlu):
        self.__titlu = titlu
        self.__lista_clienti = []

    def __len__(self):
        return len(self.__lista_clienti)

    def get_titlu(self):
        return self.__titlu

    def adauga_client(self, client):
        self.__lista_clienti.append(client)

    def __str__(self):
        string = self.__titlu + ":\n"
        for client in self.__lista_clienti:
            string += "\t" + str(client)
        return string


class InchiriereDTO(object):

    def __init__(self,id_inc,id_client,id_film,data_inchiriere,data_returnare):
        self.__id_inc = id_inc
        self.__id_client = id_client
        self.__id_film = id_film
        self.__data_inchiriere = data_inchiriere
        self.__data_returnare = data_returnare

    def get_id_inc(self):
        return self.__id_inc
    def get_id_client(self):
        return self.__id_client
    def get_id_film(self):
        return self.__id_film
    def get_data_inchiriere(self):
        return self.__data_inchiriere
    def get_data_returnare(self):
        return self.__data_returnare
    def set_data_returnare(self,valoare):
        self.__data_returnare = valoare
