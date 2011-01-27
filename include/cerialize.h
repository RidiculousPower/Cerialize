/*
 *		Cerialize
 *
 *
 */

#ifndef CERIALIZE
	#define CERIALIZE

	#include "Rbdb_BaseStandardInclude.h"

	CerializedData* CerializedData_new(	void*				raw_data,
																	uint32_t		raw_data_size );
	void CerializedData_free( CerializedData**	cerialized_data );
	void* CerializedData_data( CerializedData*	cerialized_data );
	void CerializedData_setData(	CerializedData*		cerialized_data,
													void*							data_raw,
													uint32_t					data_size );
	CerializeType CerializedData_type( CerializedData* cerialized_data );
	void CerializedData_setType(	CerializedData*		cerialized_data,
													CerializeType			type );
	uint32_t CerializedData_size( CerializedData* cerialized_data );
	struct timeval* CerializedData_creationStamp( CerializedData* cerialized_data );
	struct timeval* CerializedData_modificationStamp( CerializedData* cerialized_data );

#endif

