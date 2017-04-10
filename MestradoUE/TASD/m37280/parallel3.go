package main

// os pacotes 
import (
	"fmt"
	"runtime"
	"sync"
//	"time"
	"io/ioutil"
	"os"
	"strconv"
//	"mmap"	
)

func naive(txt string, pat string) int{
	size_txt := len(txt)
	size_pat := len(pat)
	end := 0
	diff := size_txt - size_pat

	for i:= 0; i <= diff; i++{
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
		case i == 10:
			return "CATAAA"
		case i == 11:
			return "TCTAAA"
		case i == 12:
			return "TATACA"
		case i == 13:
			return "GATAAA"
		case i == 14:
			return "TATGAA"
		case i == 15:
			return "TATCAA"
		case i == 16:
			return "TATAGATATAGA"
		case i == 17:
			return "TATAAG"
		case i == 18:
			return "TATAAC"
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

	}

	return ""
}

func handleArgs(argv []string) ( cores int,work int,pattern_i int){

	cores,_ = strconv.Atoi(argv[1])					// number of cores to be used
	work,_ = strconv.Atoi(argv[2])					// total workload
	pattern_i,_ = strconv.Atoi(argv[3])				// pattern
	return cores,work,pattern_i
}

func parallelization(cores int, workload int, pattern int)(){

	runtime.GOMAXPROCS(cores)		// maximum amount of cores to be used (limited to number of virtual cores in machine)
									// 8 is maximum 

	file, _ := ioutil.ReadFile("FINAL_MIX_FOR_REAL.fa");	// open file
	str_file := string(file)		
	
	pat := selectPattern(pattern)
	limit :=  int((len(str_file)) / (workload))			// divide the text into equal chunks
	index := 0											// index of first chunk
	end := limit										// end of chunck
	total := 0											// number of occurrences
	var wg sync.WaitGroup				
	wg.Add(workload)					// waitgroup

	// goroutines start
	
	for i:= 0; i < workload; i++{

		go func(msg string){			// goroutine
			defer wg.Done()	
			var n int			
			n = naive(msg,pat);		// search pattern
			total = total + n
		}(string(str_file[index:end]))

		index = (end) + 1					// starting point of next chunk
		end = end + limit					// ending point of next chunk
	}
	
	wg.Wait()			// wait for goroutines to finish

	fmt.Printf("Number of occurences for \"%s\": %d\n", pat, total)

}

func main(){

	n_cores,work,pattern_i := handleArgs(os.Args)
	parallelization(n_cores,work,pattern_i)

}
