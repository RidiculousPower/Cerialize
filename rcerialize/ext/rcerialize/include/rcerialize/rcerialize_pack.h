#ifndef RCERIALIZE_PACK
	#define RCERIALIZE_PACK

	#include <cerialize.h>
	#include <ruby.h>	
	#include "rcerialize/rcerialize_type.h"

CerializedData* Rcerialize_packRubyInstance(	VALUE							rb_object,
																							CerializeType			c_storage_type,
																							BOOL							type_not_footer );

	CerializedData* Rcerialize_packRubyFileContents(	VALUE		rb_file );
	CerializedData* Rcerialize_packRubyFilePath(	VALUE		rb_file );
	CerializedData* Rcerialize_packRubySymbol(	VALUE		rb_symbol );
	CerializedData* Rcerialize_packRubyRegexp(	VALUE		rb_regexp );
	CerializedData* Rcerialize_packRubyClassName(	VALUE		rb_class );
	CerializedData* Rcerialize_packRubyString(	VALUE		rb_string );
	CerializedData* Rcerialize_packRubyComplex(	VALUE		rb_complex_number );
	CerializedData* Rcerialize_packRubyRational(	VALUE		rb_rational_number );
	CerializedData* Rcerialize_packRubyInteger(	VALUE		rb_integer );
	CerializedData* Rcerialize_packRubyFloat(	VALUE		rb_float );
	CerializedData* Rcerialize_packRubyTrueFalse(	VALUE		rb_true_false );
	CerializedData* Rcerialize_packRubyArray(	VALUE		rb_array );
	CerializedData* Rcerialize_packRubyHash(	VALUE		rb_hash );
	CerializedData* Rcerialize_packRubyStruct(	VALUE		rb_struct );
	CerializedData* Rcerialize_packRubyNamedStruct(	VALUE		rb_struct );
		CerializedData* Rcerialize_packRubyKeyDataPair(	VALUE		rb_key,
																										VALUE		rb_data );


#endif
