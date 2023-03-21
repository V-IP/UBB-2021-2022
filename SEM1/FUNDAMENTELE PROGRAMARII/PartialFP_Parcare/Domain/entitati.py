class Loc(object):

    def __init__(self,id,nume,strada,numar_ultilizari):
        self.__id = id
        self.__nume = nume
        self.__strada = strada
        self.__numar_utilizari = numar_ultilizari

    def get_id(self):
    # getter pentru id
        return self.__id
    def get_nume(self):
    # getter pentru nume
        return self.__nume
    def get_strada(self):
    # getter pentru strada
        return self.__strada
    def get_nr(self):
    # getter pentru numar de utilizari
        return self.__numar_utilizari

    def __eq__(self,other):
        return self.__id == other.__id
    def __str__(self):
        return "[" + str(self.__id) + "] " + self.__nume + " pe " + self.__strada + " folosit de " + str(self.__numar_utilizari) + " ori\n"
