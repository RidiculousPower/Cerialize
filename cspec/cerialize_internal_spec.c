#include <cspec.h>
#include <cspec/cspec_output_header.h>
#include <cspec/cspec_output_verbose.h>
#include <cspec/cspec_output_unit.h>

#include "../include/cerialize.h"

/********
*  new  *
********/

DESCRIBE( CerializedData_new, "CerializedData_new( void* data, uint32_t size )" )
  IT( "maintains raw data of a given size" )

  END_IT
END_DESCRIBE

/************
*  setData  *
*  data     *
************/

DESCRIBE( CerializedData_data, "CerializedData_setData( CerializedData* cerialized_data )" )
  IT( "maintains raw data of a given size" )

  END_IT
END_DESCRIBE

/************
*  setType  *
*  type     *
************/

DESCRIBE( CerializedData_type, "CerializedData_setType( CerializedData* cerialized_data )" )
  IT( "sets and reports a storage type" )

  END_IT
END_DESCRIBE

/************
*  setSize  *
*  size     *
************/

DESCRIBE( CerializedData_setSize, "CerializedData_setSize( CerializedData* cerialized_data )" )
  IT( "maintains raw data of a given size" )

  END_IT
END_DESCRIBE

/**********************
*  creationStamp      *
*  modificationStamp  *
**********************/

DESCRIBE( CerializedData_creationStamp, "CerializedData_creationStamp( CerializedData* cerialized_data )" )
  IT( "maintains raw data of a given size" )

  END_IT
END_DESCRIBE

void Cerialize_spec( void )  {
  
  CSpec_Run( DESCRIPTION( CerializedData_new ), CSpec_NewOutputVerbose() );

}
