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

#include "rcerialize/rcerialize_unpack.h"

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
			rb_return	=	Rcerialize_unpackRubyFileContents(		c_cerialized_data );
			break;

		case CerializeType_FilePath:
			rb_return	=	Rcerialize_unpackRubyFilePath(				c_cerialized_data );
			break;

		case CerializeType_Symbol:
			rb_return	=	Rcerialize_unpackRubySymbol(					c_cerialized_data );
			break;

		case CerializeType_Regexp:
			rb_return	=	Rcerialize_unpackRubyRegexp(					c_cerialized_data );
			break;

		case CerializeType_ClassName:
			rb_return	=	Rcerialize_unpackRubyClassName(				c_cerialized_data );
			break;

		case CerializeType_Nil:
			rb_return	=	Rcerialize_unpackRubyNil(             c_cerialized_data );
			break;

		case CerializeType_Raw:
		case CerializeType_String:
			rb_return	=	Rcerialize_unpackRubyString(					c_cerialized_data );
			break;

		case CerializeType_Complex:
			rb_return	=	Rcerialize_unpackRubyComplex(					c_cerialized_data );
			break;

		case CerializeType_Rational:
			rb_return	=	Rcerialize_unpackRubyRational(				c_cerialized_data );
			break;
			
		case CerializeType_Integer:
			rb_return	=	Rcerialize_unpackRubyInteger(					c_cerialized_data );
			break;

		case CerializeType_BigInteger:
			rb_return	=	Rcerialize_unpackRubyBigInteger(			c_cerialized_data );
			break;
			
		case CerializeType_Float:
			rb_return	=	Rcerialize_unpackRubyFloat(						c_cerialized_data );
			break;
			
		case CerializeType_TrueFalse:
			rb_return	=	Rcerialize_unpackRubyTrueFalse(				c_cerialized_data );
			break;

		case CerializeType_Array:
			rb_return	=	Rcerialize_unpackRubyArray(						c_cerialized_data );
			break;

		case CerializeType_Hash:
			rb_return	=	Rcerialize_unpackRubyHash(						c_cerialized_data );
			break;

		case CerializeType_Struct:
			rb_return	=	Rcerialize_unpackRubyStruct(          c_cerialized_data,
																												rb_load_as_class );
			break;

		case CerializeType_NamedStruct:
			rb_return	=	Rcerialize_unpackRubyNamedStruct(			c_cerialized_data,
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

/***********************
*  unpackRubyFilePath  *
***********************/

VALUE Rcerialize_unpackRubyFilePath(	CerializedData*		c_cerialized_file_path )	{

	//	get file path
	VALUE	rb_file_path	=	Rcerialize_unpackRubyString(	c_cerialized_file_path );
	
	//	create file with path
	VALUE	rb_file		=	rb_funcall(	rb_cFile,
																rb_intern( "new" ),
																1,
																rb_file_path );

	return rb_file;
}

/***************************
*  unpackRubyFileContents  *
***************************/

VALUE Rcerialize_unpackRubyFileContents(	CerializedData*		c_cerialized_file_contents )	{

	//	create ruby string from file data
	VALUE	rb_file_contents	=	Rcerialize_unpackRubyString(	c_cerialized_file_contents );
	
	return rb_file_contents;
}

/*********************
*  unpackRubySymbol  *
*********************/

VALUE Rcerialize_unpackRubySymbol(	CerializedData*		c_cerialized_symbol )	{

	VALUE	rb_symbol	=	Qnil;
	VALUE	rb_symbol_as_string	=	Rcerialize_unpackRubyString(	c_cerialized_symbol );
	
	if ( rb_symbol_as_string != Qnil )	{
		rb_symbol	=	ID2SYM( rb_to_id( rb_symbol_as_string ) );
	}
	
	return rb_symbol;
}

/*********************
*  unpackRubyRegexp  *
*********************/

VALUE Rcerialize_unpackRubyRegexp(	CerializedData*		c_cerialized_regexp )	{

	VALUE	rb_regexp	=	Qnil;
	VALUE	rb_regexp_as_string	=	Rcerialize_unpackRubyString(	c_cerialized_regexp );
	
	if ( rb_regexp_as_string != Qnil )	{
	
		rb_regexp	=	rb_funcall(	rb_cRegexp,
														rb_intern( "new" ),
														1,
														rb_regexp_as_string );
	}
	
	return rb_regexp;
}

/************************
*  unpackRubyClassName  *
************************/

VALUE Rcerialize_unpackRubyClassName(	CerializedData*		c_cerialized_class_name )	{

	VALUE	rb_class	=	Qnil;
	VALUE	rb_class_name	=	Rcerialize_unpackRubyString(	c_cerialized_class_name );
	
	if ( rb_class_name != Qnil )	{
		rb_class	=	rb_path_to_class( rb_class_name );
	}
	
	return rb_class;
}

/******************
*  unpackRubyNil  *
******************/

VALUE Rcerialize_unpackRubyNil(	CerializedData*		c_cerialized_string __attribute__ ((unused)) )	{

  return Qnil;
}

/*********************
*  unpackRubyString  *
*********************/

VALUE Rcerialize_unpackRubyString(	CerializedData*		c_cerialized_string )	{

	VALUE			rb_string	=	rb_str_new(	c_cerialized_string->data,
																		CerializedData_size( c_cerialized_string ) - 1 );

	return rb_string;
}

/**********************
*  unpackRubyComplex  *
**********************/

VALUE Rcerialize_unpackRubyComplex(	CerializedData*		c_cerialized_complex )	{

	CerializeStorage_Complex*	c_complex_number	=	(CerializeStorage_Complex*) c_cerialized_complex->data;

	VALUE	rb_complex_number	=	rb_Complex(	DBL2NUM( c_complex_number->real ),
																				DBL2NUM( c_complex_number->imaginary )	);

	return rb_complex_number;
}

/***********************
*  unpackRubyRational  *
***********************/

VALUE Rcerialize_unpackRubyRational(	CerializedData*		c_cerialized_rational )	{

	CerializeStorage_Rational*	c_rational_number	=	(CerializeStorage_Rational*) c_cerialized_rational->data;

	VALUE	rb_rational_number	=	rb_Rational(	DBL2NUM( c_rational_number->numerator ),
																						DBL2NUM( c_rational_number->denominator )	);

	return rb_rational_number;
}

/*************************
*  unpackRubyBigInteger  *
*************************/

VALUE Rcerialize_unpackRubyBigInteger(	CerializedData*		c_cerialized_big_integer )	{

  char*  c_big_integer_string = c_cerialized_big_integer->data;

  VALUE rb_big_integer  = rb_cstr2inum( c_big_integer_string, 10 );
  
  return rb_big_integer;
}

/**********************
*  unpackRubyInteger  *
**********************/

VALUE Rcerialize_unpackRubyInteger(	CerializedData*		c_cerialized_integer )	{

	CerializeStorage_Integer*	c_integer	=	(CerializeStorage_Integer*) c_cerialized_integer->data;

	VALUE	rb_integer	=	LL2NUM( c_integer->integer_value );

	return rb_integer;
}

/********************
*  unpackRubyFloat  *
********************/

VALUE Rcerialize_unpackRubyFloat(	CerializedData*		c_cerialized_float )	{

	CerializeStorage_Float*	c_float	=	(CerializeStorage_Float*) c_cerialized_float->data;

	VALUE	rb_float	=	DBL2NUM( c_float->float_value );

	return rb_float;
}

/************************
*  unpackRubyTrueFalse  *
************************/

VALUE Rcerialize_unpackRubyTrueFalse(	CerializedData*		c_cerialized_true_false )	{

	BOOL*	c_true_false	=	(BOOL*) c_cerialized_true_false->data;

	VALUE	rb_true_false	=	( *c_true_false	?	Qtrue 
                                        :	Qfalse );

	return rb_true_false;
}

/********************
*  unpackRubyArray  *
********************/

VALUE Rcerialize_unpackRubyArray(	CerializedData*		c_cerialized_array )	{

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
	
		uint32_t							size					=		*(uint32_t*) c_raw_data_iterator;
		c_raw_data_iterator									+=	sizeof( uint32_t );
		
		void*									data					=		c_raw_data_iterator;
		c_raw_data_iterator									+=	size - sizeof( CerializedTypeFooter );

		CerializedTypeFooter*	type_footer		=		(CerializedTypeFooter*) c_raw_data_iterator;
		c_raw_data_iterator									+=	sizeof( CerializedTypeFooter );

		CerializedData*	c_cerialized_member	=	CerializedData_new(	(void**) & data,
																															size );

		*c_cerialized_member->type	=	type_footer->type;

		c_cerialized_member->free_does_not_free_data	=	TRUE;

		VALUE	rb_member	=	Rcerialize_unpackRubyInstance(	c_cerialized_member,
																											Qnil );
		
		rb_ary_push(	rb_return_array,
									rb_member );
		
		CerializedData_free( & c_cerialized_member );
		
	}
	
	return rb_return_array;
}

/*******************
*  unpackRubyHash  *
*******************/

VALUE Rcerialize_unpackRubyHash(	CerializedData*		c_cerialized_hash )	{
  
	VALUE	rb_return_hash	=	rb_hash_new();
	
	//	<key size><key data><data size><data data>...<type/footer>
  
	uint32_t		c_footer_size     =	0;
	if ( CerializedData_internal_hasDataFooter( c_cerialized_hash ) )	{
		c_footer_size     =	sizeof( CerializedData_DataFooterTypeForVersion( CerializedDataFooterCurrentVersion ) );
	}
	else if ( CerializedData_internal_hasTypeFooter( c_cerialized_hash ) )	{
		c_footer_size	=	sizeof( CerializedTypeFooter );
	}

  //  operate on a copy of the data pointer and size so we don't modify the data we start with
  void*     c_data = c_cerialized_hash->data;
  uint32_t  c_size = c_cerialized_hash->size;
  
	while ( c_size > c_footer_size )	{
    
    CerializedData* c_cerialized_key_data_pair   =  CerializedData_new( & c_data,
                                                                        c_size );
    CerializedData_setDataNotToFree( c_cerialized_key_data_pair );

    RcerializeKeyDataReturn*  c_key_data = Rcerialize_unpackRubyKeyDataPair(	c_cerialized_key_data_pair );

    //  move data forward and subtract processed size
    c_data +=  c_key_data->c_total_iterated_size;
    c_size -=  c_key_data->c_total_iterated_size;

    VALUE   rb_key      =   c_key_data->rb_key;
    VALUE   rb_data     =   c_key_data->rb_data;
		
    CerializedData_free( & c_cerialized_key_data_pair );
    free( c_key_data );
    
		rb_hash_aset(	rb_return_hash,
                  rb_key,
                  rb_data );
	}

	return rb_return_hash;
}

/*********************
*  unpackRubyStruct  *
*********************/

VALUE Rcerialize_unpackRubyStruct(	CerializedData*		c_cerialized_struct,
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

  uintptr_t*	c_end_of_iteration	=	c_raw_data_iterator 
                                  + c_cerialized_struct->size;
	
	//	we assume that we have a full set of struct data represented
	//	by iterating the struct members (checking our data string internally), we ensure that we fail quietly and neatly if not
	int	c_which_member	=	0;
	for( c_which_member = 0 ; c_which_member < RARRAY_LEN( rb_members ) ; c_which_member++ )	{
	
		VALUE	rb_this_member	=	RARRAY_PTR( rb_members )[ c_which_member ];
	
		if ( c_raw_data_iterator != c_end_of_iteration )	{
		
      uint32_t	c_data_size				=		*(uint32_t*) c_raw_data_iterator;
      c_raw_data_iterator					+=	sizeof( uint32_t );
      
      void*			c_data_data				=		c_raw_data_iterator;
      c_raw_data_iterator					+=	c_data_size - sizeof( CerializedTypeFooter );
      
      CerializedTypeFooter*				c_data_type_footer	=   (CerializedTypeFooter*) c_raw_data_iterator;
      CerializeType								c_data_type					=   c_data_type_footer->type;
      c_raw_data_iterator															+=	sizeof( CerializedTypeFooter );

      //  we didn't pack non-named struct using key/value pairs, so we don't have an extra footer here
      
      //	unpack key/data
      CerializedData*	c_cerialized_member	=	CerializedData_new(	& c_data_data,
                                                                c_data_size );

      CerializedData_setDataNotToFree( c_cerialized_member );

      CerializedData_setType(	c_cerialized_member,
                              c_data_type);
      
      VALUE	rb_data	=	Rcerialize_unpackRubyInstance(	c_cerialized_member,
                                                      rb_struct_class );
      
      CerializedData_free( & c_cerialized_member );

			rb_struct_aset(	rb_return_struct,
											rb_this_member,
											rb_data );

		}
	}
	
	return rb_return_struct;
}

/**************************
*  unpackRubyNamedStruct  *
**************************/

VALUE Rcerialize_unpackRubyNamedStruct(	CerializedData*		c_cerialized_named_struct,
                                        VALUE							rb_struct_class	)	{

	VALUE	rb_return_struct	=	rb_funcall(	rb_struct_class,
																				rb_intern( "new" ),
																				0 );
	
	//	<key size><key data><data size><data data>...<type/footer>

	uint32_t		c_footer_size	=	0;
	if ( CerializedData_internal_hasDataFooter( c_cerialized_named_struct ) )	{
		c_footer_size	=	sizeof( CerializedData_DataFooterTypeForVersion( CerializedDataFooterCurrentVersion ) );
	}
	else if ( CerializedData_internal_hasTypeFooter( c_cerialized_named_struct ) )	{
		c_footer_size	=	sizeof( CerializedTypeFooter );
	}
  
  void*     c_original_data = c_cerialized_named_struct->data;
  uint32_t  c_original_size = c_cerialized_named_struct->size;

	while ( c_cerialized_named_struct->size > c_footer_size )	{
    
    RcerializeKeyDataReturn*  c_key_data = Rcerialize_unpackRubyKeyDataPair( c_cerialized_named_struct );

    //  move data forward and subtract processed size
    c_cerialized_named_struct->data +=  c_key_data->c_total_iterated_size;
    c_cerialized_named_struct->size -=  c_key_data->c_total_iterated_size;

    VALUE   rb_key      =   c_key_data->rb_key;
    VALUE   rb_data     =   c_key_data->rb_data;
		
    free( c_key_data );
    
		rb_struct_aset(	rb_return_struct,
										rb_key,
										rb_data );
	}

  c_cerialized_named_struct->data =  c_original_data;
  c_cerialized_named_struct->size =  c_original_size;
		
	return rb_return_struct;
}

	/**************************
	*  unpackRubyKeyDataPair  *
	**************************/

	//	<key length><key data>
	RcerializeKeyDataReturn* Rcerialize_unpackRubyKeyDataPair(	CerializedData*		c_cerialized_key_data_pair )	{
    
    void*		c_raw_data_iterator	=	c_cerialized_key_data_pair->data;

    //  total size
    //  uint32_t  c_total_size      =   *(uint32_t*) c_raw_data_iterator;
		c_raw_data_iterator					+=	sizeof( uint32_t );

		//	key
		uint32_t	c_key_size				=		*(uint32_t*) c_raw_data_iterator;
		c_raw_data_iterator					+=	sizeof( uint32_t );
    
		void*			c_key_data				=		c_raw_data_iterator;
		c_raw_data_iterator					+=	c_key_size;
    
		//	data
		uint32_t	c_data_size				=		*(uint32_t*) c_raw_data_iterator;
		c_raw_data_iterator					+=	sizeof( uint32_t );
    
		void*			c_data_data				=		c_raw_data_iterator;
		c_raw_data_iterator					+=	c_data_size;
    
		//	Finally, we have a type footer for key/value pair
		c_raw_data_iterator					+=	sizeof( CerializedTypeFooter );
    
    CerializedData* c_cerialized_key   = CerializedData_new(  & c_key_data,
                                                              c_key_size );
    CerializedData* c_cerialized_data  = CerializedData_new(  & c_data_data,
                                                              c_data_size );

		CerializedData_setDataNotToFree( c_cerialized_key );
		CerializedData_setDataNotToFree( c_cerialized_data );

		VALUE	rb_key	=	Rcerialize_unpackRubyInstance(	c_cerialized_key,
                                                    Qnil );
		VALUE	rb_data	=	Rcerialize_unpackRubyInstance(	c_cerialized_data,
                                                    Qnil );
		
		CerializedData_free( & c_cerialized_key );
		CerializedData_free( & c_cerialized_data );
    
    RcerializeKeyDataReturn*  c_return  = calloc( 1, sizeof( RcerializeKeyDataReturn ) );
    
    c_return->rb_key   = rb_key;
    c_return->rb_data  = rb_data;
    c_return->c_total_iterated_size = c_raw_data_iterator - c_cerialized_key_data_pair->data;
    
    return c_return;
  }
