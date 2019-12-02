Invalid cases
test_char_before_quoted_column			(should return invalid)
test_empty_header_quoted_column
test_name_inquotes       			(should return invalid)
test_header_quoted_duplicate
test_missing_pair_quotations
test_name_quotations.csv
test_comma_seperator_1       			
test_non_csv 		     			(should print out no name found)
test_comma_seperator_2       			
test_comma_seperator_3       			
test_quoted_header_nonquoted_column
test_duplicate_name_header  
test_quoted_header_nonquoted_column_2
testEmpty.csv                			(should print out no name found)
test_quoted_header_spaced_column

Valid cases
successful_case_1 				(should succeed)
test_nonquoted_header_oneQuote_midColumn
'test_empty_quotes_header ' 			(should succeed)
maxTweet  
test_spaces_before_after_quotation		(works but should not display the number of tweets of an empty token)


1. Check for number of commas in each column to match the number of header commas
2. check for header consistency in columns. If a header starts with quotes at the beginning and
 end of the header name then the rest of the columns should contain a pair quotes at index 0 and last index of token
ex: "name"
    "chelsea"
		index 0 and last index should contain quotes 
    "name"
    "chel"sea" is also valid


3. Strip away outer most quotes
4. should check to see if name column exists in empty file before processing to next lines


