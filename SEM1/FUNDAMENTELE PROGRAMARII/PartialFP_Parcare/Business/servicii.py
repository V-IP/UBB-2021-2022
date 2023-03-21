from Domain.entitati import Loc

class ServiceLoc(object):

    def __init__(self, repoLoc):
        self.__repoLoc = repoLoc

    def __len__(self):
        return len(self.__repoLoc)

    def afisare_strada(self,strada,l):
    # selectez locuri de parcare care sunt pe strada introdusa
    # parametri: strada, string, strada introdusa de utilizator
    #            l, lista in care returnez locurile favorabile
    # se returneaza l goala daca nu exista locuri pe strada
        for loc in self.__repoLoc.get_all():
            if loc.get_strada() == strada:
                l.append(loc)

    def afisare_best(self,l_strada,l_nume):
    # selectez numele locurilor de parcare care sunt cele mai utilizate de pe fiecare strada
    # parametri: l_strada, lista in care imi adun toate denumirile de strazi
    #            l_nume, lista in care imi adaug numele locului cu cele mai multe utilizari
        for loc in self.__repoLoc.get_all():
            if loc.get_strada() not in l_strada:
                l_strada.append(loc.get_strada())
        for strada in l_strada:
            max = 0
            nume = ""
            for loc in self.__repoLoc.get_all():
                if loc.get_strada() == strada:
                    if loc.get_nr() > max:
                        max = loc.get_nr()
                        nume = loc.get_nume()
            l_nume.append(nume)

    def get_all(self):
        return self.__repoLoc.get_all()