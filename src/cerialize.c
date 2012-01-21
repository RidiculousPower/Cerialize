/*
 *    Cerialize
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

#include "cerialize/cerialize.h"
#include "cerialize/cerialize_internal.h"
  
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
                                    Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/********
*  new  *
********/

CerializedData* CerializedData_new(  void**      raw_data,
                                     uint32_t    raw_data_size )  {

  CerializedData*  cerialized_data  =  calloc( 1, sizeof( CerializedData ) );
  
  cerialized_data->data  =  *raw_data;
  cerialized_data->size  =  raw_data_size;
  
  if ( CerializedData_internal_hasTypeFooter( cerialized_data ) )  {
  
    CerializedTypeFooter*    type_footer  =  cerialized_data->data + cerialized_data->size - sizeof( CerializedTypeFooter );
    cerialized_data->type  = & type_footer->type;
  }
  else if ( CerializedData_internal_hasDataFooter( cerialized_data ) )  {
    
    CerializedData_DataFooterTypeForVersion( CerializedDataFooterCurrentVersion )*  data_footer  =  cerialized_data->data 
                                                                                                 + cerialized_data->size 
                                                                                                 - sizeof( CerializedData_DataFooterTypeForVersion( CerializedDataFooterCurrentVersion ) );
    cerialized_data->footer  =    data_footer;    
    cerialized_data->type    =    & data_footer->type;
  }
  
  return cerialized_data;
}

/*********
*  free  *
*********/

void CerializedData_free( CerializedData**  cerialized_data )  {

  //  we assume if we have a raw data pointer that we allocated it and are now done with it
  //  if we want to keep the pointer while freeing CerializeData, set data to NULL before freeing
  if (    ( *cerialized_data )->data != NULL
      &&  ! ( *cerialized_data )->free_does_not_free_data )  {

    free( ( *cerialized_data )->data );
    ( *cerialized_data )->data = NULL;
  }
  
  free( *cerialized_data );
  *cerialized_data  =  NULL;
}

/*********
*  data  *
*********/

void* CerializedData_data( CerializedData*  cerialized_data )  {
  
  //  if we have data but it is only a footer or only a type, return NULL
  void*  raw_data  =  NULL;
  
  if (    cerialized_data->data
      &&  (  (    cerialized_data->footer != NULL
              ||  cerialized_data->size != sizeof( CerializedData_DataFooterTypeForVersion( CerializedDataFooterCurrentVersion ) )  )
         ||  (    cerialized_data->type != NULL
              ||  cerialized_data->size != sizeof( CerializedTypeFooter ) ) ) )  {

    raw_data  =  cerialized_data->data;
  }

  return raw_data;
}

/************
*  setData  *
************/

//  we want a void** instead of a void* so that if we realloc() we don't quash the caller's pointer
void CerializedData_setData(  CerializedData*    cerialized_data,
                              void**            data_raw,
                              uint32_t          data_size )  {

  //  if we already have data and our data is the size of a footer, we need to copy our data and the footer into a new structure
  if ( cerialized_data->footer != NULL )  {
        
    //  re-allocate data to hold footer at end
    *data_raw  =  realloc( *data_raw, data_size + sizeof( CerializedData_DataFooterTypeForVersion( CerializedDataFooterCurrentVersion ) ) );
    
    //  copy footer to new data
    memcpy( *data_raw + data_size,
            cerialized_data->footer,
            sizeof( CerializedData_DataFooterTypeForVersion( CerializedDataFooterCurrentVersion ) ) );

    cerialized_data->footer  =  *data_raw + data_size;
    
    data_size  =  data_size +  sizeof( CerializedData_DataFooterTypeForVersion( CerializedDataFooterCurrentVersion ) );
    
    free( cerialized_data->data );

    cerialized_data->data  =  *data_raw;
    cerialized_data->size  =  data_size;
  }
  else if ( cerialized_data->type != NULL )  {

    CerializeType  current_type  =  CerializedData_type( cerialized_data );

    free( cerialized_data->data );
    cerialized_data->data  =  *data_raw;
    cerialized_data->size  =  data_size;

    CerializedData_internal_createTypeFooter( cerialized_data );

    CerializedData_setType( cerialized_data, current_type );

  }
  else if ( cerialized_data->data != NULL )  {
    
    free( cerialized_data->data );

    cerialized_data->data  =  *data_raw;
    cerialized_data->size  =  data_size;
  }  
  else {

    cerialized_data->data  =  *data_raw;
    cerialized_data->size  =  data_size;
    
  }

}

/*********
*  type  *
*********/

CerializeType CerializedData_type( CerializedData* cerialized_data )  {

  return *cerialized_data->type;
}

/******************
*  setType  *
******************/

void CerializedData_setType(  CerializedData*    cerialized_data,
                              CerializeType      type )  {

  if ( cerialized_data->type == NULL )  {

    CerializedData_internal_createTypeFooter( cerialized_data );
    
  }

  *cerialized_data->type        =    type;
}

/*********
*  size  *
*********/

//  Note that applications can determine the length of a record by setting the ulen field 
//  (CerializebaseRecordSettingsController_dataBufferSize) to 0 and checking the return value in the size field.
uint32_t CerializedData_size( CerializedData* cerialized_data )  {

  //  get the size
  uint32_t  size  =  cerialized_data->size;
  
  if ( cerialized_data->footer != NULL )  {
    size -= sizeof( CerializedData_DataFooterTypeForVersion( CerializedDataFooterCurrentVersion ) );
  }
  else if ( cerialized_data->type != NULL )  {
    size -= sizeof( CerializedTypeFooter );  
  }

  return size;
}  


/******************
*  creationStamp  *
******************/

struct timeval* CerializedData_creationStamp( CerializedData* cerialized_data )  {
  
  struct timeval*  creation_stamp  =  NULL;
  
  if ( cerialized_data->footer != NULL )  {

    creation_stamp  =  & cerialized_data->footer->creation_stamp;

  }

  return creation_stamp;
}

/**********************
*  modificationStamp  *
**********************/

struct timeval* CerializedData_modificationStamp( CerializedData* cerialized_data )  {
    
  struct timeval*  modification_stamp  =  NULL;
    
  if ( cerialized_data->footer != NULL )  {

    modification_stamp  =  & cerialized_data->footer->modification_stamp;

  }
    
  return modification_stamp;
}

/*********************
*  setDataNotToFree  *
*********************/

void CerializedData_setDataNotToFree(  CerializedData*    cerialized_data  )  {

  cerialized_data->free_does_not_free_data  =  TRUE;
}

/******************
*  setDataToFree  *
******************/

void CerializedData_setDataToFree(  CerializedData*    cerialized_data  )  {

  cerialized_data->free_does_not_free_data  =  FALSE;
}

