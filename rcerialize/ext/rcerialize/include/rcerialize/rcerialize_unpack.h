#ifndef RCERIALIZE_UNPACK
	#define RCERIALIZE_UNPACK

	#include <rbdb/CerializedData.h>
	#include <rbdb/CerializedData_internal.h>
	#include <ruby.h>	
	#include "rcerialize/rcerialize_types.h"

	VALUE Rcerialize_unpackRubyInstance(	CerializedData*			c_cerialized_data,
																				VALUE								rb_load_as_class );
	VALUE Rcerialize_unpackRubyObjectForFilePath(	CerializedData*		c_cerialized_file_path );
	VALUE Rcerialize_unpackRubyObjectForFileContents(	CerializedData*		c_cerialized_file_contents );
	VALUE Rcerialize_unpackRubyObjectForSymbol(	CerializedData*		c_cerialized_symbol );
	VALUE Rcerialize_unpackRubyObjectForRegexp(	CerializedData*		c_cerialized_regexp );
	VALUE Rcerialize_unpackRubyObjectForClassName(	CerializedData*		c_cerialized_class_name );
	VALUE Rcerialize_unpackRubyObjectForString(	CerializedData*		c_cerialized_string );
	VALUE Rcerialize_unpackRubyObjectForComplex(	CerializedData*		c_cerialized_complex );
	VALUE Rcerialize_unpackRubyObjectForRational(	CerializedData*		c_cerialized_rational );
	VALUE Rcerialize_unpackRubyObjectForInteger(	CerializedData*		c_cerialized_integer );
	VALUE Rcerialize_unpackRubyObjectForFloat(	CerializedData*		c_cerialized_float );
	VALUE Rcerialize_unpackRubyObjectForTrueFalse(	CerializedData*		c_cerialized_true_false );
	VALUE Rcerialize_unpackRubyObjectForHash(	CerializedData*		c_cerialized_hash );
	VALUE Rcerialize_unpackRubyObjectForArray(	CerializedData*		c_cerialized_array );
	VALUE Rcerialize_unpackRubyObjectForStruct(	CerializedData*		c_cerialized_struct,
																							VALUE							rb_struct_class );
	VALUE Rcerialize_unpackRubyObjectForNamedStruct(	CerializedData*		c_cerialized_named_struct,
																										VALUE							rb_struct_class	);

#endif
