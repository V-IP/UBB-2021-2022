class Carte(object):
    
    def __init__(self,id,titlu,autor,anAparitie):
        self.__id = id
        self.__titlu = titlu
        self.__autor = autor
        self.__anAparitie = anAparitie

    def get_id(self):
        return self.__id
    def get_titlu(self):
        return self.__titlu
    def get_autor(self):
        return self.__autor
    def get_anAparitie(self):
        return self.__anAparitie
        
    def __str__(self):
        return "[" + str(self.__id) + "] " + self.__titlu + " de " + self.__autor + " - anul: " + str(self.__anAparitie) + "\n"
    def __eq__(self,other):
        return self.__id == other.__id