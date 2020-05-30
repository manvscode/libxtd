

char* string_csv_parse_r( char* str, const char* delims, char string_escape, char** saveptr )
{
	char* p = NULL;
	char* ret = NULL;
	const char escape_chars[] = { string_escape };

	if( str != NULL )
	{
		*saveptr = str;
	}

	if( *saveptr == NULL )
	{
		return NULL;
	}


	return ret;
}
