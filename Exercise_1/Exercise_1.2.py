import time

n = input('Fibnumber: ')
if not n.isdigit():
    print('Not a digit, quitting')
    quit()
elif int(n) <= 0:
    print('0 or less is not permitted')
    quit()
else:
    n = int(n)

def fib_sequence(n):
    if n == 1 or n == 2:
        return 1
    else:
        return fib_sequence(n - 2) + fib_sequence(n - 1)

def fib_sequence_fast(n):
    if n == 1 or n == 2:
        return 1
    n1 = 1
    n2 = 1
    n3 = 0
    for i in range(2, n):
        n3 = n2 + n1
        n1 = n2
        n2 = n3
    return n3

start_time = time.time()
found = fib_sequence(n)
stop_time = time.time()
print(f'It took {round(stop_time - start_time, 4)} seconds to run it')
print(found)

start_time = time.clock() # PS: time.time() is not precise enough for very fast code snippets
found = fib_sequence_fast(n)
stop_time = time.clock()
elapsed_time = (stop_time - start_time) * 1000 # time.clock() counts ms 
print('It took {:.4E} seconds to run it with the fast algortithm'.format(stop_time - start_time))
print(found)

