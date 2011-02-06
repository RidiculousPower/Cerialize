
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
	
	#ifndef CerializedData
	typedef struct CerializedData																CerializedData;
	#endif
	
	#ifndef CerializedTypeFooter
	typedef struct		CerializedTypeFooter											CerializedTypeFooter;
	#endif
	#ifndef CerializedDataFooter1
	typedef struct		CerializedDataFooter1											CerializedDataFooter1;
	#endif
	#ifndef CerializeType
	typedef	enum			CerializeType															CerializeType;
	#endif

	#ifndef CerializeStorage_Raw
	typedef	struct		CerializeStorage_Raw											CerializeStorage_Raw;
	#endif
	#ifndef CerializeStorage_Integer
	typedef	struct		CerializeStorage_Integer									CerializeStorage_Integer;
	#endif
	#ifndef CerializeStorage_Float
	typedef	struct		CerializeStorage_Float										CerializeStorage_Float;
	#endif
	#ifndef CerializeStorage_Complex
	typedef	struct		CerializeStorage_Complex									CerializeStorage_Complex;
	#endif
	#ifndef CerializeStorage_Rational
	typedef	struct		CerializeStorage_Rational									CerializeStorage_Rational;
	#endif
	#ifndef CerializeStorage_String
	typedef	struct		CerializeStorage_String										CerializeStorage_String;
	#endif
	#ifndef CerializeStorage_Symbol
	typedef	struct		CerializeStorage_Symbol										CerializeStorage_Symbol;
	#endif
	#ifndef CerializeStorage_Regexp
	typedef	struct		CerializeStorage_Regexp										CerializeStorage_Regexp;
	#endif
	#ifndef CerializeStorage_FilePath
	typedef	struct		CerializeStorage_FilePath									CerializeStorage_FilePath;
	#endif
	#ifndef CerializeStorage_FileContents
	typedef	struct		CerializeStorage_FileContents							CerializeStorage_FileContents;
	#endif
	#ifndef CerializeStorage_TrueFalse
	typedef	struct		CerializeStorage_TrueFalse								CerializeStorage_TrueFalse;
	#endif
	#ifndef CerializeStorage_ClassName
	typedef	struct		CerializeStorage_ClassName								CerializeStorage_ClassName;
	#endif
	#ifndef CerializeStorage_Array
	typedef	struct		CerializeStorage_Array										CerializeStorage_Array;
	#endif
	#ifndef CerializeStorage_Hash
	typedef	struct		CerializeStorage_Hash											CerializeStorage_Hash;
	#endif
	#ifndef CerializeStorage_NamedStruct
	typedef	struct		CerializeStorage_NamedStruct							CerializeStorage_NamedStruct;
	#endif
	#ifndef CerializeStorage_Struct
	typedef	struct		CerializeStorage_Struct										CerializeStorage_Struct;
	#endif
	#ifndef CerializeStorage_KeyDataPair
	typedef	struct		CerializeStorage_KeyDataPair							CerializeStorage_KeyDataPair;
	#endif

	#ifndef CerializeType
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
		//	Not intended as user type
		CerializeType_KeyDataPair
		
	};
	#endif
	
	#ifndef CerializeType
	struct CerializedData	{
		uint32_t																																						size;
		void*																																								data;
		BOOL																																								free_does_not_free_data;
		CerializeType*																																			type;
		CerializedData_DataFooterTypeForVersion( CerializedDataFooterCurrentVersion )*			footer;
	};
	#endif

		#ifndef CerializeType
		struct GenericCerializedData	{
			
			uint32_t																																						size;
			void*																																								data;
			
		};
		#endif
		
	#ifndef CerializeType
	struct CerializedTypeFooter	{

		CerializeType											type;
		
		uint32_t													magic_number[ 4 ];
		
	};
	#endif

	#ifndef CerializeType
	struct CerializedDataFooter1	{
		
		struct timeval										creation_stamp;
		struct timeval										modification_stamp;

		CerializeType											type;
		
		//	version needs to be last so we can look from the end to check
		int																version;
		uint32_t													magic_number[ 4 ];
		
	};
	#endif

	#ifndef CerializeType
	struct CerializeStorage_Raw	{
	
		void*				raw;
	
	};
	#endif

	#ifndef CerializeType
	struct CerializeStorage_Integer	{
	
		long		integer_value;
		
	};
	#endif

	#ifndef CerializeType
	struct CerializeStorage_Float	{
	
		double	float_value;
	
	};
	#endif

	#ifndef CerializeType
	struct CerializeStorage_Complex	{
	
		double	real;
		double	imaginary;
	
	};
	#endif

	#ifndef CerializeType
	struct CerializeStorage_Rational	{
	
		double	numerator;
		double	denominator;
	
	};
	#endif

	#ifndef CerializeType
	struct CerializeStorage_String	{
		
		char*				string;
	
	};
	#endif

	#ifndef CerializeType
	struct CerializeStorage_Symbol	{

		char*				string;
	
	};
	#endif

	#ifndef CerializeType
	struct CerializeStorage_Regexp	{

		char*				string;
	
	};
	#endif

	#ifndef CerializeType
	struct CerializeStorage_FilePath	{
	
		char*				filepath;
	
	};
	#endif

	#ifndef CerializeType
	struct CerializeStorage_File	{
	
		FILE*				file;
	
	};
	#endif

	#ifndef CerializeType
	struct CerializeStorage_TrueFalse	{
	
		BOOL				truefalse;
		
	};
	#endif

	#ifndef CerializeType
	struct CerializeStorage_ClassName	{
	
		char*				string;
	
	};
	#endif

	#ifndef CerializeType
	struct CerializeStorage_Array	{

		struct GenericCerializedData*	member_array;

	};
	#endif

	#ifndef CerializeType
	struct CerializeStorage_Hash	{

		struct CerializeStorage_KeyValuePair*	key_value_pairs;

	};
	#endif

	#ifndef CerializeType
	struct CerializeStorage_Struct	{

		struct GenericCerializedData*	members;
		
	};
	#endif

	#ifndef CerializeType
	struct CerializeStorage_NamedStruct	{

		struct CerializeStorage_KeyValuePair*	key_value_pairs;

	};
	#endif
	
	#ifndef CerializeType
	struct CerializeStorage_KeyValuePair	{
	
		struct GenericCerializedData	key;
		struct GenericCerializedData	value;
		
	};
	#endif
	
#endif

