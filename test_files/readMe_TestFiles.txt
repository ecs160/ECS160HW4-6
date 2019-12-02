Invalid cases
maxTweeter test_char_before_quoted_column 		(now is invalid)		
maxTweeter test_name_inquotes       			(throws an error for the wrong reason)		
maxTweeter test_name_inQuotes  				
maxTweeter test_header_quoted_duplicate
maxTweeter test_missing_pair_quotations
maxTweeter test_comma_seperator_1       			
maxTweeter test_non_csv 		     		
maxTweeter test_comma_seperator_2  				
maxTweeter test_comma_seperator_3       			
maxTweeter test_duplicate_name_header  			
maxTweeter test_quoted_header_nonquoted_column_2	
maxTweeter testEmpty.csv                		
maxTweeter test_quoted_header_spaced_column		
maxTweeter 'test_empty_quotes_header '
maxTweeter test_empty_header_quoted_column
maxTweeter test_name_quotations.csv			
maxTweeter test_quoted_header_nonquoted_column

---------------------------------------------------------------------------------------------------------------------------
Valid cases
maxTweeter successful_case_1 				
maxTweeter test_nonquoted_header_oneQuote_midColumn
maxTweeter maxTweet  
maxTweeter test_spaces_before_after_quotation		

---------------------------------------------------------------------------------------------------------------------------
//DONE	1. Check for number of commas in each column to match the number of header commas	
---------------------------------------------------------------------------------------------------------------------------

//DONE	
test_quoted_header_nonquoted_column_2, successful_case_1
all have the same root problem of which is we need to check for quotation consistency of all the columns not just name column

2. check for header consistency in columns. If a header starts with quotes at the beginning and
 end of the header name then the rest of the columns should contain a pair quotes at index 0 and last index of token
ex: "name"
    "chelsea"
		index 0 and last index should contain quotes 
    "name"
    "chel"sea" is also valid

---------------------------------------------------------------------------------------------------------------------------
//DONE? 3. Strip away outer most quotes
---------------------------------------------------------------------------------------------------------------------------
//DONE 4. should check to see if name column exists in empty file before processing to next lines
---------------------------------------------------------------------------------------------------------------------------
//DONE 5. Change all the error messages to invalid Input before turning in 
---------------------------------------------------------------------------------------------------------------------------
Run fuzz testing for at least an hour or two prior to turning in 
REMOVE test_files from github repo prior to turning in 
Make the repo public and share it like specifications
