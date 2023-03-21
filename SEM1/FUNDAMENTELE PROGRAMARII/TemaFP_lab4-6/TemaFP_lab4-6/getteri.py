def obtine_ziuaData(zi):
    '''
    Functie care determina ziua unei date calendaristice
    input: zi - data calendaristica
    output: zi - int, ziua tranzactiei
    '''
    return zi["zi"]

def obtine_lunaData(zi):
    '''
    Functie care determina luna unei date calendaristice
    input: zi - data calendaristica
    output: luna - int, luna tranzactiei
    '''
    return zi["luna"]

def obtine_anData(zi):
    '''
    Functie care determina anul unei date calendaristice
    input: zi - data calendaristica
    output: an - int, anul tranzactiei
    '''
    return zi["an"]

def obtine_zi(tnz):
    '''
    Functie care determina ziua unei tranzactii
    input: tnz - o tranzactie
    output: zi - data calendaristica, data tranzactiei
    '''
    return tnz["zi"]

def obtine_suma(tnz):
    '''
    Functie care determina ziua unei tranzactii
    input: tnz - o tranzactie
    output: suma - un intreg, suma tranzactiei
    '''
    return tnz["suma"]

def obtine_tipul(tnz):
    '''
    Functie care determina ziua unei tranzactii
    input: tnz - o tranzactie
    output: tip - boolean, tipul tranzactiei
    '''
    return tnz["tipul"]