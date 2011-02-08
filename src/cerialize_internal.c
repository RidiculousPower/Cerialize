/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include <string.h>
#include <sys/time.h>

#include "cerialize/cerialize.h"
#include "cerialize/cerialize_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*********************
*  createTypeFooter  *
*********************/

void CerializedData_internal_createTypeFooter( CerializedData* cerialized_data )	{

	cerialized_data->size		+=	sizeof( CerializedTypeFooter );
	if ( cerialized_data->data == NULL )	{
		cerialized_data->data		=		calloc( 1, cerialized_data->size );	
	}
	else	{
		cerialized_data->data		=		realloc( cerialized_data->data, cerialized_data->size );
	}
	
	CerializedTypeFooter*		type_footer			=	cerialized_data->data + cerialized_data->size - sizeof( CerializedTypeFooter );

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

  CerializeType type =  CerializeType_Raw;

  //  if we have a type footer already we need to convert it to a data footer
  if ( CerializedData_internal_hasTypeFooter( cerialized_data ) ) {
  
    //  get the type
    type  = CerializedData_type( cerialized_data );
    
    //  remove type footer size for realloc to add size for data footer
    cerialized_data->size -=  sizeof( CerializedTypeFooter );
    
  }

	cerialized_data->size		+=	sizeof( CerializedData_DataFooterTypeForVersion( CerializedDataFooterCurrentVersion ) );
	if ( cerialized_data->data == NULL )	{
		cerialized_data->data		=		calloc( 1, cerialized_data->size );	
	}
	else	{
		cerialized_data->data		=		realloc( cerialized_data->data, cerialized_data->size );
	}

	cerialized_data->footer		=	cerialized_data->data + cerialized_data->size - sizeof( CerializedData_DataFooterTypeForVersion( CerializedDataFooterCurrentVersion ) );
  
  //  * type
  cerialized_data->footer->type = type;
	cerialized_data->type         =	& cerialized_data->footer->type;

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
