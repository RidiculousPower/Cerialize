#ifndef RCERIALIZE_UNPACK
  #define RCERIALIZE_UNPACK

  #include <cerialize.h>
  #include <ruby.h>  
  #include "rcerialize/rcerialize_type.h"

  VALUE Rcerialize_unpackRubyInstance(  CerializedData*      c_cerialized_data,
                                        VALUE                rb_load_as_class );
  VALUE Rcerialize_unpackRubyFilePath(  CerializedData*    c_cerialized_file_path );
  VALUE Rcerialize_unpackRubyFileContents(  CerializedData*    c_cerialized_file_contents );
  VALUE Rcerialize_unpackRubySymbol(  CerializedData*    c_cerialized_symbol );
  VALUE Rcerialize_unpackRubyRegexp(  CerializedData*    c_cerialized_regexp );
  VALUE Rcerialize_unpackRubyClassName(  CerializedData*    c_cerialized_class_name );
  VALUE Rcerialize_unpackRubyNil(  CerializedData*    c_cerialized_string );
  VALUE Rcerialize_unpackRubyString(  CerializedData*    c_cerialized_string );
  VALUE Rcerialize_unpackRubyComplex(  CerializedData*    c_cerialized_complex );
  VALUE Rcerialize_unpackRubyRational(  CerializedData*    c_cerialized_rational );
  VALUE Rcerialize_unpackRubyInteger(  CerializedData*    c_cerialized_integer );
  VALUE Rcerialize_unpackRubyBigInteger(  CerializedData*    c_cerialized_big_integer );
  VALUE Rcerialize_unpackRubyFloat(  CerializedData*    c_cerialized_float );
  VALUE Rcerialize_unpackRubyTrueFalse(  CerializedData*    c_cerialized_true_false );
  VALUE Rcerialize_unpackRubyHash(  CerializedData*    c_cerialized_hash );
  VALUE Rcerialize_unpackRubyArray(  CerializedData*    c_cerialized_array );
  VALUE Rcerialize_unpackRubyStruct(  CerializedData*    c_cerialized_struct,
                                      VALUE              rb_struct_class );
  VALUE Rcerialize_unpackRubyNamedStruct(  CerializedData*    c_cerialized_named_struct,
                                           VALUE              rb_struct_class  );
  RcerializeKeyDataReturn* Rcerialize_unpackRubyKeyDataPair(  CerializedData*    c_cerialized_key_data_pair );
  
#endif
