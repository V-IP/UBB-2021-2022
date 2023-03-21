from Testare.teste import Teste
from Infrastructura.repozitorii import FileRepoLoc
from Business.servicii import ServiceLoc
from Prezentare.consola import Consola

repo_locuri = FileRepoLoc("locuri.txt")

srv_locuri = ServiceLoc(repo_locuri)

consola = Consola(srv_locuri)

teste = Teste()
teste.ruleaza_teste()

#consola.run()

class MyInt(object):
    def __init__(self,n):
        self.__n = n
    def __add__(self,nr):
        self.__n += nr
    def getInt(self):
        return self.__n
    
def increm(i):
    i=i+1
    if i.getInt()>=3: raise ValueError()
    
i=MyInt(1)
try:
    print(i.getInt())
    increm(i)
    print(i.getInt())
    increm(i)
    print(i.getInt())
    increm(i)
except ValueError:
    print(9)