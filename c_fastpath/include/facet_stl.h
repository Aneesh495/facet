#ifndef FACET_STL_H
#define FACET_STL_H

#include "facet_types.h"

FacetMesh* facet_stl_read(const char* filepath);
bool facet_stl_write_ascii(const FacetMesh* mesh, const char* filepath, const char* solid_name);
bool facet_stl_write_binary(const FacetMesh* mesh, const char* filepath, const char* header_info);

#endif // FACET_STL_H
