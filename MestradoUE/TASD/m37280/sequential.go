package main

import (
	"fmt"

	"io/ioutil"
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
		case i == 8:
			return "TATATAT"
		case i == 9:
			return "TGTAAA"
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
	}

	return ""
}

func sequential(){

	file, _ := ioutil.ReadFile("colossal.fa");		// open file
	str_file := string(file)	

	pattern := selectPattern(19)				// pattern to find
	total := naive(str_file,pattern);			// search pattern

	fmt.Printf("Number of occurences for \"%s\": %d\n", pattern, total)
}

func main(){
	sequential()

}
