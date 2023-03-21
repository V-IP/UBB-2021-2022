class consola(object):
    
    def __init__(self,srv):
        self.__srv = srv
        
    def __UI_adauga_carte(self):
        try:
            id = int(input("Introduceti id-ul: "))
        except ValueError:
            print("Id numeric invalid!\n")
        titlu = input("Introduceti titlul: ")
        autor = input("Introduceti autorul: ")
        try:
            anAparitie = int(input("Introduceti anul aparitiei: "))
        except ValueError:
            print("An numeric invalid!\n")
        self.__srv.adauga_carte(id,titlu,autor,anAparitie)
        print("Carte adaugata cu succes!\n")
        
    def __UI_sterge_carti(self):
        try:
            cifra = int(input("Introduceti cifra pentru stergere: "))
        except ValueError:
            print("Cifra numerica invalid!\n")
        self.__srv.sterge_carti(cifra)
        print("Stergere efectuata cu succes!\n")
        
    def __UI_filtrare_carti(self):
        titlu = input("Introduceti titlul pentru filtrare: ")
        try:
            anAparitie = int(input("Introduceti anul aparitiei: "))
        except ValueError:
            print("An numeric invalid!\n")
        l = self.__srv.filtrare_carti(titlu,anAparitie)
        print("\nFiltrarea se face dupa: '",titlu,"' si < anul ",anAparitie)
        for carte in l:
            print(carte)
            
    def __UI_undo(self,l):
        self.__srv.undo(l)
        print("Undo realizat cu succes!\n")
        
    def __PornireaAplicatiei(self):
        lista = self.__srv.filtrare_carti("",-1)
        for carte in lista:
            print(carte)
        
    def run(self):
        lista = []
        self.__PornireaAplicatiei()
        while True:
            print("Comenzile disponibile sunt: adauga carte, sterge carti, filtreaza carti, undo, exit")
            cmd = input(">>>")
            if cmd == "":
                continue
            elif cmd == "exit":
                return 
            elif cmd =="adauga carte":
                self.__UI_adauga_carte()
            elif cmd == "sterge carti":
                lista.append(self.__srv.get_all())
                self.__UI_sterge_carti()
            elif cmd == "filtreaza carti":
                self.__UI_filtrare_carti()
            elif cmd == "undo":
                self.__UI_undo(lista.pop())
            else:
                print("Comanda invalida!\n")


