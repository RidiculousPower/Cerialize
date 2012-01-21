#include <cspec.h>
#include <cspec/cspec_output_header.h>
#include <cspec/cspec_output_verbose.h>
#include <cspec/cspec_output_unit.h>

#include <string.h>

#include "cerialize.h"

/********
*  new  *
********/

DESCRIBE( CerializedData_new, "\n * CerializedData_new( void* data, uint32_t size )" )
  IT( "can be created with raw data of a given size" )

  char*  data  =  strdup( "storage string" );
  CerializedData*  cerialized_data  =  CerializedData_new(  (void**) & data,
                                                        ( strlen( data ) + 1 ) * sizeof( char ) );

  SHOULD_EQUAL( cerialized_data->data, data );
  SHOULD_EQUAL( cerialized_data->size, ( strlen( data ) + 1 ) * sizeof( char ) );
  
  CerializedData_free( & cerialized_data );
  
  END_IT
END_DESCRIBE

/************
*  setData  *
*  data     *
*  size     *
************/

DESCRIBE( CerializedData_setData_data_size, "\n * CerializedData_setData( CerializedData* cerialized_data, void** data, uint32_t size )\n * CerializedData_data( CerializedData* cerialized_data )\n * CerializedData_size( CerializedData* cerialized_data )" )
  IT( "can set and return raw data of a given size and the size" )

  CerializedData*  cerialized_data  =  calloc( 1, sizeof( CerializedData ) );
  
  char*  data  =  strdup( "data" );

  CerializedData_setData(  cerialized_data,
                          (void**) & data,
                          ( strlen( data ) + 1 ) * sizeof( char ) );

  SHOULD_EQUAL( cerialized_data->data, data );

  CerializedData_free( & cerialized_data );

  END_IT
END_DESCRIBE

/************
*  setType  *
*  type     *
************/

DESCRIBE( CerializedData_setType_type, "\n * CerializedData_setType( CerializedData* cerialized_data, CerializeType type )\n * CerializedData_type( CerializedData* cerialized_data )" )
  IT( "sets and reports a storage type" )

  char*  data  =  strdup( "storage string" );
  CerializedData*  cerialized_data  =  CerializedData_new(  (void**) & data,
                                                        ( strlen( data ) + 1 ) * sizeof( char ) );
  CerializedData_setType(  cerialized_data,
                          CerializeType_Symbol );
  SHOULD_EQUAL( CerializedData_type( cerialized_data ), CerializeType_Symbol );

  CerializedData_free( & cerialized_data );
  
  END_IT
END_DESCRIBE

/**********************
*  creationStamp      *
*  modificationStamp  *
**********************/

DESCRIBE( CerializedData_creationStamp_modificationStamp, "\n * CerializedData_creationStamp( CerializedData* cerialized_data )\n * CerializedData_modificationStamp( CerializedData* cerialized_data )" )
  IT( "can maintain creation and modification stamps" )

  char*  data  =  strdup( "storage string" );
  CerializedData*  cerialized_data  =  CerializedData_new(  (void**) & data,
                                                        ( strlen( data ) + 1 ) * sizeof( char ) );

  CerializedData_internal_createDataFooter( cerialized_data );
  
  SHOULD_NOT_BE_NULL( cerialized_data->footer->creation_stamp.tv_sec );
  SHOULD_NOT_BE_NULL( cerialized_data->footer->creation_stamp.tv_usec );

  //  creation/modification should be same
  SHOULD_EQUAL(      cerialized_data->footer->creation_stamp.tv_usec, cerialized_data->footer->modification_stamp.tv_usec );

  CerializedData_internal_updateDataFooter( cerialized_data );

  //  modification should have changed
  SHOULD_NOT_EQUAL( cerialized_data->footer->creation_stamp.tv_usec, cerialized_data->footer->modification_stamp.tv_usec );

  CerializedData_free( & cerialized_data );

  END_IT
END_DESCRIBE

/**************************************************************************************************************/

/*******************
*  Cerialize_spec  *
*******************/

void Cerialize_spec( void )  {
  
  CSpec_Run( DESCRIPTION( CerializedData_new ), CSpec_NewOutputVerbose() );
  CSpec_Run( DESCRIPTION( CerializedData_setData_data_size ), CSpec_NewOutputVerbose() );
  CSpec_Run( DESCRIPTION( CerializedData_setType_type ), CSpec_NewOutputVerbose() );
  CSpec_Run( DESCRIPTION( CerializedData_creationStamp_modificationStamp ), CSpec_NewOutputVerbose() );

}
