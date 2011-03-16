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

#include <cerialize/cerialize.h>

#include "rcerialize/rcerialize_pack.h"

/*******************************************************************************************************************************************************************************************
																		Ruby Definitions
*******************************************************************************************************************************************************************************************/

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*********************
*  packRubyInstance  *
*********************/

CerializedData* Rcerialize_packRubyInstance(	VALUE							rb_object,
																							CerializeType			c_storage_type,
																							BOOL							type_not_footer )	{

	CerializedData*	c_cerialized_data	=	NULL;

	//	pack object for type (expects determination to occur externally)
	switch ( c_storage_type )	{

		case CerializeType_FileContents:
			c_cerialized_data	=	Rcerialize_packRubyFileContents(	rb_object );
			break;

		case CerializeType_FilePath:
			c_cerialized_data	=	Rcerialize_packRubyFilePath(			rb_object );
			break;

		case CerializeType_Symbol:
			c_cerialized_data	=	Rcerialize_packRubySymbol(				rb_object );
			break;

		case CerializeType_Regexp:
			c_cerialized_data	=	Rcerialize_packRubyRegexp(				rb_object );
			break;

		case CerializeType_ClassName:
			c_cerialized_data	=	Rcerialize_packRubyClassName(			rb_object );
			break;

		case CerializeType_Nil:
			c_cerialized_data	=	Rcerialize_packRubyNil(				rb_object );
			break;

		case CerializeType_String:
			c_cerialized_data	=	Rcerialize_packRubyString(				rb_object );
			break;

		case CerializeType_Complex:
			c_cerialized_data	=	Rcerialize_packRubyComplex(				rb_object );
			break;

		case CerializeType_Rational:
			c_cerialized_data	=	Rcerialize_packRubyRational(			rb_object );
			break;
			
		case CerializeType_Integer:
			c_cerialized_data	=	Rcerialize_packRubyInteger(				rb_object );
			break;
			
		case CerializeType_Float:
			c_cerialized_data	=	Rcerialize_packRubyFloat(					rb_object );
			break;
			
		case CerializeType_TrueFalse:
			c_cerialized_data	=	Rcerialize_packRubyTrueFalse(			rb_object );
			break;

		case CerializeType_Array:
			c_cerialized_data	=	Rcerialize_packRubyArray(         rb_object );
			break;

		case CerializeType_Hash:
			c_cerialized_data	=	Rcerialize_packRubyHash(          rb_object );
			break;

		case CerializeType_NamedStruct:
			c_cerialized_data	=	Rcerialize_packRubyNamedStruct(		rb_object );
			break;

		case CerializeType_Struct:
			c_cerialized_data	=	Rcerialize_packRubyStruct(        rb_object );
			break;
			
		default:			
			rb_raise( rb_eArgError, "Provided data was invalid." );
			break;
	}
  
  //  if we have a footer instead of just a type we need to move the type over to a data footer
	if ( ! type_not_footer )	{
		CerializedData_internal_createDataFooter( c_cerialized_data );
	}
	
	return c_cerialized_data;
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Private Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

static int Rcerialize_iterateRubyHashForCerializedData(	VALUE												rb_key,
																												VALUE												rb_data,
																												RcerializeHashForeachInfo*	c_passed_info );

/****************
*  packRubyNil  *
****************/

CerializedData* Rcerialize_packRubyNil(	VALUE		rb_nil __attribute__ ((unused)) )	{

	char*	c_nil	=	calloc( 1, sizeof( char ) );
	
	CerializedData*	c_cerialized_data	=	CerializedData_new(	(void**) & c_nil,
																													sizeof( char ) );
	
	CerializedData_setType(	c_cerialized_data,
													CerializeType_Nil );

	return c_cerialized_data;
}

/*******************
*  packRubyString  *
*******************/

CerializedData* Rcerialize_packRubyString(	VALUE		rb_string )	{

	char*	c_string	=	strdup( StringValuePtr(	rb_string ) );
	
	CerializedData*	c_cerialized_data	=	CerializedData_new(	(void**) & c_string,
																													RSTRING_LEN( rb_string ) + 1 * sizeof( char ) );
	
	CerializedData_setType(	c_cerialized_data,
													CerializeType_String );

	return c_cerialized_data;
}

/*******************
*  packRubySymbol  *
*******************/

CerializedData* Rcerialize_packRubySymbol(	VALUE		rb_symbol )	{

	CerializedData*	c_cerialized_data	=	NULL;

	rb_symbol	=	rb_obj_as_string(	rb_symbol );

	c_cerialized_data	=	Rcerialize_packRubyString(	rb_symbol );

	CerializedData_setType(	c_cerialized_data,
													CerializeType_Symbol );
	
	return c_cerialized_data;
}

/**********************
*  packRubyClassName  *
**********************/

CerializedData* Rcerialize_packRubyClassName(	VALUE		rb_class )	{

	CerializedData*	c_cerialized_data	=	NULL;

	rb_class				=	rb_obj_as_string(	rb_class );

	c_cerialized_data	=	Rcerialize_packRubyString(	rb_class );

	CerializedData_setType(	c_cerialized_data,
													CerializeType_ClassName );
	
	return c_cerialized_data;
}

/********************
*  packRubyInteger  *
********************/

CerializedData* Rcerialize_packRubyInteger(	VALUE		rb_integer )	{	

  //  a ruby integer can be an fixnum or a bignum

  VALUE rb_integer_klass  = rb_class_of( rb_integer );

  CerializedData*	c_cerialized_data = NULL;

  //  if we have a fixnum we store as a long
  if (      rb_integer_klass == rb_cFixnum )  {
  
    //  
    long long*	c_long				=		calloc( 1, sizeof( long long ) );
    *c_long										=		NUM2LL( rb_integer );

    c_cerialized_data	=	CerializedData_new(	(void**) & c_long,
                                            sizeof( long long ) );
  
    CerializedData_setType(	c_cerialized_data,
                            CerializeType_Integer );

  }
  //  or if we have a bignum we store as a bytestring of chars
  else if ( rb_integer_klass == rb_cBignum )  {
  
    //  get byte string (char*)
    VALUE rb_base_ten_big_integer_string  = rb_big2str( rb_integer, 10 );
    long  c_size_of_big_integer  = ( RSTRING_LEN( rb_base_ten_big_integer_string ) + 1 ) * sizeof( char );

    char*  c_big_integer_string = calloc( 1, c_size_of_big_integer );

    const char* c_base_ten_big_integer_string   = StringValuePtr( rb_base_ten_big_integer_string );
      
    strcpy( c_big_integer_string, c_base_ten_big_integer_string );

    c_cerialized_data	=	CerializedData_new(	(void**) & c_big_integer_string,
                                            c_size_of_big_integer );
  
    CerializedData_setType(	c_cerialized_data,
                            CerializeType_BigInteger );

  }

	return c_cerialized_data;
}

/******************
*  packRubyFloat  *
******************/

CerializedData* Rcerialize_packRubyFloat(	VALUE		rb_float )	{

	double*	c_double					=		calloc( 1, sizeof( double ) );
	*c_double									=		NUM2DBL( rb_float );

	CerializedData*	c_cerialized_data	=	CerializedData_new(	(void**) & c_double,
																													sizeof( double ) );

	CerializedData_setType(	c_cerialized_data,
													CerializeType_Float );

	return c_cerialized_data;
}

/*******************
*  packRubyRegexp  *
*******************/

CerializedData* Rcerialize_packRubyRegexp(	VALUE		rb_regexp )	{

	CerializedData*	c_cerialized_data	=	NULL;

	rb_regexp				=	rb_funcall(	rb_regexp,
																rb_intern( "source" ),
																0 );

	c_cerialized_data	=	Rcerialize_packRubyString(	rb_regexp );

	CerializedData_setType(	c_cerialized_data,
													CerializeType_Regexp );
	
	return c_cerialized_data;
}

/*********************
*  packRubyFilePath  *
*********************/

CerializedData* Rcerialize_packRubyFilePath(	VALUE		rb_file )	{

	CerializedData*	c_cerialized_data	=	NULL;

	//	get file path
	VALUE	rb_file_path	=	rb_funcall(	rb_file,
																		rb_intern( "path" ),
																		0 );
	
	c_cerialized_data	=	Rcerialize_packRubyString(	rb_file_path );

	CerializedData_setType(	c_cerialized_data,
													CerializeType_FilePath );
	
	return c_cerialized_data;
}

/*************************
*  packRubyFileContents  *
*************************/

CerializedData* Rcerialize_packRubyFileContents(	VALUE		rb_file )	{

	CerializedData*	c_cerialized_data	=	NULL;

	//	read lines into array
	VALUE	rb_file_lines	=	rb_funcall(	rb_file,
																		rb_intern( "readlines" ),
																		0 );

	VALUE	rb_file_contents	=	rb_funcall(	rb_file_lines,
																				rb_intern( "join" ),
																				1,
																				rb_str_new( "\n", 1 ) );

	//	store as string
	c_cerialized_data	=	Rcerialize_packRubyString(	rb_file_contents );

	CerializedData_setType(	c_cerialized_data,
													CerializeType_FileContents );

	return c_cerialized_data;
}

/********************
*  packRubyComplex  *
********************/

CerializedData* Rcerialize_packRubyComplex(	VALUE		rb_complex_number )	{

	//	store real - double
	VALUE	rb_real_part				=		rb_funcall(	rb_complex_number,
																						rb_intern( "real" ),
																						0 );
	VALUE	rb_imaginary_part		=		rb_funcall(	rb_complex_number,
																						rb_intern( "imaginary" ),
																						0 );
	
	CerializeStorage_Complex*	c_complex_number	=	calloc( 1, sizeof( CerializeStorage_Complex ) );
	c_complex_number->real				=	NUM2DBL( rb_real_part );
	c_complex_number->imaginary		=	NUM2DBL( rb_imaginary_part );

	CerializedData*	c_cerialized_data	=	CerializedData_new(	(void**) & c_complex_number,
																													sizeof( CerializeStorage_Complex ) );

	CerializedData_setType(	c_cerialized_data,
													CerializeType_Complex );

	return c_cerialized_data;
}

/*********************
*  packRubyRational  *
*********************/

CerializedData* Rcerialize_packRubyRational(	VALUE		rb_rational_number )	{

	//	store numerator - double
	VALUE	rb_numerator				=		rb_funcall(	rb_rational_number,
																						rb_intern( "numerator" ),
																						0 );
	VALUE	rb_denominator			=		rb_funcall(	rb_rational_number,
																						rb_intern( "denominator" ),
																						0 );

	CerializeStorage_Rational*	c_rational_number	=	calloc( 1, sizeof( CerializeStorage_Rational ) );
	c_rational_number->numerator			=	NUM2DBL( rb_numerator );
	c_rational_number->denominator		=	NUM2DBL( rb_denominator );

	CerializedData*	c_cerialized_data	=	CerializedData_new(	(void**) & c_rational_number,
																													sizeof( CerializeStorage_Rational ) );

	CerializedData_setType(	c_cerialized_data,
													CerializeType_Rational );

	return c_cerialized_data;
}

/**********************
*  packRubyTrueFalse  *
**********************/

CerializedData* Rcerialize_packRubyTrueFalse(	VALUE		rb_true_false )	{

	BOOL*	bool_key						=		calloc( 1, sizeof( BOOL ) );
	*bool_key									=		( rb_true_false == Qtrue	?	TRUE
																													:	FALSE );
	
	CerializedData*	c_cerialized_data	=	CerializedData_new(	(void**) & bool_key,
																													sizeof( BOOL ) );

	CerializedData_setType(	c_cerialized_data,
													CerializeType_TrueFalse );

	return c_cerialized_data;
}

/******************
*  packRubyArray  *
******************/

//	<member length><member data>...<type/footer>
CerializedData* Rcerialize_packRubyArray(	VALUE		rb_array )	{

	CerializedData*		c_cerialized_data					=	calloc( 1, sizeof( CerializedData ) );
	void*							c_raw_data_copy_pointer		=	NULL;
	
	//	allocate an array of CerializedData structs
	CerializedData**	c_cerialized_member_data	=	calloc( RARRAY_LEN( rb_array ), sizeof( CerializedData* ) );
	
	//	for each item in array
	int	c_which_member			= 0;
	uint32_t	c_total_size	=	0;
	for ( c_which_member = 0 ; c_which_member < RARRAY_LEN( rb_array ) ; c_which_member++ )	{
	
		VALUE	rb_this_member	=	RARRAY_PTR( rb_array )[ c_which_member ];

		//	pack item
		CerializeType			c_member_type							=	Rcerialize_storageTypeForRubyInstance( rb_this_member );
		c_cerialized_member_data[ c_which_member ]	=	Rcerialize_packRubyInstance(	rb_this_member,
																																								c_member_type,
																																								TRUE );
		c_total_size	+=	c_cerialized_member_data[ c_which_member ]->size;
		c_total_size	+=	sizeof( uint32_t );
	}

	//	allocate raw data
	c_cerialized_data->data		=	malloc( c_total_size );
	c_raw_data_copy_pointer		=	c_cerialized_data->data;
	c_cerialized_data->size		=	c_total_size;
	
	for ( c_which_member = 0 ; c_which_member < RARRAY_LEN( rb_array ) ; c_which_member++ )	{
		
		//	append packed data length
		memcpy(	c_raw_data_copy_pointer,
						& c_cerialized_member_data[ c_which_member ]->size,
						sizeof( uint32_t ) );
		c_raw_data_copy_pointer	+=	sizeof( uint32_t );
		
		//	append packed data
		memcpy(	c_raw_data_copy_pointer,
						c_cerialized_member_data[ c_which_member ]->data,
						c_cerialized_member_data[ c_which_member ]->size );
		c_raw_data_copy_pointer	+=	c_cerialized_member_data[ c_which_member ]->size;
		
		//	free item
		CerializedData_free( & c_cerialized_member_data[ c_which_member ] );
		
	}

	CerializedData_setType(	c_cerialized_data,
													CerializeType_Array );
	
	free( c_cerialized_member_data );
		
	return c_cerialized_data;
}

/*****************
*  packRubyHash  *
*****************/

//	<key length><key data><data length><data data>...<type/footer>
CerializedData* Rcerialize_packRubyHash(	VALUE		rb_hash )	{

	/*---------------- Iterate and cerialize each key/data -------------------*/

	CerializedData**	c_cerialized_key_data_pointers	=	calloc( RHASH_SIZE( rb_hash ), sizeof( CerializedData* ) );

	RcerializeHashForeachInfo		c_hash_passed_info;

	//	allocate CerializedData*[]
	c_hash_passed_info.c_cerialized_data	=	c_cerialized_key_data_pointers;
	c_hash_passed_info.count							=	0;
	c_hash_passed_info.total_size					=	0;
	rb_hash_foreach(	rb_hash,
										Rcerialize_iterateRubyHashForCerializedData,
										(VALUE) & c_hash_passed_info );

	/*----------------- Combine cerialized key/data elements ----------------*/

	//	<key_data_pair>...

	void*				c_data										=	calloc( 1, c_hash_passed_info.total_size );
	uint32_t		c_data_size								=	c_hash_passed_info.total_size;
	void*				c_raw_data_copy_pointer		= c_data;

	int	c_which_key_data_pair		= 0;
	for ( c_which_key_data_pair = 0 ; c_which_key_data_pair < c_hash_passed_info.count ; c_which_key_data_pair++ )	{
		
		CerializedData*	c_this_key_data_pair	=	c_cerialized_key_data_pointers[ c_which_key_data_pair ];
		
		//	concat data with combined data (footer included if present)
		memcpy(	c_raw_data_copy_pointer,
						c_this_key_data_pair->data,
						c_this_key_data_pair->size );
		
		//	move copy pointer forward
		c_raw_data_copy_pointer	+=	c_this_key_data_pair->size;
		
		//	free key-data pair
		CerializedData_free( & c_this_key_data_pair );
	}

	//	free CerializedData*[]
	free( c_cerialized_key_data_pointers );

	CerializedData*			c_cerialized_data					=	CerializedData_new(	& c_data,
																																			c_data_size );

	CerializedData_setType(	c_cerialized_data,
													CerializeType_Hash );

	return c_cerialized_data;
}

	/*************************************
	*  iterateRubyHashForCerializedData  *
	*************************************/

	static int Rcerialize_iterateRubyHashForCerializedData(	VALUE												rb_key,
																													VALUE												rb_data,
																													RcerializeHashForeachInfo*	c_passed_info )	{

		c_passed_info->c_cerialized_data[ c_passed_info->count ]	=	Rcerialize_packRubyKeyDataPair(	rb_key,
                                                                                                rb_data );

		c_passed_info->total_size	+=	c_passed_info->c_cerialized_data[ c_passed_info->count ]->size;
		
    c_passed_info->count++;
    
		return ST_CONTINUE;
	}

/*******************
*  packRubyStruct  *
*******************/

//	<data length><data data>...<type/footer>
CerializedData* Rcerialize_packRubyStruct(	VALUE		rb_struct )	{

	CerializedData*		c_cerialized_data					=	calloc( 1, sizeof( CerializedData ) );
	void*							c_raw_data_copy_pointer		=	NULL;
	
	CerializedData**  c_cerialized_struct_data  = calloc( RSTRUCT_LEN( rb_struct ), sizeof( CerializedData* ) );

	//	for each pair in struct
	int				c_which_data		=	0;
	uint32_t	c_total_size		=	0;
	for ( c_which_data = 0 ; c_which_data < RSTRUCT_LEN( rb_struct ) ; c_which_data++ ) {

		VALUE	rb_this_data	=	RSTRUCT_PTR( rb_struct )[ c_which_data ];

		//	pack key/data pair
		CerializeType			c_member_type               =	Rcerialize_storageTypeForRubyInstance( rb_this_data );
		
    CerializedData*   c_this_cerialized_struct    = Rcerialize_packRubyInstance(	rb_this_data,
                                                                                  c_member_type,
                                                                                  TRUE );
		
		c_total_size	+=	c_this_cerialized_struct->size;

    c_cerialized_struct_data[ c_which_data ]  = c_this_cerialized_struct;
		
	}
	
	//	allocate raw data
  c_total_size            +=  ( RSTRUCT_LEN( rb_struct ) * sizeof( uint32_t ) );
	c_cerialized_data->data	=   calloc( 1, c_total_size );
	c_raw_data_copy_pointer	=   c_cerialized_data->data;
	c_cerialized_data->size	=   c_total_size;
	
	//	copy data to destination
	for ( c_which_data = 0 ; c_which_data < RSTRUCT_LEN( rb_struct ) ; c_which_data++ ) {

		//	append pair size
		memcpy(	c_raw_data_copy_pointer,
						& c_cerialized_struct_data[ c_which_data ]->size,
						sizeof( uint32_t ) );
		c_raw_data_copy_pointer	+=	sizeof( uint32_t );
	
		//	append pair to data
		memcpy(	c_raw_data_copy_pointer,
						c_cerialized_struct_data[ c_which_data ]->data,
						c_cerialized_struct_data[ c_which_data ]->size );
		c_raw_data_copy_pointer	+=	c_cerialized_struct_data[ c_which_data ]->size;

		//	free packed key/data pair
		CerializedData_free( & c_cerialized_struct_data[ c_which_data ] );
	}

	CerializedData_setType(	c_cerialized_data,
													CerializeType_Struct );

  free( c_cerialized_struct_data );

	return c_cerialized_data;
}

/************************
*  packNamedRubyStruct  *
************************/

//	<key length><key data><data length><data data>...<type/footer>
CerializedData* Rcerialize_packRubyNamedStruct(	VALUE		rb_struct )	{
	
	CerializedData**	c_cerialized_key_value_pair   = calloc( RSTRUCT_LEN( rb_struct ), sizeof( CerializedData* ) );

	VALUE	rb_members  =  rb_struct_members( rb_struct );
	
	//	for each pair in struct
	int				c_which_data		=	0;
	uint32_t	c_total_size		=	0;
	for ( c_which_data = 0 ; c_which_data < RSTRUCT_LEN( rb_struct ) ; c_which_data++ ) {

		VALUE	rb_this_key		=	RARRAY_PTR( rb_members )[ c_which_data ];
		VALUE	rb_this_data	=	RSTRUCT_PTR( rb_struct )[ c_which_data ];

    CerializedData*   c_this_cerialized_struct    = Rcerialize_packRubyKeyDataPair(	rb_this_key,
                                                                                    rb_this_data );
		
		c_total_size	+=	c_this_cerialized_struct->size;

    c_cerialized_key_value_pair[ c_which_data ]  = c_this_cerialized_struct;

	}

	//	allocate raw data - key/data pairs stack
	void*           c_data                    =   calloc( 1, c_total_size );
	void*           c_raw_data_copy_pointer   =   c_data;

	//	copy data to destination
	for ( c_which_data = 0 ; c_which_data < RSTRUCT_LEN( rb_struct ) ; c_which_data++ ) {
	
		CerializedData*	c_this_key_data_pair	=	c_cerialized_key_value_pair[ c_which_data ];

		//	append pair to data
		memcpy(	c_raw_data_copy_pointer,
						c_this_key_data_pair->data,
						c_this_key_data_pair->size );
            
		c_raw_data_copy_pointer	+=	c_this_key_data_pair->size;

		//	free packed key/data pair
		CerializedData_free( & c_this_key_data_pair );

	}

  free( c_cerialized_key_value_pair );
  
  CerializedData* c_cerialized_data = CerializedData_new( & c_data,
                                                          c_total_size );

	CerializedData_setType(	c_cerialized_data,
													CerializeType_NamedStruct );

	return c_cerialized_data;
}

	/************************
	*  packRubyKeyDataPair  *
	************************/

	//	<key length><key data>
	CerializedData* Rcerialize_packRubyKeyDataPair(	VALUE		rb_key,
																									VALUE		rb_data )	{

		CerializedData*		c_cerialized_data						=	calloc( 1, sizeof( CerializedData ) );
		void*							c_raw_data_copy_pointer			=	NULL;

    /*---------------------------- Pack Key/Data ----------------------------*/

		//	pack key
		CerializeType			c_key_type									=	Rcerialize_storageTypeForRubyInstance( rb_key );
		CerializedData*		c_cerialized_key_from_pair	=	Rcerialize_packRubyInstance(	rb_key,
																																									c_key_type,
																																									TRUE );
		
		//	pack data
		CerializeType			c_data_type									=	Rcerialize_storageTypeForRubyInstance( rb_data );
		CerializedData*		c_cerialized_data_from_pair	=	Rcerialize_packRubyInstance(	rb_data,
																																									c_data_type,
																																									TRUE );

    /*----------------- Combine cerialized key/data elements ----------------*/
		
    //  pack:
    //  <total keysize/key/datasize/data size> <key data size><key data> <data data size><data data> <typefooter>
    
                                /* length of keysize/key/datasize/data/typefooter (this value) */
    uint32_t    c_total_size  = sizeof( uint32_t )
                                /* length of key/typefooter */
                              + sizeof( uint32_t )
                              + c_cerialized_key_from_pair->size
                                /* length of data/typefooter */
                              + sizeof( uint32_t )
                              + c_cerialized_data_from_pair->size;
		
		//	alloc new combined data
		c_cerialized_data->data	=	calloc( 1, c_total_size );
		c_cerialized_data->size	=	c_total_size;
		c_raw_data_copy_pointer	=	c_cerialized_data->data;

		//	append total key/data size
    uint32_t  c_total_key_data_size = c_cerialized_data->size - sizeof( uint32_t );
		memcpy(	c_raw_data_copy_pointer,
						& c_total_key_data_size,
						sizeof( uint32_t ) );
		c_raw_data_copy_pointer	+=	sizeof( uint32_t );
		
		//	append key size
		memcpy(	c_raw_data_copy_pointer,
						& c_cerialized_key_from_pair->size,
						sizeof( uint32_t ) );
		c_raw_data_copy_pointer	+=	sizeof( uint32_t );
		
		//	append key data
		memcpy(	c_raw_data_copy_pointer,
						c_cerialized_key_from_pair->data,
						c_cerialized_key_from_pair->size );
		c_raw_data_copy_pointer	+=	c_cerialized_key_from_pair->size;
		
		//	append data size
		memcpy(	c_raw_data_copy_pointer,
						& c_cerialized_data_from_pair->size,
						sizeof( uint32_t ) );
		c_raw_data_copy_pointer	+=	sizeof( uint32_t );
		
		//	append data data
		memcpy(	c_raw_data_copy_pointer,
						c_cerialized_data_from_pair->data,
						c_cerialized_data_from_pair->size );
		c_raw_data_copy_pointer	+=	c_cerialized_data_from_pair->size;
		
		//	free key and data
		CerializedData_free( & c_cerialized_key_from_pair );
		CerializedData_free( & c_cerialized_data_from_pair );

		CerializedData_setType(	c_cerialized_data,
														CerializeType_KeyDataPair );

		//	return size
		return c_cerialized_data;
	}
