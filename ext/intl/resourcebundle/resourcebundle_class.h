/*
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Authors: Hans-Peter Oeri (University of St.Gallen) <hp@oeri.ch>      |
   +----------------------------------------------------------------------+
 */

#ifndef RESOURCEBUNDLE_CLASS_H
#define RESOURCEBUNDLE_CLASS_H

#include <unicode/ures.h>

#include <zend.h>
#include "php.h"

#include "intl_error.h"

typedef struct {
	intl_error      error;

	UResourceBundle *me;
	UResourceBundle *child;
	zend_object     zend;
} ResourceBundle_object;

static inline ResourceBundle_object *php_intl_resourcebundle_fetch_object(zend_object *obj) {
	return (ResourceBundle_object *)((char*)(obj) - XtOffsetOf(ResourceBundle_object, zend));
}
#define Z_INTL_RESOURCEBUNDLE_P(zv) php_intl_resourcebundle_fetch_object(Z_OBJ_P(zv))

#define RESOURCEBUNDLE_METHOD_INIT_VARS		INTL_METHOD_INIT_VARS(ResourceBundle, rb)
#define RESOURCEBUNDLE_METHOD_FETCH_OBJECT_NO_CHECK	INTL_METHOD_FETCH_OBJECT(INTL_RESOURCEBUNDLE, rb)
#define RESOURCEBUNDLE_METHOD_FETCH_OBJECT							\
	INTL_METHOD_FETCH_OBJECT(INTL_RESOURCEBUNDLE, rb);					\
	if (RESOURCEBUNDLE_OBJECT(rb) == NULL) {						\
		intl_errors_set(&rb->error, U_ILLEGAL_ARGUMENT_ERROR,		\
				"Found unconstructed ResourceBundle", 0);	\
		RETURN_FALSE;												\
	}


#define RESOURCEBUNDLE_OBJECT(rb)			(rb)->me

void resourcebundle_register_class( void );
extern zend_class_entry *ResourceBundle_ce_ptr;

PHP_FUNCTION( resourcebundle_create );
PHP_FUNCTION( resourcebundle_get );
PHP_FUNCTION( resourcebundle_count );
PHP_FUNCTION( resourcebundle_locales );
PHP_FUNCTION( resourcebundle_get_error_code );
PHP_FUNCTION( resourcebundle_get_error_message );

#endif // #ifndef RESOURCEBUNDLE_CLASS_H
