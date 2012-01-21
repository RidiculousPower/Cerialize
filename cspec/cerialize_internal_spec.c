#include <cspec.h>
#include <cspec/cspec_output_header.h>
#include <cspec/cspec_output_verbose.h>
#include <cspec/cspec_output_unit.h>

#include "../include/cerialize.h"

#include <string.h>

/*********************
*  createTypeFooter  *
*********************/

DESCRIBE( CerializedData_internal_createTypeFooter, "\n * CerializedData_internal_createTypeFooter( CerializedData* cerialized_data )" )
  IT( "can create and append a type footer to existing data, or before existing data is set" )
  
  //  before existing data is set
  CerializedData*  cerialized_data  =  calloc( 1, sizeof( CerializedData ) );
  
    //  set footer
    CerializedData_internal_createTypeFooter( cerialized_data );    
    
      //  ensure footer exists
      SHOULD_NOT_BE_NULL( cerialized_data->type );
        
    //  set data
    char*  new_data  =  strdup( "new_data" );
    CerializedData_setData(  cerialized_data,
                            (void**) & new_data,
                            ( strlen( new_data ) + 1 ) * sizeof( char ) );
    
      //  ensure data exists
      SHOULD_BE_TRUE( strcmp( CerializedData_data( cerialized_data ), new_data ) == 0 );
      
      //  ensure footer exists
      SHOULD_NOT_BE_NULL( cerialized_data->type );
  
  //  free
  CerializedData_free( & cerialized_data );
  
  //  to existing data
  char*  existing_data  =  strdup( "existing_data" );
  cerialized_data  =  CerializedData_new(  (void**) & existing_data,
                                        ( strlen( existing_data ) + 1 ) * sizeof( char ) );

    //  ensure data exists
    SHOULD_BE_TRUE( strcmp( CerializedData_data( cerialized_data ), existing_data ) == 0 );

    //  set footer
    CerializedData_internal_createTypeFooter( cerialized_data );    
    
    //  ensure footer exists
    SHOULD_NOT_BE_NULL( cerialized_data->type );

  //  free
  CerializedData_free( & cerialized_data );
  
  END_IT
END_DESCRIBE

/*********************
*  createDataFooter  *
*********************/

DESCRIBE( CerializedData_internal_createDataFooter, "\n * CerializedData_internal_createDataFooter( CerializedData* cerialized_data )" )
  IT( "can create and append a data footer to existing data, or before existing data is set" )

  //  before existing data is set
  CerializedData*  cerialized_data  =  calloc( 1, sizeof( CerializedData ) );
  
    //  set footer
    CerializedData_internal_createDataFooter( cerialized_data );    
    
      //  ensure footer exists
      SHOULD_NOT_BE_NULL( cerialized_data->footer );
        
    //  set data
    char*  new_data  =  strdup( "new_data" );
    CerializedData_setData(  cerialized_data,
                            (void**) & new_data,
                            ( strlen( new_data ) + 1 ) * sizeof( char ) );
    
      char*  cerialized_raw_data  =  CerializedData_data( cerialized_data );
      //  ensure data exists
      SHOULD_BE_TRUE( strcmp( cerialized_raw_data, "new_data" ) == 0 );
      
      //  ensure footer exists
      SHOULD_NOT_BE_NULL( cerialized_data->footer );
  
  //  free
  CerializedData_free( & cerialized_data );
  
  //  to existing data
  char*  existing_data  =  strdup( "existing_data" );
  cerialized_data  =  CerializedData_new(  (void**) & existing_data,
                                        ( strlen( existing_data ) + 1 ) * sizeof( char ) );

    //  ensure data exists
    SHOULD_BE_TRUE( strcmp( CerializedData_data( cerialized_data ), "existing_data" ) == 0 );

    //  set footer
    CerializedData_internal_createDataFooter( cerialized_data );    
    
    //  ensure footer exists
    SHOULD_NOT_BE_NULL( cerialized_data->footer );

  //  free
  CerializedData_free( & cerialized_data );

  END_IT
END_DESCRIBE

/******************
*  hasTypeFooter  *
******************/

DESCRIBE( CerializedData_internal_hasTypeFooter, "\n * CerializedData_internal_hasTypeFooter( CerializedData* cerialized_data )" )
  IT( "can report whether it has a type footer" )

  CerializedData*  cerialized_data  =  calloc( 1, sizeof( CerializedData ) );
  
  SHOULD_BE_FALSE( CerializedData_internal_hasTypeFooter( cerialized_data ) );
  
  CerializedData_internal_createTypeFooter( cerialized_data );    

  SHOULD_BE_TRUE( CerializedData_internal_hasTypeFooter( cerialized_data ) );
  SHOULD_BE_FALSE( CerializedData_internal_hasDataFooter( cerialized_data ) );

  CerializedData_free( & cerialized_data );

  END_IT
END_DESCRIBE

/******************
*  hasDataFooter  *
******************/

DESCRIBE( CerializedData_internal_hasDataFooter, "\n * CerializedData_internal_hasDataFooter( CerializedData* cerialized_data )" )
  IT( "can report whether it has a data footer" )

  CerializedData*  cerialized_data  =  calloc( 1, sizeof( CerializedData ) );
  
  SHOULD_BE_FALSE( CerializedData_internal_hasDataFooter( cerialized_data ) );
  
  CerializedData_internal_createDataFooter( cerialized_data );    

  SHOULD_BE_TRUE( CerializedData_internal_hasDataFooter( cerialized_data ) );
  SHOULD_BE_FALSE( CerializedData_internal_hasTypeFooter( cerialized_data ) );

  CerializedData_free( & cerialized_data );

  END_IT
END_DESCRIBE

/*********************
*  updateDataFooter  *
*********************/

DESCRIBE( CerializedData_internal_updateDataFooter, "\n * CerializedData_internal_updateDataFooter( CerializedData* cerialized_data )" )
  IT( "can update a footer that was previously created" )

  CerializedData*  cerialized_data  =  calloc( 1, sizeof( CerializedData ) );

  CerializedData_internal_createDataFooter( cerialized_data );    

  SHOULD_EQUAL( cerialized_data->footer->creation_stamp.tv_sec, cerialized_data->footer->modification_stamp.tv_sec );
  SHOULD_EQUAL( cerialized_data->footer->creation_stamp.tv_usec, cerialized_data->footer->modification_stamp.tv_usec );

  CerializedData_internal_updateDataFooter( cerialized_data );

  SHOULD_NOT_EQUAL( cerialized_data->footer->creation_stamp.tv_usec, cerialized_data->footer->modification_stamp.tv_usec );

  CerializedData_free( & cerialized_data );
    
  END_IT
END_DESCRIBE

/**************************************************************************************************************/

/****************************
*  Cerialize_internal_spec  *
****************************/

void Cerialize_internal_spec( void )  {
  
  CSpec_Run( DESCRIPTION( CerializedData_internal_createTypeFooter ), CSpec_NewOutputVerbose() );
  CSpec_Run( DESCRIPTION( CerializedData_internal_createDataFooter ), CSpec_NewOutputVerbose() );
  CSpec_Run( DESCRIPTION( CerializedData_internal_hasTypeFooter ), CSpec_NewOutputVerbose() );
  CSpec_Run( DESCRIPTION( CerializedData_internal_hasDataFooter ), CSpec_NewOutputVerbose() );
  CSpec_Run( DESCRIPTION( CerializedData_internal_updateDataFooter ), CSpec_NewOutputVerbose() );

}
