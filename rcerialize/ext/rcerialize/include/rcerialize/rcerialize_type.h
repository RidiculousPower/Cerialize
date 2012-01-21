#ifndef RCERIALIZE_TYPE
  #define RCERIALIZE_TYPE

  #include <cerialize.h>
  #include <ruby.h>

  CerializeType Rcerialize_storageTypeForRubyInstance(  VALUE    rb_object );
  CerializeType Rcerialize_storageTypeForRubyClass( VALUE rb_class );

  typedef struct RcerializeHashForeachInfo    RcerializeHashForeachInfo;
  typedef struct RcerializeKeyDataReturn      RcerializeKeyDataReturn;

  /******************
  *  foreach types  *
  ******************/
  
  struct RcerializeHashForeachInfo  {
    
    CerializedData**    c_cerialized_data;
    int                 count;
    uint32_t            total_size;
    
  };

  struct RcerializeKeyDataReturn  {
    
    VALUE               rb_key;
    VALUE               rb_data;

    uint32_t            c_total_iterated_size;

  };

#endif
