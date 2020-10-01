# Made by Diego Ceballos Garza for Sunwise


# A well-known software development company has been commissioned by the Archaeological
# Society. One of the modules has to help the archaeologists to process data about the
# ruins of buildings they have found during their excavations of ancient cities.
# Development of this module has been assigned to Vasya.
# 
# Vasya, being a seasoned programmer, at once noticed that the module would need a
# database to contain the descriptions of the ruins and the estimated construction
# times of the buildings. It would be all fine, but suddenly the manager got the
# genial idea that since the database describes Roman ruins, the dates of construction
# should be stored in the Roman number system. Now Vasya is wondering how many symbols
# he needs to set aside for each year number field in the database. According to the
# functional specification, the software module must be able to handle dates from A to
# B (inclusive). Help Vasya determine the minimal number of characters sufficient for
# storing any year number in the range from A to B.


#print('Enter date range:')
ran = input()
dates = ran.split('-')
min_chars = 0
for i in range(0,2):
    #Number Processing
    dates[i] = dates[i].strip()
    length = len(dates[i])
    if(dates[i][length-1] == 'C'):
        num = int(dates[i].replace('BC', ''))*-1
    else:
        num = int(dates[i].replace('AD', '')) - 1
    dates[i] = num + 754
for i in range(dates[0], dates[1]+1):
    #print ('Decimal : ' + str(i))
    # Roman Conversion
    roman = ''
    ref = [1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1]
    cha = ['M', 'CM', 'D', 'CD', 'C', 'XC', 'L', 'XL', 'X', 'IX', 'V', 'IV', 'I']
    j = 0
    while (i != 0):
        if(i/ref[j] >= 1):
            roman = roman + cha[j]
            i = i - ref[j]
        else:
            j = j+1
    #print('Roman: ' + roman)
    if (len(roman) > min_chars):
        min_chars = len(roman)
print(min_chars)
    
    #PRINT:
#    print(dates[i])
