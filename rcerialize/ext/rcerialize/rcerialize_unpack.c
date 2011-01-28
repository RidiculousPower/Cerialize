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

#include "RcerializedData_unpack.h"

/*******************************************************************************************************************************************************************************************
																		Ruby Definitions
*******************************************************************************************************************************************************************************************/

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/***********************
*  unpackRubyInstance  *
***********************/

VALUE Rcerialize_unpackRubyInstance(	CerializedData*			c_cerialized_data,
																			VALUE								rb_load_as_class )	{

	VALUE	rb_return	=	Qnil;
	
	switch ( *c_cerialized_data->type )	{

		case CerializeType_FileContents:
		case CerializeType_FilePath:
			rb_return	=	Rcerialize_unpackRubyObjectForFilePath(				c_cerialized_data );
			break;

		case CerializeType_Symbol:
			rb_return	=	Rcerialize_unpackRubyObjectForSymbol(					c_cerialized_data );
			break;

		case CerializeType_Regexp:
			rb_return	=	Rcerialize_unpackRubyObjectForRegexp(					c_cerialized_data );
			break;

		case CerializeType_ClassName:
			rb_return	=	Rcerialize_unpackRubyObjectForClassName(			c_cerialized_data );
			break;

		case CerializeType_Raw:
		case CerializeType_String:
			rb_return	=	Rcerialize_unpackRubyObjectForString(					c_cerialized_data );
			break;

		case CerializeType_Complex:
			rb_return	=	Rcerialize_unpackRubyObjectForComplex(				c_cerialized_data );
			break;

		case CerializeType_Rational:
			rb_return	=	Rcerialize_unpackRubyObjectForRational(				c_cerialized_data );
			break;
			
		case CerializeType_Integer:
			rb_return	=	Rcerialize_unpackRubyObjectForInteger(				c_cerialized_data );
			break;
			
		case CerializeType_Float:
			rb_return	=	Rcerialize_unpackRubyObjectForFloat(					c_cerialized_data );
			break;
			
		case CerializeType_TrueFalse:
			rb_return	=	Rcerialize_unpackRubyObjectForTrueFalse(			c_cerialized_data );
			break;

		case CerializeType_Array:
			rb_return	=	Rcerialize_unpackRubyObjectForArray(					c_cerialized_data );
			break;

		case CerializeType_Hash:
			rb_return	=	Rcerialize_unpackRubyObjectForHash(						c_cerialized_data );
			break;

		case CerializeType_Struct:
			rb_return	=	Rcerialize_unpackRubyObjectForNamedStruct(		c_cerialized_data,
																																rb_load_as_class );
			break;

		case CerializeType_NamedStruct:
			rb_return	=	Rcerialize_unpackRubyObjectForNamedStruct(		c_cerialized_data,
																																rb_load_as_class );
			break;
			
		default:			
			//	unexpected data
			rb_raise( rb_eArgError, "Provided data was invalid." );
			break;
	}
	
	return rb_return;
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Private Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/****************************
*  unpackRubyObjectForFile  *
****************************/

VALUE Rcerialize_unpackRubyObjectForFilePath(	CerializedData*		c_cerialized_file_path )	{

	//	create ruby string from file data
	VALUE	rb_file_contents	=	Rcerialize_unpackRubyObjectForString(	c_cerialized_file_path );
	
	return rb_file_contents;
}

/****************************
*  unpackRubyObjectForFile  *
****************************/

VALUE Rcerialize_unpackRubyObjectForFileContents(	CerializedData*		c_cerialized_file_contents )	{

	//	get file path
	VALUE	rb_file_path	=	Rcerialize_unpackRubyObjectForString(	c_cerialized_file_contents );
	
	//	create file with path
	VALUE	rb_file		=	rb_funcall(	rb_cFile,
																rb_intern( "new" ),
																1,
																rb_file_path );

	return rb_file;
}

/******************************
*  unpackRubyObjectForSymbol  *
******************************/

VALUE Rcerialize_unpackRubyObjectForSymbol(	CerializedData*		c_cerialized_symbol )	{

	VALUE	rb_symbol	=	Qnil;
	VALUE	rb_symbol_as_string	=	Rcerialize_unpackRubyObjectForString(	c_cerialized_symbol );
	
	if ( rb_symbol_as_string != Qnil )	{
		rb_symbol	=	ID2SYM( rb_to_id( rb_symbol_as_string ) );
	}
	
	return rb_symbol;
}

/******************************
*  unpackRubyObjectForRegexp  *
******************************/

VALUE Rcerialize_unpackRubyObjectForRegexp(	CerializedData*		c_cerialized_regexp )	{

	VALUE	rb_regexp	=	Qnil;
	VALUE	rb_regexp_as_string	=	Rcerialize_unpackRubyObjectForString(	c_cerialized_regexp );
	
	if ( rb_regexp_as_string != Qnil )	{
	
		rb_regexp	=	rb_funcall(	rb_cRegexp,
														rb_intern( "new" ),
														1,
														rb_regexp_as_string );
	}
	
	return rb_regexp;
}

/*************************************
*  unpackRubyObjectForClassName  *
*************************************/

VALUE Rcerialize_unpackRubyObjectForClassName(	CerializedData*		c_cerialized_class_name )	{

	VALUE	rb_class	=	Qnil;
	VALUE	rb_class_name	=	Rcerialize_unpackRubyObjectForString(	c_cerialized_class_name );
	
	if ( rb_class_name != Qnil )	{
		rb_class	=	rb_path_to_class( rb_class_name );
	}
	
	return rb_class;
}

/******************************
*  unpackRubyObjectForString  *
******************************/

VALUE Rcerialize_unpackRubyObjectForString(	CerializedData*		c_cerialized_string )	{

	VALUE			rb_string	=	rb_str_new(	c_cerialized_string->data,
																		c_cerialized_string->size );

	return rb_string;
}

/*******************************
*  unpackRubyObjectForComplex  *
*******************************/

VALUE Rcerialize_unpackRubyObjectForComplex(	CerializedData*		c_cerialized_complex )	{

	CerializeStorage_Complex*	c_complex_number	=	(CerializeStorage_Complex*) c_cerialized_complex->data;

	VALUE	rb_complex_number	=	rb_Complex(	DBL2NUM( c_complex_number->real ),
																				DBL2NUM( c_complex_number->imaginary )	);

	return rb_complex_number;
}

/********************************
*  unpackRubyObjectForRational  *
********************************/

VALUE Rcerialize_unpackRubyObjectForRational(	CerializedData*		c_cerialized_rational )	{

	CerializeStorage_Rational*	c_rational_number	=	(CerializeStorage_Rational*) c_cerialized_rational->data;

	VALUE	rb_rational_number	=	rb_Rational(	DBL2NUM( c_rational_number->numerator ),
																						DBL2NUM( c_rational_number->denominator )	);

	return rb_rational_number;
}

/*******************************
*  unpackRubyObjectForInteger  *
*******************************/

VALUE Rcerialize_unpackRubyObjectForInteger(	CerializedData*		c_cerialized_integer )	{

	CerializeStorage_Integer*	c_integer	=	(CerializeStorage_Integer*) c_cerialized_integer->data;

	VALUE	rb_integer	=	LONG2NUM( c_integer->integer_value );

	return rb_integer;
}

/*****************************
*  unpackRubyObjectForFloat  *
*****************************/

VALUE Rcerialize_unpackRubyObjectForFloat(	CerializedData*		c_cerialized_float )	{

	CerializeStorage_Float*	c_float	=	(CerializeStorage_Float*) c_cerialized_float->data;

	VALUE	rb_float	=	LONG2NUM( c_float->float_value );

	return rb_float;
}

/*********************************
*  unpackRubyObjectForTrueFalse  *
*********************************/

VALUE Rcerialize_unpackRubyObjectForTrueFalse(	CerializedData*		c_cerialized_true_false )	{

	CerializeStorage_TrueFalse*	c_true_false	=	(CerializeStorage_TrueFalse*) c_cerialized_true_false->data;

	VALUE	rb_true_false	=	( c_true_false->truefalse	?	Qtrue 
																									:	Qfalse );

	return rb_true_false;
}

/****************************
*  unpackRubyObjectForHash  *
****************************/

VALUE Rcerialize_unpackRubyObjectForHash(	CerializedData*		c_cerialized_hash )	{

	VALUE	rb_return_hash	=	rb_hash_new();
	
	//	<key size><key data><data size><data data>...<type/footer>

	void*				c_raw_data_iterator	=	c_cerialized_hash->data;

	int					c_footer_size	=	0;
	if ( CerializedData_internal_hasDataFooter( c_cerialized_hash ) )	{
		c_footer_size	=	sizeof( CerializedData_DataFooterTypeForVersion( CerializedDataFooterCurrentVersion ) );
	}
	else if ( CerializedData_internal_hasTypeFooter( c_cerialized_hash ) )	{
		c_footer_size	=	sizeof( CerializedTypeFooter );
	}

	//	while we have data remaining, unpack key data pair
	uintptr_t*	c_end_of_iteration	=	c_raw_data_iterator 
																	+ c_cerialized_hash->size 
																	- c_footer_size;
	
	while ( c_raw_data_iterator != c_end_of_iteration )	{
	
		CerializedData	c_cerialized_key;
		
			c_cerialized_key.size		=		*(uint32_t*)c_raw_data_iterator;
			c_raw_data_iterator			+=	sizeof( uint32_t );
			
			c_cerialized_key.data		=		c_raw_data_iterator;
			c_raw_data_iterator			+=	c_cerialized_key.size - sizeof( CerializeType );

			c_cerialized_key.type		=		(CerializeType*)c_raw_data_iterator;
			c_raw_data_iterator			+=	sizeof( CerializeType );

		CerializedData	c_cerialized_data;
	
			c_cerialized_data.size	=		*(uint32_t*)c_raw_data_iterator;
			c_raw_data_iterator			+=	sizeof( uint32_t );
			
			c_cerialized_data.data	=		c_raw_data_iterator;
			c_raw_data_iterator			+=	c_cerialized_data.size - sizeof( CerializeType );

			c_cerialized_data.type	=		(CerializeType*)c_raw_data_iterator;
			c_raw_data_iterator			+=	sizeof( CerializeType );
		
	
		VALUE	rb_key	=	Rcerialize_unpackRubyInstance(	& c_cerialized_key,
																										Qnil );
		VALUE	rb_data	=	Rcerialize_unpackRubyInstance(	& c_cerialized_data,
																										Qnil );
		
		rb_hash_aset(	rb_return_hash,
									rb_key,
									rb_data );
	}
	
	return rb_return_hash;
}

/*****************************
*  unpackRubyObjectForArray  *
*****************************/

VALUE Rcerialize_unpackRubyObjectForArray(	CerializedData*		c_cerialized_array )	{

	VALUE	rb_return_array	=	rb_ary_new();

	//	<key size><key data><data size><data data>...<type/footer>

	void*				c_raw_data_iterator	=	c_cerialized_array->data;

	int					c_footer_size	=	0;
	if ( CerializedData_internal_hasDataFooter( c_cerialized_array ) )	{
		c_footer_size	=	sizeof( CerializedData_DataFooterTypeForVersion( CerializedDataFooterCurrentVersion ) );
	}
	else if ( CerializedData_internal_hasTypeFooter( c_cerialized_array ) )	{
		c_footer_size	=	sizeof( CerializedTypeFooter );
	}
	
	uintptr_t*	c_end_of_iteration	=	c_raw_data_iterator 
																	+ c_cerialized_array->size 
																	- c_footer_size;

	while ( c_raw_data_iterator != c_end_of_iteration )	{
	
		CerializedData	c_cerialized_member;
		
			c_cerialized_member.size		=		*(uint32_t*) c_raw_data_iterator;
			c_raw_data_iterator					+=	sizeof( uint32_t );
			
			c_cerialized_member.data		=		c_raw_data_iterator;
			c_raw_data_iterator					+=	c_cerialized_member.size - sizeof( CerializeType );

			c_cerialized_member.type		=		c_raw_data_iterator;
			c_raw_data_iterator					+=	sizeof( CerializeType );

		VALUE	rb_member	=	Rcerialize_unpackRubyInstance(	& c_cerialized_member,
																											Qnil );
		
		rb_ary_push(	rb_return_array,
									rb_member );

	}
	
	return rb_return_array;
}

/******************************
*  unpackRubyObjectForStruct  *
******************************/

VALUE Rcerialize_unpackRubyObjectForStruct(	CerializedData*		c_cerialized_struct,
																						VALUE							rb_struct_class )	{

	VALUE	rb_return_struct	=	rb_funcall(	rb_struct_class,
																				rb_intern( "new" ),
																				0 );

	//	<key size><key data><data size><data data>...<type/footer>

	void*				c_raw_data_iterator	=	c_cerialized_struct->data;

	int					c_footer_size	=	0;
	if ( CerializedData_internal_hasDataFooter( c_cerialized_struct ) )	{
		c_footer_size	=	sizeof( CerializedData_DataFooterTypeForVersion( CerializedDataFooterCurrentVersion ) );
	}
	else if ( CerializedData_internal_hasTypeFooter( c_cerialized_struct ) )	{
		c_footer_size	=	sizeof( CerializedTypeFooter );
	}
	
	VALUE	rb_members	=	rb_struct_members( rb_return_struct );
	
	//	we assume that we have a full set of struct data represented
	//	by iterating the struct members (checking our data string internally), we ensure that we fail quietly and neatly if not
	int	c_which_member	=	0;
	for( c_which_member = 0 ; c_which_member < RARRAY_LEN( rb_members ) ; c_which_member++ )	{
	
		VALUE	rb_this_member	=	RARRAY_PTR( rb_members )[ c_which_member ];
	
		uintptr_t*	c_end_of_iteration	=	c_raw_data_iterator 
																		+ c_cerialized_struct->size 
																		- c_footer_size;

		while ( c_raw_data_iterator != c_end_of_iteration )	{
		
			CerializedData	c_cerialized_member;
			
				c_cerialized_member.size		=		*(uint32_t*) c_raw_data_iterator;
				c_raw_data_iterator					+=	sizeof( uint32_t );
				
				c_cerialized_member.data		=		c_raw_data_iterator;
				c_raw_data_iterator					+=	c_cerialized_member.size - sizeof( CerializeType );

				c_cerialized_member.type		=		c_raw_data_iterator;
				c_raw_data_iterator					+=	sizeof( CerializeType );

			VALUE	rb_data	=	Rcerialize_unpackRubyInstance(	& c_cerialized_member,
																											Qnil );
			
			rb_struct_aset(	rb_return_struct,
											rb_this_member,
											rb_data );

		}
	}
	
	return rb_return_struct;
}

/***********************************
*  unpackRubyObjectForNamedStruct  *
***********************************/

VALUE Rcerialize_unpackRubyObjectForNamedStruct(	CerializedData*		c_cerialized_named_struct,
																									VALUE							rb_struct_class	)	{

	VALUE	rb_return_struct	=	rb_funcall(	rb_struct_class,
																				rb_intern( "new" ),
																				0 );
	
	//	<key size><key data><data size><data data>...<type/footer>

	void*				c_raw_data_iterator	=	c_cerialized_named_struct->data;

	int					c_footer_size	=	0;
	if ( CerializedData_internal_hasDataFooter( c_cerialized_named_struct ) )	{
		c_footer_size	=	sizeof( CerializedData_DataFooterTypeForVersion( CerializedDataFooterCurrentVersion ) );
	}
	else if ( CerializedData_internal_hasTypeFooter( c_cerialized_named_struct ) )	{
		c_footer_size	=	sizeof( CerializedTypeFooter );
	}
	
	uintptr_t*	c_end_of_iteration	=	c_raw_data_iterator 
																	+ c_cerialized_named_struct->size 
																	- c_footer_size;
	
	while ( c_raw_data_iterator != c_end_of_iteration )	{
	
		CerializedData	c_cerialized_key;
		
			c_cerialized_key.size		=		*(uint32_t*) c_raw_data_iterator;
			c_raw_data_iterator			+=	sizeof( uint32_t );
			
			c_cerialized_key.data		=		c_raw_data_iterator;
			c_raw_data_iterator			+=	c_cerialized_key.size - sizeof( CerializeType );

			c_cerialized_key.type		=		c_raw_data_iterator;
			c_raw_data_iterator			+=	sizeof( CerializeType );

		CerializedData	c_cerialized_data;
	
			c_cerialized_data.size	=		*(uint32_t*) c_raw_data_iterator;
			c_raw_data_iterator			+=	sizeof( uint32_t );
			
			c_cerialized_data.data	=		c_raw_data_iterator;
			c_raw_data_iterator			+=	c_cerialized_data.size - sizeof( CerializeType );

			c_cerialized_data.type	=		c_raw_data_iterator;
			c_raw_data_iterator			+=	sizeof( CerializeType );
		
	
		VALUE	rb_key	=	Rcerialize_unpackRubyInstance(	& c_cerialized_key,
																										Qnil );
		VALUE	rb_data	=	Rcerialize_unpackRubyInstance(	& c_cerialized_data,
																										Qnil );
		
		rb_struct_aset(	rb_return_struct,
										rb_key,
										rb_data );
	}
	
	return rb_return_struct;
}
