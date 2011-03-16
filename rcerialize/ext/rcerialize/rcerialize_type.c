/*
 *		Rbdb::Serialize
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "rcerialize/rcerialize_type.h"

/*******************************************************************************************************************************************************************************************
																		Ruby Definitions
*******************************************************************************************************************************************************************************************/

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*******************************************************************************************************************************************************************************************
																		Type Methods
*******************************************************************************************************************************************************************************************/

/*******************************
*  storageTypeForRubyInstance  *
*******************************/

CerializeType Rcerialize_storageTypeForRubyInstance(	VALUE		rb_object )	{
	
	enum ruby_value_type		c_ruby_type	=	TYPE( rb_object );
	
	CerializeType	c_type	=	CerializeType_Raw;
	
	switch ( c_ruby_type )	{

		case T_FILE:
			c_type	=	CerializeType_FileContents;
			break;

		case T_SYMBOL:
			c_type	=	CerializeType_Symbol;
			break;

		case T_REGEXP:
			c_type	=	CerializeType_Regexp;
			break;

		case T_CLASS:
			c_type	=	CerializeType_ClassName;
			break;

		case T_STRING:
			c_type	=	CerializeType_String;
			break;

		case T_COMPLEX:
			c_type	=	CerializeType_Complex;
			break;

		case T_RATIONAL:
			c_type	=	CerializeType_Rational;
			break;
			
		case T_BIGNUM:
		case T_FIXNUM:
			c_type	=	CerializeType_Integer;
			break;
			
		case T_FLOAT:
			c_type	=	CerializeType_Float;
			break;
			
		case T_TRUE:
		case T_FALSE:
			c_type	=	CerializeType_TrueFalse;
			break;
			
		case T_ARRAY:
			c_type	=	CerializeType_Array;
			break;

		case T_HASH:
			c_type	=	CerializeType_Hash;
			break;

		case T_STRUCT:
			c_type	=	CerializeType_Struct;
			break;
    
    case T_NIL:
      c_type  = CerializeType_Nil;
      break;

		case T_OBJECT:
		case T_MODULE:
		case T_DATA:
		default:
			rb_raise( rb_eArgError, "Provided data was invalid." );
			break;
	}
	
	return c_type;
}

/****************************
*  storageTypeForRubyClass  *
****************************/

CerializeType Rcerialize_storageTypeForRubyClass( VALUE rb_class )	{

	CerializeType	c_type	=	CerializeType_Raw;
	
	if (			rb_class == rb_cFile )	{
		c_type	=	CerializeType_FileContents;	
	}
	else if ( rb_class == rb_cSymbol )	{
		c_type	=	CerializeType_Symbol;
	}
	else if ( rb_class == rb_cRegexp )	{
		c_type	=	CerializeType_Regexp;
	}
	else if ( rb_class == rb_cClass )	{
		c_type	=	CerializeType_ClassName;
	}
	else if ( rb_class == rb_cString )	{
		c_type	=	CerializeType_String;
	}
	else if ( rb_class == rb_cInteger )	{
		c_type	=	CerializeType_Integer;
	}
	else if ( rb_class == rb_cFloat )	{
		c_type	=	CerializeType_Float;
	}
	else if ( rb_class == rb_cComplex )	{
		c_type	=	CerializeType_Complex;
	}
	else if ( rb_class == rb_cRational )	{
		c_type	=	CerializeType_Rational;
	}
	else if (	rb_class == rb_cTrueClass
				||	rb_class == rb_cFalseClass )	{
		c_type	=	CerializeType_TrueFalse;
	}
	else if ( rb_class == rb_cArray )	{
		c_type	=	CerializeType_Array;
	}
	else if ( rb_class == rb_cHash )	{
		c_type	=	CerializeType_Hash;
	}
	else if (		rb_class == rb_cStruct
					||	rb_ary_includes(	rb_mod_ancestors( rb_class ),
																rb_cStruct ) )	{
		c_type	=	CerializeType_Struct;
	}
	else {
		rb_raise( rb_eArgError, "Provided data was invalid." );		
	}

	return c_type;
}

