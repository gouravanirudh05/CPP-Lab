from math import log2
from colorama import Fore, Style
import pandas as pd
import matplotlib.pyplot as plt

tracefiles = ['gcc.trace', 'gzip.trace', 'mcf.trace', 'swim.trace', 'twolf.trace'] 

class Cache:
    def __init__(self, cache_size: int, block_size: int, associativity: int):
        self.cache_size = cache_size
        self.block_size = block_size
        self.associativity = associativity
        self.sets = cache_size//(block_size*associativity)
        self.no_of_ind_bits = int(log2(self.sets))
        self.no_of_offset_bits = int(log2(self.block_size))
        self.no_of_tag_bits = 32 - self.no_of_ind_bits - self.no_of_offset_bits
        self.hit_count = 0
        self.miss_count = 0
        self.cache = [[Block('0'*self.no_of_tag_bits, False) for i in range(self.associativity)] for j in range(self.sets)]

    def check(self, address: str):
        'Used to check if the address given by the processor is present in the cache.'  
        index = self.extract_index(address)
        tag = self.extract_tag(address)
        offset = self.extract_offset(address)
        for block in self.cache[index]:
            if block.tag == tag and block.valid:
                self.hit_count += 1
                self.lru_handling(index, True, block.lru_counter)
                return True
        self.miss_count += 1
        self.evictor(index, tag, offset)
        self.lru_handling(index, False)
        return False

    def extract_index(self, address: str):
        index_bits = address[self.no_of_tag_bits: self.no_of_tag_bits + self.no_of_ind_bits]
        return int(index_bits, 2)

    def extract_tag(self, address: str):
        tag_bits = address[:self.no_of_tag_bits]
        return tag_bits

    def extract_offset(self, address: str):
        offset_bits = address[-self.no_of_offset_bits:]
        return int(offset_bits, 2)

    def lru_handling(self, set_index: int, hit: bool, cur: int=None):
        if hit:
            for block in self.cache[set_index]:
                if block.lru_counter > cur:
                    block.lru_counter -= 1
                elif block.lru_counter == cur:
                    block.lru_counter = self.associativity - 1
        else:
            for block in self.cache[set_index]:
                block.lru_counter -= 1

    def evictor(self, set_index: int, tag: str, offset: str):
        for block in self.cache[set_index]:
            if not block.valid:
                block.tag = tag
                block.valid = True
                block.lru_counter = self.associativity
                return 
        for block in self.cache[set_index]:
            if block.lru_counter == 0:
                block.tag = tag
                block.valid = True
                block.lru_counter = self.associativity
                return

class Block:
    def __init__(self, tag: str, valid: bool, lru_counter: int=-1):
        self.tag = tag
        self.valid = valid
        self.data = "0"*32
        self.lru_counter = lru_counter

def plot(x_label, y_label,title, dfs):

    for i, df in enumerate(dfs):
        plt.plot(df[x_label], df[y_label], label = tracefiles[i])

    plt.xlabel(x_label)
    plt.ylabel(y_label)
    plt.title(title)
    plt.legend()
    plt.show()

def hextobin(address):
    """ Convert hexadecimal address to a 32-bit binary string """
    num=str(bin(int(address,base=16)))
    num=num[2:]
    return num.zfill(32)

def parta():
    cache_size = 1024 * 1024  
    block_size = 4  
    associativity = 4  
    for tracefile in tracefiles:
        cache1 = Cache(cache_size, block_size, associativity)
        with open(tracefile, 'r') as file:
            for line in file:
                address_hex = line.split()[1][2:]
                address_bin = hextobin(address_hex)
                cache1.check(address_bin)
        hit_rate = cache1.hit_count / (cache1.hit_count + cache1.miss_count)
        miss_rate = cache1.miss_count / (cache1.hit_count + cache1.miss_count)
        print(f'Hit Rate for {tracefile}: {hit_rate * 100:.6f}%')
        print(f'Miss Rate for {tracefile}: {miss_rate * 100:.6f}%')
        print()

def partb():
    dfs = []
    cache_sizes = [1024 * 2 ** i for i in range(7, 12 + 1)]
    cache_sizes_kb = [i//1024 for i in cache_sizes]

    for tracefile in tracefiles:
        hit_rates = []
        miss_rates = []
        hit_counts = []
        miss_counts = []
        for cache_size in cache_sizes:
            cache1 = Cache(cache_size, 4, 4)
            with open(tracefile, 'r') as file:
                for line in file:
                    address_hex = line.split()[1][2:]
                    address_bin = hextobin(address_hex)
                    cache1.check(address_bin)

            hit_rates.append(cache1.hit_count / (cache1.hit_count + cache1.miss_count))
            miss_rates.append(cache1.miss_count / (cache1.hit_count + cache1.miss_count))
            hit_counts.append(cache1.hit_count)
            miss_counts.append(cache1.miss_count)

        df = pd.DataFrame({'Cache Size (in kb)': cache_sizes_kb, 'Hit count': hit_counts, 'Miss count': miss_counts, 'Hit Rate': hit_rates, 'Miss Rate': miss_rates})
#        df.set_index('Cache Size (in kb)', inplace=True)

        print(tracefile)
        print()
        print(df)
        print()
        dfs.append(df)

    plot('Cache Size (in kb)', 'Miss Rate',"Cache Size vs Miss Rate",dfs)

def partc():
    dfs=[]
    cache_size = 1024 * 1024
    block_sizes = [2 ** i for i in range(0, 7 + 1)]
    for tracefile in tracefiles:
        hit_rates = []
        miss_rates = []
        hit_counts = []
        miss_counts = []
        for block_size in block_sizes:
            cache1 = Cache(cache_size, block_size, 4)
            with open(tracefile, 'r') as file:
                for line in file:
                    address_hex = line.split()[1][2:]
                    address_bin = hextobin(address_hex)
                    cache1.check(address_bin)

            hit_rates.append(cache1.hit_count / (cache1.hit_count + cache1.miss_count))
            miss_rates.append(cache1.miss_count / (cache1.hit_count + cache1.miss_count))
            hit_counts.append(cache1.hit_count)
            miss_counts.append(cache1.miss_count)

        df = pd.DataFrame({'Block Size': block_sizes, 'Hit count': hit_counts, 'Miss count': miss_counts, 'Hit Rate': hit_rates, 'Miss Rate': miss_rates})
#        df.set_index('Block Size', inplace=True)
        print(tracefile)
        print()
        print(df)
        print()
        dfs.append(df)

    plot('Block Size', 'Miss Rate','Block Size vs Miss Rate', dfs)

def partd():
    dfs = []
    cache_size = 1024 * 1024
    block_size = 4
    associativities = [2 ** i for i in range(0, 6 + 1)]
    for tracefile in tracefiles:
        hit_rates = []
        miss_rates = []
        hit_counts = []
        miss_counts = []
        for associativity in associativities:
            cache1 = Cache(cache_size, block_size, associativity)
            with open(tracefile, 'r') as file:
                for line in file:
                    address_hex = line.split()[1][2:]
                    address_bin = hextobin(address_hex)
                    cache1.check(address_bin)

            hit_rates.append(cache1.hit_count / (cache1.hit_count + cache1.miss_count))
            miss_rates.append(cache1.miss_count / (cache1.hit_count + cache1.miss_count))
            hit_counts.append(cache1.hit_count)
            miss_counts.append(cache1.miss_count)

        df = pd.DataFrame({'Associativity': associativities, 'Hit count': hit_counts, 'Miss count': miss_counts, 'Hit Rate': hit_rates, 'Miss Rate': miss_rates})
#        df.set_index('Associativity', inplace=True)

        print(tracefile)
        print()
        print(df)
        print()
        dfs.append(df)

    plot('Associativity', 'Hit Rate','Associativity vs Hit Rate', dfs)
        

def main():
    print("Cache Simulation")
    while(True):
        print(Fore.GREEN + "Options:\n1. Part A\n2. Part B\n3. Part C\n4. Part D\n-1. Exit" + Style.RESET_ALL)
        choice = input(Fore.RED + "Please enter your choice: " + Style.RESET_ALL)
        match choice:
            case '1':
                parta()
            case '2':
                partb()
            case '3':
                partc()
            case '4':
                partd()
            case '-1':
                print("Exiting...")
                exit(0)
            case _:
                print("Invalid choice. Please try again.")

if __name__ == "__main__":
    main()