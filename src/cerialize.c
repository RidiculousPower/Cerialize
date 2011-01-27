/*
 *		Cerialize
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include <string.h>
#include <sys/time.h>

#include "CerializedData.h"
#include "CerializedData_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/********
*  new  *
********/

CerializedData* CerializedData_new(	void*				raw_data,
																		uint32_t		raw_data_size )	{

	CerializedData*	cerialized_data	=	calloc( 1, sizeof( CerializedData ) );
	
	cerialized_data->data	=	raw_data;
	cerialized_data->size	=	raw_data_size;
	
	if ( CerializedData_internal_hasTypeFooter( cerialized_data ) )	{
		
	}
	else if ( CerializedData_internal_hasDataFooter( cerialized_data ) )	{
	
	}
	
	return cerialized_data;
}

/*********
*  free  *
*********/

void CerializedData_free( CerializedData**	cerialized_data )	{

	//	we assume if we have a raw data pointer that we allocated it and are now done with it
	//	if we want to keep the pointer while freeing CerializeData, set data to NULL before freeing
	if ( ( *cerialized_data )->data != NULL )	{
		free( ( *cerialized_data )->data );
		( *cerialized_data )->data = NULL;
	}
	
	free( *cerialized_data );
	*cerialized_data	=	NULL;
}

/*********
*  data  *
*********/

void* CerializedData_data( CerializedData*	cerialized_data )	{
	
	//	if we have data but it is only a footer or only a type, return NULL
	void*	raw_data	=	NULL;
	
	if (		cerialized_data->data
			&&	(		(		cerialized_data->footer != NULL
							||	cerialized_data->size != sizeof( CerializedData_DataFooterTypeForVersion( CerializedDataFooterCurrentVersion ) )	)
					||	(		cerialized_data->type != NULL
							||	cerialized_data->size != sizeof( CerializedTypeFooter ) ) ) )	{

		raw_data	=	cerialized_data->data;
	}

	return raw_data;
}

/******************
*  setRawData  *
******************/

void CerializedData_setData(	CerializedData*		cerialized_data,
															void*							data_raw,
															uint32_t					data_size )	{

	//	if we already have data and our data is the size of a footer, we need to copy our data and the footer into a new structure
	if ( cerialized_data->footer != NULL )	{
				
		//	re-allocate data to hold footer at end
		data_size	=	data_size +	sizeof( CerializedData_DataFooterTypeForVersion( CerializedDataFooterCurrentVersion ) );
		data_raw	=	realloc( data_raw, data_size );

		//	copy footer to new data
		memcpy(	data_raw,
						cerialized_data->footer,
						sizeof( CerializedData_DataFooterTypeForVersion( CerializedDataFooterCurrentVersion ) ) );
		
		cerialized_data->footer	=	data_raw;
		
		free( cerialized_data->data );

		cerialized_data->data	=	data_raw;
		cerialized_data->size	=	data_size;
	}
	else if ( cerialized_data->type != NULL )	{

		data_size	=	data_size +	sizeof( CerializedTypeFooter );
		data_raw	=	realloc( data_raw, data_size );
		
		//	copy type over
		memcpy(	data_raw,
						cerialized_data->type,
						sizeof( CerializedTypeFooter ) );
		
		void*	old_data				=	cerialized_data->data;
		cerialized_data->data	=	data_raw;
		cerialized_data->size	=	data_size;
		
		CerializedData_setType( cerialized_data, *cerialized_data->type );
		
		free( old_data );
	
	}
	else if ( cerialized_data->data != NULL )	{
		
		free( cerialized_data->data );

		cerialized_data->data	=	data_raw;
		cerialized_data->size	=	data_size;
	}	
	else {

		cerialized_data->data	=	data_raw;
		cerialized_data->size	=	data_size;
		
	}

}

/*********
*  type  *
*********/

CerializeType CerializedData_type( CerializedData* cerialized_data )	{

	return *cerialized_data->type;
}

/******************
*  setType  *
******************/

void CerializedData_setType(	CerializedData*		cerialized_data,
															CerializeType			type )	{

	if ( cerialized_data->type != NULL )	{

		*cerialized_data->type				=	type;
	
	}
	else {
		
		cerialized_data->type					=	cerialized_data->data + cerialized_data->size;
		
		//	realloc for type
		cerialized_data->data					=	realloc( cerialized_data->data, cerialized_data->size + sizeof( CerializedTypeFooter ) );
		
		*cerialized_data->type				=	type;
		
	}

}

/*********
*  size  *
*********/

//	Note that applications can determine the length of a record by setting the ulen field 
//	(CerializebaseRecordSettingsController_dataBufferSize) to 0 and checking the return value in the size field.
uint32_t CerializedData_size( CerializedData* cerialized_data )	{

	//	get the size
	uint32_t	size	=	cerialized_data->size;
	
	if ( cerialized_data->footer != NULL )	{
		size -= sizeof( CerializedData_DataFooterTypeForVersion( CerializedDataFooterCurrentVersion ) );
	}
	else if ( cerialized_data->type != NULL )	{
		size -= sizeof( CerializedTypeFooter );	
	}

	return size;
}	


/******************
*  creationStamp  *
******************/

struct timeval* CerializedData_creationStamp( CerializedData* cerialized_data )	{
	
	struct timeval*	creation_stamp	=	NULL;
	
	if ( cerialized_data->footer != NULL )	{

		creation_stamp	=	& cerialized_data->footer->creation_stamp;

	}

	return creation_stamp;
}

/**********************
*  modificationStamp  *
**********************/

struct timeval* CerializedData_modificationStamp( CerializedData* cerialized_data )	{
		
	struct timeval*	modification_stamp	=	NULL;
		
	if ( cerialized_data->footer != NULL )	{

		modification_stamp	=	& cerialized_data->footer->modification_stamp;

	}
		
	return modification_stamp;
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*********************
*  createTypeFooter  *
*********************/

void CerializedData_internal_createTypeFooter( CerializedData* cerialized_data )	{

	CerializedTypeFooter*	type_footer	=	cerialized_data->data + cerialized_data->size;

	cerialized_data->size		+=	sizeof( CerializedTypeFooter );
	cerialized_data->data		=		realloc( cerialized_data->data, cerialized_data->size );

	//	* magic number for identifying presence of key footer ("0 food, feed food!")
	type_footer->magic_number[ 0 ]	=	0x0;
	type_footer->magic_number[ 1 ]	=	0x0000F00D;
	type_footer->magic_number[ 2 ]	=	0xF33DF00D;
	type_footer->magic_number[ 3 ]	=	0x0;
	
	cerialized_data->type	=	& type_footer->type;
	
}

/*********************
*  createDataFooter  *
*********************/

void CerializedData_internal_createDataFooter( CerializedData* cerialized_data )	{

	cerialized_data->footer	=	cerialized_data->data + cerialized_data->size - sizeof( CerializedData_DataFooterTypeForVersion( CerializedDataFooterCurrentVersion ) );

	cerialized_data->size		+=	sizeof( CerializedData_DataFooterTypeForVersion( CerializedDataFooterCurrentVersion ) );
	cerialized_data->data		=		realloc( cerialized_data->data, cerialized_data->size );

	//	* magic number for identifying presence of data footer ("1 food, face food!")
	cerialized_data->footer->magic_number[ 0 ]	=	0x1;
	cerialized_data->footer->magic_number[ 1 ]	=	0x0001F00D;
	cerialized_data->footer->magic_number[ 2 ]	=	0xFACEF00D;
	cerialized_data->footer->magic_number[ 3 ]	=	0x1;

	//	* version for possible later changes to footer format
	cerialized_data->footer->version			=	CerializedDataFooterCurrentVersion;
	
	//	* creation stamp
	gettimeofday(	& cerialized_data->footer->creation_stamp, NULL );
	
	//	* modification stamp (should be the same, so we copy the values)
	cerialized_data->footer->modification_stamp.tv_sec		=	cerialized_data->footer->creation_stamp.tv_sec;
	cerialized_data->footer->modification_stamp.tv_usec		=	cerialized_data->footer->creation_stamp.tv_usec;
	
}

/******************
*  hasTypeFooter  *
******************/

BOOL CerializedData_internal_hasTypeFooter( CerializedData* cerialized_data )	{
	
	BOOL	magic_number_matched	=	FALSE;
		
	if ( cerialized_data->size >= ( sizeof( uint32_t ) * 4 ) )	{

		uint32_t*	magic_number = cerialized_data->data + cerialized_data->size - ( sizeof( uint32_t ) * 4 );
		
		if (		magic_number[ 0 ]	== 0x0
				&&	magic_number[ 1 ] == 0x0000F00D
				&&	magic_number[ 2 ] == 0xF33DF00D
				&&	magic_number[ 3 ] == 0x0 )	{
		
			magic_number_matched = TRUE;
		}
	}
	
	return magic_number_matched;
}

/******************
*  hasDataFooter  *
******************/

BOOL CerializedData_internal_hasDataFooter( CerializedData* cerialized_data )	{

	BOOL	magic_number_matched	=	FALSE;
		
	if ( cerialized_data->size >= ( sizeof( uint32_t ) * 4 ) )	{
	
		uint32_t*	magic_number = cerialized_data->data + cerialized_data->size - ( sizeof( uint32_t ) * 4 );
		
		if (		magic_number[ 0 ]	== 0x1
				&&	magic_number[ 1 ] == 0x0001F00D
				&&	magic_number[ 2 ] == 0xFACEF00D
				&&	magic_number[ 3 ] == 0x1 )	{
		
			magic_number_matched = TRUE;
		}
	}
	
	return magic_number_matched;
}

/*****************
*  updateFooter  *
*****************/

void CerializedData_internal_updateDataFooter( CerializedData* cerialized_data )	{

	//	get a new modification stamp
	gettimeofday(	& cerialized_data->footer->modification_stamp, NULL );
		
}

/******************
*  upgradeFooter  *
******************/

//	return footer from a record that currently has a footer, regardless whether it has been written to database
CerializedData_DataFooterTypeForVersion( CerializedDataFooterCurrentVersion )* CerializedData_internal_upgradeFooter( CerializedData*		cerialized_data )	{

	//	loop until record is current version
	//	each loop is responsible for updating version by 1
	while ( cerialized_data->footer->version < CerializedDataFooterCurrentVersion )	{
	
		switch ( cerialized_data->footer->version )	{
			
			case CerializedDataFooterCurrentVersion:
				// current - nothing to do
				break;
			
		}

	}

	return cerialized_data->footer;
}
