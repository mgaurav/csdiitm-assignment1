#----------------------------------------------------------------------
# Executabel file a.out should be in current directory
#----------------------------------------------------------------------
import os

associativity = 4
cache_size = 2048
block_size = 16
data_size = 4
matrix_size = 100

# Experiment : Vary Associativity, keep all other parameters fixed
os.system('echo "Associativity Hit-rate" >> expt_assoc.txt')
j = 1
while j <= 32:
    os.system('echo "' + str(j) + ' " >> expt_assoc.txt')
    os.system('./a.out ' + str(j) + ' ' + str(block_size) + ' ' +
              str(cache_size) + ' ' + str(data_size) + ' ' +
              str(matrix_size) + ' ' + str(matrix_size) + ' ' +
              str(matrix_size) + ' >> expt_assoc.txt')
    j *= 2

j = 128
os.system('echo "' + str(j) + ' " >> expt_assoc.txt')
os.system('./a.out ' + str(j) + ' ' + str(block_size) + ' ' +
              str(cache_size) + ' ' + str(data_size) + ' ' +
              str(matrix_size) + ' ' + str(matrix_size) + ' ' +
              str(matrix_size) + ' >> expt_assoc.txt')
os.system('echo "expt-1 completed"')

# Experiment : Vary Cache size, keep all other parameters fixed
os.system('echo "Cache-size Hit-rate" >> expt_cache_size.txt')
j = 128
while j <= 16384:
    os.system('echo "' + str(j) + ' " >> expt_cache_size.txt')    
    os.system('./a.out ' + str(associativity) + ' ' + str(block_size) + ' ' +
              str(j) + ' ' + str(data_size) + ' ' +
              str(matrix_size) + ' ' + str(matrix_size) + ' ' +
              str(matrix_size) + ' >> expt_cache_size.txt')
    j *= 2
os.system('echo "expt-2 completed"')

# Experiment : Vary Block size, keep all other parameters fixed
os.system('echo "Block-size Hit-rate" >> expt_block_size.txt')
j = 4
while j <= 128:
    os.system('echo "' + str(j) + ' " >> expt_block_size.txt')
    os.system('./a.out ' + str(associativity) + ' ' + str(j) + ' ' +
              str(cache_size) + ' ' + str(data_size) + ' ' +
              str(matrix_size) + ' ' + str(matrix_size) + ' ' +
              str(matrix_size) + ' >> expt_block_size.txt')
    j *= 2
os.system('echo "expt-3 completed"')

# Experiment : Vary Matrix size, keep all other parameters fixed
os.system('echo "Matrix Hit-rate" >> expt_matrix_size.txt')
j = 10
while j <= 100:
    os.system('echo "' + str(j) + ' " >> expt_matrix_size.txt')
    os.system('./a.out ' + str(associativity) + ' ' + str(block_size) + ' ' +
              str(cache_size) + ' ' + str(data_size) + ' ' +
              str(j) + ' ' + str(j) + ' ' +
              str(j) + ' >> expt_matrix_size.txt')
    j += 10
os.system('echo "expt-4 completed"')
