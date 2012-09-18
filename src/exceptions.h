#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_
#ifdef __cplusplus
extern "C" {
#endif 

#include <setjmp.h>


#define NO_EXCEPTION         0

struct exception;
typedef struct exception* exception_t;

exception_t  exception_create       ( void );
void         exception_destroy      ( exception_t *p_ex );
unsigned int exception_code         ( const exception_t ex );
void         exception_set_code     ( exception_t ex, unsigned int code );
const char*  exception_filename     ( const exception_t ex );
void         exception_set_filename ( exception_t ex, const char* filename );
unsigned int exception_line         ( const exception_t ex );
void         exception_set_line     ( exception_t ex, unsigned int line );
jmp_buf*     exception_state        ( const exception_t ex );
void         exception_throw_ex     ( const exception_t ex, unsigned int error_code, const char* filename, unsigned int line );

#define exception_throw( ex, error_code )   exception_throw_ex( ex, error_code, __FILE__, __LINE__ )
#define exception_try( ex ) \
	jmp_buf *p_state = exception_state( ex ); \
	exception_set_code( ex, setjmp(*p_state) ); \
	if( exception_code(ex) == NO_EXCEPTION ) 
#define exception_catch( ex, error_code ) else if( exception_code(ex) == error_code )


/*
exception_try( &ex )
{
	foo( );
}
exception_catch( &ex, HG_MEMORY_ALLOC_FAILED )
{
	reset_foo( );
}
exception_catch( &ex, HG_BUFFER_OVERRUN )
{
	kill_foo( );
	exit( );
}
FINALLY
{
	restart( );
}


int __error_code = setjmp( __exception ); 
if( __error_code ) {
	foo( );	
}
else if( __error_code == HG_MEMORY_ALLOC_FAILED ) {
	reset_foo( );
}
else if( __error_code == HG_BUFFER_OVERRUN ) {
	kill_foo( );
	exit( );
}
{
	restart( );
}
*/

#ifdef __cplusplus
}
#endif 
#endif /* _EXCEPTIONS_H_ */
