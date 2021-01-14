//Kareem Abdelaty
//30075331
#include <unistd.h>
#include <stdio.h>
#include <stdio.h>
#include <ctype.h>
#include <string>
#include <vector>

//define number of bytes 
#define MiB 1048576
std::vector<std::string> res;
// split string p_line into a vector of strings (words)
// the delimiters are 1 or more whitespaces
void
split( const std::string & p_line)
{
  res.clear();
  auto line = p_line + " ";
  bool in_str = false;
  std::string curr_word = "";
  for( auto c : line) {
    if( isspace(c)) {
      if( in_str)
        res.push_back(curr_word);
      in_str = false;
      curr_word = "";
    }
    else {
      curr_word.push_back(c);
      in_str = true;
    }
  }
}

// global variable used in stdin_readline()
//buffer created as an array of chars stored on stack. Buffer size is 1MiB because char size in C++ is 1 byte

char buffer[MiB];
//counter to keep track of how many bytes of the buffer was parsed. used to know when to refresh buffer
size_t i = 0;
//counter to keep track of end of buffer in case file was smaller than buffer
size_t num;

// reads in a line from STDIN
// reads until \n or EOF and result includes \n if present
// returns empty string on EOF
//code assumes that no one line is longer than 1MiB
std::string result;
void
stdin_readline()
{
	result = "";
	//if the full buffer was read reset buffer counter to zero bytes read.
	if(i>=MiB){
		i =0;
	}
	//if counter is zero refresh buffer
	if(i==0){
		//initiate read system call and store number of bytes read
		num = read( STDIN_FILENO, & buffer, MiB);
		//if zero bytes are read return empty string
		if(num <= 0){
			return;
		}
		//otherwise parse through buffer till a line end character is found is found
		while(i<num) {
			if( buffer[i] == '\n'){ 
				result.append(buffer,i);
				i++;
				break;
			}
			i++;
		}

		return;
	} 
	//if counter is in the middle of the buffer
	else{
		//store the starting positon
		size_t start  =i;
		//iterate through buffer till new line is found
		while(i<num) {
			if( buffer[i] == '\n'){ 	
				for(size_t x = start;x<=i;x++)
					result.push_back(buffer[x]);
				i++;
				return;
			}
			i++;
		}
		//if no line is found append unused part of this buffer to result and refresh buffer to continue looking for line end character or eof
		for(size_t x = start;x<i;x++)
			result.push_back(buffer[x]);
		//previously implemented this part with a recursive call to stdin_readline but it was slow so i just copied the code from above.
		i = 0;
		num = read( STDIN_FILENO, & buffer, MiB);
		//if zero bytes are read return empty string
		if(num <= 0){
			return;
		}
		//otherwise parse through buffer till a line end character is found is found
		while(i<num) {
			if( buffer[i] == '\n'){ 
				result.append(buffer,i);
				i++;
				break;
			}
			i++;
		}
		return;
	}

}

// returns true if a word is palindrome
// palindrome is a string that reads the same forward and backward
//    after converting all characters to lower case
bool
is_palindrome( const std::string & s)
{
  for( size_t i = 0 ; i < s.size() / 2 ; i ++)
    if( tolower(s[i]) != tolower(s[s.size()-i-1]))
      return false;
  return true;
}

// returns the longest palindrome on standard input
// in case of ties for length, returns the first palindrome
// all input is broken into words, and each word is checked
// word is a sequence of characters separated by white space
// white space is whatever isspace() says it is
//    i.e. ' ', '\n', '\r', '\t', '\n', '\f'
std::string max_pali;
void
get_longest_palindrome()
{
  while(1) { 
	stdin_readline();
    if(result.size() == 0) break;
	split(result);
    for( auto word : res) {
      if( word.size() <= max_pali.size()) continue;
      if( is_palindrome(word))
        max_pali = word;
    }
  }
	return;
}

int
main()
{
  get_longest_palindrome();
  printf("Longest palindrome: %s\n", max_pali.c_str());
  return 0;
}

