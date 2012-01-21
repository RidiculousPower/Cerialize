
#ifndef CERIALIZE_TYPES
  #define CERIALIZE_TYPES

  #define  RBDB_DATABASE_DATA_FOOTER_VERSION  1

  #include <stdint.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include "cerialize_macros.h"

  #ifndef BOOL
    typedef int BOOL;
  #endif
  #ifndef TRUE
    #define TRUE 1
  #endif
  #ifndef FALSE
    #define FALSE 0
  #endif
  
  typedef struct    CerializedData                            CerializedData;
  typedef struct    CerializedTypeFooter                      CerializedTypeFooter;
  typedef struct    CerializedDataFooter1                      CerializedDataFooter1;
  typedef  enum      CerializeType                              CerializeType;
  typedef  struct    CerializeStorage_Raw                      CerializeStorage_Raw;
  typedef  struct    CerializeStorage_Nil                      CerializeStorage_Nil;
  typedef  struct    CerializeStorage_Integer                  CerializeStorage_Integer;
  typedef  struct    CerializeStorage_BigInteger                CerializeStorage_BigInteger;
  typedef  struct    CerializeStorage_Float                    CerializeStorage_Float;
  typedef  struct    CerializeStorage_Complex                  CerializeStorage_Complex;
  typedef  struct    CerializeStorage_Rational                  CerializeStorage_Rational;
  typedef  struct    CerializeStorage_String                    CerializeStorage_String;
  typedef  struct    CerializeStorage_Symbol                    CerializeStorage_Symbol;
  typedef  struct    CerializeStorage_Regexp                    CerializeStorage_Regexp;
  typedef  struct    CerializeStorage_FilePath                  CerializeStorage_FilePath;
  typedef  struct    CerializeStorage_FileContents              CerializeStorage_FileContents;
  typedef  struct    CerializeStorage_TrueFalse                CerializeStorage_TrueFalse;
  typedef  struct    CerializeStorage_ClassName                CerializeStorage_ClassName;
  typedef  struct    CerializeStorage_Array                    CerializeStorage_Array;
  typedef  struct    CerializeStorage_Hash                      CerializeStorage_Hash;
  typedef  struct    CerializeStorage_NamedStruct              CerializeStorage_NamedStruct;
  typedef  struct    CerializeStorage_Struct                    CerializeStorage_Struct;
  typedef  struct    CerializeStorage_KeyDataPair              CerializeStorage_KeyDataPair;

  enum CerializeType  {
    
    CerializeType_Raw,
    CerializeType_Nil,
    CerializeType_Integer,
    CerializeType_BigInteger,
    CerializeType_Float,
    CerializeType_Complex,
    CerializeType_Rational,
    CerializeType_String,
    CerializeType_Symbol,
    CerializeType_Regexp,
    CerializeType_FilePath,
    CerializeType_FileContents,
    CerializeType_TrueFalse,
    CerializeType_ClassName,
    CerializeType_Array,
    CerializeType_Hash,
    CerializeType_NamedStruct,
    CerializeType_Struct,
    
    //  Not intended as public type
    CerializeType_KeyDataPair
    
  };

  struct CerializedData  {
    uint32_t                                                                            size;
    void*                                                                                data;
    BOOL                                                                                free_does_not_free_data;
    CerializeType*                                                                      type;
    CerializedData_DataFooterTypeForVersion( CerializedDataFooterCurrentVersion )*      footer;
  };

    struct GenericCerializedData  {
      
      uint32_t                                                                            size;
      void*                                                                                data;
      
    };

  struct CerializedTypeFooter  {

    CerializeType                      type;
    
    uint32_t                          magic_number[ 4 ];
    
  };

  struct CerializedDataFooter1  {
    
    struct timeval                    creation_stamp;
    struct timeval                    modification_stamp;

    CerializeType                      type;
    
    //  version needs to be last so we can look from the end to check
    int                                version;
    uint32_t                          magic_number[ 4 ];
    
  };

  struct CerializeStorage_Raw  {
  
    void*        raw;
  
  };

  struct CerializeStorage_Nil  {
  
    //  holds 1 char: '\0'
    char*        nil;
  
  };

  struct CerializeStorage_Integer  {
  
    long long    integer_value;
    
  };

  struct CerializeStorage_BigInteger  {
    
    //  digits[0] is "-" if negative
    char*   digits;
    
  };

  struct CerializeStorage_Float  {
  
    double  float_value;
  
  };

  struct CerializeStorage_Complex  {
  
    double  real;
    BOOL    real_is_float;
    double  imaginary;
    BOOL    imaginary_is_float;
  
  };

  struct CerializeStorage_Rational  {
  
    double  numerator;
    double  denominator;
  
  };

  struct CerializeStorage_String  {
    
    char*        string;
  
  };

  struct CerializeStorage_Symbol  {

    char*        string;
  
  };

  struct CerializeStorage_Regexp  {

    char*        string;
  
  };

  struct CerializeStorage_FilePath  {
  
    char*        filepath;
  
  };

  struct CerializeStorage_File  {
  
    FILE*        file;
  
  };

  struct CerializeStorage_TrueFalse  {
  
    BOOL        truefalse;
    
  };

  struct CerializeStorage_ClassName  {
  
    char*        string;
  
  };

  struct CerializeStorage_Array  {

    struct GenericCerializedData*  member_array;

  };

  struct CerializeStorage_Hash  {

    struct CerializeStorage_KeyValuePair*  key_value_pairs;

  };

  struct CerializeStorage_Struct  {

    struct GenericCerializedData*  members;
    
  };

  struct CerializeStorage_NamedStruct  {

    struct CerializeStorage_KeyValuePair*  key_value_pairs;

  };

  struct CerializeStorage_KeyValuePair  {
  
    struct GenericCerializedData  key;
    struct GenericCerializedData  value;
    
  };
  
#endif

