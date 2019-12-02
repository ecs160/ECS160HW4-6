Invalid cases
maxTweeter test_char_before_quoted_column		(should return invalid)
maxTweeter test_name_inquotes       			
maxTweeter test_name_inQuotes  				
maxTweeter test_header_quoted_duplicate
maxTweeter test_missing_pair_quotations
maxTweeter test_comma_seperator_1       			
maxTweeter test_non_csv 		     		(should print out no name found)
maxTweeter test_comma_seperator_2       			
maxTweeter test_comma_seperator_3       			
maxTweeter test_duplicate_name_header  			
maxTweeter test_quoted_header_nonquoted_column_2	(should print invalid)
maxTweeter testEmpty.csv                		(prints out empty line, maybe change the print statement to name col not found)
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
maxTweeter test_spaces_before_after_quotation		(doesn't work anymore, needs to be fixed)



---------------------------------------------------------------------------------------------------------------------------
//DONE	1. Check for number of commas in each column to match the number of header commas				
2. check for header consistency in columns. If a header starts with quotes at the beginning and
 end of the header name then the rest of the columns should contain a pair quotes at index 0 and last index of token
ex: "name"
    "chelsea"
		index 0 and last index should contain quotes 
    "name"
    "chel"sea" is also valid


3. Strip away outer most quotes
4. should check to see if name column exists in empty file before processing to next lines


