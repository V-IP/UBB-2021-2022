import datetime

class Film(object):
    
    def __init__(self,id_film,titlu,descriere,gen):
        self.__id_film = id_film
        self.__titlu = titlu
        self.__descriere = descriere
        self.__gen = gen

    def get_id_film(self):
        return self.__id_film
    def get_titlu(self):
        return self.__titlu
    def get_descriere(self):
        return self.__descriere
    def set_descriere(self,valoare):
        self.__descriere = valoare
    def get_gen(self):
        return self.__gen

    def __eq__(self,other):
        return self.__id_film == other.__id_film
    def __str__(self):
        return "["+str(self.__id_film)+"] "+self.__titlu+" - "+self.__gen+"\n-> "+self.__descriere+"\n"
    def __len_titlu__(self):
        return len(self.__titlu)
    def __len_gen__(self):
        return len(self.__gen)


class Client(object):
    
    def __init__(self,id_client,nume,cnp):
        self.__id_client = id_client
        self.__nume = nume
        self.__cnp = cnp
    
    def get_id_client(self):
        return self.__id_client
    def get_nume(self):
        return self.__nume
    def set_nume(self,valoare):
        self.__nume = valoare
    def get_cnp(self):
        return self.__cnp

    def __eq__(self,other):
        return self.__id_client == other.__id_client
    def __str__(self):
        return "["+str(self.__id_client)+"] "+self.__nume+" -> "+str(self.__cnp)+"\n"
    def __len_nume__(self):
        return len(self.__nume)


class Inchiriere(object):

    def __init__(self,id,film,client,data_inchiriere,data_returnare):
        self.__id = id
        self.__film = film
        self.__client = client
        self.__data_inchiriere = data_inchiriere
        self.__data_returnare = data_returnare

    def get_id(self):
        return self.__id
    def get_film(self):
        return self.__film
    def get_client(self):
        return self.__client
    def get_data_inchiriere(self):
        return self.__data_inchiriere
    def get_data_returnare(self):
        return self.__data_returnare
    def set_data_returnare(self,valoare):
        self.__data_returnare = valoare

    def __eq__(self,other):
        return self.__id == other.__id
    def __str__(self):
        return "["+str(self.__film.get_id_film())+"] "+self.__film.get_titlu()+" : "+str(self.__data_inchiriere)+" -> "+str(self.__data_returnare)+"\n"

