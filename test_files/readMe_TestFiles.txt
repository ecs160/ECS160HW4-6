Invalid cases
maxTweeter test_char_before_quoted_column		(should return invalid)
maxTweeter test_name_inquotes       			(should return invalid)
maxTweeter test_name_inQuotes  				(should return invalid)
maxTweeter test_header_quoted_duplicate
maxTweeter test_missing_pair_quotations
maxTweeter test_comma_seperator_1       			
maxTweeter test_non_csv 		     		(should print out no name found)
maxTweeter test_comma_seperator_2       			
maxTweeter test_comma_seperator_3       			
maxTweeter test_duplicate_name_header  
maxTweeter test_quoted_header_nonquoted_column_2
testEmpty.csv                				(should print out no name found)
maxTweeter test_quoted_header_spaced_column		(should print out invalid)

---------------------------------------------------------------------------------------------------------------------------
Valid cases
maxTweeter successful_case_1 				(should succeed)
maxTweeter test_nonquoted_header_oneQuote_midColumn
maxTweeter 'test_empty_quotes_header ' 			(should succeed)
maxTweeter maxTweet  
maxTweeter test_spaces_before_after_quotation		(works but should not display the number of tweets of an empty token)
maxTweeter test_empty_header_quoted_column
maxTweeter test_name_quotations.csv			(works but should strip away the outermost quotes when displaying)
maxTweeter test_quoted_header_nonquoted_column


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


