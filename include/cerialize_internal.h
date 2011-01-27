/*
 *		Cerialize
 *
 *
 */

#ifndef CERIALIZE_INTERNAL
	#define CERIALIZE_INTERNAL

	#include "Rbdb_BaseStandardInclude.h"

	void CerializedData_internal_createTypeFooter( CerializedData* cerialized_data );
	void CerializedData_internal_createDataFooter( CerializedData* cerialized_data );
	BOOL CerializedData_internal_hasTypeFooter( CerializedData* cerialized_data );
	BOOL CerializedData_internal_hasDataFooter( CerializedData* cerialized_data );
	void CerializedData_internal_updateDataFooter( CerializedData* cerialized_data );
	CerializedData_DataFooterTypeForVersion( CerializedDataFooterCurrentVersion )* CerializedData_internal_upgradeFooter( CerializedData*		cerialized_data );


#endif

