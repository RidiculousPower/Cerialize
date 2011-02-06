#include <cspec.h>

#include <ruby.h>

#include "cspec/rcerialize_pack_unpack_spec.h"

int main( void )  {

  ruby_init();
  
  Rcerialize_pack_unpack_pack_unpack_spec();

}
