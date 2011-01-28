#ifndef RCERIALIZE_TYPE
	#define RCERIALIZE_TYPE

	#include <rbdb/CerializedData.h>
	#include <ruby.h>

	CerializeType Rcerialize_storageTypeForRubyInstance(	VALUE		rb_object );
	CerializeType Rcerialize_storageTypeForRubyClass( VALUE rb_class );

	typedef struct RcerializeHashForeachInfo RcerializeHashForeachInfo;

	/******************
	*  foreach types  *
	******************/
	
	struct RcerializeHashForeachInfo	{
		
		CerializedData**		c_cerialized_data;
		int									count;
		uint32_t						total_size;
		
	};

#endif
