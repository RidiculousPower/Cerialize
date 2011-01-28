
#ifndef CERIALIZE_MACROS
	#define CERIALIZE_MACROS

	#define CerializedDataFooterCurrentVersion																		1

	//	we need two macros so the version macro is resolved before being concatenated
	#define CerializedData_DataFooterTypeForVersion( version )										CerializedData_DataFooterTypeForVersion_concat( version )
	#define CerializedData_DataFooterTypeForVersion_concat( version )							CerializedDataFooter ## version

#endif

