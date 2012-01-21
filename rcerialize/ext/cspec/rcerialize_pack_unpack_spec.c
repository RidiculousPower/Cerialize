#include <cspec.h>
#include <cspec/cspec_output_header.h>
#include <cspec/cspec_output_verbose.h>
#include <cspec/cspec_output_unit.h>

#include <ruby.h>
#include <cerialize.h>

#include "rcerialize/rcerialize_pack.h"
#include "rcerialize/rcerialize_unpack.h"

#include "cspec/rcerialize_pack_unpack_spec.h"

#include <string.h>

extern VALUE rb_cObject;

/*********************
*  packRubyString    *
*  unpackRubyString  *
*********************/

DESCRIBE( Rcerialize_pack_unpack_String, "\n * Rcerialize_packRubyString( VALUE rb_string )\n * Rcerialize_unpackRubyString( CerializedData* cerialized_data )" )
  IT( "can pack and unpack a string" )
    
  VALUE  rb_string  =  rb_str_new2( "ruby string" );
  CerializedData*  cerialized_string  =  Rcerialize_packRubyString( rb_string );  
  SHOULD_NOT_BE_NULL( cerialized_string->data );
  SHOULD_EQUAL( cerialized_string->size, RSTRING_LEN( rb_string ) + 1 + sizeof( CerializedTypeFooter ) );
  SHOULD_EQUAL( *cerialized_string->type, CerializeType_String);
  SHOULD_BE_FALSE( CerializedData_internal_hasDataFooter( cerialized_string ) );
  SHOULD_BE_TRUE( CerializedData_internal_hasTypeFooter( cerialized_string ) );
  
  VALUE  rb_unpacked_string  =  Rcerialize_unpackRubyString( cerialized_string );
  SHOULD_EQUAL( rb_str_cmp( rb_unpacked_string, rb_string ), 0 );
  
  END_IT
END_DESCRIBE

/*********************
*  packRubySymbol    *
*  unpackRubySymbol  *
*********************/

DESCRIBE( Rcerialize_pack_unpack_Symbol, "\n * Rcerialize_packRubySymbol( VALUE rb_symbol )\n * Rcerialize_unpackRubySymbol( CerializedData* cerialized_data )" )
  IT( "can pack and unpack a symbol" )

  VALUE  rb_symbol  =  ID2SYM( rb_intern( "ruby symbol" ) );
  CerializedData*  cerialized_symbol  =  Rcerialize_packRubySymbol( rb_symbol );  
  SHOULD_NOT_BE_NULL( cerialized_symbol->data );
  SHOULD_EQUAL( cerialized_symbol->size, RSTRING_LEN( rb_obj_as_string( rb_symbol ) ) + 1 + sizeof( CerializedTypeFooter ) );
  SHOULD_EQUAL( *cerialized_symbol->type, CerializeType_Symbol );
  SHOULD_BE_FALSE( CerializedData_internal_hasDataFooter( cerialized_symbol ) );
  SHOULD_BE_TRUE( CerializedData_internal_hasTypeFooter( cerialized_symbol ) );

  VALUE  rb_unpacked_symbol  =  Rcerialize_unpackRubySymbol( cerialized_symbol );
  SHOULD_EQUAL( SYM2ID( rb_unpacked_symbol ), SYM2ID( rb_symbol ) );
  
  END_IT
END_DESCRIBE

/************************
*  packRubyClassName    *
*  unpackRubyClassName  *
************************/

DESCRIBE( Rcerialize_pack_unpack_ClassName, "\n * Rcerialize_packRubyClassName( VALUE rb_class )\n * Rcerialize_unpackRubyClassName( CerializedData* cerialized_data )" )
  IT( "can pack and unpack the name from the instance of a class" )

  VALUE  rb_class  =  rb_cObject;
  CerializedData*  cerialized_class  =  Rcerialize_packRubyClassName( rb_class );  
  SHOULD_NOT_BE_NULL( cerialized_class->data );
  SHOULD_EQUAL( cerialized_class->size, RSTRING_LEN( rb_obj_as_string( rb_class ) ) + 1 + sizeof( CerializedTypeFooter ) );
  SHOULD_EQUAL( *cerialized_class->type, CerializeType_ClassName );
  SHOULD_BE_FALSE( CerializedData_internal_hasDataFooter( cerialized_class ) );
  SHOULD_BE_TRUE( CerializedData_internal_hasTypeFooter( cerialized_class ) );

  VALUE  rb_unpacked_class  =  Rcerialize_unpackRubyClassName( cerialized_class );
  SHOULD_EQUAL( rb_unpacked_class, rb_class );
  
  END_IT
END_DESCRIBE

/**********************
*  packRubyInteger    *
*  unpackRubyInteger  *
**********************/

DESCRIBE( Rcerialize_pack_unpack_Integer, "\n * Rcerialize_packRubyInteger( VALUE rb_integer )\n * Rcerialize_unpackRubyInteger( CerializedData* cerialized_data )" )
  IT( "can pack and unpack an integer" )

  VALUE  rb_integer  =  INT2FIX( 42 );
  CerializedData*  cerialized_integer  =  Rcerialize_packRubyInteger( rb_integer );  
  SHOULD_NOT_BE_NULL( cerialized_integer->data );
  SHOULD_EQUAL( cerialized_integer->size, sizeof( long ) + sizeof( CerializedTypeFooter ) );
  SHOULD_EQUAL( *cerialized_integer->type, CerializeType_Integer );
  SHOULD_BE_FALSE( CerializedData_internal_hasDataFooter( cerialized_integer ) );
  SHOULD_BE_TRUE( CerializedData_internal_hasTypeFooter( cerialized_integer ) );

  VALUE  rb_unpacked_integer  =  Rcerialize_unpackRubyInteger( cerialized_integer );
  SHOULD_EQUAL( rb_unpacked_integer, rb_integer );

  //  we also need to try a BigNum
  VALUE  rb_big_integer  =  rb_cstr2inum( "100000000000000000000", 10 );
  CerializedData*  cerialized_big_integer  =  Rcerialize_packRubyInteger( rb_big_integer );  
  SHOULD_NOT_BE_NULL( cerialized_big_integer->data );
  SHOULD_EQUAL( cerialized_big_integer->size, ( strlen( "100000000000000000000" ) + 1 ) * sizeof( char ) + sizeof( CerializedTypeFooter ) );
  SHOULD_EQUAL( *cerialized_big_integer->type, CerializeType_BigInteger );
  SHOULD_BE_FALSE( CerializedData_internal_hasDataFooter( cerialized_big_integer ) );
  SHOULD_BE_TRUE( CerializedData_internal_hasTypeFooter( cerialized_big_integer ) );

  VALUE  rb_unpacked_big_integer  =  Rcerialize_unpackRubyBigInteger( cerialized_big_integer );
  SHOULD_EQUAL( rb_str_cmp( rb_big2str( rb_unpacked_big_integer, 10 ), rb_big2str( rb_big_integer, 10 ) ), 0 );
  
  END_IT
END_DESCRIBE

/********************
*  packRubyFloat    *
*  unpackRubyFloat  *
********************/

DESCRIBE( Rcerialize_pack_unpack_Float, "\n * Rcerialize_packRubyFloat( VALUE rb_float )\n * Rcerialize_unpackRubyFloat( CerializedData* cerialized_data )" )
  IT( "can pack and unpack a float" )

  VALUE  rb_float  =  DBL2NUM( 420.42 );
  CerializedData*  cerialized_float  =  Rcerialize_packRubyFloat( rb_float );  
  SHOULD_NOT_BE_NULL( cerialized_float->data );
  SHOULD_EQUAL( cerialized_float->size, sizeof( double ) + sizeof( CerializedTypeFooter ) );
  SHOULD_EQUAL( *cerialized_float->type, CerializeType_Float );
  SHOULD_BE_FALSE( CerializedData_internal_hasDataFooter( cerialized_float ) );
  SHOULD_BE_TRUE( CerializedData_internal_hasTypeFooter( cerialized_float ) );

  VALUE  rb_unpacked_float  =  Rcerialize_unpackRubyFloat( cerialized_float );
  SHOULD_EQUAL( NUM2DBL( rb_unpacked_float ), NUM2DBL( rb_float ) );
  
  END_IT
END_DESCRIBE

/*********************
*  packRubyRegexp    *
*  unpackRubyRegexp  *
*********************/

DESCRIBE( Rcerialize_pack_unpack_Regexp, "\n * Rcerialize_packRubyRegexp( VALUE rb_regexp )\n * Rcerialize_unpackRubyRegexp( CerializedData* cerialized_data )" )
  IT( "can pack and unpack a regular expression" )

  VALUE  rb_regexp  =  rb_eval_string( "/some ([A-Za-z]+)/" );
  CerializedData*  cerialized_regexp  =  Rcerialize_packRubyRegexp( rb_regexp );  
  SHOULD_NOT_BE_NULL( cerialized_regexp->data );
  SHOULD_EQUAL( cerialized_regexp->size, RSTRING_LEN( rb_funcall( rb_regexp, rb_intern( "source" ), 0 ) ) + 1 + sizeof( CerializedTypeFooter ) );
  SHOULD_EQUAL( *cerialized_regexp->type, CerializeType_Regexp );
  SHOULD_BE_FALSE( CerializedData_internal_hasDataFooter( cerialized_regexp ) );
  SHOULD_BE_TRUE( CerializedData_internal_hasTypeFooter( cerialized_regexp ) );

  VALUE  rb_unpacked_regexp  =  Rcerialize_unpackRubyRegexp( cerialized_regexp );
  SHOULD_EQUAL( rb_str_cmp( rb_funcall( rb_unpacked_regexp, rb_intern( "source" ), 0 ), rb_funcall( rb_regexp, rb_intern( "source" ), 0 ) ), 0 );
  
  END_IT
END_DESCRIBE

/***********************
*  packRubyFilePath    *
*  unpackRubyFilePath  *
***********************/

DESCRIBE( Rcerialize_pack_unpack_FilePath, "\n * Rcerialize_packRubyFilePath( VALUE rb_file )\n * Rcerialize_unpackRubyFilePath( CerializedData* cerialized_data )" )
  IT( "can pack and unpack a file as its path (path will be unpacked as Ruby File)" )

  VALUE  rb_file  =  rb_eval_string( "File.new( './' )" );
  CerializedData*  cerialized_file_path  =  Rcerialize_packRubyFilePath( rb_file );  
  SHOULD_NOT_BE_NULL( cerialized_file_path->data );
  SHOULD_EQUAL( cerialized_file_path->size, RSTRING_LEN( rb_funcall( rb_file, rb_intern( "path" ), 0 ) ) + 1 + sizeof( CerializedTypeFooter ) );
  SHOULD_EQUAL( *cerialized_file_path->type, CerializeType_FilePath );
  SHOULD_BE_FALSE( CerializedData_internal_hasDataFooter( cerialized_file_path ) );
  SHOULD_BE_TRUE( CerializedData_internal_hasTypeFooter( cerialized_file_path ) );

  VALUE  rb_unpacked_file_path  =  Rcerialize_unpackRubyFilePath( cerialized_file_path );
  SHOULD_EQUAL( rb_str_cmp( rb_funcall( rb_unpacked_file_path, rb_intern( "path" ), 0 ), rb_funcall( rb_file, rb_intern( "path" ), 0 ) ), 0 );
  
  END_IT
END_DESCRIBE

/***************************
*  packRubyFileContents    *
*  unpackRubyFileContents  *
***************************/

DESCRIBE( Rcerialize_pack_unpack_FileContents, "\n * Rcerialize_packRubyFileContents( VALUE rb_file )\n * Rcerialize_unpackRubyFileContents( CerializedData* cerialized_data )" )
  IT( "can pack and unpack a file as its contents (contents will be unpacked as a Ruby String)" )
  
  VALUE  rb_file_contents  =  rb_eval_string( "File.open( '/etc/passwd' )" );
  CerializedData*  cerialized_file_contents  =  Rcerialize_packRubyFileContents( rb_file_contents );  
  SHOULD_NOT_BE_NULL( cerialized_file_contents->data );
  //  reset file so we can get contents again to compare
  rb_file_contents  =  rb_eval_string( "File.open( '/etc/passwd' )" );
  VALUE  rb_file_contents_string  =  rb_funcall( rb_file_contents, rb_intern( "readlines" ), 0 );
  rb_file_contents_string  =  rb_funcall(  rb_file_contents_string, rb_intern( "join" ), 0 );
  uint32_t    c_string_length  =  RSTRING_LEN( rb_file_contents_string ) + 1 + sizeof( CerializedTypeFooter );
  SHOULD_EQUAL( cerialized_file_contents->size, c_string_length );
  SHOULD_EQUAL( *cerialized_file_contents->type, CerializeType_FileContents );
  SHOULD_BE_FALSE( CerializedData_internal_hasDataFooter( cerialized_file_contents ) );
  SHOULD_BE_TRUE( CerializedData_internal_hasTypeFooter( cerialized_file_contents ) );

  VALUE  rb_unpacked_contents        =  Rcerialize_unpackRubyFileContents( cerialized_file_contents );
  SHOULD_EQUAL( rb_str_cmp( rb_unpacked_contents, rb_file_contents_string ), 0 );
  
  END_IT
END_DESCRIBE

/**********************
*  packRubyComplex    *
*  unpackRubyComplex  *
**********************/

DESCRIBE( Rcerialize_pack_unpack_Complex, "\n * Rcerialize_packRubyComplex( VALUE rb_complex )\n * Rcerialize_unpackRubyComplex( CerializedData* cerialized_data )" )
  IT( "can pack and unpack a complex number" )

  VALUE  rb_complex  =  rb_complex_raw( DBL2NUM( 420.42 ), DBL2NUM( 42.420 ) );
  CerializedData*  cerialized_complex  =  Rcerialize_packRubyComplex( rb_complex );  
  SHOULD_NOT_BE_NULL( cerialized_complex->data );
  SHOULD_EQUAL( cerialized_complex->size, sizeof( CerializeStorage_Complex ) + sizeof( CerializedTypeFooter ) );
  SHOULD_EQUAL( *cerialized_complex->type, CerializeType_Complex );
  SHOULD_BE_FALSE( CerializedData_internal_hasDataFooter( cerialized_complex ) );
  SHOULD_BE_TRUE( CerializedData_internal_hasTypeFooter( cerialized_complex ) );

  VALUE  rb_unpacked_complex  =  Rcerialize_unpackRubyComplex( cerialized_complex );
  VALUE  rb_first_real          =  rb_funcall( rb_unpacked_complex, rb_intern( "real" ), 0 );
  VALUE  rb_second_real        =  rb_funcall( rb_complex, rb_intern( "real" ), 0 );
  VALUE  rb_first_imaginary    =  rb_funcall( rb_unpacked_complex, rb_intern( "imaginary" ), 0 );
  VALUE  rb_second_imaginary    =  rb_funcall( rb_complex, rb_intern( "imaginary" ), 0 );
  SHOULD_EQUAL( NUM2DBL( rb_first_real ), NUM2DBL( rb_second_real ) );
  SHOULD_EQUAL( NUM2DBL( rb_first_imaginary ), NUM2DBL( rb_second_imaginary ) );
  
  END_IT
END_DESCRIBE

/***********************
*  packRubyRational    *
*  unpackRubyRational  *
***********************/

DESCRIBE( Rcerialize_pack_unpack_Rational, "\n * Rcerialize_packRubyRational( VALUE rb_rational )\n * Rcerialize_unpackRubyRational( CerializedData* cerialized_data )" )
  IT( "can pack and unpack a rational number" )

  VALUE  rb_rational  =  rb_rational_raw( DBL2NUM( 1 ), DBL2NUM( 2 ) );
  CerializedData*  cerialized_rational  =  Rcerialize_packRubyRational( rb_rational );  
  SHOULD_NOT_BE_NULL( cerialized_rational->data );
  SHOULD_EQUAL( cerialized_rational->size, sizeof( CerializeStorage_Rational ) + sizeof( CerializedTypeFooter ) );
  SHOULD_EQUAL( *cerialized_rational->type, CerializeType_Rational );
  SHOULD_BE_FALSE( CerializedData_internal_hasDataFooter( cerialized_rational ) );
  SHOULD_BE_TRUE( CerializedData_internal_hasTypeFooter( cerialized_rational ) );

  VALUE  rb_unpacked_rational  =  Rcerialize_unpackRubyRational( cerialized_rational );
  VALUE  rb_first_numerator    =  rb_funcall( rb_unpacked_rational, rb_intern( "numerator" ), 0 );
  VALUE  rb_second_numerator    =  rb_funcall( rb_rational, rb_intern( "numerator" ), 0 );
  VALUE  rb_first_denominator  =  rb_funcall( rb_unpacked_rational, rb_intern( "denominator" ), 0 );
  VALUE  rb_second_denominator  =  rb_funcall( rb_rational, rb_intern( "denominator" ), 0 );
  SHOULD_EQUAL( NUM2DBL( rb_first_numerator ), NUM2DBL( rb_second_numerator ) );
  SHOULD_EQUAL( NUM2DBL( rb_first_denominator ), NUM2DBL( rb_second_denominator ) );
  
  END_IT
END_DESCRIBE

/************************
*  packRubyTrueFalse    *
*  unpackRubyTrueFalse  *
************************/

DESCRIBE( Rcerialize_pack_unpack_TrueFalse, "\n * Rcerialize_packRubyTrueFalse( VALUE rb_true_false )\n * Rcerialize_unpackRubyTrueFalse( CerializedData* cerialized_data )" )
  IT( "can pack and unpack a true or false value" )

  //  TRUE
  VALUE  rb_true  =  Qtrue;
  CerializedData*  cerialized_true  =  Rcerialize_packRubyTrueFalse( rb_true );  
  SHOULD_NOT_BE_NULL( cerialized_true->data );
  SHOULD_EQUAL( cerialized_true->size, sizeof( BOOL ) + sizeof( CerializedTypeFooter ) );
  SHOULD_EQUAL( *cerialized_true->type, CerializeType_TrueFalse );
  SHOULD_BE_FALSE( CerializedData_internal_hasDataFooter( cerialized_true ) );
  SHOULD_BE_TRUE( CerializedData_internal_hasTypeFooter( cerialized_true ) );

  VALUE  rb_unpacked_true  =  Rcerialize_unpackRubyTrueFalse( cerialized_true );
  SHOULD_EQUAL( rb_unpacked_true, rb_true );

  //  FALSE
  VALUE  rb_false  =  Qfalse;
  CerializedData*  cerialized_false  =  Rcerialize_packRubyTrueFalse( rb_false );  
  SHOULD_NOT_BE_NULL( cerialized_false->data );
  SHOULD_EQUAL( cerialized_false->size, sizeof( BOOL ) + sizeof( CerializedTypeFooter ) );
  SHOULD_EQUAL( *cerialized_false->type, CerializeType_TrueFalse );
  SHOULD_BE_FALSE( CerializedData_internal_hasDataFooter( cerialized_false ) );
  SHOULD_BE_TRUE( CerializedData_internal_hasTypeFooter( cerialized_false ) );

  VALUE  rb_unpacked_false  =  Rcerialize_unpackRubyTrueFalse( cerialized_false );
  SHOULD_EQUAL( rb_unpacked_false, rb_false );
  
  END_IT
END_DESCRIBE

/********************
*  packRubyArray    *
*  unpackRubyArray  *
********************/

DESCRIBE( Rcerialize_pack_unpack_Array, "\n * Rcerialize_packRubyArray( VALUE rb_array )\n * Rcerialize_unpackRubyArray( CerializedData* cerialized_data )" )
  IT( "can pack and unpack an array" )

  VALUE  rb_array  =  rb_ary_new();
  
  VALUE  rb_member_one      =  rb_str_new2( "string" );
  VALUE  rb_member_two      =  ID2SYM( rb_intern( "symbol" ) );
  VALUE  rb_member_three    =  INT2FIX( 42 );
  
  rb_ary_push( rb_array, rb_member_one );
  rb_ary_push( rb_array, rb_member_two );
  rb_ary_push( rb_array, rb_member_three );
  
  CerializedData*  cerialized_array  =  Rcerialize_packRubyArray( rb_array );  
  SHOULD_NOT_BE_NULL( cerialized_array->data );

  uint32_t    c_size_of_string  =  RSTRING_LEN( rb_member_one ) + 1 + sizeof( CerializedTypeFooter );
  uint32_t    c_size_of_symbol  =  RSTRING_LEN( rb_obj_as_string( rb_member_two ) ) + 1 + sizeof( CerializedTypeFooter );
  uint32_t    c_size_of_int      =  sizeof( long ) + sizeof( CerializedTypeFooter );

  uint32_t    c_total_element_sizes      =  c_size_of_string + c_size_of_symbol + c_size_of_int + ( 3 * sizeof( uint32_t ) );
  uint32_t    c_total_size              =  c_total_element_sizes + sizeof( CerializedTypeFooter );

  SHOULD_EQUAL( cerialized_array->size, c_total_size );
  SHOULD_EQUAL( *cerialized_array->type, CerializeType_Array );
  SHOULD_BE_FALSE( CerializedData_internal_hasDataFooter( cerialized_array ) );
  SHOULD_BE_TRUE( CerializedData_internal_hasTypeFooter( cerialized_array ) );

  VALUE  rb_unpacked_array  =  Rcerialize_unpackRubyArray( cerialized_array );
  SHOULD_EQUAL( rb_ary_cmp( rb_unpacked_array, rb_array ), INT2FIX( 0 ) );
  
  END_IT
END_DESCRIBE

/**************************
*  packRubyKeyDataPair    *
*  unpackRubyKeyDataPair  *
**************************/

DESCRIBE( Rcerialize_pack_key_data_pair, "\n * Rcerialize_packRubyKeyDataPair( VALUE rb_key, VALUE rb_data )" )
  IT( "can pack a key/data pair (for a hash or named struct)" )

  VALUE  rb_key      =  rb_str_new2( "string" );
  VALUE  rb_data      =  ID2SYM( rb_intern( "symbol" ) );

  CerializedData*  cerialized_key_data_pair  =  Rcerialize_packRubyKeyDataPair( rb_key, rb_data );  
  SHOULD_NOT_BE_NULL( cerialized_key_data_pair->data );

  uint32_t    c_size_of_string  =  RSTRING_LEN( rb_key ) + 1 + sizeof( CerializedTypeFooter );
  uint32_t    c_size_of_symbol  =  RSTRING_LEN( rb_obj_as_string( rb_data ) ) + 1 + sizeof( CerializedTypeFooter );

  uint32_t    c_total_element_sizes      =  c_size_of_string + c_size_of_symbol + ( 3 * sizeof( uint32_t ) );
  uint32_t    c_total_size              =  c_total_element_sizes + sizeof( CerializedTypeFooter );

  SHOULD_EQUAL( cerialized_key_data_pair->size, c_total_size );
  SHOULD_EQUAL( *cerialized_key_data_pair->type, CerializeType_KeyDataPair );
  SHOULD_BE_FALSE( CerializedData_internal_hasDataFooter( cerialized_key_data_pair ) );
  SHOULD_BE_TRUE( CerializedData_internal_hasTypeFooter( cerialized_key_data_pair ) );

  RcerializeKeyDataReturn*  c_key_data  =  Rcerialize_unpackRubyKeyDataPair( cerialized_key_data_pair );
  VALUE   rb_unpacked_key      = c_key_data->rb_key;
  VALUE   rb_unpacked_data     = c_key_data->rb_data;
  SHOULD_EQUAL( rb_str_cmp( rb_unpacked_key, rb_key ), 0 );
  SHOULD_EQUAL( SYM2ID( rb_unpacked_data ), SYM2ID( rb_data ) );
  
  END_IT
END_DESCRIBE

/*******************
*  packRubyHash    *
*  unpackRubyHash  *
*******************/

DESCRIBE( Rcerialize_pack_unpack_hash, "\n * Rcerialize_packRubyHash( VALUE rb_hash )\n * Rcerialize_unpackRubyHash( CerializedData* cerialized_data )" )
  IT( "can pack and unpack a hash" )

  VALUE  rb_member_one      =  rb_str_new2( "string" );
  VALUE  rb_member_two      =  ID2SYM( rb_intern( "symbol" ) );
  VALUE  rb_member_three    =  INT2FIX( 42 );

  VALUE  rb_key_one        =  ID2SYM( rb_intern( "key_one" ) );
  VALUE  rb_key_two        =  ID2SYM( rb_intern( "key_two" ) );
  VALUE  rb_key_three      =  ID2SYM( rb_intern( "key_three" ) );

  VALUE  rb_hash            =  rb_hash_new();
  rb_hash_aset(  rb_hash,
                rb_key_one,
                rb_member_one );
  rb_hash_aset(  rb_hash,
                rb_key_two,
                rb_member_two );
  rb_hash_aset(  rb_hash,
                rb_key_three,
                rb_member_three );

  CerializedData*  cerialized_hash  =  Rcerialize_packRubyHash( rb_hash );  
  SHOULD_NOT_BE_NULL( cerialized_hash->data );

  uint32_t    c_size_of_string    =  RSTRING_LEN( rb_member_one ) + 1 + sizeof( CerializedTypeFooter );
  uint32_t    c_size_of_symbol    =  RSTRING_LEN( rb_obj_as_string( rb_member_two ) ) + 1 + sizeof( CerializedTypeFooter );
  uint32_t    c_size_of_int        =  sizeof( long ) + sizeof( CerializedTypeFooter );

  uint32_t    c_size_of_key_one    =  RSTRING_LEN( rb_obj_as_string( rb_key_one ) ) + 1 + sizeof( CerializedTypeFooter );
  uint32_t    c_size_of_key_two    =  RSTRING_LEN( rb_obj_as_string( rb_key_two ) ) + 1 + sizeof( CerializedTypeFooter );
  uint32_t    c_size_of_key_three  =  RSTRING_LEN( rb_obj_as_string( rb_key_three ) ) + 1 + sizeof( CerializedTypeFooter );

  uint32_t    c_total_element_sizes      =  c_size_of_string + c_size_of_symbol + c_size_of_int + c_size_of_key_one + c_size_of_key_two + c_size_of_key_three + ( 9 * sizeof( uint32_t ) ) + ( 2 * sizeof( CerializedTypeFooter ) );
  uint32_t    c_total_size              =  c_total_element_sizes + sizeof( CerializedTypeFooter );

  SHOULD_EQUAL( cerialized_hash->size, c_total_size );
  SHOULD_EQUAL( *cerialized_hash->type, CerializeType_Hash );
  SHOULD_BE_FALSE( CerializedData_internal_hasDataFooter( cerialized_hash ) );
  SHOULD_BE_TRUE( CerializedData_internal_hasTypeFooter( cerialized_hash ) );

  VALUE  rb_unpacked_hash  =  Rcerialize_unpackRubyHash( cerialized_hash );
  SHOULD_EQUAL( rb_funcall( rb_unpacked_hash, rb_intern( "==" ), 1, rb_hash ), Qtrue );
  
  END_IT
END_DESCRIBE

/*********************
*  packRubyStruct    *
*  unpackRubyStruct  *
*********************/

DESCRIBE( Rcerialize_pack_unpack_struct, "\n * Rcerialize_packRubyStruct( VALUE rb_named_struct )\n * Rcerialize_unpackRubyStruct( CerializedData* cerialized_data, rb_load_as_class )" )
  IT( "can pack and unpack a struct using only data" )

  VALUE  rb_member_one      =  rb_str_new2( "string" );
  VALUE  rb_member_two      =  ID2SYM( rb_intern( "symbol" ) );
  VALUE  rb_member_three    =  INT2FIX( 42 );

  VALUE  rb_struct_class    =  rb_struct_define( "RCerializeSpecStruct", "key_one", "key_two", "key_three", NULL );
  VALUE  rb_struct          =  rb_struct_new( rb_struct_class, rb_member_one, rb_member_two, rb_member_three );

  CerializedData*  cerialized_struct  =  Rcerialize_packRubyStruct( rb_struct );  
  SHOULD_NOT_BE_NULL( cerialized_struct->data );

  uint32_t    c_size_of_string    =  RSTRING_LEN( rb_member_one ) + 1 + sizeof( CerializedTypeFooter );
  uint32_t    c_size_of_symbol    =  RSTRING_LEN( rb_obj_as_string( rb_member_two ) ) + 1 + sizeof( CerializedTypeFooter );
  uint32_t    c_size_of_int        =  sizeof( long ) + sizeof( CerializedTypeFooter );

  uint32_t    c_total_element_sizes      =  c_size_of_string + c_size_of_symbol + c_size_of_int + ( 3 * sizeof( uint32_t ) );
  uint32_t    c_total_size              =  c_total_element_sizes + sizeof( CerializedTypeFooter );

  SHOULD_EQUAL( cerialized_struct->size, c_total_size );
  SHOULD_EQUAL( *cerialized_struct->type, CerializeType_Struct );
  SHOULD_BE_FALSE( CerializedData_internal_hasDataFooter( cerialized_struct ) );
  SHOULD_BE_TRUE( CerializedData_internal_hasTypeFooter( cerialized_struct ) );

  VALUE  rb_unpacked_struct  =  Rcerialize_unpackRubyStruct(  cerialized_struct,
                                                            rb_struct_class );
  SHOULD_EQUAL( rb_funcall( rb_unpacked_struct, rb_intern( "==" ), 1, rb_struct ), Qtrue );
  
  END_IT
END_DESCRIBE

/**************************
*  packNamedRubyStruct    *
*  unpackRubyNamedStruct  *
**************************/

DESCRIBE( Rcerialize_pack_unpack_named_struct, "\n * Rcerialize_packNamedRubyStruct( VALUE rb_struct )\n * Rcerialize_unpackRubyNamedStruct( CerializedData* cerialized_data, rb_load_as_class )" )
  IT( "can pack and unpack a struct using named key => data pairs" )

  VALUE  rb_member_one      =  rb_str_new2( "string" );
  VALUE  rb_member_two      =  ID2SYM( rb_intern( "symbol" ) );
  VALUE  rb_member_three    =  INT2FIX( 42 );

  VALUE  rb_key_one        =  ID2SYM( rb_intern( "key_one" ) );
  VALUE  rb_key_two        =  ID2SYM( rb_intern( "key_two" ) );
  VALUE  rb_key_three      =  ID2SYM( rb_intern( "key_three" ) );

  VALUE  rb_struct_class    =  rb_struct_define( "RCerializeSpecNamedStruct", "key_one", "key_two", "key_three", NULL );
  VALUE  rb_struct          =  rb_struct_new( rb_struct_class, rb_member_one, rb_member_two, rb_member_three );

  CerializedData*  cerialized_struct  =  Rcerialize_packRubyNamedStruct( rb_struct );  
  SHOULD_NOT_BE_NULL( cerialized_struct->data );

  uint32_t    c_size_of_string    =  RSTRING_LEN( rb_member_one ) + 1 + sizeof( CerializedTypeFooter );
  uint32_t    c_size_of_symbol    =  RSTRING_LEN( rb_obj_as_string( rb_member_two ) ) + 1 + sizeof( CerializedTypeFooter );
  uint32_t    c_size_of_int        =  sizeof( long ) + sizeof( CerializedTypeFooter );

  uint32_t    c_size_of_key_one    =  RSTRING_LEN( rb_obj_as_string( rb_key_one ) ) + 1 + sizeof( CerializedTypeFooter );
  uint32_t    c_size_of_key_two    =  RSTRING_LEN( rb_obj_as_string( rb_key_two ) ) + 1 + sizeof( CerializedTypeFooter );
  uint32_t    c_size_of_key_three  =  RSTRING_LEN( rb_obj_as_string( rb_key_three ) ) + 1 + sizeof( CerializedTypeFooter );

  uint32_t    c_total_element_sizes      =  c_size_of_string + c_size_of_symbol + c_size_of_int + c_size_of_key_one + c_size_of_key_two + c_size_of_key_three + ( 9 * sizeof( uint32_t ) ) + ( 2 * sizeof( CerializedTypeFooter ) );
  uint32_t    c_total_size              =  c_total_element_sizes + sizeof( CerializedTypeFooter );

  SHOULD_EQUAL( cerialized_struct->size, c_total_size );
  SHOULD_EQUAL( *cerialized_struct->type, CerializeType_NamedStruct );
  SHOULD_BE_FALSE( CerializedData_internal_hasDataFooter( cerialized_struct ) );
  SHOULD_BE_TRUE( CerializedData_internal_hasTypeFooter( cerialized_struct ) );
  
  VALUE  rb_unpacked_named_struct  =  Rcerialize_unpackRubyNamedStruct( cerialized_struct,
                                                                      rb_struct_class );
  SHOULD_EQUAL( rb_funcall( rb_unpacked_named_struct, rb_intern( "==" ), 1, rb_struct ), Qtrue );
  
  END_IT
END_DESCRIBE

/***********************
*  packRubyInstance    *
*  unpackRubyInstance  *
***********************/

DESCRIBE( Rcerialize_pack_unpack_Instance, "\n * Rcerialize_packRubyInstance( VALUE rb_supported_object )\n * Rcerialize_unpackRubyInstance( CerializedData* cerialized_data )" )
  IT( "can pack and unpack any supported ruby instance (basic objects without internal variables, hashes, arrays, structs)" )

  //  With Type Footer
  
    VALUE rb_string         = rb_str_new2( "string" );
    VALUE rb_symbol         = ID2SYM( rb_intern( "symbol" ) );
    VALUE rb_class          = rb_cObject;
    VALUE rb_integer        = INT2FIX( 42 );
    VALUE rb_float          = DBL2NUM( 42.0 );
    VALUE rb_regexp         = rb_eval_string( "/some ([A-Za-z]+)/" );
    VALUE rb_file_path      = rb_eval_string( "File.new( './' )" );
    VALUE rb_file_contents  = rb_eval_string( "File.open( '/etc/passwd' )" );
      VALUE  rb_file_contents_string  =  rb_funcall( rb_funcall( rb_file_contents, rb_intern( "readlines" ), 0 ), rb_intern( "join" ), 0 );
    VALUE rb_complex        = rb_complex_raw( DBL2NUM( 420.42 ), DBL2NUM( 42.420 ) );
      VALUE  rb_real            =  rb_funcall( rb_complex, rb_intern( "real" ), 0 );
      VALUE  rb_imaginary       =  rb_funcall( rb_complex, rb_intern( "imaginary" ), 0 );
    VALUE rb_rational       = rb_rational_raw( DBL2NUM( 1 ), DBL2NUM( 2 ) );
      VALUE  rb_numerator       =  rb_funcall( rb_rational, rb_intern( "numerator" ), 0 );
      VALUE  rb_denominator     =  rb_funcall( rb_rational, rb_intern( "denominator" ), 0 );
    VALUE rb_true_false     = Qtrue;
    VALUE rb_array          = rb_ary_new();
      rb_ary_push( rb_array, rb_string );
      rb_ary_push( rb_array, rb_symbol );
      rb_ary_push( rb_array, rb_integer );
    VALUE rb_hash           = rb_hash_new();
      rb_hash_aset( rb_hash, rb_string, rb_symbol );
      rb_hash_aset( rb_hash, rb_class, rb_integer );
      rb_hash_aset( rb_hash, rb_float, rb_regexp );
    VALUE  rb_struct_class    =  rb_struct_define( "RCerializeSpecInstanceStruct", "key_one", "key_two", "key_three", NULL );
      VALUE rb_member_one   = rb_string;
      VALUE rb_member_two   = rb_symbol;
      VALUE rb_member_three = rb_integer;
      VALUE  rb_struct        =  rb_struct_new( rb_struct_class, rb_member_one, rb_member_two, rb_member_three );

    //  String
    CerializedData*   c_packed_string_wtf               =   Rcerialize_packRubyInstance(    rb_string,
                                                                                            CerializeType_String,
                                                                                            TRUE );
    VALUE             rb_unpacked_string_wtf            =   Rcerialize_unpackRubyInstance(  c_packed_string_wtf,
                                                                                            Qnil );
    SHOULD_EQUAL( rb_str_cmp( rb_unpacked_string_wtf, rb_string ), 0 );
    SHOULD_BE_TRUE( CerializedData_internal_hasTypeFooter( c_packed_string_wtf ) );
    
    //  Symbol
    CerializedData*   c_packed_symbol_wtf               =   Rcerialize_packRubyInstance(    rb_symbol,
                                                                                            CerializeType_Symbol,
                                                                                            TRUE );
    VALUE             rb_unpacked_symbol_wtf            =   Rcerialize_unpackRubyInstance(  c_packed_symbol_wtf,
                                                                                            Qnil   );
    SHOULD_EQUAL( SYM2ID( rb_unpacked_symbol_wtf ), SYM2ID( rb_symbol ) );
    SHOULD_BE_TRUE( CerializedData_internal_hasTypeFooter( c_packed_symbol_wtf ) );
    
    //  ClassName
    CerializedData*   c_packed_class_wtf                =   Rcerialize_packRubyInstance(    rb_class,
                                                                                            CerializeType_ClassName,
                                                                                            TRUE );
    VALUE             rb_unpacked_class_wtf             =   Rcerialize_unpackRubyInstance(  c_packed_class_wtf,
                                                                                            Qnil   );
    SHOULD_EQUAL( rb_unpacked_class_wtf, rb_class );
    SHOULD_BE_TRUE( CerializedData_internal_hasTypeFooter( c_packed_class_wtf ) );
    
    //  Integer
    CerializedData*   c_packed_integer_wtf              =   Rcerialize_packRubyInstance(    rb_integer,
                                                                                            CerializeType_Integer,
                                                                                            TRUE );
    VALUE             rb_unpacked_integer_wtf           =   Rcerialize_unpackRubyInstance(  c_packed_integer_wtf,
                                                                                            Qnil   );
    SHOULD_EQUAL( FIX2INT( rb_unpacked_integer_wtf ), FIX2INT( rb_integer ) );
    SHOULD_BE_TRUE( CerializedData_internal_hasTypeFooter( c_packed_integer_wtf ) );
    
    //  Float
    CerializedData*   c_packed_float_wtf                =   Rcerialize_packRubyInstance(    rb_float,
                                                                                            CerializeType_Float,
                                                                                            TRUE );
    VALUE             rb_unpacked_float_wtf             =   Rcerialize_unpackRubyInstance(  c_packed_float_wtf,
                                                                                            Qnil   );
    SHOULD_EQUAL( NUM2DBL( rb_unpacked_float_wtf ), NUM2DBL( rb_float ) );
    SHOULD_BE_TRUE( CerializedData_internal_hasTypeFooter( c_packed_float_wtf ) );
    
    //  Regexp
    CerializedData*   c_packed_regexp_wtf               =   Rcerialize_packRubyInstance(    rb_regexp,
                                                                                            CerializeType_Regexp,
                                                                                            TRUE );
    VALUE             rb_unpacked_regexp_wtf            =   Rcerialize_unpackRubyInstance(  c_packed_regexp_wtf,
                                                                                            Qnil   );
    SHOULD_EQUAL( rb_str_cmp( rb_funcall( rb_unpacked_regexp_wtf, rb_intern( "source" ), 0 ), rb_funcall( rb_regexp, rb_intern( "source" ), 0 ) ), 0 );
    SHOULD_BE_TRUE( CerializedData_internal_hasTypeFooter( c_packed_regexp_wtf ) );
    
    //  Filepath
    CerializedData*   c_packed_file_path_wtf            =   Rcerialize_packRubyInstance(    rb_file_path,
                                                                                            CerializeType_FilePath,
                                                                                            TRUE );
    VALUE             rb_unpacked_file_path_wtf         =   Rcerialize_unpackRubyInstance(  c_packed_file_path_wtf,
                                                                                            Qnil   );
    SHOULD_EQUAL( rb_str_cmp( rb_funcall( rb_unpacked_file_path_wtf, rb_intern( "path" ), 0 ), rb_funcall( rb_file_path, rb_intern( "path" ), 0 ) ), 0 );
    SHOULD_BE_TRUE( CerializedData_internal_hasTypeFooter( c_packed_file_path_wtf ) );
    
    //  FileContents
    //  reset file for contents
    rb_file_contents  = rb_eval_string( "File.open( '/etc/passwd' )" );
    CerializedData*   c_packed_file_contents_wtf        =   Rcerialize_packRubyInstance(    rb_file_contents,
                                                                                            CerializeType_FileContents,
                                                                                            TRUE );
    VALUE             rb_unpacked_file_contents_wtf     =   Rcerialize_unpackRubyInstance(  c_packed_file_contents_wtf,
                                                                                            Qnil   );
    SHOULD_EQUAL( rb_str_cmp( rb_unpacked_file_contents_wtf, rb_file_contents_string ), 0 );
    SHOULD_BE_TRUE( CerializedData_internal_hasTypeFooter( c_packed_file_contents_wtf ) );
    
    //  Complex
    CerializedData*   c_packed_complex_wtf              =   Rcerialize_packRubyInstance(    rb_complex,
                                                                                            CerializeType_Complex,
                                                                                            TRUE );
    VALUE rb_unpacked_complex_wtf                       =   Rcerialize_unpackRubyInstance(  c_packed_complex_wtf,
                                                                                            Qnil   );
    VALUE  rb_unpacked_real_wtf             =  rb_funcall( rb_unpacked_complex_wtf, rb_intern( "real" ), 0 );
    VALUE  rb_unpacked_imaginary_wtf        =  rb_funcall( rb_unpacked_complex_wtf, rb_intern( "imaginary" ), 0 );
    SHOULD_EQUAL( NUM2DBL( rb_unpacked_real_wtf ), NUM2DBL( rb_real ) );
    SHOULD_EQUAL( NUM2DBL( rb_unpacked_imaginary_wtf ), NUM2DBL( rb_imaginary ) );
    SHOULD_BE_TRUE( CerializedData_internal_hasTypeFooter( c_packed_complex_wtf ) );
    
    //  Rational
    CerializedData*   c_packed_rational_wtf             =   Rcerialize_packRubyInstance(    rb_rational,
                                                                                            CerializeType_Rational,
                                                                                            TRUE );
    VALUE rb_unpacked_rational_wtf                      =   Rcerialize_unpackRubyInstance(  c_packed_rational_wtf,
                                                                                            Qnil   );
    VALUE  rb_unpacked_numerator_wtf        =  rb_funcall( rb_unpacked_rational_wtf, rb_intern( "numerator" ), 0 );
    VALUE  rb_unpacked_denominator_wtf      =  rb_funcall( rb_unpacked_rational_wtf, rb_intern( "denominator" ), 0 );
    SHOULD_EQUAL( NUM2DBL( rb_unpacked_numerator_wtf ), NUM2DBL( rb_numerator ) );
    SHOULD_EQUAL( NUM2DBL( rb_unpacked_denominator_wtf ), NUM2DBL( rb_denominator ) );
    SHOULD_BE_TRUE( CerializedData_internal_hasTypeFooter( c_packed_rational_wtf ) );
    
    //  TrueFalse
    CerializedData*   c_packed_true_false_wtf           =   Rcerialize_packRubyInstance(    rb_true_false,
                                                                                            CerializeType_TrueFalse,
                                                                                            TRUE );
    VALUE             rb_unpacked_true_false_wtf        =   Rcerialize_unpackRubyInstance(  c_packed_true_false_wtf,
                                                                                            Qnil   );
    SHOULD_EQUAL( rb_unpacked_true_false_wtf, rb_true_false );
    SHOULD_BE_TRUE( CerializedData_internal_hasTypeFooter( c_packed_true_false_wtf ) );
    
    //  Array
    CerializedData*   c_packed_array_wtf                =   Rcerialize_packRubyInstance(    rb_array,
                                                                                            CerializeType_Array,
                                                                                            TRUE );
    VALUE             rb_unpacked_array_wtf             =   Rcerialize_unpackRubyInstance(  c_packed_array_wtf,
                                                                                            Qnil   );
    SHOULD_EQUAL( rb_ary_cmp( rb_unpacked_array_wtf, rb_array ), INT2FIX( 0 ) );
    SHOULD_BE_TRUE( CerializedData_internal_hasTypeFooter( c_packed_array_wtf ) );
    
    //  Hash
    CerializedData*   c_packed_hash_wtf                 =   Rcerialize_packRubyInstance(    rb_hash,
                                                                                            CerializeType_Hash,
                                                                                            TRUE );
    VALUE             rb_unpacked_hash_wtf              =   Rcerialize_unpackRubyInstance(  c_packed_hash_wtf,
                                                                                            Qnil   );
    SHOULD_EQUAL( rb_funcall( rb_unpacked_hash_wtf, rb_intern( "==" ), 1, rb_hash ), Qtrue );
    SHOULD_BE_TRUE( CerializedData_internal_hasTypeFooter( c_packed_hash_wtf ) );
    
    //  Struct
    CerializedData*   c_packed_struct_wtf               =   Rcerialize_packRubyInstance(    rb_struct,
                                                                                            CerializeType_Struct,
                                                                                            TRUE );
    VALUE             rb_unpacked_struct_wtf            =   Rcerialize_unpackRubyInstance(  c_packed_struct_wtf,
                                                                                            rb_struct_class   );
    SHOULD_EQUAL( rb_funcall( rb_unpacked_struct_wtf, rb_intern( "==" ), 1, rb_struct ), Qtrue );
    SHOULD_BE_TRUE( CerializedData_internal_hasTypeFooter( c_packed_struct_wtf ) );
    
    //  NamedStruct
    CerializedData*   c_packed_named_struct_wtf         =   Rcerialize_packRubyInstance(    rb_struct,
                                                                                            CerializeType_NamedStruct,
                                                                                            TRUE );
    VALUE             rb_unpacked_named_struct_wtf      =   Rcerialize_unpackRubyInstance(  c_packed_named_struct_wtf,
                                                                                            rb_struct_class   );
    SHOULD_EQUAL( rb_funcall( rb_unpacked_named_struct_wtf, rb_intern( "==" ), 1, rb_struct ), Qtrue );
    SHOULD_BE_TRUE( CerializedData_internal_hasTypeFooter( c_packed_named_struct_wtf ) );

  //  With Data Footer

    //  String
    CerializedData*   c_packed_string_wdf               =   Rcerialize_packRubyInstance(    rb_string,
                                                                                            CerializeType_String,
                                                                                            FALSE );
    VALUE             rb_unpacked_string_wdf            =   Rcerialize_unpackRubyInstance(  c_packed_string_wdf,
                                                                                            Qnil   );
    SHOULD_EQUAL( rb_str_cmp( rb_unpacked_string_wdf, rb_string ), 0 );
    SHOULD_BE_TRUE( CerializedData_internal_hasDataFooter( c_packed_string_wdf ) );
    SHOULD_NOT_BE_NULL( CerializedData_creationStamp( c_packed_string_wdf ) );
    SHOULD_NOT_BE_NULL( CerializedData_modificationStamp( c_packed_string_wdf ) );

    //  Symbol
    CerializedData*   c_packed_symbol_wdf               =   Rcerialize_packRubyInstance(    rb_symbol,
                                                                                            CerializeType_Symbol,
                                                                                            FALSE );
    VALUE             rb_unpacked_symbol_wdf            =   Rcerialize_unpackRubyInstance(  c_packed_symbol_wdf,
                                                                                            Qnil   );
    SHOULD_EQUAL( SYM2ID( rb_unpacked_symbol_wdf ), SYM2ID( rb_symbol ) );
    SHOULD_BE_TRUE( CerializedData_internal_hasDataFooter( c_packed_symbol_wdf ) );
    SHOULD_NOT_BE_NULL( CerializedData_creationStamp( c_packed_symbol_wdf ) );
    SHOULD_NOT_BE_NULL( CerializedData_modificationStamp( c_packed_symbol_wdf ) );

    //  ClassName
    CerializedData*   c_packed_class_wdf                =   Rcerialize_packRubyInstance(    rb_class,
                                                                                            CerializeType_ClassName,
                                                                                            FALSE );
    VALUE             rb_unpacked_class_wdf             =   Rcerialize_unpackRubyInstance(  c_packed_class_wdf,
                                                                                            Qnil   );
    SHOULD_EQUAL( rb_unpacked_class_wdf, rb_class );
    SHOULD_BE_TRUE( CerializedData_internal_hasDataFooter( c_packed_class_wdf ) );
    SHOULD_NOT_BE_NULL( CerializedData_creationStamp( c_packed_class_wdf ) );
    SHOULD_NOT_BE_NULL( CerializedData_modificationStamp( c_packed_class_wdf ) );

    //  Integer
    CerializedData*   c_packed_integer_wdf              =   Rcerialize_packRubyInstance(    rb_integer,
                                                                                            CerializeType_Integer,
                                                                                            FALSE );
    VALUE             rb_unpacked_integer_wdf           =   Rcerialize_unpackRubyInstance(  c_packed_integer_wdf,
                                                                                            Qnil   );
    SHOULD_EQUAL( FIX2INT( rb_unpacked_integer_wdf ), FIX2INT( rb_integer ) );
    SHOULD_BE_TRUE( CerializedData_internal_hasDataFooter( c_packed_integer_wdf ) );
    SHOULD_NOT_BE_NULL( CerializedData_creationStamp( c_packed_integer_wdf ) );
    SHOULD_NOT_BE_NULL( CerializedData_modificationStamp( c_packed_integer_wdf ) );

    //  Float
    CerializedData*   c_packed_float_wdf                =   Rcerialize_packRubyInstance(    rb_float,
                                                                                            CerializeType_Float,
                                                                                            FALSE );
    VALUE             rb_unpacked_float_wdf             =   Rcerialize_unpackRubyInstance(  c_packed_float_wdf,
                                                                                            Qnil   );
    SHOULD_EQUAL( NUM2DBL( rb_unpacked_float_wdf ), NUM2DBL( rb_float ) );
    SHOULD_BE_TRUE( CerializedData_internal_hasDataFooter( c_packed_float_wdf ) );
    SHOULD_NOT_BE_NULL( CerializedData_creationStamp( c_packed_float_wdf ) );
    SHOULD_NOT_BE_NULL( CerializedData_modificationStamp( c_packed_float_wdf ) );

    //  Regexp
    CerializedData*   c_packed_regexp_wdf               =   Rcerialize_packRubyInstance(    rb_regexp,
                                                                                            CerializeType_Regexp,
                                                                                            FALSE );
    VALUE             rb_unpacked_regexp_wdf            =   Rcerialize_unpackRubyInstance(  c_packed_regexp_wdf,
                                                                                            Qnil   );
    SHOULD_EQUAL( rb_str_cmp( rb_funcall( rb_unpacked_regexp_wdf, rb_intern( "source" ), 0 ), rb_funcall( rb_regexp, rb_intern( "source" ), 0 ) ), 0 );
    SHOULD_BE_TRUE( CerializedData_internal_hasDataFooter( c_packed_regexp_wdf ) );
    SHOULD_NOT_BE_NULL( CerializedData_creationStamp( c_packed_regexp_wdf ) );
    SHOULD_NOT_BE_NULL( CerializedData_modificationStamp( c_packed_regexp_wdf ) );


    //  Filepath
    CerializedData*   c_packed_file_path_wdf            =   Rcerialize_packRubyInstance(    rb_file_path,
                                                                                            CerializeType_FilePath,
                                                                                            FALSE );
    VALUE             rb_unpacked_file_path_wdf         =   Rcerialize_unpackRubyInstance(  c_packed_file_path_wdf,
                                                                                            Qnil   );
    SHOULD_EQUAL( rb_str_cmp( rb_funcall( rb_unpacked_file_path_wdf, rb_intern( "path" ), 0 ), rb_funcall( rb_file_path, rb_intern( "path" ), 0 ) ), 0 );
    SHOULD_BE_TRUE( CerializedData_internal_hasDataFooter( c_packed_file_path_wdf ) );
    SHOULD_NOT_BE_NULL( CerializedData_creationStamp( c_packed_file_path_wdf ) );
    SHOULD_NOT_BE_NULL( CerializedData_modificationStamp( c_packed_file_path_wdf ) );

    //  FileContents
    //  reset file for contents
    rb_file_contents  = rb_eval_string( "File.open( '/etc/passwd' )" );
    CerializedData*   c_packed_file_contents_wdf        =   Rcerialize_packRubyInstance(    rb_file_contents,
                                                                                            CerializeType_FileContents,
                                                                                            FALSE );
    VALUE             rb_unpacked_file_contents_wdf     =   Rcerialize_unpackRubyInstance(  c_packed_file_contents_wdf,
                                                                                            Qnil   );
    SHOULD_EQUAL( rb_str_cmp( rb_unpacked_file_contents_wdf, rb_file_contents_string ), 0 );
    SHOULD_BE_TRUE( CerializedData_internal_hasDataFooter( c_packed_file_contents_wdf ) );
    SHOULD_NOT_BE_NULL( CerializedData_creationStamp( c_packed_file_contents_wdf ) );
    SHOULD_NOT_BE_NULL( CerializedData_modificationStamp( c_packed_file_contents_wdf ) );


    //  Complex
    CerializedData*   c_packed_complex_wdf              =   Rcerialize_packRubyInstance(    rb_complex,
                                                                                            CerializeType_Complex,
                                                                                            FALSE );
    VALUE             rb_unpacked_complex_wdf           =   Rcerialize_unpackRubyInstance(  c_packed_complex_wdf,
                                                                                            Qnil   );
    VALUE  rb_unpacked_real_wdf             =  rb_funcall( rb_unpacked_complex_wdf, rb_intern( "real" ), 0 );
    VALUE  rb_unpacked_imaginary_wdf        =  rb_funcall( rb_unpacked_complex_wdf, rb_intern( "imaginary" ), 0 );
    SHOULD_EQUAL( NUM2DBL( rb_unpacked_real_wdf ), NUM2DBL( rb_real ) );
    SHOULD_EQUAL( NUM2DBL( rb_unpacked_imaginary_wdf ), NUM2DBL( rb_imaginary ) );
    SHOULD_BE_TRUE( CerializedData_internal_hasDataFooter( c_packed_complex_wdf ) );
    SHOULD_NOT_BE_NULL( CerializedData_creationStamp( c_packed_complex_wdf ) );
    SHOULD_NOT_BE_NULL( CerializedData_modificationStamp( c_packed_complex_wdf ) );

    //  Rational
    CerializedData*   c_packed_rational_wdf             =   Rcerialize_packRubyInstance(    rb_rational,
                                                                                            CerializeType_Rational,
                                                                                            FALSE );
    VALUE             rb_unpacked_rational_wdf          =   Rcerialize_unpackRubyInstance(  c_packed_rational_wdf,
                                                                                            Qnil   );
    VALUE  rb_unpacked_numerator_wdf        =  rb_funcall( rb_unpacked_rational_wdf, rb_intern( "numerator" ), 0 );
    VALUE  rb_unpacked_denominator_wdf      =  rb_funcall( rb_unpacked_rational_wdf, rb_intern( "denominator" ), 0 );
    SHOULD_EQUAL( NUM2DBL( rb_unpacked_numerator_wdf ), NUM2DBL( rb_numerator ) );
    SHOULD_EQUAL( NUM2DBL( rb_unpacked_denominator_wdf ), NUM2DBL( rb_denominator ) );
    SHOULD_BE_TRUE( CerializedData_internal_hasDataFooter( c_packed_rational_wdf ) );
    SHOULD_NOT_BE_NULL( CerializedData_creationStamp( c_packed_rational_wdf ) );
    SHOULD_NOT_BE_NULL( CerializedData_modificationStamp( c_packed_rational_wdf ) );

    //  TrueFalse
    CerializedData*   c_packed_true_false_wdf           =   Rcerialize_packRubyInstance(    rb_true_false,
                                                                                            CerializeType_TrueFalse,
                                                                                            FALSE );
    VALUE             rb_unpacked_true_false_wdf        =   Rcerialize_unpackRubyInstance(  c_packed_true_false_wdf,
                                                                                            Qnil   );
    SHOULD_EQUAL( rb_unpacked_true_false_wdf, rb_true_false );
    SHOULD_BE_TRUE( CerializedData_internal_hasDataFooter( c_packed_true_false_wdf ) );
    SHOULD_NOT_BE_NULL( CerializedData_creationStamp( c_packed_true_false_wdf ) );
    SHOULD_NOT_BE_NULL( CerializedData_modificationStamp( c_packed_true_false_wdf ) );

    //  Array
    CerializedData*   c_packed_array_wdf                =   Rcerialize_packRubyInstance(    rb_array,
                                                                                            CerializeType_Array,
                                                                                            FALSE );
    VALUE             rb_unpacked_array_wdf             =   Rcerialize_unpackRubyInstance(  c_packed_array_wdf,
                                                                                            Qnil   );
    SHOULD_EQUAL( rb_ary_cmp( rb_unpacked_array_wdf, rb_array ), INT2FIX( 0 ) );
    SHOULD_BE_TRUE( CerializedData_internal_hasDataFooter( c_packed_array_wdf ) );
    SHOULD_NOT_BE_NULL( CerializedData_creationStamp( c_packed_array_wdf ) );
    SHOULD_NOT_BE_NULL( CerializedData_modificationStamp( c_packed_array_wdf ) );

    //  Hash
    CerializedData*   c_packed_hash_wdf                 =   Rcerialize_packRubyInstance(    rb_hash,
                                                                                            CerializeType_Hash,
                                                                                            FALSE );
    VALUE             rb_unpacked_hash_wdf              =   Rcerialize_unpackRubyInstance(  c_packed_hash_wdf,
                                                                                            Qnil   );
    SHOULD_EQUAL( rb_funcall( rb_unpacked_hash_wdf, rb_intern( "==" ), 1, rb_hash ), Qtrue );
    SHOULD_BE_TRUE( CerializedData_internal_hasDataFooter( c_packed_hash_wdf ) );
    SHOULD_NOT_BE_NULL( CerializedData_creationStamp( c_packed_hash_wdf ) );
    SHOULD_NOT_BE_NULL( CerializedData_modificationStamp( c_packed_hash_wdf ) );

    //  Struct
    CerializedData*   c_packed_struct_wdf               =   Rcerialize_packRubyInstance(    rb_struct,
                                                                                            CerializeType_Struct,
                                                                                            FALSE );
    VALUE             rb_unpacked_struct_wdf            =   Rcerialize_unpackRubyInstance(  c_packed_struct_wdf,
                                                                                            rb_struct_class   );
    SHOULD_EQUAL( rb_funcall( rb_unpacked_struct_wdf, rb_intern( "==" ), 1, rb_struct ), Qtrue );
    SHOULD_BE_TRUE( CerializedData_internal_hasDataFooter( c_packed_struct_wdf ) );
    SHOULD_NOT_BE_NULL( CerializedData_creationStamp( c_packed_struct_wdf ) );
    SHOULD_NOT_BE_NULL( CerializedData_modificationStamp( c_packed_struct_wdf ) );

    //  NamedStruct
    CerializedData*   c_packed_named_struct_wdf         =   Rcerialize_packRubyInstance(    rb_struct,
                                                                                            CerializeType_NamedStruct,
                                                                                            FALSE );
    VALUE             rb_unpacked_named_struct_wdf      =   Rcerialize_unpackRubyInstance(  c_packed_named_struct_wdf,
                                                                                            rb_struct_class   );
    SHOULD_EQUAL( rb_funcall( rb_unpacked_named_struct_wdf, rb_intern( "==" ), 1, rb_struct ), Qtrue );
    SHOULD_BE_TRUE( CerializedData_internal_hasDataFooter( c_packed_named_struct_wdf ) );
    SHOULD_NOT_BE_NULL( CerializedData_creationStamp( c_packed_named_struct_wdf ) );
    SHOULD_NOT_BE_NULL( CerializedData_modificationStamp( c_packed_named_struct_wdf ) );

  END_IT
END_DESCRIBE

/**************************************************************************************************************/

/********************************************
*  Rcerialize_pack_unpack_pack_unpack_spec  *
********************************************/

void Rcerialize_pack_unpack_pack_unpack_spec( void )  {
  
  CSpec_Run( DESCRIPTION( Rcerialize_pack_unpack_String ), CSpec_NewOutputVerbose() );
  CSpec_Run( DESCRIPTION( Rcerialize_pack_unpack_Symbol ), CSpec_NewOutputVerbose() );
  CSpec_Run( DESCRIPTION( Rcerialize_pack_unpack_ClassName ), CSpec_NewOutputVerbose() );
  CSpec_Run( DESCRIPTION( Rcerialize_pack_unpack_Integer ), CSpec_NewOutputVerbose() );
  CSpec_Run( DESCRIPTION( Rcerialize_pack_unpack_Float ), CSpec_NewOutputVerbose() );
  CSpec_Run( DESCRIPTION( Rcerialize_pack_unpack_Regexp ), CSpec_NewOutputVerbose() );
  CSpec_Run( DESCRIPTION( Rcerialize_pack_unpack_FilePath ), CSpec_NewOutputVerbose() );
  CSpec_Run( DESCRIPTION( Rcerialize_pack_unpack_FileContents ), CSpec_NewOutputVerbose() );
  CSpec_Run( DESCRIPTION( Rcerialize_pack_unpack_Complex ), CSpec_NewOutputVerbose() );
  CSpec_Run( DESCRIPTION( Rcerialize_pack_unpack_Rational ), CSpec_NewOutputVerbose() );
  CSpec_Run( DESCRIPTION( Rcerialize_pack_unpack_TrueFalse ), CSpec_NewOutputVerbose() );

  CSpec_Run( DESCRIPTION( Rcerialize_pack_unpack_Array ), CSpec_NewOutputVerbose() );
  CSpec_Run( DESCRIPTION( Rcerialize_pack_key_data_pair ), CSpec_NewOutputVerbose() );

  CSpec_Run( DESCRIPTION( Rcerialize_pack_unpack_hash ), CSpec_NewOutputVerbose() );

  CSpec_Run( DESCRIPTION( Rcerialize_pack_unpack_struct ), CSpec_NewOutputVerbose() );
  CSpec_Run( DESCRIPTION( Rcerialize_pack_unpack_named_struct ), CSpec_NewOutputVerbose() );

  CSpec_Run( DESCRIPTION( Rcerialize_pack_unpack_Instance ), CSpec_NewOutputVerbose() );

}
