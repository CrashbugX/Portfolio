# Made by Diego Ceballos Garza for Sunwise

# Exercise 1
# Starting at the top left corner of an N x M grid and facing towards the right, you
# keep walking one square at a time in the direction you are facing. If you reach the
# boundary of the grid or if the next square you are about to visit has already been
# visited, you turn right. You stop when all the squares in the grid have been visited.
# What direction will you be facing when you stop? For example: Consider the case with
# N = 3, M = 3. The path followed will be (0,0) -> (0,1) -> (0,2) -> (1,2) -> (2,2) ->
# (2,1) -> (2,0) -> (1,0) -> (1,1). At this point, all squares have been visited, and
# you are facing right.

#TEST PROGRAM

#print('Define the dimensions N and M of the grid.')
#n = input('Enter the value for N: ')
#m = input('Enter the value for M: ')
#print('Grid size: ' + n + ' x ' + m)
#res = 'X'
#if(n>m):
#    if((int(m) % 2) == 1):
#        res = 'D'
#    else:
#        res = 'U'
#else:
#    if((int(n)%2) == 1):
#        res = 'R'
#    else:
#        res = 'L'
#print('Final direction is: ' + res)

dat = []
res = []
#print('T Value:')
T = int(input())
for i in range(0, T):
    #print(str(i+1) + ' value:'
    temp = input()
    dat.append(temp)
for i in range(0,T):
    val = dat[i].split()
    n = val[0]
    m = val[1]
    if(n>m):
        if(int(m)%2 == 1):
            temp = 'D'
        else:
            temp = 'U'
    else:
        if(int(n)%2 == 1):
            temp = 'R'
        else:
            temp = 'L'
    res.append(temp)
for i in range(0,T):
    print(res[i])
