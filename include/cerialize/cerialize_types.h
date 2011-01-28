
#ifndef CERIALIZE_TYPES
	#define CERIALIZE_TYPES

	#define	RBDB_DATABASE_DATA_FOOTER_VERSION	1

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

	typedef struct CerializedData										CerializedData;
	
	typedef struct CerializedTypeFooter							CerializedTypeFooter;
	typedef struct CerializedDataFooter1						CerializedDataFooter1;
	typedef	enum   CerializeType										CerializeType;

	enum CerializeType	{
		
		CerializeType_Raw,
		CerializeType_Integer,
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
		CerializeType_KeyDataPair
		
	};
	
	struct CerializedData	{
		uint32_t																																							size;
		void*																																								data;
		CerializeType*																																			type;
		CerializedData_DataFooterTypeForVersion( CerializedDataFooterCurrentVersion )*			footer;
	};

		struct GenericCerializedData	{
			
			uint32_t																																						size;
			void*																																								data;
			
		};
		
	struct CerializedTypeFooter	{

		CerializeType											type;
		
		uint32_t*													magic_number;
		
	};

	struct CerializedDataFooter1	{
		
		struct timeval										creation_stamp;
		struct timeval										modification_stamp;

		CerializeType											type;
		
		//	version needs to be last so we can look from the end to check
		int																version;
		uint32_t													magic_number[ 4 ];
		
	};

	struct CerializeStorage_Raw	{
	
		void*				raw;
	
	};

	struct CerializeStorage_Integer	{
	
		long		integer_value;
		
	};

	struct CerializeStorage_Float	{
	
		double	float_value;
	
	};

	struct CerializeStorage_Complex	{
	
		double	real;
		double	imaginary;
	
	};

	struct CerializeStorage_Rational	{
	
		double	numerator;
		double	denominator;
	
	};

	struct CerializeStorage_String	{
		
		char*				string;
	
	};

	struct CerializeStorage_Symbol	{

		char*				string;
	
	};

	struct CerializeStorage_Regexp	{

		char*				string;
	
	};

	struct CerializeStorage_FilePath	{
	
		char*				filepath;
	
	};

	struct CerializeStorage_File	{
	
		FILE*				file;
	
	};

	struct CerializeStorage_TrueFalse	{
	
		BOOL				truefalse;
		
	};

	struct CerializeStorage_ClassName	{
	
		char*				string;
	
	};

	struct CerializeStorage_Array	{

		struct GenericCerializedData*	member_array;

	};

	struct CerializeStorage_Hash	{

		struct CerializeStorage_KeyValuePair*	key_value_pairs;

	};

	struct CerializeStorage_Struct	{

		struct GenericCerializedData*	members;
		
	};

	struct CerializeStorage_NamedStruct	{

		struct CerializeStorage_KeyValuePair*	key_value_pairs;

	};
	
	struct CerializeStorage_KeyValuePair	{
	
		struct GenericCerializedData	key;
		struct GenericCerializedData	value;
		
	};
	
#endif

