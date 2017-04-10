package main

// os pacotes 
import (
	"fmt"
	"runtime"
	"sync"
	"io/ioutil"
	"os"
	"strconv"
)

func naive(txt string, pat string) int{
	size_txt := len(txt)
	size_pat := len(pat)
	end := 0
	diff := size_txt - size_pat
	i := 0
	for i = 0; i <= diff; i++{
		var j int
		j = 0
		for j < size_pat{
			if txt[i+j] != pat[j]{
				break;
			}
			j++
		} 
		if j == size_pat{
			end++;
		}
	}
	return end
}

func selectPattern(i int)(pat string){
	switch{
		case i == 6:
			return "DIRECTLY TO"
		case i == 7:
			return "GAAACAAAAACAACAAA"
		case i == 8:
			return "TATATAT"
		case i == 9:
			return "TGTAAA"
		case i == 19:
			return "GAT"
		case i == 20:
			return "CTATTTATAG"
		case i == 21:
			return "GGTCAAAGGTCA"
		case i == 22:
			return "ACTATA"
		case i == 23:
			return "GTATAT"
		case i == 24:
			return "HUEHUEAAG"
			break;
		case i == 25:
			return "HUEAAAAG"
			break;
		case i == 26:
			return "HUEHUEAG"
			break;
	}

	return ""
}

func handleArgs(argv []string) ( cores int, n int, pattern_i int){

	cores,_ = strconv.Atoi(argv[1])				// number of cores to be used
	n,_ = strconv.Atoi(argv[2])					// number of goroutines to be used 
	pattern_i,_ = strconv.Atoi(argv[3])			// pattern to search
	
	return cores, n, pattern_i
}

func parallelization(cores int, n int, pattern_i int)(){

	runtime.GOMAXPROCS(cores)				// set the available cores to cores
	max_goroutines := cores * n 			// set maximum goroutines to be executed 
											// each core will have maximum goroutines workload p/ core

	file, _ := ioutil.ReadFile("colossal.fa");		// open file
	str_file := string(file)		

	pattern := selectPattern(pattern_i)		// pattern to find

	pat_size:= len(pattern)					// size of pattern 
	total := 0								// number of ocurrences

	limit :=  int((len(str_file)) / (max_goroutines))	// divide the text into equal chunks
	index := 0											// index of first chunk
	end := limit										// end of chunck

	var wg sync.WaitGroup	
	wg.Add(max_goroutines)					// wait group

											// goroutines start
	for i:= 0; i < max_goroutines; i++{

		go func(msg string,i int){			// goroutine

			defer wg.Done()				
			var n int;
			n = naive(msg,pattern);			// search pattern
			total = total + n				// increment total 

		}(string(str_file[index:end]),i)

		index = (end - pat_size) + 1		// starting point of next chunk
		end = end + limit					// ending point of next chunk
	}
	
	wg.Wait()								// wait for goroutines to finish
	fmt.Printf("Number of occurences for \"%s\": %d\n", selectPattern(pattern_i), total)
}

func main(){

	n_cores, n, pattern_i := handleArgs(os.Args)
	parallelization(n_cores,n,pattern_i)

}