#include <cspec.h>
#include <cspec/cspec_output_header.h>
#include <cspec/cspec_output_verbose.h>
#include <cspec/cspec_output_unit.h>

#include "../include/cerialize.h"

#include <string.h>

/*********************
*  createTypeFooter  *
*********************/

DESCRIBE( CerializedData_internal_createTypeFooter, "CerializedData_internal_createTypeFooter( CerializedData* cerialized_data )" )
  IT( "can create and append a type footer to existing data, or before existing data is set" )
	
	//	before existing data is set
	CerializedData*	cerialized_data	=	calloc( 1, sizeof( CerializedData ) );
	
		//	set footer
		CerializedData_internal_createTypeFooter( cerialized_data );		
		
			//	ensure footer exists
			SHOULD_NOT_BE_NULL( cerialized_data->footer );
				
		//	set data
		char*	new_data	=	"new_data";
		CerializedData_setData(	cerialized_data,
														(void*) new_data,
														( strlen( new_data ) + 1 ) * sizeof( char ) );
		
			//	ensure data exists
			SHOULD_EQUAL( CerializedData_data( cerialized_data ), new_data );
			
			//	ensure footer exists
			SHOULD_NOT_BE_NULL( cerialized_data->footer );
	
	//	free
	CerializedData_free( & cerialized_data );
	
	//	to existing data
	char*	existing_data	=	"existing_data";
	cerialized_data	=	CerializedData_new(	(void*) existing_data,
																				( strlen( existing_data ) + 1 ) * sizeof( char ) );

		//	ensure data exists
		SHOULD_EQUAL( CerializedData_data( cerialized_data ), existing_data );		
		
		//	ensure footer exists
		SHOULD_NOT_BE_NULL( cerialized_data->footer );
	
  END_IT
END_DESCRIBE

/*********************
*  createDataFooter  *
*********************/

DESCRIBE( CerializedData_internal_createDataFooter, "CerializedData_internal_createDataFooter( CerializedData* cerialized_data )" )
  IT( "can create and append a data footer to existing data, or before existing data is set" )

  END_IT
END_DESCRIBE

/******************
*  hasTypeFooter  *
******************/

DESCRIBE( CerializedData_internal_hasTypeFooter, "CerializedData_internal_hasTypeFooter( CerializedData* cerialized_data )" )
  IT( "can report whether it has a type footer" )

  END_IT
END_DESCRIBE

/******************
*  hasDataFooter  *
******************/

DESCRIBE( CerializedData_internal_hasDataFooter, "CerializedData_internal_hasDataFooter( CerializedData* cerialized_data )" )
  IT( "can report whether it has a data footer" )

  END_IT
END_DESCRIBE

/*********************
*  updateDataFooter  *
*********************/

DESCRIBE( CerializedData_internal_updateDataFooter, "CerializedData_internal_updateDataFooter( CerializedData* cerialized_data )" )
  IT( "can update a footer that was previously created" )

  END_IT
END_DESCRIBE

void Cerialize_spec( void )  {
  
  CSpec_Run( DESCRIPTION( CerializedData_internal_createTypeFooter ), CSpec_NewOutputVerbose() );

}
