#ifndef _UTILITY_H_
#define _UTILITY_H_
#ifdef __cplusplus
extern "C" {
#endif 

#include <stdlib.h>


typedef enum random_string_type {
	RAND_STRING_ALPHA_NUMERIC = 0,
	RAND_STRING_ALPHA,
	RAND_STRING_HEX,
	RAND_STRING_NUMERIC,
	RAND_STRING_NO_ZERO,
	RAND_STRING_DISTINCT,
} random_string_type_t;

void        crash              ( void );
void        scramble_string    ( const char* key, char* string, size_t len, unsigned short pivot );
void        unscramble_string  ( const char* key, char* string, size_t len, unsigned short pivot );
void        random_string      ( random_string_type_t type, char* string, size_t length );
const char* ordinal_string     ( long number );
void        xor_bytes          ( const void* a, size_t a_size, const void* b, size_t b_size, void* result );
void        swap               ( void* left, void *right, size_t size );

/*
 * File IO
 */
int         file_exists        ( const char *path );
int         file_is_writeable  ( const char *path );
int         file_is_readable   ( const char *path );
int         file_is_executable ( const char *path );
int         file_copy          ( const char *src_path, const char *dst_path );
int         file_delete        ( const char *path );
long        file_size          ( const char *path );
int         file_age           ( const char *path ); // Returns -1 on error 
int         is_file            ( const char *path );
int         is_dir             ( const char *path );

#ifdef __cplusplus
}
#endif 
#endif /* _UTILITY_H_ */
